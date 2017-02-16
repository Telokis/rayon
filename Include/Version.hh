#pragma once

#ifndef RAYON_VERSION_HH_
#define RAYON_VERSION_HH_

#define RAYON_MAJOR_VERSION 1
#define RAYON_MINOR_VERSION 3

extern const int RAYON_BUILD_VERSION;
extern const char* const RAYON_COMMIT_HASH;

namespace RayOn
{
  const char* version();
}

#endif // RAYON_VERSION_HH_
