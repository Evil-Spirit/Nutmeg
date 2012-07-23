// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sPanel.pas' rev: 6.00

#ifndef sPanelHPP
#define sPanelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
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

namespace Spanel
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsPanel;
class PASCALIMPLEMENTATION TsPanel : public Extctrls::TPanel 
{
	typedef Extctrls::TPanel inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	Sconst::TPaintEvent FOnPaint;
	Classes::TNotifyEvent FOnMouseLeave;
	Classes::TNotifyEvent FOnMouseEnter;
	
public:
	__fastcall virtual TsPanel(Classes::TComponent* AOwner);
	__fastcall virtual ~TsPanel(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Paint(void);
	virtual void __fastcall OurPaint(HDC DC = (HDC)(0x0), bool SendUpdated = true);
	void __fastcall PrepareCache(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	virtual void __fastcall WriteText(const Types::TRect &R, Graphics::TCanvas* aCanvas = (Graphics::TCanvas*)(0x0), HDC aDC = (HDC)(0x0));
	virtual void __fastcall PaintWindow(HDC DC);
	
__published:
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property Sconst::TPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsPanel(HWND ParentWindow) : Extctrls::TPanel(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsDragBar;
class PASCALIMPLEMENTATION TsDragBar : public TsPanel 
{
	typedef TsPanel inherited;
	
private:
	Controls::TControl* FDraggedControl;
	MESSAGE void __fastcall WMActivateApp(Messages::TWMActivateApp &Message);
	
protected:
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	
public:
	virtual void __fastcall ReadState(Classes::TReader* Reader);
	__fastcall virtual TsDragBar(Classes::TComponent* AOwner);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Alignment  = {default=2};
	__property Align  = {default=1};
	__property Color  = {default=-2147483646};
	__property Controls::TControl* DraggedControl = {read=FDraggedControl, write=FDraggedControl};
public:
	#pragma option push -w-inl
	/* TsPanel.Destroy */ inline __fastcall virtual ~TsDragBar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsDragBar(HWND ParentWindow) : TsPanel(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsContainer;
class PASCALIMPLEMENTATION TsContainer : public TsPanel 
{
	typedef TsPanel inherited;
	
public:
	#pragma option push -w-inl
	/* TsPanel.Create */ inline __fastcall virtual TsContainer(Classes::TComponent* AOwner) : TsPanel(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsPanel.Destroy */ inline __fastcall virtual ~TsContainer(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsContainer(HWND ParentWindow) : TsPanel(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsGrip;
class PASCALIMPLEMENTATION TsGrip : public TsPanel 
{
	typedef TsPanel inherited;
	
public:
	bool Transparent;
	Controls::TWinControl* LinkedControl;
	__fastcall virtual TsGrip(Classes::TComponent* AOwner);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:
	#pragma option push -w-inl
	/* TsPanel.Destroy */ inline __fastcall virtual ~TsGrip(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsGrip(HWND ParentWindow) : TsPanel(ParentWindow) { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TsColInfo
{
	int Index;
	Graphics::TColor Color;
	Types::TRect R;
	bool Selected;
} ;
#pragma pack(pop)

typedef DynamicArray<TsColInfo >  sPanel__6;

class DELPHICLASS TsColorsPanel;
class PASCALIMPLEMENTATION TsColorsPanel : public TsPanel 
{
	typedef TsPanel inherited;
	
private:
	Classes::TStrings* FColors;
	int FItemIndex;
	int FItemWidth;
	int FItemHeight;
	int FItemMargin;
	int FColCount;
	int FRowCount;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetColors(const Classes::TStrings* Value);
	void __fastcall SetItemIndex(const int Value);
	void __fastcall SetItemHeight(const int Value);
	void __fastcall SetItemWidth(const int Value);
	void __fastcall SetItemMargin(const int Value);
	void __fastcall SetColCount(const int Value);
	void __fastcall SetRowCount(const int Value);
	
public:
	int OldSelected;
	DynamicArray<TsColInfo >  ColorsArray;
	__fastcall virtual TsColorsPanel(Classes::TComponent* AOwner);
	__fastcall virtual ~TsColorsPanel(void);
	void __fastcall GenerateColors(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall OurPaint(HDC DC = (HDC)(0x0), bool SendUpdated = true);
	void __fastcall PaintColors(const HDC DC);
	int __fastcall Count(void);
	int __fastcall GetItemByCoord(const Types::TPoint &p);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	Graphics::TColor __fastcall ColorValue(void);
	
__published:
	__property int ColCount = {read=FColCount, write=SetColCount, default=5};
	__property Classes::TStrings* Colors = {read=FColors, write=SetColors};
	__property int ItemIndex = {read=FItemIndex, write=SetItemIndex, default=-1};
	__property int ItemHeight = {read=FItemHeight, write=SetItemHeight, default=21};
	__property int ItemWidth = {read=FItemWidth, write=SetItemWidth, default=21};
	__property int ItemMargin = {read=FItemMargin, write=SetItemMargin, default=6};
	__property Height  = {default=60};
	__property int RowCount = {read=FRowCount, write=SetRowCount, default=2};
	__property Width  = {default=140};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsColorsPanel(HWND ParentWindow) : TsPanel(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsStdColorsPanel;
class PASCALIMPLEMENTATION TsStdColorsPanel : public TsColorsPanel 
{
	typedef TsColorsPanel inherited;
	
public:
	#pragma option push -w-inl
	/* TsColorsPanel.Create */ inline __fastcall virtual TsStdColorsPanel(Classes::TComponent* AOwner) : TsColorsPanel(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsColorsPanel.Destroy */ inline __fastcall virtual ~TsStdColorsPanel(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsStdColorsPanel(HWND ParentWindow) : TsColorsPanel(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Spanel */
using namespace Spanel;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sPanel
