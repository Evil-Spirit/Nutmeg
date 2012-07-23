// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sBitBtn.pas' rev: 6.00

#ifndef sBitBtnHPP
#define sBitBtnHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sFade.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
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

namespace Sbitbtn
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsBitBtn;
class PASCALIMPLEMENTATION TsBitBtn : public Buttons::TBitBtn 
{
	typedef Buttons::TBitBtn inherited;
	
private:
	int FOldSpacing;
	Scommondata::TsCtrlSkinData* FCommonData;
	bool FMouseClicked;
	bool FDown;
	bool RegionChanged;
	int FFocusMargin;
	Sconst::TsDisabledKind FDisabledKind;
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseLeave;
	Sfade::TsFadeTimer* FadeTimer;
	Sconst::TsDisabledGlyphKind FDisabledGlyphKind;
	bool FGrayed;
	int FBlend;
	int FOffset;
	int FImageIndex;
	Imglist::TCustomImageList* FImages;
	bool FShowCaption;
	bool FShowFocus;
	Classes::TAlignment FAlignment;
	bool FDrawOverBorder;
	Sconst::TBmpPaintEvent FOnPaint;
	Classes::TAlignment FTextAlignment;
	Sconst::TacAnimatEvents FAnimatEvents;
	#pragma pack(push, 1)
	Types::TRect LastRect;
	#pragma pack(pop)
	
	bool FReflected;
	Imglist::TChangeLink* FImageChangeLink;
	bool FWordWrap;
	void __fastcall SetWordWrap(const bool Value);
	void __fastcall SetDown(const bool Value);
	void __fastcall SetFocusMargin(const int Value);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	HIDESBASE MESSAGE void __fastcall WMKeyUp(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CNDrawItem(Messages::TWMDrawItem &Message);
	void __fastcall SetDisabledGlyphKind(const Sconst::TsDisabledGlyphKind Value);
	void __fastcall SetBlend(const int Value);
	void __fastcall SetGrayed(const bool Value);
	void __fastcall SetOffset(const int Value);
	void __fastcall SetImageIndex(const int Value);
	void __fastcall SetImages(const Imglist::TCustomImageList* Value);
	void __fastcall SetShowCaption(const bool Value);
	void __fastcall SetShowFocus(const bool Value);
	void __fastcall SetAlignment(const Classes::TAlignment Value);
	bool __fastcall GetDown(void);
	void __fastcall SetDrawOverBorder(const bool Value);
	void __fastcall SetReflected(const bool Value);
	void __fastcall SetTextAlignment(const Classes::TAlignment Value);
	void __fastcall ImageListChange(System::TObject* Sender);
	
protected:
	bool IsFocused;
	HRGN FRegion;
	#pragma pack(push, 1)
	Types::TPoint GlyphPos;
	#pragma pack(pop)
	
	Buttons::TButtonLayout OldLayout;
	#pragma pack(push, 1)
	Types::TRect CaptionRect;
	#pragma pack(pop)
	
	void __fastcall StdDrawItem(const tagDRAWITEMSTRUCT &DrawItemStruct);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	DYNAMIC void __fastcall ActionChange(System::TObject* Sender, bool CheckDefaults);
	void __fastcall OurPaintHandler(HDC aDC);
	void __fastcall DoDrawText(Types::TRect &Rect, unsigned Flags);
	void __fastcall DrawCaption(Graphics::TCanvas* Canvas = (Graphics::TCanvas*)(0x0));
	tagSIZE __fastcall TextRectSize();
	int __fastcall GlyphWidth(void);
	int __fastcall GlyphHeight(void);
	int __fastcall GenMargin(void);
	void __fastcall PrepareCache(void);
	
public:
	__fastcall virtual TsBitBtn(Classes::TComponent* AOwner);
	virtual int __fastcall CurrentState(void);
	__fastcall virtual ~TsBitBtn(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	Types::TRect __fastcall ImgRect();
	virtual void __fastcall Invalidate(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall SetButtonStyle(bool ADefault);
	
__published:
	__property Sconst::TBmpPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property int Blend = {read=FBlend, write=SetBlend, default=0};
	__property Scommondata::TsCtrlSkinData* SkinData = {read=FCommonData, write=FCommonData};
	__property Sconst::TsDisabledGlyphKind DisabledGlyphKind = {read=FDisabledGlyphKind, write=SetDisabledGlyphKind, default=1};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property bool Down = {read=GetDown, write=SetDown, default=0};
	__property int FocusMargin = {read=FFocusMargin, write=SetFocusMargin, default=1};
	__property bool Grayed = {read=FGrayed, write=SetGrayed, default=0};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, default=-1};
	__property Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property bool Reflected = {read=FReflected, write=SetReflected, default=0};
	__property bool ShowCaption = {read=FShowCaption, write=SetShowCaption, default=1};
	__property bool ShowFocus = {read=FShowFocus, write=SetShowFocus, default=1};
	__property bool DrawOverBorder = {read=FDrawOverBorder, write=SetDrawOverBorder, default=1};
	__property int TextOffset = {read=FOffset, write=SetOffset, default=0};
	__property Classes::TAlignment TextAlignment = {read=FTextAlignment, write=SetTextAlignment, default=2};
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, default=1};
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsBitBtn(HWND ParentWindow) : Buttons::TBitBtn(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sbitbtn */
using namespace Sbitbtn;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sBitBtn
