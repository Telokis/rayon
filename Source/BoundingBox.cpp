#include "BoundingBox.hh"

#include "Tools/Globals.hh"

namespace Rayon
{
  BoundingBox::BoundingBox()
    : _min{Globals::Infinity, Globals::Infinity, Globals::Infinity}
    , _max{-Globals::Infinity, -Globals::Infinity, -Globals::Infinity}
  {
  }

  BoundingBox::BoundingBox(const Vec_t& min, const Vec_t& max) : _min(min), _max(max)
  {
  }

  const BoundingBox BoundingBox::Infinite{
    {-Globals::Infinity, -Globals::Infinity, -Globals::Infinity},
    {Globals::Infinity, Globals::Infinity, Globals::Infinity}};

  const Vec_t BoundingBox::getSize() const
  {
    if (!_size.isValid())
      _size = _max - _min;
    return _size();
  }

  bool BoundingBox::isInside(const Vec_t& point) const
  {
    if (point.x < _min.x)
      return false;
    if (point.y < _min.y)
      return false;
    if (point.z < _min.z)
      return false;
    if (point.x > _max.x)
      return false;
    if (point.y > _max.y)
      return false;
    if (point.z > _max.z)
      return false;

    return true;
  }

  Float_t BoundingBox::intersectRay(const Ray& ray) const
  {
    Float_t t1 = (_min[0] - ray.getOrigin().x) * ray.getInvDirection().x;
    Float_t t2 = (_max[0] - ray.getOrigin().x) * ray.getInvDirection().x;

    Float_t tmin = Tools::Min(t1, t2);
    Float_t tmax = Tools::Max(t1, t2);

    for (int i = 0; i < 3; ++i)
    {
      t1 = (_min[i] - ray.getOrigin()[i]) * ray.getInvDirection()[i];
      t2 = (_max[i] - ray.getOrigin()[i]) * ray.getInvDirection()[i];

      tmin = Tools::Max(tmin, Tools::Min(Tools::Min(t1, t2), tmax));
      tmax = Tools::Min(tmax, Tools::Max(Tools::Max(t1, t2), tmin));
    }

    if (tmax > Tools::Max(tmin, 0.0))
      return Tools::Smallest(tmin, tmax);

    return Globals::Invalid;
  }

  bool BoundingBox::intersectBox(const BoundingBox& bbox)
  {
    if (bbox._max.x < _min.x)
      return false;
    if (bbox._max.y < _min.y)
      return false;
    if (bbox._max.z < _min.z)
      return false;
    if (bbox._min.x > _max.x)
      return false;
    if (bbox._min.y > _max.y)
      return false;
    if (bbox._min.z > _max.z)
      return false;

    return true;
  }

  void BoundingBox::expand(const BoundingBox& bbox)
  {
    _size.invalidate();

    _min = Tools::Min(_min, bbox._min);
    _max = Tools::Max(_max, bbox._max);
  }

  bool BoundingBox::isInfinite() const
  {
    return _min == BoundingBox::Infinite._min && _max == BoundingBox::Infinite._max;
  }

  RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(BoundingBox, _min, Min);
  RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(BoundingBox, _max, Max);

}  // namespace Rayon