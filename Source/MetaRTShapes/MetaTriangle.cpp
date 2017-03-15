#include "MetaRTShapes/MetaTriangle.hh"
#include "Entities/Shapes/Triangle.hh"

namespace Rayon
{
  RTShape*    MetaTriangle::make() const
  {
    return new Triangle;
  }

  const char* MetaTriangle::shapeName() const
  {
    return Triangle::ShapeName;
  }
} // namespace Rayon
