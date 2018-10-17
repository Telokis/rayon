#include "Entities/Shapes/Triangle.hh"

#include <Json.h>

#include "SceneParse.hh"
#include "SolverSecond.hh"

namespace Rayon
{
  Triangle::Triangle(Vec_t v1, Vec_t v2, Vec_t v3) : ParentType(), _v{{v1, v2, v3}}
  {
  }

  bool Triangle::interImpl(const Ray& ray, IntersectionData& data) const
  {
    Vec_t   pvec = Tools::Cross(ray.getDirection(), _v0v2);
    Float_t det  = Tools::DotProduct(_v0v1, pvec);

    if (Tools::IsZero(det))
      return false;
    if (det < Globals::Epsilon)
      data.isInside = true;

    Float_t invDet = 1.0 / det;

    Vec_t tvec = ray.getOrigin() - _v[0];

    Float_t t, u, v;
    u = Tools::DotProduct(tvec, pvec) * invDet;

    if (u < 0 || u > 1)
      return false;

    Vec_t qvec = Tools::Cross(tvec, _v0v1);
    v          = Tools::DotProduct(ray.getDirection(), qvec) * invDet;

    if (v < 0 || u + v > 1)
      return false;

    t = Tools::DotProduct(_v0v2, qvec) * invDet;

    if (t > Globals::Epsilon)
    {
      data.k = t;
      return true;
    }

    return false;
  }

  void Triangle::fillDataImpl(IntersectionData& data) const
  {
    data.normal = _norm;
  }

  void Triangle::preprocessImpl()
  {
    _v0v1 = _v[1] - _v[0];
    _v0v2 = _v[2] - _v[0];
    _norm = Tools::Cross(_v0v1, _v0v2);
    _norm = Tools::Normalize(_norm);
  }

  void Triangle::read(const Json::Value& root)
  {
    ParentType::read(root);
    readVal(root, "v0", _v[0], Vec_t(1, 0, 0));
    readVal(root, "v1", _v[1], Vec_t(0, 1, 0));
    readVal(root, "v2", _v[2], Vec_t(0, 0, 1));
  }

  void Triangle::write(Json::Value& root) const
  {
    ParentType::write(root);
    writeVal(root, "v0", _v[0], Vec_t(1, 0, 0));
    writeVal(root, "v1", _v[1], Vec_t(0, 1, 0));
    writeVal(root, "v2", _v[2], Vec_t(0, 0, 1));
  }

}  // namespace Rayon