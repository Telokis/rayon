#include "Scene.hh"

#include <iostream>

#include "Entities/Lights/RTLight.hh"
#include "Helpers/inVector.hh"
#include "IntersectionData.hh"
#include "KDTree.hh"
#include "Materials/Plain.hh"
#include "Object.hh"
#include "Tools/Stat.hh"
#include "Worker.hh"

namespace Rayon
{
  Scene::Scene() : _ambient(0.2), _kdtree(nullptr)
  {
  }

  Scene::Scene(const Scene& other)
    : _ambient(other._ambient), _eye(other._eye), _cubemap(other._cubemap), _kdtree(nullptr)
  {
    for (const Object* object : other._objects)
      _objects.push_back(new Object(*object));

    for (auto& light : other._lights)
      _lights.push_back(light->clone());
  }

  Scene& Scene::operator=(const Scene& other)
  {
    if (this != &other)
    {
      _ambient = other._ambient;
      _eye     = other._eye;
      _cubemap = other._cubemap;
      _kdtree  = nullptr;

      for (const Object* object : other._objects)
        _objects.push_back(new Object(*object));

      for (auto&& light : other._lights)
        _lights.push_back(light->clone());
    }

    return *this;
  }

  Scene::Scene(Scene&& other)
  {
    _eye          = other._eye;
    _cubemap      = other._cubemap;
    _ambient      = other._ambient;
    _objects      = std::move(other._objects);
    _lights       = std::move(other._lights);
    _kdtree       = other._kdtree;
    other._kdtree = nullptr;
  }

  Scene& Scene::operator=(Scene&& other)
  {
    if (this != &other)
    {
      _eye          = other._eye;
      _cubemap      = other._cubemap;
      _ambient      = other._ambient;
      _objects      = std::move(other._objects);
      _lights       = std::move(other._lights);
      _kdtree       = other._kdtree;
      other._kdtree = nullptr;
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

    delete _kdtree;
  }

  void Scene::addObject(const Object& object)
  {
    _objects.push_back(new Object(object));
  }

  Object* Scene::lastObject() const
  {
    return (_objects.empty() ? nullptr : _objects.back());
  }

  auto Scene::objects() const -> const ObjectsContainer&
  {
    return _objects;
  }

  Object* Scene::getNearest(const Ray& ray, IntersectionData& data) const
  {
    IntersectionData tmp;

    tmp.stat = data.stat;

    tmp.k = _kdtree->box.intersectRay(ray);

    if (tmp.k != Globals::Invalid)
      _kdtree->getNearest(ray, tmp);

    Helpers::getNearestInVector(ray, data, _infiniteObjects);

    if (tmp.k < data.k)
      data = tmp;

    return data.obj;
  }

  bool Scene::iterateIfIntersect(const Ray&                                            ray,
                                 IntersectionData&                                     data,
                                 std::function<bool(const Object*, IntersectionData&)> func) const
  {
    data.k = _kdtree->box.intersectRay(ray);

    if (data.k != Globals::Invalid)
      if (!_kdtree->iterateIfIntersect(ray, data, func))
        return false;

    return Helpers::iterateIfIntersect(ray, data, _infiniteObjects, func);
  }

  void Scene::setEye(const Eye& eye)
  {
    _eye = eye;
  }

  const Eye& Scene::eye() const
  {
    return _eye;
  }

  void Scene::setCubeMap(const CubeMap& cubemap)
  {
    _cubemap = cubemap;
  }

  const CubeMap& Scene::cubemap() const
  {
    return _cubemap;
  }

  void Scene::addLight(RTLight* light)
  {
    _lights.push_back(light);
  }

  RTLight* Scene::lastLight() const
  {
    return _lights.back();
  }

  auto Scene::lights() const -> const LightsContainer&
  {
    return _lights;
  }

  Color Scene::processLights(const IntersectionData& data, Color& specular) const
  {
    const Color color = data.obj->getMaterial()->getColor(data);
    Color       result;

    for (size_t i = 0; i < _lights.size(); ++i)
      result += _lights[i]->apply(color, *this, data, specular);

    return result;
  }

  void Scene::preprocess()
  {
    for (Object* object : _objects)
    {
      object->getShape()->computeRotation();
      object->getShape()->preprocess();
      object->getMaterial()->preprocess();

      if (object->getShape()->getBBox().isInfinite())
        _infiniteObjects.push_back(object);
    }

    for (auto& light : _lights)
    {
      light->computeRotation();
      light->preprocess();
    }

    _eye.computeRotation();

    _kdtree = build(_objects, 0);
  }

  Color Scene::inter(const Ray& ray, uint8 depth, Tools::Stat* stat) const
  {
    return Worker::inter(*this, ray, depth, stat);
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Scene, Float_t, _ambient, Ambient);
}  // namespace Rayon
