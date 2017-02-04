#include "Entities/Lights/Sun.h"

const char   *Sun::LightName = "Soleil";

Sun::Sun()
    : _power(0.5)
{
}

Sun::Sun(const Vec_t &pos)
    : ParentType(pos, Vec_t(0, 0, 0)),
      _power(0.5)
{
}

Sun::Sun(Float_t x, Float_t y, Float_t z)
    : ParentType(x, y, z),
      _power(0.5)
{
}

Sun::~Sun()
{
}

bool    Sun::doesShadow(const Scene &scene,
                        const Vec_t &point) const
{
    double  k;
    Vec_t  light_vec;
    Vec_t  tmp_pos;

    k = RT_INVALID;
    light_vec = _pos - point;
    tmp_pos = point + light_vec * 0.001f;
    for (const auto& object : scene.objects())
    {
        k = object->inter(tmp_pos, light_vec);
        if (k > RT_ZERO_VAL && k < 1.0)
            return (true);
    }
    return (false);
}

Color       Sun::applyImpl(const Color &color,
                           const Scene &scene,
                           RTObject *obj,
                           const Vec_t &point) const
{
    double  cos_a;
    Vec_t  light_vec;
    Color   res;

    if (doesShadow(scene, point))
        return (0);
    cos_a = 0;
    light_vec = getPos() - point;
    light_vec.normalize();
    cos_a = Vec_t::dotProduct(light_vec, obj->norm(point));
    if (cos_a < RT_ZERO_VAL)
        return (0xFF000000);
    res = color * cos_a;
    return (Color::interpolate(res, getColor(), cos_a * _power));
}

void    Sun::serialize(QDomElement &node) const
{
    ParentType::serialize(node);
    node.setAttribute("Power", _power);
}

RT_GENERATE_PROPERTY_DEFINITION(Sun, Float_t, _power, Power)
