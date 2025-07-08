cmake_minimum_required(VERSION 3.10)
project(Raytracer)

# === Compilateur ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fPIC")

# === Répertoires ===
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(PLUGINS_DIR ${CMAKE_SOURCE_DIR}/plugins)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PLUGIN_DIR ${SRC_DIR}/Plugins)
set(RAYTRACER_DIR ${SRC_DIR}/RayTracer)
set(TOOLS_DIR ${SRC_DIR}/Tools)

# === Includes ===
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/Plugins)
include_directories(${TOOLS_DIR})

# === Fichiers Core (sans Plugins) ===
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/*.cpp")
list(FILTER CORE_SRC EXCLUDE REGEX ".*/Plugins/.*")

# === Lib statique pour outils communs (config, math, utils...) ===
file(GLOB_RECURSE COMMON_SRC
    "${TOOLS_DIR}/*.cpp"
    "${RAYTRACER_DIR}/Scene/*.cpp"
)
add_library(raytracer_common STATIC ${COMMON_SRC})

# === Executable principal ===
add_executable(raytracer ${CORE_SRC})
target_link_libraries(raytracer
    raytracer_common
    config++
    sfml-graphics
    sfml-window
    sfml-system
)

# === Plugins dynamiques (sphere, plane, etc.) ===
# PRIMITIVES
file(GLOB_RECURSE SPHERE_SRC "${PLUGIN_DIR}/Primitives/Sphere/*.cpp")
add_library(r_p_sphere SHARED ${SPHERE_SRC})
set_target_properties(r_p_sphere PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_sphere raytracer_common)

file(GLOB_RECURSE PLANE_SRC "${PLUGIN_DIR}/Primitives/Plane/*.cpp")
add_library(r_p_plane SHARED ${PLANE_SRC})
set_target_properties(r_p_plane PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_plane raytracer_common)

# CONE
file(GLOB_RECURSE CONE_SRC "${PLUGIN_DIR}/Primitives/Cone/*.cpp")
add_library(r_p_cone SHARED ${CONE_SRC})
set_target_properties(r_p_cone PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_cone raytracer_common)

# CYLINDER
file(GLOB_RECURSE CYLINDER_SRC "${PLUGIN_DIR}/Primitives/Cylinder/*.cpp")
add_library(r_p_cylinder SHARED ${CYLINDER_SRC})
set_target_properties(r_p_cylinder PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_cylinder raytracer_common)


# CAMERA
file(GLOB_RECURSE CAMERA_SRC "${PLUGIN_DIR}/Camera/*.cpp")
add_library(r_c_camera SHARED ${CAMERA_SRC})
set_target_properties(r_c_camera PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_c_camera raytracer_common)

# MATERIALS
file(GLOB_RECURSE FLATCOLOR_SRC "${PLUGIN_DIR}/Material/FlatColor/*.cpp")
add_library(r_m_flatcolor SHARED ${FLATCOLOR_SRC})
set_target_properties(r_m_flatcolor PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_m_flatcolor raytracer_common)

file(GLOB_RECURSE GLASS_SRC "${PLUGIN_DIR}/Material/Glass/*.cpp")
add_library(r_m_glass SHARED ${GLASS_SRC})
set_target_properties(r_m_glass PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_m_glass raytracer_common)


# LIGHTS
file(GLOB_RECURSE AMBIENT_SRC "${PLUGIN_DIR}/Light/AmbientLight/*.cpp")
add_library(r_l_ambient SHARED ${AMBIENT_SRC})
set_target_properties(r_l_ambient PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_l_ambient raytracer_common)

file(GLOB_RECURSE DIRECTIONAL_SRC "${PLUGIN_DIR}/Light/DirectionnalLight/*.cpp")
add_library(r_l_directional SHARED ${DIRECTIONAL_SRC})
set_target_properties(r_l_directional PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_l_directional raytracer_common)

# === SFMLRenderer ===
file(GLOB_RECURSE SFML_RENDERER_SRC "${PLUGIN_DIR}/Renders/SFML/*.cpp")
add_library(r_r_sfml SHARED ${SFML_RENDERER_SRC})
set_target_properties(r_r_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_r_sfml raytracer_common)


# === CLEAN targets ===
add_custom_target(my_clean
    COMMAND find ${CMAKE_BINARY_DIR} -type f -name "*.o" -exec rm -f {} \;
    COMMENT "Cleaning object files (.o)..."
)

add_custom_target(my_fclean
    COMMAND rm -f ${PLUGINS_DIR}/*.so
    COMMAND rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raytracer
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Full clean: Removing build directory and binaries..."
)

add_custom_target(my_re
    COMMAND ${CMAKE_COMMAND} --build build --target my_fclean
    COMMAND cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    COMMAND cmake --build build
    COMMENT "Rebuilding all..."
)
