#include "Batch/LocalBatchGenerator.hh"
#include "RawImage.hh"
#include "Tools/Helpers.hh"

namespace Rayon
{
  static constexpr const int BATCH_SIZE = 16;

  LocalBatchGenerator::LocalBatchGenerator(RawImage* img,
                                           int       rppStart,
                                           int       rppEnd,
                                           uint32    threadsCount)
    : _img(img)
    , _rpp(rppStart)
    , _rppStart(rppStart)
    , _rppEnd(rppEnd)
    , _pos(0, 0)
    , _rppChanged(false)
    , _threadsLeft(threadsCount)
    , _threadsCount(threadsCount)
  {
  }

  bool LocalBatchGenerator::hasNextBatch()
  {
    std::unique_lock lock(_mutex);

    if (_rppChanged)
    {
      if (--_threadsLeft)
      {
        _rppSync.wait(lock);
      }
      else
      {
        _threadsLeft = _threadsCount;
        _rppChanged  = false;
        _rppSync.notify_all();
      }
    }

    return _rpp <= _rppEnd;
  }

  Batch LocalBatchGenerator::getNextBatch()
  {
    std::lock_guard lock(_mutex);

    auto totalPixelsSide = rppToSize() * BATCH_SIZE;

    UInt32Vec2_t start = _pos;
    UInt32Vec2_t end   = {Tools::Clamp(start.x + totalPixelsSide, 0u, _img->width()),
                        Tools::Clamp(start.y + totalPixelsSide, 0u, _img->height())};

    _pos.x = end.x;

    if (_pos.x >= _img->width())
    {
      if (_pos.y >= _img->height())
      {
        increaseRpp();
      }
      else
      {
        _pos.x = 0;
        _pos.y = end.y;
      }
    }

    return Batch(this, start, end, _img, _rpp);
  }

  void LocalBatchGenerator::reset()
  {
    std::unique_lock lock(_mutex);

    _rppSync.notify_all();
    _threadsLeft = _threadsCount;
    _rppChanged  = false;
    _rpp         = _rppStart;
    _pos         = {0, 0};
  }

  void LocalBatchGenerator::increaseRpp()
  {
    _rpp += 1;
    _rppChanged = true;

    if (_rpp == 0)
    {
      _rpp = 1;
    }

    _pos = {0, 0};
  }

  int LocalBatchGenerator::getRpp()
  {
    return _rpp;
  }

  uint32 LocalBatchGenerator::rppToSize() const
  {
    if (_rpp >= 0)
    {
      return 1;
    }

    return Tools::Pow(2, -_rpp);
  }
};  // namespace Rayon