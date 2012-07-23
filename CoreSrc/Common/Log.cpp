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

#include "Log.h"

//------------------------------------------------------------------------------

#include <stdarg.h>
#include <stdio.h>

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	FILE *file = NULL;

	//--------------------------------------------------------------------------

	Log::Log() {

	}

	//--------------------------------------------------------------------------

	void Log::open(const char *name) {

		#ifndef NUTMEG_PLATFORM_BADA
			close();
			file = fopen(name, "w");
			message("Nutmeg engine\n");
		#endif

	}

	//--------------------------------------------------------------------------

	void Log::close() {

		#ifndef NUTMEG_PLATFORM_BADA
			if (file == NULL) return;

			fclose(file);
			file = NULL;
		#endif
	}

	//--------------------------------------------------------------------------

	void Log::message(const char *fmt, ...) {

		#ifndef NUTMEG_PLATFORM_BADA
			//if (fmt == NULL || file == NULL) return;
			va_list	ap;
			va_start(ap, fmt);
			if (NULL != fmt) {
				if (NULL != file)
					vfprintf(file, fmt, ap);
				vfprintf(stdout, fmt, ap);
			}
			fflush(file);
			va_end(ap);
		#endif
	}

	//--------------------------------------------------------------------------

	void Log::error(const char *fmt, ...) {

		#ifndef NUTMEG_PLATFORM_BADA
			//if (fmt == NULL || file == NULL) return;
			va_list	ap;
			va_start(ap, fmt);
			if (NULL != fmt) {
				if (NULL != file)
					vfprintf(file, fmt, ap);
				vfprintf(stdout, fmt, ap);
			}
			fflush(file);
			va_end(ap);
		#endif

	}

	//--------------------------------------------------------------------------

	void log(const char *fmt, ...) {
		#ifndef NUTMEG_PLATFORM_BADA
			//if (fmt == NULL || file == NULL) return;
			va_list	ap;
			va_start(ap, fmt);
			if (NULL != fmt) {
				if (NULL != file)
					vfprintf(file, fmt, ap);
				vfprintf(stdout, fmt, ap);
			}
			fflush(file);
			va_end(ap);
		#endif
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
