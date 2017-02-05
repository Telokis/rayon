#pragma once

#ifndef RAYON_MATERIAL_HH_
#define RAYON_MATERIAL_HH_

#include "Tools/Helpers.hh"
#include "Color.hh"
#include <bitset>

namespace RayOn
{
  enum class Flags : size_t
  {
    NoShadow = 0,   ///< Object doesn't catch shadow rays.
    NoImage,        ///< Object doesn't catch camera rays.
    NoReflection,   ///< Object doesn't catch reflection rays.
    NoTransparency, ///< Object doesn't catch transparency rays.
    NoShading,      ///< Object ignores diffuse lighting.


    COUNT
  };

  class Material
  {
    void  setFlag(Flags flag, bool value = true);
    bool  testFlag(Flags flag) const;

    RAYON_GENERATE_PROPERTY_DECLARATION(Material, Color, _color, Color)
    RAYON_GENERATE_PROPERTY_DECLARATION(Material, Float_t, _reflexion, Reflexion)
    RAYON_GENERATE_PROPERTY_DECLARATION(Material, Float_t, _transparency, Transparency)
    RAYON_GENERATE_PROPERTY_DECLARATION(Material, Float_t, _refraction, Refraction)

  private:
    std::bitset<static_cast<size_t>(Flags::COUNT)>  _flags;
  };
} // namespace RayOn

#endif // RAYON_MATERIAL_HH_