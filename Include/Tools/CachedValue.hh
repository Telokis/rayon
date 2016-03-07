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

      bool          isValid() const;

    private:
      T             _value;
      bool mutable  _valid;
    };


    // CachedValue implementation below :
    template<typename T>
    CachedValue<T>::CachedValue()
      : _value(),
      _valid(false)
    {
    }

    template<typename T>
    CachedValue<T>::CachedValue(const T& value, bool valid)
      : _value(value),
      _valid(valid)
    {
    }

    template<typename T>
    void  CachedValue<T>::set(const T& value)
    {
      _value = value;
      _valid = true;
    }

    template<typename T>
    void  CachedValue<T>::invalidate() const
    {
      _valid = false;
    }

    template<typename T>
    bool  CachedValue<T>::isValid() const
    {
      return _valid;
    }

    template<typename T>
    CachedValue<T>&  CachedValue<T>::operator=(const T& value)
    {
      set(value);
      return *this;
    }

    template<typename T>
    const T CachedValue<T>::operator()() const
    {
      return _value;
    }

    template<typename T>
    T&      CachedValue<T>::operator()()
    {
      return _value;
    }
  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_CACHEDVALUE_HH_