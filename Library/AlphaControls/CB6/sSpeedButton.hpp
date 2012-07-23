// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sSpeedButton.pas' rev: 6.00

#ifndef sSpeedButtonHPP
#define sSpeedButtonHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sFade.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
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

namespace Sspeedbutton
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsSpeedButton;
class PASCALIMPLEMENTATION TsSpeedButton : public Buttons::TSpeedButton 
{
	typedef Buttons::TSpeedButton inherited;
	
private:
	int FOldNumGlyphs;
	int FOldSpacing;
	Imglist::TChangeLink* FImageChangeLink;
	bool FStoredDown;
	Scommondata::TsCtrlSkinData* FCommonData;
	Sconst::TsDisabledKind FDisabledKind;
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseLeave;
	Sfade::TsAnimTimer* FadeTimer;
	Sconst::TsDisabledGlyphKind FDisabledGlyphKind;
	bool FGrayed;
	int FBlend;
	int FOffset;
	int FImageIndex;
	Imglist::TCustomImageList* FImages;
	bool FShowCaption;
	Classes::TAlignment FAlignment;
	int FTextLayout;
	Comctrls::TToolButtonStyle FButtonStyle;
	Menus::TPopupMenu* FDropdownMenu;
	bool FDrawOverBorder;
	Sconst::TBmpPaintEvent FOnPaint;
	Classes::TAlignment FTextAlignment;
	Sconst::TacAnimatEvents FAnimatEvents;
	void __fastcall ImageListChange(System::TObject* Sender);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	void __fastcall SetDisabledGlyphKind(const Sconst::TsDisabledGlyphKind Value);
	void __fastcall SetBlend(const int Value);
	void __fastcall SetGrayed(const bool Value);
	void __fastcall SetOffset(const int Value);
	void __fastcall SetImageIndex(const int Value);
	void __fastcall SetImages(const Imglist::TCustomImageList* Value);
	void __fastcall SetShowCaption(const bool Value);
	void __fastcall SetAlignment(const Classes::TAlignment Value);
	void __fastcall SetButtonStyle(const Comctrls::TToolButtonStyle Value);
	void __fastcall SetDropdownMenu(const Menus::TPopupMenu* Value);
	void __fastcall SetDrawOverBorder(const bool Value);
	void __fastcall SetTextAlignment(const Classes::TAlignment Value);
	bool FReflected;
	void __fastcall SetReflected(const bool Value);
	
protected:
	bool DroppedDown;
	Classes::TNotifyEvent OldOnChange;
	Buttons::TButtonLayout OldLayout;
	AnsiString OldCaption;
	void __fastcall SetFakeCaption(void);
	int __fastcall ArrowWidth(void);
	virtual void __fastcall DoDrawText(Types::TRect &Rect, int Flags);
	virtual void __fastcall DrawCaption(void);
	virtual tagSIZE __fastcall TextRectSize();
	virtual void __fastcall DrawGlyph(void);
	virtual int __fastcall GlyphWidth(void);
	virtual int __fastcall GlyphHeight(void);
	int __fastcall GenMargin(void);
	virtual void __fastcall PrepareCache(void);
	DYNAMIC void __fastcall ActionChange(System::TObject* Sender, bool CheckDefaults);
	void __fastcall Ac_CMMouseEnter(Messages::TMessage &Message);
	void __fastcall Ac_CMMouseLeave(Messages::TMessage &Message);
	virtual void __fastcall StdPaint(bool PaintButton = true);
	virtual void __fastcall Paint(void);
	HIDESBASE void __fastcall GlyphChanged(System::TObject* Sender);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	virtual int __fastcall CurrentState(void);
	virtual Types::TRect __fastcall CaptionRect();
	__fastcall virtual TsSpeedButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TsSpeedButton(void);
	void __fastcall GraphRepaint(void);
	virtual void __fastcall AfterConstruction(void);
	virtual Types::TRect __fastcall ImgRect();
	virtual void __fastcall Invalidate(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	__property Canvas ;
	
__published:
	__property Align  = {default=0};
	__property Sconst::TBmpPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property int Blend = {read=FBlend, write=SetBlend, default=0};
	__property Comctrls::TToolButtonStyle ButtonStyle = {read=FButtonStyle, write=SetButtonStyle, default=0};
	__property Scommondata::TsCtrlSkinData* SkinData = {read=FCommonData, write=FCommonData};
	__property Sconst::TsDisabledGlyphKind DisabledGlyphKind = {read=FDisabledGlyphKind, write=SetDisabledGlyphKind, default=1};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property Menus::TPopupMenu* DropdownMenu = {read=FDropdownMenu, write=SetDropdownMenu};
	__property bool Grayed = {read=FGrayed, write=SetGrayed, default=0};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, default=-1};
	__property Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property bool Reflected = {read=FReflected, write=SetReflected, default=0};
	__property bool ShowCaption = {read=FShowCaption, write=SetShowCaption, default=1};
	__property bool DrawOverBorder = {read=FDrawOverBorder, write=SetDrawOverBorder, default=1};
	__property int TextOffset = {read=FOffset, write=SetOffset, default=0};
	__property Classes::TAlignment TextAlignment = {read=FTextAlignment, write=SetTextAlignment, default=2};
};


class DELPHICLASS TsTimerSpeedButton;
class PASCALIMPLEMENTATION TsTimerSpeedButton : public TsSpeedButton 
{
	typedef TsSpeedButton inherited;
	
private:
	bool FAllowTimer;
	
public:
	__fastcall virtual TsTimerSpeedButton(Classes::TComponent* AOwner);
	
__published:
	__property bool AllowTimer = {read=FAllowTimer, write=FAllowTimer, default=1};
public:
	#pragma option push -w-inl
	/* TsSpeedButton.Destroy */ inline __fastcall virtual ~TsTimerSpeedButton(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall GlowingAllowed(TsSpeedButton* Btn);

}	/* namespace Sspeedbutton */
using namespace Sspeedbutton;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sSpeedButton
