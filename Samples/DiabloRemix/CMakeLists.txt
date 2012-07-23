set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})
add_executable(DiabloRemix Source/EntityCreature.cpp Source/EntityCreature.h
							Source/main.cpp)
target_link_libraries(DiabloRemix NutmegCore
								NutmegPlatform
								NutmegAudio
								NutmegLib
								NutmegPhysics
								NutmegRender)
