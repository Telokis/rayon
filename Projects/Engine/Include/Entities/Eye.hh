#ifndef RAYON_EYE_HH_
#define RAYON_EYE_HH_

#include "Entity.hh"

namespace Rayon
{
  class Eye : public Entity
  {
  public:
    Eye();
    Eye(const Vec_t& pos, const Vec_t& rot);
    Eye(Float_t x, Float_t y, Float_t z);
    virtual ~Eye();

  public:
    void read(const YAML::Node& root) override;
    void write(YAML::Node root) const override;

  private:
  };
}  // namespace Rayon

#endif  // RAYON_EYE_HH_
