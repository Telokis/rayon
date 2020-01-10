#pragma once

#ifndef RAYON_MATERIALS_PLAINMATERIAL_HH_
#define RAYON_MATERIALS_PLAINMATERIAL_HH_

#include <yaml-cpp/node/node.h>

#include <bitset>
#include <map>

#include "Color.hh"
#include "Ray.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  enum class Flags : size_t {
    NoShadow = 0,    ///< Object doesn't catch shadow rays.
    NoImage,         ///< Object doesn't catch camera rays.
    NoReflection,    ///< Object doesn't catch reflection rays.
    NoTransparency,  ///< Object doesn't catch transparency rays.
    NoShading,       ///< Object ignores diffuse lighting.

    COUNT
  };

  class PlainMaterial
  {
  public:
    static const std::map<Flags, std::string> flagToStr;
    static const std::map<std::string, Flags> strToFlag;

  public:
    PlainMaterial();
    PlainMaterial(const PlainMaterial&) = default;
    PlainMaterial& operator=(const PlainMaterial&) = default;

    void setFlag(Flags flag, bool value = true);
    bool testFlag(Flags flag) const;
    bool testFlag(RayType type) const;

  public:
    void read(const YAML::Node& root);
    void write(YAML::Node& root) const;

    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Color, _color, Color);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _reflexion, Reflexion);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _transparency, Transparency);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _refraction, Refraction);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _glossiness, Glossiness);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _ambient, Ambient);
    RAYON_GENERATE_PROPERTY_DECLARATION(PlainMaterial, Float_t, _shininess, Shininess);

  private:
    std::bitset<static_cast<size_t>(Flags::COUNT)> _flags;
  };
}  // namespace Rayon

#endif  // RAYON_MATERIALS_PLAINMATERIAL_HH_
