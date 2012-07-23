// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sTreeView.pas' rev: 6.00

#ifndef sTreeViewHPP
#define sTreeViewHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acSBUtils.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
#include <sMessages.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
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

namespace Streeview
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsTreeView;
class PASCALIMPLEMENTATION TsTreeView : public Comctrls::TTreeView 
{
	typedef Comctrls::TTreeView inherited;
	
private:
	Scommondata::TsCtrlSkinData* FCommonData;
	Scommondata::TsBoundLabel* FBoundLabel;
	Comctrls::TTVAdvancedCustomDrawItemEvent FOldDrawItem;
	
protected:
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall Loaded(void);
	void __fastcall SkinCustomDrawItem(Comctrls::TCustomTreeView* Sender, Comctrls::TTreeNode* Node, Comctrls::TCustomDrawState State, Comctrls::TCustomDrawStage Stage, bool &PaintImages, bool &DefaultDraw);
	
public:
	Acsbutils::TacScrollWnd* ListSW;
	__fastcall virtual TsTreeView(Classes::TComponent* AOwner);
	__fastcall virtual ~TsTreeView(void);
	virtual void __fastcall AfterConstruction(void);
	
__published:
	__property Scommondata::TsBoundLabel* BoundLabel = {read=FBoundLabel, write=FBoundLabel};
	__property Scommondata::TsCtrlSkinData* SkinData = {read=FCommonData, write=FCommonData};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsTreeView(HWND ParentWindow) : Comctrls::TTreeView(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Comctrls::TTreeNode* __fastcall GetNodeByText(const Comctrls::TCustomTreeView* TreeView, const AnsiString s);

}	/* namespace Streeview */
using namespace Streeview;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sTreeView
