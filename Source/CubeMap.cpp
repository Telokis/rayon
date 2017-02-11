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

    _size = img.width();

    return true;
  }

  namespace
  {
    Color getColor(const RawImage& img, Float_t u, Float_t v, uint32 size)
    {
      u = Tools::Abs(u);
      v = 1 - Tools::Abs(v);
      uint32 umin = Tools::Floor(size * u);
      uint32 vmin = Tools::Floor(size * v);
      uint32 umax = umin + 1;
      uint32 vmax = vmin + 1;
      Float_t ucoef = Tools::Abs(size * u - umin);
      Float_t vcoef = Tools::Abs(size * v - vmin);

      umin = Tools::Clamp(umin, 0u, size - 1);
      umax = Tools::Clamp(umax, 0u, size - 1);
      vmin = Tools::Clamp(vmin, 0u, size - 1);
      vmax = Tools::Clamp(vmax, 0u, size - 1);

      const Color& c1 = img.pixel(umin, vmin);
      const Color& c2 = img.pixel(umax, vmin);
      const Color& c3 = img.pixel(umin, vmax);
      const Color& c4 = img.pixel(umax, vmax);

      Color ci1 = Color::interpolate(c1, c2, ucoef);
      Color ci2 = Color::interpolate(c3, c4, ucoef);
      return Color::interpolate(ci1, ci2, vcoef);
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
        RAYON_TMP_CODE_GENERATE_SETUP(Right);
        res = getColor(img,
                       1.0f - (ray.getDirection().z / ray.getDirection().x + 1.0f) * 0.5f,
                       (ray.getDirection().y / ray.getDirection().x + 1.0f) * 0.5f,
                       _size);
      }
      else
      {
        RAYON_TMP_CODE_GENERATE_SETUP(Left);
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
                       1.0 - (ray.getDirection().x / ray.getDirection().y + 1.0f) * 0.5f,
                       1.0 - 0.5 * (ray.getDirection().z / ray.getDirection().y + 1.0f),
                       _size);
      }
    }
    else
    {
      if (ray.getDirection().z > Globals::Epsilon)
      {
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
