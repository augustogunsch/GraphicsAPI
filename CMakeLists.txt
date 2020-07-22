cmake_minimum_required(VERSION 3.10)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

project(GraphicsAPI VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type Debug as none was specified")
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Default build type." FORCE)
endif()

# database for YCM:
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(OpenGL_PROFILE GLFW_OPENGL_CORE_PROFILE)
set(OpenGL_VERSION_MAJOR 4) 
set(OpenGL_VERSION_MINOR 3) 

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-OgWall")
set(CMAKE_C_FLAGS_DEBUG_INIT "-OgWall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3Wall")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O3Wall")

configure_file(
	"${PROJECT_SOURCE_DIR}/headers/OpenGLVersion.hpp.in"
	"${PROJECT_BINARY_DIR}/OpenGLVersion.hpp"
	)

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_C_COMPILER "g++" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "CXX compiler")

add_executable(
	executable
	main.cpp
	textures/texture.cpp 
	shaders/program.cpp shaders/light.cpp shaders/material.cpp
	models/model.cpp models/cube.cpp
	window/window.cpp window/camera.cpp
	debug/debug.cpp
	)

if(UNIX AND NOT APPLE)
	target_link_libraries(
		executable
		dl.so
		pthread.so
		)

	set_target_properties(
		executable
	       	PROPERTIES
		OUTPUT_NAME "run.out"
		)
elseif(WIN32)
	target_link_libraries(
		executable
		opengl32.dll
		gdi32.dll
		user32.dll
		kernel32.dll
		)

	set_target_properties(
		executable
		PROPERTIES
		OUTPUT_NAME "run"
		)
endif()

#glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("libraries/src/glfw")

#glad
add_library(glad STATIC "libraries/src/glad/glad.c")
target_include_directories(glad PRIVATE "libraries/includes")

target_link_libraries(
	executable
	glfw
	glad
	)

set_target_properties(
	glfw glad
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libraries/lib"
	)

#includes
target_include_directories(executable
	PUBLIC libraries/includes
	PUBLIC headers
	)
set_target_properties(
	executable
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
	)
