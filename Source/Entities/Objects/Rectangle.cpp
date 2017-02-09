#include "Entities/Objects/Rectangle.hh"

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

  Float_t      Rectangle::interImpl(const Ray& ray) const
  {
    if (!_isOk)
      return Globals::Invalid;

    Float_t  k;
    Vec_t  tmp_pos;
    Vec_t  tmp_dir;

    tmp_pos = ray.getOrigin() - _pos;
    tmp_pos = indirectRotation(tmp_pos);
    tmp_dir = indirectRotation(ray.getDirection());

    if (Tools::IsZero(tmp_pos.y) || Tools::IsZero(tmp_dir.y))
      return Globals::Invalid;
    k = -1 * tmp_pos.y / tmp_dir.y;
    if (k < Globals::Epsilon)
      return Globals::Invalid;
    Vec_t p = tmp_pos + tmp_dir * k;
    if (p.x < -_halfW)
      return Globals::Invalid;
    if (p.x > _halfW)
      return Globals::Invalid;
    if (p.z < -_halfH)
      return Globals::Invalid;
    if (p.z > _halfH)
      return Globals::Invalid;
    return k;
  }

  const Vec_t&  Rectangle::normImpl(const Vec_t&) const
  {
    return _norm;
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

} // namespace RayOn