#include "ImageFileHandlers/ImageFileHandler_JPG.hh"

#include <memory>

#include "Libraries/stb_image.hh"
#include "Libraries/stb_image_write.hh"

namespace Rayon
{
  bool ImageFileHandler_JPG::readFromFile(const char* path, RawImage& readInto) const
  {
    int            w, h, n;
    unsigned char* data = stbi_load(path, &w, &h, &n, 4);

    if (!data)
      return false;

    readInto.fromRawRGBA(data, w, h);
    stbi_image_free(data);
    return true;
  }

  bool ImageFileHandler_JPG::writeToFile(const char* path, const RawImage& readFrom) const
  {
    auto data = readFrom.rawRGBA();
    return stbi_write_jpg(path, readFrom.width(), readFrom.height(), 4, data.get(), 90) != 0;
  }

  const char* ImageFileHandler_JPG::extensionName() const
  {
    return "jpg";
  }
}  // namespace Rayon
