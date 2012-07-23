// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sStoreUtils.pas' rev: 6.00

#ifndef sStoreUtilsHPP
#define sStoreUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Buttons.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
#include <sCheckBox.hpp>	// Pascal unit
#include <sRadioButton.hpp>	// Pascal unit
#include <sMemo.hpp>	// Pascal unit
#include <sComboEdit.hpp>	// Pascal unit
#include <sPageControl.hpp>	// Pascal unit
#include <sComboBox.hpp>	// Pascal unit
#include <sCurrencyEdit.hpp>	// Pascal unit
#include <sEdit.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ActnList.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ToolWin.hpp>	// Pascal unit
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

namespace Sstoreutils
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString __fastcall ReadIniString(const AnsiString Section, const AnsiString Named, const AnsiString FileName)/* overload */;
extern PACKAGE AnsiString __fastcall ReadIniString(const AnsiString Section, const AnsiString Named, Inifiles::TMemIniFile* r)/* overload */;
extern PACKAGE void __fastcall ReadIniStrings(Classes::TStrings* Value, const AnsiString Section, const AnsiString Named, const AnsiString FileName)/* overload */;
extern PACKAGE void __fastcall ReadIniStrings(Classes::TStrings* Value, const AnsiString Section, const AnsiString Named, Inifiles::TMemIniFile* r)/* overload */;
extern PACKAGE int __fastcall ReadIniInteger(const AnsiString Section, const AnsiString Named, int Value, AnsiString FileName)/* overload */;
extern PACKAGE int __fastcall ReadIniInteger(const AnsiString Section, const AnsiString Named, int Value, Inifiles::TMemIniFile* r)/* overload */;
extern PACKAGE AnsiString __fastcall ReadRegString(HKEY Key, const AnsiString Section, const AnsiString Named);
extern PACKAGE void __fastcall WriteRegString(HKEY Key, const AnsiString Section, const AnsiString Named, const AnsiString Value);
extern PACKAGE void __fastcall DeleteRegParam(HKEY Key, const AnsiString Section, const AnsiString Named);
extern PACKAGE void __fastcall WriteRegInteger(const AnsiString Section, const AnsiString Named, int Value);
extern PACKAGE void __fastcall WriteIniStr(const AnsiString Section, const AnsiString Named, const AnsiString Value, const AnsiString FileName)/* overload */;
extern PACKAGE void __fastcall WriteIniStr(const AnsiString Section, const AnsiString Named, const AnsiString Value, Inifiles::TMemIniFile* IniFile)/* overload */;
extern PACKAGE void __fastcall WriteIniStrings(const AnsiString Section, const AnsiString Named, const AnsiString FileName, Classes::TStrings* Value)/* overload */;
extern PACKAGE void __fastcall WriteIniStrings(const AnsiString Section, const AnsiString Named, Classes::TStrings* Value, Inifiles::TMemIniFile* IniFile)/* overload */;
extern PACKAGE void __fastcall WriteIniFont(const AnsiString Section, const AnsiString Named, Graphics::TFont* Value, Inifiles::TMemIniFile* IniFile)/* overload */;
extern PACKAGE void __fastcall ReadIniFont(const AnsiString Section, const AnsiString Named, Graphics::TFont* Value, Inifiles::TMemIniFile* IniFile)/* overload */;
extern PACKAGE void __fastcall ReadSection(Classes::TStringList* Src, Classes::TStringList* Dest, const AnsiString Name);
extern PACKAGE AnsiString __fastcall ReadValue(Classes::TStringList* Src, const AnsiString Section, const AnsiString ValueName);
extern PACKAGE void __fastcall SaveFormPlacement(Forms::TForm* Form, const AnsiString IniFileName);
extern PACKAGE void __fastcall RestoreFormPlacement(Forms::TForm* Form, const AnsiString IniFileName);

}	/* namespace Sstoreutils */
using namespace Sstoreutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sStoreUtils
