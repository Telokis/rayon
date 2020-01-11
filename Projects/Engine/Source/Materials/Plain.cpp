#include "Materials/Plain.hh"

#include <yaml-cpp/yaml.h>

#include "IntersectionData.hh"
#include "Scene.hh"
#include "SceneParse.hh"

namespace Rayon
{
  static constexpr const uint8 MAX_DEPTH  = 5;
  static constexpr const uint8 MAX_GLOSSY = 5;

  Plain::Plain()
    : _color(0xffff0000)
    , _reflexion(0)
    , _transparency(0)
    , _refraction(1)
    , _flags(0)
    , _glossiness(0)
    , _ambient(-1)
    , _shininess(0)
  {
  }

  void Plain::setFlag(Flags flag, bool value)
  {
    _flags.set(static_cast<size_t>(flag), value);
  }

  bool Plain::testFlagImpl(Flags flag) const
  {
    return _flags.test(static_cast<size_t>(flag));
  }

  void Plain::read(const YAML::Node& root)
  {
    if (root["flags"] && root["flags"].IsSequence())
    {
      _flags.reset();
      const YAML::Node& flags = root["flags"];

      for (const YAML::Node& flag : flags)
      {
        if (strToFlag.count(flag.as<std::string>()))
        {
          setFlag(strToFlag.at(flag.as<std::string>()));
        }
        else
        {
          std::cout << "[Warning] Ignoring unknown material flag `" << flag.as<std::string>()
                    << "`.\n";
        }
      }
    }

    readVal(root, "color", _color, 0xffff0000);
    readVal(root, "reflexion", _reflexion, 0);
    readVal(root, "ambient", _ambient, -1);
    readVal(root, "glossiness", _glossiness, 0);
    readVal(root, "refraction", _refraction, 1);
    readVal(root, "transparency", _transparency, 0);
    readVal(root, "shininess", _shininess, 0);
  }

  void Plain::write(YAML::Node& root) const
  {
    if (!_flags.none())
    {
      YAML::Node& flags = root["flags"];

      for (const auto& pair : flagToStr)
        if (testFlag(pair.first))
          flags.push_back(pair.second);
    }

    writeVal(root, "color", _color, 0xffff0000);
    writeVal(root, "reflexion", _reflexion, 0);
    writeVal(root, "ambient", _ambient, -1);
    writeVal(root, "glossiness", _glossiness, 0);
    writeVal(root, "refraction", _refraction, 1);
    writeVal(root, "transparency", _transparency, 0);
    writeVal(root, "shininess", _shininess, 0);
  }

  Color Plain::handleReflection(const Scene&            scene,
                                const Ray&              ray,
                                const IntersectionData& data,
                                uint8                   depth) const
  {
    Ray reflected(RayType::Reflected, data.point, Tools::Reflect(ray.getDirection(), data.normal));

    if (_glossiness > Globals::Epsilon)
    {
      Color   color;
      Float_t g            = _glossiness;
      Vec_t   reflectedDir = reflected.getDirection();

      for (auto i = 0u; i < MAX_GLOSSY; ++i)
      {
        Vec_t tmp(((rand() % 100) - 50.0) / (100.0 * g),
                  1.0 * ((rand() % 100) - 50.0) / (100.0 * g),
                  ((rand() % 100) - 50.0) / (100.0 * g));
        reflected.setDirection(reflectedDir + tmp);
        reflected.normalize();
        reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
        color += scene.inter(reflected, depth + 1, data.stat);
      }

      return color * (Float_t(1.0) / MAX_GLOSSY);
    }

    reflected.setOrigin(data.point + Globals::Epsilon * reflected.getDirection());
    return scene.inter(reflected, depth + 1, data.stat);
  }

  Color Plain::handleTransparency(const Scene&            scene,
                                  const Ray&              ray,
                                  const IntersectionData& data,
                                  uint8                   depth) const
  {
    Ray     refracted(RayType::Transparency, data.point, ray.getDirection());
    Float_t eta = _refraction;

    if (eta != 1 && eta > Globals::Epsilon)
      refracted.setDirection(Tools::Refract(ray.getDirection(), data, eta));

    refracted.setOrigin(data.point + Globals::Epsilon * refracted.getDirection());

    return scene.inter(refracted, depth + 1, data.stat);
  }

  // http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
  Float_t Plain::getFresnelReflectance(const IntersectionData& data, const Ray& ray) const
  {
    Float_t n1 = _refraction;
    Float_t n2 = 1.0;

    Float_t cosI = -Tools::DotProduct(ray.getDirection(), data.normal);
    if (cosI > Globals::Epsilon)
    {
      n2 = n1;
      n1 = 1.0;
    }
    else
      cosI *= -1;

    Float_t n     = n1 / n2;
    Float_t sin2T = n * n * (Float_t(1.0) - cosI * cosI);

    if (sin2T > 1.0)
      return 1.0;

    using std::sqrt;
    Float_t cosT = sqrt(1.0 - sin2T);
    Float_t rPer = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
    Float_t rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);

    return (rPer * rPer + rPar * rPar) * Float_t(0.5);
  }

  Color Plain::handleReflectionAndRefraction(const Scene&            scene,
                                             const Ray&              ray,
                                             const IntersectionData& data,
                                             uint8                   depth) const
  {
    bool hasReflexion    = _reflexion > Globals::Epsilon;
    bool hasTransparency = _transparency > Globals::Epsilon;

    if (!(hasReflexion || hasTransparency) || depth >= MAX_DEPTH)
      return 0;

    Float_t reflectance   = _reflexion;
    Float_t transmittance = _transparency;

    Color reflexion;
    Color transparency;

    if (hasReflexion && hasTransparency)
    {
      reflectance   = getFresnelReflectance(data, ray);
      transmittance = 1.0 - reflectance;
    }

    if (hasReflexion && reflectance > Globals::Epsilon)
      reflexion = handleReflection(scene, ray, data, depth) * reflectance;

    if (hasTransparency && transmittance > Globals::Epsilon)
      transparency = handleTransparency(scene, ray, data, depth) * transmittance;

    return reflexion + transparency;
  }

  Color Plain::getColorImpl(const Scene&            scene,
                            const Ray&              ray,
                            const IntersectionData& data,
                            uint8                   depth) const
  {
    Color ambient = _color * scene.getAmbient();
    Color lighting;
    Color specular;

    if (_ambient > -Globals::Epsilon)
    {
      ambient = _color * _ambient;
    }

    if (!testFlag(Flags::NoShading))
    {
      lighting = scene.processLights(data, specular);
    }

    Color   reflectionRefraction = handleReflectionAndRefraction(scene, ray, data, depth);
    Float_t coef                 = Tools::Max(_transparency, _reflexion);

    return specular + (ambient + lighting) * (1.0 - coef) + reflectionRefraction * coef;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Color, _color, Color);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _reflexion, Reflexion);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _transparency, Transparency);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _refraction, Refraction);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _glossiness, Glossiness);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _ambient, Ambient);
  RAYON_GENERATE_PROPERTY_DEFINITION(Plain, Float_t, _shininess, Shininess);
}  // namespace Rayon
