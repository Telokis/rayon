#pragma once

#ifndef RAYON_TOOLS_STAT_HH
#define RAYON_TOOLS_STAT_HH

#include <chrono>
#include <map>

#include "Ray.hh"
#include "Tools/Types.hh"

namespace Rayon
{
  namespace Tools
  {
    struct Stat
    {
      Stat()
        : elapsed(0)
        , intersectionsChecked(0)
        , hits(0)
        , rayCounts{{RayType::Shadow, 0},
                    {RayType::Primary, 0},
                    {RayType::Reflected, 0},
                    {RayType::Transparency, 0}}
      {
      }

      std::chrono::duration<double> elapsed;
      uint64                        intersectionsChecked;
      uint64                        hits;

      std::map<RayType, uint64> rayCounts;
    };
  }  // namespace Tools
}  // namespace Rayon

#endif  // RAYON_TOOLS_STAT_HH