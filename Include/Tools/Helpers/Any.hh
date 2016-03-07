#pragma once

#ifndef RAYON_TOOLS_ANY_HH_
#define RAYON_TOOLS_ANY_HH_

#include <memory>

namespace
{

  struct AnyValueParent
  {
    virtual AnyValueParent* clone() = 0;
    virtual ~AnyValueParent() {};
  };

  template <typename T>
  struct AnyValue : AnyValueParent
  {
    AnyValue(const T& val)
      : _data(std::make_unique<T>(val))
    {
    }

    AnyValueParent* clone()
    {
      return new AnyValue<T>(*_data);
    }

    std::unique_ptr<T>  _data;
  };

} // anonymous namespace

namespace RayOn
{
  namespace Tools
  {
    namespace Helpers
    {

      class Any
      {
        template <typename T>
        friend T   AnyCast(const Any& any);

        public:
          template <typename T>
          Any(const T& value)
            : _value(std::make_unique<AnyValue<T>>(value))
          {
          }

          template <typename T>
          Any&  operator=(const T& right)
          {
            _value.reset(new AnyValue<T>(right));
            return *this;
          }

          Any&  operator=(const Any& right)
          {
            _value.reset(right._value->clone());
            return *this;
          }

        private:
          std::unique_ptr<AnyValueParent>  _value;
      };

      template <typename T>
      T   AnyCast(const Any& any)
      {
        AnyValue<T>*  attempt = dynamic_cast<AnyValue<T>*>(any._value.get());
        if (!attempt)
          throw std::bad_cast();
        return *attempt->_data;
      }

    } // namespace Helpers
  } // namespace Tools
} // namespace RayOn

#endif // RAYON_TOOLS_ANY_HH_