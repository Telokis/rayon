#pragma once

#ifndef RAYON_INTERSECTIONDATA_HH_
#define RAYON_INTERSECTIONDATA_HH_

#include "Tools/Types.hh"

namespace Rayon
{
  class Object;
  class Ray;

  namespace Tools
  {
    struct Stat;
  }

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
      , stat(nullptr)
    {
    }

    Vec_t        localPoint;
    Vec_t        point;
    Vec_t        normal;
    const Ray*   ray;
    Float_t      k;
    Object*      obj;
    bool         isInside;
    Tools::Stat* stat;
  };
}  // namespace Rayon

#endif  // RAYON_INTERSECTIONDATA_HH_