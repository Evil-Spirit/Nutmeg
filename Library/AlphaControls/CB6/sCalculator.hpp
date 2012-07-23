// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCalculator.pas' rev: 6.00

#ifndef sCalculatorHPP
#define sCalculatorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Clipbrd.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <sCalcUnit.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Scalculator
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TacCalcTitleButton { cbClose, cbMinimize };
#pragma option pop

typedef Set<TacCalcTitleButton, cbClose, cbMinimize>  TacCalcTitleButtons;

class DELPHICLASS TsCalculator;
class PASCALIMPLEMENTATION TsCalculator : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Scalcunit::TsCalcForm* FCalc;
	Extended FValue;
	Extended FMemory;
	AnsiString FCaption;
	Byte FPrecision;
	bool FBeepOnError;
	Classes::THelpContext FHelpContext;
	Classes::TNotifyEvent FOnChange;
	Controls::TKeyPressEvent FOnCalcKey;
	Classes::TNotifyEvent FOnDisplayChange;
	TacCalcTitleButtons FTitleButtons;
	int FScaleIncrement;
	Extended __fastcall GetDisplay(void);
	void __fastcall SetScaleIncrement(const int Value);
	
protected:
	bool Scaled;
	DYNAMIC void __fastcall Change(void);
	DYNAMIC void __fastcall CalcKey(char &Key);
	DYNAMIC void __fastcall DisplayChange(void);
	
public:
	__fastcall virtual TsCalculator(Classes::TComponent* AOwner);
	__fastcall virtual ~TsCalculator(void);
	__property Extended CalcDisplay = {read=GetDisplay};
	__property Extended Memory = {read=FMemory};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnDisplayChange = {read=FOnDisplayChange, write=FOnDisplayChange};
	bool __fastcall Execute(int LeftPos = 0xffffffff, int TopPos = 0xffffffff);
	
__published:
	__property bool BeepOnError = {read=FBeepOnError, write=FBeepOnError, default=1};
	__property Byte Precision = {read=FPrecision, write=FPrecision, default=24};
	__property AnsiString Caption = {read=FCaption, write=FCaption};
	__property Extended Value = {read=FValue, write=FValue};
	__property int ScaleIncrement = {read=FScaleIncrement, write=SetScaleIncrement, nodefault};
	__property TacCalcTitleButtons TitleButtons = {read=FTitleButtons, write=FTitleButtons, default=3};
	__property Classes::THelpContext HelpContext = {read=FHelpContext, write=FHelpContext, default=0};
};


//-- var, const, procedure ---------------------------------------------------
#define ButtonChars "0123456789_./*-+Q%R=\bC"

}	/* namespace Scalculator */
using namespace Scalculator;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCalculator
