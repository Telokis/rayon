#pragma once

#ifndef RAYON_RTMATERIAL_HH_
#define RAYON_RTMATERIAL_HH_

#include <yaml-cpp/node/node.h>

#include <map>

#include "Color.hh"
#include "Ray.hh"

namespace Rayon
{
  class Scene;
  class IntersectionData;
}  // namespace Rayon

namespace Rayon
{
  enum class Flags : size_t {
    NoShadow = 0,    ///< Object doesn't catch shadow rays.
    NoImage,         ///< Object doesn't catch camera rays.
    NoReflection,    ///< Object doesn't catch reflection rays.
    NoTransparency,  ///< Object doesn't catch transparency rays.
    NoShading,       ///< Object ignores diffuse lighting.

    COUNT
  };

  class RTMaterial
  {
  public:
    static const std::map<Flags, std::string> flagToStr;
    static const std::map<std::string, Flags> strToFlag;

  public:
    virtual ~RTMaterial() = 0;

  public:
    virtual void read(const YAML::Node& root)  = 0;
    virtual void write(YAML::Node& root) const = 0;

  public:
    bool testFlag(RayType type) const;

  public:
    virtual void        preprocess()                = 0;
    virtual RTMaterial* clone() const               = 0;
    virtual bool        testFlag(Flags flag) const  = 0;
    virtual Color       getColor(const Scene&            scene,
                                 const Ray&              ray,
                                 const IntersectionData& data,
                                 uint8                   depth) const = 0;
    virtual const char* name() const                = 0;
  };
}  // namespace Rayon

#endif  // RAYON_RTMATERIAL_HH_
