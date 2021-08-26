#pragma once

#ifndef RAYON_TOOLS_COLOR_H
#define RAYON_TOOLS_COLOR_H

#include <iostream>
#include <map>
#include <vector>
#include "Tools/Types.hh"

namespace Rayon
{
  class Color
  {
  public:
    Color();
    Color(uint32);
    Color(uint8 r, uint8 g, uint8 b);
    Color(uint8 a, uint8 r, uint8 g, uint8 b);
    ~Color();

    static Color interpolate(const Color& c1, const Color& c2, double val);
    static Color average(const Color* colors, size_t size);
    static Color average(const std::vector<Color>& colors);

    Color& operator*=(double val);
    Color  operator*(double val) const;

    Color& operator+=(const Color& c);
    Color  operator+(const Color& c) const;

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

    inline void setAlpha(uint32 value)
    {
      _charValues[0] = value;
    }

    inline void setRed(uint32 value)
    {
      _charValues[1] = value;
    }

    inline void setGreen(uint32 value)
    {
      _charValues[2] = value;
    }

    inline void setBlue(uint32 value)
    {
      _charValues[3] = value;
    }

    uint8 alpha() const;
    uint8 red() const;
    uint8 green() const;
    uint8 blue() const;

  private:
    uint32 _charValues[4];
  };

  inline const std::map<std::string, Color>& namedColors()
  {
    static std::map<std::string, Color> cols{{"black", 0},
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
                                             {"purple", 0x800080}};

    return cols;
  }

  std::ostream& operator<<(std::ostream& stream, const Color& color);

}  // namespace Rayon

#endif  // RAYON_TOOLS_COLOR_H
