#include "Config.hh"

namespace Rayon
{
  Config::Config() : Config(1024, 1024)
  {
  }

  Config::Config(uint32 w, uint32 h) : Config(w, h, 4)
  {
  }

  Config::Config(uint32 w, uint32 h, uint32 j) : width(w), height(h), threadsCount(j)
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, width, Width);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, height, Height);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, threadsCount, ThreadCount);
}  // namespace Rayon
