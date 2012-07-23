// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sImgListEditor.pas' rev: 6.00

#ifndef sImgListEditorHPP
#define sImgListEditorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sButton.hpp>	// Pascal unit
#include <sBitBtn.hpp>	// Pascal unit
#include <sListView.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <acAlphaImageList.hpp>	// Pascal unit
#include <sSpeedButton.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <ExtDlgs.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ActnList.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Simglisteditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFormImgListEditor;
class PASCALIMPLEMENTATION TFormImgListEditor : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Sbitbtn::TsBitBtn* sBitBtn5;
	Sbitbtn::TsBitBtn* sBitBtn6;
	Sbitbtn::TsBitBtn* sBitBtn7;
	Acalphaimagelist::TsAlphaImageList* ImageList1;
	Extdlgs::TOpenPictureDialog* OpenPictureDialog1;
	Slistview::TsListView* ListView1;
	Sspeedbutton::TsSpeedButton* SpeedButton1;
	Sspeedbutton::TsSpeedButton* SpeedButton2;
	Sspeedbutton::TsSpeedButton* SpeedButton3;
	Sspeedbutton::TsSpeedButton* SpeedButton4;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Acalphaimagelist::TsAlphaImageList* sAlphaImageList1;
	Dialogs::TSaveDialog* SaveDialog1;
	Sspeedbutton::TsSpeedButton* SpeedButton5;
	Sspeedbutton::TsSpeedButton* SpeedButton6;
	void __fastcall ListView1DragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, Controls::TDragState State, bool &Accept);
	void __fastcall ListView1DragDrop(System::TObject* Sender, System::TObject* Source, int X, int Y);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall ListView1Click(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall SpeedButton2Click(System::TObject* Sender);
	void __fastcall SpeedButton3Click(System::TObject* Sender);
	void __fastcall sBitBtn5Click(System::TObject* Sender);
	void __fastcall sBitBtn6Click(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ListView1KeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	void __fastcall sBitBtn7Click(System::TObject* Sender);
	void __fastcall SpeedButton4Click(System::TObject* Sender);
	void __fastcall SpeedButton5Click(System::TObject* Sender);
	void __fastcall CheckScroll(System::TObject* Sender);
	void __fastcall SpeedButton6Click(System::TObject* Sender);
	
public:
	Acalphaimagelist::TsAlphaImageList* sImageList;
	MESSAGE void __fastcall WMDropFiles(Messages::TWMDropFiles &Msg);
	void __fastcall ListViewRefresh(void);
	void __fastcall InitFromImgList(Acalphaimagelist::TsAlphaImageList* ImgList);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TFormImgListEditor(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormImgListEditor(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormImgListEditor(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFormImgListEditor(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFormImgListEditor* FormImgListEditor;
extern PACKAGE Extctrls::TTimer* ScrollTimer;

}	/* namespace Simglisteditor */
using namespace Simglisteditor;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sImgListEditor
