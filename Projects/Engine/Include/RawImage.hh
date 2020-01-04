#pragma once

#ifndef RAYON_RAWIMAGE_HH_
#define RAYON_RAWIMAGE_HH_

#include <memory>
#include <vector>

#include "Color.hh"

namespace Rayon
{
  class RawImage
  {
    static const int BYTES_PER_PIXEL = 4;
    using StorageType                = std::vector<Color>;

  public:
    RawImage();
    RawImage(const uint32 width, const uint32 height);

    void resize(const uint32 width, const uint32 height);

    std::unique_ptr<uint8[]> rawRGB() const;
    std::unique_ptr<uint8[]> rawRGBA() const;
    void                     fromRawRGB(const uint8* data, uint32 w, uint32 h);
    void                     fromRawRGBA(const uint8* data, uint32 w, uint32 h);

    inline uint32 width() const
    {
      return _width;
    };

    inline uint32 height() const
    {
      return _height;
    };

    inline const StorageType& pixels() const
    {
      return _pixels;
    };

    inline StorageType& pixels()
    {
      return _pixels;
    };

    inline Color& pixel(uint32 x, uint32 y)
    {
      return _pixels.at(x + y * _width);
    }

    inline Color pixel(uint32 x, uint32 y) const
    {
      return _pixels.at(x + y * _width);
    }

  private:
    uint32      _width;
    uint32      _height;
    StorageType _pixels;
  };
}  // namespace Rayon

#endif  // RAYON_RAWIMAGE_HH_