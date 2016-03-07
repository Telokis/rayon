#pragma once

#ifndef RAYON_TOOLS_VECTOR3_HH
#define RAYON_TOOLS_VECTOR3_HH

#include <array>

namespace RayOn
{
  namespace Tools
  {
    template <typename T>
    class		    Vector3
    {
    public:
      Vector3();
      Vector3(T _x, T _y, T _z);
      Vector3(T a);

      ~Vector3();

      Vector3(const Vector3 &ref) = default;
      Vector3	    &operator=(const Vector3 &ref) = default;

      Vector3(Vector3 &&ref);
      Vector3	    &operator=(Vector3 &&ref);

    public:
      // Add
      Vector3	    &operator+=(const Vector3 &ref);

      // Sub
      Vector3	    &operator-=(const Vector3 &ref);

      // Mult
      Vector3	    &operator*=(const Vector3 &ref);

      // Div
      Vector3	    &operator/=(const Vector3 &ref);

    public:
      inline T&            x()
      {
        return _data[0];
      }

      inline T&            y()
      {
        return _data[1];
      }

      inline T&            z()
      {
        return _data[2];
      }

      inline const T       x() const
      {
        return _data[0];
      }

      inline const T       y() const
      {
        return _data[1];
      }

      inline const T       z() const
      {
        return _data[2];
      }

    public:
      void	        normalize();
      Vector3	    normalized() const;

    public:
      constexpr static T      dotProduct(const Vector3 &a, const Vector3 &b);

    public:
      std::array<T, 3>  _data;
    }; // Vector3

    template<typename T>
    const Vector3<T>     operator+(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    const Vector3<T>     operator-(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    const Vector3<T>     operator*(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    const Vector3<T>     operator/(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    bool          operator==(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    bool          operator!=(const Vector3<T>& left, const Vector3<T>& right);

    // Useful typedefs for easier use
    typedef	Vector3<float>          	Vec3;
    typedef	Vector3<float>	            fVec3;
    typedef	Vector3<int>	            iVec3;
    typedef	Vector3<double>	            dVec3;
    typedef	Vector3<char>	            cVec3;
    typedef	Vector3<unsigned int>		uiVec3;
    typedef	Vector3<unsigned char>		ucVec3;

    // Definitions
    template <typename T>
    Vector3<T>::Vector3()
    {
      _data.fill(T());
    }

    template <typename T>
    Vector3<T>::Vector3(T _x, T _y, T _z)
      : _data{{_x, _y, _z}}
    {
    }

    template <typename T>
    Vector3<T>::Vector3(T a)
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
    const Vector3<T>  operator*(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>  res(left);

      res *= right;
      return (res);
    }

    template <typename T>
    const Vector3<T>  operator+(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>  res(left);

      res += right;
      return (res);
    }

    template <typename T>
    const Vector3<T>	operator/(const Vector3<T>& left, const Vector3<T>& right)
    {
      Vector3<T>	res(left);

      res /= right;
      return (res);
    }

    template <typename T>
    const Vector3<T>  operator-(const Vector3<T>& left, const Vector3<T>& right)
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

  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_VECTOR3_HH
