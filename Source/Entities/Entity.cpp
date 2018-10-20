#include "Entities/Entity.hh"

#include <Json.h>

#include "SceneParse.hh"

namespace Rayon
{
  Entity::Entity() : _pos(0, 0, 0), _rot(0, 0, 0)
  {
  }

  Entity::Entity(const Vec_t& pos, const Vec_t& rot) : _pos(pos), _rot(rot)
  {
  }

  Entity::Entity(Float_t x, Float_t y, Float_t z) : _pos(x, y, z), _rot(0, 0, 0)
  {
  }

  Entity::~Entity()
  {
  }

  void Entity::computeRotation()
  {
    _rotIsIdentity = Tools::IsZero(_rot.x) && Tools::IsZero(_rot.y) && Tools::IsZero(_rot.z);
    _rot.x         = Tools::DegToRad(_rot.x);
    _rot.y         = Tools::DegToRad(_rot.y);
    _rot.z         = Tools::DegToRad(_rot.z);
    computeDirectRotation();
    computeIndirectRotation();
  }

  void Entity::computeDirectRotation()
  {
    using std::cos;
    using std::sin;

    Vec_t c(cos(-1 * _rot.x), cos(-1 * _rot.y), cos(-1 * _rot.z));
    Vec_t s(sin(-1 * _rot.x), sin(-1 * _rot.y), sin(-1 * _rot.z));

    _directMatrix[0][0] = c.y * c.z;
    _directMatrix[1][0] = c.y * s.z;
    _directMatrix[2][0] = -1 * s.y;
    _directMatrix[0][1] = -1 * c.x * s.z + s.x * s.y * c.z;
    _directMatrix[1][1] = c.x * c.z + s.x * s.y * s.z;
    _directMatrix[2][1] = s.x * c.y;
    _directMatrix[0][2] = s.x * s.z + c.x * s.y * c.z;
    _directMatrix[1][2] = -1 * s.x * c.z + c.x * s.y * s.z;
    _directMatrix[2][2] = c.x * c.y;
  }

  void Entity::computeIndirectRotation()
  {
    using std::cos;
    using std::sin;

    Vec_t c(cos(_rot.x), cos(_rot.y), cos(_rot.z));
    Vec_t s(sin(_rot.x), sin(_rot.y), sin(_rot.z));

    _indirectMatrix[0][0] = c.y * c.z;
    _indirectMatrix[1][0] = c.x * s.z + c.z * s.x * s.y;
    _indirectMatrix[2][0] = s.x * s.z - c.x * c.z * s.y;
    _indirectMatrix[0][1] = -1 * c.y * s.z;
    _indirectMatrix[1][1] = c.x * c.z - s.x * s.y * s.z;
    _indirectMatrix[2][1] = s.x * c.z + c.x * s.y * s.z;
    _indirectMatrix[0][2] = s.y;
    _indirectMatrix[1][2] = -1 * c.y * s.x;
    _indirectMatrix[2][2] = c.x * c.y;
  }

  void Entity::read(const Json::Value& root)
  {
    readVal(root, "position", _pos, {0, 0, 0});
    readVal(root, "rotation", _rot, {0, 0, 0});
  }

  void Entity::write(Json::Value& root) const
  {
    writeVal(root, "position", _pos, {0, 0, 0});
    writeVal(root, "rotation", _rot, {0, 0, 0});
  }

  Vec_t Entity::directRotation(const Vec_t& vec) const
  {
    if (_rotIsIdentity)
      return vec;
    return vec * _directMatrix;
  }

  Vec_t Entity::indirectRotation(const Vec_t& vec) const
  {
    if (_rotIsIdentity)
      return vec;
    return vec * _indirectMatrix;
  }

  RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(Entity, _pos, Pos);
  RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(Entity, _rot, Rot);

}  // namespace Rayon