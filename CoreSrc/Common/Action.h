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

#ifndef ActionH
#define ActionH

//------------------------------------------------------------------------------

#include "Array.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	class Event;

	//--------------------------------------------------------------------------
	//
	// class Action
	//
	//--------------------------------------------------------------------------

	class Action {

		friend class Event;

		Event *event;

	protected:
								  
		void setEvent(Event *event_) {
			event = event_;
		}

	
	public:

		Action() {
			event = NULL;
		}

		virtual ~Action();

		virtual void *getInstance() = 0;
		virtual const void *getInstance() const = 0;
		virtual void run() = 0;
	
    	#ifdef __BCPLUSPLUS__
			template <class T>
			static Action *create(T *instance, void (T::*func)(void)) {
				return new ActionTemplate <T> (instance, func);
			}
        #else
			template <class T>
			static Action *create(T *instance, void (T::*func)(void));
        #endif
	
	};

	//--------------------------------------------------------------------------
	//
	// class Event
	//
	//--------------------------------------------------------------------------

	class Event {

		friend class Action;

		Array <Action> actions;
	
	public:

		Event() : actions(false) {
		
		}

		void addAction(Action *action) {
			actions.append(action);
			action->setEvent(this);
		}

		void removeAction(Action *action) {
			int index = actions.seek(action);
			if (index < 0) return;
			actions.remove(index);
		}

		void removeAction(int index) {
			actions[index].setEvent(NULL);
			actions.remove(index);
		}

		void run() {
			for (int i=0; i<actions.count(); i++) {
				actions[i].run();
			}
		}

	};

	//--------------------------------------------------------------------------
	//
	// class Action
	//
	//--------------------------------------------------------------------------

	template <class Instance>
	class ActionTemplate : public Action {
	
		typedef void (Instance::*ActionFunc)(void);
	
		Instance *instance;
		ActionFunc func;
	
	
	public:
	
		//
		ActionTemplate(Instance *instance_, ActionFunc func_) {
			instance = instance_;
			func = func_;
		}
	
		//
		virtual void run() {
			(instance->*func)();
		}
	
		//
		virtual void *getInstance() {
			return instance;
		}

		//
		virtual const void *getInstance() const {
			return instance;
		}
	
	};

	//--------------------------------------------------------------------------

    #ifndef __BCPLUSPLUS__

		template <class T>
		Action *Action::create(T *instance, void (T::*func)(void)) {
			return new ActionTemplate <T> (instance, func);
		}
        
    #endif

	//--------------------------------------------------------------------------

}

#endif

//------------------------------------------------------------------------------
