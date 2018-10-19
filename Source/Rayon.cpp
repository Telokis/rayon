#include "Rayon.hh"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>

#include "ImageFileHandlers/ImageFileHandler.hh"
#include "RawImage.hh"
#include "SceneParse.hh"
#include "Version.hh"
#include "Worker.hh"

template <class T>
std::string formatNumber(T value)
{
  std::stringstream ss;
  ss.imbue(std::locale(""));
  ss << std::fixed << value;
  return ss.str();
}

namespace Rayon
{
  using UniqueStat = std::unique_ptr<Tools::Stat>;
  using Duration_t = std::chrono::duration<double>;

  void printStats(const std::vector<UniqueStat>& stats, Duration_t overallDuration, uint32 pixels)
  {
    Tools::Stat total;

    std::cout << "Thread breakdown:\n";
    for (uint32 i = 0; i < stats.size(); ++i)
    {
      auto&& stat = stats.at(i);

      total.intersectionsChecked += stat->intersectionsChecked;
      total.hits += stat->hits;
      total.rayCounts.at(RayType::Primary) += stat->rayCounts.at(RayType::Primary);
      total.rayCounts.at(RayType::Shadow) += stat->rayCounts.at(RayType::Shadow);
      total.rayCounts.at(RayType::Reflected) += stat->rayCounts.at(RayType::Reflected);
      total.rayCounts.at(RayType::Transparency) += stat->rayCounts.at(RayType::Transparency);

      std::cout << " Thread #" << (i + 1) << ":\n";
      std::cout << "  Intersections checked: " << formatNumber(stat->intersectionsChecked) << "\n";
      std::cout << "  Hits: " << formatNumber(stat->hits) << " ("
                << (stat->intersectionsChecked / static_cast<double>(stat->hits))
                << " checks per hit)"
                << "\n";
      std::cout << "  Primary rays: " << formatNumber(stat->rayCounts.at(RayType::Primary)) << "\n";
      std::cout << "  Shadow rays: " << formatNumber(stat->rayCounts.at(RayType::Shadow)) << "\n";
      std::cout << "  Reflected rays: " << formatNumber(stat->rayCounts.at(RayType::Reflected))
                << "\n";
      std::cout << "  Transparency rays: "
                << formatNumber(stat->rayCounts.at(RayType::Transparency)) << "\n";
      std::cout << "  Thread worked for: " << stat->elapsed.count() << " seconds\n\n";
    }

    std::cout << "Total:\n";
    std::cout << "  Intersections checked: " << formatNumber(total.intersectionsChecked) << "\n";
    std::cout << "  Hits: " << formatNumber(total.hits) << " ("
              << (total.intersectionsChecked / static_cast<double>(total.hits))
              << " checks per hit)"
              << "\n";
    std::cout << "  Primary rays: " << formatNumber(total.rayCounts.at(RayType::Primary)) << "\n";
    std::cout << "  Shadow rays: " << formatNumber(total.rayCounts.at(RayType::Shadow)) << "\n";
    std::cout << "  Reflected rays: " << formatNumber(total.rayCounts.at(RayType::Reflected))
              << "\n";
    std::cout << "  Transparency rays: " << formatNumber(total.rayCounts.at(RayType::Transparency))
              << "\n\n";

    std::cout << "Rendered " << formatNumber(pixels) << " pixels in " << overallDuration.count()
              << "s.\n";
  }

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

    _scene.preprocess();
    uint8 jn = config().getThreadCount();

    auto                     start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    std::vector<UniqueStat>  stats;
    threads.reserve(jn);
    stats.reserve(jn);

    for (uint8 i = 0; i < jn; ++i)
    {
      uint32 xStart = i * width / jn;
      uint32 xStop  = (i + 1) * width / jn;

      auto stat = std::make_unique<Tools::Stat>();

      threads.emplace_back(Worker(&img, xStart, xStop, stat.get()), width, height, &_scene);
      stats.emplace_back(std::move(stat));
    }

    for (auto&& thread : threads)
      thread.join();

    auto       end  = std::chrono::steady_clock::now();
    Duration_t diff = end - start;

    printStats(stats, diff, width * height);

    ImageFileHandler::writeToFileBasedOnExtension(config().getOutputPath(), img);
    return 0;
  }

}  // namespace Rayon
