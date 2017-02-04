#pragma once

#ifndef RAYON_TOOLS_BOUNDINGBOX_HH_
#define RAYON_TOOLS_BOUNDINGBOX_HH_

#include "Tools/CachedValue.hh"
#include "Tools/Helpers.hh"

namespace RayOn
{
  class BoundingBox
  {
  public:
    BoundingBox();
    BoundingBox(const Vec_t& min, const Vec_t& max);

  public:
    const Vec_t  getSize() const;
    bool              isInside(const Vec_t& point) const;

  private:
    Vec_t                      _min;
    Vec_t                      _max;
    mutable CachedValue<Vec_t> _size;
  };

} // namespace RayOn

#endif // RAYON_TOOLS_BOUNDINGBOX_HH_