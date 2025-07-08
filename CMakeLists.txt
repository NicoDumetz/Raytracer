cmake_minimum_required(VERSION 3.10)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fno-gnu-unique")

# === Directories ===
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(PLUGINS_DIR ${CMAKE_SOURCE_DIR}/plugins)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TOOLS_DIR ${SRC_DIR}/Tools)
set(PLUGIN_DIR ${SRC_DIR}/Plugins)
set(PLUGIN_CAMERA_DIR ${PLUGIN_DIR}/Camera)
set(PLUGIN_LIGHT_DIR ${PLUGIN_DIR}/Light)
set(PLUGIN_MATERIAL_DIR ${PLUGIN_DIR}/Material)
set(PLUGIN_PRIMITIVES_DIR ${PLUGIN_DIR}/Primitives)

include_directories(${SRC_DIR})

# === raytracer_utils === (ConfigNode, Color, Ray, etc.)
file(GLOB_RECURSE UTILS_SRC
    "${TOOLS_DIR}/ConfigNode/*.cpp"
    "${TOOLS_DIR}/Color/*.cpp"
    "${TOOLS_DIR}/Math/**/*.cpp"
    "${TOOLS_DIR}/Ray/*.cpp"
    "${TOOLS_DIR}/HitRecord/*.cpp"
)
add_library(raytracer_utils SHARED ${UTILS_SRC})
target_include_directories(raytracer_utils PUBLIC ${SRC_DIR})

# === Core app ===
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/*.cpp")
list(FILTER CORE_SRC EXCLUDE REGEX ".*/Plugins/.*")

add_executable(raytracer ${CORE_SRC})
target_link_libraries(raytracer raytracer_utils config++)

# === PRIMITIVES ===

file(GLOB_RECURSE SPHERE_SRC "${PLUGIN_PRIMITIVES_DIR}/Sphere/*.cpp")
add_library(r_p_sphere SHARED ${SPHERE_SRC})
target_include_directories(r_p_sphere PUBLIC ${SRC_DIR})
target_link_libraries(r_p_sphere raytracer_utils)
set_target_properties(r_p_sphere PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

file(GLOB_RECURSE PLANE_SRC "${PLUGIN_PRIMITIVES_DIR}/Plane/*.cpp")
add_library(r_p_plane SHARED ${PLANE_SRC})
target_include_directories(r_p_plane PUBLIC ${SRC_DIR})
target_link_libraries(r_p_plane raytracer_utils)
set_target_properties(r_p_plane PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# === MATERIALS ===

file(GLOB_RECURSE FLATCOLOR_SRC "${PLUGIN_MATERIAL_DIR}/FlatColor/*.cpp")
add_library(r_m_flatcolor SHARED ${FLATCOLOR_SRC})
target_include_directories(r_m_flatcolor PUBLIC ${SRC_DIR})
target_link_libraries(r_m_flatcolor raytracer_utils)
set_target_properties(r_m_flatcolor PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# === LIGHTS ===

file(GLOB_RECURSE AMBIENTLIGHT_SRC "${PLUGIN_LIGHT_DIR}/AmbientLight/*.cpp")
add_library(r_l_ambient SHARED ${AMBIENTLIGHT_SRC})
target_include_directories(r_l_ambient PUBLIC ${SRC_DIR})
target_link_libraries(r_l_ambient raytracer_utils)
set_target_properties(r_l_ambient PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

file(GLOB_RECURSE DIRECTIONAL_SRC "${PLUGIN_LIGHT_DIR}/DirectionnalLight/*.cpp")
add_library(r_l_directional SHARED ${DIRECTIONAL_SRC})
target_include_directories(r_l_directional PUBLIC ${SRC_DIR})
target_link_libraries(r_l_directional raytracer_utils)
set_target_properties(r_l_directional PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# === CAMERA ===

file(GLOB_RECURSE CAMERA_SRC "${PLUGIN_CAMERA_DIR}/*.cpp")
add_library(r_c_camera SHARED ${CAMERA_SRC})
target_include_directories(r_c_camera PUBLIC ${SRC_DIR})
target_link_libraries(r_c_camera raytracer_utils)
set_target_properties(r_c_camera PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")

# === CLEANING ===

add_custom_target(my_clean
    COMMAND find ${CMAKE_BINARY_DIR} -type f -name "*.o" -exec rm -f {} \;
    COMMENT "Cleaning object files (.o)...")

add_custom_target(my_fclean
    COMMAND rm -f ${PLUGINS_DIR}/*.so
    COMMAND rm -rf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/raytracer
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Full clean: Removing build directory and libraries...")

add_custom_target(my_re
    COMMAND ${CMAKE_COMMAND} --build build --target my_fclean
    COMMAND cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    COMMAND cmake --build build
    COMMENT "Recompiling everything...")
