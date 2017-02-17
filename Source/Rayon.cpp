#include "Rayon.hh"
#include "Version.hh"
#include "Worker.hh"
#include "RawImage.hh"
#include "SceneParse.hh"
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

namespace Rayon
{

  Rayon::Rayon(int ac, char** av)
  {
    config().init(ac, av);

    if (!config().getInputPath().empty())
      sceneRead(_scene, config().getInputPath());
  }

  int Rayon::run()
  {
    if (config().handleStoppingArgs())
      return 0;

    auto width = config().getWidth();
    auto height = config().getHeight();
    RawImage  img(width, height);

    uint8 jn = config().getThreadCount();
    jn=1;
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

} // namespace Rayon
