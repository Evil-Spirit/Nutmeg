set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})
add_executable(EntitySample Source/main.cpp)
target_link_libraries(EntitySample NutmegCore
								NutmegPlatform
								NutmegAudio
								NutmegLib
								NutmegPhysics
								NutmegRender)
