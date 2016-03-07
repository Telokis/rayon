#pragma once

#ifndef RAYON_TOOLS_HELPERS_GLOBALS_HH
#define RAYON_TOOLS_HELPERS_GLOBALS_HH

#include "Tools/Color.hh"
#include "Tools/Helpers/PI.hh"

namespace RayOn
{
  namespace Globals
  {
    /**
    * @brief   When no intersection is found.
    */
    extern const RayOn::Tools::Color NoColor;

    /**
    * @brief   Represents an infinite number.
    */
    extern const double Infinity;

    /**
    * @brief   Represents an invalid number.
    */
    extern const double Invalid;

    /**
    * @brief   Represents a floating zero.
    */
    extern const double SmallEnough;

  } // namespace Globals
} // namespace RayOn

#endif // RAYON_TOOLS_HELPERS_GLOBALS_HH