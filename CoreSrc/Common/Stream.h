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

#ifndef StreamH
#define StreamH

//------------------------------------------------------------------------------

#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Stream
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Stream {

	public:
		
		virtual ~Stream() {};

		virtual int size() = 0;
		virtual int tell() = 0;
		virtual void seek(int) = 0;

		virtual void readData(void *data, int size) const = 0;
		virtual void writeData(const void *data, int size) = 0;

		template <class T> void readPlain(T &c) const { 
			readData(&c, sizeof(c)); 
		}

		template <class T> void writePlain(const T &c) {	
			writeData(&c, sizeof(c)); 
		}
		
	};

	//--------------------------------------------------------------------------

}
//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
