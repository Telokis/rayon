#pragma once

#ifndef RAYON_IMETA_RTMATERIAL_HH_
#define RAYON_IMETA_RTMATERIAL_HH_

#include "Materials/RTMaterial.hh"

namespace Rayon
{
  class IMetaRTMaterial
  {
  public:
    virtual RTMaterial* make() const = 0;

    virtual const char* materialName() const = 0;
  };
}  // namespace Rayon

#endif  // RAYON_IMETA_RTMATERIAL_HH_