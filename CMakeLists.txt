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

target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/core/include/")
target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/platform/include/")
target_include_directories(engine-3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/")

target_link_libraries(engine-3d PRIVATE glm glfw glad stb_image imgui)