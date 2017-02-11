#include "Registry.hh"
#include "RayOn.hh"
#include <iostream>
namespace RayOn
{
  Registry::Registry()
  {
  }

  Registry::~Registry()
  {
  }

  bool Registry::registerImageFileHandler(const std::string& id,
                                          IImageFileHandler* handler)
  {
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

} // namespace RayOn
