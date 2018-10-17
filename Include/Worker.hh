#pragma once

#ifndef RAYON_WORKER_HH_
#define RAYON_WORKER_HH_

#include <memory>

#include "RawImage.hh"
#include "Scene.hh"

namespace Rayon
{
  class Worker
  {
  public:
    Worker(RawImage* img, uint32 yStart, uint32 yStop);
    void operator()(uint32 width, uint32 height, Scene* scene_) const;

  public:  // SLOTS
    void pause();
    void start();

  private:
    RawImage* _img;
    uint32    _yStart;
    uint32    _yStop;
  };
}  // namespace Rayon

#endif  // RAYON_WORKER_HH_