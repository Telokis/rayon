#include "Batch/Batch.hh"
#include "Scene.hh"
#include "RawImage.hh"

namespace Rayon
{
  Batch::Batch(const Scene* scene, Int32Vec2_t start, Int32Vec2_t end, RawImage* img, int rpp)
    : _scene(scene), _start(start), _end(end), _img(img), _rpp(rpp)
  {
  }

  void Batch::forEachWork(WorkFunction_t f)
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Batch, const Scene*, _scene, Scene);
};  // namespace Rayon