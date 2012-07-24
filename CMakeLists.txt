cmake_minimum_required(VERSION 2.6)

project(NutmegCore)

set(BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

message("Source located in " ${PROJECT_SOURCE_DIR})

add_definitions(-g -ggdb)

set(NUTMEG_INCLUDES CoreSrc
					CoreSrc/Common
					CoreSrc/Audio
					CoreSrc/Platform
					CoreSrc/Engine
					CoreSrc/Game
					CoreSrc/Math
					CoreSrc/Physics
					CoreSrc/Render
					CoreSrc/Scene
					Library/Squall
					Library/OpenGL
					Library/Newton
					Library/DevIL)
include_directories(${NUTMEG_INCLUDES})
link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(CoreSrc)
add_subdirectory(Library)
add_subdirectory(Subsystems)
add_subdirectory(Samples)
