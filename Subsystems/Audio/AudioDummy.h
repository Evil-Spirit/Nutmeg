
//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Cyril Bazhenov
//
//------------------------------------------------------------------------------

#ifndef AudioDummyH
#define AudioDummyH

//------------------------------------------------------------------------------

#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class AbstractAudio;
	class Engine;

	//--------------------------------------------------------------------------

	NUTMEG_API bool isAudioDummySupported();
	NUTMEG_API AbstractAudio *createAudioDummy(Engine *engine);

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
