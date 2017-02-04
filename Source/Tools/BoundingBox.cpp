#include "Tools/BoundingBox.hh"

namespace RayOn
{

  BoundingBox::BoundingBox()
  {
  }

  BoundingBox::BoundingBox(const Vec_t& min, const Vec_t& max)
    : _min(min), _max(max)
  {
  }

  const Vec_t  BoundingBox::getSize() const
  {
    if (!_size.isValid())
      _size = _max - _min;
    return _size();
  }

  bool              BoundingBox::isInside(const Vec_t& point) const
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

  bool  BoundingBox::intersectRay(const Ray& ray) const
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

    return tmax > Tools::Max(tmin, 0.0);
  }

} // namespace RayOn