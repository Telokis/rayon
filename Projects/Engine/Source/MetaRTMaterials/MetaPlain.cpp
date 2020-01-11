#include "MetaRTMaterials/MetaPlain.hh"

#include "Materials/Plain.hh"

namespace Rayon
{
  RTMaterial* MetaPlain::make() const
  {
    return new Plain;
  }

  const char* MetaPlain::materialName() const
  {
    return Plain::MaterialName;
  }
}  // namespace Rayon
