#pragma once

#ifndef RAYON_TOOLS_COLOR_H
#define RAYON_TOOLS_COLOR_H

#include "Tools/Helpers.hh"
#include <vector>
#include <map>
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

  inline  const std::map<std::string, Color>& colors()
  {
    static std::map<std::string, Color> cols{
      {"black", 0},
      {"white", 0xffffff},
      {"red", 0xff0000},
      {"green", 0xff00},
      {"blue", 0xff},
      {"swimming pool", 0xFF67E6EC},
      {"deeppink4", 0xFF8B0A50},
      {"silver", 0xC0C0C0},
      {"gray", 0x808080},
      {"maroon", 0x800000},
      {"yellow", 0xFFFF00},
      {"olive", 0x808000},
      {"lime", 0x00FF00},
      {"aqua", 0x00FFFF},
      {"teal", 0x008080},
      {"navy", 0x000080},
      {"fuchsia", 0xFF00FF},
      {"purple", 0x800080}
    };

    return cols;
  }

  std::ostream& operator<<(std::ostream& stream, const Color& color);

} // namespace RayOn

#endif // RAYON_TOOLS_COLOR_H
