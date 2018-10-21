#include "KDTree.hh"

#include <algorithm>

#include "Entities/Shapes/RTShape.hh"
#include "Helpers/getNearestInVector.hh"
#include "Object.hh"

namespace Rayon
{
  KDTree::KDTree() : left{nullptr}, right{nullptr}
  {
  }

  KDTree::~KDTree()
  {
    delete left;
    delete right;
  }

  Object* KDTree::getNearest(const Ray& ray, IntersectionData& data) const
  {
    ++data.stat->treeBranchesExplored;

    if (left && right)
    {
      Float_t          closestDist;
      Float_t          farthestDist;
      IntersectionData closestMatch;
      KDTree*          close;
      KDTree*          far;

      closestMatch.stat = data.stat;

      closestDist  = left->box.intersectRay(ray);
      farthestDist = right->box.intersectRay(ray);

      close = left;
      far   = right;

      if (farthestDist < closestDist)
      {
        std::swap(close, far);
        std::swap(closestDist, farthestDist);
      }

      if (closestDist != Globals::Invalid)
        close->getNearest(ray, closestMatch);

      if (closestMatch.obj == nullptr && farthestDist != Globals::Invalid)
        far->getNearest(ray, closestMatch);

      data = closestMatch;
    }
    else
    {
      Helpers::getNearestInVector(ray, data, objects);
    }

    return data.obj;
  }

  KDTree::KDTreePtr build(std::vector<Object*>& objects, uint32 depth)
  {
    auto   node = new KDTree();
    uint32 axis = 0;

    node->objects = objects;

    std::vector<Object*> sorted;
    sorted.reserve(objects.size());

    for (auto&& object : objects)
    {
      if (depth > 0 || !object->getShape()->getBBox().isInfinite())
      {
        node->box.expand(object->getShape()->getBBox());
        sorted.push_back(object);
      }
    }

    if (objects.size() <= 10)
      return node;

    axis = node->box.biggestAxis();

    std::sort(sorted.begin(), sorted.end(), [axis](const auto& obj1, const auto& obj2) {
      return obj1->getShape()->getPos()[axis] < obj2->getShape()->getPos()[axis];
    });

    auto    mid       = sorted.size() / 2;
    Object* median    = sorted.at(mid);
    auto    medianPos = median->getShape()->getPos()[axis];

    std::vector<Object*> left;
    std::vector<Object*> right;
    uint32               overlapping = 0;

    for (auto&& object : sorted)
    {
      auto bbox    = object->getShape()->getBBox();
      bool inLeft  = bbox.getMin()[axis] <= medianPos;
      bool inRight = bbox.getMax()[axis] >= medianPos;

      if (inLeft)
        left.push_back(object);

      if (inRight)
        right.push_back(object);

      if (inLeft && inRight)
        ++overlapping;
    }

    if (overlapping / static_cast<float>(sorted.empty() ? 1 : sorted.size()) < 0.5f)
    {
      node->left  = build(left, depth + 1);
      node->right = build(right, depth + 1);
    }

    return node;
  }

}  // namespace Rayon