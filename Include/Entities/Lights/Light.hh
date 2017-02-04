#ifndef RTLight_H
#define RTLight_H

#include "include/Entities/Lights/RTLight.h"

template <class Derived>
class   Light : public RTLight
{
public:
    Light(const Color &color = 0xffffffff)
        : RTLight(color)
    {
    }

    Light(const Vec_t &pos,
          const Vec_t &rot,
          const Color &color = 0xffffffff)
        : RTLight(pos, rot, color)
    {
    }

    Light(Float_t x, Float_t y, Float_t z,
          const Color &color = 0xffffffff)
        : RTLight(x, y, z, color)
    {
    }

    virtual ~Light()
    {
    }

protected:
    void    preprocessImpl()
    {
    }

public:
    RTLight    *clone() const final
    {
        return (new Derived(static_cast<Derived const&>(*this)));
    }

    Color       apply(const Color &color,
                      const Scene &scene,
                      RTObject *obj,
                      const Vec_t &point) final
    {
        return (static_cast<Derived*>(this)->applyImpl(color, scene, obj, point));
    }

    void        preprocess() final
    {
        static_cast<Derived*>(this)->preprocessImpl();
    }

    const char  *name() const final
    {
        return (Derived::LightName);
    }
};

#endif // RTLight_H
