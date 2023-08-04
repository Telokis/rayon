#include "Object.hh"

#include <yaml-cpp/yaml.h>

#include "Entities/Shapes/RTShape.hh"
#include "IntersectionData.hh"
#include "Materials/Plain.hh"
#include "Ray.hh"
#include "Registry.hh"
#include "SceneParse.hh"

namespace Rayon
{
  Object::Object(RTShape* shape, RTMaterial* material) : _shape(shape), _material(material)
  {
  }

  Object::~Object()
  {
    delete _shape;
  }

  Object::Object(const Object& object)
    : _shape(object._shape->clone()), _material(object._material->clone())
  {
  }

  Object& Object::operator=(const Object& object)
  {
    delete _shape;

    _shape    = object._shape->clone();
    _material = object._material->clone();

    return *this;
  }

  Object::Object(Object&& object)
    : _shape(std::exchange(object._shape, nullptr))
    , _material(std::exchange(object._material, nullptr))
  {
  }

  Object& Object::operator=(Object&& object)
  {
    delete _shape;
    delete _material;

    _shape    = std::exchange(object._shape, nullptr);
    _material = std::exchange(object._material, nullptr);

    return *this;
  }

  const RTShape* Object::getShape() const
  {
    return _shape;
  }

  RTShape* Object::getShape()
  {
    return _shape;
  }

  const RTMaterial* Object::getMaterial() const
  {
    return _material;
  }

  RTMaterial* Object::getMaterial()
  {
    return _material;
  }

  void Object::setShape(RTShape* shape)
  {
    delete _shape;
    _shape = shape;
  }

  void Object::setMaterial(RTMaterial* material)
  {
    _material = material;
  }

  bool Object::read(const YAML::Node& root)
  {
    if (root["type"] && isString(root["type"]))
    {
      auto                name = root["type"].as<std::string>();
      const IMetaRTShape* meta = registry().getMetaRTShape(name);

      if (meta)
      {
        _shape = meta->make();
        _shape->read(root);
      }
      else
      {
        std::cout << "[Warning] Unknown type `" << name << "` for object. Skipping...\n";
        return false;
      }
    }
    else
    {
      std::cout << "[Warning] Invalid `type` for object. Skipping...\n";
      return false;
    }

    readMaterial(root["material"], _material);

    return true;
  }

  void Object::write(YAML::Node root) const
  {
    _shape->write(root);

    auto material = root["material"];

    _material->write(material);
  }

  bool Object::inter(const Ray& ray, IntersectionData& data) const
  {
    if (getMaterial()->testFlag(ray.getType()))
      return false;

    return _shape->inter(ray, data);
  }
}  // namespace Rayon
