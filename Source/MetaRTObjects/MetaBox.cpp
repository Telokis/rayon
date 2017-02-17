#include "MetaRTObjects/MetaBox.hh"
#include "Entities/Objects/Box.hh"

namespace Rayon
{
  RTObject*    MetaBox::make() const
  {
    return new Box;
  }

  const char* MetaBox::objectName() const
  {
    return Box::ObjectName;
  }
} // namespace Rayon
