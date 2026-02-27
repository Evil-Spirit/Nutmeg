cmake_minimum_required(VERSION 3.15)

project(NutmegCore)

if(POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()

set(BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})
set(RUNTIME_OUTPUT_DIRECTORY ${BUILD_ROOT})

message("Source located in " ${PROJECT_SOURCE_DIR})

if(UNIX)
	set(FLAGS -Wall)

	if(USE_CLANG)
		set(CMAKE_C_COMPILER   "/usr/bin/clang")
		set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
		set(CMAKE_AR           "/usr/bin/llvm-ar")
		set(CMAKE_NM           "/usr/bin/llvm-nm")
		set(CMAKE_OBJDUMP      "/usr/bin/llvm-objdump")
		set(CMAKE_RANLIB       "/usr/bin/llvm-ranlib")
	else()
		set(FLAGS ${FLAGS} -Wno-parentheses)
	endif()

	set(CMAKE_C_FLAGS                "-Wall -Wno-parentheses")
	set(CMAKE_C_FLAGS_DEBUG          "-g")
	set(CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	set(CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

	set(CMAKE_CXX_FLAGS                "-Wall -Wno-parentheses -Wno-strict-overflow -Wno-maybe-uninitialized")
	set(CMAKE_CXX_FLAGS_DEBUG          "-g")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
endif()

if(WIN32)
	add_definitions(-DNUTMEG_PLATFORM_WINDOWS -DNOMINMAX)
endif()

if(UNIX)
	add_definitions(-DNUTMEG_PLATFORM_LINUX)
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Find DevIL (Developer's Image Library).
# Module mode works with system packages on Linux.
# Config mode works with Conan-generated packages on Windows.
find_package(DevIL QUIET)
if(NOT IL_FOUND)
	find_package(DevIL CONFIG QUIET)
	if(DevIL_FOUND)
		set(IL_LIBRARIES DevIL::IL)
		set(ILU_LIBRARIES DevIL::ILU)
		set(ILUT_LIBRARIES DevIL::ILUT)
		# Conan puts headers under include/IL/; extract that path so
		# code using #include "il.h" finds them without path qualification.
		get_target_property(_il_inc DevIL::IL INTERFACE_INCLUDE_DIRECTORIES)
		set(IL_INCLUDE_DIR "${_il_inc}/IL")
	else()
		message(FATAL_ERROR
			"DevIL (Developer's Image Library) not found.\n"
			"  Linux:   sudo apt install libdevil-dev\n"
			"  Windows: install Conan 2.x, then run:\n"
			"             conan install . --output-folder=<build_dir> --build=missing\n"
			"           and configure CMake with:\n"
			"             cmake -B <build_dir> -DCMAKE_TOOLCHAIN_FILE=<build_dir>/conan_toolchain.cmake")
	endif()
endif()

set(NUTMEG_INCLUDES
	CoreSrc
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
	Library/Newton)

if(IL_INCLUDE_DIR)
	list(APPEND NUTMEG_INCLUDES ${IL_INCLUDE_DIR})
endif()

include_directories(${NUTMEG_INCLUDES})
link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(External/newton-dynamics-2.35)
add_subdirectory(CoreSrc)
add_subdirectory(Library)
add_subdirectory(Subsystems)
add_subdirectory(Samples)
