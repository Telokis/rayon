#ifndef AMBIANT_HH
#define AMBIANT_HH

/** \file Ambiant.h
 * Describes the @ref Ambiant class.
 */

#include "Entities/Lights/Light.h"

/**
 * @brief   The @ref Ambiant class represents an homogeneous
 *          light affecting each point of the scene.
 *          Thus, the position and orientation of the light
 *          doesn't matter at all.
 */
class   Ambiant : public Light<Ambiant>
{
    typedef Light<Ambiant> ParentType;  /**< Typedef for easier access to parent's type */
    friend  ParentType;                 /**< Required for CRTP used by @ref Light */

public:
    /**
     * @brief   Default constructor, lets the parent choose
     *          default position/rotation and sets the power
     *          to 0.5.
     */
    Ambiant();

    /**
     * @brief   Destructor. Doesn't do anything.
     */
    ~Ambiant();

private:
    /**
     * @brief   This is the display name of the @ref RTLight.
     * @see     RTLight::name
     */
    static const char   *LightName;

private:
    /**
     * @brief           This method writes the informations of the
     *                  @ref RTLight to the given XML Node.
     * @param[out] node The current node representing the @ref RTLight
     *                  in the xml file.
     */
    virtual void    serialize(QDomElement &node) const Q_DECL_OVERRIDE;

    /**
     * @brief           This method transforms the given @a color
     *                  to "apply" the light on it. For the @ref Ambiant
     *                  light, it simply @ref Color::interpolate between
     *                  the light's color and the @a color based on the
     *                  light's power.
     * @param[in] color The color to transform.
     * @param[in] scene Ignored for @ref Ambiant light.
     * @param[in] obj   Ignored for @ref Ambiant light.
     * @param[in] point Ignored for @ref Ambiant light.
     * @return          The transformed color.
     */
    Color   applyImpl(const Color &color,
                      const Scene &scene,
                      RTObject *obj,
                      const Vec_t &point) const;

    RT_GENERATE_PROPERTY_DECLARATION(Ambiant, Float_t, _power, Power)
};

#endif // AMBIANT_HH

