#include "Tools/RawImage.hh"

namespace RayOn
{
  RawImage::RawImage(const uint32 width, const uint32 height)
    : _width(width)
    , _height(height)
    , _pixels(width * height)
  {
  }

  RawImage::RawImage()
    : _width(0)
    , _height(0)
  {
  }

  void  RawImage::resize(const uint32 width, const uint32 height)
  {
    _width = width;
    _height = height;
    _pixels.resize(width * height);
  }

} // namespace RayOn
