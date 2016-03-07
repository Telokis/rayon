#include "Tools/Angle/Radian.hh"
#include "Tools/Angle/Degree.hh"

namespace RayOn
{
  namespace Tools
  {

    Radian::Radian(const Degree& degreeAngle)
      : _value(fromDegreeToRadian(degreeAngle.getValue()))
    {
    }

    Radian::Radian(double angleValue)
      : _value(angleValue)
    {
    }

    double        Radian::getValue() const
    {
      return _value;
    }

    Radian&       Radian::operator=(const Degree& degreeAngle)
    {
      _value = fromDegreeToRadian(degreeAngle.getValue());
      return *this;
    }

    Radian&       Radian::operator=(double angleValue)
    {
      _value = angleValue;
      return *this;
    }

    Radian&       Radian::operator+=(const Radian& right)
    {
      _value += right.getValue();
      return *this;
    }

    Radian&       Radian::operator-=(const Radian& right)
    {
      _value -= right.getValue();
      return *this;
    }

    Radian&       Radian::operator*=(double right)
    {
      _value *= right;
      return *this;
    }

    Radian&       Radian::operator/=(double right)
    {
      _value /= right;
      return *this;
    }

    // Comparison operators
    bool  operator==(const Radian& left, const Radian& right)
    {
      return left.getValue() == right.getValue();
    }
    
    bool  operator!=(const Radian& left, const Radian& right)
    {
      return !(left == right);
    }
    
    bool  operator<(const Radian& left, const Radian& right)
    {
      return left.getValue() < right.getValue();
    }
    
    bool  operator>(const Radian& left, const Radian& right)
    {
      return left.getValue() > right.getValue();
    }
    
    bool  operator<=(const Radian& left, const Radian& right)
    {
      return !(left > right);
    }
    
    bool  operator>=(const Radian& left, const Radian& right)
    {
      return !(left < right);
    }
    
    // Arithmetic operators
    const Radian  operator+(const Radian& left, const Radian& right)
    {
      Radian  result(left);
      result += right;
      return result;
    }
    
    const Radian  operator-(const Radian& left, const Radian& right)
    {
      Radian  result(left);
      result -= right;
      return result;
    }
    
    const Radian  operator*(const Radian& left, double right)
    {
      Radian  result(left);
      result *= right;
      return result;
    }
    
    const Radian  operator/(const Radian& left, double right)
    {
      Radian  result(left);
      result /= right;
      return result;
    }
    
  } // namespace Tools
} // namespace RayOn