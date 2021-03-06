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

#ifndef LightH
#define LightH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Light
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Light {

	public:

		vec3 pos;
		vec3 color;
		vec3 attenuation;
		vec3 direction;
		float radius;

		Light();

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

