#pragma once

#ifndef RAYON_TOOLS_HELPERS_TYPES_HH
#define RAYON_TOOLS_HELPERS_TYPES_HH

#include <cstdint>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

namespace Rayon
{
  using int8  = std::int8_t;
  using int16 = std::int16_t;
  using int32 = std::int32_t;
  using int64 = std::int64_t;

  using uint8  = std::uint8_t;
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;
  using uint64 = std::uint64_t;

  /**
   * @brief   Typedef for values.
   *          We may want to change it later.
   */
  using Float_t = long double;

  /**
   * @brief   Typedef for Vec_ts.
   *          We may want to change it later.
   */
  using Vec_t = glm::tvec3<Float_t>;

  using Mat_t = glm::tmat3x3<Float_t>;
}  // namespace Rayon

#endif  // RAYON_TOOLS_HELPERS_TYPES_HH