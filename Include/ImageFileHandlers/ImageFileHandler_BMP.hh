#pragma once

#ifndef RAYON_IMAGEFILE_HANDLER_BMP_HH_
#define RAYON_IMAGEFILE_HANDLER_BMP_HH_

#include "IImageFileHandler.hh"

namespace Rayon
{
  class ImageFileHandler_BMP : public IImageFileHandler
  {
  public:
    bool readFromFile(const char* path, RawImage& readInto) const final;

    bool writeToFile(const char* path, const RawImage& readFrom) const final;

    const char* extensionName() const final;
  };
}  // namespace Rayon

#endif  // RAYON_IMAGEFILE_HANDLER_BMP_HH_