#include "ImageFileHandlers/ImageFileHandler.hh"

#include <algorithm>
#include <iostream>

#include "RawImage.hh"
#include "Registry.hh"

namespace Rayon
{
  bool ImageFileHandler::readFromFileBasedOnExtension(const std::string& file, RawImage& readInto)
  {
    std::string ext = file.substr(file.find_last_of('.') + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext.empty())
    {
      std::cerr << "[Warning]No extension specified. Defaulting to bmp\n";
      ext = "bmp";
    }

    const IImageFileHandler* handler = registry().getImageFileHandler(ext);
    if (handler)
      return handler->readFromFile(file.c_str(), readInto);

    std::cerr << "[Error]No handler found for extension [" << ext << "].\n";
    return false;
  }

  bool ImageFileHandler::writeToFileBasedOnExtension(const std::string& file,
                                                     const RawImage&    readFrom,
                                                     bool               force)
  {
    std::string ext = file.substr(file.find_last_of('.') + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext.empty())
    {
      std::cerr << "[Warning]No extension specified. Defaulting to png\n";
      ext = "png";
    }

    const auto&              handlers = registry().getImageFileHandlers();
    const IImageFileHandler* def      = handlers.empty() ? nullptr : handlers.begin()->second.get();
    const IImageFileHandler* handler  = registry().getImageFileHandler(ext);

    if (handler)
      return handler->writeToFile(file.c_str(), readFrom);

    if (force)
    {
      if (def)
      {
        std::cout << "[Info]No handler found for extension [" << ext
                  << "]."
                     " Forcing to "
                  << def->extensionName() << "...\n";

        return def->writeToFile(
          (file.substr(0, file.length() - ext.length()) + def->extensionName()).c_str(), readFrom);
      }
      std::cerr << "[SEVERE]No handler registered.\n";
      return false;
    }

    std::cerr << "[Error]No handler found for extension [" << ext << "].\n";
    std::cerr << "       Set force to true to default to another handler.\n";
    return false;
  }
}  // namespace Rayon
