// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acSBUtils.pas' rev: 6.00

#ifndef acSBUtilsHPP
#define acSBUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <TypInfo.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <acAlphaImageList.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acsbutils
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDropMarkMode { dmmNone, dmmLeft, dmmRight };
#pragma option pop

#pragma pack(push, 4)
struct THeaderPaintInfo
{
	Graphics::TCanvas* TargetCanvas;
	Classes::TCollectionItem* Column;
	Types::TRect PaintRectangle;
	Types::TRect TextRectangle;
	bool IsHoverIndex;
	bool IsDownIndex;
	bool IsEnabled;
	bool ShowHeaderGlyph;
	bool ShowSortGlyph;
	bool ShowRightBorder;
	TDropMarkMode DropMark;
	Types::TPoint GlyphPos;
	Types::TPoint SortGlyphPos;
} ;
#pragma pack(pop)

#pragma option push -b-
enum acSBUtils__1 { hpeBackground, hpeDropMark, hpeHeaderGlyph, hpeSortGlyph, hpeText };
#pragma option pop

typedef Set<acSBUtils__1, hpeBackground, hpeText>  THeaderPaintElements;

typedef void __fastcall (__closure *TAdvancedHeaderPaintEvent)(Classes::TPersistent* Sender, THeaderPaintInfo &PaintInfo, const THeaderPaintElements Elements);

typedef void __fastcall (__closure *THeaderPaintQueryElementsEvent)(Classes::TPersistent* Sender, THeaderPaintInfo &PaintInfo, THeaderPaintElements &Elements);

typedef TAdvancedHeaderPaintEvent *PAdvancedHeaderPaintEvent;

typedef THeaderPaintQueryElementsEvent *PHeaderPaintQueryElementsEvent;

class DELPHICLASS TacScrollBar;
class DELPHICLASS TacScrollWnd;
class DELPHICLASS TacMainWnd;
class PASCALIMPLEMENTATION TacMainWnd : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	bool DlgMode;
	AnsiString Caption;
	#pragma pack(push, 1)
	Types::TRect WndRect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	tagSIZE WndSize;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TPoint WndPos;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect ParentRect;
	#pragma pack(pop)
	
	HWND ParentWnd;
	Classes::TWndMethod OldWndProc;
	void *OldProc;
	HWND CtrlHandle;
	Sskinmanager::TsSkinManager* SkinManager;
	Scommondata::TsCommonData* SkinData;
	bool DontRepaint;
	bool ParamsChanged;
	Graphics::TColor StdColor;
	Graphics::TColor StdFontColor;
	bool Destroyed;
	bool OwnSkinData;
	void *NewWndProcInstance;
	int Tag;
	__fastcall virtual TacMainWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	virtual void __fastcall SaveStdParams(void);
	virtual void __fastcall RestoreStdParams(void);
	virtual void __fastcall SetSkinParams(void);
	__fastcall virtual ~TacMainWnd(void);
	int __fastcall CallPrevWndProc(HWND Handle, int Msg, int WParam, int &LParam);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
};


class PASCALIMPLEMENTATION TacScrollWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Word bars;
	TacScrollBar* sBarHorz;
	TacScrollBar* sBarVert;
	bool fThumbTracking;
	bool fLeftScrollbar;
	int cxLeftEdge;
	int cxRightEdge;
	int cyTopEdge;
	int cyBottomEdge;
	bool bPreventStyleChange;
	__fastcall virtual ~TacScrollWnd(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacScrollWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TacScrollBar : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Word fScrollFlags;
	bool fScrollVisible;
	#pragma pack(push, 1)
	tagSCROLLINFO ScrollInfo;
	#pragma pack(pop)
	
	int nArrowLength;
	int nArrowWidth;
	int nButSizeBefore;
	int nButSizeAfter;
	bool fButVisibleBefore;
	bool fButVisibleAfter;
	Word nBarType;
	Word fFlatScrollbar;
	int nMinThumbSize;
	TacScrollWnd* sw;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TacScrollBar(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TacScrollBar(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacSpeedButtonHandler;
class PASCALIMPLEMENTATION TacSpeedButtonHandler : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	#pragma pack(push, 1)
	Types::TRect WndRect;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	tagSIZE WndSize;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TPoint WndPos;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect ParentRect;
	#pragma pack(pop)
	
	HWND ParentWnd;
	Controls::TControl* Ctrl;
	Classes::TWndMethod OldWndProc;
	void *OldProc;
	Sskinmanager::TsSkinManager* SkinManager;
	Scommondata::TsCommonData* SkinData;
	bool Destroyed;
	void *NewWndProcInstance;
	__fastcall virtual TacSpeedButtonHandler(Controls::TControl* Btn, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacSpeedButtonHandler(void);
	int __fastcall CallPrevWndProc(Controls::TControl* Ctrl, int Msg, int WParam, int &LParam);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	void __fastcall AC_WMPaint(Messages::TWMPaint &Message);
	void __fastcall PrepareCache(void);
	void __fastcall DrawCaption(void);
	void __fastcall DrawGlyph(void);
	AnsiString __fastcall Caption();
	Types::TRect __fastcall ImgRect();
	int __fastcall GlyphHeight(void);
	Types::TRect __fastcall CaptionRect();
	tagSIZE __fastcall TextRectSize();
	int __fastcall GlyphWidth(void);
	void __fastcall DoDrawText(Types::TRect &Rect, int Flags);
	int __fastcall CurrentState(void);
};


class DELPHICLASS TacStaticWnd;
class PASCALIMPLEMENTATION TacStaticWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	virtual void __fastcall AC_WMPaint(Messages::TWMPaint &Message);
	virtual bool __fastcall PaintText(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacStaticWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacStaticWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacEdgeWnd;
class PASCALIMPLEMENTATION TacEdgeWnd : public TacStaticWnd 
{
	typedef TacStaticWnd inherited;
	
public:
	virtual void __fastcall AC_WMPaint(Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacEdgeWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacStaticWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacEdgeWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacIconWnd;
class PASCALIMPLEMENTATION TacIconWnd : public TacStaticWnd 
{
	typedef TacStaticWnd inherited;
	
public:
	bool IsBmp;
	Graphics::TBitmap* FBmp;
	__fastcall virtual TacIconWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacIconWnd(void);
	virtual bool __fastcall PaintText(void);
};


class DELPHICLASS TacDlgPanelWnd;
class PASCALIMPLEMENTATION TacDlgPanelWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Extctrls::TPanel* Panel;
	__fastcall virtual TacDlgPanelWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	DYNAMIC void __fastcall PrepareCache(void);
	void __fastcall AC_WMNCPaint(HDC aDC);
	void __fastcall AC_WMPaint(HDC aDC);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual void __fastcall SetSkinParams(void);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacDlgPanelWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacLinkWnd;
class PASCALIMPLEMENTATION TacLinkWnd : public TacStaticWnd 
{
	typedef TacStaticWnd inherited;
	
public:
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual bool __fastcall PaintText(void);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacLinkWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacStaticWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacLinkWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacBtnWnd;
class PASCALIMPLEMENTATION TacBtnWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	__fastcall virtual TacBtnWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	unsigned __fastcall CtrlStyle(void);
	bool __fastcall Down(void);
	int __fastcall CurrentState(void);
	virtual void __fastcall DrawCaption(void);
	virtual void __fastcall DrawGlyph(void);
	virtual tagSIZE __fastcall GlyphSize();
	virtual void __fastcall DoDrawText(Types::TRect &Rect, int Flags);
	virtual Types::TRect __fastcall CaptionRect();
	virtual int __fastcall MaxCaptionWidth(void);
	virtual tagSIZE __fastcall TextRectSize();
	virtual void __fastcall PrepareCache(void);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	void __fastcall Repaint(void);
	virtual void __fastcall RestoreStdParams(void);
	virtual void __fastcall SetSkinParams(void);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacBtnWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacBitBtnWnd;
class PASCALIMPLEMENTATION TacBitBtnWnd : public TacBtnWnd 
{
	typedef TacBtnWnd inherited;
	
public:
	HBITMAP hBmp;
	HICON hIco;
	virtual Types::TRect __fastcall CaptionRect();
	Types::TRect __fastcall GlyphRect();
	virtual tagSIZE __fastcall GlyphSize();
	virtual void __fastcall DrawGlyph(void);
	virtual int __fastcall MaxCaptionWidth(void);
public:
	#pragma option push -w-inl
	/* TacBtnWnd.Create */ inline __fastcall virtual TacBitBtnWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacBtnWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacBitBtnWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacSizerWnd;
class PASCALIMPLEMENTATION TacSizerWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacSizerWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacSizerWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacSpinWnd;
class PASCALIMPLEMENTATION TacSpinWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	int lOffset;
	bool bMousePressed;
	int Btn1State;
	int Btn2State;
	virtual bool __fastcall IsVertical(void);
	__fastcall virtual TacSpinWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	void __fastcall PrepareCache(void);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacSpinWnd(void) { }
	#pragma option pop
	
};


typedef DynamicArray<Types::TPoint >  TAPoint;

class DELPHICLASS TacTrackWnd;
class PASCALIMPLEMENTATION TacTrackWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	bool bMousePressed;
	int TrackBarNdx;
	int TickHeight;
	double iStep;
	virtual bool __fastcall IsVertical(void);
	__fastcall virtual TacTrackWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	void __fastcall PrepareCache(void);
	void __fastcall PaintBody(void);
	void __fastcall PaintBar(void);
	void __fastcall PaintThumb(int i);
	void __fastcall PaintTicksHor(void);
	void __fastcall PaintTicksVer(void);
	void __fastcall PaintTick(const Types::TPoint &P, bool Horz);
	Comctrls::TTickMark __fastcall TickMarks(void);
	Comctrls::TTickStyle __fastcall TickStyle(void);
	int __fastcall TickCount(void);
	TAPoint __fastcall TicksArray();
	int __fastcall TickPos(int i);
	Types::TRect __fastcall ThumbRect();
	Types::TRect __fastcall ChannelRect();
	int __fastcall Mode(void);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacTrackWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacCheckBoxWnd;
class PASCALIMPLEMENTATION TacCheckBoxWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	bool OwnerDraw;
	Stdctrls::TCheckBoxState __fastcall State(void);
	int __fastcall CtlState(void);
	Types::TRect __fastcall CheckRect();
	Types::TRect __fastcall SkinCheckRect(int i);
	int __fastcall SkinGlyphWidth(int i);
	int __fastcall SkinGlyphHeight(int i);
	void __fastcall DrawCheckText(void);
	void __fastcall DrawSkinGlyph(int i);
	short __fastcall GlyphMaskIndex(Stdctrls::TCheckBoxState State);
	void __fastcall PrepareCache(void);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	__fastcall virtual TacCheckBoxWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacCheckBoxWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacToolBarWnd;
class PASCALIMPLEMENTATION TacToolBarWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	#pragma pack(push, 1)
	Types::TRect ClientRect;
	#pragma pack(pop)
	
	int BorderWidth;
	int HotBtn;
	void __fastcall PrepareCache(void);
	void __fastcall DrawButtons(Graphics::TBitmap* Bmp);
	void __fastcall DrawBtn(int Index, const Types::TRect &R, HDC DC);
	Types::TRect __fastcall GetButtonRect(int Index);
	int __fastcall Count(void);
	Types::TRect __fastcall ButtonRect(int Index);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	void __fastcall AC_WMPrint(const Messages::TWMPaint &Message);
	void __fastcall AC_WMNCPaint(const Messages::TMessage &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacToolBarWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacToolBarWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacTransPanelWnd;
class PASCALIMPLEMENTATION TacTransPanelWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	virtual void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacTransPanelWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacTransPanelWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacGroupBoxWnd;
class PASCALIMPLEMENTATION TacGroupBoxWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	__fastcall virtual TacGroupBoxWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	Types::TRect __fastcall CaptionRect();
	void __fastcall PrepareCache(void);
	void __fastcall WriteText(const Types::TRect &R);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacGroupBoxWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacTabWnd;
class PASCALIMPLEMENTATION TacTabWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Types::TRect __fastcall DisplayRect();
	void __fastcall PrepareCache(void);
	void __fastcall AC_WMPaint(const Messages::TWMPaint &Message);
	void __fastcall AC_WMNCPaint(const Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacTabWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacMainWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacTabWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacPanelWnd;
class PASCALIMPLEMENTATION TacPanelWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	__fastcall virtual TacPanelWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	virtual void __fastcall PrepareCache(void);
	void __fastcall AC_WMNCPaint(HDC aDC);
	virtual void __fastcall AC_WMPaint(HDC &aDC);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	void __fastcall WriteText(const Types::TRect &R, Graphics::TCanvas* aCanvas = (Graphics::TCanvas*)(0x0), HDC aDC = (HDC)(0x0));
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacPanelWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacMnuWnd;
class PASCALIMPLEMENTATION TacMnuWnd : public TacScrollWnd 
{
	typedef TacScrollWnd inherited;
	
public:
	int RgnChanged;
	DYNAMIC void __fastcall PrepareCache(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	__fastcall virtual TacMnuWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacMnuWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacBaseWnd;
class PASCALIMPLEMENTATION TacBaseWnd : public TacScrollWnd 
{
	typedef TacScrollWnd inherited;
	
public:
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacBaseWnd(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacBaseWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacScrollWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
};


class DELPHICLASS TacMDIWnd;
class PASCALIMPLEMENTATION TacMDIWnd : public TacBaseWnd 
{
	typedef TacBaseWnd inherited;
	
public:
	Forms::TForm* FForm;
	Scommondata::TsCommonData* MDISkinData;
	System::TObject* SkinProvider;
	__fastcall virtual ~TacMDIWnd(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	void __fastcall UpdateGraphControls(void);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Create */ inline __fastcall virtual TacMDIWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacBaseWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
};


class DELPHICLASS TacEditWnd;
class PASCALIMPLEMENTATION TacEditWnd : public TacBaseWnd 
{
	typedef TacBaseWnd inherited;
	
public:
	Graphics::TColor Color;
	Graphics::TColor FocusColor;
	int FrameColor;
	Graphics::TBrush* Brush;
	__fastcall virtual TacEditWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual void __fastcall SaveStdParams(void);
	virtual void __fastcall SetSkinParams(void);
	virtual void __fastcall RestoreStdParams(void);
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacEditWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacComboListWnd;
class PASCALIMPLEMENTATION TacComboListWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	bool Showed;
	bool SimplyBox;
	__fastcall virtual TacComboListWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall TacComboListWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint, bool Simply);
	__fastcall virtual ~TacComboListWnd(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
};


class DELPHICLASS TacListViewWnd;
class PASCALIMPLEMENTATION TacListViewWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	HWND FhWndHeader;
	void *FhHeaderProc;
	void *FhDefHeaderProc;
	int FPressedColumn;
	int HoverColIndex;
	int ListLineHeight;
	bool FFlag;
	Comctrls::TViewStyle __fastcall ViewStyle(void);
	__fastcall virtual TacListViewWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual void __fastcall RestoreStdParams(void);
	virtual void __fastcall SaveStdParams(void);
	virtual void __fastcall SetSkinParams(void);
	void __fastcall ColumnSkinPaint(const Types::TRect &ControlRect, int cIndex, HDC DC);
	int __fastcall AllColWidth(void);
	bool __fastcall HotTrack(void);
	void __fastcall HeaderWndProc(Messages::TMessage &Message);
	Types::TRect __fastcall GetHeaderColumnRect(int Index);
	void __fastcall PaintHeader(HDC DC);
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacListViewWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacGridWnd;
class PASCALIMPLEMENTATION TacGridWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	Graphics::TColor FixedColor;
	Graphics::TColor FooterColor;
	Graphics::TColor FooterCellColor;
	Graphics::TColor TitleFontColor;
	Graphics::TColor TitleColor;
	Graphics::TColor IndColor;
	Graphics::TColor SelectionColor;
	Graphics::TColor SelectionTextColor;
	Graphics::TColor GridLineColor;
	Graphics::TColor GridFixedLineColor;
	Graphics::TColor FixedGradientFrom;
	Graphics::TColor FixedGradientTo;
	Graphics::TColor FixedGradientMirrorFrom;
	Graphics::TColor FixedGradientMirrorTo;
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual void __fastcall SaveStdParams(void);
	virtual void __fastcall SetSkinParams(void);
	virtual void __fastcall RestoreStdParams(void);
public:
	#pragma option push -w-inl
	/* TacEditWnd.Create */ inline __fastcall virtual TacGridWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacEditWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacGridWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacGridEhWnd;
class PASCALIMPLEMENTATION TacGridEhWnd : public TacGridWnd 
{
	typedef TacGridWnd inherited;
	
public:
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacEditWnd.Create */ inline __fastcall virtual TacGridEhWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacGridWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacGridEhWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacTreeViewWnd;
class PASCALIMPLEMENTATION TacTreeViewWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	virtual void __fastcall SetSkinParams(void);
	virtual void __fastcall RestoreStdParams(void);
	__fastcall virtual ~TacTreeViewWnd(void);
public:
	#pragma option push -w-inl
	/* TacEditWnd.Create */ inline __fastcall virtual TacTreeViewWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacEditWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
};


class DELPHICLASS TacComboBoxWnd;
class PASCALIMPLEMENTATION TacComboBoxWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	HWND FListHandle;
	void *FDefListProc;
	Scommondata::TsCommonData* LBSkinData;
	TacComboListWnd* ListSW;
	bool LBoxOpening;
	bool __fastcall DroppedDown(void);
	int __fastcall ButtonHeight(void);
	virtual Types::TRect __fastcall ButtonRect();
	void __fastcall PaintButton(HDC DC);
	void __fastcall RepaintButton(void);
	void __fastcall PaintText(void);
	void __fastcall PrepareSimple(void);
	__fastcall virtual TacComboBoxWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacComboBoxWnd(void);
	void __fastcall Invalidate(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
};


class DELPHICLASS TacVirtualTreeViewWnd;
class PASCALIMPLEMENTATION TacVirtualTreeViewWnd : public TacEditWnd 
{
	typedef TacEditWnd inherited;
	
public:
	Graphics::TColor CompressedTextColor;
	Graphics::TColor FileTextColor;
	Graphics::TColor FolderTextColor;
	bool OwnerDraw;
	Typinfo::TPropInfo *PropInfo;
	void __fastcall AdvancedHeaderDraw(Classes::TPersistent* Sender, THeaderPaintInfo &PaintInfo, const THeaderPaintElements Elements);
	void __fastcall HeaderDrawQueryElements(Classes::TPersistent* Sender, THeaderPaintInfo &PaintInfo, THeaderPaintElements &Elements);
	virtual void __fastcall SaveStdParams(void);
	virtual void __fastcall SetSkinParams(void);
	virtual void __fastcall RestoreStdParams(void);
	tagSIZE __fastcall GetBorderDimensions();
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacEditWnd.Create */ inline __fastcall virtual TacVirtualTreeViewWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint) : TacEditWnd(AHandle, ASkinData, ASkinManager, SkinSection, Repaint) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TacScrollWnd.Destroy */ inline __fastcall virtual ~TacVirtualTreeViewWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacWWComboBoxWnd;
class PASCALIMPLEMENTATION TacWWComboBoxWnd : public TacComboBoxWnd 
{
	typedef TacComboBoxWnd inherited;
	
private:
	Stdctrls::TCustomListBox* ListBox;
	TacScrollWnd* ListBoxSW;
	Scommondata::TsCommonData* ListBoxSkinData;
	bool FShowButton;
	bool __fastcall GetShowButton(Controls::TWinControl* aCtrl);
	
public:
	virtual Types::TRect __fastcall ButtonRect();
	__fastcall TacWWComboBoxWnd(Controls::TWinControl* aCtrl, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacWWComboBoxWnd(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
};


class DELPHICLASS TacTabControlWnd;
class PASCALIMPLEMENTATION TacTabControlWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	TacSpinWnd* BtnSW;
	int __fastcall TabCount(void);
	virtual Types::TRect __fastcall ClientRect();
	virtual Types::TRect __fastcall PageRect();
	Types::TRect __fastcall TabRect(const int Index);
	int __fastcall TabRow(int TabIndex);
	Types::TRect __fastcall TabsRect();
	Comctrls::TTabPosition __fastcall TabPosition(void);
	Comctrls::TTabStyle __fastcall Style(void);
	int __fastcall ActiveTabIndex(void);
	Types::TRect __fastcall SkinTabRect(int Index, bool Active);
	void __fastcall CheckUpDown(void);
	void __fastcall DrawSkinTabs(const Sconst::TCacheInfo &CI);
	void __fastcall DrawSkinTab(int Index, int State, Graphics::TBitmap* Bmp, const Types::TPoint &OffsetPoint)/* overload */;
	void __fastcall DrawSkinTab(int Index, int State, HDC DC)/* overload */;
	void __fastcall AC_WMPaint(Messages::TWMPaint &Message);
	__fastcall virtual TacTabControlWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	__fastcall virtual ~TacTabControlWnd(void);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
};


class DELPHICLASS TacPageWnd;
class PASCALIMPLEMENTATION TacPageWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Comctrls::TTabSheet* Page;
	Comctrls::TTabPosition __fastcall TabPosition(void);
	void __fastcall PrepareCache(void);
	void __fastcall AC_WMEraseBKGnd(Messages::TWMPaint &Message);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	__fastcall virtual TacPageWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacPageWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacPageControlWnd;
class PASCALIMPLEMENTATION TacPageControlWnd : public TacTabControlWnd 
{
	typedef TacTabControlWnd inherited;
	
public:
	virtual Types::TRect __fastcall ClientRect();
	virtual Types::TRect __fastcall PageRect();
	void __fastcall InitPages(bool Skinned);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
	__fastcall virtual TacPageControlWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
public:
	#pragma option push -w-inl
	/* TacTabControlWnd.Destroy */ inline __fastcall virtual ~TacPageControlWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacToolBarVCLWnd;
class PASCALIMPLEMENTATION TacToolBarVCLWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Comctrls::TToolBar* ToolBar;
	Comctrls::TToolButton* DroppedButton;
	int HotButtonIndex;
	Types::TRect __fastcall DisplayRect();
	void __fastcall WMNCPaint(const HDC aDC = (HDC)(0x0));
	Types::TRect __fastcall GetButtonRect(int Index);
	__fastcall virtual TacToolBarVCLWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	void __fastcall PrepareCache(void);
	int __fastcall IndexByMouse(const Types::TPoint &MousePos);
	void __fastcall RepaintButton(int Index);
	void __fastcall OurAdvancedCustomDraw(Comctrls::TToolBar* Sender, const Types::TRect &ARect, Comctrls::TCustomDrawStage Stage, bool &DefaultDraw);
	void __fastcall OurAdvancedCustomDrawButton(Comctrls::TToolBar* Sender, Comctrls::TToolButton* Button, Comctrls::TCustomDrawState State, Comctrls::TCustomDrawStage Stage, Comctrls::TTBCustomDrawFlags &Flags, bool &DefaultDraw);
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacToolBarVCLWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacStatusBarWnd;
class PASCALIMPLEMENTATION TacStatusBarWnd : public TacMainWnd 
{
	typedef TacMainWnd inherited;
	
public:
	Comctrls::TStatusBar* StatusBar;
	bool __fastcall SimplePanel(void);
	int __fastcall PartsCount(void);
	AnsiString __fastcall PartText(const int Index);
	Types::TRect __fastcall PartRect(const int Index);
	__fastcall virtual TacStatusBarWnd(HWND AHandle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager, const AnsiString SkinSection, bool Repaint);
	void __fastcall PaintPanels(void);
	void __fastcall DrawPanel(const int Index, const Types::TRect &Rect);
	void __fastcall InternalDrawPanel(const int Index, const AnsiString Text, const Types::TRect &Rect);
	void __fastcall DoDrawText(const AnsiString Text, Types::TRect &Rect, const int Flags);
	void __fastcall PrepareCache(void);
	void __fastcall WMPaint(const HDC aDC = (HDC)(0x0));
	void __fastcall WMNCPaint(const HDC aDC = (HDC)(0x0));
	virtual void __fastcall acWndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TacMainWnd.Destroy */ inline __fastcall virtual ~TacStatusBarWnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacWinControl;
class PASCALIMPLEMENTATION TacWinControl : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
public:
	#pragma option push -w-inl
	/* TWinControl.Create */ inline __fastcall virtual TacWinControl(Classes::TComponent* AOwner) : Controls::TWinControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TacWinControl(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TacWinControl(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define acPropStr "ACSBSC"
static const Shortint CSBS_NORMAL = 0x0;
static const Shortint CSBS_HOTTRACKED = 0x2;
static const Shortint CSBS_THUMBALWAYS = 0x4;
static const Shortint CSBS_VISIBLE = 0x8;
static const Shortint THUMBTRACK_SNAPDIST = 0x18;
static const Shortint MINTHUMBSIZE_NT4 = 0x8;
static const Shortint MINTHUMBSIZE_2000 = 0x6;
static const Shortint SM_CXVERTSB = 0x1;
static const Shortint SM_CYVERTSB = 0x0;
static const Shortint SM_CXHORZSB = 0x0;
static const Shortint SM_CYHORZSB = 0x1;
static const Shortint SM_SCROLL_LENGTH = 0x0;
static const Shortint COOLSB_NONE = 0xffffffff;
static const Shortint HTSCROLL_NONE = 0xffffffff;
static const Shortint HTSCROLL_NORMAL = 0xffffffff;
static const Shortint SYSTEM_METRIC = 0xffffffff;
static const Shortint HTSCROLL_LEFT = 0x0;
static const Shortint HTSCROLL_UP = 0x0;
static const Shortint HTSCROLL_DOWN = 0x1;
static const Shortint HTSCROLL_RIGHT = 0x1;
static const Shortint HTSCROLL_THUMB = 0x5;
static const Shortint HTSCROLL_PAGELEFT = 0x2;
static const Shortint HTSCROLL_PAGERIGHT = 0x3;
static const Shortint HTSCROLL_PAGEUP = 0x2;
static const Shortint HTSCROLL_PAGEDOWN = 0x3;
static const Word COOLSB_TIMERID1 = 0xfffd;
static const Word COOLSB_TIMERID2 = 0xfffe;
static const Word COOLSB_TIMERID3 = 0xfff2;
static const Word COOLSB_TIMERINTERVAL1 = 0x12c;
static const Shortint COOLSB_TIMERINTERVAL2 = 0x37;
static const Shortint COOLSB_TIMERINTERVAL3 = 0x14;
#define acColor "Color"
#define acTitleFont "TitleFont"
#define acDataSource "DataSource"
#define acFont "Font"
#define acFixedFont "FixedFont"
#define acFixedColor "FixedColor"
#define acHeaderFont "HeaderFont"
#define acColumns "Columns"
#define acSelectionColor "SelectionColor"
#define acSelectionTextColor "SelectionTextColor"
#define acControlLook "ControlLook"
#define acFixedGradientFrom "FixedGradientFrom"
#define acFixedGradientTo "FixedGradientTo"
#define acFixedGradientMirrorFrom "FixedGradientMirrorFrom"
#define acFixedGradientMirrorTo "FixedGradientMirrorTo"
#define acGridFixedLineColor "GridFixedLineColor"
#define acGridLineColor "GridLineColor"
#define acIndColor "IndicatorIconColor"
#define acFooterColor "FooterColor"
#define acFooterCellColor "FooterCellColor"
#define acTitleColor "TitleColor"
#define acTwwDBGrid "TwwDBGrid"
#define acVETColors "VETColors"
#define acCompressedTextColor "CompressedTextColor"
#define acFileTextColor "FileTextColor"
#define acFolderTextColor "FolderTextColor"
#define acFocusColor "FocusColor"
#define acOnAdvancedHeaderDraw "OnAdvancedHeaderDraw"
#define acOnHeaderDrawQueryElements "OnHeaderDrawQueryElements"
#define achoOwnerDraw "hoOwnerDraw"
#define achoVisible "hoVisible"
#define acPaintInfoColumn "PaintInfoColumn"
#define acThemed "Themed"
#define acStyle "Style"
#define acHeight "Height"
#define acTDBAdvGrid "TDBAdvGrid"
#define acTAdvStringGrid "TAdvStringGrid"
#define acOptions "Options"
#define acHeader "Header"
static const Shortint PreviewBorderWidth = 0x6;
static const Shortint TopOffset = 0x4;
static const Shortint BottomOffset = 0x1;
static const Shortint LeftOffset = 0x1;
static const Shortint RightOffset = 0x1;
extern PACKAGE int nLastSBPos;
extern PACKAGE bool acDlgMode;
extern PACKAGE bool inPaint;
extern PACKAGE void __stdcall (*Ac_UninitializeFlatSB)(HWND hWnd);
extern PACKAGE BOOL __stdcall (*Ac_InitializeFlatSB)(HWND hWnd);
extern PACKAGE void __fastcall AlphaBroadCastCheck(Controls::TControl* Control, HWND Handle, void *Message);
extern PACKAGE bool __fastcall MayBeHot(const Scommondata::TsCommonData* SkinData);
extern PACKAGE void __fastcall InitCtrlData(HWND Wnd, HWND &ParentWnd, Types::TRect &WndRect, Types::TRect &ParentRect, tagSIZE &WndSize, Types::TPoint &WndPos, const AnsiString Caption);
extern PACKAGE void __fastcall RefreshScrolls(Scommondata::TsCommonData* SkinData, TacScrollWnd* &ListSW);
extern PACKAGE void __fastcall RefreshEditScrolls(Scommondata::TsCommonData* SkinData, TacScrollWnd* &ListSW);
extern PACKAGE void __fastcall RefreshTreeScrolls(Scommondata::TsCommonData* SkinData, TacScrollWnd* &ListSW);
extern PACKAGE void __fastcall UpdateScrolls(TacScrollWnd* sw, bool Repaint = false);
extern PACKAGE void __fastcall PrepareCache(Scommondata::TsCommonData* SkinData, HWND CtrlHandle = (HWND)(0x0), bool DlgMode = false);
extern PACKAGE void __fastcall UninitializeACScroll(HWND Handle, bool FreeSW, bool Repaint, TacScrollWnd* &ListSW);
extern PACKAGE void __fastcall InitControl(HWND Handle, Scommondata::TsCommonData* ASkinData, Sskinmanager::TsSkinManager* ASkinManager);
extern PACKAGE bool __fastcall Scrolls_SetStyle(HWND Handle, int wBar, int nStyle);
extern PACKAGE void __fastcall InitializeACScrolls(TacScrollWnd* sw, HWND AHandle, bool Repaint = true);
extern PACKAGE void __fastcall InitializeACWnd(TacMainWnd* sw, HWND AHandle);
extern PACKAGE void __fastcall UninitializeACWnd(HWND Handle, bool FreeSW, bool Repaint, TacMainWnd* &ListSW);
extern PACKAGE TacScrollWnd* __fastcall HookScrollWnd(HWND Handle, Sskinmanager::TsSkinManager* ASkinManager, Scommondata::TsCommonData* ASkinData = (Scommondata::TsCommonData*)(0x0));
extern PACKAGE int __fastcall Ac_SetScrollInfo(HWND Handle, int fnBar, const tagSCROLLINFO &si, bool fRedraw);
extern PACKAGE void __fastcall Ac_RedrawNonClient(HWND Handle, bool fFrameChanged);
extern PACKAGE TacScrollWnd* __fastcall Ac_GetScrollWndFromHwnd(HWND Handle);
extern PACKAGE TacScrollBar* __fastcall Ac_GetScrollBarFromHwnd(HWND Handle, Word nBar);
extern PACKAGE int __fastcall Ac_GetDefaultMinThumbSize(void);
extern PACKAGE bool __fastcall Ac_SetMinThumbSize(HWND Handle, Word wBar, Word Size);
extern PACKAGE int __fastcall GetScrollMetric(TacScrollBar* sBar, int metric, bool Btn = false);
extern PACKAGE void __fastcall AC_GetHScrollRect(TacScrollWnd* sw, HWND Handle, Types::TRect &R);
extern PACKAGE void __fastcall AC_GetVScrollRect(TacScrollWnd* sw, HWND Handle, Types::TRect &R);
extern PACKAGE int __fastcall Ac_NCPaint(TacScrollWnd* sw, HWND Handle, int wParam, int lParam, int ThumbPos = 0xffffffff, HDC aDC = (HDC)(0x0));
extern PACKAGE int __fastcall Ac_NCDrawHScrollbar(TacScrollBar* sb, HWND Handle, HDC DC, const Types::TRect &R, int uDrawFlags, int SliderPos = 0xffffffff);
extern PACKAGE int __fastcall Ac_NCDrawVScrollbar(TacScrollBar* sb, HWND Handle, HDC DC, const Types::TRect &R, int uDrawFlags, int SliderPos = 0xffffffff);
extern PACKAGE int __fastcall Ac_NCDrawScrollbar(TacScrollBar* sb, HWND Handle, HDC DC, const Types::TRect &R, int uDrawFlags, int ThumbPos = 0xffffffff);
extern PACKAGE int __fastcall Ac_NCCalcSize(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_Notify(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_ThumbTrackHorz(TacScrollBar* sbar, HWND Handle, int x, int y);
extern PACKAGE int __fastcall Ac_ThumbTrackVert(TacScrollBar* sbar, HWND Handle, int x, int y);
extern PACKAGE int __fastcall Ac_MouseMove(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_SetCursor(TacScrollWnd* sw, HWND Handle, int &wParam, int &lParam);
extern PACKAGE int __fastcall Ac_StyleChange(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_NCHitTest(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_GetHorzPortion(TacScrollBar* sb, HWND Handle, const Types::TRect &R, int x, int y);
extern PACKAGE int __fastcall Ac_GetVertPortion(TacScrollBar* sb, HWND Handle, const Types::TRect &R, int x, int y);
extern PACKAGE int __fastcall Ac_CalcThumbSize(TacScrollBar* sb, const Types::TRect &R, int &pthumbsize, int &pthumbpos, bool Ext = false);
extern PACKAGE bool __fastcall Ac_IsScrollInfoActive(const tagSCROLLINFO &si);
extern PACKAGE bool __fastcall Ac_IsScrollbarActive(TacScrollBar* sb);
extern PACKAGE int __fastcall Ac_GetHorzScrollPortion(TacScrollBar* sb, HWND Handle, const Types::TRect &R, int x, int y);
extern PACKAGE int __fastcall Ac_GetVertScrollPortion(TacScrollBar* sb, HWND Handle, const Types::TRect &R, int x, int y);
extern PACKAGE void __fastcall Ac_GetRealScrollRect(TacScrollBar* sb, Types::TRect &R);
extern PACKAGE Types::TRect __fastcall RotateRect0(TacScrollBar* sb, Types::TRect &R);
extern PACKAGE void __fastcall SendScrollMessage(HWND Handle, int scrMsg, int scrId, int pos);
extern PACKAGE int __fastcall Ac_NCLButtonDown(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_LButtonUp(TacScrollWnd* sw, HWND Handle, int wParam, int lParam);
extern PACKAGE int __fastcall Ac_Timer(TacScrollWnd* sw, HWND Handle, int wTimerId, int lParam);

}	/* namespace Acsbutils */
using namespace Acsbutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acSBUtils
