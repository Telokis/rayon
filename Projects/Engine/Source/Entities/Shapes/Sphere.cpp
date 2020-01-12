#include "Entities/Shapes/Sphere.hh"

#include <yaml-cpp/yaml.h>

#include "SceneParse.hh"
#include "SolverSecond.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  Sphere::Sphere(Float_t radius) : _radius(radius)
  {
  }

  Sphere::Sphere(const Vec_t& pos, const Vec_t& rot, Float_t radius)
    : ParentType(pos, rot), _radius(radius)
  {
  }

  Sphere::Sphere(Float_t x, Float_t y, Float_t z, Float_t radius)
    : ParentType(x, y, z), _radius(radius)
  {
  }

  Sphere::~Sphere()
  {
  }

  bool Sphere::interImpl(const Ray& ray, IntersectionData& data) const
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
      data.k = Tools::Smallest(results[0], results[1]);

      if (data.k == results[1])
        data.isInside = true;

      data.localPoint = tmp_pos + data.k * tmp_dir;

      return data.k != Globals::Invalid;
    }

    return false;
  }

  BoundingBox Sphere::getBBoxImpl() const
  {
    return BoundingBox{
      {_pos.x - _radius, _pos.y - _radius, _pos.z - _radius},
      {_pos.x + _radius, _pos.y + _radius, _pos.z + _radius},
    };
  }

  void Sphere::fillDataImpl(IntersectionData& data) const
  {
    data.normal = Tools::Normalize(data.point - _pos);

    Float_t phi   = std::atan2(data.normal.x, -1 * data.normal.z);
    Float_t theta = std::asin(-1 * data.normal.y);

    data.uv.x = 1 - (phi + Globals::PI) / (2 * Globals::PI);
    data.uv.y = (theta + Globals::PI / 2) / Globals::PI;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Sphere, Float_t, _radius, Radius);

  void Sphere::read(const YAML::Node& root)
  {
    ParentType::read(root);
    readVal(root, "radius", _radius, 1);
  }

  void Sphere::write(YAML::Node& root) const
  {
    ParentType::write(root);
    writeVal(root, "radius", _radius, 1);
  }

}  // namespace Rayon