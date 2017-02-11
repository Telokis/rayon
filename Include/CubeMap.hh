#pragma once

#ifndef RAYON_CUBEMAP_HH_
#define RAYON_CUBEMAP_HH_

#include "RawImage.hh"
#include "Ray.hh"
#include <array>

namespace RayOn
{
  enum class Side : size_t
  {
    Front,
    Back,
    Left,
    Right,
    Up,
    Down
  };

  class CubeMap
  {
  public:
    CubeMap();
    bool  loadSide(Side side, const std::string& path);
    Color interceptRay(const Ray& ray) const;

  private:
    std::array<RawImage, 6> _images;
    uint32  _size;
  };
} // namespace RayOn

#endif // RAYON_CUBEMAP_HH_