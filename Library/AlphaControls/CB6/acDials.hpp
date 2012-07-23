// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acDials.pas' rev: 6.00

#ifndef acDialsHPP
#define acDialsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <StdCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <acSBUtils.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acdials
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TacBorderStyle { acbsDialog, acbsSingle, acbsNone, acbsSizeable, acbsToolWindow, acbsSizeToolWin };
#pragma option pop

class DELPHICLASS TacSystemMenu;
class DELPHICLASS TacDialogWnd;
class DELPHICLASS TacProvider;
class PASCALIMPLEMENTATION TacProvider : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	Forms::TForm* FForm;
	
public:
	bool BiDiLeft;
	unsigned CtrlHandle;
	Sskinprovider::TsSkinProvider* sp;
	TacDialogWnd* ListSW;
	Classes::TList* acSkinnedCtrls;
	__fastcall virtual TacProvider(Classes::TComponent* AOwner);
	__fastcall virtual ~TacProvider(void);
	void __fastcall InitForm(Forms::TCustomForm* Form);
	bool __fastcall InitSkin(HWND aHandle);
	bool __fastcall InitHwndControls(HWND hWnd);
	bool __fastcall PrintHwndControls(HWND hWnd, HDC DC);
	bool __fastcall AddControl(HWND aHwnd);
	System::TObject* __fastcall FindCtrlInList(unsigned hwnd);
};


class PASCALIMPLEMENTATION TacDialogWnd : public Acsbutils::TacScrollWnd 
{
	typedef Acsbutils::TacScrollWnd inherited;
	
protected:
	DynamicArray<Types::TRect >  ArOR;
	int CurrentHT;
	bool FFormActive;
	bool FWMPaintForbidden;
	int FCaptionSkinIndex;
	Sskinprovider::TacMoveTimer* MoveTimer;
	bool Initialized;
	void __fastcall InitExBorders(const bool Active);
	
public:
	Forms::TForm* CoverForm;
	Sskinprovider::TacBorderForm* BorderForm;
	Sskinprovider::TsCaptionButton ButtonMin;
	Sskinprovider::TsCaptionButton ButtonMax;
	Sskinprovider::TsCaptionButton ButtonClose;
	Sskinprovider::TsCaptionButton ButtonHelp;
	#pragma pack(push, 1)
	Types::TRect LastClientRect;
	#pragma pack(pop)
	
	Graphics::TBitmap* TitleGlyph;
	HICON TitleIcon;
	Graphics::TFont* TitleFont;
	unsigned FormState;
	int dwStyle;
	int dwExStyle;
	bool RgnChanged;
	#pragma pack(push, 1)
	Types::TRect WndRect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	tagSIZE WndSize;
	#pragma pack(pop)
	
	TacBorderStyle BorderStyle;
	Graphics::TBitmap* TitleBG;
	Graphics::TBitmap* TempBmp;
	Sskinprovider::TacCtrlAdapter* Adapter;
	TacSystemMenu* SystemMenu;
	TacProvider* Provider;
	void __fastcall AdapterRemove(void);
	void __fastcall SendToAdapter(const Messages::TMessage &Message);
	void __fastcall MakeTitleBG(void);
	void __fastcall PaintAll(void);
	void __fastcall PaintBorderIcons(void);
	void __fastcall PaintCaption(const HDC DC);
	void __fastcall PaintForm(HDC &DC, bool SendUpdated = true);
	void __fastcall PrepareTitleGlyph(void);
	void __fastcall RepaintButton(int i);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	__fastcall virtual TacDialogWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacDialogWnd(void);
	void __fastcall InitParams(void);
	void __fastcall UpdateIconsIndexes(void);
	void __fastcall KillAnimations(void);
	void __fastcall Ac_WMPaint(Messages::TWMPaint &Msg);
	void __fastcall Ac_WMNCPaint(Messages::TMessage &Message);
	void __fastcall Ac_WMNCHitTest(Messages::TMessage &Message);
	void __fastcall Ac_WMNCLButtonDown(Messages::TWMNCHitMessage &Message);
	void __fastcall Ac_WMLButtonUp(Messages::TMessage &Message);
	void __fastcall Ac_WMActivate(Messages::TMessage &Message);
	void __fastcall Ac_WMNCActivate(Messages::TMessage &Message);
	void __fastcall Ac_DrawStaticItem(Messages::TWMDrawItem &Message);
	int __fastcall HTProcess(Messages::TWMNCHitTest &Message);
	void __fastcall SetHotHT(int i, bool Repaint = true);
	void __fastcall SetPressedHT(int i);
	void __fastcall DropSysMenu(int x, int y);
	bool __fastcall AboveBorder(const Messages::TWMNCHitTest &Message);
	int __fastcall BarWidth(int i);
	int __fastcall BorderHeight(void);
	int __fastcall ButtonHeight(int Index);
	int __fastcall CaptionHeight(bool CheckSkin = true);
	Types::TPoint __fastcall CursorToPoint(int x, int y);
	bool __fastcall FormActive(void);
	int __fastcall HeaderHeight(void);
	int __fastcall OffsetX(void);
	int __fastcall OffsetY(void);
	Types::TRect __fastcall IconRect();
	Types::TRect __fastcall ShadowSize();
	int __fastcall SysButtonWidth(const Sskinprovider::TsCaptionButton &Btn);
	int __fastcall TitleBtnsWidth(void);
	bool __fastcall VisibleMax(void);
	bool __fastcall VisibleMin(void);
	bool __fastcall VisibleHelp(void);
	bool __fastcall VisibleClose(void);
	bool __fastcall VisibleRestore(void);
	bool __fastcall EnabledMax(void);
	bool __fastcall EnabledMin(void);
	bool __fastcall EnabledClose(void);
	bool __fastcall EnabledRestore(void);
};


class PASCALIMPLEMENTATION TacSystemMenu : public Sskinprovider::TsCustomSysMenu 
{
	typedef Sskinprovider::TsCustomSysMenu inherited;
	
public:
	TacDialogWnd* FOwner;
	Menus::TMenuItem* ItemRestore;
	Menus::TMenuItem* ItemMove;
	Menus::TMenuItem* ItemSize;
	Menus::TMenuItem* ItemMinimize;
	Menus::TMenuItem* ItemMaximize;
	Menus::TMenuItem* ItemClose;
	__fastcall virtual TacSystemMenu(Classes::TComponent* AOwner);
	bool __fastcall EnabledMove(void);
	bool __fastcall EnabledSize(void);
	HIDESBASE void __fastcall UpdateItems(void);
	void __fastcall RestoreClick(System::TObject* Sender);
	void __fastcall MoveClick(System::TObject* Sender);
	void __fastcall SizeClick(System::TObject* Sender);
	void __fastcall MinClick(System::TObject* Sender);
	void __fastcall MaxClick(System::TObject* Sender);
	void __fastcall CloseClick(System::TObject* Sender);
	virtual bool __fastcall EnabledMax(void);
	virtual bool __fastcall EnabledMin(void);
	virtual bool __fastcall EnabledRestore(void);
	virtual bool __fastcall VisibleClose(void);
	virtual bool __fastcall VisibleMax(void);
	virtual bool __fastcall VisibleMin(void);
	bool __fastcall VisibleSize(void);
public:
	#pragma option push -w-inl
	/* TPopupMenu.Destroy */ inline __fastcall virtual ~TacSystemMenu(void) { }
	#pragma option pop
	
};


typedef DynamicArray<Acsbutils::TacMnuWnd* >  TacMnuArray;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE HHOOK HookCallback;
extern PACKAGE HHOOK WndCallBack;
extern PACKAGE HHOOK WndCallRet;
extern PACKAGE Classes::TList* acSupportedList;
extern PACKAGE Types::TRect fRect;
extern PACKAGE int DlgLeft;
extern PACKAGE int DlgTop;
extern PACKAGE DynamicArray<Acsbutils::TacMnuWnd* >  MnuArray;
extern PACKAGE void __fastcall BroadCastHwnd(const HWND hWnd, const Messages::TMessage &Message);
extern PACKAGE void __fastcall StartBlendOnMovingDlg(TacDialogWnd* dw);
extern PACKAGE void __fastcall FinishBlendOnMovingDlg(TacDialogWnd* dw);
extern PACKAGE int __fastcall VisibleDlgCount(void);
extern PACKAGE bool __fastcall ControlExists(HWND CtrlHandle, const AnsiString Name);
extern PACKAGE int __stdcall SkinHookCBT(int code, int wParam, int lParam);
extern PACKAGE bool __fastcall AddSupportedForm(unsigned hwnd, Windows::PCreateStructA cStruct = (void *)(0x0));
extern PACKAGE AnsiString __fastcall GetWndClassName(unsigned hwnd);
extern PACKAGE System::TObject* __fastcall FindFormInList(unsigned hwnd);
extern PACKAGE Forms::TCustomForm* __fastcall FindFormOnScreen(unsigned hwnd);
extern PACKAGE void __fastcall InitDialog(unsigned hwnd, TacDialogWnd* &ListSW);
extern PACKAGE void __fastcall DrawAppIcon(TacDialogWnd* ListSW);
extern PACKAGE WideString __fastcall GetWndText(unsigned hwnd);
extern PACKAGE void __fastcall FillArOR(TacDialogWnd* ListSW);
extern PACKAGE void __fastcall UpdateRgn(TacDialogWnd* ListSW, bool Repaint = true);
extern PACKAGE HRGN __fastcall GetRgnFromArOR(TacDialogWnd* ListSW, int X = 0x0, int Y = 0x0);
extern PACKAGE void __fastcall ClearMnuArray(void);
extern PACKAGE void __fastcall CleanArray(void);

}	/* namespace Acdials */
using namespace Acdials;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acDials
