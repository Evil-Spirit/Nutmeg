 
set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT})

set(NUTMEG_CORE_AUDIO_SRC Audio/AbstractAudio.cpp
							Audio/AbstractAudio.h)
set(NUTMEG_CORE_COMMON_SRC Common/Debug.cpp
							Common/Debug.h
							Common/File.cpp
							Common/File.h
							Common/Log.cpp
							Common/Log.h
							Common/Resource.cpp
							Common/Resource.h
							Common/Str.cpp
							Common/Str.h
							Common/Xml.cpp
							Common/Xml.h)
set(NUTMEG_CORE_ENGINE_SRC Engine/Application.cpp
							Engine/Application.h
							Engine/Console.cpp
							Engine/Console.h
							Engine/Engine.cpp
							Engine/Engine.h
							Engine/Profiler.cpp
							Engine/Profiler.h
							Engine/Subsystem.cpp
							Engine/Subsystem.h
							Engine/Timer.cpp
							Engine/Timer.h)
set(NUTMEG_CORE_GAME_SRC Game/Entity.cpp
							Game/Entity.h
							Game/Game.cpp
							Game/Game.h
							Game/Level.cpp
							Game/Level.h)
set(NUTMEG_CORE_MATH_SRC Math/MathCore.cpp
							Math/MathCore.h)
set(NUTMEG_CORE_PHYSICS_SRC Physics/AbstractPhysics.cpp
							Physics/AbstractPhysics.h)
set(NUTMEG_CORE_PLATFORM_SRC Platform/AbstractPlatform.cpp
							Platform/AbstractPlatform.h
							Platform/Input.cpp
							Platform/Input.h)
set(NUTMEG_CORE_RENDER_SRC Render/AbstractRender.cpp
							Render/AbstractRender.h
							Render/Camera.cpp
							Render/Camera.h
							Render/Light.cpp
							Render/Light.h
							Render/Material.cpp
							Render/Material.h
							Render/Mesh.cpp
							Render/Mesh.h
							Render/Skeleton.cpp
							Render/Skeleton.h
							Render/Sprite.cpp
							Render/Sprite.h)
set(NUTMEG_CORE_SCENE_SRC Scene/BoneNode.cpp
							Scene/BoneNode.h
							Scene/CameraNode.cpp
							Scene/CameraNode.h
							Scene/ControllerNode.cpp
							Scene/ControllerNode.h
							Scene/EntityNode.cpp
							Scene/EntityNode.h
							Scene/LightNode.cpp
							Scene/LightNode.h
							Scene/MeshNode.cpp
							Scene/MeshNode.h
							Scene/Node.cpp
							Scene/Node.h
							Scene/OriginNode.cpp
							Scene/OriginNode.h
							Scene/ParticleNode.cpp
							Scene/ParticleNode.h
							Scene/ParticleSystemNode.cpp
							Scene/ParticleSystemNode.h
							Scene/PhysicsNode.cpp
							Scene/PhysicsNode.h
							Scene/Scene.cpp
							Scene/Scene.h
							Scene/SkinnedMeshNode.cpp
							Scene/SkinnedMeshNode.h
							Scene/TextNode.cpp
							Scene/TextNode.h
							Scene/TriggerNode.cpp
							Scene/TriggerNode.h)
							
set(NUTMEG_SRC ${NUTMEG_CORE_AUDIO_SRC} ${NUTMEG_CORE_COMMON_SRC} ${NUTMEG_CORE_ENGINE_SRC}
				${NUTMEG_CORE_GAME_SRC} ${NUTMEG_CORE_MATH_SRC} ${NUTMEG_CORE_PHYSICS_SRC}
				${NUTMEG_CORE_PLATFORM_SRC} ${NUTMEG_CORE_RENDER_SRC} ${NUTMEG_CORE_SCENE_SRC})
if(LINUX)
set(NUTMEG_PLATFORM_LIBS X11)
endif()

add_library(NutmegCore SHARED ${NUTMEG_SRC})
target_link_libraries(NutmegCore IL ILU ILUT GL Newton ${NUTMEG_PLATFORM_LIBS})