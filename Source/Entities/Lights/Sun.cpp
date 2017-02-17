#include "Entities/Lights/Sun.hh"
#include "Scene.hh"
#include "SceneParse.hh"

#include <iostream>
#include <Json.h>

namespace RayOn
{
  Sun::Sun()
    : _power(0.5)
  {
  }

  Sun::Sun(const Vec_t &pos)
    : ParentType(pos, Vec_t(0, 0, 0)),
    _power(0.5)
  {
  }

  Sun::Sun(Float_t x, Float_t y, Float_t z)
    : ParentType(x, y, z),
    _power(0.5)
  {
  }

  Sun::~Sun()
  {
  }

  Color       Sun::applyImpl(const Color& color,
                             const Scene& scene,
                             const IntersectionData& data,
                             Color& specular) const
  {
    Float_t cos_a;
    Vec_t   light_vec;

    if (doesShadow(_pos, scene, data.point, data.obj))
      return 0;
    cos_a = 0;
    light_vec = getPos() - data.point;
    light_vec = Tools::Normalize(light_vec);
    cos_a = Tools::DotProduct(light_vec, data.normal);
    if (cos_a < Globals::Epsilon)
      return 0;
    specular += getSpecular(light_vec, scene, _color, data);
    return color * cos_a * _power;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Sun, Float_t, _power, Power)

  void Sun::read(const Json::Value& root)
  {
    ParentType::read(root);
    readVal(root, "power", _power, 0.5);
  }

  void Sun::write(Json::Value& root) const
  {
    ParentType::write(root);
    writeVal(root, "power", _power, 0.5);
  }

} // namespace RayOn
