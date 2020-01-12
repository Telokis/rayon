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

    bool testFlagImpl(Flags flag) const
    {
      return false;
    }

    Float_t getReflexionImpl(const IntersectionData& data, uint32 depth) const
    {
      return 0;
    }

    Float_t getTransparencyImpl(const IntersectionData& data, uint32 depth) const
    {
      return 0;
    }

    Float_t getRefractionImpl(const IntersectionData& data, uint32 depth) const
    {
      return 1;
    }

    Float_t getGlossinessImpl(const IntersectionData& data, uint32 depth) const
    {
      return 0;
    }

    Float_t getShininessImpl(const IntersectionData& data, uint32 depth) const
    {
      return 0;
    }

  public:
    Color getColor(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getColorImpl(data, depth);
    }

    Float_t getReflexion(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getReflexionImpl(data, depth);
    }

    Float_t getTransparency(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getTransparencyImpl(data, depth);
    }

    Float_t getRefraction(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getRefractionImpl(data, depth);
    }

    Float_t getGlossiness(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getGlossinessImpl(data, depth);
    }

    Float_t getShininess(const IntersectionData& data, uint32 depth) const final
    {
      return static_cast<Derived const*>(this)->getShininessImpl(data, depth);
    }

  public:
    RTMaterial* clone() const final
    {
      return new Derived(static_cast<Derived const&>(*this));
    }

    bool testFlag(Flags flag) const final
    {
      return static_cast<Derived const*>(this)->testFlagImpl(flag);
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
