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
    Rayon();
    Rayon(const Config& config);

  public:
    int  run(RawImage& img, Scene& scene, bool preprocess = false);
    int  run(RawImage& img, bool preprocess = true);
    void loadSceneFromFile(const std::string& filename);
    void loadSceneFromString(const std::string& spec);

  private:
    Scene  _scene;
    Config _config;
  };
}  // namespace Rayon

#endif  // RAYON_RAYON_HH_
