cmake_minimum_required(VERSION 3.10)
project(Raytracer)

## prog language & compile flags ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fno-gnu-unique")

## Directories ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(PLUGINS_DIR ${CMAKE_SOURCE_DIR}/plugins)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CORE_DIR ${SRC_DIR}/Core)
set(FACTORY_DIR ${SRC_DIR}/Factory)
set(INTERFACE_DIR ${SRC_DIR}/Interface)
set(SOURCE_PLUGINS_DIR ${SRC_DIR}/Plugins)
set(PLUGIN_CAMERA_DIR ${SOURCE_PLUGINS_DIR}/Camera)
set(PLUGIN_LIGHT_DIR ${SOURCE_PLUGINS_DIR}/Light)
set(PLUGIN_MATERIAL_DIR ${SOURCE_PLUGINS_DIR}/Material)
set(PLUGIN_PRIMITIVES_DIR ${SOURCE_PLUGINS_DIR}/Primitives)
set(PLUGIN_RENDERS_DIR ${SOURCE_PLUGINS_DIR}/Renders)
set(RAYTRACER_DIR ${SRC_DIR}/RayTracer)
set(BUILDER_DIR ${RAYTRACER_DIR}/Builder)
set(CAMERA_DIR ${RAYTRACER_DIR}/Camera)
set(LIGHT_MANAGER_DIR ${RAYTRACER_DIR}/LightManager)
set(PARSER_DIR ${RAYTRACER_DIR}/Parser)
set(SCENE_DIR ${RAYTRACER_DIR}/Scene)
set(SHARED_DIR ${SRC_DIR}/Shared)
set(TOOLS_DIR ${SRC_DIR}/Tools)

# GLOBAL INCLUDE
include_directories(${CMAKE_SOURCE_DIR}/src)

# CORE FILES – ajoute tout dans src/** sauf plugins
file(GLOB_RECURSE CORE_SRC
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.cc"
    "${SRC_DIR}/*.cxx"
)

# Supprime les fichiers de Plugins (si tu veux les compiler à part comme avant)
list(FILTER CORE_SRC EXCLUDE REGEX ".*/Plugins/.*")

## Main program ##
add_executable(raytracer ${CORE_SRC})
target_link_libraries(raytracer config++)  # Pour libconfig++

### LIBRARIES ####

# SPHERE #
file(GLOB_RECURSE SPHERE_SRC "${PLUGIN_PRIMITIVES_DIR}/Sphere/*.cpp")
include_directories(${PLUGIN_PRIMITIVES_DIR})
include_directories(${PLUGIN_PRIMITIVES_DIR}/Sphere)
add_library(r_p_sphere SHARED ${SPHERE_SRC})
set_target_properties(r_p_sphere PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# PLANE #
file(GLOB_RECURSE PLANE_SRC "${PLUGIN_PRIMITIVES_DIR}/Plane/*.cpp")
include_directories(${PLUGIN_PRIMITIVES_DIR})
include_directories(${PLUGIN_PRIMITIVES_DIR}/Plane)
add_library(r_p_plane SHARED ${PLANE_SRC})
set_target_properties(r_p_plane PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# TO ADD A LIBRARY (see sphere):
# add a file(path to the *.cpp)
# include_directory(path to *.hpp directories)
# add_library(store lib into TOTO_SRC (tmp dir))
# set_target_properties(set path where to put the lib and the prefix)

## BUILD

# CLEAN
add_custom_target(my_clean
    COMMAND find ${CMAKE_BINARY_DIR} -type f -name "*.o" -exec rm -f {} \;
    COMMENT "Cleaning object files (.o)...")

# FCLEAN
add_custom_target(my_fclean
    COMMAND rm -f ${PLUGINS_DIR}/*.so
    COMMAND rm -rf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raytracer
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Full clean: Removing build directory and libraries...")

# RE
add_custom_target(my_re
    COMMAND ${CMAKE_COMMAND} --build build --target my_fclean
    COMMAND cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    COMMAND cmake --build build
    COMMENT "Recompiling everything...")
