// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sScrollBar.pas' rev: 6.00

#ifndef sScrollBarHPP
#define sScrollBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Types.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <Consts.hpp>	// Pascal unit
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

namespace Sscrollbar
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsScrollBar;
class PASCALIMPLEMENTATION TsScrollBar : public Stdctrls::TScrollBar 
{
	typedef Stdctrls::TScrollBar inherited;
	
private:
	#pragma pack(push, 1)
	Types::TRect FBtn1Rect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect FBtn2Rect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect FBar1Rect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect FBar2Rect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect FSliderRect;
	#pragma pack(pop)
	
	Extctrls::TTimer* Timer;
	int FBtn1State;
	int FBar2State;
	int FBtn2State;
	int FBar1State;
	int FSliderState;
	Scommondata::TsCommonData* FCommonData;
	Sconst::TsDisabledKind FDisabledKind;
	bool MustBeRecreated;
	#pragma pack(push, 1)
	tagSCROLLINFO FSI;
	#pragma pack(pop)
	
	int FCurrPos;
	bool FBeginTrack;
	HIDESBASE bool __fastcall NotRightToLeft(void);
	HIDESBASE MESSAGE void __fastcall CNHScroll(Messages::TWMScroll &Message);
	HIDESBASE MESSAGE void __fastcall CNVScroll(Messages::TWMScroll &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Messages::TWMNCHitTest &Message);
	HIDESBASE MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Msg);
	void __fastcall SetInteger(int Index, int Value);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	Sskinmanager::TsSkinManager* __fastcall GetSkinManager(void);
	void __fastcall SetSkinManager(const Sskinmanager::TsSkinManager* Value);
	
protected:
	Sconst::TCacheInfo CI;
	bool AppShowHint;
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall Paint(HDC MsgDC);
	void __fastcall PlaceToLinked(void);
	void __fastcall InitDontChange(void);
	void __fastcall ClearDontChange(void);
	void __fastcall DrawBtnTop(Graphics::TBitmap* b);
	void __fastcall DrawBtnLeft(Graphics::TBitmap* b);
	void __fastcall DrawBtnRight(Graphics::TBitmap* b);
	void __fastcall DrawBtnBottom(Graphics::TBitmap* b);
	void __fastcall DrawSlider(Graphics::TBitmap* b);
	Types::TRect __fastcall Bar1Rect();
	Types::TRect __fastcall Bar2Rect();
	Types::TRect __fastcall Btn1Rect();
	Types::TRect __fastcall Btn2Rect();
	Types::TRect __fastcall Btn1DRect();
	Types::TRect __fastcall Btn2DRect();
	int __fastcall WorkSize(void);
	Types::TRect __fastcall SliderRect();
	int __fastcall SliderSize(void);
	int __fastcall Btn1SkinIndex(void);
	int __fastcall Btn2SkinIndex(void);
	Types::TPoint __fastcall CoordToPoint(const Types::TPoint &p);
	int __fastcall CoordToPosition(const Types::TPoint &p);
	int __fastcall PositionToCoord(void);
	int __fastcall FirstPoint(void);
	bool __fastcall BarIsHot(void);
	void __fastcall PrepareTimer(void);
	void __fastcall PrepareBtnTimer(void);
	void __fastcall PrepareBarTimer(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	void __fastcall IncPos(int Offset);
	void __fastcall SetPos(int Pos);
	
public:
	int ScrollCode;
	bool RepaintNeeded;
	int MouseOffset;
	bool DrawingForbidden;
	Controls::TWinControl* LinkedControl;
	bool DontChange;
	bool DoSendChanges;
	__fastcall virtual TsScrollBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TsScrollBar(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	void __fastcall UpdateBar(void);
	void __fastcall OnTimer(System::TObject* Sender);
	void __fastcall OnBtnTimer(System::TObject* Sender);
	void __fastcall OnBarTimer(System::TObject* Sender);
	__property int Btn1State = {read=FBtn1State, write=SetInteger, index=0, nodefault};
	__property int Btn2State = {read=FBtn2State, write=SetInteger, index=1, nodefault};
	__property int Bar1State = {read=FBar1State, write=SetInteger, index=2, nodefault};
	__property int Bar2State = {read=FBar2State, write=SetInteger, index=3, nodefault};
	__property int SliderState = {read=FSliderState, write=SetInteger, index=4, nodefault};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	
__published:
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property Sskinmanager::TsSkinManager* SkinManager = {read=GetSkinManager, write=SetSkinManager};
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsScrollBar(HWND ParentWindow) : Stdctrls::TScrollBar(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall UpdateControlScrollBar(Controls::TWinControl* Control, TsScrollBar* &ScrollBar, Forms::TScrollBarKind Kind, bool Free = true);

}	/* namespace Sscrollbar */
using namespace Sscrollbar;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sScrollBar
