#include "Rayon.hh"

#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include <chrono>
#include <mutex>
#include <iomanip>
#include <iostream>
#include <locale>
#include <numeric>
#include <sstream>
#include <vector>

#include "RawImage.hh"
#include "Registry.hh"
#include "SceneParse.hh"
#include "Version.hh"

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
  using StatStorage_t = Rayon::StatStorage_t;
  using Duration_t    = std::chrono::duration<double>;

  void printStats(const StatStorage_t& stats, Duration_t overallDuration, uint32 pixels)
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

  int Rayon::run(RawImage& img, IBatchGenerator* batchGenerator, bool preprocess)
  {
    return run(img, _scene, batchGenerator, preprocess);
  }

  void runMultipleThreads(
    Rayon::WorkersStorage_t& workerData,
    StatStorage_t&           stats,
    uint8                    jn,
    RawImage&                img,
    Scene&                   scene,
    IBatchGenerator*         batchGenerator,
    bool                     joinThreads,
    std::function<void()>    callback = []() {})
  {
    auto count  = std::make_shared<std::atomic_int>(0);
    auto width  = img.width();
    auto height = img.height();

    workerData.reserve(jn);
    stats.reserve(jn);

    for (uint8 i = 0; i < jn; ++i)
    {
      uint32 xStart = i * width / jn;
      uint32 xStop  = (i + 1) * width / jn;

      auto stat = std::make_unique<Tools::Stat>();

      Worker w(batchGenerator, stat.get());

      if (!joinThreads)
      {
        w.sigFinished->connect([&workerData, count, callback, jn] {
          (*count)++;

          if (*count >= jn)
          {
            callback();
          }
        });
      }

      std::thread thread(w, width, height, &scene);

      workerData.emplace_back(std::move(thread), w);
      stats.emplace_back(std::move(stat));
    }

    if (joinThreads)
    {
      for (auto&& [thread, worker] : workerData)
        thread.join();
    }
  }

  void Rayon::runAsync(RawImage&        img,
                       Scene&           scene,
                       IBatchGenerator* batchGenerator,
                       bool             preprocess)
  {
    auto width  = _config.getWidth();
    auto height = _config.getHeight();

    _stats.clear();
    _workerData.clear();
    img.resize(width, height);

    if (preprocess)
    {
      scene.preprocess();
      sigPreprocessFinished();
    }

    uint8 jn = _config.getThreadCount();

    runMultipleThreads(
      _workerData, _stats, jn, img, scene, batchGenerator, false, [this] { sigFinished(); });
  }

  void Rayon::sendStopSignal()
  {
    for (auto&& [thread, worker] : _workerData)
      worker.stop();
  }

  void Rayon::joinThreads()
  {
    for (auto&& [thread, worker] : _workerData)
      thread.join();
  }

  void Rayon::stopAndJoinThreads()
  {
    sendStopSignal();
    joinThreads();
  }

  int Rayon::run(RawImage& img, Scene& scene, IBatchGenerator* batchGenerator, bool preprocess)
  {
    auto        width  = _config.getWidth();
    auto        height = _config.getHeight();
    TimePoint_t start;
    TimePoint_t end;

    _workerData.clear();
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
    StatStorage_t stats;

    if (jn > 1 || _config.getForceUseThread())
    {
      runMultipleThreads(_workerData, stats, jn, img, scene, batchGenerator, true);
    }
    else
    {
      auto stat   = std::make_unique<Tools::Stat>();
      auto worker = Worker(batchGenerator, stat.get());

      worker(width, height, &scene);

      stats.emplace_back(std::move(stat));
    }

    end             = std::chrono::steady_clock::now();
    Duration_t diff = end - start;

    if (!_config.getSilent())
    {
      printStats(stats, diff, width * height);
    }

    sigFinished();

    return 0;
  }

}  // namespace Rayon
