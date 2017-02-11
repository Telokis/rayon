#ifndef RAYON_OBJECT_HH_
#define RAYON_OBJECT_HH_

#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  template <class Derived>
  class   Object : public RTObject
  {
  public:
    Object()
    {
    }

    Object(const Vec_t &pos,
           const Vec_t &rot)
      : RTObject(pos, rot)
    {
    }

    Object(Float_t x, Float_t y, Float_t z)
      : RTObject(x, y, z)
    {
    }

    virtual ~Object()
    {
    }

  protected:
    void    preprocessImpl()
    {
    }

  public:
    RTObject*   clone() const final
    {
      return new Derived(static_cast<Derived const&>(*this));
    }

    bool  inter(const Ray &ray, IntersectionData& data) const final
    {
      if (getMaterial().testFlag(ray.getType()))
        return Globals::Invalid;
      return static_cast<Derived const*>(this)->interImpl(ray, data);
    }

    void        fillData(IntersectionData& data) const final
    {
      return static_cast<Derived const*>(this)->fillDataImpl(data);
    }

    const char* name() const final
    {
      return Derived::ObjectName;
    }

    void        preprocess() final
    {
      static_cast<Derived*>(this)->preprocessImpl();
    }
  };

} // namespace RayOn

#endif // RTOBJECT_H
