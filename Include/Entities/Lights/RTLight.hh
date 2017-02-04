#ifndef RTLight_h
#define RTLight_h

#include "Entities/Entity.h"
#include "Scene.h"
#include "Tools/Color.h"

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

    virtual void    serialize(QDomElement &node) const Q_DECL_OVERRIDE;

public:
    virtual void        preprocess() = 0;
    virtual RTLight     *clone() const = 0;
    virtual Color       apply(const Color &color,
                              const Scene &scene,
                              RTObject *obj,
                              const Vec_t &point) = 0;
    virtual const char  *name() const = 0;

    RT_GENERATE_PROPERTY_DECLARATION(RTLight, Color, _color, Color)
};

#endif // RTLight_h
