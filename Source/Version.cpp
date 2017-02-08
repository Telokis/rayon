#include "Version.hh"
#include <string>

using namespace std;

const int RAYON_BUILD_VERSION = 16;

const char* const RAYON_COMMIT_HASH = "584b886";

const char* const RayOn::version()
{
  return "0.4.16 (584b886)";
}
