#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "ImageFileHandlers/ImageFileHandler_TGA.hh"

#include "Ray.hh"
#include "RayOn.hh"
#include "Registry.hh"

#include <iostream>

void  setupDefaultRegistry()
{
  RayOn::registry().registerImageFileHandler("bmp", new RayOn::ImageFileHandler_BMP);
  RayOn::registry().registerImageFileHandler("png", new RayOn::ImageFileHandler_PNG);
  RayOn::registry().registerImageFileHandler("tga", new RayOn::ImageFileHandler_TGA);
}

int  main(int ac, char** av)
{
  try
  {
    setupDefaultRegistry();
    RayOn::RayOn  app(ac, av);
    return app.run();
  }
  catch (std::exception& except)
  {
    std::cerr << "*****************************************************\n";
    std::cerr << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n";
    std::cerr << "_____________________________________________________\n";
    std::cerr << except.what() << "\n";
    std::cerr << "_____________________________________________________\n";
    std::cerr << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n";
    std::cerr << "*****************************************************\n";
    return 1;
  }
}
