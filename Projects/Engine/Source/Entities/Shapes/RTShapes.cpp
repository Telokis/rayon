#include <yaml-cpp/yaml.h>

#include "Entities/Shapes/RTShape.hh"
#include "SceneParse.hh"

namespace Rayon
{
  RTShape::RTShape()
  {
  }

  RTShape::RTShape(const Vec_t& pos, const Vec_t& rot) : Entity(pos, rot)
  {
  }

  RTShape::RTShape(Float_t x, Float_t y, Float_t z) : Entity(x, y, z)
  {
  }

  RTShape::~RTShape()
  {
  }

  void RTShape::read(const YAML::Node& root)
  {
    Entity::read(root);
  }

  void RTShape::write(YAML::Node& root) const
  {
    Entity::write(root);
  }

}  // namespace Rayon
