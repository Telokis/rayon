#ifndef RAYON_ENTITY_HH_
#define RAYON_ENTITY_HH_

#include "Tools/Helpers.hh"
#include <Json-forwards.h>

namespace RayOn
{
  class   Entity
  {
  public:
    Entity();
    Entity(const Vec_t &pos,
           const Vec_t &rot);
    Entity(Float_t x, Float_t y, Float_t z);
    virtual ~Entity();

  public:
    void    computeRotation();
    void    computeDirectRotation();
    void    computeIndirectRotation();

  public:
    virtual void  read(const Json::Value& root);
    virtual void  write(Json::Value& root) const;

  public:
    Vec_t  directRotation(const Vec_t &Vec_t) const;
    Vec_t  indirectRotation(const Vec_t &Vec_t) const;

  public:
    RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(Entity, Pos)
    RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(Entity, Rot)

  protected:
    bool  _rotIsIdentity;
    Vec_t _pos;
    Vec_t _rot;
    Mat_t _directMatrix;
    Mat_t _indirectMatrix;
  };

} // namespace RayOn

#endif // RAYON_ENTITY_HH_
