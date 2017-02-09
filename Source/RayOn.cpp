#include "RayOn.hh"
#include "Version.hh"
#include "RawImage.hh"
#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "Entities/Objects/Sphere.hh"
#include "Entities/Objects/Plane.hh"
#include "Entities/Lights/Sun.hh"
#include "Entities/Eye.hh"

#include <iostream>

namespace RayOn
{

  RayOn::RayOn(int ac, char** av)
  {
    config().init(ac, av);

    Eye* eye = new Eye(Vec_t(0, 0, -20), Vec_t(0, 0, 0));
    _scene << eye;
    Sphere* sphere = new Sphere(Vec_t(0, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0xff0000);
    _scene << sphere;
    Plane* plane = new Plane(Vec_t(0, -1.2, 0), Vec_t(15, 0, 0));
    plane->getMaterial().setColor(0xff00);
    _scene << plane;
    Sun* sun = new Sun(10, 10, -10);
    sun->setColor(Color(255, 255, 255));
    _scene << sun;
  }

  Color inter(Scene& scene,
              const Ray& ray,
              int depth = 0)
  {
    RTObject    *obj;
    Vec_t       point;
    Float_t     k;
    Color       color(0);
    Color       tmp_color;

    obj = scene.getNearest(k, ray);
    if (obj)
    {
      point = ray.evaluate(k);
      color = scene.processLights(obj->getMaterial().getColor(), scene, obj, point);
      if (obj->getMaterial().getReflexion() > Globals::Epsilon && depth < 5)
      {
        Ray reflected(RayType::Reflected, point,
                      Tools::Reflect(ray.getDirection(), obj->norm(point)));
        tmp_color = inter(scene, reflected, depth + 1);
        color = Color::interpolate(color, tmp_color, obj->getMaterial().getReflexion());
      }
      if (obj->getMaterial().getTransparency() > Globals::Epsilon && depth < 5)
      {
        Ray refracted(RayType::Transparency, point,
                      Tools::Refract(ray.getDirection(), obj->norm(point),
                                     obj->getMaterial().getReflexion()));
        tmp_color = inter(scene, refracted, depth + 1);
        color = Color::interpolate(color, tmp_color, obj->getMaterial().getTransparency());
      }
    }
    return color;
  }

  int RayOn::run()
  {
    if (config().handleStoppingArgs())
      return 0;

    _scene.preprocess();

    auto width = config().getWidth();
    auto height = config().getHeight();
    RawImage  img(width, height);
    Ray       cameraRay(RayType::Primary, _scene.eye()->getPos(), Vec_t());

    std::cout << std::hex;
    for (uint32 x = 0; x < width; ++x)
    {
      for (uint32 y = 0; y < height; ++y)
      {
        cameraRay.setDirection(_scene.eye()->indirectRotation(Vec_t(width / 2.0 - x,
                                                                    height / 2.0 - y,
                                                                    1000.0)));
        cameraRay.normalize();
        auto color = inter(_scene, cameraRay);
        img.pixel(x, y) = color;
      }
    }
    IImageFileHandler* bmp = new ImageFileHandler_BMP;
    std::cout << "Success : " << bmp->writeToFile("rendu.bmp", img) << '\n';
    return 0;
  }

} // namespace RayOn
