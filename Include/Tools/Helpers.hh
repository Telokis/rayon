#pragma once

#ifndef RAYON_TOOLS_HELPERS_HH
#define RAYON_TOOLS_HELPERS_HH

#include "Tools/Vector3.hh"

#include "Tools/Helpers/PI.hh"
#include "Tools/Helpers/Pow.hh"
#include "Tools/Helpers/Clamp.hh"
#include "Tools/Helpers/Types.hh"

#include "Tools/Color.hh"

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
 * @brief   When no intersection is found.
 */
 #define NO_COLOR (0xff000000);

/**
 * @brief       Converts a degree angle to radian
 * @param[in] x Angle to convert.
 * @return      Returns radian value.
 */
#define RT_DEG_TO_RAD(x)  (((double)(x) * M_PI / 180))

/**
 * @brief       Converts a radian angle to degree
 * @param[in] x Angle to convert.
 * @return      Returns degree value.
 */
#define RT_RAD_TO_DEG(x)  (((double)(x) * 180 / M_PI))

/**
 * @brief   Represents an invalid number.
 */
#define RT_INVALID          (INFINITY)

/**
 * @brief   Represents a floating zero.
 */
#define RT_ZERO_VAL         (0.00001)

/**
 * @brief       Checks whether @a a is 0 or not based
 *              on @ref RT_ZERO_VAL
 * @param[in] a Value to test.
 * @return      True if @a a is considered 0.
 *              False otherwise.
 */
#define RT_NULL_FLOAT(a)    ((a) < RT_ZERO_VAL && (a) > -1 * RT_ZERO_VAL)

/**
 * @brief       Returns the smallest positive value choosing between
 *              @a a and @a b.
 * @param[in] a First value.
 * @param[in] b Second value.
 * @return      @a a if @a a > @ref RT_ZERO_VAL && @a a < @a b.
 *              @a b if @a b > @ref RT_ZERO_VAL && @a b < @a a.
 *              @ref RT_INVALID if @a b < @ref RT_ZERO_VAL && @a a < @ref RT_ZERO_VAL.
 */
#define RT_RETURN_SMALLEST_ABOVE_ZERO(a, b) \
    ((a) < RT_ZERO_VAL && (b) > RT_ZERO_VAL ? \
    (b) : (a) > RT_ZERO_VAL && (b) < RT_ZERO_VAL ? \
    (a) : (a) < RT_ZERO_VAL && (b) < RT_ZERO_VAL ? \
    RT_INVALID : (a) < (b) ? (a) : (b))

#endif // RAYON_TOOLS_HELPERS_HH
