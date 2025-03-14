#include "MetaRTLights/MetaSun.hh"

#include "Entities/Lights/Sun.hh"

namespace Rayon
{
  RTLight* MetaSun::make() const
  {
    return new Sun;
  }

  const char* MetaSun::lightName() const
  {
    return Sun::LightName;
  }
}  // namespace Rayon
