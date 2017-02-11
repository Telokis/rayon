#pragma once

#ifndef RAYON_RAYON_HH_
#define RAYON_RAYON_HH_

#include "Config.hh"
#include "Scene.hh"

namespace RayOn
{
  inline Config& config()
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
    Scene _scene;
  };
} // namespace RayOn

#endif // RAYON_RAYON_HH_