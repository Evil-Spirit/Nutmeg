// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCurrEdit.pas' rev: 6.00

#ifndef sCurrEditHPP
#define sCurrEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <sCalcUnit.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Scurredit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsCustomNumEdit;
class PASCALIMPLEMENTATION TsCustomNumEdit : public Scustomcomboedit::TsCustomComboEdit 
{
	typedef Scustomcomboedit::TsCustomComboEdit inherited;
	
private:
	Controls::TControlCanvas* FCanvas;
	Classes::TAlignment FAlignment;
	bool FFocused;
	Extended FValue;
	Extended FMinValue;
	Extended FMaxValue;
	unsigned FDecimalPlaces;
	bool FBeepOnError;
	bool FCheckOnExit;
	bool FFormatOnEditing;
	bool FFormatting;
	AnsiString *FDisplayFormat;
	void __fastcall SetFocused(bool Value);
	HIDESBASE void __fastcall SetAlignment(Classes::TAlignment Value);
	void __fastcall SetBeepOnError(bool Value);
	void __fastcall SetDisplayFormat(const AnsiString Value);
	AnsiString __fastcall GetDisplayFormat();
	void __fastcall SetDecimalPlaces(unsigned Value);
	Extended __fastcall GetValue(void);
	void __fastcall SetValue(Extended AValue);
	int __fastcall GetAsInteger(void);
	void __fastcall SetMaxValue(Extended AValue);
	void __fastcall SetMinValue(Extended AValue);
	HIDESBASE AnsiString __fastcall GetText();
	HIDESBASE void __fastcall SetText(const AnsiString AValue);
	AnsiString __fastcall TextToValText(const AnsiString AValue);
	Extended __fastcall CheckValue(Extended NewValue, bool RaiseOnError);
	bool __fastcall IsFormatStored(void);
	HIDESBASE MESSAGE void __fastcall CMEnter(Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMExit(Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall WMPaste(Messages::TMessage &Message);
	void __fastcall CalcWindowClose(System::TObject* Sender, Forms::TCloseAction &Action);
	
protected:
	DYNAMIC void __fastcall Change(void);
	DYNAMIC void __fastcall ReformatEditText(void);
	virtual void __fastcall DataChanged(void);
	virtual AnsiString __fastcall DefFormat();
	DYNAMIC void __fastcall KeyPress(char &Key);
	virtual bool __fastcall IsValidChar(char Key);
	AnsiString __fastcall FormatDisplayText(Extended Value);
	virtual AnsiString __fastcall GetDisplayText();
	virtual void __fastcall Reset(void);
	void __fastcall CheckRange(void);
	void __fastcall UpdateData(void);
	__property bool Formatting = {read=FFormatting, nodefault};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=1};
	__property bool BeepOnError = {read=FBeepOnError, write=SetBeepOnError, default=1};
	__property bool CheckOnExit = {read=FCheckOnExit, write=FCheckOnExit, default=0};
	__property unsigned DecimalPlaces = {read=FDecimalPlaces, write=SetDecimalPlaces, default=2};
	__property AnsiString DisplayFormat = {read=GetDisplayFormat, write=SetDisplayFormat, stored=IsFormatStored};
	__property Extended MaxValue = {read=FMaxValue, write=SetMaxValue};
	__property Extended MinValue = {read=FMinValue, write=SetMinValue};
	__property AnsiString Text = {read=GetText, write=SetText, stored=false};
	__property MaxLength  = {default=0};
	virtual void __fastcall PopupWindowShow(void);
	__property ClickKey  = {default=32808};
	virtual void __fastcall PaintText(void);
	
public:
	__fastcall virtual TsCustomNumEdit(Classes::TComponent* AOwner);
	__fastcall virtual ~TsCustomNumEdit(void);
	virtual void __fastcall Clear(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	__property int AsInteger = {read=GetAsInteger, nodefault};
	__property AnsiString DisplayText = {read=GetDisplayText};
	__property DroppedDown ;
	__property Extended Value = {read=GetValue, write=SetValue};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCustomNumEdit(HWND ParentWindow) : Scustomcomboedit::TsCustomComboEdit(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsCalcEdit;
class PASCALIMPLEMENTATION TsCalcEdit : public TsCustomNumEdit 
{
	typedef TsCustomNumEdit inherited;
	
public:
	__property AsInteger ;
	__fastcall virtual TsCalcEdit(Classes::TComponent* AOwner);
	
__published:
	__property ClickKey  = {default=32808};
	__property AutoSelect  = {default=1};
	__property BeepOnError  = {default=1};
	__property DirectInput  = {default=1};
	__property DragCursor  = {default=-12};
	__property Enabled  = {default=1};
	__property Font ;
	__property HideSelection  = {default=1};
	__property ImeMode  = {default=3};
	__property ImeName ;
	__property MaxLength  = {default=0};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupAlign  = {default=0};
	__property PopupMenu ;
	__property ReadOnly  = {default=0};
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property OnButtonClick ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property Alignment  = {default=1};
	__property CheckOnExit  = {default=0};
	__property DecimalPlaces  = {default=2};
	__property DisplayFormat ;
	__property MaxValue ;
	__property MinValue ;
	__property Text ;
	__property Value ;
public:
	#pragma option push -w-inl
	/* TsCustomNumEdit.Destroy */ inline __fastcall virtual ~TsCalcEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCalcEdit(HWND ParentWindow) : TsCustomNumEdit(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Scurredit */
using namespace Scurredit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCurrEdit
