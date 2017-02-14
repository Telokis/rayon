#include "Material.hh"

namespace RayOn
{
  Material::Material()
    : _color(0)
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

  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Color, _color, Color)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _reflexion, Reflexion)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _transparency, Transparency)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _refraction, Refraction)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _glossiness, Glossiness)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _ambient, Ambient)
} // namespace RayOn
