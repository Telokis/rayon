#include "Entities/Lights/Sun.hh"
#include "Scene.hh"
#include <iostream>
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

  bool    Sun::doesShadow(const Scene& scene,
                          const Vec_t& point,
                          RTObject* obj) const
  {
    Vec_t   light_vec(_pos - point);
    Vec_t   tmp_pos(point + light_vec * Globals::Epsilon);
    IntersectionData  data;

    data.k = Globals::Invalid;
    Ray shadowRay(RayType::Shadow, tmp_pos, light_vec);

    for (const auto& object : scene.objects())
    {
      if (obj != object && object->inter(shadowRay, data) && data.k < 1.0)
        return true;
    }
    return false;
  }

  Color       Sun::applyImpl(const Color& color,
                             const Scene& scene,
                             const IntersectionData& data) const
  {
    Float_t cos_a;
    Vec_t   light_vec;

    if (doesShadow(scene, data.point, data.obj))
      return 0;
    cos_a = 0;
    light_vec = getPos() - data.point;
    light_vec = Tools::Normalize(light_vec);
    cos_a = Tools::DotProduct(light_vec, data.normal);
    if (cos_a < Globals::Epsilon)
      return 0;
    return color * cos_a * _power;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Sun, Float_t, _power, Power)

} // namespace RayOn
