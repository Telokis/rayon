#ifndef RAYON_EYE_HH_
#define RAYON_EYE_HH_

#include "Entity.hh"

namespace Rayon
{
  class   Eye : public Entity
  {
  public:
    Eye();
    Eye(const Vec_t &pos,
        const Vec_t &rot);
    Eye(Float_t x, Float_t y, Float_t z);
    virtual ~Eye();

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  private:
  };
} // namespace Rayon

#endif // RAYON_EYE_HH_
