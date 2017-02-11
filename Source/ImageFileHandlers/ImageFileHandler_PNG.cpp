#include "Libraries/stb_image.hh"
#include "Libraries/stb_image_write.hh"

#include <memory>

#include "ImageFileHandlers/ImageFileHandler_PNG.hh"

namespace RayOn
{
  bool ImageFileHandler_PNG::readFromFile(const char* path, RawImage& readInto) const
  {
    int w, h, n;
    unsigned char *data = stbi_load(path, &w, &h, &n, 4);
    if (!data)
      return false;
    readInto.fromRawRGBA(data, w, h);
    stbi_image_free(data);
    return true;
  }

  bool ImageFileHandler_PNG::writeToFile(const char* path, const RawImage& readFrom) const
  {
    auto data = readFrom.rawRGBA();
    return stbi_write_png(path, readFrom.width(), readFrom.height(),
                          4, data.get(), readFrom.width() * 4) != 0;
  }
  const char* ImageFileHandler_PNG::extensionName() const
  {
    return "png";
  }
} // namespace RayOn
