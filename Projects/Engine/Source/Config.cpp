#include "Config.hh"

namespace Rayon
{
  Config::Config() : width(1024), height(1024), threadsCount(4)
  {
  }

  Config::Config(uint32 w, uint32 h) : width(w), height(h), threadsCount(4)
  {
  }

  Config::Config(uint32 w, uint32 h, uint32 j) : width(w), height(h), threadsCount(j)
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, width, Width);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, height, Height);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, threadsCount, ThreadCount);
}  // namespace Rayon
