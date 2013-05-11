
FILE (GLOB SRC
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

FILE (GLOB HDR
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

IF (LINUX)
	SET (NUTMEG_PLATFORM_LIBS X11 dl)
ENDIF ()

ADD_LIBRARY (NutmegCore SHARED ${SRC} ${HDR})
TARGET_LINK_LIBRARIES (NutmegCore IL ILU ILUT GL Newton ${NUTMEG_PLATFORM_LIBS})
