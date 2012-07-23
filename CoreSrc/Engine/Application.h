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

#ifndef ApplicationH
#define ApplicationH

//------------------------------------------------------------------------------

#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;
	class AbstractPlatform;
	class AbstractRender;
	class AbstractAudio;
	class Console;
	class Profiler;
	class ResourceManager;

	//--------------------------------------------------------------------------
	//
	// class Application
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Application {

		friend class Engine;

	protected:

		Engine *engine;
		AbstractPlatform *platform;
		AbstractRender *render;
		AbstractAudio *audio;
		Console *console;
		Profiler *profiler;
		ResourceManager *resource_manager;

		//----------------------------------------------------------------------

		void initSystemVariables(Engine *engine);

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		Application();
		virtual ~Application();

		//----------------------------------------------------------------------
		// system events
		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv);
		virtual void onShutdown();

		virtual void onRender();
		virtual void onUpdate(float dt);
		virtual void onResize(int w, int h);
		virtual void onActivate(bool active);

		virtual void onError(const char *message);

		//----------------------------------------------------------------------
		//  input events
		//----------------------------------------------------------------------

		virtual void onKeyDown(int key);
		virtual void onKeyRepeat(int key);
		virtual void onKeyUp(int key);
		virtual void onKeyChar(char key);

		virtual void onMouseDoubleClick(int x, int y, int button);
		virtual void onMouseDown(int x, int y, int button);
		virtual void onMouseUp(int x, int y, int button);
		virtual void onMouseMove(int x, int y);

		virtual void onAccelerationSensor(float x, float y, float z);

		//----------------------------------------------------------------------
		// subsystems
		//----------------------------------------------------------------------

		Engine *getEngine();
		const Engine *getEngine() const;

		AbstractPlatform *getPlatform();
		const AbstractPlatform *getPlatform() const;

		AbstractRender *getRender();
		const AbstractRender *getRender() const;

		AbstractAudio *getAudio();
		const AbstractAudio *getAudio() const;

		Console *getConsole();
		const Console *getConsole() const;

		Profiler *getProfiler();
		const Profiler *getProfiler() const;

		ResourceManager *getResourceManager();
		const ResourceManager *getResourceManager() const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

};

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
