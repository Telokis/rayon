#include "Worker.hh"

#include <chrono>

#include "Entities/Shapes/RTShape.hh"
#include "IntersectionData.hh"
#include "Object.hh"
#include "Tools/Stat.hh"

namespace Rayon
{
  Worker::Worker(RawImage* img, uint32 xStart, uint32 xStop, Tools::Stat* stat)
    : _img(img), _xStart(xStart), _xStop(xStop), _stat(stat)
  {
  }

  void Worker::operator()(uint32 width, uint32 height, const Scene* scene)
  {
    auto start = std::chrono::steady_clock::now();
    Ray  cameraRay(RayType::Primary, scene->eye().getPos(), Vec_t());

    Float_t fovX = Tools::DegToRad(55.0);
    Float_t fovY = (fovX * height) / width;

    Float_t angleV = fovX / width;
    Float_t angleH = fovY / height;

    for (uint32 x = _xStart; x < _xStop; ++x)
    {
      for (uint32 y = 0; y < height; ++y)
      {
        Float_t tmpAngleV = fovX / 2 - angleV * x;
        Float_t tmpAngleH = fovY / 2 - angleH * y;
        Float_t cosV      = Tools::Cos(tmpAngleV);
        Float_t cosH      = Tools::Cos(tmpAngleH);

        Vec_t tmp{
          Tools::Sin(tmpAngleV) * cosH,
          Tools::Sin(tmpAngleH) * cosV,
          cosH * cosV,
        };

        cameraRay.setDirection(tmp);
        cameraRay.setDirection(scene->eye().indirectRotation(tmp));
        cameraRay.normalize();

        auto color        = scene->inter(cameraRay, 0, _stat);
        _img->pixel(x, y) = color;
      }
    }

    auto end       = std::chrono::steady_clock::now();
    _stat->elapsed = end - start;
  }

}  // namespace Rayon
