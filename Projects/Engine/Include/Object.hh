#pragma once

#ifndef RAYON_OBJECT_HH_
#define RAYON_OBJECT_HH_

#include <yaml-cpp/node/node.h>

#include "Materials/RTMaterial.hh"

namespace Rayon
{
  class RTShape;
  class Ray;
  struct IntersectionData;

  class Object
  {
  public:
    Object(RTShape* = nullptr, RTMaterial* = nullptr);
    ~Object();
    Object(const Object& object);
    Object& operator=(const Object& object);
    Object(Object&& object);
    Object& operator=(Object&& object);

  public:
    const RTShape*    getShape() const;
    RTShape*          getShape();
    const RTMaterial* getMaterial() const;
    RTMaterial*       getMaterial();

    void setShape(RTShape* shape);
    void setMaterial(RTMaterial* material);

  public:
    bool inter(const Ray& ray, IntersectionData& data) const;

  public:
    bool read(const YAML::Node& root);
    void write(YAML::Node& root) const;

  private:
    RTShape*    _shape;
    RTMaterial* _material;
  };
}  // namespace Rayon

#endif  // RAYON_OBJECT_HH_
