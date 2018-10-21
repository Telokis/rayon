#ifndef RAYON_SCENE_HH_
#define RAYON_SCENE_HH_

#include <memory>
#include <vector>

#include "CubeMap.hh"
#include "Entities/Eye.hh"

namespace Rayon
{
  class RTLight;
  class Object;
  struct IntersectionData;
  class KDTree;
}  // namespace Rayon

namespace Rayon
{
  /**
   * @brief   The Scene class is used to store lights,
   *          objects and eye for easier manipulation.
   *          The Scene is taking care of all pointers
   *          it holds, properly releasing memory on
   *          deletion.
   */
  class Scene
  {
    typedef std::vector<Object*>  ObjectsContainer; /**< Typedef for the @ref Object container */
    typedef std::vector<RTLight*> LightsContainer;  /**< Typedef for the @ref RTLight container */

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
    Scene& operator=(const Scene& other);

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
    Scene& operator=(Scene&& other);

    /**
     * @brief  Destructor. Will delete all pointers held
     *         by the instance.
     */
    ~Scene();

  public:
    /**
     * @brief   Adds a new @ref Object into the Scene.
     *          The Scene will add the pointer as is (no
     *          Object::clone involved) and will take
     *          care of its deletion.
     * @param[in] object    The @ref Object to add to
     *                      the Scene.
     */
    void addObject(const Object& object);

    /**
     * @brief   Will return the last @ref Object added
     *          to the Scene.
     * @return  The last @ref Object added to the Scene
     *          or nullptr if no @ref Object is held.
     */
    Object* lastObject() const;

    /**
     * @brief   Will return the @ref Object container to
     *          allow outside read access.
     * @return  A const reference on the container.
     */
    const ObjectsContainer& objects() const;

    /**
     * @brief       Will return the nearest @ref Object
     *              intersected for this @a origin and
     *              @a direction.
     * @param[in]   ray   The ray to shoot.
     * @param[out]  data  Data to be filled by the object.
     * @return      The nearest @ref Object found.
     *              nullptr if no intersection was found.
     *              nullptr if no @ref Object is in the Scene.
     */
    Object* getNearest(const Ray& ray, IntersectionData& data) const;

  public:
    /**
     * @brief           Will set the Scene's @ref Eye to @a eye.
     * @param[in] eye   The @ref Eye to store.
     */
    void setEye(const Eye& eye);

    /**
     * @brief   Returns the @ref Eye held by the Scene.
     * @return  The @ref Eye held by the Scene.
     */
    const Eye& eye() const;

  public:
    /**
     * @brief             Will set the Scene's @ref CubeMap to @a cubemap.
     * @param[in] cubemap The @ref CubeMap to store.
     */
    void setCubeMap(const CubeMap& cubemap);

    /**
     * @brief   Returns the @ref CubeMap held by the Scene.
     * @return  The @ref CubeMap held by the Scene.
     */
    const CubeMap& cubemap() const;

  public:
    /**
     * @brief           Adds a @ref RTLight to the Scene.
     * @param[in] light The @ref RTLight to add.
     */
    void addLight(RTLight* light);

    /**
     * @brief   Returns the last @ref RTLight added to
     *          the Scene.
     * @return  The last @ref RTLight added to the Scene.
     */
    RTLight* lastLight() const;

    /**
     * @brief   Will return the @ref RTLight container to
     *          allow outside read access.
     * @return  A const reference on the container.
     */
    const LightsContainer& lights() const;

    /**
     * @brief   Processes all @ref RTLight to modify the
     *          @a color.
     *          Iterates over all @ref RTLight and determines
     *          if the light is hidden by a @ref RTObject by
     *          iterating over all objects stored.
     *          If no object hides the light, computes light's
     *          color influence. Otherwise, uses black for the
     *          current light.
     * @param[in]   data      The data.
     * @param[out]  specular  The specular color.
     * @return  The computed color to use.
     */
    Color processLights(const IntersectionData& data, Color& specular) const;

  public:
    /**
     * @brief   Preprocesses everything stored in the Scene.
     *          Preprocessing computes rotation matrix.
     */
    void preprocess();

  private:
    ObjectsContainer
                     _infiniteObjects; /**< Collection of @ref Object * which have an infinite bbox */
    ObjectsContainer _objects;         /**< Collection of @ref Object * */
    LightsContainer  _lights;          /**< Collection of @ref RTLight * */
    Eye              _eye;             /**< @ref Eye of the Scene */
    CubeMap          _cubemap;         /**< @ref CubeMap of the Scene */
    KDTree*          _kdtree;          /**< KD-Tree of the Scene */

    RAYON_GENERATE_PROPERTY_DECLARATION(Scene, Float_t, _ambient, Ambient);
  };
}  // namespace Rayon

#endif  // RAYON_SCENE_HH_
