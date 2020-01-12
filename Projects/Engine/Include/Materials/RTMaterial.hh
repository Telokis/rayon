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
    virtual ~RTMaterial();

  public:
    virtual void read(const YAML::Node& root)  = 0;
    virtual void write(YAML::Node& root) const = 0;

  public:
    bool testFlag(RayType type) const;

  public:
    Color   getColor(const IntersectionData& data) const;
    Float_t getReflexion(const IntersectionData& data) const;
    Float_t getTransparency(const IntersectionData& data) const;
    Float_t getRefraction(const IntersectionData& data) const;
    Float_t getGlossiness(const IntersectionData& data) const;
    Float_t getShininess(const IntersectionData& data) const;

  public:
    virtual Color   getColor(const IntersectionData& data, uint32 depth) const        = 0;
    virtual Float_t getReflexion(const IntersectionData& data, uint32 depth) const    = 0;
    virtual Float_t getTransparency(const IntersectionData& data, uint32 depth) const = 0;
    virtual Float_t getRefraction(const IntersectionData& data, uint32 depth) const   = 0;
    virtual Float_t getGlossiness(const IntersectionData& data, uint32 depth) const   = 0;
    virtual Float_t getShininess(const IntersectionData& data, uint32 depth) const    = 0;

  public:
    virtual void        preprocess()               = 0;
    virtual RTMaterial* clone() const              = 0;
    virtual bool        testFlag(Flags flag) const = 0;
    virtual const char* name() const               = 0;
  };
}  // namespace Rayon

#endif  // RAYON_RTMATERIAL_HH_
