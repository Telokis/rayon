#include "Tools/Random.hh"

#include <cassert>
#include <numeric>

namespace Rayon::Tools
{
  Random::Random() : Random(std::random_device{}())
  {
  }

  Random::Random(unsigned int seed) : _generator(seed)
  {
  }

  void Random::seed(unsigned int s)
  {
    _generator.seed(s);
  }

  int Random::nextInt()
  {
    return nextInt(0, std::numeric_limits<int>::max());
  }

  int Random::nextInt(int max)
  {
    return nextInt(0, max);
  }

  int Random::nextInt(int min, int max)
  {
    assert(min < max);
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(_generator);
  }

  double Random::nextDouble()
  {
    return nextDouble(0.0, 1.0);
  }

  double Random::nextDouble(double max)
  {
    return nextDouble(0.0, max);
  }

  double Random::nextDouble(double min, double max)
  {
    assert(min < max);
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(_generator);
  }
}  // namespace Rayon::Tools