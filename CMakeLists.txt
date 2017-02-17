cmake_minimum_required (VERSION 3.3.2)
project(Rayon)

SET(RAYON_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
SET(RAYON_HEADER_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")
SET(RAYON_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")
set(RAYON_CMAKE_FOLDER_DIR ${CMAKE_CURRENT_LIST_DIR}/CMake)

# Configurable variables
set(ENABLE_SOURCE_GROUPING true CACHE BOOL "Enable source subfolders")
set(GLM_ROOT "${CMAKE_CURRENT_LIST_DIR}/Dependencies/glm" CACHE PATH "Path to GLM root directory")
set(BOOST_ROOT "${RAYON_ROOT_DIR}/Dependencies/boost_1_63_0")

# Set the debug postfix
SET(CMAKE_DEBUG_POSTFIX "_d")

# Compile flags
if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -O3")
endif()

set(CMAKE_MODULE_PATH ${RAYON_CMAKE_FOLDER_DIR}/Modules ${CMAKE_MODULE_PATH})
include(${RAYON_CMAKE_FOLDER_DIR}/Source_Grouping.cmake)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Dependencies/json)

file(GLOB_RECURSE RAYON_SOURCE_FILES RELATIVE ${RAYON_SOURCE_DIR} "${RAYON_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE RAYON_HEADER_FILES RELATIVE ${RAYON_HEADER_DIR} "${RAYON_HEADER_DIR}/*.hh" "${RAYON_HEADER_DIR}/*.hpp")

# Source grouping setup
if (ENABLE_SOURCE_GROUPING)
    SOURCE_GROUP(Headers REGULAR_EXPRESSION ".*\\.h(h|pp)")
    SOURCE_GROUP(Sources REGULAR_EXPRESSION ".*\\.cpp")

    GroupSources(RAYON_HEADER_FILES ${RAYON_HEADER_DIR} Headers)
    GroupSources(RAYON_SOURCE_FILES ${RAYON_SOURCE_DIR} Sources)
endif()

prefix_custom_list(RAYON_HEADERS "${RAYON_HEADER_DIR}/" RAYON_HEADER_FILES)
prefix_custom_list(RAYON_SOURCES "${RAYON_SOURCE_DIR}/" RAYON_SOURCE_FILES)

link_directories("${RAYON_ROOT_DIR}/Dependencies/boost_1_63_0/lib")
# Set sources
add_executable(Rayon ${RAYON_SOURCES} ${RAYON_HEADERS})

if (UNIX)
  target_link_libraries(Rayon "pthread")
endif()
target_link_libraries(Rayon "${JSON_LIBRARY}")
include_directories(Rayon "${JSON_HEADER_DIR}")

# Find GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# Find BOOST
set(Boost_NO_SYSTEM_PATHS true)
find_package(Boost 1.63.0 EXACT COMPONENTS program_options log)
if(NOT Boost_FOUND)
	message("Boost not found. Setting up download...")
	include(${RAYON_CMAKE_FOLDER_DIR}/Build_Boost.cmake)
	add_dependencies(Rayon Boost)
endif()
include_directories("${RAYON_ROOT_DIR}/Dependencies/boost_1_63_0/include")

if (UNIX)
	target_link_libraries(Rayon "${Boost_LIBRARIES}")
else()
	add_definitions(-DBOOST_AUTO_LINK_TAGGED)
endif()

target_include_directories(Rayon PUBLIC "${RAYON_HEADER_DIR}")

# Files
add_custom_command(TARGET Rayon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/files"
        $<TARGET_FILE_DIR:Rayon>/files)

if (WIN32)
# Copies again the files for Windows
    add_custom_command(TARGET Rayon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_LIST_DIR}/files"
            ${CMAKE_BINARY_DIR}/files)
endif(WIN32)
