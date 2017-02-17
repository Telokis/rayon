#pragma once

#ifndef RAYON_INTERSECTIONDATA_HH_
#define RAYON_INTERSECTIONDATA_HH_

#include "Tools/Types.hh"

namespace RayOn
{
  class RTObject;
  class Material;

  struct IntersectionData
  {
    IntersectionData()
      : localPoint(0)
      , point(0)
      , normal(0)
      , k(0)
      , obj(nullptr)
      , material(nullptr)
      , isInside(false)
    {
    }

    Vec_t     localPoint;
    Vec_t     point;
    Vec_t     normal;
    Float_t   k;
    RTObject* obj;
    Material* material;
    bool      isInside;
  };
} // namespace RayOn

#endif // RAYON_INTERSECTIONDATA_HH_