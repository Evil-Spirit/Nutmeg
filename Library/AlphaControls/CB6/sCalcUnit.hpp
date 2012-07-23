// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCalcUnit.pas' rev: 6.00

#ifndef sCalcUnitHPP
#define sCalcUnitHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Grids.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <sSpeedButton.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <Clipbrd.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ActnList.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace Scalcunit
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsCalcState { csFirst, csValid, csError };
#pragma option pop

class DELPHICLASS TsCalcForm;
class PASCALIMPLEMENTATION TsCalcForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Menus::TMenuItem* OK1;
	Menus::TMenuItem* Cancel1;
	Spanel::TsPanel* FMainPanel;
	Menus::TPopupMenu* PopupMenu1;
	Menus::TMenuItem* N1;
	Menus::TMenuItem* N2;
	Spanel::TsPanel* FCalculatorPanel;
	Spanel::TsPanel* FCalcPanel;
	Sspeedbutton::TsSpeedButton* sSpeedButton1;
	Sspeedbutton::TsSpeedButton* sSpeedButton2;
	Sspeedbutton::TsSpeedButton* sSpeedButton3;
	Sspeedbutton::TsSpeedButton* sSpeedButton4;
	Sspeedbutton::TsSpeedButton* sSpeedButton5;
	Sspeedbutton::TsSpeedButton* sSpeedButton6;
	Sspeedbutton::TsSpeedButton* sSpeedButton7;
	Sspeedbutton::TsSpeedButton* sSpeedButton8;
	Sspeedbutton::TsSpeedButton* sSpeedButton9;
	Sspeedbutton::TsSpeedButton* sSpeedButton10;
	Sspeedbutton::TsSpeedButton* sSpeedButton11;
	Sspeedbutton::TsSpeedButton* sSpeedButton12;
	Sspeedbutton::TsSpeedButton* sSpeedButton13;
	Sspeedbutton::TsSpeedButton* sSpeedButton14;
	Sspeedbutton::TsSpeedButton* sSpeedButton15;
	Sspeedbutton::TsSpeedButton* sSpeedButton16;
	Sspeedbutton::TsSpeedButton* sSpeedButton17;
	Sspeedbutton::TsSpeedButton* sSpeedButton18;
	Sspeedbutton::TsSpeedButton* sSpeedButton19;
	Sspeedbutton::TsSpeedButton* sSpeedButton20;
	Sspeedbutton::TsSpeedButton* sSpeedButton21;
	Sspeedbutton::TsSpeedButton* sSpeedButton22;
	Sspeedbutton::TsSpeedButton* sSpeedButton23;
	Sspeedbutton::TsSpeedButton* sSpeedButton24;
	Sspeedbutton::TsSpeedButton* sSpeedButton25;
	Sspeedbutton::TsSpeedButton* sSpeedButton26;
	Spanel::TsPanel* FDisplayPanel;
	Spanel::TsDragBar* sDragBar1;
	Sspeedbutton::TsSpeedButton* sToolButton3;
	Sspeedbutton::TsSpeedButton* sToolButton1;
	void __fastcall sSpeedButton22Click(System::TObject* Sender);
	void __fastcall FormKeyPress(System::TObject* Sender, char &Key);
	void __fastcall N1Click(System::TObject* Sender);
	void __fastcall N2Click(System::TObject* Sender);
	void __fastcall PopupMenu1Popup(System::TObject* Sender);
	void __fastcall sSpeedButton24Click(System::TObject* Sender);
	void __fastcall sSpeedButton23Click(System::TObject* Sender);
	void __fastcall sSpeedButton25Click(System::TObject* Sender);
	void __fastcall sSpeedButton26Click(System::TObject* Sender);
	void __fastcall sSpeedButton19Click(System::TObject* Sender);
	void __fastcall sSpeedButton13Click(System::TObject* Sender);
	void __fastcall sSpeedButton7Click(System::TObject* Sender);
	void __fastcall sSpeedButton21Click(System::TObject* Sender);
	void __fastcall sSpeedButton15Click(System::TObject* Sender);
	void __fastcall sSpeedButton9Click(System::TObject* Sender);
	void __fastcall sSpeedButton3Click(System::TObject* Sender);
	void __fastcall OK1Click(System::TObject* Sender);
	void __fastcall Cancel1Click(System::TObject* Sender);
	void __fastcall sSpeedButton2Click(System::TObject* Sender);
	void __fastcall sSpeedButton14Click(System::TObject* Sender);
	void __fastcall sSpeedButton8Click(System::TObject* Sender);
	void __fastcall sSpeedButton20Click(System::TObject* Sender);
	void __fastcall sSpeedButton1Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall sToolButton3Click(System::TObject* Sender);
	void __fastcall sToolButton1Click(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormDeactivate(System::TObject* Sender);
	
protected:
	Extended FOperand;
	Classes::TNotifyEvent FOnError;
	Classes::TNotifyEvent FOnOk;
	Classes::TNotifyEvent FOnCancel;
	Classes::TNotifyEvent FOnResult;
	Classes::TNotifyEvent FOnTextChange;
	Controls::TKeyPressEvent FOnCalcKey;
	Classes::TNotifyEvent FOnDisplayChange;
	
private:
	virtual void __fastcall TextChanged(void);
	
public:
	AnsiString FText;
	Extended FMemory;
	Byte FPrecision;
	bool FBeepOnError;
	TsCalcState FStatus;
	char FOperator;
	Mask::TCustomMaskEdit* FEditor;
	void __fastcall FillArOR(void);
	HRGN __fastcall GetRgnFromArOR(void);
	Variant __fastcall GetValue();
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall SetValue(const Variant &Value);
	HIDESBASE void __fastcall SetText(const AnsiString Value);
	void __fastcall CheckFirst(void);
	void __fastcall CalcKey(char Key);
	void __fastcall Clear(void);
	void __fastcall Error(void);
	void __fastcall SetDisplay(Extended R);
	Extended __fastcall GetDisplay(void);
	void __fastcall UpdateMemoryLabel(void);
	void __fastcall Copy(void);
	void __fastcall Paste(void);
	__property Extended DisplayValue = {read=GetDisplay, write=SetDisplay};
	__property AnsiString Text = {read=FText};
	__property Classes::TNotifyEvent OnResultClick = {read=FOnResult, write=FOnResult};
	__property Classes::TNotifyEvent OnError = {read=FOnError, write=FOnError};
	__property Classes::TNotifyEvent OnTextChange = {read=FOnTextChange, write=FOnTextChange};
	__property Controls::TKeyPressEvent OnCalcKey = {read=FOnCalcKey, write=FOnCalcKey};
	__property Classes::TNotifyEvent OnDisplayChange = {read=FOnDisplayChange, write=FOnDisplayChange};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TsCalcForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TsCalcForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TsCalcForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCalcForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define ResultKeys (System::Set<char, 0, 255> () << '\xd' << '\x25' << '\x2d' )

}	/* namespace Scalcunit */
using namespace Scalcunit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCalcUnit
