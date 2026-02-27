
set(NUTMEG_LIBRARY_SRC OpenGL/OpenGL.cpp OpenGL/OpenGL.h)

add_library(NutmegLib SHARED ${NUTMEG_LIBRARY_SRC})
target_link_libraries(NutmegLib GLEW::GLEW OpenGL::GL)
