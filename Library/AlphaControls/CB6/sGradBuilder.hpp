// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sGradBuilder.pas' rev: 6.00

#ifndef sGradBuilderHPP
#define sGradBuilderHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <sGroupBox.hpp>	// Pascal unit
#include <sSpeedButton.hpp>	// Pascal unit
#include <sColorSelect.hpp>	// Pascal unit
#include <sPageControl.hpp>	// Pascal unit
#include <sDialogs.hpp>	// Pascal unit
#include <sRadioButton.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sComboBox.hpp>	// Pascal unit
#include <sButton.hpp>	// Pascal unit
#include <sLabel.hpp>	// Pascal unit
#include <sPanel.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <sGradient.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
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

namespace Sgradbuilder
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TGradPoint;
class PASCALIMPLEMENTATION TGradPoint : public Extctrls::TPanel 
{
	typedef Extctrls::TPanel inherited;
	
public:
	int Number;
	__fastcall virtual TGradPoint(Classes::TComponent* AOwner);
public:
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TGradPoint(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TGradPoint(HWND ParentWindow) : Extctrls::TPanel(ParentWindow) { }
	#pragma option pop
	
};


typedef DynamicArray<TGradPoint* >  TPointArray;

class DELPHICLASS TGradBuilder;
class PASCALIMPLEMENTATION TGradBuilder : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Menus::TPopupMenu* PopupMenu1;
	Menus::TMenuItem* Changecolor1;
	Menus::TMenuItem* Delete1;
	Sskinprovider::TsSkinProvider* sSkinProvider1;
	Sbutton::TsButton* BitBtn1;
	Sbutton::TsButton* sButton1;
	Sbutton::TsButton* sButton2;
	Sradiobutton::TsRadioButton* sRadioButton1;
	Sradiobutton::TsRadioButton* sRadioButton2;
	Sradiobutton::TsRadioButton* sRadioButton3;
	Sgroupbox::TsGroupBox* sGroupBox1;
	Spanel::TsPanel* PaintPanel;
	Extctrls::TPaintBox* PaintBox1;
	Spanel::TsPanel* Panel2;
	Spanel::TsPanel* TemplatePanel;
	Sgroupbox::TsGroupBox* sGroupBox2;
	Spanel::TsPanel* sPanel1;
	Extctrls::TPaintBox* PaintBox2;
	Scolorselect::TsColorSelect* sColorSelect5;
	Scolorselect::TsColorSelect* sColorSelect3;
	Scolorselect::TsColorSelect* sColorSelect4;
	Scolorselect::TsColorSelect* sColorSelect2;
	Scolorselect::TsColorSelect* sColorSelect1;
	void __fastcall Panel2Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall TemplatePanelMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall TemplatePanelMouseMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall Changecolor1Click(System::TObject* Sender);
	void __fastcall PopupMenu1Popup(System::TObject* Sender);
	void __fastcall Delete1Click(System::TObject* Sender);
	void __fastcall PaintBox1Paint(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BitBtn1Click(System::TObject* Sender);
	void __fastcall TemplatePanelMouseUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall TemplatePanelDblClick(System::TObject* Sender);
	void __fastcall sButton1Click(System::TObject* Sender);
	void __fastcall sButton2Click(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	void __fastcall sRadioButton1Click(System::TObject* Sender);
	void __fastcall sColorSelect1Change(System::TObject* Sender);
	
private:
	int __fastcall GetDirection(void);
	void __fastcall SetDirection(const int Value);
	void __fastcall MakefirstPoints(void);
	void __fastcall InitTriangles(void);
	
public:
	DynamicArray<TGradPoint* >  a;
	DynamicArray<Sconst::TsGradPie >  g;
	TGradPoint* LastPoint;
	Controls::TModalResult ModalResult;
	DynamicArray<Sconst::TsGradPie >  CurrentArray;
	Dialogs::TColorDialog* ColorDialog1;
	AnsiString __fastcall AsString();
	void __fastcall LoadFromArray(Sconst::TsGradArray NewArray);
	void __fastcall ReCalcData(void);
	void __fastcall NewPoint(Spanel::TsPanel* Owner, int y, Graphics::TColor Color);
	void __fastcall DeleteFromArray(TGradPoint* p);
	void __fastcall Reinit(void);
	__property int Direction = {read=GetDirection, write=SetDirection, nodefault};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TGradBuilder(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGradBuilder(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGradBuilder(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TGradBuilder(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint PointHeight = 0x6;
extern PACKAGE TGradBuilder* GradBuilder;
extern PACKAGE bool NoMouse;
extern PACKAGE Dialogs::TColorDialog* ColorDialog;
extern PACKAGE void __fastcall CreateEditorForm(void)/* overload */;
extern PACKAGE void __fastcall CreateEditorForm(Dialogs::TColorDialog* CustomDlg)/* overload */;
extern PACKAGE void __fastcall KillForm(void);

}	/* namespace Sgradbuilder */
using namespace Sgradbuilder;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sGradBuilder
