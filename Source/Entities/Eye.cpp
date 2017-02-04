#include "Entities/Eye.hh"

namespace RayOn
{
  Eye::Eye()
  {
  }

  Eye::Eye(const Vec_t &pos, const Vec_t &rot)
    : Entity(pos, rot)
  {
  }

  Eye::Eye(Float_t x, Float_t y, Float_t z)
    : Entity(x, y, z)
  {
  }

  Eye::~Eye()
  {
  }
} // namespace RayOn
