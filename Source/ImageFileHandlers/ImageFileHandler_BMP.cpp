#include "libraries/stb_image.hh"
#include "libraries/stb_image_write.hh"

#include <memory>

#include "ImageFileHandlers/ImageFileHandler_BMP.hh"

namespace RayOn
{
  bool ImageFileHandler_BMP::readFromFile(const char* path, RawImage& readInto) const
  {
    int w, h, n;
    unsigned char *data = stbi_load(path, &w, &h, &n, 4);
    if (!data)
      return false;
    readInto.fromRaw(data, w, h);
    stbi_image_free(data);
    return true;
  }

  bool ImageFileHandler_BMP::writeToFile(const char* path, const RawImage& readFrom) const
  {
    auto data = readFrom.raw();
    return stbi_write_bmp(path, readFrom.width(), readFrom.height(), 4, data.get()) != 0;
  }
  const char* ImageFileHandler_BMP::extensionName() const
  {
    return "bmp";
  }
} // namespace RayOn
