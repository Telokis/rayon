#pragma once

#ifndef RAYON_IMAGEFILE_HANDLER_TGA_HH_
#define RAYON_IMAGEFILE_HANDLER_TGA_HH_

#include "IImageFileHandler.hh"

namespace RayOn
{
  class ImageFileHandler_TGA : public IImageFileHandler
  {
  public:
    bool readFromFile(const char* path, RawImage& readInto) const final;

    bool writeToFile(const char* path, const RawImage& readFrom) const final;

    const char* extensionName() const final;
  };
} // namespace RayOn

#endif // RAYON_IMAGEFILE_HANDLER_TGA_HH_