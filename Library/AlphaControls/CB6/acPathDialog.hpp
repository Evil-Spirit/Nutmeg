// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acPathDialog.pas' rev: 6.00

#ifndef acPathDialogHPP
#define acPathDialogHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acAlphaImageList.hpp>	// Pascal unit
#include <sLabel.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <sScrollBox.hpp>	// Pascal unit
#include <sTreeView.hpp>	// Pascal unit
#include <sEdit.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <acShellCtrls.hpp>	// Pascal unit
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

namespace Acpathdialog
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPathDialogForm;
class PASCALIMPLEMENTATION TPathDialogForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Acshellctrls::TsShellTreeView* sShellTreeView1;
	Sbitbtn::TsBitBtn* sBitBtn1;
	Sbitbtn::TsBitBtn* sBitBtn2;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Sbitbtn::TsBitBtn* sBitBtn3;
	Sscrollbox::TsScrollBox* sScrollBox1;
	Slabel::TsLabel* sLabel1;
	Acalphaimagelist::TsAlphaImageList* ImageList1;
	void __fastcall sShellTreeView1Change(System::TObject* Sender, Comctrls::TTreeNode* Node);
	void __fastcall sBitBtn3Click(System::TObject* Sender);
	void __fastcall sBitBtn2Click(System::TObject* Sender);
	void __fastcall sBitBtn1Click(System::TObject* Sender);
	
public:
	void __fastcall InitLngCaptions(void);
	void __fastcall GenerateButtons(void);
	void __fastcall UpdateAnchors(void);
	void __fastcall BtnOnClick(System::TObject* Sender);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TPathDialogForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPathDialogForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPathDialogForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPathDialogForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TPathDialogForm* PathDialogForm;
extern PACKAGE int FLargeImages;

}	/* namespace Acpathdialog */
using namespace Acpathdialog;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acPathDialog
