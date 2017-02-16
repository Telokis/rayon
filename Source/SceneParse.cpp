#include "SceneParse.hh"
#include "Scene.hh"
#include "Registry.hh"
#include "Entities/Lights/RTLight.hh"

#include <Json.h>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace RayOn
{
  namespace
  {
    void        readJson(const fs::path& path, Json::Value& root)
    {
      std::string str = path.string();
      std::ifstream file(str);

      if (!file.is_open())
        throw std::runtime_error("Unable to open `" + str + "`");

      Json::Reader    reader;
      if (!reader.parse(file, root))
        throw std::runtime_error("Error while parsing `" + str + "`: "
                                 + reader.getFormattedErrorMessages());
    }

    void        writeJson(const fs::path& path, Json::Value& root)
    {
      std::string str = path.string();
      std::ofstream file(str);

      if (!file.is_open())
        throw std::runtime_error("Unable to open `" + str + "`");

      file << root;
    }
  }

  void  sceneRead(Scene& scene, const std::string& filename)
  {
    Json::Value root;

    readJson(filename, root);
    if (root.isMember("eye") && root["eye"].isObject())
    {
      Eye eye;
      eye.read(root["eye"]);
      scene.setEye(eye);
    }
    if (root.isMember("cubemap") && root["cubemap"].isObject())
    {
      CubeMap cubemap;
      cubemap.read(root["cubemap"]);
      scene.setCubeMap(cubemap);
    }
    if (root.isMember("objects") && root["objects"].isArray())
    {
      const Json::Value& objects = root["objects"];

      for (const Json::Value& object : objects)
      {
        if (object.isMember("type") && object["type"].isString())
        {
          std::string name = object["type"].asString();
          const IMetaRTObject* meta = registry().getMetaRTObject(name);
          if (meta)
          {
            RTObject* obj = meta->make();
            obj->read(object);
            scene.addObject(obj);
          }
          else
          {
            std::cout << "[Warning] Unknown type `" << name << "` for object. Skipping...\n";
            continue;
          }
        }
        else
          std::cout << "[Warning] Invalid `type` for object. Skipping...\n";
      }
    }
    if (root.isMember("lights") && root["lights"].isArray())
    {
      const Json::Value& lights = root["lights"];

      for (const Json::Value& light : lights)
      {
        if (light.isMember("type") && light["type"].isString())
        {
          std::string name = light["type"].asString();
          const IMetaRTLight* meta = registry().getMetaRTLight(name);
          if (meta)
          {
            RTLight* lig = meta->make();
            lig->read(light);
            scene.addLight(lig);
          }
          else
          {
            std::cout << "[Warning] Unknown type `" << name << "` for light. Skipping...\n";
            continue;
          }
        }
        else
          std::cout << "[Warning] Invalid `type` for light. Skipping...\n";
      }
    }
  }

  void  sceneWrite(const Scene& scene, const std::string& filename)
  {
    Json::Value root;

    scene.eye().write(root["eye"]);
    scene.cubemap().write(root["cubemap"]);
    Json::Value& lights = root["lights"];
    for (const auto& light : scene.lights())
    {
      Json::Value val;
      val["type"] = light->name();
      light->write(val);
      lights.append(val);
    }
    Json::Value& objects = root["objects"];
    for (const auto& obj : scene.objects())
    {
      Json::Value val;
      val["type"] = obj->name();
      obj->write(val);
      objects.append(val);
    }
    writeJson(filename, root);
  }

  /*
   *  Write
   */
  void  writeVal(Json::Value& node, const std::string& name, const Float_t& val)
  {
    node[name] = static_cast<double>(val);
  }

  void  writeVal(Json::Value& node, const std::string& name, const Color& color)
  {
    Json::Value& subNode = node[name];
    subNode["red"] = color.red();
    subNode["green"] = color.green();
    subNode["blue"] = color.blue();
  }

  void  writeVal(Json::Value& node, const std::string& name, const Vec_t& vec)
  {
    Json::Value& subNode = node[name];
    writeVal(subNode, "x", vec.x);
    writeVal(subNode, "y", vec.y);
    writeVal(subNode, "z", vec.z);
  }

  /*
   *  Read
   */
  void  readVal(const Json::Value& parent, const std::string& name, Float_t& val)
  {
    if (parent.isMember(name) && parent[name].isDouble())
      val = parent[name].asDouble();
  }

  void  readVal(const Json::Value& parent, const std::string& name, Color& color)
  {
    if (parent.isMember(name) && parent[name].isObject())
    {
      const Json::Value& colorNode = parent[name];
      if (colorNode.isMember("red") && colorNode["red"].isUInt())
        color.red() = colorNode["red"].asUInt();
      if (colorNode.isMember("green") && colorNode["green"].isUInt())
        color.green() = colorNode["green"].asUInt();
      if (colorNode.isMember("blue") && colorNode["blue"].isUInt())
        color.blue() = colorNode["blue"].asUInt();
    }
  }

  void  readVal(const Json::Value& parent, const std::string& name, Vec_t& vec)
  {
    if (parent.isMember(name) && parent[name].isObject())
    {
      const Json::Value& node = parent[name];
      readVal(node, "x", vec.x);
      readVal(node, "y", vec.y);
      readVal(node, "z", vec.z);
    }
  }
} // namespace RayOn
