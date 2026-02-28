
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

if(WIN32)
	ADD_EXECUTABLE (DiabloRemix WIN32 ${SRC} ${HDR} ../winmain.cpp)
else()
	ADD_EXECUTABLE (DiabloRemix ${SRC} ${HDR})
endif()
TARGET_LINK_LIBRARIES (DiabloRemix NutmegCore NutmegLib)
