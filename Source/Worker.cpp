#include "Worker.hh"
#include "IntersectionData.hh"

namespace RayOn
{
  namespace
  {
    static constexpr const uint8 MAX_DEPTH = 5;
    static constexpr const uint8 MAX_GLOSSY = 5;
    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth = 0);

    Color handleReflection(const Scene& scene,
                           const Ray& ray,
                           const IntersectionData& data,
                           uint8 depth)
    {
      Ray reflected(RayType::Reflected, data.point,
                    Tools::Reflect(ray.getDirection(), data.normal));
      if (data.material->getGlossiness() > Globals::Epsilon)
      {
        Color color;
        Float_t g = data.material->getGlossiness();
        Vec_t reflectedDir = reflected.getDirection();
        for (auto i = 0u; i < MAX_GLOSSY; ++i)
        {
          Vec_t tmp(((rand() % 100) - 50.0) / (100.0 * g),
                    1.0 * ((rand() % 100) - 50.0) / (100.0 * g),
                    ((rand() % 100) - 50.0) / (100.0 * g));
          reflected.setDirection(reflectedDir + tmp);
          reflected.normalize();
          reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
          color += inter(scene, reflected, depth + 1);
        }
        return color * (Float_t(1.0) / MAX_GLOSSY);
      }
      reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
      return inter(scene, reflected, depth + 1);
    }

    Color handleTransparency(const Scene& scene,
                             const Ray& ray,
                             const IntersectionData& data,
                             uint8 depth)
    {
      Ray refracted(RayType::Transparency, data.point, ray.getDirection());
      Float_t eta = data.material->getRefraction();

      if (eta != 1 && eta > Globals::Epsilon)
        refracted.setDirection(Tools::Refract(ray.getDirection(), data, eta));
      refracted.setOrigin(data.point + Globals::Epsilon * refracted.getDirection());
      return inter(scene, refracted, depth + 1);
    }

    // http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
    Float_t getFresnelReflectance(const IntersectionData& data, const Ray& ray)
    {
      Float_t n1 = data.material->getRefraction();
      Float_t n2 = 1.0;

      Float_t cosI = -Tools::DotProduct(ray.getDirection(), data.normal);
      if (cosI > Globals::Epsilon)
      {
        n2 = n1;
        n1 = 1.0;
      }
      else
        cosI *= -1;

      Float_t n = n1 / n2;
      Float_t sin2T = n * n * (Float_t(1.0) - cosI * cosI);

      if (sin2T > 1.0)
        return 1.0;

      using std::sqrt;
      Float_t cosT = sqrt(1.0 - sin2T);
      Float_t rPer = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
      Float_t rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
      return (rPer * rPer + rPar * rPar) * Float_t(0.5);
    }

    Color handleReflectionAndRefraction(const Scene& scene,
                                        const Ray& ray,
                                        const IntersectionData& data,
                                        uint8 depth)
    {
      bool hasReflexion = data.material->getReflexion() > Globals::Epsilon;
      bool hasTransparency = data.material->getTransparency() > Globals::Epsilon;

      if (!(hasReflexion || hasTransparency) || depth >= MAX_DEPTH)
        return 0;

      Float_t reflectance = data.material->getReflexion();
      Float_t transmittance = data.material->getTransparency();

      Color reflexion;
      Color transparency;

      if (hasReflexion && hasTransparency)
      {
        reflectance = getFresnelReflectance(data, ray);
        transmittance = 1.0 - reflectance;
      }

      if (hasReflexion && reflectance > Globals::Epsilon)
        reflexion = handleReflection(scene, ray, data, depth) * reflectance;

      if (hasTransparency && transmittance > Globals::Epsilon)
        transparency = handleTransparency(scene, ray, data, depth) * transmittance;

      return reflexion + transparency;
    }

    Color   getColor(const Scene& scene,
                     const Ray& ray,
                     const IntersectionData& data,
                     uint8 depth)
    {
      Color color = data.material->getColor();
      Color ambient = color * scene.getAmbient();
      Color lighting;

      if (data.material->getAmbient() > -Globals::Epsilon)
        ambient = color * data.material->getAmbient();
      if (!data.material->testFlag(Flags::NoShading))
        lighting = scene.processLights(data);
      Color reflectionRefraction = handleReflectionAndRefraction(scene, ray, data, depth);

      Float_t coef = Tools::Max(data.material->getTransparency(), data.material->getReflexion());
      return (ambient + lighting) * (1.0 - coef) + reflectionRefraction * coef;
    }

    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth)
    {
      IntersectionData  data;

      data.obj = scene.getNearest(ray, data);
      if (data.obj)
      {
        data.material = &data.obj->getMaterial();
        data.point = ray.evaluate(data.k);
        data.obj->fillData(data);
        if (data.isInside)
          data.normal *= -1;
        return getColor(scene, ray, data, depth);
      }
      return scene.cubemap().interceptRay(ray);
    }
  } // anonymous namespace

  Worker::Worker(RawImage* img, uint32 yStart, uint32 yStop)
    : _img(img)
    , _yStart(yStart)
    , _yStop(yStop)
  {
  }

  void Worker::operator()(uint32 width, uint32 height, Scene* scene_) const
  {
    Scene scene = *scene_;
    scene.preprocess();
    Ray   cameraRay(RayType::Primary, scene.eye().getPos(), Vec_t());

    for (uint32 x = 0; x < width; ++x)
    {
      Float_t i = x * 2.0 / width - 1.0;
      for (uint32 y = _yStart; y < _yStop; ++y)
      {
        Float_t j = 0.0 - (y * 2.0 / height - 1.0);
        cameraRay.setDirection(scene.eye().indirectRotation(Vec_t(i, j, 1)));
        cameraRay.normalize();
        auto color = inter(scene, cameraRay);
        _img->pixel(x, y) = color;
      }
    }
  }

} // namespace RayOn
