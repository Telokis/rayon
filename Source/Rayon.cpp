#include "Rayon.hh"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "ImageFileHandlers/ImageFileHandler.hh"
#include "RawImage.hh"
#include "SceneParse.hh"
#include "Version.hh"
#include "Worker.hh"

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

    auto     width  = config().getWidth();
    auto     height = config().getHeight();
    RawImage img(width, height);

    uint8 jn = config().getThreadCount();

    auto                     start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (uint8 i = 0; i < jn; ++i)
    {
      uint32 yStart = i * height / jn;
      uint32 yStop  = (i + 1) * height / jn;
      threads.push_back(std::thread(Worker(&img, yStart, yStop), width, height, &_scene));
    }

    for (std::thread& thread : threads)
      thread.join();

    auto                          end  = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Took " << diff.count() << "s.\n";

    ImageFileHandler::writeToFileBasedOnExtension(config().getOutputPath(), img);
    return 0;
  }

}  // namespace Rayon
