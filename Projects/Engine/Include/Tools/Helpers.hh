#pragma once

#ifndef RAYON_TOOLS_HELPERS_HH
#define RAYON_TOOLS_HELPERS_HH

#include <algorithm>
#include <iostream>

#include "IntersectionData.hh"
#include "Tools/Globals.hh"
#include "Tools/Pow.hh"

namespace Rayon
{
  namespace Tools
  {
    /**
     * @brief       Checks whether @a a is 0 or not based
     *              on @ref Rayon::Globals::Epsilon
     * @param[in] a Value to test.
     * @return      True if @a a is considered 0.
     *              False otherwise.
     */
    inline constexpr bool IsZero(Float_t val)
    {
      return (val < Globals::Epsilon) && (val > -Globals::Epsilon);
    }

    inline constexpr bool IsEqual(Float_t val1, Float_t val2)
    {
      return (val1 - Globals::Epsilon) < (val2 + Globals::Epsilon)
             && (val1 + Globals::Epsilon) > (val2 - Globals::Epsilon);
    }

    inline constexpr Float_t Abs(Float_t val)
    {
      return val < 0 ? -val : val;
    }

    template <class T, class U>
    inline constexpr U Interp(T val, U a, U b)
    {
      return static_cast<U>(a * (1 - val) + b * val);
    }

    template <class T, class U>
    constexpr const T Clamp(const T x, const U min, const U max)
    {
      return x < min ? min : x > max ? max : x;
    }

    inline constexpr Float_t Remap(Float_t value,
                                   Float_t inMin,
                                   Float_t inMax,
                                   Float_t outMin,
                                   Float_t outMax)
    {
      return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }

    inline constexpr Float_t Remap(Float_t value, Float_t inMax, Float_t outMax)
    {
      return Remap(value, 0, inMax, 0, outMax);
    }

    inline Float_t DotProduct(Vec_t a, Vec_t b)
    {
      return glm::dot(a, b);
    }

    inline Vec_t Cross(Vec_t a, Vec_t b)
    {
      return glm::cross(a, b);
    }

    inline Vec_t Normalize(Vec_t v)
    {
      return glm::normalize(v);
    }

    inline Float_t Length(Vec_t v)
    {
      return glm::length(v);
    }

    inline Vec_t Reflect(Vec_t v, Vec_t n)
    {
      return glm::reflect(v, n);
    }

    inline Vec_t Refract(Vec_t v, const IntersectionData& data, Float_t eta)
    {
      Float_t _eta = 2.0f - eta;
      Vec_t   n    = data.normal;
      Float_t sgn  = (eta > 1.0f ? _eta : eta) > 1.0f ? -1.0f : 1.0f;
      Float_t cosi = sgn * Tools::DotProduct(n, v);
      Vec_t   o    = (sgn * v * _eta - sgn * n * (-cosi + _eta * cosi));
      return o;
    }

    inline int32 Floor(Float_t val)
    {
      using std::floor;
      return static_cast<int32>(floor(val));
    }

    inline Int32Vec_t Floor(const Vec_t& val)
    {
      return {Floor(val.x), Floor(val.y), Floor(val.z)};
    }

    inline Int32Vec2_t Floor(const Vec2_t& val)
    {
      return {Floor(val.x), Floor(val.y)};
    }

    inline Float_t Min(Float_t a, Float_t b)
    {
      using std::min;
      return min(a, b);
    }

    inline Float_t Max(Float_t a, Float_t b)
    {
      using std::max;
      return max(a, b);
    }

    inline Vec_t Min(const Vec_t& a, const Vec_t& b)
    {
      using Tools::Min;
      return {Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z)};
    }

    inline Vec_t Max(const Vec_t& a, const Vec_t& b)
    {
      using Tools::Max;
      return {Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z)};
    }

    inline Float_t Tan(Float_t a)
    {
      using std::tan;
      return tan(a);
    }

    inline Float_t Sin(Float_t a)
    {
      using std::sin;
      return sin(a);
    }

    inline Float_t Cos(Float_t a)
    {
      using std::cos;
      return cos(a);
    }

    inline constexpr Float_t DegToRad(Float_t val)
    {
      return val * Globals::PI / 180.0;
    }

    inline constexpr Float_t RadToDeg(Float_t val)
    {
      return val * 180.0 / Globals::PI;
    }

    template <typename T>
    inline constexpr T Pow(const T& num, const T& power)
    {
      if (power == T(0))
      {
        return T(1);
      }

      T result = num;

      for (auto i = 0; i < power - 1; ++i)
      {
        result *= num;
      }

      return result;
    }

    /**
     * @brief       Returns the smallest positive value choosing between
     *              @a a and @a b.
     * @param[in] a First value.
     * @param[in] b Second value.
     * @return      @a a if @a a > @ref RT_ZERO_VAL && @a a < @a b.
     *              @a b if @a b > @ref RT_ZERO_VAL && @a b < @a a.
     *              @ref RT_INVALID if @a b < @ref RT_ZERO_VAL && @a a <
     * @ref RT_ZERO_VAL.
     * @deprecated  Not meant to be used anymore.
     */
    inline constexpr Float_t Smallest(Float_t a, Float_t b)
    {
      return ((a) < Globals::Epsilon && (b) > Globals::Epsilon
                ? (b)
                : (a) > Globals::Epsilon && (b) < Globals::Epsilon
                    ? (a)
                    : (a) < Globals::Epsilon && (b) < Globals::Epsilon ? Globals::Invalid
                                                                       : (a) < (b) ? (a) : (b));
    }
  }  // namespace Tools

  template <typename T>
  inline std::ostream& operator<<(std::ostream& stream, const RawVec3_t<T>& vec)
  {
    stream << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }";
    return stream;
  }

  template <typename T>
  inline std::ostream& operator<<(std::ostream& stream, const RawVec2_t<T>& vec)
  {
    stream << "{ " << vec.x << ", " << vec.y << " }";
    return stream;
  }
}  // namespace Rayon

#include "CodeMacros.hh"

#endif  // RAYON_TOOLS_HELPERS_HH
