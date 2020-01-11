#include "Materials/Plain.hh"

#include <yaml-cpp/yaml.h>

#include "IntersectionData.hh"
#include "Scene.hh"
#include "SceneParse.hh"

namespace Rayon
{
  Plain::Plain()
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

  void Plain::setFlag(Flags flag, bool value)
  {
    _flags.set(static_cast<size_t>(flag), value);
  }

  bool Plain::testFlagImpl(Flags flag) const
  {
    return _flags.test(static_cast<size_t>(flag));
  }

  void Plain::read(const YAML::Node& root)
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

  void Plain::write(YAML::Node& root) const
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

  Plain& Plain::setColor(Color value)
  {
    _color = value;
    return *this;
  }

  Plain& Plain::setReflexion(Float_t value)
  {
    _reflexion = value;
    return *this;
  }

  Plain& Plain::setTransparency(Float_t value)
  {
    _transparency = value;
    return *this;
  }

  Plain& Plain::setRefraction(Float_t value)
  {
    _refraction = value;
    return *this;
  }

  Plain& Plain::setGlossiness(Float_t value)
  {
    _glossiness = value;
    return *this;
  }

  Plain& Plain::setAmbient(Float_t value)
  {
    _ambient = value;
    return *this;
  }

  Plain& Plain::setShininess(Float_t value)
  {
    _shininess = value;
    return *this;
  }

  Color Plain::getColorImpl(const IntersectionData&) const
  {
    return _color;
  }

  Float_t Plain::getReflexionImpl(const IntersectionData&) const
  {
    return _reflexion;
  }

  Float_t Plain::getTransparencyImpl(const IntersectionData&) const
  {
    return _transparency;
  }

  Float_t Plain::getRefractionImpl(const IntersectionData&) const
  {
    return _refraction;
  }

  Float_t Plain::getGlossinessImpl(const IntersectionData&) const
  {
    return _glossiness;
  }

  Float_t Plain::getAmbientImpl(const IntersectionData&) const
  {
    return _ambient;
  }

  Float_t Plain::getShininessImpl(const IntersectionData&) const
  {
    return _shininess;
  }
}  // namespace Rayon
