#include "MetaRTObjects/MetaBox.hh"
#include "Entities/Objects/Box.hh"

namespace RayOn
{
  RTObject*    MetaBox::make() const
  {
    return new Box;
  }

  const char* MetaBox::objectName() const
  {
    return Box::ObjectName;
  }
} // namespace RayOn
