// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sAlphaGraph.pas' rev: 6.00

#ifndef sAlphaGraphHPP
#define sAlphaGraphHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sCommonData.hpp>	// Pascal unit
#include <sMaskData.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
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

namespace Salphagraph
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsCorner { scLeftTop, scLeftBottom, scRightTop, scRightBottom };
#pragma option pop

typedef Set<TsCorner, scLeftTop, scRightBottom>  TsCorners;

class DELPHICLASS TacFast32;
class PASCALIMPLEMENTATION TacFast32 : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Graphics::TBitmap* FBitmap;
	int FWidth;
	int FHeight;
	int FDelta;
	Sconst::TsColor __fastcall GetPixel(int X, int Y);
	void __fastcall SetPixel(int X, int Y, const Sconst::TsColor Value);
	
public:
	int FStart;
	int FLength;
	int DstStart;
	bool __fastcall Attach(Graphics::TBitmap* Bmp);
	void __fastcall FillBitmap(Graphics::TColor &Color);
	void __fastcall FillRect(const Types::TRect &R, Graphics::TColor &Color);
	__property int Width = {read=FWidth, nodefault};
	__property int Height = {read=FHeight, nodefault};
	__property Sconst::TsColor Pixels[int X][int Y] = {read=GetPixel, write=SetPixel/*, default*/};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TacFast32(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TacFast32(void) { }
	#pragma option pop
	
};


class DELPHICLASS TacFastSum32;
class PASCALIMPLEMENTATION TacFastSum32 : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Graphics::TBitmap* FBmpSrc;
	Graphics::TBitmap* FBmpDst;
	int FWidthDst;
	int FHeightDst;
	int FStartSrc;
	int FStartDst;
	int FDeltaSrc;
	int FDeltaDst;
	
public:
	Byte Alpha;
	int DstX1;
	int DstY1;
	int DstX2;
	int DstY2;
	int SrcX1;
	int SrcY1;
	int SrcX2;
	int SrcY2;
	void __fastcall BlendBitmaps(void);
	void __fastcall BlendBitmapsRect(void);
	bool __fastcall Attach(Graphics::TBitmap* BmpSrc, Graphics::TBitmap* BmpDst);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TacFastSum32(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TacFastSum32(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall FillTransPixels32(const Graphics::TBitmap* DstBmp, const Graphics::TBitmap* SrcBmp, const Types::TRect &DstRect, const Types::TPoint &SrcPoint, int MaskIndex = 0xffffffff, System::TObject* SkinManager = (System::TObject*)(0x0), unsigned MaskPos = (unsigned)(0xd));
extern PACKAGE void __fastcall WriteText32(const Graphics::TBitmap* Bmp, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags, int SkinIndex, bool Hot, System::TObject* SkinManager = (System::TObject*)(0x0), bool IsAnsi = false);
extern PACKAGE Graphics::TColor __fastcall CorrectColor32(Graphics::TColor Color);
extern PACKAGE void __fastcall FillDCBorder32(const Graphics::TBitmap* Bmp, const Types::TRect &aRect, const int wl, const int wt, const int wr, const int wb, const Graphics::TColor Color);
extern PACKAGE void __fastcall BlendColorRect(Graphics::TBitmap* Bmp, const Types::TRect &R, Sconst::TPercent Transparency, Graphics::TColor Color);
extern PACKAGE Graphics::TColor __fastcall SwapColor(Graphics::TColor Color);
extern PACKAGE Graphics::TColor __fastcall SwapRedBlue(Graphics::TColor Color);
extern PACKAGE void __fastcall FillRect32(const Graphics::TBitmap* Bmp, const Types::TRect &R, Graphics::TColor Color);
extern PACKAGE void __fastcall FillAlphaRect(const Graphics::TBitmap* Bmp, const Types::TRect &R, Byte Value, bool SkipFuchsia = false);
extern PACKAGE void __fastcall BmpDisabledKind(Graphics::TBitmap* Bmp, Sconst::TsDisabledKind DisabledKind, Controls::TControl* Parent, const Sconst::TCacheInfo &CI, const Types::TPoint &Offset);
extern PACKAGE void __fastcall DrawSmallSkinRect(Graphics::TBitmap* Bmp, const Types::TRect &R, bool Filling, const Sconst::TCacheInfo &ci, const Smaskdata::TsMaskData &MaskData, int State);
extern PACKAGE void __fastcall DrawSkinRect(const Graphics::TBitmap* Bmp, const Types::TRect &R, const bool Filling, const Sconst::TCacheInfo &ci, const Smaskdata::TsMaskData &MaskData, const int State, const bool UpdateCorners, System::TObject* SkinManager = (System::TObject*)(0x0));
extern PACKAGE void __fastcall CopyMasterRect(const Types::TRect &R1, const Types::TRect &R2, Graphics::TBitmap* Bmp, const Sconst::TCacheInfo &CI, const Smaskdata::TsMaskData &MaskData);
extern PACKAGE void __fastcall CopyMasterRectA(const Types::TRect &R1, const Types::TRect &R2, Graphics::TBitmap* Bmp, const Sconst::TCacheInfo &CI, const Smaskdata::TsMaskData &MaskData);
extern PACKAGE void __fastcall DrawSkinGlyph(Graphics::TBitmap* Bmp, const Types::TPoint &P, int State, int AddedTransparency, const Smaskdata::TsMaskData &MaskData, const Sconst::TCacheInfo &CI);
extern PACKAGE void __fastcall BlendGlyphByMask(const Types::TRect &R1, const Types::TRect &R2, Graphics::TBitmap* Bmp1, Graphics::TBitmap* Bmp2, Graphics::TColor TransColor, int AddedTransparency, const Smaskdata::TsMaskData &MaskData);
extern PACKAGE void __fastcall UpdateCorners(Scommondata::TsCommonData* SkinData, int State)/* overload */;
extern PACKAGE void __fastcall UpdateCorners(Scommondata::TsCommonData* SkinData, int State, TsCorners Corners)/* overload */;
extern PACKAGE void __fastcall FillLongword(void *X, int Count, unsigned Value);

}	/* namespace Salphagraph */
using namespace Salphagraph;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sAlphaGraph
