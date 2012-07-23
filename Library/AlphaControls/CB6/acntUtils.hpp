// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acntUtils.pas' rev: 6.00

#ifndef acntUtilsHPP
#define acntUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <IniFiles.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
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

namespace Acntutils
{
//-- type declarations -------------------------------------------------------
typedef Sysutils::TSearchRec  TacSearchRec;

typedef TStrings TacStrings;
;

typedef TStringList TacStringList;
;

typedef TFileStream TacFileStream;
;

typedef _WIN32_FIND_DATAA  TacWIN32FindData;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall GetCaptionFontSize(void);
extern PACKAGE HFONT __fastcall acGetTitleFont(void);
extern PACKAGE int __fastcall CheckLimits(int Value, int MinValue, int MaxValue);
extern PACKAGE Byte __fastcall IntToByte(const int Value);
extern PACKAGE __int64 __fastcall HexToInt(AnsiString HexStr);
extern PACKAGE void __fastcall GetIniSections(Classes::TStringList* IniList, Classes::TStringList* SectionsList);
extern PACKAGE void __fastcall GetIniSection(const AnsiString Section, Classes::TStrings* Sections, Classes::TStrings* Strings);
extern PACKAGE AnsiString __fastcall ReadIniString(Classes::TStringList* IniList, Classes::TStringList* SectionsList, const AnsiString Section, const AnsiString Ident, const AnsiString Default);
extern PACKAGE int __fastcall ReadIniInteger(Classes::TStringList* IniList, Classes::TStringList* SectionsList, const AnsiString Section, const AnsiString Ident, int Default);
extern PACKAGE void __fastcall Alert(void)/* overload */;
extern PACKAGE void __fastcall Alert(const AnsiString s)/* overload */;
extern PACKAGE void __fastcall Alert(int i)/* overload */;
extern PACKAGE Extended __fastcall StringToFloat(AnsiString S);
extern PACKAGE AnsiString __fastcall BoolToStr(bool b);
extern PACKAGE Messages::TMessage __fastcall MakeMessage(int Msg, int WParam, int LParam, int Rsult);
extern PACKAGE short __fastcall GetCents(Extended Value);
extern PACKAGE AnsiString __fastcall iff(bool L, const AnsiString s1, const AnsiString s2);
extern PACKAGE System::TObject* __fastcall iffo(bool L, System::TObject* o1, System::TObject* o2);
extern PACKAGE int __fastcall iffi(bool L, int i1, int i2);
extern PACKAGE bool __fastcall Between(int Value, int i1, int i2);
extern PACKAGE int __fastcall SumTrans(int i1, int i2);
extern PACKAGE int __fastcall Maxi(int i1, int i2);
extern PACKAGE int __fastcall Mini(int i1, int i2);
extern PACKAGE int __fastcall LimitIt(int Value, int MinValue, int MaxValue);
extern PACKAGE void __fastcall Changei(int &i1, int &i2);
extern PACKAGE bool __fastcall IsValidFloat(const AnsiString Value, Extended &RetValue);
extern PACKAGE AnsiString __fastcall FormatFloatStr(const AnsiString S, bool Thousands);
extern PACKAGE bool __fastcall acGetAnimation(void);
extern PACKAGE void __fastcall acSetAnimation(bool Value);
extern PACKAGE bool __fastcall RectIsVisible(const Types::TRect &ParentRect, const Types::TRect &Rect);
extern PACKAGE bool __fastcall RectInRect(const Types::TRect &BigRect, const Types::TRect &SmallRect);
extern PACKAGE Types::TRect __fastcall RotateRect(const Types::TRect &R);
extern PACKAGE Types::TRect __fastcall RectsAnd(const Types::TRect &R1, const Types::TRect &R2);
extern PACKAGE Types::TPoint __fastcall OffsetPoint(const Types::TPoint &p, int x, int y);
extern PACKAGE int __fastcall WidthOf(const Types::TRect &r, bool CheckNegative = false);
extern PACKAGE int __fastcall HeightOf(const Types::TRect &r, bool CheckNegative = false);
extern PACKAGE bool __fastcall SubStrInclude(const AnsiString SubString, const AnsiString s, bool CaseInsensitive);
extern PACKAGE AnsiString __fastcall CorrectString(const AnsiString s);
extern PACKAGE int __fastcall acWordPosition(const int N, const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE int __fastcall WordPosition(const int N, const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE AnsiString __fastcall ExtractWord(int N, const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE int __fastcall acWordCount(const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE int __fastcall WordCount(const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE int __fastcall GetWordNumber(const AnsiString W, const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE AnsiString __fastcall AnsiProperCase(const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE AnsiString __fastcall MakeStr(char C, int N);
extern PACKAGE AnsiString __fastcall DelRSpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelESpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelBSpace(const AnsiString S);
extern PACKAGE AnsiString __fastcall DelChars(const AnsiString S, char Chr);
extern PACKAGE AnsiString __fastcall ReplaceStr(const AnsiString S, const AnsiString Srch, const AnsiString Replace);
extern PACKAGE AnsiString __fastcall ExtractSubStr(const AnsiString S, int &Pos, const Sysutils::TSysCharSet &Delims);
extern PACKAGE bool __fastcall IsEmptyStr(const AnsiString S, const Sysutils::TSysCharSet &EmptyChars);
extern PACKAGE bool __fastcall IsNTFamily(void);
extern PACKAGE Sconst::TCacheInfo __fastcall MakeCacheInfo(Graphics::TBitmap* Bmp, int x = 0x0, int y = 0x0);
extern PACKAGE AnsiString __fastcall AddChar(char C, const AnsiString S, int N);
extern PACKAGE AnsiString __fastcall AddCharR(char C, const AnsiString S, int N);
extern PACKAGE AnsiString __fastcall OemToAnsiStr(const AnsiString OemStr);
extern PACKAGE bool __fastcall IsWordPresent(const AnsiString W, const AnsiString S, const Sysutils::TSysCharSet &WordDelims);
extern PACKAGE double __fastcall CurRound(double f);
extern PACKAGE bool __fastcall DeleteRequest(void);
extern PACKAGE bool __fastcall CustomRequest(const AnsiString s);
extern PACKAGE void __fastcall ShowWarning(const AnsiString S);
extern PACKAGE void __fastcall ShowError(const AnsiString s);
extern PACKAGE void __fastcall Delay(int MSecs);
extern PACKAGE bool __fastcall IsIDERunning(void);
extern PACKAGE BOOL __fastcall IsWOW64Proc(void);
extern PACKAGE bool __fastcall HasProperty(System::TObject* Component, AnsiString PropName);
extern PACKAGE System::TObject* __fastcall GetObjProp(System::TObject* Component, AnsiString PropName);
extern PACKAGE void __fastcall SetObjProp(System::TObject* Component, AnsiString PropName, System::TObject* Value);
extern PACKAGE bool __fastcall CheckSetProp(System::TObject* Component, AnsiString PropName, AnsiString Value);
extern PACKAGE bool __fastcall SetSetPropValue(System::TObject* Component, AnsiString PropName, AnsiString ValueName, bool Value);
extern PACKAGE int __fastcall GetIntProp(System::TObject* Component, AnsiString PropName);
extern PACKAGE void __fastcall SetIntProp(System::TObject* Component, AnsiString PropName, int Value);
extern PACKAGE AnsiString __fastcall GetSystemDir();
extern PACKAGE AnsiString __fastcall NormalDir(const AnsiString DirName);
extern PACKAGE __int64 __fastcall GetFileSize(const AnsiString FileName)/* overload */;
extern PACKAGE BOOL __fastcall acFindNextFile(unsigned hFindFile, _WIN32_FIND_DATAA &lpFindFileData);
extern PACKAGE unsigned __fastcall acFindFirstFile(char * lpFileName, _WIN32_FIND_DATAA &lpFindFileData);
extern PACKAGE bool __fastcall ValidFileName(const AnsiString FileName);
extern PACKAGE bool __fastcall acDirExists(const AnsiString Name);
extern PACKAGE AnsiString __fastcall ShortToLongFileName(const AnsiString ShortName);
extern PACKAGE AnsiString __fastcall LongToShortFileName(const AnsiString LongName);
extern PACKAGE AnsiString __fastcall ShortToLongPath(AnsiString ShortName);
extern PACKAGE AnsiString __fastcall LongToShortPath(AnsiString LongName);
extern PACKAGE void __fastcall CopyFiles(AnsiString SrcMask, AnsiString SrcDir, AnsiString DstDir);
extern PACKAGE bool __fastcall acCreateDir(const AnsiString DirName);
extern PACKAGE bool __fastcall acRemoveDir(const AnsiString DirName);
extern PACKAGE bool __fastcall acSetCurrentDir(const AnsiString DirName);
extern PACKAGE AnsiString __fastcall acGetCurrentDir();
extern PACKAGE bool __fastcall acDeleteFile(const AnsiString FileName);
extern PACKAGE bool __fastcall acCopyFile(const AnsiString ExistingFileName, const AnsiString NewFileName, bool bFailIfExists);
extern PACKAGE int __fastcall acFileSetAttr(const AnsiString FileName, unsigned Attr);
extern PACKAGE unsigned __fastcall acFileGetAttr(const AnsiString FileName);
extern PACKAGE int __fastcall acFindFirst(const AnsiString Path, int Attr, Sysutils::TSearchRec &F);
extern PACKAGE int __fastcall acFindNext(Sysutils::TSearchRec &F);
extern PACKAGE void __fastcall acFindClose(Sysutils::TSearchRec &F);
extern PACKAGE bool __fastcall ClearDir(const AnsiString Path, bool Delete);
extern PACKAGE AnsiString __fastcall GetAppName();
extern PACKAGE AnsiString __fastcall GetAppPath();
extern PACKAGE Graphics::TIcon* __fastcall GetIconForFile(const AnsiString FullFileName, int Flag);
extern PACKAGE void __fastcall GetDirs(const AnsiString Path, Classes::TStrings* Items);
extern PACKAGE bool __fastcall acSameText(const AnsiString S1, const AnsiString S2);
extern PACKAGE void __fastcall acFillString(AnsiString &S, int nCount, char C);
extern PACKAGE AnsiString __fastcall acMakeString(char C, int nCount);
extern PACKAGE bool __fastcall CharInSet(char C, const Sysutils::TSysCharSet &CharSet);

}	/* namespace Acntutils */
using namespace Acntutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acntUtils
