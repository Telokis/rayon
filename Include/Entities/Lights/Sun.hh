#ifndef RAYON_SUN_HH_
#define RAYON_SUN_HH_
/** \file Sun.hh
 * Describes the @ref Sun class.
 */

#include "Entities/Lights/Light.hh"

namespace RayOn
{
  /**
   * @brief   The @ref Sun class represents a point light
   *          with an infinite range.
   *          For this @ref Entity, the rotation doesn't
   *          matter.
   */
  class   Sun : public Light<Sun>
  {
    typedef Light<Sun> ParentType;  /**< Typedef for easier access to parent's type */
    friend  ParentType;             /**< Required for CRTP used by @ref Light */

  public:
    /**
     * @brief   Default constructor, lets the parent choose
     *          default position/rotation and sets the power
     *          to 0.5.
     */
    Sun();

    /**
     * @brief   Vec_t constructor. Sets the position to
     *          @a pos and the power to 0.5.
     * @param[in] pos   The desired position for the @ref Entity.
     */
    Sun(const Vec_t& pos);

    /**
     * @brief   Coordinates constructor. Sets the position to
     *          @a x, @a y, @a z and the power to 0.5.
     * @param[in] x   The desired x position for the @ref Entity.
     * @param[in] y   The desired y position for the @ref Entity.
     * @param[in] z   The desired z position for the @ref Entity.
     */
    Sun(Float_t x, Float_t y, Float_t z);

    /**
     * @brief   Destructor. Doesn't do anything.
     */
    ~Sun();

  private:
    /**
     * @brief   This is the display name of the @ref RTLight.
     * @see     RTLight::name
     */
    static const constexpr auto LightName = "Soleil";

  private:
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
    bool    doesShadow(const Scene& scene,
                       const Vec_t& point,
                       RTObject* obj) const;

    /**
     * @brief           This method transforms the given @a color
     *                  to "apply" the light on it.
     *                  For the @ref Sun light, it first test
     *                  for a shadowing object using @ref Sun::doesShadow.
     *                  If no objects obstructs the light,
     *                  it calculates the angle
     *                  between the object's normal Vec_t at the given
     *                  @a point and the light's Vec_t to determine the
     *                  @ref Color to use.
     * @param[in] color The color to transform.
     * @param[in] scene Used to determine if the light is obstructed or seen.
     * @param[in] obj   The touched object. Used to get its normal Vec_t.
     * @param[in] point The impact point.
     * @return          The transformed color.
     */
    Color   applyImpl(const Color& color,
                      const Scene& scene,
                      const IntersectionData& data) const;

    RAYON_GENERATE_PROPERTY_DECLARATION(Sun, Float_t, _power, Power)
  };
} // namespace RayOn

#endif // RAYON_SUN_HH_
