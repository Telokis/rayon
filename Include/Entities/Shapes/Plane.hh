#ifndef RAYON_PLANE_HH_
#define RAYON_PLANE_HH_

#include "Shape.hh"

namespace Rayon
{

  class   Plane : public Shape<Plane>
  {
    typedef Shape<Plane> ParentType;
    friend  ParentType;

  public:
    Plane();
    Plane(const Vec_t& pos, const Vec_t& rot);
    Plane(Float_t x, Float_t y, Float_t z);
    ~Plane();

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  private:
    Vec_t              _norm;

  public:
    static const constexpr auto ShapeName = "Plane";

  private:
    bool  interImpl(const Ray& ray, IntersectionData& data) const;
    void  fillDataImpl(IntersectionData& data) const;
    void  preprocessImpl();
  };

} // namespace Rayon

#endif // RAYON_PLANE_HH_
