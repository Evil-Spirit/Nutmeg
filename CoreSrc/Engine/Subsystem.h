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

#ifndef SubsystemH
#define SubsystemH

//------------------------------------------------------------------------------

#include "Application.h"
#include "Factory.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;

	//--------------------------------------------------------------------------
	//
	// class Subsystem
	//
	//--------------------------------------------------------------------------

	template <class T>
	class NUTMEG_API Subsystem : public Application {

	protected:

		static Factory <T, Engine *> factory;

	public:

		//----------------------------------------------------------------------

		Subsystem(Engine *engine) {
			initSystemVariables(engine);
		}

		//----------------------------------------------------------------------
		// implementations
		//----------------------------------------------------------------------

		static T *createImplementation(const char *id, Engine *engine) {
			return factory.create(id, engine);
		}

		//----------------------------------------------------------------------

		template <class Implementation>
		static void addImplementation(const char *id) {
			factory.template addType <Implementation> (id);
		}

		//----------------------------------------------------------------------


		static void addImplementation(const char *id, typename Factory <T, Engine *>::CreateFunctionType creator) {
			factory.addType(id, creator);
		}

		//----------------------------------------------------------------------

		static int getImplementationsCount() {
			return factory.getTypesCount();
		}

		//----------------------------------------------------------------------

		static const char *getImplementationName(int index) {
        	return factory.getTypeName(index);
		}

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

	#define IMP_SUBSYSTEM(subsystem) \
		template <> Factory <subsystem, Engine *> Subsystem <subsystem>::factory = Factory <subsystem, Engine *> ();

	//--------------------------------------------------------------------------

};

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
