#include "MetaRTObjects/MetaPlane.hh"
#include "Entities/Objects/Plane.hh"

namespace RayOn
{
  RTObject*    MetaPlane::make() const
  {
    return new Plane;
  }

  const char* MetaPlane::objectName() const
  {
    return Plane::ObjectName;
  }
} // namespace RayOn
