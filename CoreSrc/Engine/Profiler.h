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

#ifndef ProfilerH
#define ProfilerH

//------------------------------------------------------------------------------

#include "Timer.h"
#include "Array.h"
#include "Str.h"
#include "MathCore.h"
#include "Subsystem.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class AbstractRender;

	//--------------------------------------------------------------------------
	//
	// class Profiler
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Profiler : public Subsystem <Profiler> {

		struct ProfilerInfo {

			Str name;
			FPSTimer timer;
			vec3 color;
			bool finished;

			ProfilerInfo(const char *n, const vec3 &c);
			void start();
			void finish();

		};

		Array <ProfilerInfo> profilers;
		Array <ProfilerInfo> started;
		bool visible;

	public:

		Profiler(Engine *engine);

		void start(const char *name, const vec3 &color = vec3(1.0f, 1.0f, 1.0f));
		void finish();
		void update(float dt);
		void render(AbstractRender *r);
		void setVisible(bool state);
		bool isVisible() const;

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
