#pragma once

#ifndef RAYON_OBJECT_HH_
#define RAYON_OBJECT_HH_

#include <Json-forwards.h>

#include "Material.hh"

namespace Rayon
{
  class RTShape;
  class Ray;
  struct IntersectionData;

  class Object
  {
  public:
    Object();
    ~Object();
    Object(const Object& object);
    Object& operator=(const Object& object);
    Object(Object&& object);
    Object& operator=(Object&& object);

  public:
    const RTShape* getShape() const;
    const Material getMaterial() const;
    RTShape*       getShape();

    void setShape(RTShape* shape);
    void setMaterial(Material material);

  public:
    bool inter(const Ray& ray, IntersectionData& data) const;

  public:
    bool read(const Json::Value& root);
    void write(Json::Value& root) const;

  private:
    RTShape* _shape;
    Material _material;
  };
}  // namespace Rayon

#endif  // RAYON_OBJECT_HH_
