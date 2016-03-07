#include "Tools/BoundingBox.hh"

namespace RayOn
{
  namespace Tools
  {

    BoundingBox::BoundingBox()
    {
    }

    BoundingBox::BoundingBox(const VectorType& min, const VectorType& max)
      : _min(min), _max(max)
    {
    }

    const VectorType  BoundingBox::getSize() const
    {
      if (!_size.isValid())
        _size = _max - _min;
      return _size();
    }

    bool              BoundingBox::isInside(const VectorType& point) const
    {
      if (point.x() < _min.x())
        return false;
      if (point.y() < _min.y())
        return false;
      if (point.z() < _min.z())
        return false;
      if (point.x() > _max.x())
        return false;
      if (point.y() > _max.y())
        return false;
      if (point.z() > _max.z())
        return false;

        return true;
    }


  } // namespace Tools
} // namespace RayOn