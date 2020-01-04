#include "MetaRTShapes/MetaMobius.hh"

#include "Entities/Shapes/Mobius.hh"

namespace Rayon
{
  RTShape* MetaMobius::make() const
  {
    return new Mobius;
  }

  const char* MetaMobius::shapeName() const
  {
    return Mobius::ShapeName;
  }
}  // namespace Rayon
