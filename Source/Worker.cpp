#include "Worker.hh"

namespace RayOn
{
  namespace
  {
    static constexpr const uint8 MAX_DEPTH = 10;
    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth = 0);

    Color handleReflection(RTObject* obj, const Ray& ray, Color color,
                           const Vec_t& point, const Scene& scene, uint8 depth)
    {
      Color tmp_color;

      if (obj->getMaterial().getReflexion() > Globals::Epsilon && depth < MAX_DEPTH)
      {
        Ray reflected(RayType::Reflected, point,
                      Tools::Reflect(ray.getDirection(), obj->norm(point)));
        tmp_color = inter(scene, reflected, depth + 1);
        color = Color::interpolate(color, tmp_color, obj->getMaterial().getReflexion());
      }
      return color;
    }

    Color handleRefraction(RTObject* obj, const Ray& ray, Color color,
                           const Vec_t& point, const Scene& scene, uint8 depth)
    {
      Color tmp_color;

      if (obj->getMaterial().getTransparency() > Globals::Epsilon && depth < MAX_DEPTH)
      {
        Ray refracted(RayType::Transparency, point,
                      Tools::Refract(ray.getDirection(), obj->norm(point),
                                     obj->getMaterial().getRefraction()));
        tmp_color = inter(scene, refracted, depth + 1);
        color = Color::interpolate(color, tmp_color, obj->getMaterial().getTransparency());
      }
      return color;
    }

    Color inter(const Scene& scene,
                const Ray& ray,
                uint8 depth)
    {
      RTObject*   obj;
      Vec_t       point;
      Float_t     k;
      Color       color(0);

      obj = scene.getNearest(k, ray);
      if (obj)
      {
        point = ray.evaluate(k + Globals::Epsilon);
        color = obj->getMaterial().getColor();
        if (!obj->getMaterial().testFlag(Flags::NoShading))
          color = scene.processLights(obj->getMaterial().getColor(), obj, point);
        color = handleReflection(obj, ray, color, point, scene, depth);
        color = handleRefraction(obj, ray, color, point, scene, depth);
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
