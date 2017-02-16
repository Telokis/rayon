#pragma once

#ifndef RAYON_META_PLANE_HH_
#define RAYON_META_PLANE_HH_

#include "MetaRTObjects/IMetaRTObject.hh"

namespace RayOn
{
  class MetaPlane : public IMetaRTObject
  {
  public:
    RTObject*   make() const final;

    const char* objectName() const final;
  };
} // namespace RayOn

#endif // RAYON_META_PLANE_HH_