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
    readInto.resize(w, h);
    size_t i = 0;
    for (Color& color : readInto.pixels())
    {
      auto index = i * 4;
      color.red()   = data[index];
      color.green() = data[index + 1];
      color.blue()  = data[index + 2];
      color.alpha() = data[index + 3];
      ++i;
    }
    stbi_image_free(data);
    return true;
  }

  bool ImageFileHandler_BMP::writeToFile(const char* path, const RawImage& readFrom) const
  {
    std::unique_ptr<char[]> data(new char[readFrom.width() * readFrom.height() * 4]);

    size_t i = 0;
    for (const Color& color : readFrom.pixels())
    {
      auto index = i * 4;
      data[index    ] = color.red();
      data[index + 1] = color.green();
      data[index + 2] = color.blue();
      data[index + 3] = color.alpha();
      ++i;
    }
    return stbi_write_bmp(path, readFrom.width(), readFrom.height(), 4, data.get()) != 0;
  }
} // namespace RayOn
