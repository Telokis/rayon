#pragma once

#ifndef RAYON_TOOLS_RANDOM_HH
#define RAYON_TOOLS_RANDOM_HH

#include <random>

namespace Rayon
{
  namespace Tools
  {
    class Random
    {
    public:
      Random();
      Random(unsigned int seed);

    public:
      void seed(unsigned int s);

    public:
      int nextInt();
      int nextInt(int max);
      int nextInt(int min, int max);

    public:
      double nextDouble();
      double nextDouble(double max);
      double nextDouble(double min, double max);

    private:
      std::mt19937 _generator;
    };

    Random& random()
    {
      static Random rnd;
      return rnd;
    }
  }  // namespace Tools
}  // namespace Rayon

#endif  // RAYON_TOOLS_RANDOM_HH