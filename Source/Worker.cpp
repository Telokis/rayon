#include "Worker.hh"
#include "IntersectionData.hh"

namespace RayOn
{
  namespace
  {
    static constexpr const uint8 MAX_DEPTH = 5;
    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth = 0);

    Color handleReflection(IntersectionData& data, const Ray& ray, Color color,
                           const Scene& scene, uint8 depth)
    {
      Color tmp_color;

      if (data.material->getReflexion() > Globals::Epsilon && depth < MAX_DEPTH)
      {
        Ray reflected(RayType::Reflected, data.point,
                      Tools::Reflect(ray.getDirection(), data.normal));
        reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
        tmp_color = inter(scene, reflected, depth + 1);
        color = Color::interpolate(color, tmp_color, data.material->getReflexion());
      }
      return color;
    }

    Color handleRefraction(IntersectionData& data, const Ray& ray, Color color,
                           const Scene& scene, uint8 depth)
    {
      Color tmp_color;

      if (data.material->getTransparency() > Globals::Epsilon && depth < MAX_DEPTH)
      {
        Ray refracted(RayType::Transparency, data.point, ray.getDirection());
        Float_t eta = data.material->getRefraction();

        if (eta != 1 && eta > Globals::Epsilon)
          refracted.setDirection(Tools::Refract(ray.getDirection(), data.normal, eta));
        refracted.setOrigin(data.point + Globals::Epsilon * refracted.getDirection());
        tmp_color = inter(scene, refracted, depth + 1);
        color = Color::interpolate(color, tmp_color, data.material->getTransparency());
      }
      return color;
    }

    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth)
    {
      Color             color(0);
      IntersectionData  data;

      data.obj = scene.getNearest(ray, data);
      if (data.obj)
      {
        data.material = &data.obj->getMaterial();
        data.point = ray.evaluate(data.k);
        data.obj->fillData(data);
        color = data.material->getColor();
        if (!data.material->testFlag(Flags::NoShading))
          color = scene.processLights(data);
        color = handleReflection(data, ray, color, scene, depth);
        color = handleRefraction(data, ray, color, scene, depth);
      }
      else if (scene.cubemap())
      {
        return scene.cubemap()->interceptRay(ray);
      }
      return color;
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
    Ray   cameraRay(RayType::Primary, scene.eye()->getPos(), Vec_t());

    for (uint32 x = 0; x < width; ++x)
    {
      Float_t i = x * 2.0 / width - 1.0;
      for (uint32 y = _yStart; y < _yStop; ++y)
      {
        Float_t j = 0.0 - (y * 2.0 / height - 1.0);
        cameraRay.setDirection(scene.eye()->indirectRotation(Vec_t(i, j, 1)));
        cameraRay.normalize();
        auto color = inter(scene, cameraRay);
        _img->pixel(x, y) = color;
      }
    }
  }

} // namespace RayOn
