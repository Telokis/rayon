#pragma once

#ifndef RAYON_TOOLS_ANGLE_RADIAN_HH_
#define RAYON_TOOLS_ANGLE_RADIAN_HH_

#include "Tools/Helpers/PI.hh"

namespace RayOn
{
  namespace Tools
  {
    class Degree;

    class Radian
    {
    public:
      Radian(const Degree& degreeAngle);
      Radian(double angleValue);

    public:
      double        getValue() const;
      Radian&       operator=(const Degree& degreeAngle);
      Radian&       operator=(double angleValue);
      Radian&       operator+=(const Radian& right);
      Radian&       operator-=(const Radian& right);
      Radian&       operator*=(double right);
      Radian&       operator/=(double right);

    private:
      double        _value;
    };

    bool  operator==(const Radian& left, const Radian& right);
    bool  operator!=(const Radian& left, const Radian& right);
    bool  operator<(const Radian& left, const Radian& right);
    bool  operator>(const Radian& left, const Radian& right);
    bool  operator<=(const Radian& left, const Radian& right);
    bool  operator>=(const Radian& left, const Radian& right);
    const Radian operator+(const Radian& left, const Radian& right);
    const Radian operator-(const Radian& left, const Radian& right);
    const Radian operator*(const Radian& left, double right);
    const Radian operator/(const Radian& left, double right);

    constexpr inline double fromDegreeToRadian(double value)
    {
      return (value * RayOn::Globals::PI) / 180.0;
    }

  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_ANGLE_RADIAN_HH_