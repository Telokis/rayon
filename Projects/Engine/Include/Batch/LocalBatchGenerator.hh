#pragma once

#ifndef RAYON_BATCH_LOCALBATCHGENERATOR_HH_
#define RAYON_BATCH_LOCALBATCHGENERATOR_HH_

#include "Batch/IBatchGenerator.hh"

namespace Rayon
{
  class Scene;
  class RawImage;
}  // namespace Rayon

namespace Rayon
{
  class LocalBatchGenerator
  {
  public:
    LocalBatchGenerator(const Scene* scene,
                        Int32Vec2_t  start,
                        Int32Vec2_t  end,
                        RawImage*    img,
                        int          rpp);

  public:
    void forEachWork(std::function<Color(double x, double y)> f);

  private:
    int         _rpp;
    Int32Vec2_t _start;
    Int32Vec2_t _end;
    RawImage*   _img;

    RAYON_GENERATE_PROPERTY_DECLARATION(LocalBatchGenerator, const Scene*, _scene, Scene);
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_LOCALBATCHGENERATOR_HH_