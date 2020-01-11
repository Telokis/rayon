#include "Materials/RTMaterial.hh"

#include <yaml-cpp/yaml.h>

#include "IntersectionData.hh"
#include "Scene.hh"
#include "SceneParse.hh"

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
}  // namespace Rayon
