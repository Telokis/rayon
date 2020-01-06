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
    Config();
    Config(uint32 w, uint32 h);
    Config(uint32 w, uint32 h, uint32 j);

  public:
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, width, Width);
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, height, Height);
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, uint32, threadsCount, ThreadCount);
    RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(Config, bool, silent, Silent);
  };

}  // namespace Rayon

#endif  // RAYON_CONFIG_HH_