#ifndef RAYON_RTLIGHT_HH_
#define RAYON_RTLIGHT_HH_

#include "Entities/Entity.hh"
#include "Color.hh"
#include "Entities/Objects/RTObject.hh"

namespace RayOn
{
  class Scene;
} // namespace RayOn

namespace RayOn
{
  class   RTLight : public Entity
  {
  public:
    explicit RTLight(const Color &color = 0xffffffff);
    RTLight(const Vec_t &pos,
            const Vec_t &rot,
            const Color &color = 0xffffffff);
    RTLight(Float_t x, Float_t y, Float_t z,
            const Color &color = 0xffffffff);
    virtual ~RTLight();

  protected:
    /**
    * @brief       Internally used to check shadows.
    *              Iterates through all objects in the given @a scene
    *              and tests if there is an object between @a point and
    *              the @ref Sun's position.
    * @param scene The scene to use to retrieve @ref RTObject.
    * @param point The point from which we should "look".
    * @return      True if an opaque object is in the way.
    *              False if no opaque object were found.
    */
    bool    doesShadow(const Vec_t& pos,
                       const Scene& scene,
                       const Vec_t& point,
                       RTObject* obj) const;

  public:
    void    read(const Json::Value& root) override;
    void    write(Json::Value& root) const override;

  public:
    virtual void        preprocess() = 0;
    virtual RTLight     *clone() const = 0;
    virtual Color       apply(const Color& color,
                              const Scene& scene,
                              const IntersectionData& data) const = 0;
    virtual const char* name() const = 0;

    RAYON_GENERATE_PROPERTY_DECLARATION(RTLight, Color, _color, Color)
  };
} // namespace RayOn

#endif // RAYON_RTLIGHT_HH_
