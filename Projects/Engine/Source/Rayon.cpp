#include "Rayon.hh"

#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <numeric>
#include <sstream>
#include <thread>
#include <vector>

#include "RawImage.hh"
#include "Registry.hh"
#include "SceneParse.hh"
#include "Version.hh"
#include "Worker.hh"

using TimePoint_t = std::chrono::steady_clock::time_point;

struct dotted : std::numpunct<char>
{
  char do_thousands_sep() const
  {
    return ' ';
  }

  std::string do_grouping() const
  {
    return "\3";
  }

  static void imbue(std::ostream& os)
  {
    os.imbue(std::locale(os.getloc(), new dotted));
  }
};

template <class T>
std::string formatNumber(T value)
{
  std::stringstream ss;
  dotted::imbue(ss);
  ss << std::setprecision(3) << std::fixed << value;
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

      total.treeBranchesExplored += stat->treeBranchesExplored;
      total.intersectionsChecked += stat->intersectionsChecked;
      total.hits += stat->hits;
      total.rayCounts.at(RayType::Primary) += stat->rayCounts.at(RayType::Primary);
      total.rayCounts.at(RayType::Shadow) += stat->rayCounts.at(RayType::Shadow);
      total.rayCounts.at(RayType::Reflected) += stat->rayCounts.at(RayType::Reflected);
      total.rayCounts.at(RayType::Transparency) += stat->rayCounts.at(RayType::Transparency);

      std::cout << " Thread #" << (i + 1) << ":\n";
      std::cout << "  Tree branches explored: " << formatNumber(stat->treeBranchesExplored) << "\n";
      std::cout << "  Intersections checked: " << formatNumber(stat->intersectionsChecked) << "\n";
      std::cout << "  Hits: " << formatNumber(stat->hits) << " ("
                << formatNumber(stat->hits / static_cast<double>(stat->intersectionsChecked) * 100)
                << "%)"
                << "\n";
      std::cout << "  Primary rays: " << formatNumber(stat->rayCounts.at(RayType::Primary)) << "\n";
      std::cout << "  Shadow rays: " << formatNumber(stat->rayCounts.at(RayType::Shadow)) << "\n";
      std::cout << "  Reflected rays: " << formatNumber(stat->rayCounts.at(RayType::Reflected))
                << "\n";
      std::cout << "  Transparency rays: "
                << formatNumber(stat->rayCounts.at(RayType::Transparency)) << "\n";
      std::cout << "  Thread worked for: " << formatNumber(stat->elapsed.count()) << " seconds\n\n";
    }

    std::cout << "Total:\n";
    std::cout << "  Tree branches explored: " << formatNumber(total.treeBranchesExplored) << "\n";
    std::cout << "  Intersections checked: " << formatNumber(total.intersectionsChecked) << "\n";
    std::cout << "  Hits: " << formatNumber(total.hits) << " ("
              << formatNumber(total.hits / static_cast<double>(total.intersectionsChecked) * 100)
              << "%)"
              << "\n";
    std::cout << "  Primary rays: " << formatNumber(total.rayCounts.at(RayType::Primary)) << "\n";
    std::cout << "  Shadow rays: " << formatNumber(total.rayCounts.at(RayType::Shadow)) << "\n";
    std::cout << "  Reflected rays: " << formatNumber(total.rayCounts.at(RayType::Reflected))
              << "\n";
    std::cout << "  Transparency rays: " << formatNumber(total.rayCounts.at(RayType::Transparency))
              << "\n\n";

    std::cout << "Rendered " << formatNumber(pixels) << " pixels in "
              << formatNumber(overallDuration.count()) << "s.\n";
  }

  Rayon::Rayon()
  {
  }

  Rayon::Rayon(const Config& config) : _config(config)
  {
  }

  void Rayon::loadSceneFromFile(const std::string& filename)
  {
    readSceneFromFile(_scene, filename);
  }

  int Rayon::run(RawImage& img, bool preprocess)
  {
    return run(img, _scene, preprocess);
  }

  void runMultipleThreads(std::vector<UniqueStat>& stats,
                          uint8                    jn,
                          RawImage&                img,
                          Scene&                   scene,
                          uint32                   width,
                          uint32                   height)
  {
    std::vector<std::thread> threads;
    threads.reserve(jn);
    stats.reserve(jn);

    for (uint8 i = 0; i < jn; ++i)
    {
      uint32 xStart = i * width / jn;
      uint32 xStop  = (i + 1) * width / jn;

      auto stat = std::make_unique<Tools::Stat>();

      threads.emplace_back(Worker(&img, xStart, xStop, stat.get()), width, height, &scene);
      stats.emplace_back(std::move(stat));
    }

    for (auto&& thread : threads)
      thread.join();
  }

  int Rayon::run(RawImage& img, Scene& scene, bool preprocess)
  {
    auto        width  = _config.getWidth();
    auto        height = _config.getHeight();
    TimePoint_t start;
    TimePoint_t end;

    img.resize(width, height);

    if (preprocess)
    {
      start = std::chrono::steady_clock::now();
      scene.preprocess();
      end = std::chrono::steady_clock::now();

      if (!_config.getSilent())
      {
        std::cout << "Preprocessing took " << Duration_t(end - start).count() << "s" << std::endl;
      }
    }

    uint8 jn = _config.getThreadCount();

    start = std::chrono::steady_clock::now();
    std::vector<UniqueStat> stats;

    if (jn > 1 || _config.getForceUseThread())
    {
      runMultipleThreads(stats, jn, img, scene, width, height);
    }
    else
    {
      auto stat   = std::make_unique<Tools::Stat>();
      auto worker = Worker(&img, 0, width, stat.get());

      worker(width, height, &scene);

      stats.emplace_back(std::move(stat));
    }

    end             = std::chrono::steady_clock::now();
    Duration_t diff = end - start;

    if (!_config.getSilent())
    {
      printStats(stats, diff, width * height);
    }

    return 0;
  }

}  // namespace Rayon
