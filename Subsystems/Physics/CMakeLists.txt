set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_PHYSICS_SUBSYSTEM_SRC PhysicsNewton.cpp PhysicsNewton.h
#								PhysicsTokamak.cpp PhysicsTokamak.h)
								)

add_library(NutmegPhysics SHARED ${NUTMEG_PHYSICS_SUBSYSTEM_SRC})
target_link_libraries(NutmegPhysics Newton)
