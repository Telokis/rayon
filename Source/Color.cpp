#include "Color.hh"

using RayOn::Tools::Clamp;

namespace RayOn
{

  Color::Color()
    : _charValues{0xff, 0, 0, 0}
  {
  }

  Color::Color(uint32 v)
  {
    _charValues[0] = 0xff;
    _charValues[1] = (v & uint32(0xFF0000)) >> 16;
    _charValues[2] = (v & uint32(0xFF00)) >> 8;
    _charValues[3] = (v & uint32(0xFF));
  }

  Color::Color(uint8 r, uint8 g, uint8 b)
    : _charValues{0xff, r, g, b}
  {
  }

  Color::Color(uint8 a, uint8 r, uint8 g, uint8 b)
    : _charValues{a, r, g, b}
  {
  }

  Color   &Color::operator*=(double val)
  {
    val = Clamp(val, 0, 1);
    _charValues[1] = Tools::Floor(_charValues[1] * val + 0.5);
    _charValues[2] = Tools::Floor(_charValues[2] * val + 0.5);
    _charValues[3] = Tools::Floor(_charValues[3] * val + 0.5);
    return *this;
  }

  Color::~Color()
  {
  }

  Color       Color::operator*(double val) const
  {
    Color   result = *this;

    result *= val;
    return result;
  }

  Color& Color::operator+=(const Color& c)
  {
    red() = red() + c.red();
    green() = green() + c.green();
    blue() = blue() + c.blue();
    return *this;
  }

  Color Color::operator+(const Color& c) const
  {
    Color   result = *this;

    result += c;
    return result;
  }

  Color       Color::interpolate(const Color& c1, const Color& c2, double val)
  {
    val = Clamp(val, 0, 1);
    return Tools::Interp(val, c1, c2);
  }

  Color       Color::average(const Color* colors, size_t size)
  {
    Color   result;
    uint64  tmp[3] = {0};

    if (!size)
      return result;

    for (size_t i = 0; i < size; ++i)
    {
      tmp[0] += colors[i].red();
      tmp[1] += colors[i].green();
      tmp[2] += colors[i].blue();
    }

    result.red() = static_cast<uint8>(tmp[0] / size);
    result.green() = static_cast<uint8>(tmp[1] / size);
    result.blue() = static_cast<uint8>(tmp[2] / size);
    return result;
  }

  Color       Color::average(const std::vector<Color>& colors)
  {
    return average(colors.data(), colors.size());
  }

  std::ostream& operator<<(std::ostream& stream, const Color& color)
  {
    return stream << color.intValue();
  }

} // namespace RayOn