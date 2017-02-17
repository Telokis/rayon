#include "Entities/Objects/Plane.hh"
#include "SolverSecond.hh"
#include "SceneParse.hh"

#include <Json.h>

namespace Rayon
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

  bool        Plane::interImpl(const Ray& ray, IntersectionData& data) const
  {
    Vec_t tmp_pos;
    Vec_t tmp_dir;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    if (Tools::IsZero(tmp_pos.y) || Tools::IsZero(tmp_dir.y))
      return false;
    data.k = -1 * tmp_pos.y / tmp_dir.y;
    if (data.k < Globals::Epsilon)
      return false;
    return true;
  }

  void    Plane::fillDataImpl(IntersectionData& data) const
  {
    data.normal = _norm;
  }

  void        Plane::preprocessImpl()
  {
    _norm = Tools::Normalize(directRotation(Vec_t(0, 1, 0)));
  }

  void Plane::read(const Json::Value& root)
  {
    ParentType::read(root);
  }

  void Plane::write(Json::Value& root) const
  {
    ParentType::write(root);
  }

} // namespace Rayon