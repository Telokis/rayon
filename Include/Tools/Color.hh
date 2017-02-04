#pragma once

#ifndef RAYON_TOOLS_COLOR_H
#define RAYON_TOOLS_COLOR_H

#include "Tools/Helpers/Types.hh"
#include <vector>

namespace RayOn
{
  class   Color
  {
  public:
    Color();
    Color(uint32);
    Color(uint8 r, uint8 g, uint8 b);
    Color(uint8 a, uint8 r, uint8 g, uint8 b);
    ~Color();

    static Color    interpolate(const Color& c1, const Color& c2, double val);
    static Color    average(const Color* colors, size_t size);
    static Color    average(const std::vector<Color> &colors);

    Color   &operator*=(double val);
    Color   operator*(double val) const;

    inline uint32& intValue()
    {
      return _intValue;
    }

    inline const uint32 intValue() const
    {
      return _intValue;
    }

    inline uint8& alpha()
    {
      return _charValues[0];
    }

    inline uint8& red()
    {
      return _charValues[1];
    }

    inline uint8& green()
    {
      return _charValues[2];
    }

    inline uint8& blue()
    {
      return _charValues[3];
    }


    inline const uint8 alpha() const
    {
      return _charValues[0];
    }

    inline const uint8 red() const
    {
      return _charValues[1];
    }

    inline const uint8 green() const
    {
      return _charValues[2];
    }

    inline const uint8 blue() const
    {
      return _charValues[3];
    }

  private:
    union
    {
      uint32  _intValue;
      uint8   _charValues[4];
    };
  };

} // namespace RayOn

#endif // RAYON_TOOLS_COLOR_H
