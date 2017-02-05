#include "Entities/Objects/Sphere.hh"
#include "SolverSecond.hh"
#include "Tools/Helpers.hh"

namespace RayOn
{
  Sphere::Sphere(Float_t radius)
    : _radius(radius)
  {
  }

  Sphere::Sphere(const Vec_t& pos, const Vec_t& rot, Float_t radius)
    : ParentType(pos, rot),
    _radius(radius)
  {
  }

  Sphere::Sphere(Float_t x, Float_t y, Float_t z, Float_t radius)
    : ParentType(x, y, z),
    _radius(radius)
  {
  }

  Sphere::~Sphere()
  {
  }

  Float_t      Sphere::interImpl(const Ray& ray) const
  {
    using Tools::Pow2;

    Vec_t   tmp_pos;
    Vec_t   tmp_dir;
    Float_t results[2];

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    if (Tools::Solver::Second(results,
                              Pow2(tmp_dir.x) + Pow2(tmp_dir.y) + Pow2(tmp_dir.z),
                              2.0 * Tools::DotProduct(tmp_pos, tmp_dir),
                              Pow2(tmp_pos.x) + Pow2(tmp_pos.y) + Pow2(tmp_pos.z) - Pow2(_radius)))
    {
      return Tools::Smallest(results[0], results[1]);
    }
    return Globals::Invalid;
  }

  Vec_t       Sphere::normImpl(const Vec_t& point) const
  {
    return Tools::Normalize(point - _pos);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Sphere, Float_t, _radius, Radius)

} // namespace RayOn