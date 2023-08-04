#include "Materials/Checkerboard.hh"

#include <yaml-cpp/yaml.h>

#include "IntersectionData.hh"
#include "Scene.hh"
#include "SceneParse.hh"

namespace Rayon
{
  Checkerboard::Checkerboard() : _scale(1)
  {
  }

  void Checkerboard::read(const YAML::Node& root)
  {
    if (root["tiles"].IsSequence())
    {
      for (auto&& tileNode : root["tiles"])
      {
        RTMaterial* tile;

        readMaterial(tileNode, tile);
        addTile(tile);
      }
    }
    else
    {
      std::cout << "No tile defined for Checkerboard material. Using a default Plain...\n";

      RTMaterial* tile;

      readMaterial(YAML::Node{}, tile);
      addTile(tile);
    }

    readVal(root, "scale", _scale, 1);
  }

  void Checkerboard::write(YAML::Node root) const
  {
    root["type"] = name();

    writeVal(root, "scale", _scale, 1);

    for (auto&& tile : _tiles)
    {
      YAML::Node node;

      writeMaterial(node, tile);
      root["tiles"].push_back(node);
    }
  }

  void Checkerboard::preprocessImpl()
  {
    if (_scale <= Globals::Epsilon)
    {
      _scale = 1;
    }

    for (auto&& tile : _tiles)
    {
      tile->preprocess();
    }
  }

  const std::vector<RTMaterial*>& Checkerboard::getTiles() const
  {
    return _tiles;
  }

  std::vector<RTMaterial*>& Checkerboard::getTiles()
  {
    return _tiles;
  }

  Checkerboard& Checkerboard::addTile(RTMaterial* material)
  {
    _tiles.push_back(material);
    return *this;
  }

  RTMaterial* Checkerboard::getRealMaterial(const IntersectionData& data, uint32 depth) const
  {
    if (_tiles.size() == 0)
    {
      return nullptr;
    }

    auto checkerUV = data.uv * Float_t(_tiles.size() * 16) / _scale;
    auto point     = Tools::Floor(checkerUV * Float_t(Tools::Pow(2u, depth)));
    auto r         = (point.x + point.y) % _tiles.size();

    if (r < 0)
    {
      r += _tiles.size();
    }

    return _tiles.at(r);
  }

#define RAYON_GENERATE_CHECKERBOARD_IMPL(name, type, def)                         \
  type Checkerboard::name##Impl(const IntersectionData& data, uint32 depth) const \
  {                                                                               \
    RTMaterial* real = getRealMaterial(data, depth);                              \
                                                                                  \
    if (real)                                                                     \
    {                                                                             \
      return real->name(data, depth + 1);                                         \
    }                                                                             \
                                                                                  \
    return def;                                                                   \
  }

  RAYON_GENERATE_CHECKERBOARD_IMPL(getColor, Color, Color{});
  RAYON_GENERATE_CHECKERBOARD_IMPL(getReflexion, Float_t, 0);
  RAYON_GENERATE_CHECKERBOARD_IMPL(getTransparency, Float_t, 0);
  RAYON_GENERATE_CHECKERBOARD_IMPL(getRefraction, Float_t, 1);
  RAYON_GENERATE_CHECKERBOARD_IMPL(getGlossiness, Float_t, 0);
  RAYON_GENERATE_CHECKERBOARD_IMPL(getShininess, Float_t, 0);

#undef RAYON_GENERATE_CHECKERBOARD_IMPL

  RAYON_GENERATE_PROPERTY_DEFINITION(Checkerboard, Float_t, _scale, Scale);
}  // namespace Rayon
