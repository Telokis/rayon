#include "Entities/Eye.hh"

namespace Rayon
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

  void Eye::read(const Json::Value& root)
  {
    Entity::read(root);
  }

  void Eye::write(Json::Value& root) const
  {
    Entity::write(root);
  }

} // namespace Rayon
