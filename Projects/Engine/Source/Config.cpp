#include "Config.hh"

namespace Rayon
{
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, std::string, outputPath, OutputPath);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, std::string, inputPath, InputPath);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, width, Width);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, height, Height);
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, threadsCount, ThreadCount);
}  // namespace Rayon
