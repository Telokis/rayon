#include "Entities/Lights/RTLight.hh"
#include "SceneParse.hh"
#include "Scene.hh"

#include <Json.h>

namespace RayOn
{
  RTLight::RTLight(const Color &color)
    : _color(color)
  {
  }

  RTLight::RTLight(const Vec_t &pos,
                   const Vec_t &rot,
                   const Color &color)
    : Entity(pos, rot), _color(color)
  {
  }

  RTLight::RTLight(Float_t x, Float_t y, Float_t z,
                   const Color &color)
    : Entity(x, y, z), _color(color)
  {
  }

  RTLight::~RTLight()
  {
  }

  bool    RTLight::doesShadow(const Vec_t& pos,
                              const Scene& scene,
                              const Vec_t& point,
                              RTObject* obj) const
  {
    Vec_t   light_vec(pos - point);
    Vec_t   tmp_pos(point + light_vec * Globals::Epsilon);
    IntersectionData  data;

    data.k = Globals::Invalid;
    Ray shadowRay(RayType::Shadow, tmp_pos, light_vec);

    for (const auto& object : scene.objects())
    {
      if (obj != object && object->inter(shadowRay, data) && data.k < 1.0)
        return true;
    }
    return false;
  }

  Color    RTLight::getSpecular(const Vec_t& lightVec,
                                const Scene& scene,
                                const Color& lightColor,
                                const IntersectionData& data) const
  {
    Vec_t   refLight = Tools::Reflect(lightVec, data.normal);
    Float_t dot = Tools::DotProduct(data.ray->getDirection(), refLight);

    if (dot > Globals::Epsilon)
      return lightColor * Tools::Pow<15>(dot) * data.material->getShininess();
    return 0;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(RTLight, Color, _color, Color)

  void RTLight::read(const Json::Value& root)
  {
    Entity::read(root);
    readVal(root, "color", _color, 0xffffffff);
  }

  void RTLight::write(Json::Value& root) const
  {
    Entity::write(root);
    writeVal(root, "color", _color, 0xffffffff);
  }

} // namespace RayOn