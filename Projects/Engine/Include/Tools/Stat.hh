#pragma once

#ifndef RAYON_TOOLS_STAT_HH
#define RAYON_TOOLS_STAT_HH

#include <chrono>
#include <map>

#include "Ray.hh"
#include "Tools/Types.hh"

namespace Rayon::Tools
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
      , treeBranchesExplored(0)
    {
    }

    std::chrono::duration<double> elapsed;
    uint64                        intersectionsChecked;
    uint64                        hits;
    uint64                        treeBranchesExplored;

    std::map<RayType, uint64> rayCounts;
  };
}  // namespace Rayon::Tools

#endif  // RAYON_TOOLS_STAT_HH