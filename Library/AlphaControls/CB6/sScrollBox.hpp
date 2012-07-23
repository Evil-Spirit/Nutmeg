// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sScrollBox.pas' rev: 6.00

#ifndef sScrollBoxHPP
#define sScrollBoxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <acSBUtils.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <sLabel.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sscrollbox
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TsPaintEvent)(Graphics::TBitmap* ControlBmp);

class DELPHICLASS TsScrollBox;
class PASCALIMPLEMENTATION TsScrollBox : public Forms::TScrollingWinControl 
{
	typedef Forms::TScrollingWinControl inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	TsPaintEvent FOnPaint;
	Classes::TNotifyEvent FOnBeforeScroll;
	Classes::TNotifyEvent FOnAfterScroll;
	Controls::TControlCanvas* FCanvas;
	Classes::TNotifyEvent FOnMouseLeave;
	Classes::TNotifyEvent FOnMouseEnter;
	bool FAutoMouseWheel;
	Graphics::TCanvas* __fastcall GetCanvas(void);
	void __fastcall SetBorderStyle(const Forms::TBorderStyle Value);
	
protected:
	int acTrackPos;
	Forms::TFormBorderStyle FBorderStyle;
	bool FAutoFrameSize;
	HIDESBASE MESSAGE void __fastcall WMEraseBkGnd(Messages::TWMPaint &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TWMPaint &Message);
	MESSAGE void __fastcall WMPrint(Messages::TWMPaint &Message);
	virtual void __fastcall SetParent(Controls::TWinControl* AParent);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMCtl3DChanged(Messages::TMessage &Message);
	
public:
	Acsbutils::TacScrollWnd* ListSW;
	__fastcall virtual TsScrollBox(Classes::TComponent* AOwner);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	__fastcall virtual ~TsScrollBox(void);
	DYNAMIC bool __fastcall DoMouseWheel(Classes::TShiftState Shift, int WheelDelta, const Types::TPoint &MousePos);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	HIDESBASE void __fastcall ScrollBy(int DeltaX, int DeltaY);
	virtual void __fastcall PrepareCache(void);
	virtual void __fastcall Paint(HDC aDC = (HDC)(0x0), bool SendUpdated = true);
	virtual void __fastcall PaintWindow(HDC DC);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property TsPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Classes::TNotifyEvent OnAfterScroll = {read=FOnAfterScroll, write=FOnAfterScroll};
	__property Classes::TNotifyEvent OnBeforeScroll = {read=FOnBeforeScroll, write=FOnBeforeScroll};
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property bool AutoMouseWheel = {read=FAutoMouseWheel, write=FAutoMouseWheel, default=0};
	__property AutoScroll  = {default=1};
	__property BiDiMode ;
	__property Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=1};
	__property Graphics::TCanvas* Canvas = {read=GetCanvas};
	__property Constraints ;
	__property DockSite  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Color  = {default=-2147483643};
	__property Ctl3D ;
	__property Font ;
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=1};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property Visible  = {default=1};
	__property OnCanResize ;
	__property OnClick ;
	__property OnConstrainedResize ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDockDrop ;
	__property OnDockOver ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnGetSiteInfo ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnMouseWheel ;
	__property OnMouseWheelDown ;
	__property OnMouseWheelUp ;
	__property OnResize ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property OnUnDock ;
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsScrollBox(HWND ParentWindow) : Forms::TScrollingWinControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall SkinScrollInView(Controls::TControl* AControl, TsScrollBox* ScrollBox);

}	/* namespace Sscrollbox */
using namespace Sscrollbox;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sScrollBox
