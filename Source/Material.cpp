#include "Material.hh"
#include "SceneParse.hh"
#include <Json.h>

namespace RayOn
{
  #define RAYON_DECLARE(flag) \
    {Flags::flag, #flag}
  const std::map<Flags, std::string> Material::flagToStr {
    RAYON_DECLARE(NoShadow),
    RAYON_DECLARE(NoImage),
    RAYON_DECLARE(NoReflection),
    RAYON_DECLARE(NoTransparency),
    RAYON_DECLARE(NoShading)
  };
  #undef RAYON_DECLARE
  #define RAYON_DECLARE(flag) \
    {#flag, Flags::flag}
  const std::map<std::string, Flags> Material::strToFlag {
    RAYON_DECLARE(NoShadow),
    RAYON_DECLARE(NoImage),
    RAYON_DECLARE(NoReflection),
    RAYON_DECLARE(NoTransparency),
    RAYON_DECLARE(NoShading)
  };
  #undef RAYON_DECLARE

  Material::Material()
    : _color(0xffffff)
    , _reflexion(0)
    , _transparency(0)
    , _refraction(1)
    , _flags(0)
    , _glossiness(0)
    , _ambient(-1)
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
    readVal(root, "color", _color);
    readVal(root, "reflexion", _reflexion);
    readVal(root, "ambient", _ambient);
    readVal(root, "glossiness", _glossiness);
    readVal(root, "refraction", _refraction);
    readVal(root, "transparency", _transparency);
  }

  void Material::write(Json::Value& root) const
  {
    Json::Value& flags = root["flags"];
    for (const auto& pair : flagToStr)
      if (testFlag(pair.first))
        flags.append(pair.second);
    writeVal(root, "color", _color);
    writeVal(root, "reflexion", _reflexion);
    writeVal(root, "ambient", _ambient);
    writeVal(root, "glossiness", _glossiness);
    writeVal(root, "refraction", _refraction);
    writeVal(root, "transparency", _transparency);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Color, _color, Color)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _reflexion, Reflexion)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _transparency, Transparency)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _refraction, Refraction)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _glossiness, Glossiness)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _ambient, Ambient)
} // namespace RayOn
