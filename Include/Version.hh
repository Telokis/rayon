#pragma once

#ifndef RAYON_VERSION_HH_
#define RAYON_VERSION_HH_

#define RAYON_MAJOR_VERSION 0
#define RAYON_MINOR_VERSION 5

extern const int RAYON_BUILD_VERSION;
extern const char* const RAYON_COMMIT_HASH;

namespace RayOn
{
  const char* const version();
}

#endif // RAYON_VERSION_HH_