// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sComboBoxes.pas' rev: 6.00

#ifndef sComboBoxesHPP
#define sComboBoxesHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <acSBUtils.hpp>	// Pascal unit
#include <sComboBox.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Scomboboxes
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsCustomComboBoxEx;
class PASCALIMPLEMENTATION TsCustomComboBoxEx : public Comctrls::TCustomComboBoxEx 
{
	typedef Comctrls::TCustomComboBoxEx inherited;
	
private:
	Sconst::TsDisabledKind FDisabledKind;
	Scommondata::TsCtrlSkinData* FCommonData;
	Scommondata::TsBoundLabel* FBoundLabel;
	bool FReadOnly;
	bool FShowButton;
	HWND ExHandle;
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	HIDESBASE virtual void __fastcall WMDrawItem(Messages::TWMDrawItem &Message);
	void __fastcall SetReadOnly(const bool Value);
	HIDESBASE void __fastcall WMPaint(Messages::TWMPaint &Message);
	void __fastcall SetShowButton(const bool Value);
	
protected:
	bool FDropDown;
	HWND lboxhandle;
	Acsbutils::TacScrollWnd* ListSW;
	int __fastcall BrdWidth(void);
	virtual bool __fastcall DrawSkinItem(int aIndex, const Types::TRect &aRect, Windows::TOwnerDrawState aState, HDC aDC);
	int __fastcall ButtonHeight(void);
	Types::TRect __fastcall ButtonRect();
	void __fastcall PaintButton(void);
	void __fastcall PrepareCache(void);
	virtual void __fastcall ComboWndProc(Messages::TMessage &Message, HWND ComboWnd, void * ComboProc);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	
public:
	__fastcall virtual TsCustomComboBoxEx(Classes::TComponent* AOwner);
	virtual void __fastcall CreateWnd(void);
	__fastcall virtual ~TsCustomComboBoxEx(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Scommondata::TsBoundLabel* BoundLabel = {read=FBoundLabel, write=FBoundLabel};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property bool ShowButton = {read=FShowButton, write=SetShowButton, default=1};
	__property Scommondata::TsCtrlSkinData* SkinData = {read=FCommonData, write=FCommonData};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCustomComboBoxEx(HWND ParentWindow) : Comctrls::TCustomComboBoxEx(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsComboBoxEx;
class PASCALIMPLEMENTATION TsComboBoxEx : public TsCustomComboBoxEx 
{
	typedef TsCustomComboBoxEx inherited;
	
__published:
	__property ItemsEx ;
	__property Style  = {default=0};
	__property StyleEx ;
	__property Action ;
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property BiDiMode ;
	__property Color  = {default=-2147483643};
	__property Constraints ;
	__property Ctl3D ;
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property ImeMode  = {default=3};
	__property ImeName ;
	__property ItemHeight ;
	__property MaxLength  = {default=0};
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Text ;
	__property Visible  = {default=1};
	__property OnBeginEdit ;
	__property OnChange ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDropDown ;
	__property OnEndEdit ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnSelect ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property Images ;
	__property DropDownCount ;
public:
	#pragma option push -w-inl
	/* TsCustomComboBoxEx.Create */ inline __fastcall virtual TsComboBoxEx(Classes::TComponent* AOwner) : TsCustomComboBoxEx(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsCustomComboBoxEx.Destroy */ inline __fastcall virtual ~TsComboBoxEx(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsComboBoxEx(HWND ParentWindow) : TsCustomComboBoxEx(ParentWindow) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TsColorBoxStyles { cbStandardColors, cbExtendedColors, cbSystemColors, cbIncludeNone, cbIncludeDefault, cbCustomColor, cbPrettyNames, cbCustomColors, cbSavedColors };
#pragma option pop

typedef Set<TsColorBoxStyles, cbStandardColors, cbSavedColors>  TsColorBoxStyle;

class DELPHICLASS TsCustomColorBox;
typedef void __fastcall (__closure *TGetColorsEvent)(TsCustomColorBox* Sender, Classes::TStrings* Items);

class PASCALIMPLEMENTATION TsCustomColorBox : public TsCustomComboBoxEx 
{
	typedef TsCustomComboBoxEx inherited;
	
private:
	TsColorBoxStyle FStyle;
	bool FNeedToPopulate;
	bool FListSelected;
	Graphics::TColor FDefaultColorColor;
	Graphics::TColor FNoneColorColor;
	Graphics::TColor FSelectedColor;
	bool FShowColorName;
	int FMargin;
	TGetColorsEvent FOnGetColors;
	Graphics::TColor __fastcall GetColor(int Index);
	AnsiString __fastcall GetColorName(int Index);
	Graphics::TColor __fastcall GetSelected(void);
	void __fastcall SetSelected(const Graphics::TColor AColor);
	void __fastcall ColorCallBack(const AnsiString AName);
	void __fastcall SetDefaultColorColor(const Graphics::TColor Value);
	void __fastcall SetNoneColorColor(const Graphics::TColor Value);
	void __fastcall SetShowColorName(const bool Value);
	void __fastcall SetMargin(const int Value);
	virtual void __fastcall WMDrawItem(Messages::TWMDrawItem &Message);
	
protected:
	DYNAMIC void __fastcall CloseUp(void);
	Types::TRect __fastcall ColorRect(const Types::TRect &SourceRect, Windows::TOwnerDrawState State);
	virtual bool __fastcall DrawSkinItem(int aIndex, const Types::TRect &aRect, Windows::TOwnerDrawState aState, HDC aDC);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(char &Key);
	virtual bool __fastcall PickCustomColor(void);
	void __fastcall PopulateList(void);
	DYNAMIC void __fastcall Select(void);
	HIDESBASE void __fastcall SetStyle(TsColorBoxStyle AStyle);
	
public:
	__fastcall virtual TsCustomColorBox(Classes::TComponent* AOwner);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall CreateWnd(void);
	__property AnsiString ColorNames[int Index] = {read=GetColorName};
	__property Graphics::TColor Colors[int Index] = {read=GetColor};
	
__published:
	__property TsColorBoxStyle Style = {read=FStyle, write=SetStyle, default=7};
	__property int Margin = {read=FMargin, write=SetMargin, default=0};
	__property Graphics::TColor Selected = {read=GetSelected, write=SetSelected, default=0};
	__property bool ShowColorName = {read=FShowColorName, write=SetShowColorName, default=1};
	__property Graphics::TColor DefaultColorColor = {read=FDefaultColorColor, write=SetDefaultColorColor, default=0};
	__property Graphics::TColor NoneColorColor = {read=FNoneColorColor, write=SetNoneColorColor, default=0};
	__property TGetColorsEvent OnGetColors = {read=FOnGetColors, write=FOnGetColors};
public:
	#pragma option push -w-inl
	/* TsCustomComboBoxEx.Destroy */ inline __fastcall virtual ~TsCustomColorBox(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCustomColorBox(HWND ParentWindow) : TsCustomComboBoxEx(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsColorBox;
class PASCALIMPLEMENTATION TsColorBox : public TsCustomColorBox 
{
	typedef TsCustomColorBox inherited;
	
__published:
	__property DisabledKind  = {default=1};
	__property Anchors  = {default=3};
	__property BevelEdges  = {default=15};
	__property BevelInner  = {index=0, default=2};
	__property BevelKind  = {default=0};
	__property BevelOuter  = {index=1, default=1};
	__property BiDiMode ;
	__property Color  = {default=-2147483643};
	__property Constraints ;
	__property Ctl3D ;
	__property DropDownCount ;
	__property Enabled  = {default=1};
	__property Font ;
	__property ItemHeight ;
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property OnChange ;
	__property OnCloseUp ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDropDown ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnSelect ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property Style  = {default=7};
	__property Margin  = {default=0};
	__property Selected  = {default=0};
	__property ShowColorName  = {default=1};
	__property DefaultColorColor  = {default=0};
	__property NoneColorColor  = {default=0};
	__property SkinData ;
public:
	#pragma option push -w-inl
	/* TsCustomColorBox.Create */ inline __fastcall virtual TsColorBox(Classes::TComponent* AOwner) : TsCustomColorBox(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TsCustomComboBoxEx.Destroy */ inline __fastcall virtual ~TsColorBox(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsColorBox(HWND ParentWindow) : TsCustomColorBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Dialogs::TColorDialog* ColDlg;

}	/* namespace Scomboboxes */
using namespace Scomboboxes;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sComboBoxes
