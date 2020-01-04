#pragma once

#ifndef RAYON_META_MOBIUS_HH_
#define RAYON_META_MOBIUS_HH_

#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class MetaMobius : public IMetaRTShape
  {
  public:
    RTShape* make() const final;

    const char* shapeName() const final;
  };
}  // namespace Rayon

#endif  // RAYON_META_MOBIUS_HH_