set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_PLATFORM_SUBSYSTEM_SRC MapX11Key.h
								PlatformBada.cpp PlatformBada.h
								PlatformWindows.cpp PlatformWindows.h
								PlatformLinux.cpp PlatformLinux.h
								PlatformPlugin.cpp)

add_library(NutmegPlatform SHARED ${NUTMEG_PLATFORM_SUBSYSTEM_SRC})
if(UNIX)
target_link_libraries(NutmegPlatform X11 GL)
endif()
