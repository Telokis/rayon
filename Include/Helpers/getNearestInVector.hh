#pragma once

#ifndef RAYON_HELPERS_GETNEARESTINVECTOR_HH_
#define RAYON_HELPERS_GETNEARESTINVECTOR_HH_

#include <vector>

#include "Object.hh"
#include "Ray.hh"
#include "Tools/Stat.hh"

namespace Rayon
{
  namespace Helpers
  {
    Object* getNearestInVector(const Ray&                  ray,
                               IntersectionData&           data,
                               const std::vector<Object*>& objects);
  }
}  // namespace Rayon

#endif  // RAYON_HELPERS_GETNEARESTINVECTOR_HH_