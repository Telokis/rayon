#pragma once

#ifndef RAYON_INTERSECTIONDATA_HH_
#define RAYON_INTERSECTIONDATA_HH_

#include "Tools/Types.hh"

namespace Rayon
{
  class RTObject;
  class Material;
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
      , material(nullptr)
      , isInside(false)
    {
    }

    Vec_t       localPoint;
    Vec_t       point;
    Vec_t       normal;
    const Ray*  ray;
    Float_t     k;
    RTObject*   obj;
    Material*   material;
    bool        isInside;
  };
} // namespace Rayon

#endif // RAYON_INTERSECTIONDATA_HH_