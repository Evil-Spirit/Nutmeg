set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_AUDIO_SUBSYSTEM_SRC AudioBada.cpp AudioBada.h
								AudioDummy.cpp AudioDummy.h
								AudioSquall.cpp AudioSquall.h
								AudioPlugin.cpp)

add_library(NutmegAudio SHARED ${NUTMEG_AUDIO_SUBSYSTEM_SRC})
