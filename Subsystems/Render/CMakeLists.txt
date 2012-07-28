set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_RENDER_SRC RenderBadaOpenGL1.cpp RenderBadaOpenGL1.h
						RenderOpenGL1.cpp RenderOpenGL1.h
						RenderOpenGL2.cpp RenderOpenGL2.h
						RenderPlugin.cpp)

add_library(NutmegRender SHARED ${NUTMEG_RENDER_SRC})
target_link_libraries(NutmegRender NutmegCore GL)
