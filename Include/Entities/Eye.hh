#ifndef RAYON_EYE_HH_
#define RAYON_EYE_HH_

#include "Entity.hh"

namespace RayOn
{
  class   Eye : public Entity
  {
  public:
    Eye();
    Eye(const Vec_t &pos,
        const Vec_t &rot);
    Eye(Float_t x, Float_t y, Float_t z);
    virtual ~Eye();

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Eye, Float_t, _fov, Fov)
  };
} // namespace RayOn

#endif // RAYON_EYE_HH_
