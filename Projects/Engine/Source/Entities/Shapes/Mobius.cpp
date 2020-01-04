#include "Entities/Shapes/Mobius.hh"

#include <Json.h>

#include "Entities/Shapes/Triangle.hh"
#include "KDTree.hh"
#include "Object.hh"
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
    for (Object*& obj : _facets)
      delete obj;
    _facets.clear();

    delete _kdtree;
  }

  bool Mobius::interImpl(const Ray& ray, IntersectionData& data) const
  {
    Vec_t            tmp_pos;
    Vec_t            tmp_dir;
    bool             found = false;
    IntersectionData realData;
    realData.k    = Globals::Invalid;
    realData.stat = data.stat;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    Ray transformed(ray);
    transformed.setOrigin(tmp_pos);
    transformed.setDirection(tmp_dir);

    auto obj = _kdtree->getNearest(ray, realData);

    if (obj)
    {
      _last = obj;
      data  = realData;
      return true;
    }

    return false;
  }

  BoundingBox Mobius::getBBoxImpl() const
  {
    return _kdtree->box;
  }

  void Mobius::fillDataImpl(IntersectionData& data) const
  {
    _last->getShape()->fillData(data);
    data.normal = Tools::Normalize(directRotation(data.normal));
  }

  void Mobius::preprocessImpl()
  {
    Float_t step = .5;
    Float_t halW = _width / 2;

    for (Object*& obj : _facets)
      delete obj;

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

        Triangle* tri1 = new Triangle{p1, p2, p3};
        Triangle* tri2 = new Triangle{p3, p2, p4};

        tri1->preprocess();
        tri2->preprocess();

        _facets.emplace_back(new Object(tri1));
        _facets.emplace_back(new Object(tri2));
      }
    }

    _kdtree = build(_facets, 0);
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