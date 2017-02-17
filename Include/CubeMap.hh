#pragma once

#ifndef RAYON_CUBEMAP_HH_
#define RAYON_CUBEMAP_HH_

#include "RawImage.hh"
#include "Ray.hh"

#include <array>
#include <map>
#include <Json-forwards.h>

namespace Rayon
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
    static const std::map<Side, std::string> sideToStr;
    static const std::map<std::string, Side> strToSide;

  public:
    CubeMap();
    bool  loadSide(Side side, const std::string& path);
    Color interceptRay(const Ray& ray) const;

  public:
    void    read(const Json::Value& root);
    void    write(Json::Value& root) const;

  private:
    std::array<RawImage, 6> _images;
    std::array<std::string, 6> _paths;
    uint32  _size;
  };
} // namespace Rayon

#endif // RAYON_CUBEMAP_HH_
