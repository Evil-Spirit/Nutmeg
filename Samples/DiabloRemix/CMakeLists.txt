
FILE (GLOB SRC Source/*.cpp)
FILE (GLOB HDR Source/*.h)

ADD_EXECUTABLE (DiabloRemix ${SRC} ${HDR})
TARGET_LINK_LIBRARIES (DiabloRemix NutmegCore NutmegLib)
