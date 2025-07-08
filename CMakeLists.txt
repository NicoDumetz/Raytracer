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
##     Defines main folders for source, build and plugins                             ##
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
##     Header file include paths for compilation                                      ##
##                                                                                    ##
########################################################################################
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/Plugins)
include_directories(${TOOLS_DIR})


########################################################################################
##                                                                                    ##
##     📦 CORE SOURCES                                                                ##
##     Gathers all non-plugin .cpp files                                              ##
##                                                                                    ##
########################################################################################
file(GLOB_RECURSE CORE_SRC "${SRC_DIR}/*.cpp")
list(FILTER CORE_SRC EXCLUDE REGEX ".*/Plugins/.*")


########################################################################################
##                                                                                    ##
##     📚 COMMON STATIC LIBRARY                                                       ##
##     Shared tools (math, config, scene, etc.) built as static lib                   ##
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
##     Builds the final 'raytracer' binary                                            ##
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
##     🧩 PLUGIN MANAGEMENT FUNCTION                                                  ##
##     Reusable function to add any plugin easily                                     ##
##                                                                                    ##
########################################################################################
function(add_raytracer_plugin target subdir)
    file(GLOB_RECURSE SRC "${PLUGIN_DIR}/${subdir}/*.cpp")
    add_library(${target} SHARED ${SRC})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_DIR} PREFIX "")
    target_link_libraries(${target} raytracer_common)
endfunction()


########################################################################################
##                                                                                    ##
##     🧩 PLUGINS : DYNAMIC MODULES                                                   ##
##     All shared object (.so) plugins dynamically loaded by the raytracer engine     ##
##                                                                                    ##
########################################################################################

# ╭────────────── 🔷 PRIMITIVES ──────────────╮
add_raytracer_plugin(r_p_sphere       "Primitives/Sphere")
add_raytracer_plugin(r_p_plane        "Primitives/Plane")
add_raytracer_plugin(r_p_cone         "Primitives/Cone")
add_raytracer_plugin(r_p_cylinder     "Primitives/Cylinder")
add_raytracer_plugin(r_p_triangles    "Primitives/Triangles")
add_raytracer_plugin(r_p_Cube         "Primitives/Cube")
add_raytracer_plugin(r_p_LimitedCone  "Primitives/LimitedCone")
add_raytracer_plugin(r_p_LimitedCylinder  "Primitives/LimitedCylinder")
# ╰───────────────────────────────────────────╯

# ╭──────────────── 🎥 CAMERA ────────────────╮
add_raytracer_plugin(r_c_camera       "Camera")
# ╰───────────────────────────────────────────╯

# ╭─────────────── 🎨 MATERIALS ──────────────╮
add_raytracer_plugin(r_m_flatcolor    "Material/FlatColor")
add_raytracer_plugin(r_m_Checkboard   "Material/Checkboard")
add_raytracer_plugin(r_m_glass        "Material/Glass")
add_raytracer_plugin(r_m_perlin       "Material/Perlin")
add_raytracer_plugin(r_m_mirror       "Material/Mirror")
# ╰───────────────────────────────────────────╯

# ╭──────────────── 💡 LIGHTS ───────────────╮
add_raytracer_plugin(r_l_ambient      "Light/AmbientLight")
add_raytracer_plugin(r_l_directional  "Light/DirectionnalLight")
# ╰──────────────────────────────────────────╯

# ╭────────────── 🖼️ RENDERER ───────────────╮
add_raytracer_plugin(r_r_sfml         "Renders/SFML")
# ╰──────────────────────────────────────────╯

########################################################################################
##                                                                                    ##
##     🛠️  CUSTOM BUILD COMMANDS                                                      ##
##     Manual tools: clean, fclean, rebuild                                           ##
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
