#include "MetaRTShapes/MetaRectangle.hh"

#include "Entities/Shapes/Rectangle.hh"

namespace Rayon
{
  RTShape* MetaRectangle::make() const
  {
    return new Rectangle;
  }

  const char* MetaRectangle::shapeName() const
  {
    return Rectangle::ShapeName;
  }
}  // namespace Rayon
