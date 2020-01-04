#include "RawImage.hh"

namespace Rayon
{
  RawImage::RawImage(const uint32 width, const uint32 height)
    : _width(width), _height(height), _pixels(width * height)
  {
  }

  RawImage::RawImage() : _width(0), _height(0)
  {
  }

  void RawImage::resize(const uint32 width, const uint32 height)
  {
    _width  = width;
    _height = height;
    _pixels.resize(width * height);
  }

  std::unique_ptr<uint8[]> RawImage::rawRGBA() const
  {
    std::unique_ptr<uint8[]> data(new uint8[_width * _height * 4]);

    size_t i = 0;
    for (const Color& color : _pixels)
    {
      auto index      = i * 4;
      data[index]     = color.red();
      data[index + 1] = color.green();
      data[index + 2] = color.blue();
      data[index + 3] = color.alpha();
      ++i;
    }
    return data;
  }

  void RawImage::fromRawRGBA(const uint8* data, uint32 w, uint32 h)
  {
    resize(w, h);
    size_t i = 0;
    for (Color& color : _pixels)
    {
      auto index    = i * 4;
      color.red()   = data[index];
      color.green() = data[index + 1];
      color.blue()  = data[index + 2];
      color.alpha() = data[index + 3];
      ++i;
    }
  }

  std::unique_ptr<uint8[]> RawImage::rawRGB() const
  {
    std::unique_ptr<uint8[]> data(new uint8[_width * _height * 3]);

    size_t i = 0;
    for (const Color& color : _pixels)
    {
      auto index      = i * 3;
      data[index]     = color.red();
      data[index + 1] = color.green();
      data[index + 2] = color.blue();
      ++i;
    }
    return data;
  }

  void RawImage::fromRawRGB(const uint8* data, uint32 w, uint32 h)
  {
    resize(w, h);
    size_t i = 0;
    for (Color& color : _pixels)
    {
      auto index    = i * 3;
      color.red()   = data[index];
      color.green() = data[index + 1];
      color.blue()  = data[index + 2];
      ++i;
    }
  }

}  // namespace Rayon
