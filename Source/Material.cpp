#include "Material.hh"

#include <Json.h>

#include "SceneParse.hh"

namespace Rayon
{
#define RAYON_DECLARE(flag) \
  {                         \
    Flags::flag, #flag      \
  }
  const std::map<Flags, std::string> Material::flagToStr{RAYON_DECLARE(NoShadow),
                                                         RAYON_DECLARE(NoImage),
                                                         RAYON_DECLARE(NoReflection),
                                                         RAYON_DECLARE(NoTransparency),
                                                         RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE
#define RAYON_DECLARE(flag) \
  {                         \
#flag, Flags::flag      \
  }
  const std::map<std::string, Flags> Material::strToFlag{RAYON_DECLARE(NoShadow),
                                                         RAYON_DECLARE(NoImage),
                                                         RAYON_DECLARE(NoReflection),
                                                         RAYON_DECLARE(NoTransparency),
                                                         RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE

  Material::Material()
    : _color(0xffff0000)
    , _reflexion(0)
    , _transparency(0)
    , _refraction(1)
    , _flags(0)
    , _glossiness(0)
    , _ambient(-1)
    , _shininess(0)
  {
  }

  void Material::setFlag(Flags flag, bool value)
  {
    _flags.set(static_cast<size_t>(flag), value);
  }

  bool Material::testFlag(Flags flag) const
  {
    return _flags.test(static_cast<size_t>(flag));
  }

  bool Material::testFlag(RayType type) const
  {
    if (_flags.none())
      return false;
    switch (type)
    {
      case RayType::Shadow:
        return testFlag(Flags::NoShadow);

      case RayType::Reflected:
        return testFlag(Flags::NoReflection);

      case RayType::Transparency:
        return testFlag(Flags::NoTransparency);

      case RayType::Primary:
        return testFlag(Flags::NoImage);
    }
    return false;
  }

  void Material::read(const Json::Value& root)
  {
    if (root.isMember("flags") && root["flags"].isArray())
    {
      _flags.reset();
      const Json::Value& flags = root["flags"];
      for (const Json::Value& flag : flags)
      {
        if (strToFlag.count(flag.asString()))
          setFlag(strToFlag.at(flag.asString()));
        else
          std::cout << "[Warning] Ignoring unknown material flag `" << flag.asString() << "`.\n";
      }
    }
    readVal(root, "color", _color, 0xffff0000);
    readVal(root, "reflexion", _reflexion, 0);
    readVal(root, "ambient", _ambient, -1);
    readVal(root, "glossiness", _glossiness, 0);
    readVal(root, "refraction", _refraction, 1);
    readVal(root, "transparency", _transparency, 0);
    readVal(root, "shininess", _shininess, 0);
  }

  void Material::write(Json::Value& root) const
  {
    if (!_flags.none())
    {
      Json::Value& flags = root["flags"];
      for (const auto& pair : flagToStr)
        if (testFlag(pair.first))
          flags.append(pair.second);
    }
    writeVal(root, "color", _color, 0xffff0000);
    writeVal(root, "reflexion", _reflexion, 0);
    writeVal(root, "ambient", _ambient, -1);
    writeVal(root, "glossiness", _glossiness, 0);
    writeVal(root, "refraction", _refraction, 1);
    writeVal(root, "transparency", _transparency, 0);
    writeVal(root, "shininess", _shininess, 0);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Color, _color, Color);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _reflexion, Reflexion);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _transparency, Transparency);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _refraction, Refraction);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _glossiness, Glossiness);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _ambient, Ambient);
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _shininess, Shininess);
}  // namespace Rayon
