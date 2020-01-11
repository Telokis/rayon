#pragma once

#ifndef RAYON_REGISTRY_HH_
#define RAYON_REGISTRY_HH_

#include <map>
#include <memory>
#include <vector>

#include "ImageFileHandlers/IImageFileHandler.hh"
#include "MetaMaterials/IMetaRTMaterial.hh"
#include "MetaRTLights/IMetaRTLight.hh"
#include "MetaRTShapes/IMetaRTShape.hh"

namespace Rayon
{
  class Registry
  {
    using ImageFileHandlerType      = std::unique_ptr<IImageFileHandler>;
    using ImageFileHandlerContainer = std::map<std::string, ImageFileHandlerType>;

    using MetaRTLightType      = std::unique_ptr<IMetaRTLight>;
    using MetaRTLightContainer = std::map<std::string, MetaRTLightType>;

    using MetaRTShapeType      = std::unique_ptr<IMetaRTShape>;
    using MetaRTShapeContainer = std::map<std::string, MetaRTShapeType>;

    using MetaRTMaterialType      = std::unique_ptr<IMetaRTMaterial>;
    using MetaRTMaterialContainer = std::map<std::string, MetaRTMaterialType>;

  public:
    Registry();
    ~Registry();

  public:
    bool                             registerImageFileHandler(IImageFileHandler* handler);
    const IImageFileHandler*         getImageFileHandler(const std::string& id) const;
    const ImageFileHandlerContainer& getImageFileHandlers() const;

  public:
    bool                        registerMetaRTLight(IMetaRTLight* meta);
    const IMetaRTLight*         getMetaRTLight(const std::string& id) const;
    const MetaRTLightContainer& getMetaRTLights() const;

  public:
    bool                        registerMetaRTShape(IMetaRTShape* meta);
    const IMetaRTShape*         getMetaRTShape(const std::string& id) const;
    const MetaRTShapeContainer& getMetaRTShapes() const;

  public:
    bool                           registerMetaRTMaterial(IMetaRTMaterial* meta);
    const IMetaRTMaterial*         getMetaRTMaterial(const std::string& id) const;
    const MetaRTMaterialContainer& getMetaRTMaterialss() const;

  public:
    void registerDefaults();

  private:
    ImageFileHandlerContainer _imgHandlers;
    MetaRTLightContainer      _metaRTLights;
    MetaRTShapeContainer      _metaRTShapes;
    MetaRTMaterialContainer   _metaRTMaterials;
  };

  inline Registry& registry()
  {
    static Registry reg;
    return reg;
  }
}  // namespace Rayon

#endif  // RAYON_REGISTRY_HH_