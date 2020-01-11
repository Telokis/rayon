#ifndef RAYON_MATERIAL_HH_
#define RAYON_MATERIAL_HH_

#include "Materials/RTMaterial.hh"

namespace Rayon
{
  template <class Derived>
  class Material : public RTMaterial
  {
  public:
    virtual ~Material()
    {
    }

  protected:
    void preprocessImpl()
    {
    }

    bool testFlagImpl(Flags flag)
    {
      return false;
    }

  public:
    RTMaterial* clone() const final
    {
      return new Derived(static_cast<Derived const&>(*this));
    }

    bool testFlag(Flags flag) const
    {
      return static_cast<Derived const*>(this)->testFlagImpl(flag);
    }

    Color getColor(const Scene&            scene,
                   const Ray&              ray,
                   const IntersectionData& data,
                   uint8                   depth) const final
    {
      return static_cast<Derived const*>(this)->getColorImpl(scene, ray, data, depth);
    }

    void preprocess() final
    {
      static_cast<Derived*>(this)->preprocessImpl();
    }

    const char* name() const final
    {
      return Derived::MaterialName;
    }
  };
}  // namespace Rayon

#endif  // RAYON_MATERIAL_HH_
