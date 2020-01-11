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
    Color        getColorImpl(const Scene&            scene,
                              const Ray&              ray,
                              const IntersectionData& data,
                              uint8                   depth) const;
    bool         testFlagImpl(Flags flag) const;
    const Plain* getPlainImpl() const;

  private:
    Color   handleReflection(const Scene&            scene,
                             const Ray&              ray,
                             const IntersectionData& data,
                             uint8                   depth) const;
    Color   handleTransparency(const Scene&            scene,
                               const Ray&              ray,
                               const IntersectionData& data,
                               uint8                   depth) const;
    Float_t getFresnelReflectance(const IntersectionData& data, const Ray& ray) const;
    Color   handleReflectionAndRefraction(const Scene&            scene,
                                          const Ray&              ray,
                                          const IntersectionData& data,
                                          uint8                   depth) const;

  protected:
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Color, _color, Color);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _reflexion, Reflexion);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _transparency, Transparency);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _refraction, Refraction);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _glossiness, Glossiness);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _ambient, Ambient);
    RAYON_GENERATE_PROPERTY_DECLARATION(Plain, Float_t, _shininess, Shininess);

  private:
    std::bitset<static_cast<size_t>(Flags::COUNT)> _flags;
  };
}  // namespace Rayon

#endif  // RAYON_MATERIALS_PLAIN_HH_
