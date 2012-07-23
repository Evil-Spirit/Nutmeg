// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acSelectSkin.pas' rev: 6.00

#ifndef acSelectSkinHPP
#define acSelectSkinHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sTooledit.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <sMaskEdit.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <sBitBtn.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <sListBox.hpp>	// Pascal unit
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

namespace Acselectskin
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFormSkinSelect;
class PASCALIMPLEMENTATION TFormSkinSelect : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Slistbox::TsListBox* sListBox1;
	Sbitbtn::TsBitBtn* sBitBtn1;
	Sbitbtn::TsBitBtn* sBitBtn2;
	Spanel::TsPanel* sPanel1;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Stooledit::TsDirectoryEdit* sDirectoryEdit1;
	void __fastcall sListBox1Click(System::TObject* Sender);
	void __fastcall sDirectoryEdit1Change(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall sListBox1DblClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	
public:
	AnsiString sName;
	Sskinmanager::TacSkinTypes SkinTypes;
	Sskinmanager::TacSkinPlaces SkinPlaces;
	Sskinmanager::TsSkinManager* SkinManager;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TFormSkinSelect(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormSkinSelect(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormSkinSelect(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFormSkinSelect(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFormSkinSelect* FormSkinSelect;
extern PACKAGE bool __fastcall SelectSkin(Sskinmanager::TsSkinManager* SkinManager, Sskinmanager::TacSkinPlaces SkinPlaces = (Sskinmanager::TacSkinPlaces)(0x2))/* overload */;
extern PACKAGE bool __fastcall SelectSkin(AnsiString &SkinName, AnsiString &SkinDir, Sskinmanager::TacSkinTypes SkinTypes = (Sskinmanager::TacSkinTypes)(0x2))/* overload */;
extern PACKAGE bool __fastcall SelectSkin(Classes::TStringList* NameList, AnsiString &SkinDir, Sskinmanager::TacSkinTypes SkinTypes = (Sskinmanager::TacSkinTypes)(0x2))/* overload */;

}	/* namespace Acselectskin */
using namespace Acselectskin;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acSelectSkin
