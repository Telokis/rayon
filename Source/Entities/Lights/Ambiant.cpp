#include "Entities/Lights/Ambiant.hh"

const char   *Ambiant::LightName = "Ambiante";

Ambiant::Ambiant()
    : _power(0.5)
{
}

Ambiant::~Ambiant()
{
}

Color       Ambiant::applyImpl(const Color &color,
                               const Scene &,
                               RTObject *,
                               const Vec_t &) const
{
    return (Color::interpolate(0, color & getColor(), _power));
}

void    Ambiant::serialize(QDomElement &node) const
{
    ParentType::serialize(node);
    node.setAttribute("Power", _power);
}

RT_GENERATE_PROPERTY_DEFINITION(Ambiant, Float_t, _power, Power)
