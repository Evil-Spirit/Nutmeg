// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sToolBar.pas' rev: 6.00

#ifndef sToolBarHPP
#define sToolBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ToolWin.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
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

namespace Stoolbar
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsToolBar;
class PASCALIMPLEMENTATION TsToolBar : public Comctrls::TToolBar 
{
	typedef Comctrls::TToolBar inherited;
	
private:
	int HotButtonIndex;
	Scommondata::TsCommonData* FCommonData;
	Sconst::TsDisabledKind FDisabledKind;
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TWMNCPaint &Message);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	
protected:
	Comctrls::TToolButton* DroppedButton;
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	int __fastcall OffsetX(void);
	int __fastcall OffsetY(void);
	void __fastcall PrepareCache(void);
	void __fastcall OurAdvancedCustomDraw(Comctrls::TToolBar* Sender, const Types::TRect &ARect, Comctrls::TCustomDrawStage Stage, bool &DefaultDraw);
	void __fastcall OurAdvancedCustomDrawButton(Comctrls::TToolBar* Sender, Comctrls::TToolButton* Button, Comctrls::TCustomDrawState State, Comctrls::TCustomDrawStage Stage, Comctrls::TTBCustomDrawFlags &Flags, bool &DefaultDraw);
	Types::TRect __fastcall GetButtonRect(int Index);
	int __fastcall IndexByMouse(const Types::TPoint &MousePos);
	void __fastcall RepaintButton(int Index);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__fastcall virtual TsToolBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TsToolBar(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	void __fastcall UpdateEvents(void);
	
__published:
	__property Flat  = {default=0};
	__property Sconst::TsDisabledKind BtnDisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsToolBar(HWND ParentWindow) : Comctrls::TToolBar(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Stoolbar */
using namespace Stoolbar;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sToolBar
