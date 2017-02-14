#include "RayOn.hh"
#include "Version.hh"
#include "Worker.hh"
#include "RawImage.hh"
#include "ImageFileHandlers/ImageFileHandler.hh"
#include "Entities/Objects/Sphere.hh"
#include "Entities/Objects/Plane.hh"
#include "Entities/Objects/Rectangle.hh"
#include "Entities/Objects/Box.hh"
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

    CubeMap* cmap = new CubeMap;
    /*cmap->loadSide(Side::Left, "./files/textures/cubemap/alpleft.tga");
    cmap->loadSide(Side::Right, "./files/textures/cubemap/alpright.tga");
    cmap->loadSide(Side::Up, "./files/textures/cubemap/alpup.tga");
    cmap->loadSide(Side::Down, "./files/textures/cubemap/alpdown.tga");
    cmap->loadSide(Side::Front, "./files/textures/cubemap/alpforward.tga");
    cmap->loadSide(Side::Back, "./files/textures/cubemap/alpback.tga");*/
    cmap->loadSide(Side::Left, "./files/textures/cubemap/stormydays_lf.tga");
    cmap->loadSide(Side::Right, "./files/textures/cubemap/stormydays_rt.tga");
    cmap->loadSide(Side::Up, "./files/textures/cubemap/stormydays_up.tga");
    cmap->loadSide(Side::Down, "./files/textures/cubemap/stormydays_dn.tga");
    cmap->loadSide(Side::Front, "./files/textures/cubemap/stormydays_ft.tga");
    cmap->loadSide(Side::Back, "./files/textures/cubemap/stormydays_bk.tga");
    _scene.setCubeMap(cmap);

    Eye* eye = new Eye(Vec_t(0, 3, -4), Vec_t(20, 0, 0));
    _scene << eye;
    Box* box = new Box(Vec_t(0, 2.6847, 2.5), Vec_t(0, 45, 0), 1, 1, 1);
    box->getMaterial().setColor(0x8b8b);
    _scene << box;
    Sphere* sphere = new Sphere(Vec_t(2.5, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setTransparency(1);
    sphere->getMaterial().setRefraction(1.5);
    _scene << sphere;
    sphere = new Sphere(Vec_t(-2.5, 0, 0), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setFlag(Flags::NoShading);
    sphere->getMaterial().setAmbient(1);
    sphere->getMaterial().setReflexion(1);
    sphere->getMaterial().setGlossiness(2.5);
    _scene << sphere;
    sphere = new Sphere(Vec_t(0, 0, 5), Vec_t(0, 0, 0), 1);
    sphere->getMaterial().setColor(0x8B0A50);
    sphere->getMaterial().setFlag(Flags::NoShadow);
    _scene << sphere;
    Plane* plane = new Plane(0, -0.8, 0);
    plane->getMaterial().setColor(0x67E6EC);
    plane->getMaterial().setReflexion(0.8);
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

    auto width = config().getWidth();
    auto height = config().getHeight();
    RawImage  img(width, height);

    uint8 jn = config().getThreadCount();

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

    bool success = ImageFileHandler::writeToFileBasedOnExtension(config().getOutputPath(), img);
    std::cout << std::boolalpha << "Success : " << success << '\n';
    return 0;
  }

} // namespace RayOn
