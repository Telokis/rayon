#ifndef RAYON_TRIANGLE_HH_
#define RAYON_TRIANGLE_HH_

#include <array>

#include "Shape.hh"

namespace Rayon
{
  class Triangle : public Shape<Triangle>
  {
    typedef Shape<Triangle> ParentType;
    friend ParentType;

  public:
    Triangle() = default;
    Triangle(Vec_t v1, Vec_t v2, Vec_t v3);
    ~Triangle() = default;

  public:
    void read(const Json::Value& root) override;
    void write(Json::Value& root) const override;

  private:
    std::array<Vec_t, 3> _v;
    Vec_t                _v0v1;
    Vec_t                _v0v2;
    Vec_t                _norm;

  public:
    static const constexpr auto ShapeName = "Triangle";

  private:
    bool        interImpl(const Ray& ray, IntersectionData& data) const;
    void        fillDataImpl(IntersectionData& data) const;
    void        preprocessImpl();
    BoundingBox getBBoxImpl() const;
  };

}  // namespace Rayon

#endif  // RAYON_TRIANGLE_HH_
