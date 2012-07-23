// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sHintManager.pas' rev: 6.00

#ifndef sHintManagerHPP
#define sHintManagerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sHtmlParse.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
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

namespace Shintmanager
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsMousePosition { mpLeftTop, mpLeftBottom, mpRightTop, mpRightBottom };
#pragma option pop

#pragma option push -b-
enum TsHintsEffectsMode { hmNone, hmSystem, hmCustom };
#pragma option pop

class DELPHICLASS TsHintKind;
class DELPHICLASS TsHintManager;
typedef void __fastcall (__closure *TacShowHintEvent)(AnsiString &HintStr, bool &CanShow, Forms::THintInfo &HintInfo, Forms::TFrame* &Frame);

class DELPHICLASS TsCustomHintWindow;
class PASCALIMPLEMENTATION TsCustomHintWindow : public Controls::THintWindow 
{
	typedef Controls::THintWindow inherited;
	
private:
	#pragma pack(push, 1)
	Types::TPoint FHintLocation;
	#pragma pack(pop)
	
	HIDESBASE MESSAGE void __fastcall WMEraseBkGND(Messages::TWMPaint &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TWMPaint &Message);
	void __fastcall PrepareMask(void);
	
protected:
	int SkinIndex;
	int BorderIndex;
	int BGIndex;
	HRGN rgn;
	int dx;
	int dy;
	TsMousePosition FMousePos;
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual Types::TPoint __fastcall GetMousePosition();
	DYNAMIC Types::TRect __fastcall MainRect();
	int __fastcall ShadowTransparency(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	int __fastcall SkinMargin(Byte Border);
	
public:
	Graphics::TBitmap* BodyBmp;
	Graphics::TBitmap* MaskBmp;
	Graphics::TBitmap* ScreenBmp;
	Graphics::TBitmap* AlphaBmp;
	DYNAMIC Graphics::TBitmap* __fastcall GetMask(void);
	DYNAMIC Graphics::TBitmap* __fastcall GetBody(void);
	virtual void __fastcall PaintShadow(Graphics::TBitmap* Bmp = (Graphics::TBitmap*)(0x0));
	__property Types::TPoint HintLocation = {read=FHintLocation, write=FHintLocation};
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall PaintBG(Graphics::TBitmap* Bmp, const Types::TRect &aRect);
	DYNAMIC void __fastcall PaintBorder(Graphics::TBitmap* Bmp);
	DYNAMIC void __fastcall TextOut(Graphics::TBitmap* Bmp);
	virtual Types::TRect __fastcall CalcHintRect(int MaxWidth, const AnsiString AHint, void * AData);
	virtual void __fastcall ActivateHint(const Types::TRect &Rect, const AnsiString AHint);
	__fastcall virtual TsCustomHintWindow(Classes::TComponent* AOwner);
	__fastcall virtual ~TsCustomHintWindow(void);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCustomHintWindow(HWND ParentWindow) : Controls::THintWindow(ParentWindow) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsHintManager : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FPauseHide;
	bool FHTMLMode;
	Sconst::TsHintsPredefinitions FPredefinitions;
	TacShowHintEvent FOnShowHint;
	TsHintKind* FHintKind;
	TsMousePosition FDefaultMousePos;
	bool FAnimated;
	#pragma pack(push, 1)
	Types::TPoint FHintPos;
	#pragma pack(pop)
	
	AnsiString FSkinSection;
	bool FUseSkinData;
	void __fastcall SetNewStyle(Sconst::TsHintStyle hs);
	void __fastcall SetPredefinitions(const Sconst::TsHintsPredefinitions Value);
	bool __fastcall GetAnimated(void);
	void __fastcall SetSkinData(const bool Value);
	void __fastcall SetPauseHide(const int Value);
	
public:
	TsCustomHintWindow* FTempHint;
	Graphics::TBitmap* FCacheBmp;
	void __fastcall OnShowHintApp(AnsiString &HintStr, bool &CanShow, Forms::THintInfo &HintInfo);
	__fastcall virtual TsHintManager(Classes::TComponent* AOwner);
	__fastcall virtual ~TsHintManager(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall AfterConstruction(void);
	void __fastcall Invalidate(void);
	void __fastcall PaintBG(Graphics::TBitmap* BGBmp, const Types::TRect &R, const Sconst::TCacheInfo &ci);
	void __fastcall ShowHint(Controls::TControl* TheControl, AnsiString HintText);
	void __fastcall HideHint(void);
	void __fastcall UpdateProperties(void);
	bool __fastcall Skinned(void);
	
__published:
	__property TacShowHintEvent OnShowHint = {read=FOnShowHint, write=FOnShowHint};
	__property bool Animated = {read=GetAnimated, write=FAnimated, default=1};
	__property TsMousePosition DefaultMousePos = {read=FDefaultMousePos, write=FDefaultMousePos, default=0};
	__property TsHintKind* HintKind = {read=FHintKind, write=FHintKind};
	__property bool HTMLMode = {read=FHTMLMode, write=FHTMLMode, default=0};
	__property int PauseHide = {read=FPauseHide, write=SetPauseHide, default=5000};
	__property Sconst::TsHintsPredefinitions Predefinitions = {read=FPredefinitions, write=SetPredefinitions, default=3};
	__property AnsiString SkinSection = {read=FSkinSection, write=FSkinSection};
	__property bool UseSkinData = {read=FUseSkinData, write=SetSkinData, default=0};
};


class PASCALIMPLEMENTATION TsHintKind : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TsHintManager* FOwner;
	bool FShadowEnabled;
	int FMarginV;
	int FTexturePercent;
	int FShadowBlur;
	int FTransparency;
	int FGradientPercent;
	int FMarginH;
	int FExOffset;
	int FShadowTransparency;
	int FShadowOffset;
	int FBevelWidth;
	int FMaxWidth;
	int FRadius;
	int FBevel;
	AnsiString FGradientData;
	AnsiString FTextureFile;
	Graphics::TColor FColorBorderTop;
	Graphics::TColor FColorBorderBottom;
	Graphics::TColor FColor;
	Graphics::TColor FShadowColor;
	Graphics::TFont* FFont;
	Graphics::TPicture* FTexture;
	Sconst::TsHintStyle FStyle;
	int FBlur;
	void __fastcall SetFont(const Graphics::TFont* Value);
	void __fastcall SetStyle(const Sconst::TsHintStyle Value);
	void __fastcall SetTexture(const Graphics::TPicture* Value);
	bool __fastcall GetShadowEnabled(void);
	int __fastcall GetShadowBlur(void);
	int __fastcall GetShadowOffset(void);
	int __fastcall GetShadowTransparency(void);
	void __fastcall SetBlur(const int Value);
	void __fastcall SetShadowColor(const Graphics::TColor Value);
	
public:
	__fastcall TsHintKind(TsHintManager* AOwner);
	__fastcall virtual ~TsHintKind(void);
	
__published:
	__property Sconst::TsHintStyle Style = {read=FStyle, write=SetStyle, default=2};
	__property int Radius = {read=FRadius, write=FRadius, default=20};
	__property int BevelWidth = {read=FBevelWidth, write=FBevelWidth, default=1};
	__property int Blur = {read=FBlur, write=SetBlur, default=0};
	__property int ExOffset = {read=FExOffset, write=FExOffset, default=32};
	__property AnsiString GradientData = {read=FGradientData, write=FGradientData};
	__property Graphics::TPicture* Texture = {read=FTexture, write=SetTexture};
	__property AnsiString TextureFile = {read=FTextureFile, write=FTextureFile};
	__property int GradientPercent = {read=FGradientPercent, write=FGradientPercent, default=0};
	__property int TexturePercent = {read=FTexturePercent, write=FTexturePercent, default=0};
	__property int Bevel = {read=FBevel, write=FBevel, nodefault};
	__property Graphics::TColor Color = {read=FColor, write=FColor, nodefault};
	__property Graphics::TColor ColorBorderTop = {read=FColorBorderTop, write=FColorBorderTop, nodefault};
	__property Graphics::TColor ColorBorderBottom = {read=FColorBorderBottom, write=FColorBorderBottom, nodefault};
	__property int Transparency = {read=FTransparency, write=FTransparency, nodefault};
	__property int ShadowBlur = {read=GetShadowBlur, write=FShadowBlur, nodefault};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=0};
	__property bool ShadowEnabled = {read=GetShadowEnabled, write=FShadowEnabled, nodefault};
	__property int ShadowOffset = {read=GetShadowOffset, write=FShadowOffset, nodefault};
	__property int ShadowTransparency = {read=GetShadowTransparency, write=FShadowTransparency, nodefault};
	__property int MarginH = {read=FMarginH, write=FMarginH, default=15};
	__property int MarginV = {read=FMarginV, write=FMarginV, default=10};
	__property int MaxWidth = {read=FMaxWidth, write=FMaxWidth, default=200};
	__property Graphics::TFont* Font = {read=FFont, write=SetFont};
};


class DELPHICLASS TsSimplyHintWindow;
class PASCALIMPLEMENTATION TsSimplyHintWindow : public TsCustomHintWindow 
{
	typedef TsCustomHintWindow inherited;
	
public:
	virtual void __fastcall PaintShadow(Graphics::TBitmap* Bmp = (Graphics::TBitmap*)(0x0));
	DYNAMIC Graphics::TBitmap* __fastcall GetMask(void);
	DYNAMIC Graphics::TBitmap* __fastcall GetBody(void);
	virtual Types::TPoint __fastcall GetMousePosition();
	DYNAMIC void __fastcall PaintBorder(Graphics::TBitmap* Bmp);
public:
	#pragma option push -w-inl
	/* TsCustomHintWindow.Create */ inline __fastcall virtual TsSimplyHintWindow(Classes::TComponent* AOwner) : TsCustomHintWindow(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsCustomHintWindow.Destroy */ inline __fastcall virtual ~TsSimplyHintWindow(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsSimplyHintWindow(HWND ParentWindow) : TsCustomHintWindow(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsComicsHintWindow;
class PASCALIMPLEMENTATION TsComicsHintWindow : public TsCustomHintWindow 
{
	typedef TsCustomHintWindow inherited;
	
public:
	DYNAMIC Types::TRect __fastcall MainRect();
	virtual void __fastcall PaintShadow(Graphics::TBitmap* Bmp = (Graphics::TBitmap*)(0x0));
	DYNAMIC Graphics::TBitmap* __fastcall GetMask(void);
	Types::TPoint __fastcall GetArrowPosition();
	virtual Types::TRect __fastcall CalcHintRect(int MaxWidth, const AnsiString AHint, void * AData);
	DYNAMIC Graphics::TBitmap* __fastcall GetBody(void);
	DYNAMIC void __fastcall PaintBorder(Graphics::TBitmap* Bmp);
public:
	#pragma option push -w-inl
	/* TsCustomHintWindow.Create */ inline __fastcall virtual TsComicsHintWindow(Classes::TComponent* AOwner) : TsCustomHintWindow(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsCustomHintWindow.Destroy */ inline __fastcall virtual ~TsComicsHintWindow(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsComicsHintWindow(HWND ParentWindow) : TsCustomHintWindow(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsEllipseHintWindow;
class PASCALIMPLEMENTATION TsEllipseHintWindow : public TsCustomHintWindow 
{
	typedef TsCustomHintWindow inherited;
	
public:
	Types::TPoint __fastcall GetArrowPosition();
	DYNAMIC Graphics::TBitmap* __fastcall GetBody(void);
	DYNAMIC Graphics::TBitmap* __fastcall GetMask(void);
	DYNAMIC Types::TRect __fastcall MainRect();
	virtual void __fastcall PaintShadow(Graphics::TBitmap* Bmp = (Graphics::TBitmap*)(0x0));
	virtual Types::TRect __fastcall CalcHintRect(int MaxWidth, const AnsiString AHint, void * AData);
	DYNAMIC void __fastcall PaintBorder(Graphics::TBitmap* Bmp);
public:
	#pragma option push -w-inl
	/* TsCustomHintWindow.Create */ inline __fastcall virtual TsEllipseHintWindow(Classes::TComponent* AOwner) : TsCustomHintWindow(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsCustomHintWindow.Destroy */ inline __fastcall virtual ~TsEllipseHintWindow(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsEllipseHintWindow(HWND ParentWindow) : TsCustomHintWindow(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsBalloonHintWindow;
class PASCALIMPLEMENTATION TsBalloonHintWindow : public TsCustomHintWindow 
{
	typedef TsCustomHintWindow inherited;
	
public:
	int BalloonCount;
	int Divid;
	virtual void __fastcall PaintShadow(Graphics::TBitmap* Bmp = (Graphics::TBitmap*)(0x0));
	DYNAMIC Graphics::TBitmap* __fastcall GetMask(void);
	Graphics::TBitmap* __fastcall GetCustMask(bool Shadow);
	DYNAMIC Graphics::TBitmap* __fastcall GetBody(void);
	Types::TPoint __fastcall GetArrowPosition();
	virtual Types::TRect __fastcall CalcHintRect(int MaxWidth, const AnsiString AHint, void * AData);
	__fastcall virtual TsBalloonHintWindow(Classes::TComponent* AOwner);
	DYNAMIC Types::TRect __fastcall MainRect();
	DYNAMIC void __fastcall PaintBorder(Graphics::TBitmap* Bmp);
public:
	#pragma option push -w-inl
	/* TsCustomHintWindow.Destroy */ inline __fastcall virtual ~TsBalloonHintWindow(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsBalloonHintWindow(HWND ParentWindow) : TsCustomHintWindow(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define DefStyle (Sconst::TsHintStyle)(2)
static const Byte DefAnimationTime = 0xfa;
extern PACKAGE Sconst::TsHintsPredefinitions asHintsPredefinitions[9];
extern PACKAGE TsHintManager* Manager;
extern PACKAGE bool acHintsInEditor;

}	/* namespace Shintmanager */
using namespace Shintmanager;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sHintManager
