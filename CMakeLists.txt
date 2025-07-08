#####################################################################################################
#                                                                                                   #
#  ooooooooo.                         ooooooooooooo                                                 #
#  `888   `Y88.                       8'   888   `8                                                 #
#   888   .d88'  .oooo.   oooo    ooo      888      oooo d8b  .oooo.    .ooooo.   .ooooo.  oooo d8b #
#   888ooo88P'  `P  )88b   `88.  .8'       888      `888""8P `P  )88b  d88' `"Y8 d88' `88b `888""8P #
#   888`88b.     .oP"888    `88..8'        888       888      .oP"888  888       888ooo888  888     #
#   888  `88b.  d8(  888     `888'         888       888     d8(  888  888   .o8 888    .o  888     #
#  o888o  o888o `Y888""8o     .8'         o888o     d888b    `Y888""8o `Y8bod8P' `Y8bod8P' d888b    #
#                         .o..P'                                                                    #
#                         `Y8P'                                                                     #
#                                                                                                   #
#                       Main build configuration for Raytracer and its plugin                       #
#                                                                                                   #
#  -> Configure  : cmake -B build -DCMAKE_BUILD_TYPE=Debug                                          #
#  -> Build      : cmake --build build                                                              #
#  -> Clean      : cmake --build build --target my_clean                                            #
#  -> Full clean : cmake --build build --target my_fclean                                           #
#  -> Rebuild    : cmake --build build --target my_re                                               #
#                                                                                                   #
#####################################################################################################







########################################################################################
##                                                                                    ##
##     🔧 PROJECT SETUP                                                               ##
##     Defines project name, C++ standard and compilation flags                       ##
##                                                                                    ##
########################################################################################
cmake_minimum_required(VERSION 3.10)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fPIC")


########################################################################################
##                                                                                    ##
##     📁 DIRECTORY STRUCTURE                                                         ##
##     Defines main folders for source, build and plugins                            ##
##                                                                                    ##
########################################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(PLUGINS_DIR ${CMAKE_SOURCE_DIR}/plugins)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PLUGIN_DIR ${SRC_DIR}/Plugins)
set(RAYTRACER_DIR ${SRC_DIR}/RayTracer)
set(TOOLS_DIR ${SRC_DIR}/Tools)


########################################################################################
##                                                                                    ##
##     📌 INCLUDE DIRECTORIES                                                         ##
##     Header file include paths for compilation                                     ##
##                                                                                    ##
########################################################################################
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/Plugins)
include_directories(${TOOLS_DIR})


########################################################################################
##                                                                                    ##
##     📦 CORE SOURCES                                                                ##
##     Gathers all non-plugin .cpp files                                             ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/*.cpp")
list(FILTER CORE_SRC EXCLUDE REGEX ".*/Plugins/.*")


########################################################################################
##                                                                                    ##
##     📚 COMMON STATIC LIBRARY                                                       ##
##     Shared tools (math, config, scene, etc.) built as static lib                  ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE COMMON_SRC
    "${TOOLS_DIR}/*.cpp"
    "${RAYTRACER_DIR}/Scene/*.cpp"
)
add_library(raytracer_common STATIC ${COMMON_SRC})


########################################################################################
##                                                                                    ##
##     🚀 MAIN EXECUTABLE                                                             ##
##     Builds the final 'raytracer' binary                                           ##
##                                                                                    ##
########################################################################################
add_executable(raytracer ${CORE_SRC})
target_link_libraries(raytracer
    raytracer_common
    config++
    sfml-graphics
    sfml-window
    sfml-system
)


########################################################################################
##                                                                                    ##
##     🧩 PLUGINS : PRIMITIVES                                                        ##
##     Dynamic objects: Sphere, Cone, Plane, Cylinder                                ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE SPHERE_SRC "${PLUGIN_DIR}/Primitives/Sphere/*.cpp")
add_library(r_p_sphere SHARED ${SPHERE_SRC})
set_target_properties(r_p_sphere PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_sphere raytracer_common)

file(GLOB_RECURSE PLANE_SRC "${PLUGIN_DIR}/Primitives/Plane/*.cpp")
add_library(r_p_plane SHARED ${PLANE_SRC})
set_target_properties(r_p_plane PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_plane raytracer_common)

file(GLOB_RECURSE CONE_SRC "${PLUGIN_DIR}/Primitives/Cone/*.cpp")
add_library(r_p_cone SHARED ${CONE_SRC})
set_target_properties(r_p_cone PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_cone raytracer_common)

file(GLOB_RECURSE CYLINDER_SRC "${PLUGIN_DIR}/Primitives/Cylinder/*.cpp")
add_library(r_p_cylinder SHARED ${CYLINDER_SRC})
set_target_properties(r_p_cylinder PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_p_cylinder raytracer_common)


########################################################################################
##                                                                                    ##
##     🎥 PLUGINS : CAMERA                                                            ##
##     Dynamic camera component                                                      ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE CAMERA_SRC "${PLUGIN_DIR}/Camera/*.cpp")
add_library(r_c_camera SHARED ${CAMERA_SRC})
set_target_properties(r_c_camera PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_c_camera raytracer_common)


########################################################################################
##                                                                                    ##
##     🎨 PLUGINS : MATERIALS                                                         ##
##     Materials like Glass and FlatColor                                            ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE FLATCOLOR_SRC "${PLUGIN_DIR}/Material/FlatColor/*.cpp")
add_library(r_m_flatcolor SHARED ${FLATCOLOR_SRC})
set_target_properties(r_m_flatcolor PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_m_flatcolor raytracer_common)

file(GLOB_RECURSE GLASS_SRC "${PLUGIN_DIR}/Material/Glass/*.cpp")
add_library(r_m_glass SHARED ${GLASS_SRC})
set_target_properties(r_m_glass PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_m_glass raytracer_common)


########################################################################################
##                                                                                    ##
##     💡 PLUGINS : LIGHTS                                                            ##
##     Lighting models: Ambient and Directional                                     ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE AMBIENT_SRC "${PLUGIN_DIR}/Light/AmbientLight/*.cpp")
add_library(r_l_ambient SHARED ${AMBIENT_SRC})
set_target_properties(r_l_ambient PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_l_ambient raytracer_common)

file(GLOB_RECURSE DIRECTIONAL_SRC "${PLUGIN_DIR}/Light/DirectionnalLight/*.cpp")
add_library(r_l_directional SHARED ${DIRECTIONAL_SRC})
set_target_properties(r_l_directional PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_l_directional raytracer_common)


########################################################################################
##                                                                                    ##
##     🖼️  PLUGINS : RENDERER                                                         ##
##     Backend renderer using SFML                                                  ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE SFML_RENDERER_SRC "${PLUGIN_DIR}/Renders/SFML/*.cpp")
add_library(r_r_sfml SHARED ${SFML_RENDERER_SRC})
set_target_properties(r_r_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
target_link_libraries(r_r_sfml raytracer_common)


########################################################################################
##                                                                                    ##
##     🛠️  CUSTOM BUILD COMMANDS                                                     ##
##     Manual tools: clean, fclean, rebuild                                          ##
##                                                                                    ##
########################################################################################
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
