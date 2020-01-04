#include "Rayon.hh"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <numeric>
#include <sstream>
#include <thread>
#include <vector>

#include "ImageFileHandlers/ImageFileHandler.hh"
#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "ImageFileHandlers/ImageFileHandler_TGA.hh"
#include "MetaRTLights/MetaSun.hh"
#include "MetaRTShapes/MetaBox.hh"
#include "MetaRTShapes/MetaMobius.hh"
#include "MetaRTShapes/MetaPlane.hh"
#include "MetaRTShapes/MetaRectangle.hh"
#include "MetaRTShapes/MetaSphere.hh"
#include "MetaRTShapes/MetaTriangle.hh"
#include "RawImage.hh"
#include "Registry.hh"
#include "SceneParse.hh"
#include "Version.hh"
#include "Worker.hh"

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
                << formatNumber(stat->hits / static_cast<double>(stat->intersectionsChecked))
                << " hits per check)"
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
              << formatNumber(total.hits / static_cast<double>(total.intersectionsChecked))
              << " hits per check)"
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

  Rayon::Rayon(const Config& config) : _config(config)
  {
  }

  void Rayon::registerDefaults()
  {
    registry().registerImageFileHandler(new ImageFileHandler_BMP);
    registry().registerImageFileHandler(new ImageFileHandler_PNG);
    registry().registerImageFileHandler(new ImageFileHandler_TGA);

    registry().registerMetaRTLight(new MetaSun);

    registry().registerMetaRTShape(new MetaSphere);
    registry().registerMetaRTShape(new MetaPlane);
    registry().registerMetaRTShape(new MetaRectangle);
    registry().registerMetaRTShape(new MetaBox);
    registry().registerMetaRTShape(new MetaMobius);
    registry().registerMetaRTShape(new MetaTriangle);
  }

  void Rayon::loadSceneFromFile(const std::string& filename)
  {
    sceneRead(_scene, _config.getInputPath());
  }

  int Rayon::run()
  {
    auto     width  = _config.getWidth();
    auto     height = _config.getHeight();
    RawImage img(width, height);

    auto start = std::chrono::steady_clock::now();
    _scene.preprocess();
    auto end = std::chrono::steady_clock::now();
    std::cout << "Preprocessing took " << Duration_t(end - start).count() << "s" << std::endl;

    uint8 jn = _config.getThreadCount();

    start = std::chrono::steady_clock::now();
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

    end             = std::chrono::steady_clock::now();
    Duration_t diff = end - start;

    printStats(stats, diff, width * height);

    ImageFileHandler::writeToFileBasedOnExtension(_config.getOutputPath(), img);
    return 0;
  }

}  // namespace Rayon
