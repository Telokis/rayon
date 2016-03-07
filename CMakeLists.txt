cmake_minimum_required (VERSION 3.3.2)
project(RayOn)

# Configurable variables


# Set the debug postfix
SET(CMAKE_DEBUG_POSTFIX "_d")

# Changing output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compile flags
if (UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

SET(RAYON_HEADER_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")
SET(RAYON_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")

SET(RAYON_HEADER_FILES
  "${RAYON_HEADER_DIR}/EventManager.hh"

  "${RAYON_HEADER_DIR}/Tools/Helpers.hh"
  "${RAYON_HEADER_DIR}/Tools/Color.hh"
  "${RAYON_HEADER_DIR}/Tools/Vector3.hh"
  "${RAYON_HEADER_DIR}/Tools/CachedValue.hh"
  "${RAYON_HEADER_DIR}/Tools/BoundingBox.hh"

  "${RAYON_HEADER_DIR}/Tools/Angle/Radian.hh"
  "${RAYON_HEADER_DIR}/Tools/Angle/Degree.hh"

  "${RAYON_HEADER_DIR}/Tools/Helpers/Any.hh"
  "${RAYON_HEADER_DIR}/Tools/Helpers/Globals.hh"
  "${RAYON_HEADER_DIR}/Tools/Helpers/PI.hh"
  "${RAYON_HEADER_DIR}/Tools/Helpers/Pow.hh"
  "${RAYON_HEADER_DIR}/Tools/Helpers/Clamp.hh"
  "${RAYON_HEADER_DIR}/Tools/Helpers/Types.hh"
)

SET(RAYON_SOURCE_FILES
  "${RAYON_SOURCE_DIR}/TempMain.cpp"
  "${RAYON_SOURCE_DIR}/EventManager.cpp"

  "${RAYON_SOURCE_DIR}/Tools/Color.cpp"
  "${RAYON_SOURCE_DIR}/Tools/BoundingBox.cpp"

  "${RAYON_SOURCE_DIR}/Tools/Helpers/Globals.cpp"
  
  "${RAYON_SOURCE_DIR}/Tools/Angle/Radian.cpp"
  "${RAYON_SOURCE_DIR}/Tools/Angle/Degree.cpp"
)

# Set sources
add_executable(RayOn ${RAYON_SOURCE_FILES} ${RAYON_HEADER_FILES})

target_include_directories(RayOn PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Include")