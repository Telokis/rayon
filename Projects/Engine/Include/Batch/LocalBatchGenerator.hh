#pragma once

#ifndef RAYON_BATCH_LOCALBATCHGENERATOR_HH_
#define RAYON_BATCH_LOCALBATCHGENERATOR_HH_

#include "Batch/IBatchGenerator.hh"
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace Rayon
{
  class Scene;
  class RawImage;
}  // namespace Rayon

namespace Rayon
{
  class LocalBatchGenerator : public IBatchGenerator
  {
  public:
    LocalBatchGenerator(RawImage* img, int rppStart, int rppEnd, uint32 threadsCount);

  public:
    bool  hasNextBatch();
    Batch getNextBatch();
    void  reset();
    int   getRpp();

  protected:
    void   increaseRpp();
    uint32 rppToSize() const;

  protected:
    RawImage*               _img;
    int                     _rpp;
    int                     _rppStart;
    int                     _rppEnd;
    Int32Vec2_t             _pos;
    std::mutex              _mutex;
    std::condition_variable _rppSync;
    std::atomic_bool        _rppChanged;
    std::atomic<uint32>     _threadsLeft;
    uint32                  _threadsCount;
  };

}  // namespace Rayon

#endif  // RAYON_BATCH_LOCALBATCHGENERATOR_HH_