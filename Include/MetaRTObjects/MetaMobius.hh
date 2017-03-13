#pragma once

#ifndef RAYON_META_MOBIUS_HH_
#define RAYON_META_MOBIUS_HH_

#include "MetaRTObjects/IMetaRTObject.hh"

namespace Rayon
{
  class MetaMobius : public IMetaRTObject
  {
  public:
    RTObject*   make() const final;

    const char* objectName() const final;
  };
} // namespace Rayon

#endif // RAYON_META_MOBIUS_HH_