#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  RTObject::RTObject()
  {
    _color = 0;
    _reflexion = 0;
  }

  RTObject::RTObject(const Vec_t &pos, const Vec_t &rot)
    : Entity(pos, rot)
  {
    _color = 0;
    _reflexion = 0;
  }

  RTObject::RTObject(Float_t x, Float_t y, Float_t z)
    : Entity(x, y, z)
  {
    _color = 0;
    _reflexion = 0;
  }

  RTObject::~RTObject()
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(RTObject, Color, _color, Color)
  RAYON_GENERATE_PROPERTY_DEFINITION(RTObject, double, _reflexion, Reflexion)
} // namespace RayOn
