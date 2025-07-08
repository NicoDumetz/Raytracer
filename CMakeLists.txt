cmake_minimum_required(VERSION 3.10)
project(Raytracer)

## prog language & compile flags ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fno-gnu-unique")

## Directories ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CORE_DIR ${SRC_DIR}/Core)
set(FACTORY_DIR ${SRC_DIR}/Factory)
set(INTERFACE_DIR ${SRC_DIR}/Interface)
set(SOURCE_PLUGINS_DIR ${SRC_DIR}/Plugins)
set(RAYTRACER_DIR ${SRC_DIR}/RayTracer)
set(TOOLS_DIR ${SRC_DIR}/Tools)
set(SHARED_DIR ${SRC_DIR}/shared)
set(PLUGINS_DIR ${CMAKE_SOURCE_DIR}/plugins)
set(SOURCE_LIB_DIR ${CMAKE_SOURCE_DIR}/src/plugins)

# GLOBAL INCLUDE
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/Core/*.cpp")
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/Core/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/src)

## Main program ##
add_executable(raytracer ${SRC_DIR}/main.cpp ${CORE_SRC})

### LIBRARIES ####

# SFML #
# find_package(SFML 2.6.0 COMPONENTS graphics window system REQUIRED)
# file(GLOB_RECURSE SFML_SRC "${SOURCE_PLUGINS_DIR}/SFML/*.cpp")
# include_directories(${SOURCE_PLUGINS_DIR}/SFML)
# add_library(raytracer_sfml SHARED ${SFML_SRC})
# target_link_libraries(raytracer_sfml sfml-graphics sfml-window sfml-system)
# set_target_properties(raytracer_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

## PRIMITIVES ##

# SPHERE #
file(GLOB_RECURSE SPHERE_SRC "${SOURCE_PLUGINS_DIR}/Sphere/*.cpp")
include_directories(${SOURCE_PLUGINS_DIR}/Sphere)
add_library(r_p_sphere SHARED ${SPHERE_SRC})
set_target_properties(r_p_sphere PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# PLANE #
file(GLOB_RECURSE PLANE_SRC "${SOURCE_PLUGINS_DIR}/Plane/*.cpp")
include_directories(${SOURCE_PLUGINS_DIR}/Plane)
add_library(r_p_plane SHARED ${PLANE_SRC})
set_target_properties(r_p_plane PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# TO ADD A LIBRARY :
# add a file(path to the *.cpp)
# include_directory(path to *.hpp)
# add_librabry(store lib into TOTO_SRC (tmp dir))
# set_target_propreties(set path where to put the lib and the prefix)

## BUILD

# CLEAN
add_custom_target(my_clean
    COMMAND find ${CMAKE_BINARY_DIR} -type f -name "*.o" -exec rm -f {} \;
    COMMENT "Cleaning object files (.o)...")

# FCLEAN
add_custom_target(my_fclean
    COMMAND rm -f ${PLUGINS_DIR}*.so
    COMMAND rm -rf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raytracer
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Full clean: Removing build directory and libraries...")

# RE
add_custom_target(my_re
    COMMAND ${CMAKE_COMMAND} --build build --target fclean
    COMMAND cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    COMMAND cmake --build build
    COMMENT "Recompiling everything...")
