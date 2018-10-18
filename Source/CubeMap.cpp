#include "CubeMap.hh"

#include <Json.h>

#include <iostream>

#include "ImageFileHandlers/ImageFileHandler.hh"

namespace Rayon
{
#define RAYON_DECLARE(side, name) \
  {                               \
    Side::side, #name             \
  }
  const std::map<Side, std::string> CubeMap::sideToStr{RAYON_DECLARE(Front, front),
                                                       RAYON_DECLARE(Back, back),
                                                       RAYON_DECLARE(Left, left),
                                                       RAYON_DECLARE(Right, right),
                                                       RAYON_DECLARE(Up, up),
                                                       RAYON_DECLARE(Down, down)};
#undef RAYON_DECLARE
#define RAYON_DECLARE(side, name) \
  {                               \
#name, Side::side             \
  }
  const std::map<std::string, Side> CubeMap::strToSide{RAYON_DECLARE(Front, front),
                                                       RAYON_DECLARE(Back, back),
                                                       RAYON_DECLARE(Left, left),
                                                       RAYON_DECLARE(Right, right),
                                                       RAYON_DECLARE(Up, up),
                                                       RAYON_DECLARE(Down, down)};
#undef RAYON_DECLARE

  CubeMap::CubeMap() : _size(0)
  {
  }

  bool CubeMap::loadSide(Side side, const std::string& path)
  {
    RawImage&    img  = _images.at(static_cast<size_t>(side));
    std::string& file = _paths.at(static_cast<size_t>(side));
    bool         res  = ImageFileHandler::readFromFileBasedOnExtension(path, img);
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
      std::cout << "[Error]Image [" << path
                << "]. All sides of the cubemap must be the same size.\n";
      return false;
    }

    _size = img.width();
    file  = path;

    return true;
  }

  namespace
  {
    Color getColor(const RawImage& img, Float_t u, Float_t v, uint32 size)
    {
      u             = Tools::Abs(u);
      v             = 1 - Tools::Abs(v);
      uint32  umin  = Tools::Floor(size * u);
      uint32  vmin  = Tools::Floor(size * v);
      uint32  umax  = umin + 1;
      uint32  vmax  = vmin + 1;
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
  }  // namespace

  Color CubeMap::interceptRay(const Ray& ray) const
  {
    Color res;
#define RAYON_TMP_CODE_GENERATE_SETUP(s)                          \
  const RawImage& img = _images.at(static_cast<size_t>(Side::s)); \
  if (img.width() == 0)                                           \
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

  void CubeMap::read(const Json::Value& root)
  {
    for (auto it = root.begin(); it != root.end(); ++it)
    {
      const std::string& key = it.key().asString();
      if (strToSide.count(key) && it->isString())
        loadSide(strToSide.at(key), it->asString());
      else if (!it->isString())
        std::cout << "[Warning] Non string path found for cubemap. Skipping...\n";
      else if (!strToSide.count(key))
        std::cout << "[Warning] Unknown side found for cubemap. Skipping...\n";
    }
  }

  void CubeMap::write(Json::Value& root) const
  {
    for (auto i = 0u; i < _paths.size(); ++i)
    {
      const std::string& str = _paths[i];
      if (!str.empty())
        root[sideToStr.at(static_cast<Side>(i))] = str;
    }
  }
}  // namespace Rayon
