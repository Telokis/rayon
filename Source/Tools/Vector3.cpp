#include "Tools/Vector3.hh"
#include <math.h>

namespace RayOn
{
  namespace Tools
  {
    template <typename T>
    constexpr Vector3<T>::Vector3()
    {
      _data.fill(T());
    }

    template <typename T>
    constexpr Vector3<T>::Vector3(T _x, T _y, T _z)
      : _data{{_x, _y, _z}}
    {
    }

    template <typename T>
    constexpr Vector3<T>::Vector3(T a)
    {
      _data.fill(a);
    }

    template <typename T>
    Vector3<T>::~Vector3()
    {
    }

    template <typename T>
    Vector3<T>::Vector3(Vector3<T> &&ref)
    {
      _data = std::move(ref._data);
    }

    template <typename T>
    Vector3<T>	&Vector3<T>::operator=(Vector3<T> &&ref)
    {
      if (this != &ref)
        _data = std::move(ref._data);
      return (*this);
    }

    template <typename T>
    void    Vector3<T>::normalize()
    {
      T     d;

      d = static_cast<T>(sqrt(static_cast<long double>(x() * x() + y() * y() + z() * z())));
      *this /= d;
    }

    template <typename T>
    Vector3<T>      Vector3<T>::normalized() const
    {
      Vector3<T>    res(*this);

      res.normalize();
      return (res);
    }

    template <typename T>
    constexpr T   Vector3<T>::dotProduct(const Vector3 &a, const Vector3 &b)
    {
      return (a.x() * b.x() + a.y() * b.y() + a.z() * b.z());
    }

    // ---------- Add ---------
    template <typename T>
    Vector3<T>	&Vector3<T>::operator+=(const Vector3<T> &ref)
    {
      _data[0] += ref.x();
      _data[1] += ref.y();
      _data[2] += ref.z();
      return (*this);
    }

    // ---------- Sub ----------
    template <typename T>
    Vector3<T>	&Vector3<T>::operator-=(const Vector3<T> &ref)
    {
      _data[0] -= ref.x();
      _data[1] -= ref.y();
      _data[2] -= ref.z();
      return (*this);
    }

    // ---------- Mult ----------
    template <typename T>
    Vector3<T>	&Vector3<T>::operator*=(const Vector3<T> &ref)
    {
      _data[0] *= ref.x();
      _data[1] *= ref.y();
      _data[2] *= ref.z();
      return (*this);
    }

    // ---------- Div ----------
    template <typename T>
    Vector3<T>	&Vector3<T>::operator/=(const Vector3<T> &ref)
    {
      _data[0] /= ref.x();
      _data[1] /= ref.y();
      _data[2] /= ref.z();
      return (*this);
    }

    // Stand alone
    template <typename T>
    Vector3<T>  operator*(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>  res(left);

      res *= right;
      return (res);
    }

    template <typename T>
    Vector3<T>  operator+(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>  res(left);

      res += right;
      return (res);
    }

    template <typename T>
    Vector3<T>	operator/(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>	res(left);

      res /= right;
      return (res);
    }

    template <typename T>
    Vector3<T>  operator-(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>  res(left);

      res -= right;
      return (res);
    }

    template <typename T>
    bool	operator==(const Vector3<T>& left, const Vector3<T>& right)
    {
      return (left.x() == right.x() && left.y() == right.y() && left.z() == right.z());
    }

    template <typename T>
    bool	operator!=(const Vector3<T>& left, const Vector3<T>& right)
    {
      return !(left == right);
    }

    template class Vector3 < int >;
    template class Vector3 < float >;
    template class Vector3 < double >;
    template class Vector3 < char >;
    template class Vector3 < unsigned int >;
    template class Vector3 < unsigned char >;

  } // namespace Tools
} // namespace RayOn