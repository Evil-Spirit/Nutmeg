
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

if(WIN32)
	ADD_EXECUTABLE (EntitySample WIN32 ${SRC} ${HDR} ../winmain.cpp)
else()
	ADD_EXECUTABLE (EntitySample ${SRC} ${HDR})
endif()
TARGET_LINK_LIBRARIES (EntitySample NutmegCore NutmegLib)
