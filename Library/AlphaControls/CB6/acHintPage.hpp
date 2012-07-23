// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acHintPage.pas' rev: 6.00

#ifndef acHintPageHPP
#define acHintPageHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sPanel.hpp>	// Pascal unit
#include <ExtDlgs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <acAlphaHints.hpp>	// Pascal unit
#include <sGroupBox.hpp>	// Pascal unit
#include <sRadioButton.hpp>	// Pascal unit
#include <sTrackBar.hpp>	// Pascal unit
#include <sLabel.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <sFrameAdapter.hpp>	// Pascal unit
#include <sPageControl.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <sSpeedButton.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <sScrollBox.hpp>	// Pascal unit
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

namespace Achintpage
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrameHintPage;
class PASCALIMPLEMENTATION TFrameHintPage : public Forms::TFrame 
{
	typedef Forms::TFrame inherited;
	
__published:
	Sscrollbox::TsScrollBox* sScrollBox1;
	Sframeadapter::TsFrameAdapter* sFrameAdapter1;
	Extctrls::TPaintBox* PaintBox1;
	Sgroupbox::TsGroupBox* sGroupBox1;
	Sspeedbutton::TsSpeedButton* sSpeedButton3;
	Slabel::TsLabel* sLabel21;
	Slabel::TsLabel* sLabel22;
	Slabel::TsLabel* sLabel23;
	Slabel::TsLabel* sLabel24;
	Extdlgs::TOpenPictureDialog* OpenPictureDialog1;
	Sgroupbox::TsGroupBox* sGroupBox2;
	Strackbar::TsTrackBar* sTrackBar1;
	Strackbar::TsTrackBar* sTrackBar4;
	Strackbar::TsTrackBar* sTrackBar6;
	Strackbar::TsTrackBar* sTrackBar8;
	Slabel::TsLabel* sLabel14;
	Slabel::TsLabel* sLabel19;
	Slabel::TsLabel* sLabel2;
	Slabel::TsLabel* sLabel9;
	Sgroupbox::TsGroupBox* sGroupBox3;
	Strackbar::TsTrackBar* sTrackBar2;
	Strackbar::TsTrackBar* sTrackBar3;
	Strackbar::TsTrackBar* sTrackBar5;
	Strackbar::TsTrackBar* sTrackBar7;
	Slabel::TsLabel* sLabel4;
	Slabel::TsLabel* sLabel10;
	Slabel::TsLabel* sLabel15;
	Slabel::TsLabel* sLabel20;
	Sgroupbox::TsGroupBox* sGroupBox4;
	Spanel::TsPanel* sGroupBox5;
	Sradiobutton::TsRadioButton* sRadioButton1;
	Sradiobutton::TsRadioButton* sRadioButton2;
	Spanel::TsPanel* sGroupBox6;
	Sradiobutton::TsRadioButton* sRadioButton3;
	Sradiobutton::TsRadioButton* sRadioButton4;
	Slabel::TsLabel* sLabel26;
	Slabel::TsLabel* sLabel27;
	Slabel::TsLabel* sLabel28;
	Slabel::TsLabel* sLabel29;
	Slabel::TsLabel* sLabel30;
	Slabel::TsLabel* sLabel31;
	Slabel::TsLabel* sLabel32;
	Slabel::TsLabel* sLabel33;
	Spanel::TsPanel* sPanel1;
	Spanel::TsPanel* sPanel2;
	Sradiobutton::TsRadioButton* sRadioButton5;
	Sradiobutton::TsRadioButton* sRadioButton6;
	Slabel::TsLabel* sLabel34;
	Slabel::TsLabel* sLabel35;
	Slabel::TsLabel* sLabel36;
	Slabel::TsLabel* sLabel37;
	Sradiobutton::TsRadioButton* sRadioButton7;
	Sradiobutton::TsRadioButton* sRadioButton8;
	Spanel::TsPanel* sPanel3;
	Sradiobutton::TsRadioButton* sRadioButton9;
	Sradiobutton::TsRadioButton* sRadioButton10;
	Slabel::TsLabel* sLabel38;
	void __fastcall sTrackBar1Change(System::TObject* Sender);
	void __fastcall sTrackBar2Change(System::TObject* Sender);
	void __fastcall sTrackBar4Change(System::TObject* Sender);
	void __fastcall sTrackBar3Change(System::TObject* Sender);
	void __fastcall sTrackBar6Change(System::TObject* Sender);
	void __fastcall sTrackBar5Change(System::TObject* Sender);
	void __fastcall sTrackBar8Change(System::TObject* Sender);
	void __fastcall sTrackBar7Change(System::TObject* Sender);
	void __fastcall PaintBox1Paint(System::TObject* Sender);
	void __fastcall sSpeedButton3Click(System::TObject* Sender);
	void __fastcall sRadioButton1Click(System::TObject* Sender);
	void __fastcall sRadioButton2Click(System::TObject* Sender);
	void __fastcall sRadioButton3Click(System::TObject* Sender);
	void __fastcall sRadioButton4Click(System::TObject* Sender);
	void __fastcall sRadioButton5Click(System::TObject* Sender);
	void __fastcall sRadioButton6Click(System::TObject* Sender);
	void __fastcall sRadioButton7Click(System::TObject* Sender);
	void __fastcall sRadioButton8Click(System::TObject* Sender);
	void __fastcall sRadioButton9Click(System::TObject* Sender);
	void __fastcall sRadioButton10Click(System::TObject* Sender);
	
public:
	Acalphahints::TacHintImage* Image;
	void __fastcall LoadImage(Acalphahints::TacHintImage* Img, bool Repaint = true);
	void __fastcall UnloadImage(void);
	Graphics::TBitmap* __fastcall CreatePreviewBmp(const int Width, const int Height);
	Graphics::TBitmap* __fastcall CreateAlphaBmp(void);
	void __fastcall UpdateData(bool Repaint = true);
	void __fastcall RefreshPaintBox(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
public:
	#pragma option push -w-inl
	/* TCustomFrame.Create */ inline __fastcall virtual TFrameHintPage(Classes::TComponent* AOwner) : Forms::TFrame(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TFrameHintPage(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TFrameHintPage(HWND ParentWindow) : Forms::TFrame(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool acUpdating;

}	/* namespace Achintpage */
using namespace Achintpage;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acHintPage
