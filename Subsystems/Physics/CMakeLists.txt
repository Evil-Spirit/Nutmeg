set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_PHYSICS_SUBSYSTEM_SRC PhysicsNewton.cpp PhysicsNewton.h
#								PhysicsTokamak.cpp PhysicsTokamak.h)
								PhysicsPlugin.cpp)

add_library(NutmegPhysics SHARED ${NUTMEG_PHYSICS_SUBSYSTEM_SRC})
target_include_directories(NutmegPhysics PRIVATE
	${CMAKE_SOURCE_DIR}/External/newton-dynamics-2.35/coreLibrary_200/source/newton)
if(WIN32)
	target_compile_definitions(NutmegPhysics PRIVATE _NEWTON_USE_LIB)
endif()
target_link_libraries(NutmegPhysics NutmegCore Newton)
