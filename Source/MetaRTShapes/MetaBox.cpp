#include "MetaRTShapes/MetaBox.hh"
#include "Entities/Shapes/Box.hh"

namespace Rayon
{
  RTShape*    MetaBox::make() const
  {
    return new Box;
  }

  const char* MetaBox::shapeName() const
  {
    return Box::ShapeName;
  }
} // namespace Rayon
