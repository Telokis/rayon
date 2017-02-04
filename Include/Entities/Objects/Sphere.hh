#ifndef RAYON_SPHERE_HH_
#define RAYON_SPHERE_HH_

#include "Object.hh"

namespace RayOn
{
  class   Sphere : public Object<Sphere>
  {
    using ParentType = Object<Sphere>;
    friend  ParentType;

  public:
    explicit Sphere(Float_t radius);
    Sphere(const Vec_t &pos, const Vec_t &rot, Float_t radius);
    Sphere(Float_t x, Float_t y, Float_t z, Float_t radius);
    ~Sphere();

  private:
    static constexpr const auto ObjectName = "Sphere";

  private:
    Float_t  interImpl(const Vec_t &origin,
                       const Vec_t &direction) const;
    Vec_t  normImpl(const Vec_t &point) const;

    RAYON_GENERATE_PROPERTY_DECLARATION(Sphere, Float_t, _radius, Radius)
  };
} // namespace RayOn

#endif // RAYON_SPHERE_HH_
