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

#ifndef EngineH
#define EngineH

//------------------------------------------------------------------------------

#include "Application.h"
#include "LibApi.h"
#include "Str.h"

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

	class NUTMEG_API Engine : public Application {

		//----------------------------------------------------------------------

		Application *application;

		bool resizing_redraw;

		//----------------------------------------------------------------------

		Str subsystem_core_id;
		Str subsystem_render_id;
		Str subsystem_audio_id;
		Str subsystem_physics_id;

		//----------------------------------------------------------------------

	protected:

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
		//  input
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

	public:

		//----------------------------------------------------------------------

		Engine();

		//----------------------------------------------------------------------
		// resizing
		//----------------------------------------------------------------------

		bool isResizingRedraw() const;
		void setResizingRedraw(bool state);

		//----------------------------------------------------------------------
		// subsystems
		//----------------------------------------------------------------------

		const char *getSubsystemCoreId() const;
		void setSubsystemCoreId(const char *id);

		const char *getSubsystemRenderId() const;
		void setSubsystemRenderId(const char *id);

		const char *getSubsystemAudioId() const;
		void setSubsystemAudioId(const char *id);

		const char *getSubsystemPhysicsId() const;
		void setSubsystemPhysicsId(const char *id);

		//----------------------------------------------------------------------
		// execute control
		//----------------------------------------------------------------------

		int execute(Application *application, int argc, const char **argv);
		void halt();

		Application *getApplication();

		//----------------------------------------------------------------------

		void redraw();
		void resize();

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
