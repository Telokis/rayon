#pragma once

#ifndef RAYON_MATERIALS_PLAIN_HH_
#define RAYON_MATERIALS_PLAIN_HH_

#include <yaml-cpp/node/node.h>

#include <bitset>

#include "Color.hh"
#include "Material.hh"
#include "Ray.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  class Plain : public Material<Plain>
  {
  public:
    static const constexpr auto MaterialName = "Plain";

  public:
    Plain();
    Plain(const Plain&) = default;
    Plain& operator=(const Plain&) = default;
    Plain(Plain&&)                 = default;
    Plain& operator=(Plain&&) = default;

    void setFlag(Flags flag, bool value = true);

  public:
    void read(const YAML::Node& root) override;
    void write(YAML::Node& root) const override;

  public:
    bool testFlagImpl(Flags flag) const;

  protected:
    Color   _color;
    Float_t _reflexion;
    Float_t _transparency;
    Float_t _refraction;
    Float_t _glossiness;
    Float_t _ambient;
    Float_t _shininess;

  public:
    Plain& setColor(Color value);
    Plain& setReflexion(Float_t value);
    Plain& setTransparency(Float_t value);
    Plain& setRefraction(Float_t value);
    Plain& setGlossiness(Float_t value);
    Plain& setAmbient(Float_t value);
    Plain& setShininess(Float_t value);

  public:
    Color   getColorImpl(const IntersectionData& data) const;
    Float_t getReflexionImpl(const IntersectionData& data) const;
    Float_t getTransparencyImpl(const IntersectionData& data) const;
    Float_t getRefractionImpl(const IntersectionData& data) const;
    Float_t getGlossinessImpl(const IntersectionData& data) const;
    Float_t getAmbientImpl(const IntersectionData& data) const;
    Float_t getShininessImpl(const IntersectionData& data) const;

  private:
    std::bitset<static_cast<size_t>(Flags::COUNT)> _flags;
  };
}  // namespace Rayon

#endif  // RAYON_MATERIALS_PLAIN_HH_
