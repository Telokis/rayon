#pragma once

#ifndef RAYON_REGISTRY_HH_
#define RAYON_REGISTRY_HH_

#include "ImageFileHandlers/IImageFileHandler.hh"
#include <vector>
#include <memory>
#include <map>

namespace RayOn
{
  class Registry
  {
    using ImageFileHandlerType = std::unique_ptr<IImageFileHandler>;
    using ImageFileHandlerContainer = std::map<std::string, ImageFileHandlerType>;

  public:
    Registry();
    ~Registry();

  public:
    bool  registerImageFileHandler(const std::string& id,
                                   IImageFileHandler* handler);
    const IImageFileHandler*  getImageFileHandler(const std::string& id) const;
    const ImageFileHandlerContainer&  getImageFileHandlers() const;

  private:
    ImageFileHandlerContainer _imgHandlers;
  };

  inline Registry& registry()
  {
    static Registry reg;
    return reg;
  }
} // namespace RayOn

#endif // RAYON_REGISTRY_HH_