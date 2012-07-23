// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sMessages.pas' rev: 6.00

#ifndef sMessagesHPP
#define sMessagesHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Smessages
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct TacSectionInfo
{
	int SkinIndex;
	AnsiString Name;
	bool RepaintNeeded;
} ;
#pragma pack(pop)

typedef TacSectionInfo *PacSectionInfo;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE unsigned SM_ALPHACMD;
static const Shortint AC_SETNEWSKIN = 0x1;
static const Shortint AC_REMOVESKIN = 0x2;
static const Shortint AC_REFRESH = 0x3;
static const Shortint AC_GETPROVIDER = 0x4;
static const Shortint AC_GETCACHE = 0x5;
static const Shortint AC_ENDPARENTUPDATE = 0x6;
static const Shortint AC_CTRLHANDLED = 0x7;
static const Shortint AC_UPDATING = 0x8;
static const Shortint AC_URGENTPAINT = 0x9;
static const Shortint AC_PREPARING = 0xa;
static const Shortint AC_GETHALFVISIBLE = 0xb;
static const Shortint AC_UPDATESECTION = 0xd;
static const Shortint AC_DROPPEDDOWN = 0xe;
static const Shortint AC_SETSECTION = 0xf;
static const Shortint AC_STOPFADING = 0x10;
static const Shortint AC_SETBGCHANGED = 0x11;
static const Shortint AC_INVALIDATE = 0x12;
static const Shortint AC_CHILDCHANGED = 0x13;
static const Shortint AC_SETCHANGEDIFNECESSARY = 0x14;
static const Shortint AC_GETCONTROLCOLOR = 0x15;
static const Shortint AC_SETHALFVISIBLE = 0x16;
static const Shortint AC_PREPARECACHE = 0x17;
static const Shortint AC_DRAWANIMAGE = 0x18;
static const Shortint AC_CONTROLLOADED = 0x19;
static const Shortint AC_GETSKININDEX = 0x1a;
static const Shortint AC_GETSERVICEINT = 0x1b;
static const Shortint AC_UPDATECHILDREN = 0x1c;
static const Shortint AC_MOUSEENTER = 0x1d;
static const Shortint AC_MOUSELEAVE = 0x1e;
static const Shortint AC_BEGINUPDATE = 0x1f;
static const Shortint AC_ENDUPDATE = 0x20;
static const Shortint AC_GETBG = 0x22;
static const Shortint AC_GETDISKIND = 0x23;
static const Shortint AC_GETSKINSTATE = 0x24;
static const Shortint AC_PRINTING = 0x26;
static const Shortint AC_BEFORESCROLL = 0x33;
static const Shortint AC_AFTERSCROLL = 0x34;
static const Shortint AC_GETAPPLICATION = 0x3c;
static const Shortint AC_PARENTCLOFFSET = 0x3d;
static const Word WM_DRAWMENUBORDER = 0xbcb3;
static const Word WM_DRAWMENUBORDER2 = 0xbcb4;

}	/* namespace Smessages */
using namespace Smessages;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sMessages
