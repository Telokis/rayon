#pragma once

#ifndef RAYON_INTERSECTIONDATA_HH_
#define RAYON_INTERSECTIONDATA_HH_

#include "Tools/Types.hh"

namespace Rayon
{
  class Object;
  class Ray;

  struct IntersectionData
  {
    IntersectionData()
      : localPoint(0)
      , point(0)
      , normal(0)
      , ray(nullptr)
      , k(0)
      , obj(nullptr)
      , isInside(false)
    {
    }

    Vec_t       localPoint;
    Vec_t       point;
    Vec_t       normal;
    const Ray*  ray;
    Float_t     k;
    Object*     obj;
    bool        isInside;
  };
} // namespace Rayon

#endif // RAYON_INTERSECTIONDATA_HH_