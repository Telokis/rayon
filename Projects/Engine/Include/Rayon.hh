#pragma once

#ifndef RAYON_RAYON_HH_
#define RAYON_RAYON_HH_

#include "Config.hh"
#include "Scene.hh"

namespace Rayon
{
  class Rayon
  {
  public:
    Rayon(const Config& config);

  public:
    int  run(RawImage& img);
    void registerDefaults();
    void loadSceneFromFile(const std::string& filename);

  private:
    Scene  _scene;
    Config _config;
  };
}  // namespace Rayon

#endif  // RAYON_RAYON_HH_
