#ifndef RAYON_OBJECT_HH_
#define RAYON_OBJECT_HH_

#include "Entities/Shapes/RTShape.hh"

namespace Rayon
{
  template <class Derived>
  class   Shape : public RTShape
  {
  public:
    Shape()
    {
    }

    Shape(const Vec_t &pos,
           const Vec_t &rot)
      : RTShape(pos, rot)
    {
    }

    Shape(Float_t x, Float_t y, Float_t z)
      : RTShape(x, y, z)
    {
    }

    virtual ~Shape()
    {
    }

  protected:
    void    preprocessImpl()
    {
    }

  public:
    RTShape*   clone() const final
    {
      return new Derived(static_cast<Derived const&>(*this));
    }

    bool  inter(const Ray &ray, IntersectionData& data) const final
    {
      return static_cast<Derived const*>(this)->interImpl(ray, data);
    }

    void        fillData(IntersectionData& data) const final
    {
      return static_cast<Derived const*>(this)->fillDataImpl(data);
    }

    const char* name() const final
    {
      return Derived::ShapeName;
    }

    void        preprocess() final
    {
      static_cast<Derived*>(this)->preprocessImpl();
    }
  };

} // namespace Rayon

#endif // RTOBJECT_H
