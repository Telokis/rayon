#include "Material.hh"

namespace RayOn
{
  void Material::setFlag(Flags flag, bool value)
  {
    _flags.set(static_cast<size_t>(flag), value);
  }

  bool Material::testFlag(Flags flag) const
  {
    return _flags.test(static_cast<size_t>(flag));
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Color, _color, Color)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _reflexion, Reflexion)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _transparency, Transparency)
  RAYON_GENERATE_PROPERTY_DEFINITION(Material, Float_t, _refraction, Refraction)
} // namespace RayOn
