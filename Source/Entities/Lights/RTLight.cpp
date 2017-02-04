#include "Entities/Lights/RTLight.hh"

namespace RayOn
{
  RTLight::RTLight(const Color &color)
    : _color(color)
  {
  }

  RTLight::RTLight(const Vec_t &pos,
                   const Vec_t &rot,
                   const Color &color)
    : Entity(pos, rot), _color(color)
  {
  }

  RTLight::RTLight(Float_t x, Float_t y, Float_t z,
                   const Color &color)
    : Entity(x, y, z), _color(color)
  {
  }

  RTLight::~RTLight()
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(RTLight, Color, _color, Color)

} // namespace RayOn