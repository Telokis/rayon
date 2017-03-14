#pragma once

#ifndef RAYON_META_RECTANGLE_HH_
#define RAYON_META_RECTANGLE_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaRectangle : public IMetaRTShape
  {
  public:
    RTShape*   make() const final;

    const char* shapeName() const final;
  };
} // namespace Rayon

#endif // RAYON_META_RECTANGLE_HH_