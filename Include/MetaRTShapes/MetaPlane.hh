#pragma once

#ifndef RAYON_META_PLANE_HH_
#define RAYON_META_PLANE_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaPlane : public IMetaRTShape
  {
  public:
    RTShape* make() const final;

    const char* shapeName() const final;
  };
}  // namespace Rayon

#endif  // RAYON_META_PLANE_HH_