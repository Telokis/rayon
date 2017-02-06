#define _CRT_SECURE_NO_WARNINGS 1
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_BMP
#include "libraries/stb_image.hh"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libraries/stb_image_write.hh"
#undef _CRT_SECURE_NO_WARNINGS

#include "Ray.hh"
#include "ImageFileHandlers/ImageFileHandler_BMP.hh"
#include <iostream>
#include <iomanip>
#include <string>

using namespace RayOn;

int  main()
{
  RawImage img(2, 2);

  img.pixel(0, 0) = Color(255, 0, 0);
  img.pixel(1, 0) = Color(0, 0, 255);
  img.pixel(0, 1) = Color(255, 255, 255);
  img.pixel(1, 1) = Color(0, 0, 0);
  
  IImageFileHandler* ifh = new ImageFileHandler_BMP;
  ifh->writeToFile("./test.bmp", img);
  return 0;
}