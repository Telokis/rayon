#include "MetaRTMaterials/MetaTexture.hh"

#include "Materials/Texture.hh"

namespace Rayon
{
  RTMaterial* MetaTexture::make() const
  {
    return new Texture;
  }

  const char* MetaTexture::materialName() const
  {
    return Texture::MaterialName;
  }
}  // namespace Rayon
