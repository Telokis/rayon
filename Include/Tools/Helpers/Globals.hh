#pragma once

#ifndef RAYON_TOOLS_HELPERS_GLOBALS_HH
#define RAYON_TOOLS_HELPERS_GLOBALS_HH

#include "Tools/Color.hh"
#include "Tools/Helpers/PI.hh"
#include "Tools/Helpers/Types.hh"

namespace RayOn
{
  namespace Globals
  {
    /**
     * @brief   Represents an infinite number.
     */
    extern constexpr const Float_t Infinity = std::numeric_limits<Float_t>::infinity();

    /**
     * @brief   Represents an invalid number.
     */
    extern constexpr const Float_t Invalid = Infinity;

    /**
     * @brief   Represents a floating zero.
     */
    extern constexpr const Float_t SmallEnough = 0.00000001;

  } // namespace Globals
} // namespace RayOn

#endif // RAYON_TOOLS_HELPERS_GLOBALS_HH