CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (NutmegCore)

SET (BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

SET (LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
SET (EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})
SET (RUNTIME_OUTPUT_DIRECTORY ${BUILD_ROOT})

MESSAGE ("Source located in " ${PROJECT_SOURCE_DIR})

IF (UNIX)
	SET (FLAGS -Wall)

	IF (USE_CLANG)
		#SET (FLAGS ${FLAGS} "")
		SET (CMAKE_C_COMPILER   "/usr/bin/clang")
		SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
		SET (CMAKE_AR           "/usr/bin/llvm-ar")
		SET (CMAKE_LINKER       "/usr/bin/llvm-ld")
		SET (CMAKE_NM           "/usr/bin/llvm-nm")
		SET (CMAKE_OBJDUMP      "/usr/bin/llvm-objdump")
		SET (CMAKE_RANLIB       "/usr/bin/llvm-ranlib")
	ELSE ()
		SET (FLAGS ${FLAGS} -Wno-parentheses)
	ENDIF ()

	SET (CMAKE_C_FLAGS                "-Wall -Wno-parentheses")
	SET (CMAKE_C_FLAGS_DEBUG          "-g")
	SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

	SET (CMAKE_CXX_FLAGS                "-Wall -Wno-parentheses -Wno-strict-overflow -Wno-maybe-uninitialized")
	SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
	SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
ENDIF ()

IF (WIN32)
	ADD_DEFINITIONS (-DNUTMEG_PLATFORM_WINDOWS)
ENDIF()

IF(UNIX)
	ADD_DEFINITIONS (-DNUTMEG_PLATFORM_LINUX)
endIF()

SET (NUTMEG_INCLUDES
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
	Library/Newton
	Library/DevIL)

INCLUDE_DIRECTORIES (${NUTMEG_INCLUDES})
LINK_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
LINK_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/External)

ADD_SUBDIRECTORY (CoreSrc)
ADD_SUBDIRECTORY (Library)
ADD_SUBDIRECTORY (Subsystems)
ADD_SUBDIRECTORY (Samples)
