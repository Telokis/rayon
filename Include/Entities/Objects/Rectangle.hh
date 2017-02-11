#ifndef RAYON_RECTANGLE_HH_
#define RAYON_RECTANGLE_HH_

#include "Object.hh"

namespace RayOn
{

  class   Rectangle : public Object<Rectangle>
  {
    typedef Object<Rectangle> ParentType;
    friend  ParentType;

  public:
    Rectangle(Float_t width, Float_t height);
    Rectangle(const Vec_t& pos, const Vec_t& rot, Float_t width, Float_t height);
    Rectangle(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height);
    ~Rectangle();

  private:
    Vec_t   _norm;
    bool    _isOk;
    Float_t _halfW;
    Float_t _halfH;
    static const constexpr auto ObjectName = "Rectangle";

  private:
    bool  interImpl(const Ray& ray, IntersectionData& data) const;
    void  fillDataImpl(IntersectionData& data) const;
    void  preprocessImpl();

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Rectangle, Float_t, _width, Width)
    RAYON_GENERATE_PROPERTY_DECLARATION(Rectangle, Float_t, _height, Height)
  };

} // namespace RayOn

#endif // RAYON_RECTANGLE_HH_
