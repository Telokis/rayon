#include "KDTree.hh"

#include <algorithm>

#include "Entities/Shapes/RTShape.hh"
#include "Object.hh"

namespace Rayon
{
  KDTree::KDTree() : left{nullptr}, right{nullptr}
  {
  }

  KDTree::KDTreePtr build(std::vector<Object*>& objects, uint32 depth)
  {
    auto node = std::make_unique<KDTree>();
    auto axis = depth % 3;

    node->objects = objects;
    if (objects.size() <= 5)
      return node;

    std::vector<Object*> sorted;
    sorted.reserve(objects.size());

    for (auto&& object : objects)
    {
      if (depth == 0 && !object->getShape()->getBBox().isInfinite())
      {
        auto it = std::lower_bound(
          sorted.begin(), sorted.end(), object, [axis](const auto& obj1, const auto& obj2) {
            return obj1->getShape()->getPos()[axis] < obj2->getShape()->getPos()[axis];
          });

        sorted.insert(it, object);
        node->box.expand(object->getShape()->getBBox());
      }
    }

    auto    mid       = sorted.size() / 2;
    Object* median    = sorted.at(mid);
    auto    medianPos = median->getShape()->getPos()[axis];

    std::vector<Object*> left;
    std::vector<Object*> right;

    for (auto&& object : sorted)
    {
      auto bbox = object->getShape()->getBBox();

      if (bbox.getMin()[axis] <= medianPos)
        left.push_back(object);

      if (bbox.getMax()[axis] >= medianPos)
        right.push_back(object);
    }

    node->left  = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
  }

}  // namespace Rayon