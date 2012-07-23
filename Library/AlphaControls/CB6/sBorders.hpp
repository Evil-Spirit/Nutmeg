// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sBorders.pas' rev: 6.00

#ifndef sBordersHPP
#define sBordersHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sGraphUtils.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <sMaskData.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sborders
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Types::TRect __fastcall PaintBorderFast(HDC DC, const Types::TRect &aRect, int MinBorderWidth, Scommondata::TsCommonData* SkinData, int State);
extern PACKAGE void __fastcall CopyMask(int DstX1, int DstY1, int DstX2, int DstY2, int SrcX1, int SrcY1, int SrcX2, int SrcY2, Graphics::TBitmap* Bmp, HRGN Region, const Smaskdata::TsMaskData &MaskData, bool FillRgn = false);
extern PACKAGE void __fastcall PaintRgnBorder(Graphics::TBitmap* Bmp, HRGN Region, bool Filling, const Smaskdata::TsMaskData &MaskData, int State);

}	/* namespace Sborders */
using namespace Sborders;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sBorders
