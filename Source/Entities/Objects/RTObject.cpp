#include "Entities/Objects/RTObject.hh"
#include "SceneParse.hh"

#include <Json.h>

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

  void RTObject::read(const Json::Value& root)
  {
    Entity::read(root);
    _material.read(root["material"]);
  }

  void RTObject::write(Json::Value& root) const
  {
    Entity::write(root);
    _material.write(root["material"]);
  }

} // namespace RayOn
