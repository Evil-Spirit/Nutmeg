
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

ADD_EXECUTABLE (Boets ${SRC} ${HDR})
TARGET_LINK_LIBRARIES (Boets NutmegCore NutmegLib)
