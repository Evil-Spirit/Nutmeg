// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sStyleSimply.pas' rev: 6.00

#ifndef sStyleSimplyHPP
#define sStyleSimplyHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <IniFiles.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sstylesimply
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsSkinData;
class PASCALIMPLEMENTATION TsSkinData : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString SkinPath;
	bool Active;
	double Version;
	AnsiString Author;
	AnsiString Description;
	Graphics::TColor Shadow1Color;
	short Shadow1Offset;
	short Shadow1Blur;
	short Shadow1Transparency;
	short ExBorderWidth;
	short ExTitleHeight;
	short ExMaxHeight;
	short ExContentOffs;
	short ExShadowOffs;
	short ExCenterOffs;
	short ExDrawMode;
	Graphics::TColor FXColor;
	Graphics::TColor BorderColor;
	short BISpacing;
	short BIVAlign;
	short BIRightMargin;
	short BILeftMargin;
	short BITopMargin;
	short BIKeepHUE;
	short BICloseGlow;
	short BICloseGlowMargin;
	short BIMaxGlow;
	short BIMaxGlowMargin;
	short BIMinGlow;
	short BIMinGlowMargin;
	__fastcall virtual ~TsSkinData(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TsSkinData(void) : System::TObject() { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TConstantSkinData
{
	short IndexGLobalInfo;
	short ExBorder;
	short IndexTabTop;
	short IndexTabBottom;
	short IndexTabLeft;
	short IndexTabRight;
	short MaskTabTop;
	short MaskTabBottom;
	short MaskTabLeft;
	short MaskTabRight;
	short IndexScrollTop;
	short IndexScrollBottom;
	short IndexScrollLeft;
	short IndexScrollRight;
	short MaskScrollTop;
	short MaskScrollBottom;
	short MaskScrollLeft;
	short MaskScrollRight;
	short IndexBGScrollTop;
	short IndexBGScrollBottom;
	short IndexBGScrollLeft;
	short IndexBGScrollRight;
	short IndexBGHotScrollTop;
	short IndexBGHotScrollBottom;
	short IndexBGHotScrollLeft;
	short IndexBGHotScrollRight;
	short MaskArrowTop;
	short MaskArrowBottom;
	short MaskArrowLeft;
	short MaskArrowRight;
	short IndexSliderVert;
	short IndexSliderHorz;
	short MaskSliderVert;
	short MaskSliderHorz;
	short MaskSliderGlyphVert;
	short MaskSliderGlyphHorz;
	short ScrollSliderBGHorz;
	short ScrollSliderBGHotHorz;
	short ScrollSliderBGVert;
	short ScrollSliderBGHotVert;
	short IndexScrollBar1H;
	short IndexScrollBar1V;
	short IndexScrollBar2H;
	short IndexScrollBar2V;
	short MaskScrollBar1H;
	short MaskScrollBar1V;
	short MaskScrollBar2H;
	short MaskScrollBar2V;
	short BGScrollBar1H;
	short BGScrollBar1V;
	short BGScrollBar2H;
	short BGScrollBar2V;
	short BGHotScrollBar1H;
	short BGHotScrollBar1V;
	short BGHotScrollBar2H;
	short BGHotScrollBar2V;
	short CheckBoxChecked;
	short CheckBoxUnChecked;
	short CheckBoxGrayed;
	short RadioButtonChecked;
	short RadioButtonUnChecked;
	short RadioButtonGrayed;
	short SmallCheckBoxChecked;
	short SmallCheckBoxUnChecked;
	short SmallCheckBoxGrayed;
	int ComboBtnIndex;
	int ComboBtnBorder;
	int ComboBtnBG;
	int ComboBtnBGHot;
	int ComboGlyph;
} ;
#pragma pack(pop)

typedef DynamicArray<Classes::TComponent* >  sStyleSimply__2;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString GlobalSectionName;
extern PACKAGE Graphics::TIcon* AppIcon;
extern PACKAGE Graphics::TIcon* AppIconLarge;
extern PACKAGE bool aSkinChanging;
extern PACKAGE DynamicArray<Classes::TComponent* >  HookedComponents;
extern PACKAGE void __fastcall CopyExForms(Classes::TComponent* SkinManager);
extern PACKAGE void __fastcall LockForms(Classes::TComponent* SkinManager);
extern PACKAGE void __fastcall UnLockForms(Classes::TComponent* SkinManager, bool Repaint = true);
extern PACKAGE void __fastcall AppBroadCastS(void *Message);
extern PACKAGE void __fastcall SendToHooked(void *Message);
extern PACKAGE void __fastcall IntSkinForm(Forms::TCustomForm* Form);
extern PACKAGE void __fastcall IntUnSkinForm(Forms::TCustomForm* Form);

}	/* namespace Sstylesimply */
using namespace Sstylesimply;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sStyleSimply
