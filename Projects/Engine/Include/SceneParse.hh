#ifndef RAYON_SCENEPARSE_HH_
#define RAYON_SCENEPARSE_HH_

#include <yaml-cpp/node/node.h>

#include <string>

#include "Tools/Helpers.hh"

namespace Rayon
{
  class Scene;
  class Material;
  class Color;

  bool isString(const YAML::Node& node);
  bool isUint32(const YAML::Node& node);
  bool isDouble(const YAML::Node& node);

  void readSceneFromFile(Scene& scene, const std::string& filename);
  void readSceneFromString(Scene& scene, const std::string& content);
  void sceneWrite(const Scene& scene, const std::string& filename);

  void materialRead(Material& material, const std::string& filename);
  void materialWrite(const Material& material, const std::string& filename);

  void writeVal(YAML::Node& node, const std::string& name, const uint32& val, const uint32& def);
  void writeVal(YAML::Node& node, const std::string& name, const Float_t& val, const Float_t& def);
  void writeVal(YAML::Node& node, const std::string& name, const Color& color, const Color& def);
  void writeVal(YAML::Node& node, const std::string& name, const Vec_t& vec, const Vec_t& def);

  void readVal(const YAML::Node& parent, const std::string& name, uint32& val, const uint32& def);
  void readVal(const YAML::Node& parent, const std::string& name, Float_t& val, const Float_t& def);
  void readVal(const YAML::Node& parent, const std::string& name, Color& color, const Color& def);
  void readVal(const YAML::Node& parent, const std::string& name, Vec_t& vec, const Vec_t& def);
}  // namespace Rayon

#endif  // RAYON_SCENEPARSE_HH_
