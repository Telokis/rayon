#ifndef RAYON_MOBIUS_HH_
#define RAYON_MOBIUS_HH_

#include <vector>

#include "Entities/Shapes/Shape.hh"

namespace Rayon
{
  class KDTree;
  class RTShape;
  class Object;
}  // namespace Rayon

namespace Rayon
{
  class Mobius : public Shape<Mobius>
  {
    typedef Shape<Mobius> ParentType;
    friend ParentType;

  public:
    Mobius();
    Mobius(const Vec_t& pos, const Vec_t& rot);
    Mobius(Float_t x, Float_t y, Float_t z);
    ~Mobius();

  public:
    void read(const YAML::Node& root) override;
    void write(YAML::Node root) const override;

  private:
    std::vector<Object*> _facets;
    mutable Object*      _last   = nullptr;
    KDTree*              _kdtree = nullptr;

  public:
    static const constexpr auto ShapeName = "Mobius";

  private:
    bool        interImpl(const Ray& ray, IntersectionData& data) const;
    void        fillDataImpl(IntersectionData& data) const;
    void        preprocessImpl();
    BoundingBox getBBoxImpl() const;

    RAYON_GENERATE_PROPERTY_DECLARATION(Mobius, uint32, _torsion, Torsion);
    RAYON_GENERATE_PROPERTY_DECLARATION(Mobius, Float_t, _width, Width);
  };

}  // namespace Rayon

#endif  // RAYON_MOBIUS_HH_
