// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sUpDown.pas' rev: 6.00

#ifndef sUpDownHPP
#define sUpDownHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
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

namespace Supdown
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsDrawingState { dsDefault, dsPrevUp, dsNextUp, dsPrevDown, dsNextDown };
#pragma option pop

#pragma option push -b-
enum TsBtnKind { sbkTop, sbkLeft, sbkBottom, sbkRight };
#pragma option pop

class DELPHICLASS TsUpDown;
class PASCALIMPLEMENTATION TsUpDown : public Comctrls::TCustomUpDown 
{
	typedef Comctrls::TCustomUpDown inherited;
	
private:
	bool FShowInaccessibility;
	Sconst::TsDisabledKind FDisabledKind;
	TsDrawingState FDrawingState;
	AnsiString FButtonSkin;
	void __fastcall SetShowInaccessibility(const bool Value);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	void __fastcall SetDrawingState(const TsDrawingState Value);
	void __fastcall SetSkinSection(const AnsiString Value);
	
protected:
	bool Pressed;
	Types::TRect __fastcall BtnRect();
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	void __fastcall DrawBtn(Graphics::TBitmap* Btn, TsBtnKind Kind);
	__fastcall virtual TsUpDown(Classes::TComponent* AOwner);
	__property TsDrawingState DrawingState = {read=FDrawingState, write=SetDrawingState, default=0};
	
__published:
	__property Align  = {default=0};
	__property AlignButton  = {default=1};
	__property Anchors  = {default=3};
	__property Associate ;
	__property ArrowKeys  = {default=1};
	__property Enabled  = {default=1};
	__property Hint ;
	__property Min ;
	__property Max  = {default=100};
	__property Increment  = {default=1};
	__property Constraints ;
	__property Orientation  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property Position ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property Thousands  = {default=1};
	__property Visible  = {default=1};
	__property Wrap ;
	__property OnChanging ;
	__property OnChangingEx ;
	__property OnContextPopup ;
	__property OnClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property AnsiString ButtonSkin = {read=FButtonSkin, write=SetSkinSection};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property bool ShowInaccessibility = {read=FShowInaccessibility, write=SetShowInaccessibility, default=1};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsUpDown(HWND ParentWindow) : Comctrls::TCustomUpDown(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TsUpDown(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Supdown */
using namespace Supdown;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sUpDown
