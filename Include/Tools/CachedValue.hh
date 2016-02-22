#pragma once

#ifndef RAYON_TOOLS_CACHEDVALUE_HH_
#define RAYON_TOOLS_CACHEDVALUE_HH_

namespace RayOn
{
  namespace Tools
  {
    template<typename T>
    class CachedValue
    {
    public:
      CachedValue();
      CachedValue(const T& value, bool valid = false);

      void  set(const T& value);
      void  invalidate() const;

      CachedValue&  operator=(const T& value);
      const T       operator()() const;
      T&            operator()();

    private:
      T             _value;
      bool mutable  _valid;
    };


    // CachedValue implementation below :
    template<typename T>
    CachedValue::CachedValue()
      : _value(),
      _valid(false)
    {
    }

    template<typename T>
    CachedValue::CachedValue(const T& value, bool valid)
      : _value(value),
      _valid(valid)
    {
    }

    template<typename T>
    void  CachedValue::set(const T& value)
    {
      _value = value;
      _valid = true;
    }

    template<typename T>
    void  CachedValue::invalidate() const
    {
      _valid = false;
    }

    template<typename T>
    CachedValue&  CachedValue::operator=(const T& value)
    {
      set(value);
      return *this;
    }

    template<typename T>
    const T CachedValue::operator()() const
    {
      return _value;
    }

    template<typename T>
    T&      CachedValue::operator()()
    {
      return _value;
    }
  }
}

#endif // RAYON_TOOLS_CACHEDVALUE_HH_