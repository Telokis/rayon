#pragma once

#ifndef RAYON_CONFIG_HH_
#define RAYON_CONFIG_HH_

#include <string>

#include "Tools/CodeMacros.hh"
#include "Tools/Types.hh"

namespace Rayon
{
  struct Config
  {
  public:
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, width, Width);
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, height, Height);
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, threadsCount, ThreadCount);
  };

}  // namespace Rayon

#endif  // RAYON_CONFIG_HH_