// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sSpinEdit.pas' rev: 6.00

#ifndef sSpinEditHPP
#define sSpinEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sSpeedButton.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sEdit.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sspinedit
{
//-- type declarations -------------------------------------------------------
typedef Buttons::TNumGlyphs TNumGlyphs;

class DELPHICLASS TsSpinButton;
class DELPHICLASS TsSpinEdit;
class DELPHICLASS TsBaseSpinEdit;
class PASCALIMPLEMENTATION TsBaseSpinEdit : public Sedit::TsEdit 
{
	typedef Sedit::TsEdit inherited;
	
private:
	TsSpinButton* FButton;
	bool FEditorEnabled;
	Classes::TNotifyEvent FOnUpClick;
	Classes::TNotifyEvent FOnDownClick;
	Classes::TAlignment FAlignment;
	int __fastcall GetMinHeight(void);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	MESSAGE void __fastcall WMPaste(Messages::TWMNoParams &Message);
	MESSAGE void __fastcall WMCut(Messages::TWMNoParams &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Message);
	void __fastcall SetAlignment(const Classes::TAlignment Value);
	
protected:
	void __fastcall SetEditRect(void);
	virtual bool __fastcall IsValidChar(char &Key);
	virtual void __fastcall UpClick(System::TObject* Sender) = 0 ;
	virtual void __fastcall DownClick(System::TObject* Sender) = 0 ;
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(char &Key);
	virtual void __fastcall PaintText(void);
	virtual void __fastcall PrepareCache(void);
	
public:
	__fastcall virtual TsBaseSpinEdit(Classes::TComponent* AOwner);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall CreateWnd(void);
	__fastcall virtual ~TsBaseSpinEdit(void);
	DYNAMIC void __fastcall GetChildren(Classes::TGetChildProc Proc, Classes::TComponent* Root);
	__property TsSpinButton* Button = {read=FButton};
	__property CharCase  = {default=0};
	virtual void __fastcall Loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=0};
	__property bool EditorEnabled = {read=FEditorEnabled, write=FEditorEnabled, default=1};
	__property Classes::TNotifyEvent OnDownClick = {read=FOnDownClick, write=FOnDownClick};
	__property Classes::TNotifyEvent OnUpClick = {read=FOnUpClick, write=FOnUpClick};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsBaseSpinEdit(HWND ParentWindow) : Sedit::TsEdit(ParentWindow) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsSpinEdit : public TsBaseSpinEdit 
{
	typedef TsBaseSpinEdit inherited;
	
private:
	int FMinValue;
	int FMaxValue;
	int FIncrement;
	int __fastcall GetValue(void);
	int __fastcall CheckValue(int NewValue);
	void __fastcall SetValue(int NewValue);
	HIDESBASE MESSAGE void __fastcall CMExit(Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseWheel(Controls::TCMMouseWheel &Message);
	
protected:
	virtual bool __fastcall IsValidChar(char &Key);
	virtual void __fastcall UpClick(System::TObject* Sender);
	virtual void __fastcall DownClick(System::TObject* Sender);
	
public:
	__fastcall virtual TsSpinEdit(Classes::TComponent* AOwner);
	
__published:
	__property int Increment = {read=FIncrement, write=FIncrement, default=1};
	__property int MaxValue = {read=FMaxValue, write=FMaxValue, nodefault};
	__property int MinValue = {read=FMinValue, write=FMinValue, nodefault};
	__property int Value = {read=GetValue, write=SetValue, nodefault};
public:
	#pragma option push -w-inl
	/* TsBaseSpinEdit.Destroy */ inline __fastcall virtual ~TsSpinEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsSpinEdit(HWND ParentWindow) : TsBaseSpinEdit(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsTimerSpeedButton;
#pragma option push -b-
enum sSpinEdit__5 { tbFocusRect, tbAllowTimer };
#pragma option pop

typedef Set<sSpinEdit__5, tbFocusRect, tbAllowTimer>  TTimeBtnState;

class PASCALIMPLEMENTATION TsTimerSpeedButton : public Sspeedbutton::TsSpeedButton 
{
	typedef Sspeedbutton::TsSpeedButton inherited;
	
private:
	TsSpinButton* FOwner;
	Extctrls::TTimer* FRepeatTimer;
	TTimeBtnState FTimeBtnState;
	void __fastcall TimerExpired(System::TObject* Sender);
	
protected:
	virtual void __fastcall Paint(void);
	virtual void __fastcall DrawGlyph(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	
public:
	bool Up;
	__fastcall virtual TsTimerSpeedButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TsTimerSpeedButton(void);
	void __fastcall PaintTo(HDC DC, const Types::TPoint &P);
	__property TTimeBtnState TimeBtnState = {read=FTimeBtnState, write=FTimeBtnState, nodefault};
};


class PASCALIMPLEMENTATION TsSpinButton : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	TsSpinEdit* FOwner;
	TsTimerSpeedButton* FUpButton;
	TsTimerSpeedButton* FDownButton;
	TsTimerSpeedButton* FFocusedButton;
	Controls::TWinControl* FFocusControl;
	Classes::TNotifyEvent FOnUpClick;
	Classes::TNotifyEvent FOnDownClick;
	TsTimerSpeedButton* __fastcall CreateButton(void);
	Graphics::TBitmap* __fastcall GetUpGlyph(void);
	Graphics::TBitmap* __fastcall GetDownGlyph(void);
	void __fastcall SetUpGlyph(Graphics::TBitmap* Value);
	void __fastcall SetDownGlyph(Graphics::TBitmap* Value);
	void __fastcall BtnClick(System::TObject* Sender);
	void __fastcall BtnMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall SetFocusBtn(TsTimerSpeedButton* Btn);
	HIDESBASE void __fastcall AdjustSize(int &W, int &H);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	HIDESBASE void __fastcall PaintTo(HDC DC, const Types::TPoint &P);
	__fastcall virtual TsSpinButton(Classes::TComponent* AOwner);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property Constraints ;
	__property Ctl3D ;
	__property Graphics::TBitmap* DownGlyph = {read=GetDownGlyph, write=SetDownGlyph};
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Controls::TWinControl* FocusControl = {read=FFocusControl, write=FFocusControl};
	__property ParentCtl3D  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property Graphics::TBitmap* UpGlyph = {read=GetUpGlyph, write=SetUpGlyph};
	__property Visible  = {default=1};
	__property Classes::TNotifyEvent OnDownClick = {read=FOnDownClick, write=FOnDownClick};
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property Classes::TNotifyEvent OnUpClick = {read=FOnUpClick, write=FOnUpClick};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsSpinButton(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TsSpinButton(void) { }
	#pragma option pop
	
};


class DELPHICLASS TsDecimalSpinEdit;
class PASCALIMPLEMENTATION TsDecimalSpinEdit : public TsBaseSpinEdit 
{
	typedef TsBaseSpinEdit inherited;
	
private:
	Extended FValue;
	Extended FMinValue;
	Extended FMaxValue;
	Extended FIncrement;
	int fDecimalPlaces;
	bool FUseSystemDecSeparator;
	Extended __fastcall CheckValue(Extended NewValue);
	void __fastcall SetValue(Extended NewValue);
	void __fastcall SetDecimalPlaces(int New);
	HIDESBASE MESSAGE void __fastcall CMExit(Messages::TWMNoParams &Message);
	void __fastcall FormatText(void);
	HIDESBASE MESSAGE void __fastcall CMChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseWheel(Controls::TCMMouseWheel &Message);
	Extended __fastcall GetValue(void);
	
protected:
	bool ValueChanging;
	bool TextChanging;
	virtual bool __fastcall IsValidChar(char &Key);
	virtual void __fastcall UpClick(System::TObject* Sender);
	virtual void __fastcall DownClick(System::TObject* Sender);
	
public:
	__fastcall virtual TsDecimalSpinEdit(Classes::TComponent* AOwner);
	virtual void __fastcall CreateWnd(void);
	
__published:
	__property Extended Increment = {read=FIncrement, write=FIncrement};
	__property Extended MaxValue = {read=FMaxValue, write=FMaxValue};
	__property Extended MinValue = {read=FMinValue, write=FMinValue};
	__property Extended Value = {read=GetValue, write=SetValue};
	__property int DecimalPlaces = {read=fDecimalPlaces, write=SetDecimalPlaces, default=2};
	__property bool UseSystemDecSeparator = {read=FUseSystemDecSeparator, write=FUseSystemDecSeparator, default=1};
public:
	#pragma option push -w-inl
	/* TsBaseSpinEdit.Destroy */ inline __fastcall virtual ~TsDecimalSpinEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsDecimalSpinEdit(HWND ParentWindow) : TsBaseSpinEdit(ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TacTimePortion { tvHours, tvMinutes, tvSeconds };
#pragma option pop

class DELPHICLASS TsTimePicker;
class PASCALIMPLEMENTATION TsTimePicker : public TsBaseSpinEdit 
{
	typedef TsBaseSpinEdit inherited;
	
private:
	Word fHour;
	Word fMin;
	Word fSec;
	bool FDoBeep;
	bool FShowSeconds;
	bool FUse12Hour;
	System::TDateTime __fastcall GetValue(void);
	void __fastcall SetValue(System::TDateTime NewValue);
	System::TDateTime __fastcall CheckValue(System::TDateTime NewValue);
	HIDESBASE MESSAGE void __fastcall CMExit(Messages::TWMNoParams &Message);
	void __fastcall SetShowSeconds(const bool Value);
	void __fastcall SetUse12Hour(const bool Value);
	
protected:
	int FPos;
	virtual bool __fastcall IsValidChar(char &Key);
	virtual void __fastcall UpClick(System::TObject* Sender);
	virtual void __fastcall DownClick(System::TObject* Sender);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall SetHour(int NewHour);
	void __fastcall SetMin(int NewMin);
	void __fastcall SetSec(int NewSec);
	void __fastcall DecodeValue(void);
	TacTimePortion __fastcall Portion(void);
	void __fastcall SetPos(int NewPos, bool Highlight = true);
	void __fastcall IncPos(void);
	void __fastcall ReplaceAtPos(int APos, char AChar);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(char &Key);
	void __fastcall HighlightPos(int APos);
	DYNAMIC void __fastcall Change(void);
	AnsiString __fastcall EmptyText();
	int __fastcall TextLength(void);
	Word __fastcall Sec(void);
	
public:
	int MaxHour;
	__fastcall virtual TsTimePicker(Classes::TComponent* AOwner);
	virtual void __fastcall Loaded(void);
	
__published:
	__property System::TDateTime Date = {read=GetValue, write=SetValue};
	__property bool DoBeep = {read=FDoBeep, write=FDoBeep, default=0};
	__property System::TDateTime Value = {read=GetValue, write=SetValue};
	__property System::TDateTime Time = {read=GetValue, write=SetValue};
	__property bool ShowSeconds = {read=FShowSeconds, write=SetShowSeconds, default=1};
	__property bool Use12Hour = {read=FUse12Hour, write=SetUse12Hour, default=0};
public:
	#pragma option push -w-inl
	/* TsBaseSpinEdit.Destroy */ inline __fastcall virtual ~TsTimePicker(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsTimePicker(HWND ParentWindow) : TsBaseSpinEdit(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word InitRepeatPause = 0x190;
static const Shortint RepeatPause = 0x64;

}	/* namespace Sspinedit */
using namespace Sspinedit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sSpinEdit
