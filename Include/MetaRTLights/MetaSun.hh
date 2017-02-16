#pragma once

#ifndef RAYON_META_SUN_HH_
#define RAYON_META_SUN_HH_

#include "MetaRTLights/IMetaRTLight.hh"

namespace RayOn
{
  class MetaSun : public IMetaRTLight
  {
  public:
    RTLight*    make() const final;

    const char* lightName() const final;
  };
} // namespace RayOn

#endif // RAYON_META_SUN_HH_