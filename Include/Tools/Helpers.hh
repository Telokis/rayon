#pragma once

#ifndef RAYON_TOOLS_HELPERS_HH
#define RAYON_TOOLS_HELPERS_HH

#include "Tools/Globals.hh"
#include "Tools/Pow.hh"
#include "IntersectionData.hh"
#include <algorithm>
#include <iostream>

namespace RayOn
{
  namespace Tools
  {
    /**
     * @brief       Checks whether @a a is 0 or not based
     *              on @ref RayOn::Globals::Epsilon
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
                                   Float_t inMin, Float_t inMax,
                                   Float_t outMin, Float_t outMax)
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

    inline Vec_t Reflect(Vec_t v, Vec_t n)
    {
      return glm::reflect(v, n);
    }

    inline Vec_t Refract(Vec_t v, const IntersectionData& data, Float_t eta)
    {
      Float_t n = eta;

      if (data.isInside)
        n = 1.0 / n;
      double cosI = Tools::DotProduct(v, data.normal);

      return v * n - data.normal * (-cosI + n * cosI);
    }

    inline uint32 Floor(Float_t val)
    {
      using std::floor;
      return static_cast<uint32>(floor(val));
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

    /**
     * @brief       Returns the smallest positive value choosing between
     *              @a a and @a b.
     * @param[in] a First value.
     * @param[in] b Second value.
     * @return      @a a if @a a > @ref RT_ZERO_VAL && @a a < @a b.
     *              @a b if @a b > @ref RT_ZERO_VAL && @a b < @a a.
     *              @ref RT_INVALID if @a b < @ref RT_ZERO_VAL && @a a < @ref RT_ZERO_VAL.
     * @deprecated  Not meant to be used anymore.
     */
    inline constexpr Float_t Smallest(Float_t a, Float_t b)
    {
      return ((a) < Globals::Epsilon && (b) > Globals::Epsilon ?
        (b) : (a) > Globals::Epsilon && (b) < Globals::Epsilon ?
              (a) : (a) < Globals::Epsilon && (b) < Globals::Epsilon ?
              Globals::Invalid : (a) < (b) ? (a) : (b));
    }

  } // namespace Tools
} // namespace RayOn

/**
 * @brief       Generates code for a property declaration inside a class.
 *              Will generate :
 *              - The property itself. An attribute marked as protected.
 *              - The declaration of the setter associated with the property.
 *              - The declaration of the getter associated with the property.
 *
 *	Here is an example :
 *	@code{.cpp}
 *  class Entity
 *  {
 *      RAYON_GENERATE_PROPERTY_DECLARATION(Entity, int, _color, Color)
 *  };
 *	@endcode
 *
 *  Will become :
 *	@code{.cpp}
 *  class Entity
 *  {
 *      protected:
 *          int     _color;
 *      public:
 *          Entity  *setColor(int value);
 *          int     getColor() const;
 *  };
 *	@endcode
 *
 * @param[in] className Name of the class.
 * @param[in] type      Type of the property variable. (E.g : int)
 * @param[in] varName   The name of the property variable. (E.g : _color)
 * @param[in] prefix    Name of the property. (E.g : Color)
 *
 * @see RAYON_GENERATE_PROPERTY_DEFINITION
 */
#define RAYON_GENERATE_PROPERTY_DECLARATION(className, type, varName, prefix)    \
    protected:                          \
    type    varName;                    \
    public:                             \
    void    set ## prefix(type value);  \
    type    get ## prefix() const;

 /**
  * @brief       Generates code for a property definition inside a class.
  *              Will generate :
  *              - The code of the setter associated with the property.
  *              - The code of the getter associated with the property.
  *
  *	Here is an example :
  *	@code{.cpp}
  *      RAYON_GENERATE_PROPERTY_DEFINITION(Entity, int, _color, Color)
  *	@endcode
  *
  *  Will become :
  *	@code{.cpp}
  *      Entity  *Entity::setColor(int value)
  *      {
  *          _color = value;
  *          return (this);
  *      }
  *      int     Entity::getColor() const
  *      {
  *          return (_color);
  *      }
  *	@endcode
  *
  * @param[in] className Name of the class.
  * @param[in] type      Type of the property variable. (E.g : int)
  * @param[in] varName   The name of the property variable. (E.g : _color)
  * @param[in] prefix    Name of the property. (E.g : Color)
  *
  * @see RAYON_GENERATE_PROPERTY_DECLARATION
  */
#define RAYON_GENERATE_PROPERTY_DEFINITION(className, type, varName, prefix)  \
    void    className::set ## prefix(type value)  \
    {                                             \
        varName = value;                          \
    }                                             \
    type    className::get ## prefix() const      \
    {                                             \
        return (varName);                         \
    }

#define RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(className, prefix) \
    const Vec_t&  get ## prefix() const;                          \
    Float_t       get ## prefix ## X() const;                     \
    Float_t       get ## prefix ## Y() const;                     \
    Float_t       get ## prefix ## Z() const;                     \
    void          set ## prefix(const Vec_t &);                   \
    void          set ## prefix(Float_t x, Float_t y, Float_t z); \
    void          set ## prefix ## X(Float_t value);              \
    void          set ## prefix ## Y(Float_t value);              \
    void          set ## prefix ## Z(Float_t value);

#define RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(className, varName, prefix) \
    void          className::set ## prefix(const Vec_t &vec)                \
    {                                                                       \
        varName = vec;                                                      \
    }                                                                       \
    void          className::set ## prefix(Float_t x, Float_t y, Float_t z) \
    {                                                                       \
        varName = std::move(Vec_t(x, y, z));                                \
    }                                                                       \
    void          className::set ## prefix ## X(Float_t value)              \
    {                                                                       \
        varName.x = (value);                                                \
    }                                                                       \
    void          className::set ## prefix ## Y(Float_t value)              \
    {                                                                       \
        varName.y = (value);                                                \
    }                                                                       \
    void          className::set ## prefix ## Z(Float_t value)              \
    {                                                                       \
        varName.z = (value);                                                \
    }                                                                       \
    const Vec_t&  className::get ## prefix() const                          \
    {                                                                       \
        return (varName);                                                   \
    }                                                                       \
    Float_t       className::get ## prefix ## X() const                     \
    {                                                                       \
        return (varName.x);                                                 \
    }                                                                       \
    Float_t       className::get ## prefix ## Y() const                     \
    {                                                                       \
        return (varName.y);                                                 \
    }                                                                       \
    Float_t       className::get ## prefix ## Z() const                     \
    {                                                                       \
        return (varName.z);                                                 \
    }

#endif // RAYON_TOOLS_HELPERS_HH
