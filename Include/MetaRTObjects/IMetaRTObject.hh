#pragma once

#ifndef RAYON_IMETA_RTOBJECT_HH_
#define RAYON_IMETA_RTOBJECT_HH_

#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  class IMetaRTObject
  {
  public:
    virtual RTObject*   make() const = 0;

    virtual const char* objectName() const = 0;
  };
} // namespace RayOn

#endif // RAYON_IMETA_RTOBJECT_HH_