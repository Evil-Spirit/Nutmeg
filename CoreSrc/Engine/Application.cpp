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

#include "Application.h"

//------------------------------------------------------------------------------

#include <stdio.h>
#include "Debug.h"
#include "Engine.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Application
	//
	//--------------------------------------------------------------------------

	Application::Application() {
		engine = NULL;
		platform = NULL;
		render = NULL;
		audio = NULL;
		console = NULL;
		profiler = NULL;
		resource_manager = NULL;
	}

	//--------------------------------------------------------------------------

	Application::~Application() { }

	//--------------------------------------------------------------------------

	void Application::initSystemVariables(Engine *engine_) {

		engine = engine_;
		assert(engine != NULL);

		platform = engine->getPlatform();
		render = engine->getRender();
		audio = engine->getAudio();
		console = engine->getConsole();
		profiler = engine->getProfiler();
		resource_manager = engine->getResourceManager();

	}

	//--------------------------------------------------------------------------
	// system events
	//--------------------------------------------------------------------------

	void Application::onStartup(int argc, const char **argv) { }
	void Application::onShutdown() { }

	void Application::onRender() { }
	void Application::onUpdate(float dt) { }
	void Application::onResize(int w, int h) { }
	void Application::onActivate(bool active) { }

	void Application::onError(const char *message) { }

	//--------------------------------------------------------------------------
	//  input events
	//--------------------------------------------------------------------------

	void Application::onKeyDown(int key) { }
	void Application::onKeyRepeat(int key) { }
	void Application::onKeyUp(int key) { }
	void Application::onKeyChar(char key) { }

	void Application::onMouseDoubleClick(int x, int y, int button) { }
	void Application::onMouseDown(int x, int y, int button) { }
	void Application::onMouseUp(int x, int y, int button) { }
	void Application::onMouseMove(int x, int y) { }

	void Application::onAccelerationSensor(float x, float y, float z) { }

	//--------------------------------------------------------------------------
	// subsystems
	//--------------------------------------------------------------------------

	Engine *Application::getEngine() { return engine; }
	const Engine *Application::getEngine() const { return engine; }

	//--------------------------------------------------------------------------

	AbstractPlatform *Application::getPlatform() { return platform; }
	const AbstractPlatform *Application::getPlatform() const { return platform; }

	//--------------------------------------------------------------------------

	AbstractRender *Application::getRender() { return render; }
	const AbstractRender *Application::getRender() const { return render; }

	//--------------------------------------------------------------------------

	Profiler *Application::getProfiler() { return profiler; }
	const Profiler *Application::getProfiler() const { return profiler; }

	//--------------------------------------------------------------------------

	AbstractAudio *Application::getAudio() { return audio; }
	const AbstractAudio *Application::getAudio() const { return audio; }

	//--------------------------------------------------------------------------

	Console *Application::getConsole() { return console; }
	const Console *Application::getConsole() const { return console; }

	//--------------------------------------------------------------------------

	ResourceManager *Application::getResourceManager() { return resource_manager; }
	const ResourceManager *Application::getResourceManager() const { return resource_manager; }

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
