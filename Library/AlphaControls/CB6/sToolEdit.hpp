// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sTooledit.pas' rev: 6.00

#ifndef sTooleditHPP
#define sTooleditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MaskUtils.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sMonthCalendar.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <sStrings.hpp>	// Pascal unit
#include <sPopupClndr.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <FileCtrl.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <sDateUtils.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <sDialogs.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Stooledit
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TExecOpenDialogEvent)(System::TObject* Sender, AnsiString &Name, bool &Action);

class DELPHICLASS TsFileDirEdit;
class PASCALIMPLEMENTATION TsFileDirEdit : public Scustomcomboedit::TsCustomComboEdit 
{
	typedef Scustomcomboedit::TsCustomComboEdit inherited;
	
private:
	bool FAcceptFiles;
	Classes::TNotifyEvent FOnDropFiles;
	TExecOpenDialogEvent FOnBeforeDialog;
	TExecOpenDialogEvent FOnAfterDialog;
	void __fastcall SetDragAccept(bool Value);
	void __fastcall SetAcceptFiles(bool Value);
	MESSAGE void __fastcall WMDropFiles(Messages::TWMDropFiles &Msg);
	
protected:
	bool FMultipleDirs;
	virtual void __fastcall CreateHandle(void);
	virtual void __fastcall DestroyWindowHandle(void);
	virtual AnsiString __fastcall GetLongName(void) = 0 ;
	virtual AnsiString __fastcall GetShortName(void) = 0 ;
	DYNAMIC void __fastcall DoAfterDialog(AnsiString &FileName, bool &Action);
	DYNAMIC void __fastcall DoBeforeDialog(AnsiString &FileName, bool &Action);
	virtual void __fastcall ReceptFileDir(const AnsiString AFileName) = 0 ;
	virtual void __fastcall ClearFileList(void);
	__property MaxLength  = {default=255};
	
public:
	__fastcall virtual TsFileDirEdit(Classes::TComponent* AOwner);
	__property AnsiString LongName = {read=GetLongName};
	__property AnsiString ShortName = {read=GetShortName};
	__property bool AcceptFiles = {read=FAcceptFiles, write=SetAcceptFiles, default=0};
	
__published:
	__property TExecOpenDialogEvent OnBeforeDialog = {read=FOnBeforeDialog, write=FOnBeforeDialog};
	__property TExecOpenDialogEvent OnAfterDialog = {read=FOnAfterDialog, write=FOnAfterDialog};
	__property Classes::TNotifyEvent OnDropFiles = {read=FOnDropFiles, write=FOnDropFiles};
public:
	#pragma option push -w-inl
	/* TsCustomComboEdit.Destroy */ inline __fastcall virtual ~TsFileDirEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsFileDirEdit(HWND ParentWindow) : Scustomcomboedit::TsCustomComboEdit(ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TFileDialogKind { dkOpen, dkSave, dkOpenPicture, dkSavePicture };
#pragma option pop

class DELPHICLASS TsFilenameEdit;
class PASCALIMPLEMENTATION TsFilenameEdit : public TsFileDirEdit 
{
	typedef TsFileDirEdit inherited;
	
private:
	Dialogs::TOpenDialog* FDialog;
	TFileDialogKind FDialogKind;
	void __fastcall CreateEditDialog(void);
	AnsiString __fastcall GetFileName();
	AnsiString __fastcall GetDefaultExt();
	Dialogs::TFileEditStyle __fastcall GetFileEditStyle(void);
	AnsiString __fastcall GetFilter();
	int __fastcall GetFilterIndex(void);
	AnsiString __fastcall GetInitialDir();
	Classes::TStrings* __fastcall GetHistoryList(void);
	Dialogs::TOpenOptions __fastcall GetOptions(void);
	AnsiString __fastcall GetDialogTitle();
	Classes::TStrings* __fastcall GetDialogFiles(void);
	void __fastcall SetDialogKind(TFileDialogKind Value);
	void __fastcall SetFileName(const AnsiString Value);
	void __fastcall SetDefaultExt(AnsiString Value);
	void __fastcall SetFileEditStyle(Dialogs::TFileEditStyle Value);
	void __fastcall SetFilter(const AnsiString Value);
	void __fastcall SetFilterIndex(int Value);
	void __fastcall SetInitialDir(const AnsiString Value);
	void __fastcall SetHistoryList(Classes::TStrings* Value);
	void __fastcall SetOptions(Dialogs::TOpenOptions Value);
	void __fastcall SetDialogTitle(const AnsiString Value);
	bool __fastcall IsCustomTitle(void);
	bool __fastcall IsCustomFilter(void);
	
protected:
	DYNAMIC void __fastcall ButtonClick(void);
	virtual void __fastcall ReceptFileDir(const AnsiString AFileName);
	virtual void __fastcall ClearFileList(void);
	virtual AnsiString __fastcall GetLongName();
	virtual AnsiString __fastcall GetShortName();
	__property Dialogs::TFileEditStyle FileEditStyle = {read=GetFileEditStyle, write=SetFileEditStyle, default=0};
	
public:
	__fastcall virtual TsFilenameEdit(Classes::TComponent* AOwner);
	__property Dialogs::TOpenDialog* Dialog = {read=FDialog};
	__property Classes::TStrings* DialogFiles = {read=GetDialogFiles};
	__property AnsiString DialogTitle = {read=GetDialogTitle, write=SetDialogTitle, stored=IsCustomTitle};
	
__published:
	__property AcceptFiles  = {default=0};
	__property AnsiString DefaultExt = {read=GetDefaultExt, write=SetDefaultExt};
	__property int FilterIndex = {read=GetFilterIndex, write=SetFilterIndex, default=1};
	__property AnsiString InitialDir = {read=GetInitialDir, write=SetInitialDir};
	__property TFileDialogKind DialogKind = {read=FDialogKind, write=SetDialogKind, default=0};
	__property AnsiString FileName = {read=GetFileName, write=SetFileName, stored=false};
	__property AnsiString Filter = {read=GetFilter, write=SetFilter, stored=IsCustomFilter};
	__property Classes::TStrings* HistoryList = {read=GetHistoryList, write=SetHistoryList};
	__property Dialogs::TOpenOptions DialogOptions = {read=GetOptions, write=SetOptions, default=524292};
public:
	#pragma option push -w-inl
	/* TsCustomComboEdit.Destroy */ inline __fastcall virtual ~TsFilenameEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsFilenameEdit(HWND ParentWindow) : TsFileDirEdit(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsDirectoryEdit;
class PASCALIMPLEMENTATION TsDirectoryEdit : public TsFileDirEdit 
{
	typedef TsFileDirEdit inherited;
	
private:
	Filectrl::TSelectDirOpts FOptions;
	AnsiString FInitialDir;
	AnsiString FDialogText;
	AnsiString FRoot;
	bool FNoChangeDir;
	bool FShowRootBtns;
	
protected:
	DYNAMIC void __fastcall ButtonClick(void);
	virtual void __fastcall ReceptFileDir(const AnsiString AFileName);
	virtual AnsiString __fastcall GetLongName();
	virtual AnsiString __fastcall GetShortName();
	
public:
	__fastcall virtual TsDirectoryEdit(Classes::TComponent* AOwner);
	
__published:
	__property AcceptFiles  = {default=0};
	__property AnsiString InitialDir = {read=FInitialDir, write=FInitialDir};
	__property Filectrl::TSelectDirOpts DialogOptions = {read=FOptions, write=FOptions, default=7};
	__property AnsiString DialogText = {read=FDialogText, write=FDialogText};
	__property bool MultipleDirs = {read=FMultipleDirs, write=FMultipleDirs, default=0};
	__property bool NoChangeDir = {read=FNoChangeDir, write=FNoChangeDir, default=0};
	__property AnsiString Root = {read=FRoot, write=FRoot};
	__property bool ShowRootBtns = {read=FShowRootBtns, write=FShowRootBtns, default=0};
public:
	#pragma option push -w-inl
	/* TsCustomComboEdit.Destroy */ inline __fastcall virtual ~TsDirectoryEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsDirectoryEdit(HWND ParentWindow) : TsFileDirEdit(ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TYearDigits { dyDefault, dyFour, dyTwo };
#pragma option pop

typedef void __fastcall (__closure *TOnAcceptDate)(System::TObject* Sender, System::TDateTime &aDate, bool &CanAccept);

class DELPHICLASS TsCustomDateEdit;
class PASCALIMPLEMENTATION TsCustomDateEdit : public Scustomcomboedit::TsCustomComboEdit 
{
	typedef Scustomcomboedit::TsCustomComboEdit inherited;
	
private:
	AnsiString *FTitle;
	TOnAcceptDate FOnAcceptDate;
	bool FDefaultToday;
	bool FHooked;
	bool FCheckOnExit;
	char FBlanksChar;
	Classes::TStrings* FCalendarHints;
	Comctrls::TCalDayOfWeek FStartOfWeek;
	Sconst::TDaysOfWeek FWeekends;
	Graphics::TColor FWeekendColor;
	TYearDigits FYearDigits;
	System::SmallString<10>  FDateFormat;
	bool FFormatting;
	System::TDateTime FMinDate;
	System::TDateTime FMaxDate;
	Smonthcalendar::TGetCellParams FOnGetCellParams;
	bool FShowCurrentDate;
	Smonthcalendar::TGetCellParams FOnDrawDay;
	bool FShowWeeks;
	bool FShowTodayBtn;
	System::TDateTime __fastcall GetDate(void);
	void __fastcall SetDate(System::TDateTime Value);
	void __fastcall SetYearDigits(TYearDigits Value);
	AnsiString __fastcall GetDialogTitle();
	void __fastcall SetDialogTitle(const AnsiString Value);
	bool __fastcall IsCustomTitle(void);
	void __fastcall SetCalendarHints(Classes::TStrings* Value);
	void __fastcall CalendarHintsChanged(System::TObject* Sender);
	void __fastcall SetWeekendColor(Graphics::TColor Value);
	void __fastcall SetWeekends(Sconst::TDaysOfWeek Value);
	void __fastcall SetStartOfWeek(Comctrls::TCalDayOfWeek Value);
	void __fastcall SetBlanksChar(char Value);
	bool __fastcall TextStored(void);
	bool __fastcall FourDigitYear(void);
	bool __fastcall FormatSettingsChange(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMExit(Messages::TWMNoParams &Message);
	void __fastcall SetMinDate(const System::TDateTime Value);
	void __fastcall SetMaxDate(const System::TDateTime Value);
	void __fastcall SetShowCurrentDate(const bool Value);
	
protected:
	DYNAMIC void __fastcall Change(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(char &Key);
	virtual void __fastcall CreateWindowHandle(const Controls::TCreateParams &Params);
	virtual void __fastcall DestroyWindowHandle(void);
	AnsiString __fastcall GetDateFormat();
	bool __fastcall DateIsStored(void);
	virtual void __fastcall ApplyDate(System::TDateTime Value);
	void __fastcall UpdateFormat(void);
	void __fastcall UpdatePopup(void);
	virtual void __fastcall PopupWindowShow(void);
	__property bool Formatting = {read=FFormatting, nodefault};
	__property EditMask  = {stored=false};
	__property AnsiString DialogTitle = {read=GetDialogTitle, write=SetDialogTitle, stored=IsCustomTitle};
	__property char BlanksChar = {read=FBlanksChar, write=SetBlanksChar, default=32};
	__property Classes::TStrings* CalendarHints = {read=FCalendarHints, write=SetCalendarHints};
	__property bool CheckOnExit = {read=FCheckOnExit, write=FCheckOnExit, default=0};
	__property bool DefaultToday = {read=FDefaultToday, write=FDefaultToday, default=0};
	__property MaxLength  = {stored=false, default=0};
	__property Comctrls::TCalDayOfWeek StartOfWeek = {read=FStartOfWeek, write=SetStartOfWeek, default=7};
	__property Sconst::TDaysOfWeek Weekends = {read=FWeekends, write=SetWeekends, default=64};
	__property Graphics::TColor WeekendColor = {read=FWeekendColor, write=SetWeekendColor, default=255};
	__property TYearDigits YearDigits = {read=FYearDigits, write=SetYearDigits, default=1};
	__property TOnAcceptDate OnAcceptDate = {read=FOnAcceptDate, write=FOnAcceptDate};
	
public:
	virtual void __fastcall Loaded(void);
	__fastcall virtual TsCustomDateEdit(Classes::TComponent* AOwner);
	__fastcall virtual ~TsCustomDateEdit(void);
	bool __fastcall CheckValidDate(void);
	AnsiString __fastcall GetDateMask();
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall UpdateMask(void);
	__property System::TDateTime Date = {read=GetDate, write=SetDate};
	__property Text  = {stored=DateIsStored};
	
__published:
	__property System::TDateTime MinDate = {read=FMinDate, write=SetMinDate};
	__property System::TDateTime MaxDate = {read=FMaxDate, write=SetMaxDate};
	__property bool ShowCurrentDate = {read=FShowCurrentDate, write=SetShowCurrentDate, default=1};
	__property bool ShowWeeks = {read=FShowWeeks, write=FShowWeeks, default=0};
	__property bool ShowTodayBtn = {read=FShowTodayBtn, write=FShowTodayBtn, default=1};
	__property Smonthcalendar::TGetCellParams OnDrawDay = {read=FOnDrawDay, write=FOnDrawDay};
	__property Smonthcalendar::TGetCellParams OnGetCellParams = {read=FOnGetCellParams, write=FOnGetCellParams};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCustomDateEdit(HWND ParentWindow) : Scustomcomboedit::TsCustomComboEdit(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsDateEdit;
class PASCALIMPLEMENTATION TsDateEdit : public TsCustomDateEdit 
{
	typedef TsCustomDateEdit inherited;
	
public:
	__fastcall virtual TsDateEdit(Classes::TComponent* AOwner);
	__property EditMask ;
	
__published:
	__property BlanksChar  = {default=32};
	__property CalendarHints ;
	__property CheckOnExit  = {default=0};
	__property ClickKey  = {default=32808};
	__property Date ;
	__property DefaultToday  = {default=0};
	__property DialogTitle ;
	__property MaxDate ;
	__property MinDate ;
	__property PopupAlign  = {default=0};
	__property PopupWidth  = {default=197};
	__property StartOfWeek  = {default=7};
	__property Text ;
	__property Weekends  = {default=64};
	__property WeekendColor  = {default=255};
	__property YearDigits  = {default=1};
	__property OnAcceptDate ;
	__property OnButtonClick ;
	__property OnChange ;
	__property OnContextPopup ;
public:
	#pragma option push -w-inl
	/* TsCustomDateEdit.Destroy */ inline __fastcall virtual ~TsDateEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsDateEdit(HWND ParentWindow) : TsCustomDateEdit(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall DateFormatChanged(void);
extern PACKAGE System::TDateTime __fastcall StrToDateFmt(const AnsiString DateFormat, const AnsiString S);
extern PACKAGE System::TDateTime __fastcall StrToDateFmtDef(const AnsiString DateFormat, const AnsiString S, System::TDateTime Default);

}	/* namespace Stooledit */
using namespace Stooledit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sTooledit
