#pragma once

#ifndef RAYON_WORKER_HH_
#define RAYON_WORKER_HH_

#include <memory>
#include <boost/signals2.hpp>

#include "RawImage.hh"
#include "Scene.hh"
#include "Tools/Stat.hh"

namespace sigs = boost::signals2;

namespace Rayon
{
  class Worker
  {
  public:
    static Color inter(const Scene& scene, const Ray& ray, uint8 depth, Tools::Stat* stat);

  public:
    Worker(RawImage* img, uint32 xStart, uint32 xStop, Tools::Stat* stat);
    void operator()(uint32 width, uint32 height, const Scene* scene_);

    void stop();

  public:
    std::shared_ptr<sigs::signal<void()>> sigFinished;

  private:
    RawImage*                         _img;
    uint32                            _xStart;
    uint32                            _xStop;
    Tools::Stat*                      _stat;
    std::shared_ptr<std::atomic_bool> _shouldStop;
  };
}  // namespace Rayon

#endif  // RAYON_WORKER_HH_