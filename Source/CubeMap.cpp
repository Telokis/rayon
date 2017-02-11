#include "CubeMap.hh"
#include "ImageFileHandlers/ImageFileHandler.hh"
#include <iostream>

namespace RayOn
{
  CubeMap::CubeMap()
    : _size(0)
  {
  }

  bool  CubeMap::loadSide(Side side, const std::string& path)
  {
    RawImage& img = _images.at(static_cast<size_t>(side));
    bool res = ImageFileHandler::readFromFileBasedOnExtension(path, img);
    if (!res)
    {
      std::cout << "[Error]Unable to load image [" << path << "] for cubemap.\n";
      return false;
    }

    if (img.width() != img.height())
    {
      std::cout << "[Error]Image [" << path << "] must be a square for cubemap.\n";
      return false;
    }

    if (_size != 0 && img.width() != _size)
    {
      std::cout << "[Error]Image [" << path << "]. All sides of the cubemap must be the same size.\n";
      return false;
    }
    return true;
  }

  namespace
  {
    Color getColor(const RawImage& img, Float_t x, Float_t y, uint32 size)
    {
      x = Tools::Clamp(Tools::Abs(x), 0u, size);
      y = Tools::Clamp(Tools::Abs(y), 0u, size);
      uint32 i1 = Tools::Floor(x * size);
      uint32 i2 = i1 + 1;
      uint32 j1 = Tools::Floor(y * size);
      uint32 j2 = j1 + 1;
      const Color& c1 = img.pixel(i1, j1);
      const Color& c2 = img.pixel(i2, j1);
      const Color& c3 = img.pixel(i1, j2);
      const Color& c4 = img.pixel(i2, j2);

      Color ci1 = Color::interpolate(c1, c2, x);
      Color ci2 = Color::interpolate(c3, c4, x);
      return Color::interpolate(ci1, ci2, y);
    }
  }

  Color CubeMap::interceptRay(const Ray& ray) const
  {
    Color res;
    const RawImage& img = _images.at(0);
#define RAYON_TMP_CODE_GENERATE_SETUP(s) \
    const RawImage& img = _images.at(static_cast<size_t>(Side::s)); \
    if (img.width() == 0) \
      return res

    if ((Tools::Abs(ray.getDirection().x) >= Tools::Abs(ray.getDirection().y))
        && (Tools::Abs(ray.getDirection().x) >= Tools::Abs(ray.getDirection().z)))
    {
      if (ray.getDirection().x > Globals::Epsilon)
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Left);
        res = getColor(img,
                       1.0f - (ray.getDirection().z / ray.getDirection().x + 1.0f) * 0.5f,
                       (ray.getDirection().y / ray.getDirection().x + 1.0f) * 0.5f,
                       _size);
      }
      else
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Right);
        res = getColor(img,
                       1.0f - (ray.getDirection().z / ray.getDirection().x + 1.0f) * 0.5f,
                       1.0f - (ray.getDirection().y / ray.getDirection().x + 1.0f) * 0.5f,
                       _size);
      }
    }
    else if ((Tools::Abs(ray.getDirection().y) >= Tools::Abs(ray.getDirection().x))
             && (Tools::Abs(ray.getDirection().y) >= Tools::Abs(ray.getDirection().z)))
    {
      if (ray.getDirection().y > Globals::Epsilon)
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Up);
        res = getColor(img,
                       0.5 * (ray.getDirection().x / ray.getDirection().y + 1.0f),
                       1.0f - (ray.getDirection().z / ray.getDirection().y + 1.0f) * 0.5f,
                       _size);
      }
      else
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Down);
        res = getColor(img,
                       1.0f - (ray.getDirection().x / ray.getDirection().y + 1.0f) * 0.5f,
                       (ray.getDirection().z / ray.getDirection().y + 1.0f) * 0.5f,
                       _size);
      }
    }
    else
    {
      if (ray.getDirection().z > Globals::Epsilon)
      {/*
        std::cout << "Coucou\n";
        std::cout << (0.5 * (ray.getDirection().x / ray.getDirection().z + 1.0f)) << "\n";
        std::cout << ((ray.getDirection().y / ray.getDirection().z + 1.0f) * 0.5f) << "\n";*/
        RAYON_TMP_CODE_GENERATE_SETUP(Front);
        res = getColor(img,
                       0.5 * (ray.getDirection().x / ray.getDirection().z + 1.0f),
                       (ray.getDirection().y / ray.getDirection().z + 1.0f) * 0.5f,
                       _size);
      }
      else
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Back);
        res = getColor(img,
                       0.5 * (ray.getDirection().x / ray.getDirection().z + 1.0f),
                       1.0f - (ray.getDirection().y / ray.getDirection().z + 1) * 0.5f,
                       _size);
      }
    }

#undef RAYON_TMP_CODE_GENERATE_SETUP
    return res;
  }
} // namespace RayOn
