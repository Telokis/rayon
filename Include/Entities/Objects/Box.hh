#ifndef RAYON_BOX_HH_
#define RAYON_BOX_HH_

#include "Object.hh"

namespace RayOn
{

  class   Box : public Object<Box>
  {
    typedef Object<Box> ParentType;
    friend  ParentType;

  public:
    Box(Float_t width, Float_t height, Float_t depth);
    Box(const Vec_t& pos, const Vec_t& rot, Float_t width, Float_t height, Float_t depth);
    Box(Float_t x, Float_t y, Float_t z, Float_t width, Float_t height, Float_t depth);
    ~Box();

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  private:
    Vec_t   _norm[3];
    bool    _isOk;
    Vec_t   _min;
    Vec_t   _max;
    static const constexpr auto ObjectName = "Box";

  private:
    bool    interImpl(const Ray& ray, IntersectionData& data) const;
    void    fillDataImpl(IntersectionData& data) const;
    void    preprocessImpl();

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _width, Width)
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _height, Height)
    RAYON_GENERATE_PROPERTY_DECLARATION(Box, Float_t, _depth, Depth)
  };

} // namespace RayOn

#endif // RAYON_BOX_HH_
