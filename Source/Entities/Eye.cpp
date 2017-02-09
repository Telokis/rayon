#include "Entities/Eye.hh"

namespace RayOn
{
  Eye::Eye()
    : _fov(60)
  {
  }

  Eye::Eye(const Vec_t &pos, const Vec_t &rot)
    : Entity(pos, rot)
    , _fov(60)
  {
  }

  Eye::Eye(Float_t x, Float_t y, Float_t z)
    : Entity(x, y, z)
    , _fov(60)
  {
  }

  Eye::~Eye()
  {
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Eye, Float_t, _fov, Fov)
} // namespace RayOn
