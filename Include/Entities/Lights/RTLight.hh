#ifndef RAYON_RTLIGHT_HH_
#define RAYON_RTLIGHT_HH_

#include "Entities/Entity.hh"
#include "Color.hh"
#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  class Scene;
} // namespace RayOn

namespace RayOn
{
  class   RTLight : public Entity
  {
  public:
    explicit RTLight(const Color &color = 0xffffffff);
    RTLight(const Vec_t &pos,
            const Vec_t &rot,
            const Color &color = 0xffffffff);
    RTLight(Float_t x, Float_t y, Float_t z,
            const Color &color = 0xffffffff);
    virtual ~RTLight();

  public:
    virtual void        preprocess() = 0;
    virtual RTLight     *clone() const = 0;
    virtual Color       apply(const Color& color,
                              const Scene& scene,
                              RTObject* obj,
                              const Vec_t& point) = 0;
    virtual const char* name() const = 0;

    RAYON_GENERATE_PROPERTY_DECLARATION(RTLight, Color, _color, Color)
  };
} // namespace RayOn

#endif // RAYON_RTLIGHT_HH_
