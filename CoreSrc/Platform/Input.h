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

#ifndef InputH
#define InputH

//------------------------------------------------------------------------------

#include "LibApi.h"

//------------------------------------------------------------------------------

namespace Nutmeg {

	enum KeyScanCode {
		KEY_ESCAPE				= 1,
		KEY_1					= 2,
		KEY_2					= 3,
		KEY_3					= 4,
		KEY_4					= 5,
		KEY_5					= 6,
		KEY_6					= 7,
		KEY_7					= 8,
		KEY_8					= 9,
		KEY_9					= 10,
		KEY_0					= 11,
		KEY_MINUS				= 12,
		KEY_PLUS				= 13,
		KEY_BACKSPACE			= 14,
		KEY_TAB					= 15,
		KEY_Q					= 16,
		KEY_W					= 17,
		KEY_E					= 18,
		KEY_R					= 19,
		KEY_T					= 20,
		KEY_Y					= 21,
		KEY_U					= 22,
		KEY_I					= 23,
		KEY_O					= 24,
		KEY_P					= 25,
		KEY_LBRACKET			= 26,
		KEY_RBRACKET			= 27,
		KEY_ENTER				= 28,
		KEY_CONTROL				= 29,
		KEY_A					= 30,
		KEY_S					= 31,
		KEY_D					= 32,
		KEY_F					= 33,
		KEY_G					= 34,
		KEY_H					= 35,
		KEY_J					= 36,
		KEY_K					= 37,
		KEY_L					= 38,
		KEY_SEMICOLON			= 39,
		KEY_APOSTROPHE			= 40,
		KEY_GRAVE				= 41,
		KEY_LSHIFT				= 42,
		KEY_BACKSLASH			= 43,
		KEY_Z					= 44,
		KEY_X					= 45,
		KEY_C					= 46,
		KEY_V					= 47,
		KEY_B					= 48,
		KEY_N					= 49,
		KEY_M					= 50,
		KEY_COMMA				= 51,
		KEY_PERIOD				= 52,
		KEY_SLASH				= 53,
		KEY_RSHIFT				= 54,
		KEY_MULTIPLY			= 55,
		KEY_LALT				= 56,
		KEY_SPACE				= 57,
		KEY_CAPS_LOCK			= 58,
		KEY_F1					= 59,
		KEY_F2					= 60,
		KEY_F3					= 61,
		KEY_F4					= 62,
		KEY_F5					= 63,
		KEY_F6					= 64,
		KEY_F7					= 65,
		KEY_F8					= 66,
		KEY_F9					= 67,
		KEY_F10					= 68,
		KEY_NUM_LOCK			= 69,
		KEY_SCROLL_LOCK			= 70,
		KEY_HOME				= 71,
		KEY_UP					= 72,
		KEY_PAGE_UP				= 73,
		KEY_NUM_MINUS			= 74,
		KEY_LEFT				= 75,
		KEY_NUM_5				= 76,
		KEY_RIGHT				= 77,
		KEY_NUM_PLUS			= 78,
		KEY_END					= 79,
		KEY_DOWN				= 80,
		KEY_PAGE_DOWN			= 81,
		KEY_INSERT				= 82,
		KEY_DELETE				= 83,
		KEY_84					= 84,
		KEY_85					= 85,
		KEY_86					= 86,
		KEY_F11					= 87,
		KEY_F12					= 88,
		KEY_89					= 89,
		KEY_90					= 90,
		KEY_91					= 91,
		KEY_F92					= 92,
		KEY_F93					= 93,
		KEY_POWER				= 94,
		KEY_SLEEP				= 95,
		KEY_96					= 96,
		KEY_97					= 97,
		KEY_98					= 98,
		KEY_WAKE				= 99,
		KEY_COUNT,
		KEY_MUST_BE_INT			= -2 * 0xFFFF
	};

	enum MouseButton {
		WHEEL_DOWN			= -2,
		WHEEL_UP			= -1,
		BUTTON_LEFT			= 0,
		BUTTON_RIGHT		= 1,
		BUTTON_MIDDLE		= 2,
		BUTTON_COUNT,
		BUTTON_MUST_BE_INT	= -2 * 0xFFFF
	};

	NUTMEG_API const char *getKeyName(int scan_code);
	NUTMEG_API int getKeyByName(const char *name);

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
