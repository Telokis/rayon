#pragma once

#ifndef RAYON_TOOLS_KDTREE_HH_
#define RAYON_TOOLS_KDTREE_HH_

#include <memory>

#include "BoundingBox.hh"
#include "Scene.hh"

namespace Rayon
{
  class KDTree
  {
  public:
    KDTree();
    ~KDTree();

  public:
    using KDTreePtr = KDTree*;

  public:
    Object* getNearest(const Ray& ray, IntersectionData& data) const;

  public:
    std::vector<Object*> objects;
    BoundingBox          box;
    KDTreePtr            left;
    KDTreePtr            right;
  };

  KDTree::KDTreePtr build(std::vector<Object*>& objects, uint32 depth);

}  // namespace Rayon

#endif  // RAYON_TOOLS_KDTREE_HH_