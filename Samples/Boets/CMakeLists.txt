set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

add_executable(Boets  Source/EntityActor.cpp Source/EntityActor.h
						Source/EntityPlayer.cpp Source/EntityPlayer.h
						Source/EntityWeapon.cpp Source/EntityWeapon.h
						Source/main.cpp)
target_link_libraries(Boets NutmegCore
								NutmegPlatform
								NutmegAudio
								NutmegLib
								NutmegPhysics
								NutmegRender)
