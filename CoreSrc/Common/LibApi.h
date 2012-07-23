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

#ifndef LibApiH
#define LibApiH

//------------------------------------------------------------------------------

#if defined(NUTMEG_BUILD_DLL)
	#define NUTMEG_API __declspec(dllexport)
#elif defined(NUTMEG_USE_DLL)
	#define NUTMEG_API __declspec(dllimport)
#else
	#define NUTMEG_API
#endif

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
