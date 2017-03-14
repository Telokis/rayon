#pragma once

#ifndef RAYON_META_SPHERE_HH_
#define RAYON_META_SPHERE_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaSphere : public IMetaRTShape
  {
  public:
    RTShape*   make() const final;

    const char* shapeName() const final;
  };
} // namespace Rayon

#endif // RAYON_META_SPHERE_HH_