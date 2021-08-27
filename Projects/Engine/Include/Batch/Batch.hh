#pragma once

#ifndef RAYON_BATCH_BATCH_HH_
#define RAYON_BATCH_BATCH_HH_

#include <functional>
#include "Color.hh"
#include "Tools/Types.hh"

namespace Rayon
{
  class RawImage;
  class IBatchGenerator;
}  // namespace Rayon

namespace Rayon
{
  class Batch
  {
  public:
    using WorkFunction_t = std::function<Color(double x, double y)>;

  public:
    Batch(IBatchGenerator* parent, UInt32Vec2_t start, UInt32Vec2_t end, RawImage* img, int rpp);

  public:
    void forEachWork(WorkFunction_t f);

  private:
    void fillColor(int x, int y, const Color& color);

  private:
    UInt32Vec2_t     _start;
    UInt32Vec2_t     _end;
    RawImage*        _img;
    int              _rpp;
    IBatchGenerator* _parent;
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_BATCH_HH_