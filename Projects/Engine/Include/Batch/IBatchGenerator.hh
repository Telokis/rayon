#pragma once

#ifndef RAYON_BATCH_IBATCHGENERATOR_HH_
#define RAYON_BATCH_IBATCHGENERATOR_HH_

#include <string_view>
#include "Batch/Batch.hh"

namespace Rayon
{
  class IBatchGenerator
  {
  public:
    virtual Batch getNextBatch(const std::string_view& sourceIdentifier) = 0;
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_IBATCHGENERATOR_HH_