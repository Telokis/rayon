#pragma once

#ifndef RAYON_IMETA_RTLIGHT_HH_
#define RAYON_IMETA_RTLIGHT_HH_

#include "Entities/Lights/RTLight.hh"

namespace Rayon
{
  class IMetaRTLight
  {
  public:
    virtual RTLight* make() const = 0;

    virtual const char* lightName() const = 0;
  };
}  // namespace Rayon

#endif  // RAYON_IMETA_RTLIGHT_HH_