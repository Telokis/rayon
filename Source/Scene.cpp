#include "Scene.hh"
#include "IntersectionData.hh"
#include "Entities/Lights/RTLight.hh"
#include <iostream>

namespace RayOn
{
  Scene::Scene()
    : _eye(nullptr)
    , _cubemap(nullptr)
    , _ambient(0.2)
  {
  }

  Scene::Scene(const Scene& other)
    : _eye(nullptr)
    , _cubemap(nullptr)
    , _ambient(other._ambient)
  {
    if (other._eye)
      _eye = new Eye(*other._eye);
    if (other._cubemap)
      _cubemap = new CubeMap(*other._cubemap);
    for (auto& object : other._objects)
      _objects.push_back(object->clone());
    for (auto& light : other._lights)
      _lights.push_back(light->clone());
  }

  Scene&  Scene::operator=(const Scene& other)
  {
    if (this != &other)
    {
      _ambient = other._ambient;
      if (other._eye)
        _eye = new Eye(*other._eye);
      if (other._cubemap)
        _cubemap = new CubeMap(*other._cubemap);
      for (auto&& object : other._objects)
        _objects.push_back(object->clone());
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
    other._eye = nullptr;
    other._cubemap = nullptr;
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
      other._eye = nullptr;
      other._cubemap = nullptr;
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
    delete _eye;
    delete _cubemap;
  }

  void    Scene::addObject(RTObject* object)
  {
    _objects.push_back(object);
  }

  RTObject*   Scene::lastObject() const
  {
    return (_objects.empty() ?
            nullptr :
            _objects.back());
  }

  auto Scene::objects() const -> const ObjectsContainer&
  {
      return _objects;
  }

    RTObject*   Scene::getNearest(const Ray& ray,
                                  IntersectionData& data) const
  {
    RTObject* result = nullptr;
    Float_t   k_tmp;

    data.k = Globals::Invalid;
    k_tmp = Globals::Invalid;
    for (RTObject* item : _objects)
    {
      bool res = item->inter(ray, data);
      if (res && data.k < k_tmp)
      {
        k_tmp = data.k;
        result = item;
      }
      else
        data.k = k_tmp;
    }
    return result;
  }

  void        Scene::setEye(Eye* eye)
  {
    _eye = eye;
  }

  Eye*        Scene::eye() const
  {
    return _eye;
  }

  void Scene::setCubeMap(CubeMap* cubemap)
  {
    _cubemap = cubemap;
  }

  CubeMap* Scene::cubemap() const
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

  Color   Scene::processLights(const IntersectionData& data) const
  {
    const Color color = data.material->getColor();
    Color result;
    for (size_t i = 0; i < _lights.size(); ++i)
      result += _lights[i]->apply(color, *this, data);
    return result;
  }

  void        Scene::preprocess()
  {
    for (auto& item : _objects)
    {
      item->preprocess();
      item->computeRotation();
    }
    for (auto& item : _lights)
    {
      item->preprocess();
      item->computeRotation();
    }
    if (_eye)
    {
      _eye->computeRotation();
    }
    _colors.resize(_lights.size());
  }

  Scene&   Scene::operator<<(RTObject* object)
  {
    addObject(object);
    return *this;
  }

  Scene&    Scene::operator<<(RTLight* light)
  {
    addLight(light);
    return *this;
  }

  Scene&    Scene::operator<<(Eye* eye)
  {
    setEye(eye);
    return *this;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Scene, Float_t, _ambient, Ambient)
} // namespace RayOn
