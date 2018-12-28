#include "Object.hh"

#include <Json.h>

#include "Entities/Shapes/RTShape.hh"
#include "IntersectionData.hh"
#include "Ray.hh"
#include "Registry.hh"

namespace Rayon
{
  Object::Object(RTShape* shape) : _shape(shape)
  {
  }

  Object::~Object()
  {
    delete _shape;
  }

  Object::Object(const Object& object) : _shape(object._shape->clone()), _material(object._material)
  {
  }

  Object& Object::operator=(const Object& object)
  {
    delete _shape;
    _shape    = object._shape->clone();
    _material = object._material;
    return *this;
  }

  Object::Object(Object&& object)
    : _shape(std::exchange(object._shape, nullptr)), _material(object._material)
  {
  }

  Object& Object::operator=(Object&& object)
  {
    delete _shape;
    _shape    = std::exchange(object._shape, nullptr);
    _material = object._material;
    return *this;
  }

  const RTShape* Object::getShape() const
  {
    return _shape;
  }

  const Material Object::getMaterial() const
  {
    return _material;
  }

  RTShape* Object::getShape()
  {
    return _shape;
  }

  void Object::setShape(RTShape* shape)
  {
    delete _shape;
    _shape = shape;
  }

  void Object::setMaterial(Material material)
  {
    _material = material;
  }

  bool Object::read(const Json::Value& root)
  {
    if (root.isMember("type") && root["type"].isString())
    {
      std::string         name = root["type"].asString();
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
    _material.read(root["material"]);
    return true;
  }

  void Object::write(Json::Value& root) const
  {
    _shape->write(root);
    _material.write(root["material"]);
  }

  bool Object::inter(const Ray& ray, IntersectionData& data) const
  {
    if (getMaterial().testFlag(ray.getType()))
      return false;
    return _shape->inter(ray, data);
  }
}  // namespace Rayon
