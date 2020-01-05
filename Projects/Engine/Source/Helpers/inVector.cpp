#include "Helpers/inVector.hh"

namespace Rayon::Helpers
{
  Object* getNearestInVector(const Ray&                  ray,
                             IntersectionData&           data,
                             const std::vector<Object*>& objects)
  {
    Object*          result = nullptr;
    IntersectionData tmp;

    tmp.stat = data.stat;

    for (Object* object : objects)
    {
      ++(data.stat->intersectionsChecked);
      bool res = object->inter(ray, data);

      if (res && data.k < tmp.k)
      {
        tmp    = data;
        result = object;
      }
      else
        data.k = tmp.k;
    }

    data     = tmp;
    data.obj = result;

    return result;
  }

  bool iterateIfIntersect(const Ray&                                            ray,
                          IntersectionData&                                     data,
                          const std::vector<Object*>&                           objects,
                          std::function<bool(const Object*, IntersectionData&)> func)
  {
    for (Object* object : objects)
    {
      ++(data.stat->intersectionsChecked);

      if (object->inter(ray, data))
        if (!func(object, data))
          return false;
    }

    return true;
  }
}  // namespace Rayon::Helpers