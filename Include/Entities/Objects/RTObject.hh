#ifndef RAYON_RTOBJECT_HH_
#define RAYON_RTOBJECT_HH_

#include "Entities/Entity.hh"
#include "Color.hh"
#include "Ray.hh"
#include "Material.hh"
#include "IntersectionData.hh"

namespace RayOn
{
  class Material;
}

namespace RayOn
{
  class   RTObject : public Entity
  {
  public:
    RTObject();
    RTObject(const Vec_t& pos,
             const Vec_t& rot);
    RTObject(Float_t x, Float_t y, Float_t z);
    virtual ~RTObject();

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  public:
    virtual bool        inter(const Ray& ray, IntersectionData& data) const = 0;
    virtual void        preprocess() = 0;
    virtual RTObject*   clone() const = 0;
    virtual void        fillData(IntersectionData& data) const = 0;
    virtual const char* name() const = 0;

  protected:
    Material  _material;

  public:
    void  setMaterial(const Material& material);
    Material& getMaterial();
    const Material& getMaterial() const;
  };
} // namespace RayOn

#endif // RAYON_RTOBJECT_HH_
