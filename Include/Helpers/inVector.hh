#pragma once

#ifndef RAYON_HELPERS_INVECTOR_HH_
#define RAYON_HELPERS_INVECTOR_HH_

#include <functional>
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

    bool iterateIfIntersect(const Ray&                                            ray,
                            IntersectionData&                                     data,
                            const std::vector<Object*>&                           objects,
                            std::function<bool(const Object*, IntersectionData&)> func);
  }  // namespace Helpers
}  // namespace Rayon

#endif  // RAYON_HELPERS_INVECTOR_HH_