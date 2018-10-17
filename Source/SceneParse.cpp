#include "SceneParse.hh"
#include "Scene.hh"
#include "Registry.hh"
#include "Object.hh"
#include "Entities/Lights/RTLight.hh"

#include <Json.h>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace Rayon
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
        Object  obj;
        if (obj.read(object))
          scene.addObject(obj);
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
    for (const Object* obj : scene.objects())
    {
      Json::Value val;
      val["type"] = obj->getShape()->name();
      obj->write(val);
      objects.append(val);
    }
    writeJson(filename, root);
  }

  void materialRead(Material& material, const std::string& filename)
  {
    Json::Value root;

    readJson(filename, root);
    material.read(root);
  }

  void materialWrite(const Material& material, const std::string& filename)
  {
    Json::Value root;

    material.write(root);
    writeJson(filename, root);
  }

  /*
   *  Write
   */
  void  writeVal(Json::Value& node, const std::string& name,
                 const Float_t& val, const Float_t& def)
  {
    node[name] = static_cast<double>(val);
  }

  void  writeVal(Json::Value& node, const std::string& name,
                 const uint32& val, const uint32& def)
  {
    node[name] = val;
  }

  void  writeVal(Json::Value& node, const std::string& name,
                 const Color& color, const Color& def)
  {
    Json::Value& subNode = node[name];
    const auto value = color.intValue();
    const auto& cols = colors();
    for (const auto& pair : cols)
    {
      if (value == pair.second.intValue())
      {
        subNode = pair.first;
        return;
      }
    }
    writeVal(subNode, "red", uint32(color.red()), uint32(def.red()));
    writeVal(subNode, "green", uint32(color.green()), uint32(def.green()));
    writeVal(subNode, "blue", uint32(color.blue()), uint32(def.blue()));
  }

  void  writeVal(Json::Value& node, const std::string& name,
                 const Vec_t& vec, const Vec_t& def)
  {
    Json::Value& subNode = node[name];
    writeVal(subNode, "x", vec.x, def.x);
    writeVal(subNode, "y", vec.y, def.y);
    writeVal(subNode, "z", vec.z, def.z);
  }

  /*
   *  Read
   */
  void  readVal(const Json::Value& parent, const std::string& name,
                uint32& val, const uint32& def)
  {
    if (parent.isMember(name) && parent[name].isUInt())
      val = parent[name].asUInt();
    else
      val = def;
  }

  void  readVal(const Json::Value& parent, const std::string& name,
                Float_t& val, const Float_t& def)
  {
    if (parent.isMember(name) && parent[name].isDouble())
      val = parent[name].asDouble();
    else
      val = def;
  }

  void  readVal(const Json::Value& parent, const std::string& name,
                Color& color, const Color& def)
  {
    if (parent.isMember(name))
    {
      if (parent[name].isObject())
      {
        const Json::Value& colorNode = parent[name];
        readVal(colorNode, "red", color.red(), def.red());
        readVal(colorNode, "green", color.green(), def.green());
        readVal(colorNode, "blue", color.blue(), def.blue());
        return;
      }
      else if (parent[name].isString())
      {
        const std::string str = parent[name].asString();
        if (colors().count(str))
        {
          color = colors().at(str);
          return;
        }
        else
          std::cout << "[Warning] Color `" << str << "` unknown. Skipping...\n";
      }
    }
    color = def;
  }

  void  readVal(const Json::Value& parent, const std::string& name,
                Vec_t& vec, const Vec_t& def)
  {
    if (parent.isMember(name) && parent[name].isObject())
    {
      const Json::Value& node = parent[name];
      readVal(node, "x", vec.x, def.x);
      readVal(node, "y", vec.y, def.y);
      readVal(node, "z", vec.z, def.z);
    }
    else
      vec = def;
  }
} // namespace Rayon
