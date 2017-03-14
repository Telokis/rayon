#ifndef RAYON_SPHERE_HH_
#define RAYON_SPHERE_HH_

#include "Shape.hh"

namespace Rayon
{
  class   Sphere : public Shape<Sphere>
  {
    using ParentType = Shape<Sphere>;
    friend  ParentType;

  public:
    explicit Sphere(Float_t radius = 1.0);
    Sphere(const Vec_t& pos, const Vec_t& rot, Float_t radius);
    Sphere(Float_t x, Float_t y, Float_t z, Float_t radius);
    ~Sphere();

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  public:
    static constexpr const auto ShapeName = "Sphere";

  private:
    bool  interImpl(const Ray& ray, IntersectionData& data) const;
    void  fillDataImpl(IntersectionData& data) const;

    RAYON_GENERATE_PROPERTY_DECLARATION(Sphere, Float_t, _radius, Radius)
  };
} // namespace Rayon

#endif // RAYON_SPHERE_HH_
