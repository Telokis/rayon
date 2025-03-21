#include "Entities/Shapes/Box.hh"

#include <yaml-cpp/yaml.h>

#include "SceneParse.hh"

namespace Rayon
{
  Box::Box(Float_t width, Float_t height, Float_t depth)
    : _width(width), _height(height), _depth(depth)
  {
  }

  Box::Box(const Vec_t& pos, const Vec_t& rot, Float_t width, Float_t height, Float_t depth)
    : ParentType(pos, rot), _width(width), _height(height), _depth(depth)
  {
  }

  Box::Box(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height, Float_t depth)
    : ParentType(x, y, z), _width(width), _height(height), _depth(depth)
  {
  }

  Box::~Box()
  {
  }

  bool Box::interImpl(const Ray& ray, IntersectionData& data) const
  {
    if (!_isOk)
      return false;

    Vec_t tmp_pos;
    Vec_t tmp_dir;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = Float_t(1.0) / indirectRotation(ray.getDirection());

    Float_t t1 = (_min[0] - tmp_pos.x) * tmp_dir.x;
    Float_t t2 = (_max[0] - tmp_pos.x) * tmp_dir.x;

    Float_t tmin = Tools::Min(t1, t2);
    Float_t tmax = Tools::Max(t1, t2);

    for (int i = 0; i < 3; ++i)
    {
      t1 = (_min[i] - tmp_pos[i]) * tmp_dir[i];
      t2 = (_max[i] - tmp_pos[i]) * tmp_dir[i];

      tmin = Tools::Max(tmin, Tools::Min(Tools::Min(t1, t2), tmax));
      tmax = Tools::Min(tmax, Tools::Max(Tools::Max(t1, t2), tmin));
    }

    if (tmax > Tools::Max(tmin, 0.0))
    {
      data.k          = Tools::Smallest(tmin, tmax);
      data.localPoint = tmp_pos + data.k * tmp_dir;

      return true;
    }
    return false;
  }

  BoundingBox Box::getBBoxImpl() const
  {
    return BoundingBox::Infinite;
  }

  void Box::fillDataImpl(IntersectionData& data) const
  {
    data.localPoint = data.point - _pos;
    data.localPoint = indirectRotation(data.localPoint);

    if (Tools::IsEqual(data.localPoint.x, _min.x))
      data.normal = -_norm[0];
    else if (Tools::IsEqual(data.localPoint.x, _max.x))
      data.normal = _norm[0];
    else if (Tools::IsEqual(data.localPoint.y, _min.y))
      data.normal = -_norm[1];
    else if (Tools::IsEqual(data.localPoint.y, _max.y))
      data.normal = _norm[1];
    else if (Tools::IsEqual(data.localPoint.z, _min.z))
      data.normal = -_norm[2];
    else if (Tools::IsEqual(data.localPoint.z, _max.z))
      data.normal = _norm[2];
  }

  void Box::preprocessImpl()
  {
    _isOk = !(_width < Globals::Epsilon || _height < Globals::Epsilon || _depth < Globals::Epsilon);
    _min  = {-_width / 2, -_height / 2, -_depth / 2};
    _max  = {_width / 2, _height / 2, _depth / 2};
    _norm[0] = Tools::Normalize(directRotation(Vec_t(1, 0, 0)));
    _norm[1] = Tools::Normalize(directRotation(Vec_t(0, 1, 0)));
    _norm[2] = Tools::Normalize(directRotation(Vec_t(0, 0, 1)));
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Box, Float_t, _width, Width);
  RAYON_GENERATE_PROPERTY_DEFINITION(Box, Float_t, _height, Height);
  RAYON_GENERATE_PROPERTY_DEFINITION(Box, Float_t, _depth, Depth);

  void Box::read(const YAML::Node& root)
  {
    ParentType::read(root);
    readVal(root, "width", _width, 1);
    readVal(root, "height", _height, 1);
    readVal(root, "depth", _depth, 1);
  }

  void Box::write(YAML::Node root) const
  {
    ParentType::write(root);
    writeVal(root, "width", _width, 1);
    writeVal(root, "height", _height, 1);
    writeVal(root, "depth", _depth, 1);
  }

}  // namespace Rayon