#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "ImageFileHandlers/ImageFileHandler_TGA.hh"
#include "MetaRTLights/MetaSun.hh"
#include "MetaRTShapes/MetaBox.hh"
#include "MetaRTShapes/MetaMobius.hh"
#include "MetaRTShapes/MetaPlane.hh"
#include "MetaRTShapes/MetaRectangle.hh"
#include "MetaRTShapes/MetaSphere.hh"
#include "MetaRTShapes/MetaTriangle.hh"
#include "Ray.hh"
#include "Rayon.hh"
#include "Registry.hh"

void setupDefaultRegistry()
{
  Rayon::registry().registerImageFileHandler(new Rayon::ImageFileHandler_BMP);
  Rayon::registry().registerImageFileHandler(new Rayon::ImageFileHandler_PNG);
  Rayon::registry().registerImageFileHandler(new Rayon::ImageFileHandler_TGA);

  Rayon::registry().registerMetaRTLight(new Rayon::MetaSun);

  Rayon::registry().registerMetaRTShape(new Rayon::MetaSphere);
  Rayon::registry().registerMetaRTShape(new Rayon::MetaPlane);
  Rayon::registry().registerMetaRTShape(new Rayon::MetaRectangle);
  Rayon::registry().registerMetaRTShape(new Rayon::MetaBox);
  Rayon::registry().registerMetaRTShape(new Rayon::MetaMobius);
  Rayon::registry().registerMetaRTShape(new Rayon::MetaTriangle);
}

int main(int ac, char** av)
{
  try
  {
    std::cout << std::hex;
    setupDefaultRegistry();
    Rayon::Rayon app(ac, av);
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
    std::cin.get();
    return 1;
  }
}
