#pragma once

#ifndef RAYON_TOOLS_HELPERS_POW_HH
#define RAYON_TOOLS_HELPERS_POW_HH

namespace RayOn
{
  namespace Tools
  {
    namespace Helpers
    {
      namespace // Anonymous namespace
      {
        template<unsigned int P, typename T>
        struct PowImpl
        {
          static const constexpr T Compute(const T& n)
          {
            return n * PowImpl<P - 1, T>::Compute(n);
          }
        };

        template<typename T>
        struct PowImpl<1, T>
        {
          static const constexpr T Compute(const T& n)
          {
            return n;
          }
        };
      } // Anonymous namespace

      template<unsigned int P, typename T>
      constexpr inline T Pow(const T& n)
      {
        return PowImpl<P, T>::Compute(n);
      }

      template<typename T>
      constexpr inline T Pow2(const T& n)
      {
        return Pow<2>(n);
      }

      template<typename T>
      constexpr inline T Pow3(const T& n)
      {
        return Pow<3>(n);
      }
    }
  }
}

#endif // RAYON_TOOLS_HELPERS_POW_HH