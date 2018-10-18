#ifndef RAYON_LIGHT_HH_
#define RAYON_LIGHT_HH_

#include "Entities/Lights/RTLight.hh"

namespace Rayon
{
  template <class Derived>
  class Light : public RTLight
  {
  public:
    Light(const Color& color = 0xffffffff) : RTLight(color)
    {
    }

    Light(const Vec_t& pos, const Vec_t& rot, const Color& color = 0xffffffff)
      : RTLight(pos, rot, color)
    {
    }

    Light(Float_t x, Float_t y, Float_t z, const Color& color = 0xffffffff)
      : RTLight(x, y, z, color)
    {
    }

    virtual ~Light()
    {
    }

  protected:
    void preprocessImpl()
    {
    }

  public:
    RTLight* clone() const final
    {
      return new Derived(static_cast<Derived const&>(*this));
    }

    Color apply(const Color&            color,
                const Scene&            scene,
                const IntersectionData& data,
                Color&                  specular) const final
    {
      return static_cast<Derived const*>(this)->applyImpl(
        color, scene, data, specular);
    }

    void preprocess() final
    {
      static_cast<Derived*>(this)->preprocessImpl();
    }

    const char* name() const final
    {
      return Derived::LightName;
    }
  };
}  // namespace Rayon

#endif  // RAYON_LIGHT_HH_
