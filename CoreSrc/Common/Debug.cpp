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

#include "Debug.h"

//------------------------------------------------------------------------------

#ifndef NUTMEG_PLATFORM_BADA

	//--------------------------------------------------------------------------

	#include "Log.h"
	#include <stdarg.h>
	#include <stdio.h>

	//--------------------------------------------------------------------------

	void debugLog(const char *fmt, ...) {

		#ifdef NUTMEG_DEBUG

			static char str[2048];

			if (fmt == NULL) return;

			va_list	ap;
			va_start(ap, fmt);
			vsprintf(str, fmt, ap);
			va_end(ap);

			Nutmeg::Log::message(str);

		#endif

	}

	//--------------------------------------------------------------------------

	void fatal(const char *fmt, ...) {

		static char str[2048];

		if (fmt == NULL) throw "Unknown fatal error.";

		va_list	ap;
		va_start(ap, fmt);
		vsprintf(str, fmt, ap);
		va_end(ap);

		throw str;

	}

	//--------------------------------------------------------------------------

	void bug(const char *fmt, ...) {

		static char str[2048];

		if (fmt == NULL) throw "Unknown fatal error.";

		va_list	ap;
		va_start(ap, fmt);
		vsprintf(str, fmt, ap);
		va_end(ap);

		throw str;

	}

	//--------------------------------------------------------------------------

	void warning(const char *fmt, ...) {

		#ifdef NUTMEG_DEBUG

			static char str[2048];

			if (fmt == NULL) return;

			va_list	ap;
			va_start(ap, fmt);
			vsprintf(str, fmt, ap);
			va_end(ap);

			Nutmeg::Log::message(str);

		#endif

	}

	//--------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
