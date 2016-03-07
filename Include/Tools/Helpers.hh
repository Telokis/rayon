#pragma once

#ifndef RAYON_TOOLS_HELPERS_HH
#define RAYON_TOOLS_HELPERS_HH

#include "Tools/Helpers/Globals.hh"
#include "Tools/Helpers/Pow.hh"
#include "Tools/Helpers/Clamp.hh"
#include "Tools/Helpers/Types.hh"

#include "Tools/Angle/Degree.hh"
#include "Tools/Angle/Radian.hh"

#include "Tools/Vector3.hh"
#include "Tools/Color.hh"

namespace RayOn
{
/**
 * @brief   Typedef for values.
 *          We may want to change it later.
 */
typedef double NumberType;

/**
 * @brief   Typedef for vectors.
 *          We may want to change it later.
 */
typedef RayOn::Tools::Vector3<NumberType>   VectorType;

/**
 * @brief       Checks whether @a a is 0 or not based
 *              on @ref RayOn::Globals::SmallEnough
 * @param[in] a Value to test.
 * @return      True if @a a is considered 0.
 *              False otherwise.
 */
inline bool IsZero(double val)
{
  return (val < RayOn::Globals::SmallEnough) && (val > -RayOn::Globals::SmallEnough);
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
#define RT_RETURN_SMALLEST_ABOVE_ZERO(a, b) \
    ((a) < RT_ZERO_VAL && (b) > RT_ZERO_VAL ? \
    (b) : (a) > RT_ZERO_VAL && (b) < RT_ZERO_VAL ? \
    (a) : (a) < RT_ZERO_VAL && (b) < RT_ZERO_VAL ? \
    RT_INVALID : (a) < (b) ? (a) : (b))

} // namespace RayOn

#endif // RAYON_TOOLS_HELPERS_HH
