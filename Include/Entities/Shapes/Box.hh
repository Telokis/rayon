#ifndef RAYON_BOX_HH_
#define RAYON_BOX_HH_

#include "Shape.hh"

namespace Rayon
{
  class Box : public Shape<Box>
  {
    typedef Shape<Box> ParentType;
    friend ParentType;

  public:
    Box(Float_t width = 1.0, Float_t height = 1.0, Float_t depth = 1.0);
    Box(const Vec_t& pos, const Vec_t& rot, Float_t width, Float_t height, Float_t depth);
    Box(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height, Float_t depth);
    ~Box();

  public:
    void read(const Json::Value& root) override;
    void write(Json::Value& root) const override;

  private:
    Vec_t _norm[3];
    bool  _isOk;
    Vec_t _min;
    Vec_t _max;

  public:
    static const constexpr auto ShapeName = "Box";

  private:
    bool        interImpl(const Ray& ray, IntersectionData& data) const;
    void        fillDataImpl(IntersectionData& data) const;
    void        preprocessImpl();
    BoundingBox getBBoxImpl() const;

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _width, Width)
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _height, Height)
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _depth, Depth)
  };

}  // namespace Rayon

#endif  // RAYON_BOX_HH_
