#include "Scene.hh"
#include "IntersectionData.hh"
#include "Entities/Lights/RTLight.hh"
#include "Object.hh"
#include <iostream>

namespace Rayon
{
  Scene::Scene()
    : _ambient(0.2)
  {
  }

  Scene::Scene(const Scene& other)
    : _ambient(other._ambient)
    , _eye(other._eye)
    , _cubemap(other._cubemap)
  {
    for (const Object* object : other._objects)
      _objects.push_back(new Object(*object));
    for (auto& light : other._lights)
      _lights.push_back(light->clone());
  }

  Scene&  Scene::operator=(const Scene& other)
  {
    if (this != &other)
    {
      _ambient = other._ambient;
      _eye = other._eye;
      _cubemap = other._cubemap;
      for (const Object* object : other._objects)
        _objects.push_back(new Object(*object));
      for (auto&& light : other._lights)
        _lights.push_back(light->clone());
    }
    return *this;
  }

  Scene::Scene(Scene&& other)
  {
    _eye = other._eye;
    _cubemap = other._cubemap;
    _ambient = other._ambient;
    _objects = std::move(other._objects);
    _lights = std::move(other._lights);
  }

  Scene&    Scene::operator=(Scene&& other)
  {
    if (this != &other)
    {
      _eye = other._eye;
      _cubemap = other._cubemap;
      _ambient = other._ambient;
      _objects = std::move(other._objects);
      _lights = std::move(other._lights);
    }
    return *this;
  }

  Scene::~Scene()
  {
    for (auto& item : _objects)
    {
      delete item;
      item = nullptr;
    }
    for (auto& item : _lights)
    {
      delete item;
      item = nullptr;
    }
  }

  void    Scene::addObject(const Object& object)
  {
    _objects.push_back(new Object(object));
  }

  Object*   Scene::lastObject() const
  {
    return (_objects.empty() ?
            nullptr :
            _objects.back());
  }

  auto Scene::objects() const -> const ObjectsContainer&
  {
      return _objects;
  }

  Object*   Scene::getNearest(const Ray& ray,
                              IntersectionData& data) const
  {
    Object* result = nullptr;
    IntersectionData  tmp;

    data.k = Globals::Invalid;
    tmp.k = Globals::Invalid;
    for (Object* item : _objects)
    {
      bool res = item->inter(ray, data);
      if (res && data.k < tmp.k)
      {
        tmp = data;
        result = item;
      }
      else
        data.k = tmp.k;
    }
    data = tmp;
    return result;
  }

  void        Scene::setEye(const Eye& eye)
  {
    _eye = eye;
  }

  const Eye&  Scene::eye() const
  {
    return _eye;
  }

  void Scene::setCubeMap(const CubeMap& cubemap)
  {
    _cubemap = cubemap;
  }

  const CubeMap&  Scene::cubemap() const
  {
    return _cubemap;
  }

  void        Scene::addLight(RTLight* light)
  {
    _lights.push_back(light);
  }

  RTLight*    Scene::lastLight() const
  {
    return _lights.back();
  }

  auto Scene::lights() const -> const LightsContainer&
  {
      return _lights;
  }

  Color   Scene::processLights(const IntersectionData& data,
                               Color& specular) const
  {
    const Color color = data.obj->getMaterial().getColor();
    Color result;
    for (size_t i = 0; i < _lights.size(); ++i)
      result += _lights[i]->apply(color, *this, data, specular);
    return result;
  }

  void        Scene::preprocess()
  {
    for (Object* item : _objects)
    {
      item->getShape()->computeRotation();
      item->getShape()->preprocess();
    }
    for (auto& item : _lights)
    {
      item->computeRotation();
      item->preprocess();
    }
    _eye.computeRotation();
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Scene, Float_t, _ambient, Ambient)
} // namespace Rayon
