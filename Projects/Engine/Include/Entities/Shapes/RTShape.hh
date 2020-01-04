#ifndef RAYON_RTOBJECT_HH_
#define RAYON_RTOBJECT_HH_

#include "BoundingBox.hh"
#include "Color.hh"
#include "Entities/Entity.hh"
#include "IntersectionData.hh"
#include "Material.hh"
#include "Ray.hh"

namespace Rayon
{
  class Material;
}

namespace Rayon
{
  class RTShape : public Entity
  {
  public:
    RTShape();
    RTShape(const Vec_t& pos, const Vec_t& rot);
    RTShape(Float_t x, Float_t y, Float_t z);
    virtual ~RTShape();

  public:
    void read(const Json::Value& root) override;
    void write(Json::Value& root) const override;

  public:
    virtual bool        inter(const Ray& ray, IntersectionData& data) const = 0;
    virtual void        preprocess()                                        = 0;
    virtual RTShape*    clone() const                                       = 0;
    virtual void        fillData(IntersectionData& data) const              = 0;
    virtual BoundingBox getBBox() const                                     = 0;
    virtual const char* name() const                                        = 0;
  };
}  // namespace Rayon

#endif  // RAYON_RTOBJECT_HH_
