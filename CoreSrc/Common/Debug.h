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

#ifndef DebugH
#define DebugH

//------------------------------------------------------------------------------

#include "Settings.h"
#include "LibApi.h"

//------------------------------------------------------------------------------

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)
#define CURRENT_FILE_LINE __FILE__ ":" TO_STRING(__LINE__)
#undef assert

#ifdef NUTMEG_DEBUG

	#if defined(NUTMEG_PLATFORM_BADA)

		#include "FBase.h"

		#define debugLog(...) AppLog(__VA_ARGS__);
		#define fatal(...) AppLog(__VA_ARGS__);
		#define warning(...) AppLog(__VA_ARGS__);
		#define bug(...) AppLog(__VA_ARGS__);

		#define assert(EXP) { \
			if (bool(EXP) == false) { \
				fatal("File: \"" CURRENT_FILE_LINE "\" Assertion failed: " TO_STRING(EXP)); \
			} \
		};

	#else

		#include "Log.h"

		void NUTMEG_API debugLog(const char *fmt, ...);
		void NUTMEG_API fatal(const char *fmt, ...);
		void NUTMEG_API warning(const char *fmt, ...);
		void NUTMEG_API bug(const char *fmt, ...);

		#define assert(EXP) { \
			if (bool(EXP) == false) { \
				fatal("File: \"" CURRENT_FILE_LINE "\n\" Assertion failed:\n" TO_STRING(EXP)); \
			} \
		};

		#define assert_bug(EXP) { \
			if (bool(EXP) == false) { \
				bug("File: \"" CURRENT_FILE_LINE "\n\" Assertion failed:\n" TO_STRING(EXP)); \
			} \
		};


	#endif

#else

	#define assert(EXP)
	#define debugLog(STR)
	#define fatal(STR)
	#define warning(STR)

#endif

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
