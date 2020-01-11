#include "Entities/Lights/RTLight.hh"

#include <yaml-cpp/yaml.h>

#include "Object.hh"
#include "Scene.hh"
#include "SceneParse.hh"
#include "Tools/Stat.hh"

namespace Rayon
{
  RTLight::RTLight(const Color& color) : _color(color)
  {
  }

  RTLight::RTLight(const Vec_t& pos, const Vec_t& rot, const Color& color)
    : Entity(pos, rot), _color(color)
  {
  }

  RTLight::RTLight(Float_t x, Float_t y, Float_t z, const Color& color)
    : Entity(x, y, z), _color(color)
  {
  }

  RTLight::~RTLight()
  {
  }

  Float_t RTLight::shadowCoef(const Vec_t& pos,
                              const Scene& scene,
                              const Vec_t& point,
                              RTShape*     obj,
                              Tools::Stat* stat) const
  {
    Vec_t            light_vec(pos - point);
    Vec_t            tmp_pos(point + light_vec * Globals::Epsilon);
    IntersectionData data;
    Float_t          coef = 1.0;

    data.stat = stat;
    Ray shadowRay(RayType::Shadow, tmp_pos, light_vec);

    stat->rayCounts[RayType::Shadow] += 1;

    scene.iterateIfIntersect(
      shadowRay, data, [obj, &coef](const Object* object, IntersectionData& data) {
        if (obj != object->getShape())
        {
          if (data.k < 1.0)
          {
            data.stat->hits += 1;
            coef *= object->getMaterial()->getPlain()->getTransparency();
          }
        }

        return !Tools::IsZero(coef);
      });

    return coef;
  }

  Color RTLight::getSpecular(const Vec_t&            lightVec,
                             const Scene&            scene,
                             const Color&            lightColor,
                             const IntersectionData& data) const
  {
    if (data.obj->getMaterial()->getPlain()->getShininess() < Globals::Epsilon)
      return 0;

    Vec_t   refLight = Tools::Reflect(lightVec, data.normal);
    Float_t dot      = Tools::DotProduct(data.ray->getDirection(), refLight);

    if (dot > Globals::Epsilon)
      return lightColor * std::pow(dot, data.obj->getMaterial()->getPlain()->getShininess());
    return 0;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(RTLight, Color, _color, Color);

  void RTLight::read(const YAML::Node& root)
  {
    Entity::read(root);
    readVal(root, "color", _color, 0xffffffff);
  }

  void RTLight::write(YAML::Node& root) const
  {
    Entity::write(root);
    writeVal(root, "color", _color, 0xffffffff);
  }

}  // namespace Rayon