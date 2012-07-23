// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sLabel.pas' rev: 6.00

#ifndef sLabelHPP
#define sLabelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sMessages.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
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

namespace Slabel
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsShadowMode { smNone, smCustom, smSkin1 };
#pragma option pop

#pragma option push -b-
enum TsKindType { ktStandard, ktCustom, ktSkin };
#pragma option pop

class DELPHICLASS TsShadow;
class PASCALIMPLEMENTATION TsShadow : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	bool FBuffered;
	int FBlurCount;
	int FDistance;
	Graphics::TColor FColor;
	Controls::TControl* ParentControl;
	TsShadowMode FMode;
	void __fastcall SetBlurCount(const int Value);
	void __fastcall SetDistance(const int Value);
	void __fastcall SetColor(const Graphics::TColor Value);
	void __fastcall SetMode(const TsShadowMode Value);
	
public:
	int sr;
	int sg;
	int sb;
	__fastcall TsShadow(Classes::TComponent* AOwner, Controls::TControl* Control);
	__fastcall virtual ~TsShadow(void);
	__property bool ShadowBuffered = {read=FBuffered, write=FBuffered, default=0};
	
__published:
	__property TsShadowMode Mode = {read=FMode, write=SetMode, default=2};
	__property Graphics::TColor Color = {read=FColor, write=SetColor, default=0};
	__property int BlurCount = {read=FBlurCount, write=SetBlurCount, default=4};
	__property int Distance = {read=FDistance, write=SetDistance, default=1};
};


class DELPHICLASS TsCustomLabel;
class PASCALIMPLEMENTATION TsCustomLabel : public Stdctrls::TCustomLabel 
{
	typedef Stdctrls::TCustomLabel inherited;
	
private:
	Classes::TNotifyEvent FOnMouseLeave;
	Classes::TNotifyEvent FOnMouseEnter;
	AnsiString FSkinSection;
	void __fastcall SetSkinSection(const AnsiString Value);
	
protected:
	virtual Graphics::TFont* __fastcall GetCurrentFont(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TsCustomLabel(Classes::TComponent* AOwner);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall DoDrawText(Types::TRect &Rect, int Flags);
	__property Font ;
	
__published:
	__property Align  = {default=0};
	__property Alignment  = {default=0};
	__property Anchors  = {default=3};
	__property AutoSize  = {default=1};
	__property BiDiMode ;
	__property AnsiString SkinSection = {read=FSkinSection, write=SetSkinSection};
	__property Caption ;
	__property Color  = {default=-2147483643};
	__property Constraints ;
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property FocusControl ;
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowAccelChar  = {default=1};
	__property ShowHint ;
	__property Transparent  = {default=1};
	__property Layout  = {default=0};
	__property Visible  = {default=1};
	__property WordWrap  = {default=0};
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TsCustomLabel(void) { }
	#pragma option pop
	
};


#pragma pack(push, 1)
struct TsClassSkinData
{
	bool CustomColor;
	bool CustomFont;
} ;
#pragma pack(pop)

class DELPHICLASS TsLabel;
class PASCALIMPLEMENTATION TsLabel : public TsCustomLabel 
{
	typedef TsCustomLabel inherited;
	
private:
	bool FUseSkinColor;
	
protected:
	virtual Graphics::TFont* __fastcall GetCurrentFont(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TsLabel(Classes::TComponent* AOwner);
	
__published:
	__property Font ;
	__property bool UseSkinColor = {read=FUseSkinColor, write=FUseSkinColor, default=1};
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TsLabel(void) { }
	#pragma option pop
	
};


class DELPHICLASS TsEditLabel;
class PASCALIMPLEMENTATION TsEditLabel : public TsLabel 
{
	typedef TsLabel inherited;
	
public:
	System::TObject* BoundLabel;
	__fastcall TsEditLabel(Classes::TComponent* AOwner, System::TObject* BoundStruct);
	__fastcall virtual ~TsEditLabel(void);
public:
	#pragma option push -w-inl
	/* TsLabel.Create */ inline __fastcall virtual TsEditLabel(Classes::TComponent* AOwner) : TsLabel(AOwner) { }
	#pragma option pop
	
};


class DELPHICLASS TsWebLabel;
class PASCALIMPLEMENTATION TsWebLabel : public TsLabel 
{
	typedef TsLabel inherited;
	
private:
	Graphics::TFont* FNormalFont;
	void __fastcall SetHoverFont(const Graphics::TFont* Value);
	void __fastcall SetNormalFont(const Graphics::TFont* Value);
	
protected:
	Graphics::TFont* FHoverFont;
	AnsiString FURL;
	Sconst::TsWindowShowMode FShowMode;
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMEraseBkGnd(Messages::TWMMouse &Message);
	virtual Graphics::TFont* __fastcall GetCurrentFont(void);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
public:
	bool MouseAbove;
	__fastcall virtual TsWebLabel(Classes::TComponent* AOwner);
	__fastcall virtual ~TsWebLabel(void);
	virtual void __fastcall Loaded(void);
	
__published:
	__property Graphics::TFont* Font = {read=FNormalFont, write=SetNormalFont};
	__property Cursor  = {default=-21};
	__property Graphics::TFont* HoverFont = {read=FHoverFont, write=SetHoverFont};
	__property Sconst::TsWindowShowMode ShowMode = {read=FShowMode, write=FShowMode, default=10};
	__property AnsiString URL = {read=FURL, write=FURL};
};


class DELPHICLASS TsKind;
class PASCALIMPLEMENTATION TsKind : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Controls::TControl* FOwner;
	TsKindType FKindType;
	Graphics::TColor FColor;
	__fastcall TsKind(Controls::TControl* AOwner);
	void __fastcall SetKindType(const TsKindType Value);
	void __fastcall SetColor(const Graphics::TColor Value);
	
public:
	__fastcall virtual ~TsKind(void);
	
__published:
	__property TsKindType KindType = {read=FKindType, write=SetKindType, default=2};
	__property Graphics::TColor Color = {read=FColor, write=SetColor, default=16777215};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TsKind(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TsLabelFX;
class PASCALIMPLEMENTATION TsLabelFX : public TsCustomLabel 
{
	typedef TsCustomLabel inherited;
	
private:
	Graphics::TBitmap* FMask;
	void *FMaskBits;
	int FMaskBitsSize;
	TsShadow* FShadow;
	bool FNeedInvalidate;
	int OffsTopLeft;
	int OffsRightBottom;
	TsKind* FKind;
	
public:
	__fastcall virtual TsLabelFX(Classes::TComponent* AOwner);
	__fastcall virtual ~TsLabelFX(void);
	DYNAMIC void __fastcall DoDrawText(Types::TRect &Rect, int Flags);
	
__published:
	__property Font ;
	__property TsKind* Kind = {read=FKind, write=FKind};
	__property TsShadow* Shadow = {read=FShadow, write=FShadow};
};


#pragma option push -b-
enum TAlignTo { altLeft, altTop, altBottom, altRight };
#pragma option pop

class DELPHICLASS TsStickyLabel;
class PASCALIMPLEMENTATION TsStickyLabel : public TsLabel 
{
	typedef TsLabel inherited;
	
private:
	Controls::TWinControl* FAttachTo;
	TAlignTo FAlignTo;
	int FGap;
	Classes::TWndMethod FOldWinProc;
	bool FRealigning;
	void __fastcall SetGap(int Value);
	void __fastcall SetAttachTo(Controls::TWinControl* Value);
	void __fastcall SetAlignTo(TAlignTo Value);
	void __fastcall NewWinProc(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TsStickyLabel(Classes::TComponent* AOwner);
	__fastcall virtual ~TsStickyLabel(void);
	void __fastcall Adjust(bool MoveLabel);
	
__published:
	__property Font ;
	__property TAlignTo AlignTo = {read=FAlignTo, write=SetAlignTo, default=0};
	__property Controls::TWinControl* AttachTo = {read=FAttachTo, write=SetAttachTo};
	__property int Gap = {read=FGap, write=SetGap, default=2};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Sconst::TCacheInfo __fastcall GetParentCache(Controls::TControl* Control);

}	/* namespace Slabel */
using namespace Slabel;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sLabel
