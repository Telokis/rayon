#include "MetaRTShapes/MetaPlane.hh"
#include "Entities/Shapes/Plane.hh"

namespace Rayon
{
  RTShape*    MetaPlane::make() const
  {
    return new Plane;
  }

  const char* MetaPlane::shapeName() const
  {
    return Plane::ShapeName;
  }
} // namespace Rayon
