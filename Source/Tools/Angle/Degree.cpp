#include "Tools/Angle/Radian.hh"
#include "Tools/Angle/Degree.hh"

namespace RayOn
{
  namespace Tools
  {

    Degree::Degree(const Radian& radianAngle)
      : _value(fromRadianToDegree(radianAngle.getValue()))
    {
    }

    Degree::Degree(double angleValue)
      : _value(angleValue)
    {
    }

    double        Degree::getValue() const
    {
      return _value;
    }

    Degree&       Degree::operator=(const Radian& radianAngle)
    {
      _value = fromRadianToDegree(radianAngle.getValue());
      return *this;
    }

    Degree&       Degree::operator=(double angleValue)
    {
      _value = angleValue;
      return *this;
    }

    Degree&       Degree::operator+=(const Degree& right)
    {
      _value += right.getValue();
      return *this;
    }

    Degree&       Degree::operator-=(const Degree& right)
    {
      _value -= right.getValue();
      return *this;
    }

    Degree&       Degree::operator*=(double right)
    {
      _value *= right;
      return *this;
    }

    Degree&       Degree::operator/=(double right)
    {
      _value /= right;
      return *this;
    }

    // Comparison operators
    bool  operator==(const Degree& left, const Degree& right)
    {
      return left.getValue() == right.getValue();
    }

    bool  operator!=(const Degree& left, const Degree& right)
    {
      return !(left == right);
    }

    bool  operator<(const Degree& left, const Degree& right)
    {
      return left.getValue() < right.getValue();
    }

    bool  operator>(const Degree& left, const Degree& right)
    {
      return left.getValue() > right.getValue();
    }

    bool  operator<=(const Degree& left, const Degree& right)
    {
      return !(left > right);
    }

    bool  operator>=(const Degree& left, const Degree& right)
    {
      return !(left < right);
    }

    // Arithmetic operators
    const Degree  operator+(const Degree& left, const Degree& right)
    {
      Degree  result(left);
      result += right;
      return result;
    }

    const Degree  operator-(const Degree& left, const Degree& right)
    {
      Degree  result(left);
      result -= right;
      return result;
    }

    const Degree  operator*(const Degree& left, double right)
    {
      Degree  result(left);
      result *= right;
      return result;
    }

    const Degree  operator/(const Degree& left, double right)
    {
      Degree  result(left);
      result /= right;
      return result;
    }

  } // namespace Tools
} // namespace RayOn