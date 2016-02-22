#pragma once

#ifndef RAYON_TOOLS_HELPERS_CLAMP_HH
#define RAYON_TOOLS_HELPERS_CLAMP_HH

namespace RayOn
{
  namespace Tools
  {
    namespace Helpers
    {
      template<typename T, typename U>
      constexpr const T Clamp(const T x, const U min,  const U max)
      {
        return x < min ? min : x > max ? max : x;
      }
    }
  }
}

#endif // RAYON_TOOLS_HELPERS_CLAMP_HH