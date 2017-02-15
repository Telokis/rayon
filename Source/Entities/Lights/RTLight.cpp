#include "Entities/Lights/RTLight.hh"
#include "SceneParse.hh"

#include <Json.h>

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

  void RTLight::read(const Json::Value& root)
  {
    Entity::read(root);
    readVal(root, "color", _color);
  }

  void RTLight::write(Json::Value& root) const
  {
    Entity::write(root);
    writeVal(root, "color", _color);
  }

} // namespace RayOn