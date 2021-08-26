#include "Worker.hh"

#include <chrono>

#include "Entities/Shapes/RTShape.hh"
#include "IntersectionData.hh"
#include "Object.hh"
#include "Tools/Stat.hh"

namespace Rayon
{
  Worker::Worker(RawImage* img, uint32 xStart, uint32 xStop, Tools::Stat* stat)
    : _img(img)
    , _xStart(xStart)
    , _xStop(xStop)
    , _stat(stat)
    , _shouldStop(std::make_shared<std::atomic_bool>(false))
    , sigFinished(std::make_shared<sigs::signal<void()>>())
  {
  }

  void Worker::stop()
  {
    _shouldStop->store(true);
  }

  void Worker::operator()(uint32 width, uint32 height, const Scene* scene)
  {
    auto start = std::chrono::steady_clock::now();
    Ray  cameraRay(RayType::Primary, scene->eye().getPos(), Vec_t());

    Float_t fovX = Tools::DegToRad(55.0);
    Float_t fovY = (fovX * height) / width;

    Float_t angleV = fovX / width;
    Float_t angleH = fovY / height;

    for (uint32 x = _xStart; x < _xStop; ++x)
    {
      for (uint32 y = 0; y < height; ++y)
      {
        Float_t tmpAngleV = fovX / 2 - angleV * x;
        Float_t tmpAngleH = fovY / 2 - angleH * y;
        Float_t cosV      = Tools::Cos(tmpAngleV);
        Float_t cosH      = Tools::Cos(tmpAngleH);

        Vec_t tmp{
          Tools::Sin(tmpAngleV) * cosH,
          Tools::Sin(tmpAngleH) * cosV,
          cosH * cosV,
        };

        cameraRay.setDirection(tmp);
        cameraRay.setDirection(scene->eye().indirectRotation(tmp));
        cameraRay.normalize();

        auto color        = scene->inter(cameraRay, 0, _stat);
        _img->pixel(x, y) = color;

        if (_shouldStop->load())
        {
          return;
        }
      }
    }

    auto end       = std::chrono::steady_clock::now();
    _stat->elapsed = end - start;

    (*sigFinished)();
  }

  namespace
  {
    static constexpr const uint8 MAX_DEPTH  = 5;
    static constexpr const uint8 MAX_GLOSSY = 5;

    Color handleReflection(const Scene&            scene,
                           const Ray&              ray,
                           const IntersectionData& data,
                           uint8                   depth)
    {
      Float_t materialGlossiness = data.obj->getMaterial()->getGlossiness(data);
      Ray     reflected(
        RayType::Reflected, data.point, Tools::Reflect(ray.getDirection(), data.normal));

      if (materialGlossiness > Globals::Epsilon)
      {
        Color   color;
        Float_t g            = materialGlossiness;
        Vec_t   reflectedDir = reflected.getDirection();

        for (auto i = 0u; i < MAX_GLOSSY; ++i)
        {
          Vec_t tmp(((rand() % 100) - 50.0) / (100.0 * g),
                    1.0 * ((rand() % 100) - 50.0) / (100.0 * g),
                    ((rand() % 100) - 50.0) / (100.0 * g));
          reflected.setDirection(reflectedDir + tmp);
          reflected.normalize();
          reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
          color += scene.inter(reflected, depth + 1, data.stat);
        }

        return color * (Float_t(1.0) / MAX_GLOSSY);
      }

      reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
      return scene.inter(reflected, depth + 1, data.stat);
    }

    Color handleTransparency(const Scene&            scene,
                             const Ray&              ray,
                             const IntersectionData& data,
                             uint8                   depth)
    {
      Ray     refracted(RayType::Transparency, data.point, ray.getDirection());
      Float_t eta = data.obj->getMaterial()->getRefraction(data);

      if (eta != 1 && eta > Globals::Epsilon)
        refracted.setDirection(Tools::Refract(ray.getDirection(), data, eta));

      refracted.setOrigin(data.point + Globals::Epsilon * refracted.getDirection());

      return scene.inter(refracted, depth + 1, data.stat);
    }

    // http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
    Float_t getFresnelReflectance(const IntersectionData& data, const Ray& ray)
    {
      Float_t n1 = data.obj->getMaterial()->getRefraction(data);
      Float_t n2 = 1.0;

      Float_t cosI = -Tools::DotProduct(ray.getDirection(), data.normal);
      if (cosI > Globals::Epsilon)
      {
        n2 = n1;
        n1 = 1.0;
      }
      else
        cosI *= -1;

      Float_t n     = n1 / n2;
      Float_t sin2T = n * n * (Float_t(1.0) - cosI * cosI);

      if (sin2T > 1.0)
        return 1.0;

      using std::sqrt;
      Float_t cosT = sqrt(1.0 - sin2T);
      Float_t rPer = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
      Float_t rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);

      return (rPer * rPer + rPar * rPar) * Float_t(0.5);
    }

    Color handleReflectionAndRefraction(const Scene&            scene,
                                        const Ray&              ray,
                                        const IntersectionData& data,
                                        uint8                   depth)
    {
      Float_t reflectance   = data.obj->getMaterial()->getReflexion(data);
      Float_t transmittance = data.obj->getMaterial()->getTransparency(data);

      bool hasReflexion    = reflectance > Globals::Epsilon;
      bool hasTransparency = transmittance > Globals::Epsilon;

      if (!(hasReflexion || hasTransparency) || depth >= MAX_DEPTH)
        return 0;

      Color reflexion;
      Color transparency;

      if (hasReflexion && hasTransparency)
      {
        reflectance   = getFresnelReflectance(data, ray);
        transmittance = 1.0 - reflectance;
      }

      if (hasReflexion && reflectance > Globals::Epsilon)
        reflexion = handleReflection(scene, ray, data, depth) * reflectance;

      if (hasTransparency && transmittance > Globals::Epsilon)
        transparency = handleTransparency(scene, ray, data, depth) * transmittance;

      return reflexion + transparency;
    }

    Color getColor(const Scene& scene, const Ray& ray, const IntersectionData& data, uint8 depth)
    {
      Color materialColor = data.obj->getMaterial()->getColor(data);
      Color ambient       = materialColor * scene.getAmbient();
      Color lighting;
      Color specular;

      if (!data.obj->getMaterial()->testFlag(Flags::NoShading))
      {
        lighting = scene.processLights(data, specular);
      }

      Color   reflectionRefraction = handleReflectionAndRefraction(scene, ray, data, depth);
      Float_t coef                 = Tools::Max(data.obj->getMaterial()->getTransparency(data),
                                data.obj->getMaterial()->getReflexion(data));

      return specular + (ambient + lighting) * (1.0 - coef) + reflectionRefraction * coef;
    }
  }  // namespace

  Color Worker::inter(const Scene& scene, const Ray& ray, uint8 depth, Tools::Stat* stat)
  {
    IntersectionData data;

    stat->rayCounts[ray.getType()] += 1;

    data.stat = stat;
    data.obj  = scene.getNearest(ray, data);

    if (data.obj)
    {
      stat->hits += 1;
      data.point = ray.evaluate(data.k);
      data.obj->getShape()->fillData(data);
      data.ray = &ray;

      if (data.isInside)
        data.normal *= -1;

      return getColor(scene, ray, data, depth);
    }

    return scene.cubemap().interceptRay(ray);
  }

}  // namespace Rayon
