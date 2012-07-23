//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// url:			http://nutmeg-engine.ru
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#include "Engine.h"

//------------------------------------------------------------------------------

#include <stdio.h>
//#include "Assert.h"
#include "Log.h"
#include "Scene.h"

// subsystems
#include "AbstractPlatform.h"
#include "AbstractRender.h"
#include "AbstractAudio.h"
#include "AbstractPhysics.h"
#include "Console.h"
#include "Profiler.h"
#include "Resource.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Engine
	//
	//--------------------------------------------------------------------------

	Engine::Engine() {

		application = NULL;

		resizing_redraw = false;

		subsystem_core_id = "null";
		subsystem_render_id = "null";
		subsystem_audio_id = "null";
		subsystem_physics_id = "null";

	}

	//--------------------------------------------------------------------------

	int Engine::execute(Application *application_, int argc, const char **argv) {

		int result = -1;
		try {

			//------------------------------------------------------------------

			application = application_;
			assert(application != NULL);

			//------------------------------------------------------------------
			// platform
			//------------------------------------------------------------------

			platform = AbstractPlatform::createImplementation(subsystem_core_id, this);

			if (platform == NULL) {
				fatal("Engine::execute(): can not create Core with id \"%s\".\n", subsystem_core_id.str());
				return 1;
			}

			//------------------------------------------------------------------
			// main
			//------------------------------------------------------------------

			result = platform->main(this, argc, argv);

		} catch (const char *str) {
			platform->message(str, "Error");
			return 1;
		} catch (...) {
			platform->message("Unknown", "Error");
			return 1;
		}

		delete platform;
		platform = NULL;

		return result;

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------

	void Engine::halt() {
		platform->halt();
	}

	//--------------------------------------------------------------------------

	Application *Engine::getApplication() {
		return application;
	}

	//--------------------------------------------------------------------------

	void Engine::onStartup(int argc, const char **argv) {

		//----------------------------------------------------------------------
		// console
		//----------------------------------------------------------------------

		console = new Console(this);

		//----------------------------------------------------------------------
		// profiler
		//----------------------------------------------------------------------

		profiler = new Profiler(this);

		//----------------------------------------------------------------------
		// render
		//----------------------------------------------------------------------

		AbstractRender::init();
		render = AbstractRender::create(subsystem_render_id);

		if (render == NULL) {
			fatal("Engine::onStartup(): can not create Render with id \"%s\".\n", subsystem_render_id.str());
		}

		render->init(this, argc, argv);

		//----------------------------------------------------------------------
		// audio
		//----------------------------------------------------------------------

		audio = AbstractAudio::createImplementation(subsystem_audio_id, this);

		if (audio == NULL) {
			fatal("Engine::onStartup(): can not create Audio with id \"%s\".\n", subsystem_audio_id.str());
		}

		//----------------------------------------------------------------------
		// physics
		//----------------------------------------------------------------------

		AbstractPhysics::init();

		//----------------------------------------------------------------------
		// resource manager
		//----------------------------------------------------------------------

		resource_manager = new ResourceManager(this);

		//----------------------------------------------------------------------
		// system variables
		//----------------------------------------------------------------------

		platform->initSystemVariables(this);
		console->initSystemVariables(this);
		profiler->initSystemVariables(this);
		//render->initSystemVariables(this);
		audio->initSystemVariables(this);
		//physics->initSystemVariables(this);
		resource_manager->initSystemVariables(this);
		application->initSystemVariables(this);

		//----------------------------------------------------------------------
		// startup
		//----------------------------------------------------------------------

		resource_manager->onStartup(argc, argv);
		console->onStartup(argc, argv);
		platform->onStartup(argc, argv);
		profiler->onStartup(argc, argv);
		//render->onStartup(argc, argv);
		audio->onStartup(argc, argv);
		//physics->onStartup(argc, argv);
		application->onStartup(argc, argv);

		//----------------------------------------------------------------------
		// console
		//----------------------------------------------------------------------

		console->addVariable("engine.resizing_redraw", &resizing_redraw);

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------

	void Engine::onShutdown() {

		if (application != NULL) application->onShutdown();
		if (audio != NULL) audio->onShutdown();
		if (render != NULL) render->shutdown();
		if (console != NULL) console->onShutdown();
		if (resource_manager != NULL) resource_manager->onShutdown();

		delete application;
		application = NULL;

		delete profiler;
		profiler = NULL;

		delete console;
		console = NULL;

		delete resource_manager;
		resource_manager = NULL;

		delete audio;
		audio = NULL;

		delete render;
		render = NULL;

	}

	//--------------------------------------------------------------------------
	// system events
	//--------------------------------------------------------------------------

	void Engine::onRender() {

		application->onRender();

		render->begin2d(-1, -1);
		console->onRender();
		profiler->render(render);
		platform->onRender();
		render->end2d();

	}

	//--------------------------------------------------------------------------

	void Engine::onUpdate(float dt) {

		resource_manager->onUpdate(dt);
		console->onUpdate(dt);
		profiler->update(dt);
		if (console->isActive()) return;

		application->onUpdate(dt);
	}

	//--------------------------------------------------------------------------

	void Engine::onResize(int w, int h) {

		render->setResolution(w, h);
		render->setPixelAspectRatio(platform->getPixelAspectRatio());
		application->onResize(w, h);
		platform->onResize(w, h);

		if (resizing_redraw == true) {
			onRender();
			platform->swap();
		}

	}

	//--------------------------------------------------------------------------

	void Engine::onActivate(bool active) {
		if (audio != NULL) {
			if (active == false) {
				audio->pauseSounds();
			} else {
				audio->resumeSounds();
			}
		}
		if (application != NULL) {
			application->onActivate(active);
		}
		platform->onActivate(active);
	}

	//--------------------------------------------------------------------------

	void Engine::onError(const char *message) {
		application->onError(message);
	}

	//--------------------------------------------------------------------------
	//  input events
	//--------------------------------------------------------------------------

	void Engine::onKeyDown(int key) {
		if (console->isActive()) return;
		application->onKeyDown(key);
	}

	//--------------------------------------------------------------------------

	void Engine::onKeyRepeat(int key) {
		console->processKey(key);
		if (console->isActive()) return;
		application->onKeyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void Engine::onKeyUp(int key) {
		if (console->isActive()) return;
		application->onKeyUp(key);
	}

	//--------------------------------------------------------------------------

	void Engine::onKeyChar(char key) {
		console->processChar(key);
		if (console->isActive()) return;
		application->onKeyChar(key);
	}

	//--------------------------------------------------------------------------

	void Engine::onMouseDoubleClick(int x, int y, int button) {
		if (console->isActive()) return;
		application->onMouseDoubleClick(x, y, button);
	}

	//--------------------------------------------------------------------------

	void Engine::onMouseDown(int x, int y, int button) {
		if (console->isActive()) {
			console->processMouseDown(x, y, button);
			return;
		}
		application->onMouseDown(x, y, button);
	}

	//--------------------------------------------------------------------------

	void Engine::onMouseUp(int x, int y, int button) {
		if (console->isActive()) return;
		application->onMouseUp(x, y, button);
	}

	//--------------------------------------------------------------------------

	void Engine::onMouseMove(int x, int y) {
		if (console->isActive()) return;
		application->onMouseMove(x, y);
	}

	//--------------------------------------------------------------------------

	void Engine::onAccelerationSensor(float x, float y, float z) {
		if (console->isActive()) return;
		application->onAccelerationSensor(x, y, z);
	}

	//--------------------------------------------------------------------------
	// resizing
	//--------------------------------------------------------------------------

	bool Engine::isResizingRedraw() const {
		return resizing_redraw;
	}

	//--------------------------------------------------------------------------

	void Engine::setResizingRedraw(bool state) {
		resizing_redraw = state;
	}

	//--------------------------------------------------------------------------
	// subsystems
	//--------------------------------------------------------------------------

	const char *Engine::getSubsystemCoreId() const {
		return subsystem_core_id;
	}

	//--------------------------------------------------------------------------

	void Engine::setSubsystemCoreId(const char *id) {
		subsystem_core_id = id;
	}

	//--------------------------------------------------------------------------

	const char *Engine::getSubsystemRenderId() const {
		return subsystem_render_id;
	}

	//--------------------------------------------------------------------------

	void Engine::setSubsystemRenderId(const char *id) {
		subsystem_render_id = id;
	}

	//--------------------------------------------------------------------------

	const char *Engine::getSubsystemAudioId() const {
		return subsystem_audio_id;
	}

	//--------------------------------------------------------------------------

	void Engine::setSubsystemAudioId(const char *id) {
		subsystem_audio_id = id;
	}

	//--------------------------------------------------------------------------

	const char *Engine::getSubsystemPhysicsId() const {
		return subsystem_physics_id;
	}

	//--------------------------------------------------------------------------

	void Engine::setSubsystemPhysicsId(const char *id) {
		subsystem_physics_id = id;
	}

	//--------------------------------------------------------------------------

	void Engine::redraw() {
		onRender();
		platform->swap();
	}

	//--------------------------------------------------------------------------

	void Engine::resize() {
		onResize(platform->getWidth(), platform->getHeight());
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

