#pragma once

#ifndef RAYON_RAYON_HH_
#define RAYON_RAYON_HH_

#include <memory>
#include <thread>
#include <boost/signals2.hpp>
#include "Config.hh"
#include "Worker.hh"
#include "Scene.hh"

namespace sigs = boost::signals2;

namespace Rayon
{
  namespace Tools
  {
    class Stat;
  };

  class Rayon
  {
  public:
    using WorkersStorage_t = std::vector<std::pair<std::thread, Worker>>;
    using UniqueStat       = std::unique_ptr<Tools::Stat>;
    using StatStorage_t    = std::vector<UniqueStat>;

  public:
    Rayon();
    Rayon(const Config& config);

  public:
    void runAsync(RawImage&        img,
                  Scene&           scene,
                  IBatchGenerator* batchGenerator,
                  bool             preprocess = false);
    void sendStopSignal();
    void joinThreads();
    void stopAndJoinThreads();
    int  run(RawImage& img, Scene& scene, IBatchGenerator* batchGenerator, bool preprocess = false);
    int  run(RawImage& img, IBatchGenerator* batchGenerator, bool preprocess = true);
    void loadSceneFromFile(const std::string& filename);
    void loadSceneFromString(const std::string& spec);

  public:
    sigs::signal<void()> sigPreprocessFinished;
    sigs::signal<void()> sigFinished;

  private:
    Scene            _scene;
    Config           _config;
    WorkersStorage_t _workerData;
    StatStorage_t    _stats;
  };
}  // namespace Rayon

#endif  // RAYON_RAYON_HH_
