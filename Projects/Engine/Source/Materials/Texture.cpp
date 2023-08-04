#include "Materials/Texture.hh"

#include <yaml-cpp/yaml.h>

#include "ImageFileHandlers/ImageFileHandler.hh"
#include "IntersectionData.hh"
#include "Scene.hh"
#include "SceneParse.hh"

namespace Rayon
{
  Texture::Texture()
  {
  }

  void Texture::read(const YAML::Node& root)
  {
    if (isString(root["filepath"]))
    {
      _filepath = root["filepath"].as<std::string>();
    }

    if (root["transparentColor"])
    {
      _transparentColor.emplace();
      readVal(root, "transparentColor", _transparentColor.value(), 0);
    }
  }

  void Texture::write(YAML::Node root) const
  {
    root["type"] = name();

    if (_filepath.length())
    {
      root["filepath"] = _filepath;
    }

    if (_transparentColor.has_value())
    {
      writeVal(root, "transparentColor", _transparentColor.value(), 0);
    }
  }

  void Texture::preprocessImpl()
  {
    std::string alteredPath = _filepath;

    // if (alteredPath.rfind("<scenePath>/", 0) == 0)
    // {
    //   if (_sourceFilename != "")
    //   {
    //     auto sourceFileDir = std::string(_sourceFilename.data(), _sourceFilename.rfind("/"));

    //     alteredPath = std::regex_replace(alteredPath, std::regex("<scenePath>"), sourceFileDir);
    //     std::cout << "Altered CubeMap path. New path is " << alteredPath << "\n";
    //   }
    //   else
    //   {
    //     std::cout << "[Warning] No source file found. Replacing '<scenePath>' by '.'...\n";
    //     alteredPath = std::regex_replace(alteredPath, std::regex("<scenePath>"), ".");
    //   }
    // }

    bool res = ImageFileHandler::readFromFileBasedOnExtension(alteredPath, _img);

    if (!res)
    {
      throw std::runtime_error("[Error]Unable to load image [" + alteredPath + "] for Texture.\n");
    }

    _imgSize = {_img.width() - 1, _img.height() - 1};

    _alphaPixels.clear();
    _alphaPixels.resize(_img.width());

    for (auto i = 0u; i < _img.width(); ++i)
    {
      _alphaPixels[i].resize(_img.height());

      for (auto j = 0u; j < _img.height(); ++j)
      {
        _alphaPixels[i][j] = (255 - _img.pixel(i, j).alpha()) / Float_t(255);
      }
    }
  }

  RawImage& Texture::getImage()
  {
    return _img;
  }

  Color Texture::getColorImpl(const IntersectionData& data, uint32 depth) const
  {
    auto checkerUV = Tools::Floor(data.uv * _imgSize);
    auto pixel     = _img.pixel(checkerUV.x, checkerUV.y);

    if (!_transparentColor || pixel.alpha() == 255)
    {
      return pixel;
    }

    return Color::interpolate(_transparentColor.value(), pixel, pixel.alpha() / Float_t(255));
  }

  Float_t Texture::getTransparencyImpl(const IntersectionData& data, uint32 depth) const
  {
    if (_transparentColor)
    {
      return 0;
    }

    auto checkerUV = Tools::Floor(data.uv * _imgSize);

    return _alphaPixels[checkerUV.x][checkerUV.y];
  }

  std::optional<Color>& Texture::getTransparentColor()
  {
    return _transparentColor;
  }

  const std::optional<Color>& Texture::getTransparentColor() const
  {
    return _transparentColor;
  }

  Texture& Texture::setTransparentColor(Color value)
  {
    _transparentColor = value;
    return *this;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Texture, std::string, _filepath, Filepath);
  RAYON_GENERATE_PROPERTY_DEFINITION(Texture, RawImage, _img, Image);
}  // namespace Rayon
