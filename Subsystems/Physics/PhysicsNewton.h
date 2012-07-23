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

#ifndef PhysicsNewtonH
#define PhysicsNewtonH

//------------------------------------------------------------------------------

#include "AbstractPhysics.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	bool isNewtonPhysicsSupported();
	PhysicsWorld *createNewtonPhysics();
		
}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

