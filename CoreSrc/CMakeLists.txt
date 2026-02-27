
file(GLOB SRC
	*.cpp
	Audio/*.cpp
	Common/*.cpp
	Engine/*.cpp
	Game/*.cpp
	Math/*.cpp
	Physics/*.cpp
	Platform/*.cpp
	Render/*.cpp
	Scene/*.cpp)

file(GLOB HDR
	*.h
	Audio/*.h
	Common/*.h
	Engine/*.h
	Game/*.h
	Math/*.h
	Physics/*.h
	Platform/*.h
	Render/*.h
	Scene/*.h)

if(UNIX)
	set(NUTMEG_PLATFORM_LIBS X11 dl)
endif()

add_library(NutmegCore SHARED ${SRC} ${HDR})
target_link_libraries(NutmegCore ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES} OpenGL::GL Newton ${NUTMEG_PLATFORM_LIBS})
