// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sHtmlParse.pas' rev: 6.00

#ifndef sHtmlParseHPP
#define sHtmlParseHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Shtmlparse
{
//-- type declarations -------------------------------------------------------
typedef DynamicArray<Graphics::TFont* >  sHtmlParse__2;

class DELPHICLASS TsHtml;
class PASCALIMPLEMENTATION TsHtml : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Graphics::TBitmap* Bitmap;
	int CurX;
	int CurY;
	int Len;
	AnsiString Origin;
	AnsiString UppedText;
	DynamicArray<Graphics::TFont* >  aFonts;
	#pragma pack(push, 1)
	Types::TRect Area;
	#pragma pack(pop)
	
	int MaxBmpWidth;
	int MaxBmpHeight;
	int CurWidthValue;
	int CurHeightValue;
	int CurrentRowHeight;
	Classes::TAlignment CurrentRowAlignment;
	__fastcall virtual ~TsHtml(void);
	void __fastcall ShowCut(int i2, int &i1);
	void __fastcall Init(Graphics::TBitmap* Bmp, AnsiString Text, const Types::TRect &aRect);
	bool __fastcall ExecTag(const AnsiString s);
	void __fastcall NewRow(void);
	void __fastcall NewFont(const AnsiString s);
	void __fastcall BackFont(void);
	Types::TRect __fastcall HTMLText();
	void __fastcall SetAlignment(const AnsiString Tag);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TsHtml(void) : System::TObject() { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define Letters (System::Set<char, 0, 255> () << '\x41' << '\x42' << '\x43' << '\x44' << '\x45' << '\x46' )
#define Digits (System::Set<char, 0, 255> () << '\x30' << '\x31' << '\x32' << '\x33' << '\x34' << '\x35' << '\x36' << '\x37' << '\x38' << '\x39' )
#define DisabledChars (System::Set<char, 0, 255> () << '\xa' << '\xd' )
extern PACKAGE AnsiString __fastcall GetTag(const AnsiString s, int CurPos);
extern PACKAGE void __fastcall SetFont(Graphics::TFont* Font, const AnsiString Tag);

}	/* namespace Shtmlparse */
using namespace Shtmlparse;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sHtmlParse
