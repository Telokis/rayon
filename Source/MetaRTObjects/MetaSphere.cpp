#include "MetaRTObjects/MetaSphere.hh"
#include "Entities/Objects/Sphere.hh"

namespace RayOn
{
  RTObject*    MetaSphere::make() const
  {
    return new Sphere;
  }

  const char* MetaSphere::objectName() const
  {
    return Sphere::ObjectName;
  }
} // namespace RayOn
