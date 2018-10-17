#pragma once

#ifndef RAYON_META_BOX_HH_
#define RAYON_META_BOX_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaBox : public IMetaRTShape
  {
  public:
    RTShape* make() const final;

    const char* shapeName() const final;
  };
}  // namespace Rayon

#endif  // RAYON_META_BOX_HH_