#include "Registry.hh"

#include <yaml-cpp/yaml.h>

#include <iostream>

#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "ImageFileHandlers/ImageFileHandler_TGA.hh"
#include "MetaMaterials/MetaPlain.hh"
#include "MetaRTLights/MetaSun.hh"
#include "MetaRTShapes/MetaBox.hh"
#include "MetaRTShapes/MetaMobius.hh"
#include "MetaRTShapes/MetaPlane.hh"
#include "MetaRTShapes/MetaRectangle.hh"
#include "MetaRTShapes/MetaSphere.hh"
#include "MetaRTShapes/MetaTriangle.hh"
#include "Rayon.hh"

namespace Rayon
{
  Registry::Registry()
  {
    registerMetaMaterial(new MetaPlain);
  }

  Registry::~Registry()
  {
  }

  void Registry::registerDefaults()
  {
    registerImageFileHandler(new ImageFileHandler_BMP);
    registerImageFileHandler(new ImageFileHandler_PNG);
    registerImageFileHandler(new ImageFileHandler_TGA);

    registerMetaRTLight(new MetaSun);

    registerMetaRTShape(new MetaSphere);
    registerMetaRTShape(new MetaPlane);
    registerMetaRTShape(new MetaRectangle);
    registerMetaRTShape(new MetaBox);
    registerMetaRTShape(new MetaMobius);
    registerMetaRTShape(new MetaTriangle);
  }

  bool Registry::registerImageFileHandler(IImageFileHandler* handler)
  {
    std::string id = handler->extensionName();
    if (_imgHandlers.count(id))
      return false;
    _imgHandlers[id].reset(handler);
    return true;
  }

  const IImageFileHandler* Registry::getImageFileHandler(const std::string& id) const
  {
    if (!_imgHandlers.count(id))
      return nullptr;
    return _imgHandlers.at(id).get();
  }

  auto Registry::getImageFileHandlers() const -> const ImageFileHandlerContainer&
  {
    return _imgHandlers;
  }

  bool Registry::registerMetaRTLight(IMetaRTLight* meta)
  {
    std::string id = meta->lightName();
    if (_metaRTLights.count(id))
      return false;
    _metaRTLights[id].reset(meta);
    return true;
  }

  const IMetaRTLight* Registry::getMetaRTLight(const std::string& id) const
  {
    if (!_metaRTLights.count(id))
      return nullptr;
    return _metaRTLights.at(id).get();
  }

  auto Registry::getMetaRTLights() const -> const MetaRTLightContainer&
  {
    return _metaRTLights;
  }

  bool Registry::registerMetaRTShape(IMetaRTShape* meta)
  {
    std::string id = meta->shapeName();
    if (_metaRTShapes.count(id))
      return false;
    _metaRTShapes[id].reset(meta);
    return true;
  }

  const IMetaRTShape* Registry::getMetaRTShape(const std::string& id) const
  {
    if (!_metaRTShapes.count(id))
      return nullptr;
    return _metaRTShapes.at(id).get();
  }

  auto Registry::getMetaRTShapes() const -> const MetaRTShapeContainer&
  {
    return _metaRTShapes;
  }

  bool Registry::registerMetaMaterial(IMetaRTMaterial* meta)
  {
    std::string id = meta->materialName();

    if (_metaMaterials.count(id))
      return false;

    _metaMaterials[id].reset(meta);
    return true;
  }

  const IMetaRTMaterial* Registry::getMetaMaterial(const std::string& id) const
  {
    if (!_metaMaterials.count(id))
      return nullptr;

    return _metaMaterials.at(id).get();
  }

  auto Registry::getMetaMaterialss() const -> const MetaMaterialContainer&
  {
    return _metaMaterials;
  }

}  // namespace Rayon
