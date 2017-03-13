#include "Entities/Objects/Mobius.hh"
#include "SolverSecond.hh"
#include "SceneParse.hh"

#include <Json.h>

namespace Rayon
{
  Mobius::Mobius()
  {
  }

  Mobius::Mobius(const Vec_t &pos, const Vec_t &rot)
    : ParentType(pos, rot)
    , _last(nullptr)
  {
  }

  Mobius::Mobius(Float_t x, Float_t y, Float_t z)
    : ParentType(x, y, z)
    , _last(nullptr)
  {
  }

  Mobius::~Mobius()
  {
  }

  bool        Mobius::interImpl(const Ray& ray, IntersectionData& data) const
  {
    Vec_t tmp_pos;
    Vec_t tmp_dir;
    bool  found = false;
    IntersectionData realData;
    realData.k = Globals::Invalid;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    Ray transformed(ray);
    transformed.setOrigin(tmp_pos);
    transformed.setDirection(tmp_dir);

    for (const Sphere& sphere : _facets)
    {
      if (sphere.inter(transformed, data))
      {
        if (data.k < realData.k && data.k > Globals::Epsilon)
        {
          found = true;
          realData = data;
          _last = &sphere;
        }
      }
    }
    data = realData;
    return found;
  }

  void    Mobius::fillDataImpl(IntersectionData& data) const
  {
    _last->fillData(data);
  }

  void      Mobius::preprocessImpl()
  {
    Float_t step = .1;
    Vec_t p;

    _facets.clear();

    for (Float_t v = 0; v <= Globals::PI; v += (step / 2))
    {
      if (v > Globals::PI)
        v = Globals::PI;

      for (Float_t t = -0.5; t <= 0.5; t += step)
      {
        if (t > 1)
          t = 1;

        Float_t dv = 2 * v;
        Float_t tv = _torsion * v;
        Float_t c = 2 + t * Tools::Cos(tv);

        p.x = c * Tools::Cos(dv);
        p.z = c * Tools::Sin(dv);
        p.y = t * Tools::Sin(tv);

        _facets.emplace_back(p, Vec_t(0), step);
      }
    }
  }

  void Mobius::read(const Json::Value& root)
  {
    ParentType::read(root);
    readVal(root, "torsion", _torsion, 1);
    readVal(root, "width", _width, 1);
  }

  void Mobius::write(Json::Value& root) const
  {
    ParentType::write(root);
    writeVal(root, "torsion", _torsion, 1);
    writeVal(root, "width", _width, 1);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Mobius, uint32, _torsion, Torsion)
  RAYON_GENERATE_PROPERTY_DEFINITION(Mobius, Float_t, _width, Width)
} // namespace Rayon