#include "Materials/PlainMaterial.hh"

#include <yaml-cpp/yaml.h>

#include "SceneParse.hh"

namespace Rayon
{
#define RAYON_DECLARE(flag) \
  {                         \
    Flags::flag, #flag      \
  }
  const std::map<Flags, std::string> PlainMaterial::flagToStr{RAYON_DECLARE(NoShadow),
                                                         RAYON_DECLARE(NoImage),
                                                         RAYON_DECLARE(NoReflection),
                                                         RAYON_DECLARE(NoTransparency),
                                                         RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE
#define RAYON_DECLARE(flag) \
  {                         \
#flag, Flags::flag      \
  }
  const std::map<std::string, Flags> PlainMaterial::strToFlag{RAYON_DECLARE(NoShadow),
                                                         RAYON_DECLARE(NoImage),
                                                         RAYON_DECLARE(NoReflection),
                                                         RAYON_DECLARE(NoTransparency),
                                                         RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE

  PlainMaterial::PlainMaterial()
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

  void PlainMaterial::setFlag(Flags flag, bool value)
  {
    _flags.set(static_cast<size_t>(flag), value);
  }

  bool PlainMaterial::testFlag(Flags flag) const
  {
    return _flags.test(static_cast<size_t>(flag));
  }

  bool PlainMaterial::testFlag(RayType type) const
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

  void PlainMaterial::read(const YAML::Node& root)
  {
    if (root["flags"] && root["flags"].IsSequence())
    {
      _flags.reset();
      const YAML::Node& flags = root["flags"];

      for (const YAML::Node& flag : flags)
      {
        if (strToFlag.count(flag.as<std::string>()))
        {
          setFlag(strToFlag.at(flag.as<std::string>()));
        }
        else
        {
          std::cout << "[Warning] Ignoring unknown material flag `" << flag.as<std::string>()
                    << "`.\n";
        }
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

  void PlainMaterial::write(YAML::Node& root) const
  {
    if (!_flags.none())
    {
      YAML::Node& flags = root["flags"];

      for (const auto& pair : flagToStr)
        if (testFlag(pair.first))
          flags.push_back(pair.second);
    }

    writeVal(root, "color", _color, 0xffff0000);
    writeVal(root, "reflexion", _reflexion, 0);
    writeVal(root, "ambient", _ambient, -1);
    writeVal(root, "glossiness", _glossiness, 0);
    writeVal(root, "refraction", _refraction, 1);
    writeVal(root, "transparency", _transparency, 0);
    writeVal(root, "shininess", _shininess, 0);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Color, _color, Color);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _reflexion, Reflexion);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _transparency, Transparency);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _refraction, Refraction);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _glossiness, Glossiness);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _ambient, Ambient);
  RAYON_GENERATE_PROPERTY_DEFINITION(PlainMaterial, Float_t, _shininess, Shininess);
}  // namespace Rayon
