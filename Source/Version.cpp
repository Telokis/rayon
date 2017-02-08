#include "Version.hh"
#include <string>

using namespace std;

const int RAYON_BUILD_VERSION = 17;

const char* const RAYON_COMMIT_HASH = "529b715";

const char* const RayOn::version()
{
  return "0.4.17 (529b715)";
}
