#ifndef RAYON_PLANE_HH_
#define RAYON_PLANE_HH_

#include "Object.hh"

namespace RayOn
{

  class   Plane : public Object<Plane>
  {
    typedef Object<Plane> ParentType;
    friend  ParentType;

  public:
    Plane();
    Plane(const Vec_t& pos, const Vec_t& rot);
    Plane(Float_t x, Float_t y, Float_t z);
    ~Plane();

  private:
    Vec_t              _norm;
    static const constexpr auto ObjectName = "Plane";

  private:
    bool  interImpl(const Ray& ray, IntersectionData& data) const;
    void  fillDataImpl(IntersectionData& data) const;
    void  preprocessImpl();
  };

} // namespace RayOn

#endif // RAYON_PLANE_HH_
