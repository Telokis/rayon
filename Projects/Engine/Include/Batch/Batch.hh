#pragma once

#ifndef RAYON_BATCH_BATCH_HH_
#define RAYON_BATCH_BATCH_HH_

#include <functional>
#include "Color.hh"
#include "Tools/Types.hh"
#include "Tools/CodeMacros.hh"

namespace Rayon
{
  class Scene;
  class RawImage;
}  // namespace Rayon

namespace Rayon
{
  class Batch
  {
  public:
    using WorkFunction_t = std::function<Color(double x, double y)>;

  public:
    Batch(const Scene* scene, Int32Vec2_t start, Int32Vec2_t end, RawImage* img, int rpp);

  public:
    void forEachWork(WorkFunction_t f);

  private:
    Int32Vec2_t _start;
    Int32Vec2_t _end;
    RawImage*   _img;
    int         _rpp;

    RAYON_GENERATE_PROPERTY_DECLARATION(Batch, const Scene*, _scene, Scene);
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_BATCH_HH_