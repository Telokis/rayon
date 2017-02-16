#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include "ImageFileHandlers/ImageFileHandler_PNG.hh"
#include "ImageFileHandlers/ImageFileHandler_TGA.hh"

#include "MetaRTLights/MetaSun.hh"

#include "MetaRTObjects/MetaSphere.hh"
#include "MetaRTObjects/MetaPlane.hh"
#include "MetaRTObjects/MetaRectangle.hh"
#include "MetaRTObjects/MetaBox.hh"

#include "Ray.hh"
#include "RayOn.hh"
#include "Registry.hh"

#include <iostream>

void  setupDefaultRegistry()
{
  RayOn::registry().registerImageFileHandler(new RayOn::ImageFileHandler_BMP);
  RayOn::registry().registerImageFileHandler(new RayOn::ImageFileHandler_PNG);
  RayOn::registry().registerImageFileHandler(new RayOn::ImageFileHandler_TGA);

  RayOn::registry().registerMetaRTLight(new RayOn::MetaSun);

  RayOn::registry().registerMetaRTObject(new RayOn::MetaSphere);
  RayOn::registry().registerMetaRTObject(new RayOn::MetaPlane);
  RayOn::registry().registerMetaRTObject(new RayOn::MetaRectangle);
  RayOn::registry().registerMetaRTObject(new RayOn::MetaBox);
}

int  main(int ac, char** av)
{
  try
  {
    std::cout << std::hex;
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
