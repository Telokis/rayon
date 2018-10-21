#include "Helpers/getNearestInVector.hh"

namespace Rayon
{
  namespace Helpers
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
  }  // namespace Helpers
}  // namespace Rayon