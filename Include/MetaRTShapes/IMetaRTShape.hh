#pragma once

#ifndef RAYON_IMETA_RTSHAPE_HH_
#define RAYON_IMETA_RTSHAPE_HH_

#include "Entities/Shapes/RTShape.hh"

namespace Rayon
{
  class IMetaRTShape
  {
  public:
    virtual RTShape*    make() const = 0;

    virtual const char* shapeName() const = 0;
  };
} // namespace Rayon

#endif // RAYON_IMETA_RTSHAPE_HH_