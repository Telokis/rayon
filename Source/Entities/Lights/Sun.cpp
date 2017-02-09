#include "Entities/Lights/Sun.hh"
#include "Scene.hh"

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
                          const Vec_t& point) const
  {
    Float_t k;
    Vec_t   light_vec(_pos - point);
    Vec_t   tmp_pos(point + light_vec * Globals::Epsilon);

    k = Globals::Invalid;
    Ray shadowRay(RayType::Shadow, tmp_pos, light_vec);

    for (const auto& object : scene.objects())
    {
      k = object->inter(shadowRay);
      if (k > Globals::Epsilon && k < 1.0)
        return true;
    }
    return false;
  }

  Color       Sun::applyImpl(const Color& color,
                             const Scene& scene,
                             RTObject* obj,
                             const Vec_t& point) const
  {
    Float_t cos_a;
    Vec_t   light_vec;
    Color   res;

    if (doesShadow(scene, point))
      return 0;
    cos_a = 0;
    light_vec = getPos() - point;
    light_vec = Tools::Normalize(light_vec);
    cos_a = Tools::DotProduct(light_vec, obj->norm(point));
    if (cos_a < Globals::Epsilon)
      return 0xFF000000;
    res = color * cos_a;
    return Color::interpolate(res, getColor(), cos_a * _power);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Sun, Float_t, _power, Power)

} // namespace RayOn
