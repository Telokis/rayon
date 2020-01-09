#pragma once

#ifndef RAYON_OBJECT_HH_
#define RAYON_OBJECT_HH_

#include <yaml-cpp/node/node.h>

#include "Material.hh"

namespace Rayon
{
  class RTShape;
  class Ray;
  struct IntersectionData;

  class Object
  {
  public:
    Object(RTShape* = nullptr);
    ~Object();
    Object(const Object& object);
    Object& operator=(const Object& object);
    Object(Object&& object);
    Object& operator=(Object&& object);

  public:
    const RTShape* getShape() const;
    const Material getMaterial() const;
    Material*      getMaterialPtr();
    RTShape*       getShape();

    void setShape(RTShape* shape);
    void setMaterial(Material material);

  public:
    bool inter(const Ray& ray, IntersectionData& data) const;

  public:
    bool read(const YAML::Node& root);
    void write(YAML::Node& root) const;

  private:
    RTShape* _shape;
    Material _material;
  };
}  // namespace Rayon

#endif  // RAYON_OBJECT_HH_
