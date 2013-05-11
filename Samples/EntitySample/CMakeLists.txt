
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

ADD_EXECUTABLE (EntitySample ${SRC} ${HDR})
TARGET_LINK_LIBRARIES (EntitySample NutmegCore NutmegLib)
