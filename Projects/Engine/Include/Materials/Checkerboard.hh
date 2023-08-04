#pragma once

#ifndef RAYON_MATERIALS_CHECKERBOARD_HH_
#define RAYON_MATERIALS_CHECKERBOARD_HH_

#include <yaml-cpp/node/node.h>

#include <vector>

#include "Color.hh"
#include "Material.hh"
#include "Ray.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  class Checkerboard : public Material<Checkerboard>
  {
  public:
    static const constexpr auto MaterialName = "Checkerboard";

  public:
    Checkerboard();
    Checkerboard(const Checkerboard&) = default;
    Checkerboard& operator=(const Checkerboard&) = default;
    Checkerboard(Checkerboard&&)                 = default;
    Checkerboard& operator=(Checkerboard&&) = default;

  public:
    void read(const YAML::Node& root) override;
    void write(YAML::Node root) const override;

  public:
    const std::vector<RTMaterial*>& getTiles() const;
    std::vector<RTMaterial*>&       getTiles();
    Checkerboard&                   addTile(RTMaterial* material);

  public:
    Color   getColorImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getReflexionImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getTransparencyImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getRefractionImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getGlossinessImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getAmbientImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getShininessImpl(const IntersectionData& data, uint32 depth) const;
    void    preprocessImpl();

  private:
    RTMaterial* getRealMaterial(const IntersectionData& data, uint32 depth) const;

  private:
    std::vector<RTMaterial*> _tiles;

  protected:
    RAYON_GENERATE_PROPERTY_DECLARATION(Checkerboard, Float_t, _scale, Scale);
  };
}  // namespace Rayon

#endif  // RAYON_MATERIALS_CHECKERBOARD_HH_
