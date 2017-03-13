#include "MetaRTObjects/MetaMobius.hh"
#include "Entities/Objects/Mobius.hh"

namespace Rayon
{
  RTObject*    MetaMobius::make() const
  {
    return new Mobius;
  }

  const char* MetaMobius::objectName() const
  {
    return Mobius::ObjectName;
  }
} // namespace Rayon
