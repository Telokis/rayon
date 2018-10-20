#pragma once

#ifndef RAYON_TOOLS_BOUNDINGBOX_HH_
#define RAYON_TOOLS_BOUNDINGBOX_HH_

#include "CachedValue.hh"
#include "Ray.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  class BoundingBox
  {
  public:
    BoundingBox();
    BoundingBox(const Vec_t& min, const Vec_t& max);

  public:
    static const BoundingBox Infinite;

  public:
    const Vec_t getSize() const;
    bool        isInside(const Vec_t& point) const;
    Float_t     intersectRay(const Ray& ray) const;
    bool        intersectBox(const BoundingBox& bbox);
    void        expand(const BoundingBox& bbox);

    bool isInfinite() const;

  private:
    Vec_t                      _min;
    Vec_t                      _max;
    mutable CachedValue<Vec_t> _size;
  };

}  // namespace Rayon

#endif  // RAYON_TOOLS_BOUNDINGBOX_HH_