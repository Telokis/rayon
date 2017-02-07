#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_BMP
#include "libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include "Ray.hh"
#include "RayOn.hh"

#include <iostream>

int  main(int ac, char** av)
{
  try
  {
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