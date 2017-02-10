#include "RayOn.hh"
#include "Version.hh"
#include "RawImage.hh"
#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "Entities/Objects/Sphere.hh"
#include "Entities/Objects/Plane.hh"
#include "Entities/Objects/Rectangle.hh"
#include "Entities/Lights/Sun.hh"
#include "Entities/Eye.hh"

#include <iostream>

namespace RayOn
{

  RayOn::RayOn(int ac, char** av)
  {
    config().init(ac, av);

    Eye* eye = new Eye(Vec_t(0, 1, -5), Vec_t(0, 0, 0));
    _scene << eye;
    Sphere* sphere = new Sphere(Vec_t(0, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setFlag(Flags::NoShading);
    _scene << sphere;
    sphere = new Sphere(Vec_t(-2.5, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    _scene << sphere;
    sphere = new Sphere(Vec_t(2.5, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setFlag(Flags::NoShadow);
    _scene << sphere;
    Rectangle* rectangle = new Rectangle(Vec_t(0, -0.8, 0), Vec_t(0, 0, 0), 8, 5);
    rectangle->getMaterial().setColor(0x67E6EC);
    _scene << rectangle;
    Sun* sun = new Sun(10, 10, -20);
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
      color = obj->getMaterial().getColor();
      if (!obj->getMaterial().testFlag(Flags::NoShading))
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

  /*
  Given longitude and latitude on a sphere of radius S,
  the 3D coordinates P = (P.x, P.y, P.z) are:
  P.x = S * sin(ax) * cos(ay)
  P.y = S * sin(ax) * sin(ay)
  P.z = S * cos(ax)
  ax [0, pi]
  ay [0, 2pi]

  vect->x = sin(angle_h) * cos_v;
  vect->y = sin(angle_v) * cos_h;
  vect->z = cos_h * cos_v;
  */

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
      Float_t i = x * 2.0 / width - 1.0;
      for (uint32 y = 0; y < height; ++y)
      {
        Float_t j = 0.0 - (y * 2.0 / height - 1.0);
        cameraRay.setDirection(_scene.eye()->indirectRotation(Vec_t(i, j, 1)));
        cameraRay.normalize();
        auto color = inter(_scene, cameraRay);
        img.pixel(x, y) = color;
      }
    }
    IImageFileHandler* bmp = new ImageFileHandler_BMP;
    std::cout << "Success : " << bmp->writeToFile(config().getOutputPath().c_str(), img) << '\n';
    return 0;
  }

} // namespace RayOn
