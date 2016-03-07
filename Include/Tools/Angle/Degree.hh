#pragma once

#ifndef RAYON_TOOLS_ANGLE_DEGREE_HH_
#define RAYON_TOOLS_ANGLE_DEGREE_HH_

#include "Tools/Helpers/PI.hh"

namespace RayOn
{
  namespace Tools
  {
    class Radian;

    class Degree
    {
    public:
      Degree(const Radian& radianAngle);
      Degree(double angleValue);

    public:
      double        getValue() const;
      Degree&       operator=(const Radian& radianAngle);
      Degree&       operator=(double angleValue);
      Degree&       operator+=(const Degree& right);
      Degree&       operator-=(const Degree& right);
      Degree&       operator*=(double right);
      Degree&       operator/=(double right);

    private:
      double        _value;
    };

    bool  operator==(const Degree& left, const Degree& right);
    bool  operator!=(const Degree& left, const Degree& right);
    bool  operator<(const Degree& left, const Degree& right);
    bool  operator>(const Degree& left, const Degree& right);
    bool  operator<=(const Degree& left, const Degree& right);
    bool  operator>=(const Degree& left, const Degree& right);
    const Degree operator+(const Degree& left, const Degree& right);
    const Degree operator-(const Degree& left, const Degree& right);
    const Degree operator*(const Degree& left, double right);
    const Degree operator/(const Degree& left, double right);

    constexpr inline double fromRadianToDegree(double value)
    {
      return (value * 180.0) / RayOn::Globals::PI;
    }

  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_ANGLE_DEGREE_HH_