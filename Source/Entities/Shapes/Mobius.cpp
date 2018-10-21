#include "Entities/Shapes/Mobius.hh"

#include <Json.h>

#include "SceneParse.hh"
#include "SolverSecond.hh"

namespace Rayon
{
  Mobius::Mobius()
  {
  }

  Mobius::Mobius(const Vec_t& pos, const Vec_t& rot) : ParentType(pos, rot)
  {
  }

  Mobius::Mobius(Float_t x, Float_t y, Float_t z) : ParentType(x, y, z)
  {
  }

  Mobius::~Mobius()
  {
  }

  bool Mobius::interImpl(const Ray& ray, IntersectionData& data) const
  {
    Vec_t            tmp_pos;
    Vec_t            tmp_dir;
    bool             found = false;
    IntersectionData realData;
    realData.k = Globals::Invalid;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    Ray transformed(ray);
    transformed.setOrigin(tmp_pos);
    transformed.setDirection(tmp_dir);

    size_t i = 0;
    for (const Triangle& tri : _facets)
    {
      if (tri.inter(transformed, data))
      {
        if (data.k < realData.k && data.k > Globals::Epsilon)
        {
          found    = true;
          realData = data;
          _last    = i;
        }
      }
      ++i;
    }
    data = realData;
    return found;
  }

  BoundingBox Mobius::getBBoxImpl() const
  {
    return BoundingBox::Infinite;
  }

  void Mobius::fillDataImpl(IntersectionData& data) const
  {
    _facets.at(_last).fillData(data);
    data.normal = Tools::Normalize(directRotation(data.normal));
  }

  void Mobius::preprocessImpl()
  {
    Float_t step = .1;
    Float_t halW = _width / 2;

    _facets.clear();

    auto lambda = [this](Float_t v, Float_t t) {
      Vec_t p;

      Float_t cdv = Tools::Cos(2 * v);
      Float_t sdv = Tools::Sin(2 * v);
      Float_t ctv = Tools::Cos(_torsion * v);
      Float_t stv = Tools::Sin(_torsion * v);

      Float_t c = 2 + t * ctv;

      p.x = c * cdv;
      p.z = c * sdv;
      p.y = t * stv;

      return p;
    };

    for (Float_t v = 0; v < Globals::PI; v += (step / 2))
    {
      if (v > Globals::PI)
        v = Globals::PI;

      for (Float_t t = -halW; t < halW; t += step)
      {
        if (t > halW)
          t = halW;

        Vec_t p1 = lambda(v, t);
        Vec_t p2 = lambda(v + step, t);
        Vec_t p3 = lambda(v, t + step);
        Vec_t p4 = lambda(v + step, t + step);
        _facets.emplace_back(p1, p2, p3);
        _facets.back().preprocess();
        _facets.emplace_back(p3, p2, p4);
        _facets.back().preprocess();
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

  RAYON_GENERATE_PROPERTY_DEFINITION(Mobius, uint32, _torsion, Torsion);
  RAYON_GENERATE_PROPERTY_DEFINITION(Mobius, Float_t, _width, Width);
}  // namespace Rayon