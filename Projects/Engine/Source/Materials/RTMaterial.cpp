#include "Materials/RTMaterial.hh"

#include <yaml-cpp/yaml.h>

namespace Rayon
{
#define RAYON_DECLARE(flag) \
  {                         \
    Flags::flag, #flag      \
  }
  const std::map<Flags, std::string> RTMaterial::flagToStr{RAYON_DECLARE(NoShadow),
                                                           RAYON_DECLARE(NoImage),
                                                           RAYON_DECLARE(NoReflection),
                                                           RAYON_DECLARE(NoTransparency),
                                                           RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE
#define RAYON_DECLARE(flag) \
  {                         \
#flag, Flags::flag      \
  }
  const std::map<std::string, Flags> RTMaterial::strToFlag{RAYON_DECLARE(NoShadow),
                                                           RAYON_DECLARE(NoImage),
                                                           RAYON_DECLARE(NoReflection),
                                                           RAYON_DECLARE(NoTransparency),
                                                           RAYON_DECLARE(NoShading)};
#undef RAYON_DECLARE

  RTMaterial::~RTMaterial()
  {
  }

  bool RTMaterial::testFlag(RayType type) const
  {
    switch (type)
    {
      case RayType::Shadow:
        return testFlag(Flags::NoShadow);

      case RayType::Reflected:
        return testFlag(Flags::NoReflection);

      case RayType::Transparency:
        return testFlag(Flags::NoTransparency);

      case RayType::Primary:
        return testFlag(Flags::NoImage);
    }

    return false;
  }

  Color RTMaterial::getColor(const IntersectionData& data) const
  {
    return getColor(data, 0);
  }

  Float_t RTMaterial::getReflexion(const IntersectionData& data) const
  {
    return getReflexion(data, 0);
  }

  Float_t RTMaterial::getTransparency(const IntersectionData& data) const
  {
    return getTransparency(data, 0);
  }

  Float_t RTMaterial::getRefraction(const IntersectionData& data) const
  {
    return getRefraction(data, 0);
  }

  Float_t RTMaterial::getGlossiness(const IntersectionData& data) const
  {
    return getGlossiness(data, 0);
  }

  Float_t RTMaterial::getShininess(const IntersectionData& data) const
  {
    return getShininess(data, 0);
  }

}  // namespace Rayon
