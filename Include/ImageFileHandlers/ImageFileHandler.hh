#pragma once

#ifndef RAYON_IMAGEFILE_HANDLER_HH_
#define RAYON_IMAGEFILE_HANDLER_HH_

#include <string>

namespace Rayon
{
  class RawImage;

  class ImageFileHandler
  {
  public:
    static bool  readFromFileBasedOnExtension(const std::string& file,
                                              RawImage& readInto);
    static bool  writeToFileBasedOnExtension(const std::string& file,
                                             const RawImage& readFrom,
                                             bool force = true);
  };
} // namespace Rayon

#endif // RAYON_IMAGEFILE_HANDLER_HH_