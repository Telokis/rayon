#ifndef RAYON_RECTANGLE_HH_
#define RAYON_RECTANGLE_HH_

#include "Shape.hh"

namespace Rayon
{
  class Rectangle : public Shape<Rectangle>
  {
    typedef Shape<Rectangle> ParentType;
    friend ParentType;

  public:
    Rectangle(Float_t width = 1.0, Float_t height = 1.0);
    Rectangle(const Vec_t& pos, const Vec_t& rot, Float_t width, Float_t height);
    Rectangle(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height);
    ~Rectangle();

  public:
    void read(const Json::Value& root) override;
    void write(Json::Value& root) const override;

  private:
    Vec_t   _norm;
    bool    _isOk;
    Float_t _halfW;
    Float_t _halfH;

  public:
    static const constexpr auto ShapeName = "Rectangle";

  private:
    bool        interImpl(const Ray& ray, IntersectionData& data) const;
    void        fillDataImpl(IntersectionData& data) const;
    void        preprocessImpl();
    BoundingBox getBBoxImpl() const;

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Rectangle, Float_t, _width, Width)
    RAYON_GENERATE_PROPERTY_DECLARATION(Rectangle, Float_t, _height, Height)
  };

}  // namespace Rayon

#endif  // RAYON_RECTANGLE_HH_
