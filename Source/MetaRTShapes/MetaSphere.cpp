#include "MetaRTShapes/MetaSphere.hh"
#include "Entities/Shapes/Sphere.hh"

namespace Rayon
{
  RTShape*    MetaSphere::make() const
  {
    return new Sphere;
  }

  const char* MetaSphere::shapeName() const
  {
    return Sphere::ShapeName;
  }
} // namespace Rayon
