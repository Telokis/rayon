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

} // namespace RayOn