cmake_minimum_required (VERSION 3.10.2)

project (Quake3Renderer)

find_package(OpenGL REQUIRED)

if (WIN32 AND CMAKE_SYSTEM_VERSION)
    link_directories(${PROJECT_SOURCE_DIR}/libraries/Win32)
endif()

set(SOURCES source/glad.c
			source/bitstream.cpp
			source/bsp.cpp
			source/bsprenderer.cpp
			source/game.cpp
			source/matrix.cpp
			source/pk3.cpp
			source/shaders.cpp
			source/transform.cpp)

add_compile_options(-D GLFW_INCLUDE_NONE)
add_executable(Quake3Renderer source/main.cpp ${SOURCES})

include_directories( ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Quake3Renderer ${OPENGL_INCLUDE_DIRS} glfw3)