set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

if(WIN32)
	# AudioBada is Bada-only; AudioSquall requires the Squall library (not in repo).
	# On Windows, use the dummy backend only.
	set(NUTMEG_AUDIO_SUBSYSTEM_SRC AudioDummy.cpp AudioDummy.h AudioPlugin.cpp)
else()
	set(NUTMEG_AUDIO_SUBSYSTEM_SRC AudioBada.cpp AudioBada.h
								AudioDummy.cpp AudioDummy.h
								AudioSquall.cpp AudioSquall.h
								AudioPlugin.cpp)
endif()

add_library(NutmegAudio SHARED ${NUTMEG_AUDIO_SUBSYSTEM_SRC})
target_link_libraries(NutmegAudio NutmegCore)
