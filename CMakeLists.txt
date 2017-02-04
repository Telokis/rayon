cmake_minimum_required (VERSION 3.3.2)
project(RayOn)

SET(RAYON_HEADER_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")
SET(RAYON_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")
set(RAYON_CMAKE_FOLDER_DIR ${CMAKE_CURRENT_LIST_DIR}/CMake)

# Configurable variables
set(ENABLE_SOURCE_GROUPING true CACHE BOOL "Enable source subfolders")
set(GLM_ROOT "${CMAKE_CURRENT_LIST_DIR}/Dependencies/glm" CACHE PATH "Path to GLM root directory")

# Set the debug postfix
SET(CMAKE_DEBUG_POSTFIX "_d")

# Compile flags
if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -O3")
endif()

set(CMAKE_MODULE_PATH ${RAYON_CMAKE_FOLDER_DIR}/Modules ${CMAKE_MODULE_PATH})
include(${RAYON_CMAKE_FOLDER_DIR}/Source_Grouping.cmake)

file(GLOB_RECURSE RAYON_SOURCE_FILES_GLOBBED "${RAYON_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE RAYON_HEADER_FILES_GLOBBED "${RAYON_HEADER_DIR}/*.hh")

foreach(dir ${RAYON_HEADER_FILES_GLOBBED})
  string(REPLACE "${RAYON_HEADER_DIR}/" "" tmp_str ${dir})
  set(RAYON_HEADER_FILES ${RAYON_HEADER_FILES} ${tmp_str})
endforeach(dir)

foreach(dir ${RAYON_SOURCE_FILES_GLOBBED})
  string(REPLACE "${RAYON_SOURCE_DIR}/" "" tmp_str ${dir})
  set(RAYON_SOURCE_FILES ${RAYON_SOURCE_FILES} ${tmp_str})
endforeach(dir)

# Source grouping setup
if (ENABLE_SOURCE_GROUPING)
    SOURCE_GROUP(Headers REGULAR_EXPRESSION ".*\\.h(h|pp)")
    SOURCE_GROUP(Sources REGULAR_EXPRESSION ".*\\.cpp")

    GroupSources(RAYON_HEADER_FILES ${RAYON_HEADER_DIR} Headers)
    GroupSources(RAYON_SOURCE_FILES ${RAYON_SOURCE_DIR} Sources)
endif()

prefix_custom_list(RAYON_HEADERS "${RAYON_HEADER_DIR}/" RAYON_HEADER_FILES)
prefix_custom_list(RAYON_SOURCES "${RAYON_SOURCE_DIR}/" RAYON_SOURCE_FILES)

# Set sources
add_executable(RayOn ${RAYON_SOURCES} ${RAYON_HEADERS})

# Find GLM
find_package(GLM REQUIRED)
include_directories(Arkneo ${GLM_INCLUDE_DIR})

target_include_directories(RayOn PUBLIC "${RAYON_HEADER_DIR}")