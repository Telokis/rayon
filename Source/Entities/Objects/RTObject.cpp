#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  RTObject::RTObject()
  {
  }

  RTObject::RTObject(const Vec_t& pos, const Vec_t& rot)
    : Entity(pos, rot)
  {
  }

  RTObject::RTObject(Float_t x, Float_t y, Float_t z)
    : Entity(x, y, z)
  {
  }

  RTObject::~RTObject()
  {
  }

  void RTObject::setMaterial(const Material& material)
  {
    _material = material;
  }

  Material& RTObject::getMaterial()
  {
    return _material;
  }

  const Material& RTObject::getMaterial() const
  {
    return _material;
  }

} // namespace RayOn
