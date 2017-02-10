#include "RayOn.hh"
#include "Version.hh"
#include "Worker.hh"
#include "RawImage.hh"
#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "Entities/Objects/Sphere.hh"
#include "Entities/Objects/Plane.hh"
#include "Entities/Objects/Rectangle.hh"
#include "Entities/Lights/Sun.hh"
#include "Entities/Eye.hh"

#include <iostream>
#include <thread>
#include <vector>

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
    sphere->getMaterial().setFlag(Flags::NoReflection);
    _scene << sphere;
    sphere = new Sphere(Vec_t(2.5, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setFlag(Flags::NoShadow);
    _scene << sphere;
    Plane* plane = new Plane(0, -0.8, 0);
    plane->getMaterial().setColor(0x67E6EC);
    plane->getMaterial().setReflexion(0.9);
    _scene << plane;
    Sun* sun = new Sun(10, 10, -20);
    sun->setColor(Color(255, 255, 255));
    _scene << sun;
    sun = new Sun(-10, 10, -20);
    sun->setColor(Color(255, 255, 255));
    _scene << sun;
    sun = new Sun(10, 50, -20);
    sun->setColor(Color(255, 255, 255));
    _scene << sun;
    sun = new Sun(-10, 30, -20);
    sun->setColor(Color(255, 255, 255));
    _scene << sun;
  }

  int RayOn::run()
  {
    if (config().handleStoppingArgs())
      return 0;

    _scene.preprocess();

    auto width = config().getWidth();
    auto height = config().getHeight();
    RawImage  img(width, height);

    uint8 jn = 4;

    std::vector<std::thread> threads;
    for (uint8 i = 0; i < jn; ++i)
    {
      uint32 yStart = i * height / jn;
      uint32 yStop = (i + 1) * height / jn;
      threads.push_back(std::thread(Worker(&img, yStart, yStop),
                                    width, height, &_scene));
    }

    for (std::thread& thread : threads)
      thread.join();

    IImageFileHandler* png = new ImageFileHandler_PNG;
    std::cout << "Success : " << png->writeToFile(config().getOutputPath().c_str(), img) << '\n';
    return 0;
  }

} // namespace RayOn
