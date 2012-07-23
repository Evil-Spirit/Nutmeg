// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sInternalSkins.pas' rev: 6.00

#ifndef sInternalSkinsHPP
#define sInternalSkinsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sListBox.hpp>	// Pascal unit
#include <sButton.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <ActnList.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <FileCtrl.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Sinternalskins
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFormInternalSkins;
class PASCALIMPLEMENTATION TFormInternalSkins : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Actnlist::TActionList* ActionList1;
	Actnlist::TAction* ActionAddNew;
	Actnlist::TAction* ActionDelete;
	Actnlist::TAction* ActionRename;
	Actnlist::TAction* ActionClose;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Slistbox::TsListBox* ListBox1;
	Sbutton::TsButton* sBitBtn1;
	Spanel::TsPanel* sPanel1;
	Sbutton::TsButton* sButton2;
	Sbutton::TsButton* sButton3;
	Sbutton::TsButton* sButton4;
	Sbutton::TsButton* sButton1;
	Sbutton::TsButton* sButton5;
	Actnlist::TAction* ActionClear;
	Actnlist::TAction* ActionExtract;
	void __fastcall ActionAddNewExecute(System::TObject* Sender);
	void __fastcall ActionCloseExecute(System::TObject* Sender);
	void __fastcall ActionRenameExecute(System::TObject* Sender);
	void __fastcall ActionDeleteExecute(System::TObject* Sender);
	void __fastcall ListBox1Click(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall ActionExtractExecute(System::TObject* Sender);
	void __fastcall ActionClearExecute(System::TObject* Sender);
	
public:
	AnsiString NewName;
	AnsiString NewDir;
	Sskinmanager::TsSkinManager* SkinManager;
	void __fastcall AddNewSkin(void);
	void __fastcall UpdateMyActions(void);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TFormInternalSkins(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormInternalSkins(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormInternalSkins(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFormInternalSkins(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFormInternalSkins* FormInternalSkins;

}	/* namespace Sinternalskins */
using namespace Sinternalskins;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sInternalSkins
