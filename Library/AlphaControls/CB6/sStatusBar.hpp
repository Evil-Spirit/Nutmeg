// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sStatusBar.pas' rev: 6.00

#ifndef sStatusBarHPP
#define sStatusBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sCommonData.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sstatusbar
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsStatusBar;
class PASCALIMPLEMENTATION TsStatusBar : public Comctrls::TStatusBar 
{
	typedef Comctrls::TStatusBar inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	
protected:
	void __fastcall PaintGrip(void);
	void __fastcall PaintPanels(void);
	int __fastcall PanelOffset(int k);
	HIDESBASE void __fastcall DrawPanel(Comctrls::TStatusPanel* Panel, const Types::TRect &Rect);
	void __fastcall InternalDrawPanel(Comctrls::TStatusPanel* Panel, AnsiString Text, const Types::TRect &Rect);
	void __fastcall DoDrawText(const AnsiString Text, Types::TRect &Rect, int Flags);
	void __fastcall PrepareCache(void);
	void __fastcall OurPaintHandler(HDC MsgDC);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall PaintWindow(HDC DC);
	
public:
	__fastcall virtual TsStatusBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TsStatusBar(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall AfterConstruction(void);
	
__published:
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsStatusBar(HWND ParentWindow) : Comctrls::TStatusBar(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sstatusbar */
using namespace Sstatusbar;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sStatusBar
