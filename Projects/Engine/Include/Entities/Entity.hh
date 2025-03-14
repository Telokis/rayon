#ifndef RAYON_ENTITY_HH_
#define RAYON_ENTITY_HH_

#include <yaml-cpp/node/node.h>

#include "Tools/Helpers.hh"

namespace Rayon
{
  class Entity
  {
  public:
    Entity();
    Entity(const Vec_t& pos, const Vec_t& rot);
    Entity(Float_t x, Float_t y, Float_t z);
    virtual ~Entity();

  public:
    void computeRotation();
    void computeDirectRotation();
    void computeIndirectRotation();

  public:
    virtual void read(const YAML::Node& root);
    virtual void write(YAML::Node root) const;

  public:
    Vec_t directRotation(const Vec_t& Vec_t) const;
    Vec_t indirectRotation(const Vec_t& Vec_t) const;

  public:
    RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(Entity, Pos);
    RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(Entity, Rot);

  protected:
    bool  _rotIsIdentity;
    Vec_t _pos;
    Vec_t _rot;
    Mat_t _directMatrix;
    Mat_t _indirectMatrix;
  };

}  // namespace Rayon

#endif  // RAYON_ENTITY_HH_
