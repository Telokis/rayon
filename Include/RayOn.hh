#pragma once

#ifndef RAYON_RAYON_HH_
#define RAYON_RAYON_HH_

#include "Config.hh"
#include "Scene.hh"

namespace Rayon
{
  inline Config& config()
  {
    static Config config;
    return config;
  }

  class Rayon
  {
  public:
    Rayon(int ac, char** av);

  public:
    int run();

  private:
    Scene _scene;
  };
} // namespace Rayon

#endif // RAYON_RAYON_HH_