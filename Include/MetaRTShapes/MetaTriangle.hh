#pragma once

#ifndef RAYON_META_TRIANGLE_HH_
#define RAYON_META_TRIANGLE_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaTriangle : public IMetaRTShape
  {
  public:
    RTShape*   make() const final;

    const char* shapeName() const final;
  };
} // namespace Rayon

#endif // RAYON_META_TRIANGLE_HH_