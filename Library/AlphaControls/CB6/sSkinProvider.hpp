// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sSkinProvider.pas' rev: 6.00

#ifndef sSkinProviderHPP
#define sSkinProviderHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acSBUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <acThdTimer.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <acGlow.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <acPNG.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <sSkinMenus.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sskinprovider
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TacGraphItem;
class PASCALIMPLEMENTATION TacGraphItem : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
public:
	Controls::TControl* Ctrl;
	Scommondata::TsCommonData* SkinData;
	System::TObject* Adapter;
	Acsbutils::TacSpeedButtonHandler* Handler;
	__fastcall virtual TacGraphItem(void);
	__fastcall virtual ~TacGraphItem(void);
	virtual void __fastcall DoHook(Controls::TControl* Control);
};


class DELPHICLASS TacAdapterItem;
class PASCALIMPLEMENTATION TacAdapterItem : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
public:
	Controls::TWinControl* WinCtrl;
	Scommondata::TsCommonData* SkinData;
	int OldFontColor;
	System::TObject* Adapter;
	Acsbutils::TacMainWnd* ScrollWnd;
	__fastcall virtual TacAdapterItem(void);
	__fastcall virtual ~TacAdapterItem(void);
	virtual void __fastcall DoHook(Controls::TWinControl* Control);
};


typedef void __fastcall (__closure *TAddItemEvent)(Classes::TComponent* Item, bool &CanBeAdded, AnsiString &SkinSection);

typedef void __fastcall (__closure *TacNCHitTest)(Messages::TWMNCHitTest &Msg);

#pragma option push -b-
enum TacAnimEvent { aeShowing, aeHiding, aeSkinChanging };
#pragma option pop

typedef void __fastcall (__closure *TacAfterAnimation)(TacAnimEvent AnimType);

#pragma option push -b-
enum TsGripMode { gmNone, gmRightBottom };
#pragma option pop

#pragma option push -b-
enum TsResizeMode { rmStandard, rmBorder };
#pragma option pop

class DELPHICLASS TacSBAnimation;
class DELPHICLASS TacBorderForm;
class DELPHICLASS TsSkinProvider;
class DELPHICLASS TsTitleIcon;
class PASCALIMPLEMENTATION TsTitleIcon : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Graphics::TBitmap* FGlyph;
	int FHeight;
	int FWidth;
	void __fastcall SetGlyph(const Graphics::TBitmap* Value);
	void __fastcall SetHeight(const int Value);
	void __fastcall SetWidth(const int Value);
	
public:
	__fastcall TsTitleIcon(void);
	__fastcall virtual ~TsTitleIcon(void);
	
__published:
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property int Height = {read=FHeight, write=SetHeight, default=0};
	__property int Width = {read=FWidth, write=SetWidth, default=0};
};


class DELPHICLASS TsTitleButtons;
class DELPHICLASS TsTitleButton;
class PASCALIMPLEMENTATION TsTitleButtons : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
public:
	TsTitleButton* operator[](int Index) { return Items[Index]; }
	
private:
	TsSkinProvider* FOwner;
	HIDESBASE TsTitleButton* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TsTitleButton* Value);
	
protected:
	DYNAMIC Classes::TPersistent* __fastcall GetOwner(void);
	virtual void __fastcall Update(Classes::TCollectionItem* Item);
	
public:
	__fastcall TsTitleButtons(TsSkinProvider* AOwner);
	__fastcall virtual ~TsTitleButtons(void);
	__property TsTitleButton* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
};


class DELPHICLASS TacAddedTitle;
class PASCALIMPLEMENTATION TacAddedTitle : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	bool FShowMainCaption;
	void __fastcall SetShowMainCaption(const bool Value);
	
protected:
	AnsiString FText;
	Graphics::TFont* FFont;
	void __fastcall SetText(const AnsiString Value);
	void __fastcall SetFont(const Graphics::TFont* Value);
	void __fastcall Repaint(void);
	
public:
	TsSkinProvider* FOwner;
	__fastcall virtual TacAddedTitle(void);
	__fastcall virtual ~TacAddedTitle(void);
	
__published:
	__property Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property AnsiString Text = {read=FText, write=SetText};
	__property bool ShowMainCaption = {read=FShowMainCaption, write=SetShowMainCaption, default=1};
};


#pragma pack(push, 4)
struct TsCaptionButton
{
	int State;
	int ImageIndex;
	Types::TRect Rect;
	bool HaveAlignment;
	int GlowID;
	TacSBAnimation* Timer;
	unsigned HitCode;
} ;
#pragma pack(pop)

class DELPHICLASS TacCtrlAdapter;
typedef DynamicArray<TacAdapterItem* >  TacAdapterItems;

typedef DynamicArray<TacGraphItem* >  TacGraphItems;

class PASCALIMPLEMENTATION TacCtrlAdapter : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
public:
	System::TObject* CtrlClass;
	AnsiString DefaultSection;
	DynamicArray<TacAdapterItem* >  Items;
	DynamicArray<TacGraphItem* >  GraphItems;
	TsSkinProvider* Provider;
	virtual bool __fastcall IsControlSupported(Classes::TComponent* Control);
	int __fastcall Count(void);
	__fastcall TacCtrlAdapter(TsSkinProvider* AProvider);
	__fastcall virtual ~TacCtrlAdapter(void);
	virtual TacAdapterItem* __fastcall GetItem(int Index);
	virtual Scommondata::TsCommonData* __fastcall GetCommonData(int Index);
	int __fastcall IndexOf(Controls::TWinControl* Ctrl);
	virtual void __fastcall AfterConstruction(void);
	void __fastcall AddAllItems(Controls::TWinControl* OwnerCtrl = (Controls::TWinControl*)(0x0));
	virtual void __fastcall AddNewItem(const Buttons::TSpeedButton* Ctrl)/* overload */;
	virtual void __fastcall AddNewItem(const Controls::TWinControl* Ctrl)/* overload */;
	virtual void __fastcall AddNewItem(const Controls::TWinControl* Ctrl, const AnsiString SkinSection)/* overload */;
	virtual void __fastcall RemoveItem(int Index);
	void __fastcall RemoveAllItems(void);
	void __fastcall CleanItems(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
};


class DELPHICLASS TsSystemMenu;
class DELPHICLASS TsCustomSysMenu;
class PASCALIMPLEMENTATION TsCustomSysMenu : public Menus::TPopupMenu 
{
	typedef Menus::TPopupMenu inherited;
	
__published:
	virtual bool __fastcall VisibleClose(void) = 0 ;
	virtual bool __fastcall VisibleMax(void) = 0 ;
	virtual bool __fastcall VisibleMin(void) = 0 ;
	virtual bool __fastcall EnabledMax(void) = 0 ;
	virtual bool __fastcall EnabledMin(void) = 0 ;
	virtual bool __fastcall EnabledRestore(void) = 0 ;
public:
	#pragma option push -w-inl
	/* TPopupMenu.Create */ inline __fastcall virtual TsCustomSysMenu(Classes::TComponent* AOwner) : Menus::TPopupMenu(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPopupMenu.Destroy */ inline __fastcall virtual ~TsCustomSysMenu(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsSystemMenu : public TsCustomSysMenu 
{
	typedef TsCustomSysMenu inherited;
	
public:
	int ExtItemsCount;
	TsSkinProvider* FOwner;
	Forms::TCustomForm* FForm;
	Menus::TMenuItem* ItemRestore;
	Menus::TMenuItem* ItemMove;
	Menus::TMenuItem* ItemSize;
	Menus::TMenuItem* ItemMinimize;
	Menus::TMenuItem* ItemMaximize;
	Menus::TMenuItem* ItemClose;
	__fastcall virtual TsSystemMenu(Classes::TComponent* AOwner);
	void __fastcall Generate(void);
	HIDESBASE void __fastcall UpdateItems(bool Full = false);
	void __fastcall UpdateGlyphs(void);
	void __fastcall MakeSkinItems(void);
	bool __fastcall VisibleRestore(void);
	bool __fastcall VisibleSize(void);
	virtual bool __fastcall VisibleMin(void);
	virtual bool __fastcall VisibleMax(void);
	virtual bool __fastcall VisibleClose(void);
	virtual bool __fastcall EnabledRestore(void);
	bool __fastcall EnabledMove(void);
	bool __fastcall EnabledSize(void);
	virtual bool __fastcall EnabledMin(void);
	virtual bool __fastcall EnabledMax(void);
	void __fastcall RestoreClick(System::TObject* Sender);
	void __fastcall MoveClick(System::TObject* Sender);
	void __fastcall SizeClick(System::TObject* Sender);
	void __fastcall MinClick(System::TObject* Sender);
	void __fastcall MaxClick(System::TObject* Sender);
	void __fastcall CloseClick(System::TObject* Sender);
	void __fastcall SkinSelect(System::TObject* Sender);
	void __fastcall ExtClick(System::TObject* Sender);
public:
	#pragma option push -w-inl
	/* TPopupMenu.Destroy */ inline __fastcall virtual ~TsSystemMenu(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsSkinProvider : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	DynamicArray<Types::TRect >  ArOR;
	bool RgnChanged;
	int CurrentHT;
	Graphics::TBitmap* TempBmp;
	bool FMakeSkinMenu;
	bool FShowAppIcon;
	bool ControlsChanged;
	bool HaveSysMenu;
	Classes::TAlignment FCaptionAlignment;
	TsTitleIcon* FTitleIcon;
	TsTitleButtons* FTitleButtons;
	TsGripMode FGripMode;
	Scommondata::TsCommonData* FCommonData;
	TsResizeMode FResizeMode;
	bool FirstInitialized;
	bool FScreenSnap;
	int FSnapBuffer;
	bool FUseGlobalColor;
	AnsiString FTitleSkin;
	AnsiString FMenuLineSkin;
	int UserBtnIndex;
	TAddItemEvent FOnSkinItem;
	bool FDrawNonClientArea;
	bool FAllowExtBorders;
	TacNCHitTest FOnExtHitTest;
	TacAfterAnimation FOnAfterAnimation;
	TacAddedTitle* FAddedTitle;
	bool FAllowBlendOnMoving;
	void __fastcall OnChildMnuClick(System::TObject* Sender);
	void __fastcall SetCaptionAlignment(const Classes::TAlignment Value);
	void __fastcall SetShowAppIcon(const bool Value);
	void __fastcall SetTitleButtons(const TsTitleButtons* Value);
	void __fastcall SetUseGlobalColor(const bool Value);
	int __fastcall GetLinesCount(void);
	void __fastcall SetTitleSkin(const AnsiString Value);
	void __fastcall SetMenuLineSkin(const AnsiString Value);
	void __fastcall SetDrawNonClientArea(const bool Value);
	void __fastcall SetAllowExtBorders(const bool Value);
	
protected:
	int LockCount;
	bool ClearButtons;
	bool MenusInitialized;
	bool RegionChanged;
	bool CaptChanged;
	bool CaptRgnChanged;
	Graphics::TBitmap* FGlow1;
	Graphics::TBitmap* FGlow2;
	Forms::TForm* CoverForm;
	Graphics::TBitmap* CoverBmp;
	#pragma pack(push, 1)
	Types::TRect NormalBounds;
	#pragma pack(pop)
	
	TsCaptionButton ButtonMin;
	TsCaptionButton ButtonMax;
	TsCaptionButton ButtonClose;
	TsCaptionButton ButtonHelp;
	TsCaptionButton MDIMin;
	TsCaptionButton MDIMax;
	TsCaptionButton MDIClose;
	#pragma pack(push, 1)
	Types::TRect LastClientRect;
	#pragma pack(pop)
	
	bool FSysExHeight;
	int FTitleSkinIndex;
	int FCaptionSkinIndex;
	Acthdtimer::TacThreadedTimer* FormTimer;
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	void __fastcall AdapterRemove(void);
	virtual void __fastcall AdapterCreate(void);
	void __fastcall SendToAdapter(const Messages::TMessage &Message);
	void __fastcall PaintAll(void);
	void __fastcall PaintForm(HDC DC, bool SendUpdated = true);
	void __fastcall PaintCaption(HDC DC);
	void __fastcall PaintBorderIcons(void);
	void __fastcall RepaintButton(int i);
	void __fastcall RepaintMenuItem(Menus::TMenuItem* mi, const Types::TRect &R, Windows::TOwnerDrawState State);
	void __fastcall MakeTitleBG(void);
	void __fastcall SaveBGForBtns(bool Full = false);
	void __fastcall RestoreBtnsBG(void);
	void __fastcall OurPaintHandler(const Messages::TWMPaint &Msg);
	void __fastcall AC_WMEraseBkGnd(HDC aDC);
	void __fastcall AC_WMNCPaint(void);
	void __fastcall AC_WMNCCalcSize(Messages::TWMNCCalcSize &Message);
	void __fastcall AC_WMGetMinMaxInfo(Messages::TWMGetMinMaxInfo &Message);
	void __fastcall AC_CMMouseWheel(Controls::TCMMouseWheel &Message);
	void __fastcall AC_WMInitMenuPopup(Messages::TWMInitMenuPopup &Message);
	int __fastcall HTProcess(Messages::TWMNCHitTest &Message);
	Types::TPoint __fastcall CursorToPoint(int x, int y);
	bool __fastcall MDIButtonsNeeded(void);
	Types::TPoint __fastcall RBGripPoint(int ImgIndex);
	Types::TRect __fastcall IconRect();
	Types::TPoint __fastcall FormLeftTop();
	int __fastcall SysButtonsCount(void);
	int __fastcall SmallButtonWidth(void);
	int __fastcall ButtonHeight(void);
	int __fastcall SmallButtonHeight(void);
	int __fastcall SysButtonWidth(const TsCaptionButton &Btn);
	int __fastcall TitleBtnsWidth(void);
	int __fastcall UserButtonWidth(TsTitleButton* Btn);
	int __fastcall BarWidth(int i);
	void __fastcall KillAnimations(void);
	void __fastcall UpdateIconsIndexes(void);
	void __fastcall StartMove(int X, int Y);
	void __fastcall StopMove(int X, int Y);
	void __fastcall DrawFormBorder(int X, int Y);
	void __fastcall SetHotHT(int i, bool Repaint = true);
	void __fastcall SetPressedHT(int i);
	bool __fastcall FormChanged(void);
	bool __fastcall IconVisible(void);
	AnsiString __fastcall TitleSkinSection();
	int __fastcall TitleSkinIndex(void);
	void __fastcall CheckSysMenu(const bool Skinned);
	void __fastcall InitExBorders(const bool Active);
	
public:
	bool RTInit;
	bool RTEmpty;
	bool InAero;
	bool InMenu;
	bool FInAnimation;
	Forms::TShowAction ShowAction;
	bool SkipAnimation;
	bool fAnimating;
	Acsbutils::TacScrollWnd* ListSW;
	TacCtrlAdapter* Adapter;
	unsigned FormState;
	bool RgnChanging;
	bool MenuChanged;
	Classes::TWndMethod OldWndProc;
	System::TObject* MDIForm;
	bool FormActive;
	Graphics::TBitmap* MenuLineBmp;
	Forms::TForm* Form;
	int FLinesCount;
	TsSystemMenu* SystemMenu;
	Forms::TForm* CaptForm;
	Classes::TWndMethod OldCaptFormProc;
	TacBorderForm* BorderForm;
	__fastcall virtual TsSkinProvider(Classes::TComponent* AOwner);
	__fastcall virtual ~TsSkinProvider(void);
	__fastcall TsSkinProvider(Classes::TComponent* AOwner, bool InitRT);
	void __fastcall DropSysMenu(int x, int y);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	void __fastcall LoadInit(void);
	void __fastcall PrepareForm(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	int __fastcall OffsetX(void);
	int __fastcall OffsetY(void);
	Types::TRect __fastcall ShadowSize();
	void __fastcall NewWndProc(Messages::TMessage &Message);
	void __fastcall DsgnWndProc(Messages::TMessage &Message);
	void __fastcall HookMDI(bool Active = true);
	int __fastcall HeaderHeight(void);
	int __fastcall BorderHeight(bool CheckSkin = true);
	int __fastcall BorderWidth(bool CheckSkin = true);
	int __fastcall CaptionHeight(bool CheckSkin = true);
	int __fastcall CaptionWidth(void);
	int __fastcall MenuHeight(void);
	bool __fastcall MenuPresent(void);
	Graphics::TColor __fastcall FormColor(void);
	void __fastcall MdiIcoFormPaint(System::TObject* Sender);
	void __fastcall CaptFormPaint(System::TObject* Sender);
	void __fastcall NewCaptFormProc(Messages::TMessage &Message);
	bool __fastcall UpdateMenu(void);
	void __fastcall InitMenuItems(bool A);
	void __fastcall RepaintMenu(void);
	__property int LinesCount = {read=GetLinesCount, nodefault};
	
__published:
	__property TacAddedTitle* AddedTitle = {read=FAddedTitle, write=FAddedTitle};
	__property bool AllowExtBorders = {read=FAllowExtBorders, write=SetAllowExtBorders, default=1};
	__property bool AllowBlendOnMoving = {read=FAllowBlendOnMoving, write=FAllowBlendOnMoving, default=1};
	__property Classes::TAlignment CaptionAlignment = {read=FCaptionAlignment, write=SetCaptionAlignment, default=0};
	__property bool DrawNonClientArea = {read=FDrawNonClientArea, write=SetDrawNonClientArea, default=1};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property TsGripMode GripMode = {read=FGripMode, write=FGripMode, default=0};
	__property bool MakeSkinMenu = {read=FMakeSkinMenu, write=FMakeSkinMenu, default=0};
	__property AnsiString MenuLineSkin = {read=FMenuLineSkin, write=SetMenuLineSkin};
	__property TsResizeMode ResizeMode = {read=FResizeMode, write=FResizeMode, default=0};
	__property bool ScreenSnap = {read=FScreenSnap, write=FScreenSnap, default=0};
	__property int SnapBuffer = {read=FSnapBuffer, write=FSnapBuffer, default=10};
	__property bool ShowAppIcon = {read=FShowAppIcon, write=SetShowAppIcon, default=1};
	__property TsTitleButtons* TitleButtons = {read=FTitleButtons, write=SetTitleButtons};
	__property TsTitleIcon* TitleIcon = {read=FTitleIcon, write=FTitleIcon};
	__property AnsiString TitleSkin = {read=FTitleSkin, write=SetTitleSkin};
	__property bool UseGlobalColor = {read=FUseGlobalColor, write=SetUseGlobalColor, default=1};
	__property TacAfterAnimation OnAfterAnimation = {read=FOnAfterAnimation, write=FOnAfterAnimation};
	__property TacNCHitTest OnExtHitTest = {read=FOnExtHitTest, write=FOnExtHitTest};
	__property TAddItemEvent OnSkinItem = {read=FOnSkinItem, write=FOnSkinItem};
};


class PASCALIMPLEMENTATION TacBorderForm : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
protected:
	System::TObject* FOwner;
	TsSkinProvider* sp;
	
public:
	bool acInMouseMsg;
	Forms::TForm* AForm;
	Classes::TWndMethod OldBorderProc;
	bool ExBorderShowing;
	Graphics::TBitmap* ShadowTemplate;
	Scommondata::TsCommonData* SkinData;
	__fastcall TacBorderForm(System::TObject* AOwner);
	void __fastcall CreateNewForm(void);
	__fastcall virtual ~TacBorderForm(void);
	void __fastcall KillAnimations(void);
	int __fastcall OffsetX(void);
	int __fastcall OffsetY(void);
	TsCaptionButton __fastcall ButtonMin();
	TsCaptionButton __fastcall ButtonMax();
	TsCaptionButton __fastcall ButtonClose();
	TsCaptionButton __fastcall ButtonHelp();
	HWND __fastcall OwnerHandle(void);
	Types::TRect __fastcall ShadowSize();
	int __fastcall CaptionHeight(bool CheckSkin = true);
	int __fastcall MenuHeight(void);
	Types::TRect __fastcall IconRect();
	void __fastcall SetHotHT(const int i, bool Repaint = true);
	void __fastcall PaintAll(void);
	HRGN __fastcall MakeRgn(int NewWidth = 0x0, int NewHeight = 0x0);
	unsigned __fastcall FormState(void);
	bool __fastcall MouseAboveTheShadow(const Messages::TWMMouse &Message);
	void __fastcall BorderProc(Messages::TMessage &Message);
	void __fastcall UpdateExBordersPos(bool Redraw = true, Byte Blend = (Byte)(0xff));
	int __fastcall Ex_WMNCHitTest(Messages::TWMNCHitTest &Message);
	bool __fastcall Ex_WMSetCursor(Messages::TWMSetCursor &Message);
};


typedef TsCaptionButton *PsCaptionButton;

class PASCALIMPLEMENTATION TacSBAnimation : public Extctrls::TTimer 
{
	typedef Extctrls::TTimer inherited;
	
public:
	TacBorderForm* BorderForm;
	Scommondata::TsCommonData* SkinData;
	HWND FormHandle;
	TsCaptionButton *PBtnData;
	int CurrentLevel;
	int CurrentState;
	bool Up;
	int MaxIterations;
	Forms::TForm* AForm;
	Graphics::TBitmap* ABmp;
	__fastcall virtual TacSBAnimation(Classes::TComponent* AOwner);
	__fastcall virtual ~TacSBAnimation(void);
	Types::TRect __fastcall GetFormBounds();
	int __fastcall Offset(void);
	int __fastcall Step(void);
	void __fastcall MakeForm(void);
	void __fastcall UpdateForm(const int Blend);
	void __fastcall StartAnimation(int NewState, bool ToUp);
	void __fastcall ChangeState(int NewState, bool ToUp);
	void __fastcall MakeImg(void);
	void __fastcall CheckMouseLeave(void);
	void __fastcall OnAnimTimer(System::TObject* Sender);
};

/*
#pragma pack(push, 4)
struct TsCaptionButton
{
	int State;
	int ImageIndex;
	Types::TRect Rect;
	bool HaveAlignment;
	int GlowID;
	TacSBAnimation* Timer;
	unsigned HitCode;
} ;
#pragma pack(pop)
*/
class PASCALIMPLEMENTATION TsTitleButton : public Classes::TCollectionItem
{
	typedef Classes::TCollectionItem inherited;
	
private:
	bool FUseSkinData;
	AnsiString FName;
	Graphics::TBitmap* FGlyph;
	Controls::TMouseEvent FOnMouseUp;
	Controls::TMouseEvent FOnMouseDown;
	bool FEnabled;
	AnsiString FHint;
	bool FVisible;
	void __fastcall SetGlyph(const Graphics::TBitmap* Value);
	void __fastcall SetName(const AnsiString Value);
	void __fastcall MouseDown(int BtnIndex, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall MouseUp(int BtnIndex, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall SetVisible(const bool Value);
	void __fastcall OnGlyphChange(System::TObject* Sender);
	
public:
	Controls::THintWindow* HintWnd;
	TsCaptionButton BtnData;
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	__fastcall virtual TsTitleButton(Classes::TCollection* Collection);
	__fastcall virtual ~TsTitleButton(void);
	virtual AnsiString __fastcall GetDisplayName();
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property AnsiString Hint = {read=FHint, write=FHint};
	__property AnsiString Name = {read=FName, write=SetName};
	__property bool UseSkinData = {read=FUseSkinData, write=FUseSkinData, default=1};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
	__property Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
};


class DELPHICLASS TacMoveTimer;
class PASCALIMPLEMENTATION TacMoveTimer : public Acthdtimer::TacThreadedTimer 
{
	typedef Acthdtimer::TacThreadedTimer inherited;
	
public:
	Byte BlendValue;
	Byte CurrentBlendValue;
	Byte BlendStep;
	TsSkinProvider* SP;
	TacBorderForm* BorderForm;
	unsigned FormHandle;
	virtual void __fastcall TimeHandler(void);
public:
	#pragma option push -w-inl
	/* TacThreadedTimer.Create */ inline __fastcall virtual TacMoveTimer(Classes::TComponent* AOwner) : Acthdtimer::TacThreadedTimer(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacThreadedTimer.CreateOwned */ inline __fastcall virtual TacMoveTimer(Classes::TComponent* AOwner, bool ChangeEvent) : Acthdtimer::TacThreadedTimer(AOwner, ChangeEvent) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacThreadedTimer.Destroy */ inline __fastcall virtual ~TacMoveTimer(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacMinTimer;
class PASCALIMPLEMENTATION TacMinTimer : public Acthdtimer::TacThreadedTimer 
{
	typedef Acthdtimer::TacThreadedTimer inherited;
	
public:
	#pragma pack(push, 1)
	Types::TRect RectFrom;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect RectTo;
	#pragma pack(pop)
	
	double CurLeft;
	double CurTop;
	double CurRight;
	double CurBottom;
	double DeltaX;
	double DeltaY;
	int XFrom;
	int XTo;
	int YFrom;
	int YTo;
	double DeltaW;
	double DeltaH;
	Byte AlphaOrigin;
	Byte AlphaFrom;
	Byte AlphaTo;
	Byte CurrentAlpha;
	double BlendStep;
	Forms::TForm* AnimForm;
	unsigned TBPosition;
	TsSkinProvider* sp;
	TacBorderForm* BorderForm;
	unsigned FormHandle;
	Graphics::TBitmap* SavedImage;
	Graphics::TBitmap* AlphaBmp;
	bool Minimized;
	int StepCount;
	bool AlphaFormWasCreated;
	__fastcall virtual TacMinTimer(Classes::TComponent* AOwner);
	__fastcall virtual TacMinTimer(Classes::TComponent* AOwner, bool ChangeEvent);
	__fastcall virtual ~TacMinTimer(void);
	Types::TRect __fastcall GetRectTo();
	void __fastcall InitData(void);
	void __fastcall UpdateDstRect(void);
	virtual void __fastcall TimeHandler(void);
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint UserButtonsOffset = 0x8;
static const Shortint ScrollWidth = 0x12;
static const Shortint IconicHeight = 0x1a;
static const Word HTUDBTN = 0x3e8;
static const Shortint FS_SIZING = 0x1;
static const Byte FS_BLENDMOVING = 0x80;
static const Word FS_ANIMMINIMIZING = 0x100;
static const Word FS_ANIMCLOSING = 0x200;
static const Word FS_ANIMRESTORING = 0x400;
static const Word FS_THUMBDRAWING = 0x800;
static const Word FS_CHANGING = 0x1000;
static const Word FS_MAXHEIGHT = 0x2000;
static const Word FS_MAXWIDTH = 0x4000;
static const Word FS_ACTIVATE = 0x8000;
static const Word FS_MAXBOUNDS = 0x6000;
static const Word FS_FULLPAINTING = 0x1180;
extern PACKAGE int Style;
extern PACKAGE Sskinmenus::TMenuItemData HotItem;
extern PACKAGE Menus::TMenuItem* SelectedMenuItem;
extern PACKAGE bool acTaskBarChanging;
extern PACKAGE bool bInProcess;
extern PACKAGE bool DoStartMove;
extern PACKAGE bool bCapture;
extern PACKAGE bool bFlag;
extern PACKAGE bool bRemoving;
extern PACKAGE bool bMode;
extern PACKAGE HWND deskwnd;
extern PACKAGE HDC formDC;
extern PACKAGE int ntop;
extern PACKAGE int nleft;
extern PACKAGE int nbottom;
extern PACKAGE int nright;
extern PACKAGE int nX;
extern PACKAGE int nY;
extern PACKAGE int nDirection;
extern PACKAGE int nMinHeight;
extern PACKAGE int nMinWidth;
extern PACKAGE int nDC;
extern PACKAGE unsigned hDWMAPI;
extern PACKAGE bool __fastcall SetThumbIcon(HWND Handle, TsSkinProvider* sp, int Width, int Height);
extern PACKAGE bool __fastcall SetPreviewBmp(HWND Handle, TsSkinProvider* sp);
extern PACKAGE void __fastcall DwmInvalidateIconicBitmaps(HWND hwnd);
extern PACKAGE void __fastcall SetFormBlendValue(unsigned FormHandle, Graphics::TBitmap* Bmp, int Value, Types::PPoint NewPos = (void *)(0x0));
extern PACKAGE Forms::TForm* __fastcall MakeCoverForm(unsigned Wnd);
extern PACKAGE unsigned __fastcall ShellTrayWnd(void);
extern PACKAGE void __fastcall StartMinimizing(TsSkinProvider* sp);
extern PACKAGE bool __fastcall StartRestoring(TsSkinProvider* sp);
extern PACKAGE void __fastcall StartBlendOnMoving(TsSkinProvider* sp);
extern PACKAGE void __fastcall FinishBlendOnMoving(TsSkinProvider* sp);
extern PACKAGE void __fastcall PaintFormTo(Graphics::TBitmap* DstBmp, TsSkinProvider* sp);
extern PACKAGE void __fastcall StartSBAnimation(const PsCaptionButton Btn, const int State, const int Iterations, const bool ToUp, const TsSkinProvider* SkinProvider, void * acDialog = (void *)(0x0));
extern PACKAGE int __fastcall SysBorderWidth(const HWND Handle, const TacBorderForm* BorderForm, bool CheckSkin = true);
extern PACKAGE int __fastcall SysBorderHeight(const HWND Handle, const TacBorderForm* BorderForm, bool CheckSkin = true);
extern PACKAGE int __fastcall SkinTitleHeight(const TacBorderForm* BorderForm);
extern PACKAGE int __fastcall SkinBorderWidth(const TacBorderForm* BorderForm);
extern PACKAGE Types::TPoint __fastcall SkinMenuOffset(const TsSkinProvider* sp);
extern PACKAGE int __fastcall DiffTitle(const TacBorderForm* BorderForm);
extern PACKAGE int __fastcall DiffBorder(const TacBorderForm* BorderForm);
extern PACKAGE void __fastcall InitDwmApi(void);
extern PACKAGE HRESULT __fastcall DwmSetWindowAttribute(HWND hwnd, unsigned dwAttribute, void * pvAttribute, unsigned cbAttribute);
extern PACKAGE bool __fastcall AeroIsEnabled(void);
extern PACKAGE bool __fastcall ForbidSysAnimating(void);
extern PACKAGE void __fastcall InitDwm(const unsigned Handle, const bool Skinned, const bool Repaint = false);
extern PACKAGE bool __fastcall BigButtons(TsSkinProvider* sp);
extern PACKAGE bool __fastcall IsBorderUnchanged(const int BorderIndex, const Sskinmanager::TsSkinManager* sm);
extern PACKAGE bool __fastcall IsGripVisible(const TsSkinProvider* sp);
extern PACKAGE bool __fastcall InAnimation(const TsSkinProvider* sp);
extern PACKAGE void __fastcall PaintGrip(const HDC aDC, const TsSkinProvider* sp);
extern PACKAGE bool __fastcall CtrlIsReadyForHook(const Controls::TWinControl* Ctrl);
extern PACKAGE void __fastcall FillArOR(TsSkinProvider* sp);
extern PACKAGE void __fastcall UpdateRgn(TsSkinProvider* sp, bool Repaint = true);
extern PACKAGE HRGN __fastcall GetRgnFromArOR(TsSkinProvider* sp, int X = 0x0, int Y = 0x0);
extern PACKAGE void __fastcall ForbidDrawing(TsSkinProvider* sp, bool MDIAlso = false);
extern PACKAGE void __fastcall PermitDrawing(TsSkinProvider* sp, bool MDIAlso = false);
extern PACKAGE bool __fastcall HaveBorder(TsSkinProvider* sp);
extern PACKAGE void __fastcall UpdateSkinCaption(TsSkinProvider* SkinProvider);
extern PACKAGE TsSkinProvider* __fastcall GetSkinProvider(Classes::TComponent* Cmp);
extern PACKAGE void __fastcall DrawAppIcon(TsSkinProvider* SkinProvider);
extern PACKAGE int __fastcall GetWindowWidth(HWND Handle);
extern PACKAGE int __fastcall GetClientWidth(HWND Handle);
extern PACKAGE int __fastcall GetWindowHeight(HWND Handle);
extern PACKAGE int __fastcall GetClientHeight(HWND Handle);
extern PACKAGE void __fastcall UpdateMainForm(bool UpdateNow = true);
extern PACKAGE bool __fastcall DoLayered(HWND FormHandle, bool Layered);
extern PACKAGE Types::TRect __fastcall acWorkRect(Forms::TForm* Form);

}	/* namespace Sskinprovider */
using namespace Sskinprovider;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sSkinProvider
