#include "MetaRTObjects/MetaPlane.hh"
#include "Entities/Objects/Plane.hh"

namespace Rayon
{
  RTObject*    MetaPlane::make() const
  {
    return new Plane;
  }

  const char* MetaPlane::objectName() const
  {
    return Plane::ObjectName;
  }
} // namespace Rayon
