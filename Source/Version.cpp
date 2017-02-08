#include "Version.hh"
#include <string>

using namespace std;

const int RAYON_BUILD_VERSION = 18;

const char* const RAYON_COMMIT_HASH = "acf1d43";

const char* const RayOn::version()
{
  return "0.4.18 (acf1d43)";
}
