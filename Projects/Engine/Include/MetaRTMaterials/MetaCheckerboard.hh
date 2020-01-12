#pragma once

#ifndef RAYON_META_CHECKERBOARD_HH_
#define RAYON_META_CHECKERBOARD_HH_

#include "MetaRTMaterials/IMetaRTMaterial.hh"

namespace Rayon
{
  class MetaCheckerboard : public IMetaRTMaterial
  {
  public:
    RTMaterial* make() const final;

    const char* materialName() const final;
  };
}  // namespace Rayon

#endif  // RAYON_META_CHECKERBOARD_HH_