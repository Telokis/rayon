#pragma once

#ifndef RAYON_BATCH_IBATCHGENERATOR_HH_
#define RAYON_BATCH_IBATCHGENERATOR_HH_

#include "Batch/Batch.hh"

namespace Rayon
{
  class IBatchGenerator
  {
  public:
    virtual bool  hasNextBatch() = 0;
    virtual Batch getNextBatch() = 0;
    virtual void  reset()        = 0;
    virtual int   getRpp()       = 0;
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_IBATCHGENERATOR_HH_