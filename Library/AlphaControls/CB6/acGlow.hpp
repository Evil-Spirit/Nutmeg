// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acGlow.pas' rev: 6.00

#ifndef acGlowHPP
#define acGlowHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Messages.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acglow
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TacGlowEffect;
class PASCALIMPLEMENTATION TacGlowEffect : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Sskinmanager::TsSkinManager* SkinManager;
	int MaskIndex;
	int Margin;
	Forms::TForm* Wnd;
	Graphics::TBitmap* AlphaBmp;
	Classes::TWndMethod OldWndProc;
	__fastcall virtual TacGlowEffect(void);
	virtual void __fastcall CreateAlphaBmp(const int Width, const int Height);
	__fastcall virtual ~TacGlowEffect(void);
	int __fastcall IntBorderWidth(void);
	void __fastcall Show(const Types::TRect &R, const Types::TRect &RealRect, const int Alpha, HWND WndHandle);
	void __fastcall NewWndProc(Messages::TMessage &Message);
};


typedef DynamicArray<TacGlowEffect* >  TacGlowEffects;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall ShowGlow(const Types::TRect &R, const Types::TRect &RealRect, const AnsiString SkinSection, const AnsiString Name, const int Margin, const int Alpha, HWND WndHandle, Sskinmanager::TsSkinManager* SkinManager = (Sskinmanager::TsSkinManager*)(0x0));
extern PACKAGE void __fastcall HideGlow(const int ID);
extern PACKAGE void __fastcall ClearGlows(void);

}	/* namespace Acglow */
using namespace Acglow;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acGlow
