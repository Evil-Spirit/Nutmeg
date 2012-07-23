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

#include "AbstractPlatform.h"

//------------------------------------------------------------------------------

#include "Factory.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

 	IMP_SUBSYSTEM(AbstractPlatform);

	//--------------------------------------------------------------------------
	//
	// struct VideoMode
	//
	//--------------------------------------------------------------------------

	VideoMode::VideoMode() {
		width = 1024;
		height = 768;
		bits = 32;
		frequency = 60;
	}

	//--------------------------------------------------------------------------

	VideoMode::VideoMode(int w, int h, int b) {
		width = w;
		height = h;
		bits = b;
		frequency = 60;
	}

	//--------------------------------------------------------------------------

	VideoMode::VideoMode(int w, int h, int b, int f) {
		width = w;
		height = h;
		bits = b;
		frequency = f;
	}

	//--------------------------------------------------------------------------

	bool VideoMode::operator== (const VideoMode &o) const {
		return width == o.width && height == o.height && bits == o.bits;
	}

	//--------------------------------------------------------------------------

	bool VideoMode::operator!= (const VideoMode &o) const {
		return width != o.width || height != o.height || bits != o.bits;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

