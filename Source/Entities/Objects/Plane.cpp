#include "Entities/Objects/Plane.hh"
#include "Tools/SolverSecond.hh"

namespace RayOn
{
  Plane::Plane()
  {
  }

  Plane::Plane(const Vec_t &pos, const Vec_t &rot)
    : ParentType(pos, rot)
  {
  }

  Plane::Plane(Float_t x, Float_t y, Float_t z)
    : ParentType(x, y, z)
  {
  }

  Plane::~Plane()
  {
  }

  Float_t      Plane::interImpl(const Ray& ray) const
  {
    Float_t  k;
    Vec_t  tmp_pos;
    Vec_t  tmp_dir;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    if (Tools::IsZero(tmp_pos.z) || Tools::IsZero(tmp_dir.z))
      return Globals::Invalid;
    k = -1 * tmp_pos.z / tmp_dir.z;
    k = (k > Globals::Epsilon) ? k : Globals::Invalid;
    return k;
  }

  const Vec_t&  Plane::normImpl(const Vec_t&) const
  {
    return _norm;
  }

  void        Plane::preprocessImpl()
  {
    _norm = Tools::Normalize(directRotation(Vec_t(0, 0, 1)));
  }

} // namespace RayOn