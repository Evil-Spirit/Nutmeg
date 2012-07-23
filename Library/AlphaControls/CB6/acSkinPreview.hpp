// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acSkinPreview.pas' rev: 6.00

#ifndef acSkinPreviewHPP
#define acSkinPreviewHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sGroupBox.hpp>	// Pascal unit
#include <sCheckBox.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sEdit.hpp>	// Pascal unit
#include <sStatusBar.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sBitBtn.hpp>	// Pascal unit
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

namespace Acskinpreview
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFormSkinPreview;
class PASCALIMPLEMENTATION TFormSkinPreview : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Sedit::TsEdit* sEdit1;
	Sstatusbar::TsStatusBar* sStatusBar1;
	Spanel::TsPanel* sPanel1;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Sgroupbox::TsGroupBox* sGroupBox1;
	Scheckbox::TsCheckBox* sCheckBox1;
	Scheckbox::TsCheckBox* sCheckBox2;
	Spanel::TsPanel* sPanel2;
	Sbitbtn::TsBitBtn* sBitBtn1;
	Sbitbtn::TsBitBtn* sBitBtn2;
	Sskinmanager::TsSkinManager* PreviewManager;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TFormSkinPreview(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormSkinPreview(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormSkinPreview(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFormSkinPreview(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFormSkinPreview* FormSkinPreview;

}	/* namespace Acskinpreview */
using namespace Acskinpreview;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acSkinPreview
