#pragma once

#ifndef RAYON_TOOLS_HELPERS_GLOBALS_HH
#define RAYON_TOOLS_HELPERS_GLOBALS_HH

#include "Tools/PI.hh"
#include "Tools/Types.hh"

namespace Rayon
{
  namespace Globals
  {
    /**
     * @brief   Represents an infinite Float_t.
     */
    static constexpr const Float_t Infinity = std::numeric_limits<Float_t>::infinity();

    /**
     * @brief   Represents an invalid Float_t.
     */
    static constexpr const Float_t Invalid = Infinity;

    /**
     * @brief   Represents a floating zero.
     */
    static constexpr const Float_t Epsilon = 0.00000001;

  } // namespace Globals
} // namespace Rayon

#endif // RAYON_TOOLS_HELPERS_GLOBALS_HH
