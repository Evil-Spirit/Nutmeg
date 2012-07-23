// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acSkinPack.pas' rev: 6.00

#ifndef acSkinPackHPP
#define acSkinPackHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acskinpack
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TacImageItem
{
	AnsiString FileName;
	bool IsBitmap;
	Classes::TMemoryStream* FileStream;
} ;
#pragma pack(pop)

typedef DynamicArray<TacImageItem >  TacImageItems;

class DELPHICLASS TacSkinConvertor;
class PASCALIMPLEMENTATION TacSkinConvertor : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
public:
	int ImageCount;
	DynamicArray<TacImageItem >  Files;
	Classes::TMemoryStream* Options;
	Classes::TMemoryStream* PackedData;
	void __fastcall Clear(void);
	__fastcall virtual ~TacSkinConvertor(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TacSkinConvertor(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define acAbbr "ASzf"
extern PACKAGE void __fastcall PackDir(const AnsiString SrcPath, const AnsiString FileName);
extern PACKAGE void __fastcall UnpackSkinFile(const AnsiString Filename, const AnsiString DestDirectory);
extern PACKAGE void __fastcall LoadSkinFromFile(const AnsiString FileName, TacSkinConvertor* &Convertor, bool FreePackedData = true);
extern PACKAGE void __fastcall ExtractPackedData(TacSkinConvertor* &Convertor);

}	/* namespace Acskinpack */
using namespace Acskinpack;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acSkinPack
