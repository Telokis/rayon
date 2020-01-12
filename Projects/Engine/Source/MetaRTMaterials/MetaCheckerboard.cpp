#include "MetaRTMaterials/MetaCheckerboard.hh"

#include "Materials/Checkerboard.hh"

namespace Rayon
{
  RTMaterial* MetaCheckerboard::make() const
  {
    return new Checkerboard;
  }

  const char* MetaCheckerboard::materialName() const
  {
    return Checkerboard::MaterialName;
  }
}  // namespace Rayon
