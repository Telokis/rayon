#include "MetaRTObjects/MetaRectangle.hh"
#include "Entities/Objects/Rectangle.hh"

namespace Rayon
{
  RTObject*    MetaRectangle::make() const
  {
    return new Rectangle;
  }

  const char* MetaRectangle::objectName() const
  {
    return Rectangle::ObjectName;
  }
} // namespace Rayon
