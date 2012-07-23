// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acAlphaImageList.pas' rev: 6.00

#ifndef acAlphaImageListHPP
#define acAlphaImageListHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acntUtils.hpp>	// Pascal unit
#include <acPNG.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acalphaimagelist
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsImageFormat { ifPNG, ifICO };
#pragma option pop

class DELPHICLASS TsImgListItem;
class DELPHICLASS TsImgListItems;
class DELPHICLASS TsAlphaImageList;
class PASCALIMPLEMENTATION TsAlphaImageList : public Controls::TImageList 
{
	typedef Controls::TImageList inherited;
	
private:
	TsImgListItems* FItems;
	bool StdListIsGenerated;
	bool AcChanging;
	void __fastcall SetItems(const TsImgListItems* Value);
	
protected:
	void __fastcall CreateImgList(void);
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall DoDraw(int Index, Graphics::TCanvas* Canvas, int X, int Y, unsigned Style, bool Enabled = true);
	void __fastcall KillImgList(void);
	bool __fastcall IsDuplicated(void);
	bool __fastcall TryLoadFromFile(const AnsiString FileName);
	void __fastcall ItemsClear(void);
	
public:
	bool DoubleData;
	void __fastcall AcBeginUpdate(void);
	void __fastcall AcEndUpdate(bool DoChange = true);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	HIDESBASE void __fastcall CopyImages(const TsAlphaImageList* ImgList);
	__fastcall virtual TsAlphaImageList(Classes::TComponent* AOwner);
	__fastcall virtual ~TsAlphaImageList(void);
	void __fastcall GenerateStdList(void);
	bool __fastcall GetBitmap32(int Index, Graphics::TBitmap* Image);
	virtual void __fastcall Loaded(void);
	void __fastcall LoadFromFile(const AnsiString FileName);
	HIDESBASE void __fastcall SetNewDimensions(unsigned Value);
	
__published:
	__property TsImgListItems* Items = {read=FItems, write=SetItems};
public:
	#pragma option push -w-inl
	/* TCustomImageList.CreateSize */ inline __fastcall TsAlphaImageList(int AWidth, int AHeight) : Controls::TImageList(AWidth, AHeight) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TsImgListItems : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
public:
	TsImgListItem* operator[](int Index) { return Items[Index]; }
	
protected:
	TsAlphaImageList* FOwner;
	HIDESBASE TsImgListItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TsImgListItem* Value);
	DYNAMIC Classes::TPersistent* __fastcall GetOwner(void);
	
public:
	__fastcall TsImgListItems(TsAlphaImageList* AOwner);
	__fastcall virtual ~TsImgListItems(void);
	__property TsImgListItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
};


class PASCALIMPLEMENTATION TsImgListItem : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
private:
	TsImageFormat FImageFormat;
	Graphics::TPixelFormat FPixelFormat;
	
protected:
	TsImgListItems* FOwner;
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	void __fastcall ReadData(Classes::TStream* Reader);
	void __fastcall WriteData(Classes::TStream* Writer);
	
public:
	Classes::TMemoryStream* ImgData;
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	__fastcall virtual ~TsImgListItem(void);
	__fastcall virtual TsImgListItem(Classes::TCollection* Collection);
	
__published:
	__property TsImageFormat ImageFormat = {read=FImageFormat, write=FImageFormat, nodefault};
	__property Graphics::TPixelFormat PixelFormat = {read=FPixelFormat, write=FPixelFormat, default=7};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall GetImageFormat(const AnsiString FileName, TsImageFormat &ImageFormat);
extern PACKAGE tagSIZE __fastcall DrawAlphaImgList(const Imglist::TCustomImageList* ImgList, const Graphics::TBitmap* DestBmp, const int Left, const int Top, const int ImageIndex, const int Blend, const Graphics::TColor GrayedColor, int State, const int NumGlyphs, const bool Reflected);
extern PACKAGE void __fastcall DrawAlphaImgListDC(const Imglist::TCustomImageList* ImgList, const HDC DC, const int Left, const int Top, const int ImageIndex, const int Blend, const Graphics::TColor GrayedColor, const int State, const int NumGlyphs, const bool Reflected);
extern PACKAGE bool __fastcall HaveMagic(const AnsiString FileName, const void * Magic, const int Size);
extern PACKAGE bool __fastcall AddImageFromRes(unsigned aInstance, TsAlphaImageList* ImageList, const AnsiString ResName, TsImageFormat ImageFormat);

}	/* namespace Acalphaimagelist */
using namespace Acalphaimagelist;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acAlphaImageList
