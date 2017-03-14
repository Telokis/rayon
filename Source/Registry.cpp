#include "Registry.hh"
#include "Rayon.hh"

#include <iostream>
#include <Json.h>

namespace Rayon
{
  Registry::Registry()
  {
  }

  Registry::~Registry()
  {
  }

  bool Registry::registerImageFileHandler(IImageFileHandler* handler)
  {
    std::string id = handler->extensionName();
    if (_imgHandlers.count(id))
      return false;
    _imgHandlers[id].reset(handler);
    return true;
  }

  const IImageFileHandler*  Registry::getImageFileHandler(const std::string& id) const
  {
    if (!_imgHandlers.count(id))
      return nullptr;
    return _imgHandlers.at(id).get();
  }

  auto  Registry::getImageFileHandlers() const -> const ImageFileHandlerContainer&
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

  const IMetaRTLight*  Registry::getMetaRTLight(const std::string& id) const
  {
    if (!_metaRTLights.count(id))
      return nullptr;
    return _metaRTLights.at(id).get();
  }

  auto  Registry::getMetaRTLights() const -> const MetaRTLightContainer&
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

  const IMetaRTShape*  Registry::getMetaRTShape(const std::string& id) const
  {
    if (!_metaRTShapes.count(id))
      return nullptr;
    return _metaRTShapes.at(id).get();
  }

  auto  Registry::getMetaRTShapes() const -> const MetaRTShapeContainer&
  {
    return _metaRTShapes;
  }

} // namespace Rayon
