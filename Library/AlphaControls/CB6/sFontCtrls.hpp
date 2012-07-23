// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sFontCtrls.pas' rev: 6.00

#ifndef sFontCtrlsHPP
#define sFontCtrlsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <sComboBox.hpp>	// Pascal unit
#include <sListBox.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sfontctrls
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum FontTypes { PS, TTF, RASTER, UNKNOWN };
#pragma option pop

class DELPHICLASS TFontClass;
class PASCALIMPLEMENTATION TFontClass : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString FntName;
	FontTypes FntType;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TFontClass(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TFontClass(void) { }
	#pragma option pop
	
};


typedef DynamicArray<TFontClass* >  TFontsArray;

typedef Graphics::TBitmap* TBitmapArray[4];

#pragma option push -b-
enum TFilterOption { ShowTrueType, ShowPostScript, ShowRaster };
#pragma option pop

typedef Set<TFilterOption, ShowTrueType, ShowRaster>  TFilterOptions;

typedef void __fastcall (__closure *EValidateFont)(System::TObject* Sender, TFontClass* Font, bool &accept);

class DELPHICLASS TsFontListBox;
class PASCALIMPLEMENTATION TsFontListBox : public Slistbox::TsCustomListBox 
{
	typedef Slistbox::TsCustomListBox inherited;
	
private:
	TFilterOptions FFilterOptions;
	EValidateFont FOnValidateFont;
	bool FDrawFont;
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	void __fastcall SetDrawFont(const bool Value);
	
protected:
	void __fastcall SetFilterOptions(TFilterOptions Value);
	
public:
	__fastcall virtual TsFontListBox(Classes::TComponent* AOwner);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DrawItem(int Index, const Types::TRect &Rect, Windows::TOwnerDrawState State);
	virtual void __fastcall MeasureItem(int Index, int &Height);
	
__published:
	__property Align  = {default=0};
	__property BorderStyle  = {default=1};
	__property Color  = {default=-2147483643};
	__property Ctl3D ;
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property ExtendedSelect  = {default=1};
	__property Font ;
	__property IntegralHeight  = {default=0};
	__property ItemHeight ;
	__property Items  = {stored=false};
	__property MultiSelect  = {default=0};
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property Style  = {default=2};
	__property TabOrder  = {default=-1};
	__property TabWidth  = {default=0};
	__property Visible  = {default=1};
	__property EValidateFont OnValidateFont = {read=FOnValidateFont, write=FOnValidateFont};
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDrawItem ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMeasureItem ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property bool DrawFont = {read=FDrawFont, write=SetDrawFont, default=1};
	__property TFilterOptions FilterOptions = {read=FFilterOptions, write=SetFilterOptions, default=7};
public:
	#pragma option push -w-inl
	/* TsCustomListBox.Destroy */ inline __fastcall virtual ~TsFontListBox(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsFontListBox(HWND ParentWindow) : Slistbox::TsCustomListBox(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsFontComboBox;
class PASCALIMPLEMENTATION TsFontComboBox : public Scombobox::TsCustomComboBox 
{
	typedef Scombobox::TsCustomComboBox inherited;
	
private:
	TFilterOptions FFilterOptions;
	EValidateFont FOnValidateFont;
	bool FDrawFont;
	void __fastcall SetDrawFont(const bool Value);
	
protected:
	void __fastcall SetFilterOptions(TFilterOptions Value);
	HIDESBASE MESSAGE void __fastcall CNDrawItem(Messages::TWMDrawItem &Message);
	
public:
	__fastcall virtual TsFontComboBox(Classes::TComponent* AOwner);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DrawItem(int Index, const Types::TRect &Rect, Windows::TOwnerDrawState State);
	virtual void __fastcall MeasureItem(int Index, int &Height);
	__property Style  = {default=4};
	
__published:
	__property Align  = {default=0};
	__property Color  = {default=-2147483643};
	__property Ctl3D ;
	__property DragMode  = {default=0};
	__property DragCursor  = {default=-12};
	__property DropDownCount  = {default=16};
	__property Enabled  = {default=1};
	__property Font ;
	__property ItemHeight ;
	__property Items  = {stored=false};
	__property MaxLength  = {default=0};
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
	__property EValidateFont OnValidateFont = {read=FOnValidateFont, write=FOnValidateFont};
	__property OnChange ;
	__property OnClick ;
	__property OnCloseUp ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDrawItem ;
	__property OnDropDown ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMeasureItem ;
	__property OnStartDrag ;
	__property bool DrawFont = {read=FDrawFont, write=SetDrawFont, default=1};
	__property TFilterOptions FilterOptions = {read=FFilterOptions, write=SetFilterOptions, default=7};
public:
	#pragma option push -w-inl
	/* TsCustomComboBox.Destroy */ inline __fastcall virtual ~TsFontComboBox(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsFontComboBox(HWND ParentWindow) : Scombobox::TsCustomComboBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sfontctrls */
using namespace Sfontctrls;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sFontCtrls
