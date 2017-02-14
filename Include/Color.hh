#pragma once

#ifndef RAYON_TOOLS_COLOR_H
#define RAYON_TOOLS_COLOR_H

#include "Tools/Helpers.hh"
#include <vector>
#include <iostream>

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

    Color&  operator+=(const Color& c);
    Color   operator+(const Color& c) const;

    inline uint32 intValue() const
    {
      uint32 res = alpha();
      res <<= 8;
      res |= red();
      res <<= 8;
      res |= green();
      res <<= 8;
      res |= blue();
      return res;
    }

    inline uint32& alpha()
    {
      return _charValues[0];
    }

    inline uint32& red()
    {
      return _charValues[1];
    }

    inline uint32& green()
    {
      return _charValues[2];
    }

    inline uint32& blue()
    {
      return _charValues[3];
    }


    inline uint8 alpha() const
    {
      return static_cast<uint8>(Tools::Clamp(_charValues[0], 0u, 255u));
    }

    inline uint8 red() const
    {
      return static_cast<uint8>(Tools::Clamp(_charValues[1], 0u, 255u));
    }

    inline uint8 green() const
    {
      return static_cast<uint8>(Tools::Clamp(_charValues[2], 0u, 255u));
    }

    inline uint8 blue() const
    {
      return static_cast<uint8>(Tools::Clamp(_charValues[3], 0u, 255u));
    }

  private:
    uint32  _charValues[4];
  };

  std::ostream& operator<<(std::ostream& stream, const Color& color);

} // namespace RayOn

#endif // RAYON_TOOLS_COLOR_H
