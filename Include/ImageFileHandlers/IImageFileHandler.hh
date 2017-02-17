#pragma once

#ifndef RAYON_IIMAGEFILE_HANDLER_HH_
#define RAYON_IIMAGEFILE_HANDLER_HH_

#include "RawImage.hh"

namespace Rayon
{
  class IImageFileHandler
  {
  public:
    virtual bool readFromFile(const char* path, RawImage& readInto) const = 0;
    //virtual bool readFromMemory(const char* data, size_t size, RawImage& readInto) const = 0;

    virtual bool writeToFile(const char* path, const RawImage& readFrom) const = 0;
    //virtual bool writeToMemory(char*& data, size_t& size, const RawImage& readFrom) const = 0;

    virtual const char* extensionName() const = 0;
  };
} // namespace Rayon

#endif // RAYON_IIMAGEFILE_HANDLER_HH_