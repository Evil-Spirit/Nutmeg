// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sGraphUtils.pas' rev: 6.00

#ifndef sGraphUtilsHPP
#define sGraphUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sCommonData.hpp>	// Pascal unit
#include <sMaskData.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
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

namespace Sgraphutils
{
//-- type declarations -------------------------------------------------------
struct TsHSV
{
	int h;
	double s;
	double v;
} ;

#pragma option push -b-
enum TFilterType { ftBox, ftTriangle, ftHermite, ftBell, ftSpline, ftLanczos3, ftMitchell };
#pragma option pop

typedef Byte *TByteArrays[1000001];

typedef Sysutils::PByteArray *PByteArrays;

typedef Shortint TKernelSize;

#pragma pack(push, 4)
struct TKernel
{
	TKernelSize Size;
	float Weights[201];
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxKernelSize = 0x64;
extern PACKAGE unsigned User32Lib;
extern PACKAGE bool __stdcall (*UpdateLayeredWindow)(unsigned Handle, HDC hdcDest, Types::PPoint pptDst, Types::PSize _psize, HDC hdcSrc, Types::PPoint pptSrc, unsigned crKey, Windows::PBlendFunction pblend, unsigned dwFlags);
extern PACKAGE bool __stdcall (*SetLayeredWindowAttributes)(unsigned Hwnd, unsigned crKey, Byte bAlpha, unsigned dwFlags);
extern PACKAGE void __fastcall DrawColorArrow(Graphics::TBitmap* Bmp, Graphics::TColor Color);
extern PACKAGE int __fastcall CheckWidth(System::TObject* SkinManager);
extern PACKAGE int __fastcall CheckHeight(System::TObject* SkinManager);
extern PACKAGE void __fastcall acDrawCheck(const Types::TRect &R, Stdctrls::TCheckBoxState AState, bool AEnabled, Graphics::TBitmap* Bmp, const Sconst::TCacheInfo &CI, System::TObject* SkinManager);
extern PACKAGE bool __fastcall acLayered(void);
extern PACKAGE int __fastcall SwapInteger(const int i);
extern PACKAGE Graphics::TColor __fastcall ChangeBrightness(Graphics::TColor Color, int Delta);
extern PACKAGE Graphics::TColor __fastcall ChangeSaturation(Graphics::TColor Color, int Delta)/* overload */;
extern PACKAGE Sconst::TsColor_ __fastcall ChangeSaturation(int Delta, Sconst::TsColor_ Color)/* overload */;
extern PACKAGE Sconst::TsColor __fastcall Hsv2Rgb(double h, double s, double v);
extern PACKAGE TsHSV __fastcall Rgb2Hsv(Sconst::TsColor C);
extern PACKAGE Sconst::TsColor_ __fastcall ChangeHue(int Delta, Sconst::TsColor_ C)/* overload */;
extern PACKAGE Graphics::TColor __fastcall ChangeHue(int Delta, Graphics::TColor Color)/* overload */;
extern PACKAGE void __fastcall HSVtoRGB(const double H, const double S, const double V, double &R, double &G, double &B);
extern PACKAGE void __fastcall RGBToHSV(const double R, const double G, const double B, double &H, double &S, double &V);
extern PACKAGE void __fastcall GetRgnFromBmp(HRGN &rgn, Graphics::TBitmap* MaskBmp, Graphics::TColor TransColor);
extern PACKAGE bool __fastcall GetBGInfo(const Sconst::PacBGInfo BGInfo, const unsigned Handle, bool PleaseDraw = false)/* overload */;
extern PACKAGE Sconst::TCacheInfo __fastcall BGInfoToCI(const Sconst::PacBGInfo BGInfo);
extern PACKAGE bool __fastcall GetBGInfo(const Sconst::PacBGInfo BGInfo, const Controls::TControl* Control, bool PleaseDraw = false)/* overload */;
extern PACKAGE void __fastcall AddRgnBmp(Sconst::TAOR &AOR, Graphics::TBitmap* MaskBmp, Sconst::TsColor TransColor);
extern PACKAGE void __fastcall AddRgn(Sconst::TAOR &AOR, int Width, const Smaskdata::TsMaskData &MaskData, int VertOffset, bool Bottom);
extern PACKAGE HRGN __fastcall GetRgnForMask(int MaskIndex, int Width, int Height, System::TObject* SkinManager);
extern PACKAGE void __fastcall CopyImage(Graphics::TBitmap* Glyph, Imglist::TCustomImageList* ImageList, int Index);
extern PACKAGE void __fastcall PaintItemBG(int SkinIndex, const AnsiString SkinSection, const Sconst::TCacheInfo &ci, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, System::TObject* SkinManager = (System::TObject*)(0x0), int TextureIndex = 0xffffffff, int HotTextureIndex = 0xffffffff, Graphics::TColor CustomColor = (Graphics::TColor)(0xff00ff))/* overload */;
extern PACKAGE void __fastcall PaintItemBG(Scommondata::TsCommonData* SkinData, const Sconst::TCacheInfo &ci, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, int OffsetX = 0x0, int OffsetY = 0x0)/* overload */;
extern PACKAGE void __fastcall PaintItemBGFast(int SkinIndex, int BGIndex, int BGHotIndex, const AnsiString SkinSection, const Sconst::TCacheInfo &ci, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, System::TObject* SkinManager = (System::TObject*)(0x0));
extern PACKAGE void __fastcall PaintItem(int SkinIndex, const AnsiString SkinSection, const Sconst::TCacheInfo &ci, bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, HDC DC, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE void __fastcall PaintItem(int SkinIndex, const AnsiString SkinSection, const Sconst::TCacheInfo &ci, bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, System::TObject* SkinManager = (System::TObject*)(0x0), int BGIndex = 0xffffffff, int BGHotIndex = 0xffffffff)/* overload */;
extern PACKAGE void __fastcall PaintItemFast(int SkinIndex, int MaskIndex, int BGIndex, int BGHotIndex, const AnsiString SkinSection, Sconst::TCacheInfo &ci, bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE void __fastcall PaintSmallItem(int SkinIndex, const AnsiString SkinSection, const Sconst::TCacheInfo &ci, bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE int __fastcall PaintSection(const Graphics::TBitmap* Bmp, AnsiString Section, const AnsiString SecondSection, const int State, const System::TObject* Manager, const Types::TPoint &ParentOffset, const Graphics::TColor BGColor, HDC ParentDC = (HDC)(0x0));
extern PACKAGE void __fastcall PaintItem(Scommondata::TsCommonData* SkinData, const Sconst::TCacheInfo &ci, bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, Graphics::TBitmap* ItemBmp, bool UpdateCorners, int OffsetX = 0x0, int OffsetY = 0x0)/* overload */;
extern PACKAGE void __fastcall PaintSkinControl(const Scommondata::TsCommonData* SkinData, const Controls::TControl* Parent, const bool Filling, int State, const Types::TRect &R, const Types::TPoint &pP, const Graphics::TBitmap* ItemBmp, const bool UpdateCorners, const int OffsetX = 0x0, const int OffsetY = 0x0);
extern PACKAGE void __fastcall CopyChannel32(const Graphics::TBitmap* DstBmp, const Graphics::TBitmap* SrcBmp, const int Channel);
extern PACKAGE void __fastcall CopyChannel(const Graphics::TBitmap* Bmp32, const Graphics::TBitmap* Bmp8, const int Channel, const bool From32To8);
extern PACKAGE void __fastcall PaintControlByTemplate(const Graphics::TBitmap* DstBmp, const Graphics::TBitmap* SrcBmp, const Types::TRect &DstRect, const Types::TRect &SrcRect, const Types::TRect &BorderWidths, const Types::TRect &BorderMaxWidths, const Types::TRect &DrawModes, const bool StretchCenter, bool FillCenter = true);
extern PACKAGE void __fastcall DrawGlyphEx(Graphics::TBitmap* Glyph, Graphics::TBitmap* DstBmp, const Types::TRect &R, int NumGlyphs, bool Enabled, Sconst::TsDisabledGlyphKind DisabledGlyphKind, int State, int Blend, bool Down = false, bool Reflected = false);
extern PACKAGE void __fastcall FillDC(HDC DC, const Types::TRect &aRect, const Graphics::TColor Color);
extern PACKAGE void __fastcall FillDCBorder(const HDC DC, const Types::TRect &aRect, const int wl, const int wt, const int wr, const int wb, const Graphics::TColor Color);
extern PACKAGE void __fastcall BitBltBorder(const HDC DestDC, const int X, const int Y, const int Width, const int Height, const HDC SrcDC, const int XSrc, const int YSrc, const int BorderWidth);
extern PACKAGE void __fastcall ExcludeControls(const HDC DC, const Controls::TWinControl* Ctrl, const Sconst::TacCtrlType CtrlType, const int OffsetX, const int OffsetY);
extern PACKAGE void __fastcall GrayScale(Graphics::TBitmap* Bmp);
extern PACKAGE void __fastcall GrayScaleTrans(Graphics::TBitmap* Bmp, const Sconst::TsColor TransColor);
extern PACKAGE void __fastcall ChangeBmpHUE(const Graphics::TBitmap* Bmp, const int Value);
extern PACKAGE void __fastcall ChangeBmpSaturation(const Graphics::TBitmap* Bmp, const int Value);
extern PACKAGE AnsiString __fastcall CutText(Graphics::TCanvas* Canvas, const AnsiString Text, int MaxLength);
extern PACKAGE void __fastcall WriteText(Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags);
extern PACKAGE void __fastcall WriteTextOnDC(HDC DC, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags);
extern PACKAGE int __fastcall acDrawText(HDC hDC, const AnsiString Text, Types::TRect &lpRect, unsigned uFormat);
extern PACKAGE int __fastcall acTextWidth(const Graphics::TCanvas* Canvas, const AnsiString Text);
extern PACKAGE int __fastcall acTextHeight(const Graphics::TCanvas* Canvas, const AnsiString Text);
extern PACKAGE tagSIZE __fastcall acTextExtent(const Graphics::TCanvas* Canvas, const AnsiString Text);
extern PACKAGE void __fastcall acTextRect(const Graphics::TCanvas* Canvas, const Types::TRect &Rect, int X, int Y, const AnsiString Text);
extern PACKAGE BOOL __fastcall acGetTextExtent(const HDC DC, const AnsiString Str, tagSIZE &Size);
extern PACKAGE void __fastcall acDrawGlowForText(const Graphics::TBitmap* DstBmp, char * Text, const Types::TRect &aRect, unsigned Flags, unsigned Side, int BlurSize, Graphics::TColor Color, Graphics::TBitmap* &MaskBmp);
extern PACKAGE void __fastcall Blur8(Graphics::TBitmap* theBitmap, double radius);
extern PACKAGE void __fastcall acWriteTextEx(const Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags, Scommondata::TsCommonData* SkinData, bool Hot, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE void __fastcall acWriteTextEx(const Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags, int SkinIndex, bool Hot, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE void __fastcall acWriteText(const Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags);
extern PACKAGE void __fastcall WriteTextEx(const Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags, int SkinIndex, bool Hot, System::TObject* SkinManager = (System::TObject*)(0x0))/* overload */;
extern PACKAGE void __fastcall WriteTextEx(const Graphics::TCanvas* Canvas, char * Text, bool Enabled, Types::TRect &aRect, unsigned Flags, Scommondata::TsCommonData* SkinData, bool Hot)/* overload */;
extern PACKAGE void __fastcall FadeRect(Graphics::TCanvas* CanvasSrc, const Types::TRect &RSrc, HDC CanvasDst, const Types::TPoint &PDst, int Transparency, Graphics::TColor Color, int Blur, Sconst::TsShadowingShape Shape)/* overload */;
extern PACKAGE void __fastcall FadeRect(Graphics::TCanvas* CanvasSrc, const Types::TRect &RSrc, HDC CanvasDst, const Types::TPoint &PDst, int Transparency, Graphics::TColor Color, int Blur, Sconst::TsShadowingShape Shape, int Radius)/* overload */;
extern PACKAGE void __fastcall FadeBmp(Graphics::TBitmap* FadedBmp, const Types::TRect &aRect, int Transparency, Sconst::TsColor Color, int Blur, int Radius);
extern PACKAGE void __fastcall BlendTransRectangle(Graphics::TBitmap* Dst, int X, int Y, Graphics::TBitmap* Src, const Types::TRect &aRect, double Blend, Graphics::TColor TransColor = (Graphics::TColor)(0xff00ff));
extern PACKAGE void __fastcall BlendTransBitmap(Graphics::TBitmap* Bmp, double Blend, Sconst::TsColor Color);
extern PACKAGE void __fastcall BlendBmpByMask(Graphics::TBitmap* SrcBmp, Graphics::TBitmap* MskBmp, Sconst::TsColor BlendColor);
extern PACKAGE void __fastcall SumBitmaps(Graphics::TBitmap* SrcBmp, Graphics::TBitmap* MskBmp, Sconst::TsColor Color);
extern PACKAGE void __fastcall SumBmpRect(const Graphics::TBitmap* DstBmp, const Graphics::TBitmap* SrcBmp, const Byte AlphaValue, const Types::TRect &SrcRect, const Types::TPoint &DstPoint);
extern PACKAGE void __fastcall CopyByMask(const Types::TRect &R1, const Types::TRect &R2, const Graphics::TBitmap* Bmp1, const Graphics::TBitmap* Bmp2, const Sconst::TCacheInfo &CI, const bool UpdateTrans)/* overload */;
extern PACKAGE void __fastcall CopyBmp32(const Types::TRect &R1, const Types::TRect &R2, const Graphics::TBitmap* Bmp1, const Graphics::TBitmap* Bmp2, const Sconst::TCacheInfo &CI, const bool UpdateTrans, const Graphics::TColor GrayedColor, const int Blend, const bool Reflected);
extern PACKAGE void __fastcall CopyByMask(const Types::TRect &R1, const Types::TRect &R2, const Graphics::TBitmap* Bmp1, const Graphics::TBitmap* Bmp2, const Sconst::TCacheInfo &CI, const bool UpdateTrans, const Smaskdata::TsMaskData &MaskData)/* overload */;
extern PACKAGE void __fastcall CopyTransBitmaps(Graphics::TBitmap* DstBmp, Graphics::TBitmap* SrcBmp, int X, int Y, Sconst::TsColor TransColor);
extern PACKAGE void __fastcall CopyTransRect(Graphics::TBitmap* DstBmp, Graphics::TBitmap* SrcBmp, int X, int Y, const Types::TRect &SrcRect, Graphics::TColor TransColor, const Sconst::TCacheInfo &CI, bool UpdateTrans);
extern PACKAGE void __fastcall CopyTransRectA(Graphics::TBitmap* DstBmp, Graphics::TBitmap* SrcBmp, int X, int Y, const Types::TRect &SrcRect, Graphics::TColor TransColor, const Sconst::TCacheInfo &CI);
extern PACKAGE void __fastcall SumBitmapsByMask(Graphics::TBitmap* &ResultBmp, Graphics::TBitmap* &Src1, Graphics::TBitmap* &Src2, Graphics::TBitmap* MskBmp, Word Percent = (Word)(0x0));
extern PACKAGE void __fastcall SumByMask(Graphics::TBitmap* &Src1, Graphics::TBitmap* &Src2, Graphics::TBitmap* &MskBmp, const Types::TRect &aRect);
extern PACKAGE void __fastcall SumByMaskWith32(const Graphics::TBitmap* Src1, const Graphics::TBitmap* Src2, const Graphics::TBitmap* MskBmp, const Types::TRect &aRect);
extern PACKAGE Graphics::TBitmap* __fastcall MakeRotated90(Graphics::TBitmap* &Bmp, bool CW, bool KillSource = true);
extern PACKAGE Graphics::TBitmap* __fastcall CreateBmpLike(const Graphics::TBitmap* Bmp);
extern PACKAGE Graphics::TBitmap* __fastcall CreateBmp24(const int Width, const int Height);
extern PACKAGE Graphics::TBitmap* __fastcall CreateBmp32(const int Width, const int Height);
extern PACKAGE Graphics::TColor __fastcall ChangeColor(Graphics::TColor ColorBegin, Graphics::TColor ColorEnd, double i);
extern PACKAGE Sconst::TsColor __fastcall AverageColor(Sconst::TsColor ColorBegin, Sconst::TsColor ColorEnd)/* overload */;
extern PACKAGE Graphics::TColor __fastcall AverageColor(Graphics::TColor ColorBegin, Graphics::TColor ColorEnd)/* overload */;
extern PACKAGE Graphics::TColor __fastcall MixColors(Graphics::TColor Color1, Graphics::TColor Color2, double PercentOfColor1);
extern PACKAGE void __fastcall DrawRectangleOnDC(HDC DC, Types::TRect &R, Graphics::TColor ColorTop, Graphics::TColor ColorBottom, int &Width);
extern PACKAGE void __fastcall TileBitmap(Graphics::TCanvas* Canvas, const Types::TRect &aRect, Graphics::TGraphic* Graphic)/* overload */;
extern PACKAGE void __fastcall TileBitmap(Graphics::TCanvas* Canvas, Types::TRect &aRect, Graphics::TGraphic* Graphic, const Smaskdata::TsMaskData &MaskData, Sconst::TacFillMode FillMode = (Sconst::TacFillMode)(0x0))/* overload */;
extern PACKAGE void __fastcall TileMasked(Graphics::TBitmap* Bmp, Types::TRect &aRect, const Sconst::TCacheInfo &CI, const Smaskdata::TsMaskData &MaskData, Sconst::TacFillMode FillMode = (Sconst::TacFillMode)(0xa));
extern PACKAGE void __fastcall CalcButtonLayout(const Types::TRect &Client, const Types::TPoint &GlyphSize, const tagSIZE &TextRectSize, Buttons::TButtonLayout Layout, Classes::TAlignment Alignment, int Margin, int Spacing, Types::TPoint &GlyphPos, Types::TRect &TextBounds, int BiDiFlags);
extern PACKAGE int __fastcall GetFontHeight(HWND hFont);
extern PACKAGE tagSIZE __fastcall GetStringSize(HGDIOBJ hFont, const AnsiString Text);
extern PACKAGE bool __fastcall LoadJpegOrBmp(Graphics::TPicture* Image, const AnsiString FileName, bool Gray);
extern PACKAGE void __fastcall FocusRect(Graphics::TCanvas* Canvas, const Types::TRect &R, Graphics::TColor LightColor = (Graphics::TColor)(0x8000000f), Graphics::TColor DarkColor = (Graphics::TColor)(0x0));
extern PACKAGE void __fastcall Stretch(const Graphics::TBitmap* Src, const Graphics::TBitmap* Dst, const int Width, const int Height, TFilterType Filter, int Param = 0x0);

}	/* namespace Sgraphutils */
using namespace Sgraphutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sGraphUtils
