#include "KDTree.hh"

#include <algorithm>

#include "Entities/Shapes/RTShape.hh"
#include "Helpers/inVector.hh"
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

  bool KDTree::iterateIfIntersect(const Ray&                                            ray,
                                  IntersectionData&                                     data,
                                  std::function<bool(const Object*, IntersectionData&)> func) const
  {
    ++data.stat->treeBranchesExplored;

    if (left && right)
    {
      Float_t leftDist;
      Float_t rightDist;

      leftDist  = left->box.intersectRay(ray);
      rightDist = right->box.intersectRay(ray);

      if (leftDist != Globals::Invalid)
        if (!left->iterateIfIntersect(ray, data, func))
          return false;

      if (rightDist != Globals::Invalid)
        if (!right->iterateIfIntersect(ray, data, func))
          return false;
    }
    else
    {
      return Helpers::iterateIfIntersect(ray, data, objects, func);
    }

    return true;
  }

  Object* KDTree::getNearest(const Ray& ray, IntersectionData& data) const
  {
    ++data.stat->treeBranchesExplored;

    if (left && right)
    {
      Float_t          leftDist;
      Float_t          rightDist;
      IntersectionData closestMatch;
      IntersectionData farthestMatch;

      closestMatch.stat  = data.stat;
      farthestMatch.stat = data.stat;

      leftDist  = left->box.intersectRay(ray);
      rightDist = right->box.intersectRay(ray);

      if (leftDist != Globals::Invalid)
        left->getNearest(ray, closestMatch);

      if (rightDist != Globals::Invalid)
        right->getNearest(ray, farthestMatch);

      data = closestMatch.k < farthestMatch.k ? closestMatch : farthestMatch;
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

    if (objects.size() <= 10 || depth >= 100)
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