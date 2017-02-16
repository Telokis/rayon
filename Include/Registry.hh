#pragma once

#ifndef RAYON_REGISTRY_HH_
#define RAYON_REGISTRY_HH_

#include "ImageFileHandlers/IImageFileHandler.hh"
#include "MetaRTLights/IMetaRTLight.hh"
#include "MetaRTObjects/IMetaRTObject.hh"

#include <vector>
#include <memory>
#include <map>

namespace RayOn
{
  class Registry
  {
    using ImageFileHandlerType = std::unique_ptr<IImageFileHandler>;
    using ImageFileHandlerContainer = std::map<std::string, ImageFileHandlerType>;

    using MetaRTLightType = std::unique_ptr<IMetaRTLight>;
    using MetaRTLightContainer = std::map<std::string, MetaRTLightType>;

    using MetaRTObjectType = std::unique_ptr<IMetaRTObject>;
    using MetaRTObjectContainer = std::map<std::string, MetaRTObjectType>;

  public:
    Registry();
    ~Registry();

  public:
    bool  registerImageFileHandler(IImageFileHandler* handler);
    const IImageFileHandler*          getImageFileHandler(const std::string& id) const;
    const ImageFileHandlerContainer&  getImageFileHandlers() const;

  public:
    bool  registerMetaRTLight(IMetaRTLight* meta);
    const IMetaRTLight*         getMetaRTLight(const std::string& id) const;
    const MetaRTLightContainer& getMetaRTLights() const;

  public:
    bool  registerMetaRTObject(IMetaRTObject* meta);
    const IMetaRTObject*         getMetaRTObject(const std::string& id) const;
    const MetaRTObjectContainer& getMetaRTObjects() const;

  private:
    ImageFileHandlerContainer _imgHandlers;
    MetaRTLightContainer      _metaRTLights;
    MetaRTObjectContainer     _metaRTObjects;
  };

  inline Registry& registry()
  {
    static Registry reg;
    return reg;
  }
} // namespace RayOn

#endif // RAYON_REGISTRY_HH_