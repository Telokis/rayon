#include "RayOn.hh"
#include "Version.hh"
#include <iostream>

namespace RayOn
{

  RayOn::RayOn(int ac, char** av)
  {
    config().init(ac, av);
  }

  int RayOn::run()
  {
    if (config().handleStoppingArgs())
      return 0;

    return 0;
  }

} // namespace RayOn
