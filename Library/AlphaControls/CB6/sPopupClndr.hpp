// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sPopupClndr.pas' rev: 6.00

#ifndef sPopupClndrHPP
#define sPopupClndrHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sMonthCalendar.hpp>	// Pascal unit
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

namespace Spopupclndr
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsPopupCalendar;
class PASCALIMPLEMENTATION TsPopupCalendar : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Smonthcalendar::TsMonthCalendar* sMonthCalendar1;
	Menus::TPopupMenu* PopupMenu1;
	Menus::TMenuItem* N1;
	Menus::TMenuItem* N2;
	Menus::TMenuItem* OK1;
	Menus::TMenuItem* Cancel1;
	void __fastcall sToolButton3Click(System::TObject* Sender);
	void __fastcall sToolButton1Click(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CalendarClick(void);
	void __fastcall FormDeactivate(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	
protected:
	Scustomcomboedit::TCloseUpEvent FCloseUp;
	DYNAMIC void __fastcall KeyPress(char &Key);
	Variant __fastcall GetValue();
	void __fastcall SetValue(const Variant &Value);
	virtual void __fastcall CloseUp(bool Accept);
	void __fastcall FillArOR(void);
	HRGN __fastcall GetRgnFromArOR(void);
	
public:
	bool FFourDigitYear;
	Scustomcomboedit::TsCustomComboEdit* FEditor;
	bool __fastcall IsValidDate(System::TDateTime Date);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	__property Smonthcalendar::TsMonthCalendar* FCalendar = {read=sMonthCalendar1, write=sMonthCalendar1};
	__property Scustomcomboedit::TCloseUpEvent OnCloseUp = {read=FCloseUp, write=FCloseUp};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TsPopupCalendar(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TsPopupCalendar(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TsPopupCalendar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsPopupCalendar(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Byte FormHeight = 0x90;
extern PACKAGE TsPopupCalendar* sPopupCalendar;

}	/* namespace Spopupclndr */
using namespace Spopupclndr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sPopupClndr
