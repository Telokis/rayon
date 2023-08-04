#include "SceneParse.hh"

#include <yaml-cpp/yaml.h>

#include <fstream>

#include "Entities/Lights/RTLight.hh"
#include "Materials/Plain.hh"
#include "Object.hh"
#include "Registry.hh"
#include "Scene.hh"

namespace Rayon
{
  namespace
  {
    void parseSpecString(const std::string& content, YAML::Node& root)
    {
      root = YAML::Load(content);
    }

    void parseSpecFile(const std::string& path, YAML::Node& root)
    {
      root = YAML::LoadFile(path);
    }

    void writeSpecFile(const std::string& path, YAML::Node root)
    {
      std::ofstream file(path);

      if (!file.is_open())
        throw std::runtime_error("Unable to open `" + path + "`");

      file << root;
    }

    void populateScene(Scene& scene, const YAML::Node& root, const std::string& filename = "")
    {
      if (root["eye"] && root["eye"].IsMap())
      {
        Eye eye;

        eye.read(root["eye"]);
        scene.setEye(eye);
      }

      if (root["cubemap"] && root["cubemap"].IsMap())
      {
        CubeMap cubemap;

        cubemap.setSourceFilename(filename);
        cubemap.read(root["cubemap"]);
        scene.setCubeMap(cubemap);
      }

      if (root["objects"] && root["objects"].IsSequence())
      {
        const YAML::Node& objects = root["objects"];

        for (const YAML::Node& object : objects)
        {
          Object obj;

          if (obj.read(object))
          {
            scene.addObject(obj);
          }
        }
      }

      if (root["lights"] && root["lights"].IsSequence())
      {
        const YAML::Node& lights = root["lights"];

        for (const YAML::Node& light : lights)
        {
          if (light["type"] && isString(light["type"]))
          {
            std::string         name = light["type"].as<std::string>();
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
          {
            std::cout << "[Warning] Invalid `type` for light. Skipping...\n";
          }
        }
      }
    }
  }  // namespace

  bool isString(const YAML::Node& node)
  {
    try
    {
      auto str = node.as<std::string>();
      return true;
    }
    catch (...)
    {
      return false;
    }
  };

  bool isUint32(const YAML::Node& node)
  {
    try
    {
      auto str = node.as<uint32>();
      return true;
    }
    catch (...)
    {
      return false;
    }
  };

  bool isDouble(const YAML::Node& node)
  {
    try
    {
      auto str = node.as<Float_t>();
      return true;
    }
    catch (...)
    {
      return false;
    }
  };

  void readSceneFromFile(Scene& scene, const std::string& filename)
  {
    YAML::Node root;

    parseSpecFile(filename, root);
    populateScene(scene, root, filename);
  }

  void readSceneFromString(Scene& scene, const std::string& content)
  {
    YAML::Node root;

    parseSpecString(content, root);
    populateScene(scene, root);
  }

  void sceneWrite(const Scene& scene, const std::string& filename)
  {
    YAML::Node root;

    scene.eye().write(root["eye"]);
    scene.cubemap().write(root["cubemap"]);
    YAML::Node lights = root["lights"];

    for (const auto& light : scene.lights())
    {
      YAML::Node val;
      val["type"] = light->name();
      light->write(val);
      lights.push_back(val);
    }

    YAML::Node objects = root["objects"];
    for (const Object* obj : scene.objects())
    {
      YAML::Node val;
      val["type"] = obj->getShape()->name();
      obj->write(val);
      objects.push_back(val);
    }

    writeSpecFile(filename, root);
  }

  void readMaterial(const YAML::Node& root, RTMaterial*& material)
  {
    material = nullptr;

    if (root.IsMap() && isString(root["type"]))
    {
      auto                   name = root["type"].as<std::string>();
      const IMetaRTMaterial* meta = registry().getMetaRTMaterial(name);

      if (meta)
      {
        material = meta->make();
        material->read(root);
      }
      else
      {
        std::cout << "[Warning] Unknown type `" << name << "` for material. Forcing Plain...\n";

        material = new Plain;
        material->read(root);
      }
    }
    else
    {
      std::cout << "[Warning] Unspecified Material type. Assuming Plain...\n";

      material = new Plain;
      material->read(root);
    }
  }

  void writeMaterial(YAML::Node root, const RTMaterial* material)
  {
    material->write(root);
  }

  /*
   *  Write
   */
  void writeVal(YAML::Node node, const std::string& name, const Float_t& val, const Float_t& def)
  {
    node[name] = static_cast<double>(val);
  }

  void writeVal(YAML::Node node, const std::string& name, const uint32& val, const uint32& def)
  {
    node[name] = val;
  }

  void writeVal(YAML::Node node, const std::string& name, const Color& color, const Color& def)
  {
    YAML::Node subNode = node[name];
    const auto  value   = color.intValue();
    const auto& cols    = namedColors();

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

  void writeVal(YAML::Node node, const std::string& name, const Vec_t& vec, const Vec_t& def)
  {
    YAML::Node subNode = node[name];

    writeVal(subNode, "x", vec.x, def.x);
    writeVal(subNode, "y", vec.y, def.y);
    writeVal(subNode, "z", vec.z, def.z);
  }

  /*
   *  Read
   */
  void readVal(const YAML::Node& parent, const std::string& name, uint32& val, const uint32& def)
  {
    if (parent[name] && isUint32(parent[name]))
      val = parent[name].as<uint32>();
    else
      val = def;
  }

  void readVal(const YAML::Node& parent, const std::string& name, Float_t& val, const Float_t& def)
  {
    if (parent[name] && isDouble(parent[name]))
      val = parent[name].as<Float_t>();
    else
      val = def;
  }

  void readVal(const YAML::Node& parent, const std::string& name, Color& color, const Color& def)
  {
    if (parent[name])
    {
      if (parent[name].IsMap())
      {
        const YAML::Node& colorNode = parent[name];
        uint32            red;
        uint32            green;
        uint32            blue;

        readVal(colorNode, "red", red, def.red());
        readVal(colorNode, "green", green, def.green());
        readVal(colorNode, "blue", blue, def.blue());

        color.setRed(red);
        color.setGreen(green);
        color.setBlue(blue);

        return;
      }
      else if (isString(parent[name]))
      {
        const std::string str = parent[name].as<std::string>();

        if (namedColors().count(str))
        {
          color = namedColors().at(str);
          return;
        }
        else
          std::cout << "[Warning] Color `" << str << "` unknown. Skipping...\n";
      }
    }
    color = def;
  }

  void readVal(const YAML::Node& parent, const std::string& name, Vec_t& vec, const Vec_t& def)
  {
    if (parent[name] && parent[name].IsMap())
    {
      const YAML::Node& node = parent[name];

      readVal(node, "x", vec.x, def.x);
      readVal(node, "y", vec.y, def.y);
      readVal(node, "z", vec.z, def.z);
    }
    else
      vec = def;
  }
}  // namespace Rayon
