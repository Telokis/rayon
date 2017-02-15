#include "Entities/Objects/Rectangle.hh"
#include "SceneParse.hh"

#include <Json.h>

namespace RayOn
{
  Rectangle::Rectangle(Float_t width, Float_t height)
    : _width(width)
    , _height(height)
  {
  }

  Rectangle::Rectangle(const Vec_t &pos, const Vec_t &rot, Float_t width, Float_t height)
    : ParentType(pos, rot)
    , _width(width)
    , _height(height)
  {
  }

  Rectangle::Rectangle(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height)
    : ParentType(x, y, z)
    , _width(width)
    , _height(height)
  {
  }

  Rectangle::~Rectangle()
  {
  }

  bool      Rectangle::interImpl(const Ray& ray, IntersectionData& data) const
  {
    if (!_isOk)
      return false;

    Vec_t  tmp_pos;
    Vec_t  tmp_dir;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    if (Tools::IsZero(tmp_pos.y) || Tools::IsZero(tmp_dir.y))
      return false;
    data.k = -1 * tmp_pos.y / tmp_dir.y;
    if (data.k < Globals::Epsilon)
      return false;
    data.localPoint = tmp_pos + tmp_dir * data.k;
    if (data.localPoint.x < -_halfW)
      return false;
    if (data.localPoint.x > _halfW)
      return false;
    if (data.localPoint.z < -_halfH)
      return false;
    if (data.localPoint.z > _halfH)
      return false;
    return true;
  }

  void    Rectangle::fillDataImpl(IntersectionData& data) const
  {
    data.normal = _norm;
  }

  void        Rectangle::preprocessImpl()
  {
    _isOk = !(_width < Globals::Epsilon || _height < Globals::Epsilon);
    _halfW = _width / 2;
    _halfH = _height / 2;
    _norm = Tools::Normalize(directRotation(Vec_t(0, 1, 0)));
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Rectangle, Float_t, _width, Width)
  RAYON_GENERATE_PROPERTY_DEFINITION(Rectangle, Float_t, _height, Height)

  void Rectangle::read(const Json::Value& root)
  {
    ParentType::read(root);
    readVal(root, "width", _width);
    readVal(root, "height", _height);
  }

  void Rectangle::write(Json::Value& root) const
  {
    ParentType::write(root);
    writeVal(root, "width", _width);
    writeVal(root, "height", _height);
  }

} // namespace RayOn