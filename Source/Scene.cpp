#include "Scene.hh"
#include "Entities/Lights/RTLight.hh"
#include <iostream>

namespace RayOn
{
  Scene::Scene()
  {
    _eye = nullptr;
  }

  Scene::Scene(const Scene& other)
  {
    _eye = new Eye(*other._eye);
    for (auto& object : other._objects)
      _objects.push_back(object->clone());
    for (auto& light : other._lights)
      _lights.push_back(light->clone());
  }

  Scene&  Scene::operator=(const Scene& other)
  {
    if (this != &other)
    {
      if (other._eye)
        _eye = new Eye(*other._eye);
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
    _objects = std::move(other._objects);
    _lights = std::move(other._lights);
    other._eye = nullptr;
  }

  Scene&    Scene::operator=(Scene&& other)
  {
    if (this != &other)
    {
      _eye = other._eye;
      _objects = std::move(other._objects);
      _lights = std::move(other._lights);
      other._eye = nullptr;
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

  RTObject*   Scene::getNearest(Float_t& k,
                                const Ray& ray) const
  {
    Float_t     k_tmp;
    RTObject*   result = nullptr;

    k = Globals::Invalid;
    for (auto& item : _objects)
    {
      k_tmp = item->inter(ray);
      if (k_tmp != Globals::Invalid && k_tmp < k)
      {
        k = k_tmp;
        result = item;
      }
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

  Color   Scene::processLights(const Color& color,
                               RTObject* obj,
                               const Vec_t& point) const
  {
    for (size_t i = 0; i < _lights.size(); ++i)
      _colors[i] = _lights[i]->apply(color, *this, obj, point);
    return _lights.empty() ? Color(0xFF000000) : Color::average(_colors);
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
} // namespace RayOn
