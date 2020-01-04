#pragma once

#ifndef RAYON_TOOLS_CODEMACROS_HH
#define RAYON_TOOLS_CODEMACROS_HH

/**
 * @brief       Generates code for a property declaration inside a class.
 *              Will generate :
 *              - The property itself. An attribute marked as protected.
 *              - The declaration of the setter associated with the property.
 *              - The declaration of the getter associated with the property.
 *
 *	Here is an example :
 *	@code{.cpp}
 *  class Entity
 *  {
 *      RAYON_GENERATE_PROPERTY_DECLARATION(Entity, int, _color, Color);
 *  };
 *	@endcode
 *
 *  Will become :
 *	@code{.cpp}
 *  class Entity
 *  {
 *      protected:
 *          int     _color;
 *      public:
 *          Entity  *setColor(int value);
 *          int     getColor() const;
 *  };
 *	@endcode
 *
 * @param[in] className Name of the class.
 * @param[in] type      Type of the property variable. (E.g : int)
 * @param[in] varName   The name of the property variable. (E.g : _color)
 * @param[in] prefix    Name of the property. (E.g : Color)
 *
 * @see RAYON_GENERATE_PROPERTY_DEFINITION
 */
#define RAYON_GENERATE_PROPERTY_DECLARATION(className, type, varName, prefix) \
protected:                                                                    \
  type varName;                                                               \
                                                                              \
public:                                                                       \
  void set##prefix(type value);                                               \
  type get##prefix() const;

#define RAYON_GENERATE_PROPERTY_DECLARATION_PUBLIC(className, type, varName, prefix) \
public:                                                                              \
  type varName;                                                                      \
                                                                                     \
public:                                                                              \
  void set##prefix(type value);                                                      \
  type get##prefix() const;

/**
 * @brief       Generates code for a property definition inside a class.
 *              Will generate :
 *              - The code of the setter associated with the property.
 *              - The code of the getter associated with the property.
 *
 *	Here is an example :
 *	@code{.cpp}
 *      RAYON_GENERATE_PROPERTY_DEFINITION(Entity, int, _color, Color);
 *	@endcode
 *
 *  Will become :
 *	@code{.cpp}
 *      Entity  *Entity::setColor(int value)
 *      {
 *          _color = value;
 *          return (this);
 *      }
 *      int     Entity::getColor() const
 *      {
 *          return (_color);
 *      }
 *	@endcode
 *
 * @param[in] className Name of the class.
 * @param[in] type      Type of the property variable. (E.g : int)
 * @param[in] varName   The name of the property variable. (E.g : _color)
 * @param[in] prefix    Name of the property. (E.g : Color)
 *
 * @see RAYON_GENERATE_PROPERTY_DECLARATION
 */
#define RAYON_GENERATE_PROPERTY_DEFINITION(className, type, varName, prefix) \
  void className::set##prefix(type value)                                    \
  {                                                                          \
    varName = value;                                                         \
  }                                                                          \
  type className::get##prefix() const                                        \
  {                                                                          \
    return (varName);                                                        \
  }

#define RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DECLARATION(className, prefix) \
  const Vec_t& get##prefix() const;                                         \
  Float_t      get##prefix##X() const;                                      \
  Float_t      get##prefix##Y() const;                                      \
  Float_t      get##prefix##Z() const;                                      \
  void         set##prefix(const Vec_t&);                                   \
  void         set##prefix(Float_t x, Float_t y, Float_t z);                \
  void         set##prefix##X(Float_t value);                               \
  void         set##prefix##Y(Float_t value);                               \
  void         set##prefix##Z(Float_t value);

#define RAYON_GENERATE_Vec_t_GETTERS_SETTERS_DEFINITION(className, varName, prefix) \
  void className::set##prefix(const Vec_t& vec)                                     \
  {                                                                                 \
    varName = vec;                                                                  \
  }                                                                                 \
  void className::set##prefix(Float_t x, Float_t y, Float_t z)                      \
  {                                                                                 \
    varName = std::move(Vec_t(x, y, z));                                            \
  }                                                                                 \
  void className::set##prefix##X(Float_t value)                                     \
  {                                                                                 \
    varName.x = (value);                                                            \
  }                                                                                 \
  void className::set##prefix##Y(Float_t value)                                     \
  {                                                                                 \
    varName.y = (value);                                                            \
  }                                                                                 \
  void className::set##prefix##Z(Float_t value)                                     \
  {                                                                                 \
    varName.z = (value);                                                            \
  }                                                                                 \
  const Vec_t& className::get##prefix() const                                       \
  {                                                                                 \
    return (varName);                                                               \
  }                                                                                 \
  Float_t className::get##prefix##X() const                                         \
  {                                                                                 \
    return (varName.x);                                                             \
  }                                                                                 \
  Float_t className::get##prefix##Y() const                                         \
  {                                                                                 \
    return (varName.y);                                                             \
  }                                                                                 \
  Float_t className::get##prefix##Z() const                                         \
  {                                                                                 \
    return (varName.z);                                                             \
  }

#endif  // RAYON_TOOLS_CODEMACROS_HH
