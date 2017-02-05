#ifndef RAYON_RTOBJECT_HH_
#define RAYON_RTOBJECT_HH_

#include "Entities/Entity.hh"
#include "Tools/Color.hh"
#include "Tools/Ray.hh"

namespace RayOn
{
  class   RTObject : public Entity
  {
  public:
    RTObject();
    RTObject(const Vec_t &pos,
             const Vec_t &rot);
    RTObject(Float_t x, Float_t y, Float_t z);
    virtual ~RTObject();

  public:
    virtual Float_t     inter(const Ray &ray) = 0;
    virtual void        preprocess() = 0;
    virtual RTObject*   clone() const = 0;
    virtual Vec_t       norm(const Vec_t &point) = 0;
    virtual const char* name() const = 0;

    RAYON_GENERATE_PROPERTY_DECLARATION(RTObject, Color, _color, Color)
    RAYON_GENERATE_PROPERTY_DECLARATION(RTObject, double, _reflexion, Reflexion)
  };
} // namespace RayOn

#endif // RAYON_RTOBJECT_HH_
