#ifndef RAYON_SCENE_HH_
#define RAYON_SCENE_HH_

#include "Entities/Objects/Plane.hh"
#include "Entities/Objects/Sphere.hh"
#include "Entities/Eye.hh"
#include "CubeMap.hh"
#include <vector>

namespace RayOn
{
  class   RTLight;
  struct  IntersectionData;
} // namespace RayOn

namespace RayOn
{
  /**
   * @brief   The Scene class is used to store lights,
   *          objects and eye for easier manipulation.
   *          The Scene is taking care of all pointers
   *          it holds, properly releasing memory on
   *          deletion.
   */
  class   Scene
  {
    typedef std::vector<RTObject*> ObjectsContainer;   /**< Typedef for the @ref RTObject container */
    typedef std::vector<RTLight*>  LightsContainer;    /**< Typedef for the @ref RTLight container */

  public:
    /**
     * @brief   Default constructor, will set eye
     *          to nullptr and won't contain neither
     *          lights nor objects.
     */
    Scene();

    /**
     * @brief       Copy constructor. Will clone
     *              every object/light/eye contained
     *              in @a other.
     * @param[in]   other   @ref Scene to copy data from.
     */
    Scene(const Scene& other);

    /**
     * @brief       Assignment operator. Will clone
     *              every object/light/eye contained
     *              in @a other.
     * @param[in]   other   @ref Scene to copy data from.
     */
    Scene&  operator=(const Scene& other);

    /**
     * @brief       Move constructor. Will take ownership
     *              of all pointers held by @a other,
     *              leaving @a other in a default state.
     * @param[in]   other   @ref Scene to move data from.
     */
    Scene(Scene&& other);

    /**
     * @brief       Move assignment operator.
     *              Will take ownership
     *              of all pointers held by @a other,
     *              leaving @a other in a default state.
     * @param[in]   other   @ref Scene to move data from.
     */
    Scene   &operator=(Scene&& other);

    /**
      * @brief  Destructor. Will delete all pointers held
      *         by the instance.
      */
    ~Scene();

  public:
    /**
     * @brief   Adds a new @ref RTObject into the Scene.
     *          The Scene will add the pointer as is (no
     *          RTObject::clone involved) and will take
     *          care of its deletion.
     * @param[in] object    The @ref RTObject to add to
     *                      the Scene.
     */
    void        addObject(RTObject* object);

    /**
     * @brief   Will return the last @ref RTObject added
     *          to the Scene.
     * @return  The last @ref RTObject added to the Scene
     *          or nullptr if no @ref RTObject is held.
     */
    RTObject*   lastObject() const;

    /**
     * @brief   Will return the @ref RTObject container to
     *          allow outside read access.
     * @return  A const reference on the container.
     */
    const ObjectsContainer& objects() const;

    /**
     * @brief       Will return the nearest @ref RTObject
     *              intersected for this @a origin and
     *              @a direction.
     * @param[in]   ray   The ray to shoot.
     * @param[out]  data  Data to be filled by the object.
     * @return      The nearest @ref RTObject found.
     *              nullptr if no intersection was found.
     *              nullptr if no @ref RTObject is in the Scene.
     */
    RTObject*   getNearest(const Ray& ray,
                           IntersectionData& data) const;

  public:
    /**
     * @brief           Will set the Scene's @ref Eye to @a eye.
     * @param[in] eye   The @ref Eye to store.
     */
    void        setEye(const Eye& eye);

    /**
     * @brief   Returns the @ref Eye held by the Scene.
     * @return  The @ref Eye held by the Scene.
     */
    const Eye&  eye() const;

  public:
    /**
     * @brief             Will set the Scene's @ref CubeMap to @a cubemap.
     * @param[in] cubemap The @ref CubeMap to store.
     */
    void        setCubeMap(const CubeMap& cubemap);

    /**
     * @brief   Returns the @ref CubeMap held by the Scene.
     * @return  The @ref CubeMap held by the Scene.
     */
    const CubeMap&  cubemap() const;

  public:
    /**
     * @brief           Adds a @ref RTLight to the Scene.
     * @param[in] light The @ref RTLight to add.
     */
    void        addLight(RTLight* light);

    /**
     * @brief   Returns the last @ref RTLight added to
     *          the Scene.
     * @return  The last @ref RTLight added to the Scene.
     */
    RTLight*    lastLight() const;

    /**
     * @brief   Will return the @ref RTLight container to
     *          allow outside read access.
     * @return  A const reference on the container.
     */
    const LightsContainer&  lights() const;

    /**
     * @brief   Processes all @ref RTLight to modify the
     *          @a color.
     *          Iterates over all @ref RTLight and determines
     *          if the light is hidden by a @ref RTObject by
     *          iterating over all objects stored.
     *          If no object hides the light, computes light's
     *          color influence. Otherwise, uses black for the
     *          current light.
     * @param[in] data The data.
     * @return  The computed color to use.
     */
    Color       processLights(const IntersectionData& data) const;

  public:
    /**
     * @brief   Preprocesses everything stored in the Scene.
     *          Preprocessing computes rotation matrix.
     */
    void        preprocess();

  public:
    /**
     * @brief   Adds an @ref RTObject to the Scene.
     * @param[in] object  The @ref RTObject to add.
     * @return  *this for chaining.
     * @see     Scene::addObject
     */
    Scene   &operator<<(RTObject* object);

    /**
     * @brief   Adds an @ref RTLight to the Scene.
     * @param[in] light The @ref RTLight to add.
     * @return  *this for chaining.
     * @see     Scene::addLight
     */
    Scene   &operator<<(RTLight* light);

  private:
    ObjectsContainer  _objects;   /**< Collection of @ref RTObject * */
    LightsContainer   _lights;    /**< Collection of @ref RTLight * */
    Eye               _eye;       /**< @ref Eye of the Scene */
    CubeMap           _cubemap;   /**< @ref CubeMap of the Scene */
    
    RAYON_GENERATE_PROPERTY_DECLARATION(Scene, Float_t, _ambient, Ambient)
  };
} // namespace RayOn

#endif // RAYON_SCENE_HH_

