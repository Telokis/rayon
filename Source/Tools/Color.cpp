#include "Tools/Color.hh"
#include "Tools/Helpers/Clamp.hh"

using RayOn::Tools::Clamp;

namespace RayOn
{

  Color::Color()
    : _intValue(0xff000000)
  {
  }

  Color::Color(uint32 v)
    : _intValue(0xff000000 | v)
  {
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
    blue() = static_cast<uint8>(blue() * val);
    green() = static_cast<uint8>(green() * val);
    red() = static_cast<uint8>(red() * val);
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

  Color       Color::interpolate(const Color& c1, const Color& c2, double val)
  {
    Color   result = c1;

    val = Clamp(val, 0, 1);
    result.red() = static_cast<uint8>(c1.red() * (1.0 - val) + c2.red() * val);
    result.green() = static_cast<uint8>(c1.green() * (1.0 - val) + c2.green() * val);
    result.blue() = static_cast<uint8>(c1.blue() * (1.0 - val) + c2.blue() * val);
    return result;
  }

  Color       Color::average(const Color* colors, size_t size)
  {
    Color   result(0xff000000);
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

} // namespace RayOn