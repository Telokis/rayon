#pragma once

#ifndef RAYON_RAYON_HH_
#define RAYON_RAYON_HH_

#include "Config.hh"

namespace RayOn
{
  static Config& config()
  {
    static Config config;
    return config;
  }

  class RayOn
  {
  public:
    RayOn(int ac, char** av);

  public:
    int run();

  private:
  };
} // namespace RayOn

#endif // RAYON_RAYON_HH_