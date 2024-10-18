cmake_minimum_required (VERSION 3.6)
project (engine-3d)

add_executable(engine-3d)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
target_sources(engine-3d PRIVATE ${MY_SOURCES})

add_subdirectory("external/glad")
add_subdirectory("external/glfw-3.4")
add_subdirectory("external/glm")
add_subdirectory("external/stb_image")
add_subdirectory("external/imgui-1.91.3")
add_subdirectory("external/assimp")

set(ASSIMP_HUNTER_ENABLED OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL ON)
set(ASSIMP_INSTALL_PDB OFF)
set(ASSIMP_BUILD_DRACO OFF)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF)

target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/core/include/")
target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/platform/include/")
target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/")

target_link_libraries(engine-3d PRIVATE glm glfw glad stb_image imgui assimp)