// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sPageControl.pas' rev: 6.00

#ifndef sPageControlHPP
#define sPageControlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acSBUtils.hpp>	// Pascal unit
#include <sSpeedButton.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sUpDown.hpp>	// Pascal unit
#include <sFade.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
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

namespace Spagecontrol
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TacCloseAction { acaHide, acaFree };
#pragma option pop

typedef void __fastcall (__closure *TacCloseBtnClick)(Classes::TComponent* Sender, int TabIndex, bool &CanClose, TacCloseAction &Action);

class DELPHICLASS TsTabSkinData;
class PASCALIMPLEMENTATION TsTabSkinData : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	bool FCustomColor;
	bool FCustomFont;
	AnsiString FSkinSection;
	void __fastcall SetCustomColor(const bool Value);
	void __fastcall SetCustomFont(const bool Value);
	void __fastcall SetSkinSection(const AnsiString Value);
	
__published:
	__property bool CustomColor = {read=FCustomColor, write=SetCustomColor, nodefault};
	__property bool CustomFont = {read=FCustomFont, write=SetCustomFont, nodefault};
	__property AnsiString SkinSection = {read=FSkinSection, write=SetSkinSection};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TsTabSkinData(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TsTabSkinData(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TsTabBtn;
class DELPHICLASS TsTabSheet;
class PASCALIMPLEMENTATION TsTabSheet : public Comctrls::TTabSheet 
{
	typedef Comctrls::TTabSheet inherited;
	
private:
	AnsiString FTabSkin;
	AnsiString FButtonSkin;
	bool FUseCloseBtn;
	TsTabSkinData* FCommonData;
	void __fastcall SetUseCloseBtn(const bool Value);
	void __fastcall SetButtonSkin(const AnsiString Value);
	void __fastcall SetTabSkin(const AnsiString Value);
	
public:
	TsTabBtn* Btn;
	__fastcall virtual TsTabSheet(Classes::TComponent* AOwner);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	__fastcall virtual ~TsTabSheet(void);
	HIDESBASE MESSAGE void __fastcall WMEraseBkGnd(Messages::TWMPaint &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TWMPaint &Message);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property TsTabSkinData* SkinData = {read=FCommonData, write=FCommonData};
	__property AnsiString ButtonSkin = {read=FButtonSkin, write=SetButtonSkin};
	__property AnsiString TabSkin = {read=FTabSkin, write=SetTabSkin};
	__property bool UseCloseBtn = {read=FUseCloseBtn, write=SetUseCloseBtn, default=1};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsTabSheet(HWND ParentWindow) : Comctrls::TTabSheet(ParentWindow) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsTabBtn : public Sspeedbutton::TsSpeedButton 
{
	typedef Sspeedbutton::TsSpeedButton inherited;
	
public:
	TsTabSheet* Page;
	__fastcall virtual TsTabBtn(Classes::TComponent* AOwner);
	virtual void __fastcall Paint(void);
	void __fastcall UpdateGlyph(void);
public:
	#pragma option push -w-inl
	/* TsSpeedButton.Destroy */ inline __fastcall virtual ~TsTabBtn(void) { }
	#pragma option pop
	
};


class DELPHICLASS TsPageControl;
class PASCALIMPLEMENTATION TsPageControl : public Comctrls::TPageControl 
{
	typedef Comctrls::TPageControl inherited;
	
private:
	int StoredVisiblePageCount;
	AnsiString ChangedSkinSection;
	Scommondata::TsCommonData* FCommonData;
	Sconst::TacAnimatEvents FAnimatEvents;
	bool FShowCloseBtns;
	TacCloseBtnClick FOnCloseBtnClick;
	AnsiString FCloseBtnSkin;
	TsTabSheet* FNewDockSheet;
	void __fastcall CheckUpDown(void);
	HIDESBASE MESSAGE void __fastcall CMHintShow(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CNNotify(Messages::TWMNotify &Message);
	void __fastcall AcPaint(Messages::TWMPaint &Message);
	void __fastcall DrawSkinTabs(const Sconst::TCacheInfo &CI);
	void __fastcall DrawSkinTab(int PageIndex, int State, Graphics::TBitmap* Bmp, const Types::TPoint &OffsetPoint)/* overload */;
	void __fastcall DrawSkinTab(int PageIndex, int State, HDC DC)/* overload */;
	Types::TRect __fastcall PageRect();
	Types::TRect __fastcall TabsRect();
	Types::TRect __fastcall SkinTabRect(int Index, bool Active);
	int __fastcall TabRow(int TabIndex);
	TsTabSheet* __fastcall GetActivePage(void);
	HIDESBASE void __fastcall SetActivePage(const TsTabSheet* Value);
	void __fastcall UpdateBtnData(void);
	void __fastcall PaintButtonEx(int PageIndex, int BtnState, int TabState);
	void __fastcall PaintButtons(HDC DC);
	Types::TRect __fastcall BtnRect(int TabIndex);
	void __fastcall SetShowCloseBtns(const bool Value);
	void __fastcall SetCloseBtnSkin(const AnsiString Value);
	AnsiString __fastcall SpinSection();
	HIDESBASE MESSAGE void __fastcall CMDockClient(Controls::TCMDockClient &Message);
	bool FShowUpDown;
	void __fastcall SetShowUpDown(const bool Value);
	
protected:
	Acsbutils::TacSpinWnd* SpinWnd;
	int CurItem;
	int BtnIndex;
	int BtnWidth;
	int BtnHeight;
	DYNAMIC void __fastcall DoAddDockClient(Controls::TControl* Client, const Types::TRect &ARect);
	virtual void __fastcall PaintButton(HDC DC, const Types::TRect &TabRect, int State, const Sconst::TCacheInfo &BG);
	int __fastcall GetTabUnderMouse(const Types::TPoint &p);
	void __fastcall RepaintTab(int i, int State, HDC TabDC = (HDC)(0x0));
	void __fastcall RepaintTabs(HDC DC, int ActiveTabNdx);
	int __fastcall VisibleTabsCount(void);
	
public:
	__property bool ShowUpDown = {read=FShowUpDown, write=SetShowUpDown, default=1};
	__fastcall virtual TsPageControl(Classes::TComponent* AOwner);
	__fastcall virtual ~TsPageControl(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall UpdateActivePage(void);
	void __fastcall CloseClick(System::TObject* Sender);
	void __fastcall ArrangeButtons(void);
	
__published:
	__property TsTabSheet* ActivePage = {read=GetActivePage, write=SetActivePage};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Style  = {default=0};
	__property AnsiString CloseBtnSkin = {read=FCloseBtnSkin, write=SetCloseBtnSkin};
	__property bool ShowCloseBtns = {read=FShowCloseBtns, write=SetShowCloseBtns, default=0};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property TacCloseBtnClick OnCloseBtnClick = {read=FOnCloseBtnClick, write=FOnCloseBtnClick};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsPageControl(HWND ParentWindow) : Comctrls::TPageControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall DeletePage(TsTabSheet* Page);

}	/* namespace Spagecontrol */
using namespace Spagecontrol;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sPageControl
