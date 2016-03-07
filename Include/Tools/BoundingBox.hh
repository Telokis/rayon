#pragma once

#ifndef RAYON_TOOLS_BOUNDINGBOX_HH_
#define RAYON_TOOLS_BOUNDINGBOX_HH_

#include "Tools/CachedValue.hh"
#include "Tools/Helpers.hh"

namespace RayOn
{
  namespace Tools
  {

    class BoundingBox
    {
    public:
      BoundingBox();
      BoundingBox(const VectorType& min, const VectorType& max);

    public:
      const VectorType  getSize() const;
      bool              isInside(const VectorType& point) const;

    private:
      VectorType                      _min;
      VectorType                      _max;
      mutable CachedValue<VectorType> _size;
    };

  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_BOUNDINGBOX_HH_