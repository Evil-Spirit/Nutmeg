// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sComboEdit.pas' rev: 6.00

#ifndef sComboEditHPP
#define sComboEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <MaskUtils.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <ToolWin.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Scomboedit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsComboEdit;
class PASCALIMPLEMENTATION TsComboEdit : public Scustomcomboedit::TsCustomComboEdit 
{
	typedef Scustomcomboedit::TsCustomComboEdit inherited;
	
public:
	__fastcall virtual TsComboEdit(Classes::TComponent* AOwner);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall AfterConstruction(void);
	
__published:
	__property Alignment  = {default=0};
	__property CharCase  = {default=0};
	__property ClickKey  = {default=32808};
	__property DirectInput  = {default=1};
	__property EditMask ;
	__property Enabled  = {default=1};
	__property Font ;
	__property HideSelection  = {default=1};
	__property Anchors  = {default=3};
	__property BiDiMode ;
	__property Constraints ;
	__property DragKind  = {default=0};
	__property ParentBiDiMode  = {default=1};
	__property ImeMode  = {default=3};
	__property ImeName ;
	__property MaxLength  = {default=0};
	__property OEMConvert  = {default=0};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ReadOnly  = {default=0};
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Text ;
	__property Visible  = {default=1};
	__property OnButtonClick ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property OnContextPopup ;
	__property OnEndDock ;
	__property OnStartDock ;
	__property AutoSelect  = {default=1};
	__property HelpContext  = {default=0};
	__property PasswordChar  = {default=0};
	__property Hint ;
	__property DragCursor  = {default=-12};
	__property OnEnter ;
	__property OnExit ;
public:
	#pragma option push -w-inl
	/* TsCustomComboEdit.Destroy */ inline __fastcall virtual ~TsComboEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsComboEdit(HWND ParentWindow) : Scustomcomboedit::TsCustomComboEdit(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Scomboedit */
using namespace Scomboedit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sComboEdit
