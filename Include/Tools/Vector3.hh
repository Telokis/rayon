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
      constexpr Vector3();
      constexpr Vector3(T _x, T _y, T _z);
      constexpr Vector3(T a);

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
      Vector3	      normalized() const;

    public:
      constexpr static T      dotProduct(const Vector3 &a, const Vector3 &b);

    public:
      std::array<T, 3>  _data;
    }; // Vector3

    template<typename T>
    Vector3<T>     operator+(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    Vector3<T>     operator-(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    Vector3<T>     operator*(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    Vector3<T>     operator/(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    bool          operator==(const Vector3<T>& left, const Vector3<T>& right);

    template<typename T>
    bool          operator!=(const Vector3<T>& left, const Vector3<T>& right);

    // Useful typedefs for easier use
    typedef	Vector3<float>          	vec3;
    typedef	Vector3<float>	            fvec3;
    typedef	Vector3<int>	            ivec3;
    typedef	Vector3<double>	            dvec3;
    typedef	Vector3<char>	            cvec3;
    typedef	Vector3<unsigned int>		uivec3;
    typedef	Vector3<unsigned char>		ucvec3;

  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_VECTOR3_HH
