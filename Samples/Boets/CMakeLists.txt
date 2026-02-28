
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

if(WIN32)
	ADD_EXECUTABLE (Boets WIN32 ${SRC} ${HDR} ../winmain.cpp)
else()
	ADD_EXECUTABLE (Boets ${SRC} ${HDR})
endif()
TARGET_LINK_LIBRARIES (Boets NutmegCore NutmegLib)
