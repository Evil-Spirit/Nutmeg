// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sDateUtils.pas' rev: 6.00

#ifndef sDateUtilsHPP
#define sDateUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acntUtils.hpp>	// Pascal unit
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

namespace Sdateutils
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::TDateTime NullDate;
extern PACKAGE bool NormalYears;
extern PACKAGE int __fastcall GetKvartal(System::TDateTime Value);
extern PACKAGE System::TDateTime __fastcall FirstDayOfCurrMonth(System::TDateTime D);
extern PACKAGE System::TDateTime __fastcall LastDayOfPrMonth(System::TDateTime D);
extern PACKAGE int __fastcall DaysPerMonth(int AYear, int AMonth);
extern PACKAGE Word __fastcall ExtractDay(System::TDateTime ADate);
extern PACKAGE Word __fastcall ExtractMonth(System::TDateTime ADate);
extern PACKAGE Word __fastcall ExtractYear(System::TDateTime ADate);
extern PACKAGE AnsiString __fastcall DefDateFormat(bool NormalYears);
extern PACKAGE Sconst::TDateOrder __fastcall GetDateOrder(const AnsiString DateFormat);
extern PACKAGE AnsiString __fastcall DefDateMask(char BlanksChar, bool NormalYears);
extern PACKAGE bool __fastcall ValidDate(System::TDateTime ADate);
extern PACKAGE bool __fastcall IsValidDate(Word Y, Word M, Word D);
extern PACKAGE bool __fastcall InternalStrToDate(const AnsiString DateFormat, const AnsiString S, System::TDateTime &Date);
extern PACKAGE bool __fastcall ScanDateStr(const AnsiString Format, const AnsiString S, int &D, int &M, int &Y);
extern PACKAGE void __fastcall ExtractMask(const AnsiString Format, const AnsiString S, char Ch, int Cnt, int &I, int Blank, int Default);
extern PACKAGE Word __fastcall CurrentYear(void);
extern PACKAGE int __fastcall ExpandYear(int Year);
extern PACKAGE bool __fastcall ScanDate(const AnsiString S, const AnsiString DateFormat, int &Pos, int &Y, int &M, int &D);
extern PACKAGE Byte __fastcall MonthFromName(const AnsiString S, Byte MaxLen);
extern PACKAGE bool __fastcall ScanNumber(const AnsiString S, int MaxLength, int &Pos, int &Number);
extern PACKAGE bool __fastcall ScanChar(const AnsiString S, int &Pos, char Ch);
extern PACKAGE void __fastcall ScanBlanks(const AnsiString S, int &Pos);

}	/* namespace Sdateutils */
using namespace Sdateutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sDateUtils
