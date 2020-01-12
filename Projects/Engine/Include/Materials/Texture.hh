#pragma once

#ifndef RAYON_MATERIALS_TEXTURE_HH_
#define RAYON_MATERIALS_TEXTURE_HH_

#include <yaml-cpp/node/node.h>

#include <optional>
#include <vector>

#include "Color.hh"
#include "Material.hh"
#include "RawImage.hh"
#include "Ray.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  class Texture : public Material<Texture>
  {
  public:
    static const constexpr auto MaterialName = "Texture";

  public:
    Texture();
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;
    Texture(Texture&&)                 = default;
    Texture& operator=(Texture&&) = default;

  public:
    void read(const YAML::Node& root) override;
    void write(YAML::Node& root) const override;

  public:
    RawImage& getImage();

  public:
    Color   getColorImpl(const IntersectionData& data, uint32 depth) const;
    Float_t getTransparencyImpl(const IntersectionData& data, uint32 depth) const;
    void    preprocessImpl();

  private:
    Vec2_t                            _imgSize;
    std::vector<std::vector<Float_t>> _alphaPixels;
    std::optional<Color>              _transparentColor;

  public:
    std::optional<Color>&       getTransparentColor();
    const std::optional<Color>& getTransparentColor() const;
    Texture&                    setTransparentColor(Color value);

  protected:
    RAYON_GENERATE_PROPERTY_DECLARATION(Texture, std::string, _filepath, Filepath);
    RAYON_GENERATE_PROPERTY_DECLARATION(Texture, RawImage, _img, Image);
  };
}  // namespace Rayon

#endif  // RAYON_MATERIALS_TEXTURE_HH_
