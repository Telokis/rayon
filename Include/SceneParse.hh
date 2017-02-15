#ifndef RAYON_SCENEPARSE_HH_
#define RAYON_SCENEPARSE_HH_

#include "Tools/Helpers.hh"

#include <string>
#include <Json-forwards.h>

namespace RayOn
{
  class Scene;
  class Material;
  class Color;

  void  sceneParse(Scene& scene, const std::string& filename);
  void  sceneWrite(const Scene& scene, const std::string& filename);

  void  writeVal(Json::Value& node, const std::string& name, const Float_t& val);
  void  writeVal(Json::Value& node, const std::string& name, const Color& color);
  void  writeVal(Json::Value& node, const std::string& name, const Vec_t& vec);

  void  readVal(const Json::Value& parent, const std::string& name, Float_t& val);
  void  readVal(const Json::Value& parent, const std::string& name, Color& color);
  void  readVal(const Json::Value& parent, const std::string& name, Vec_t& vec);
} // namespace RayOn

#endif // RAYON_SCENEPARSE_HH_
