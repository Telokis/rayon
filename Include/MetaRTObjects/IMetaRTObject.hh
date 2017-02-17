#pragma once

#ifndef RAYON_IMETA_RTOBJECT_HH_
#define RAYON_IMETA_RTOBJECT_HH_

#include "Entities/Objects/RTObject.hh"

namespace Rayon
{
  class IMetaRTObject
  {
  public:
    virtual RTObject*   make() const = 0;

    virtual const char* objectName() const = 0;
  };
} // namespace Rayon

#endif // RAYON_IMETA_RTOBJECT_HH_