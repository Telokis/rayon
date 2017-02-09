#pragma once

#ifndef RAYON_RAY_HH_
#define RAYON_RAY_HH_

#include "Tools/Helpers.hh"
#include "CachedValue.hh"

namespace RayOn
{
  enum class RayType : size_t
  {
    Shadow,
    Primary,
    Reflected,
    Transparency
  };

  class Ray
  {
  public:
    inline Ray()
    {
    }

    inline Ray(const Ray& obj)
      : _origin(obj._origin)
      , _direction(obj._direction)
      , _type(obj._type)
    {
    }

    inline Ray(RayType type, const Vec_t& origin, const Vec_t& direction)
      : _origin(origin)
      , _direction(direction)
      , _type(type)
    {
    }

    inline void set(RayType type, const Vec_t& origin, const Vec_t& direction)
    {
      _origin = origin;
      _direction = direction;
      _type = type;
      _invDirection.invalidate();
    }

    inline Vec_t evaluate(Float_t depth) const
    {
      return _origin + _direction * depth;
    }

    inline const Vec_t& getOrigin() const
    {
      return _origin;
    }

    inline const Vec_t& getDirection() const
    {
      return _direction;
    }

    inline void setOrigin(const Vec_t& v)
    {
      _origin = v;
    }

    inline void setDirection(const Vec_t& v)
    {
      _direction = v;
      _invDirection.invalidate();
    }

    inline void setType(RayType type)
    {
      _type = type;
    }

    inline void normalize()
    {
      _direction = Tools::Normalize(_direction);
      _invDirection.invalidate();
    }

    inline const Vec_t& getInvDirection() const
    {
      if (!_invDirection.isValid())
        _invDirection = Float_t(1.0) / _direction;
      return _invDirection();
    }

    inline RayType getType() const
    {
      return _type;
    }

  private:
    Vec_t   _origin;
    Vec_t   _direction;
    RayType _type;
    mutable CachedValue<Vec_t>  _invDirection;
  };
} // namespace RayOn

#endif // RAYON_RAY_HH_