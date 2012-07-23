// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acMagn.pas' rev: 6.00

#ifndef acMagnHPP
#define acMagnHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <acThumbForm.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acmagn
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TPosChangingEvent)(int &X, int &Y);

typedef Word TMagnSize;

#pragma option push -b-
enum TacSizingMode { asmNone, asmFreeAspectRatio, asmFixedAspectRatio };
#pragma option pop

#pragma option push -b-
enum TacMagnStyle { amsRectangle, amsLens };
#pragma option pop

class DELPHICLASS TsMagnifier;
class PASCALIMPLEMENTATION TsMagnifier : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FScaling;
	Menus::TPopupMenu* FPopupMenu;
	Controls::TMouseEvent FOnMouseUp;
	Controls::TMouseEvent FOnMouseDown;
	TPosChangingEvent FOnPosChanging;
	Classes::TNotifyEvent FOnDblClick;
	TMagnSize FHeight;
	TMagnSize FWidth;
	TacSizingMode FSizingMode;
	TacMagnStyle FStyle;
	void __fastcall SetScaling(const int Value);
	
public:
	bool IsModal;
	__fastcall virtual TsMagnifier(Classes::TComponent* AOwner);
	__fastcall virtual ~TsMagnifier(void);
	void __fastcall Execute(int x = 0xffffffff, int y = 0xffffffff);
	void __fastcall Hide(void);
	bool __fastcall IsVisible(void);
	Types::TPoint __fastcall GetPosition();
	void __fastcall Refresh(void);
	
__published:
	__property Menus::TPopupMenu* PopupMenu = {read=FPopupMenu, write=FPopupMenu};
	__property int Scaling = {read=FScaling, write=SetScaling, default=2};
	__property TMagnSize Width = {read=FWidth, write=FWidth, default=280};
	__property TMagnSize Height = {read=FHeight, write=FHeight, default=280};
	__property TacSizingMode SizingMode = {read=FSizingMode, write=FSizingMode, default=1};
	__property TacMagnStyle Style = {read=FStyle, write=FStyle, default=0};
	__property Classes::TNotifyEvent OnDblClick = {read=FOnDblClick, write=FOnDblClick};
	__property Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
	__property TPosChangingEvent OnPosChanging = {read=FOnPosChanging, write=FOnPosChanging};
};


class DELPHICLASS TacMagnForm;
class PASCALIMPLEMENTATION TacMagnForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Menus::TPopupMenu* PopupMenu1;
	Menus::TMenuItem* N1x1;
	Menus::TMenuItem* N2x1;
	Menus::TMenuItem* N8x1;
	Menus::TMenuItem* N1;
	Menus::TMenuItem* Close1;
	Menus::TMenuItem* N16x1;
	Extctrls::TTimer* Timer1;
	void __fastcall Close1Click(System::TObject* Sender);
	void __fastcall Zoom1x1Click(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	void __fastcall FormKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall Image1DblClick(System::TObject* Sender);
	void __fastcall Image1MouseMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall FormMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	
protected:
	bool IntUpdating;
	MESSAGE void __fastcall WMPosChanging(Messages::TWMWindowPosMsg &Message);
	HIDESBASE int __fastcall WMNCHitTest(Messages::TWMNCHitTest &Message);
	void __fastcall UpdateThumbPos(bool Full = true);
	Types::TRect __fastcall BordersWidth();
	void __fastcall MakeAeroMagnifier(void);
	
public:
	TsMagnifier* Caller;
	Acthumbform::TMagnifierOwner* MagnOwner;
	Graphics::TBitmap* FMaskBmp;
	Graphics::TBitmap* FTempBmp;
	Graphics::TBitmap* AlphaBmp;
	short Scale;
	Graphics::TBitmap* MagnBmp;
	void __fastcall UpdateAero(void);
	Types::TRect __fastcall ContentMargins();
	void __fastcall FormCreateInit(void);
	tagSIZE __fastcall MagnSize();
	Types::TRect __fastcall MClientRect();
	int __fastcall MinSize(void);
	__fastcall virtual ~TacMagnForm(void);
	void __fastcall EstablishAspectRatio(Word Side, Types::TRect &Rect);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall SetZooming(int k);
	void __fastcall ShowGlass(int x, int y);
	void __fastcall CreateAlphaBmp(void);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TacMagnForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TacMagnForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TacMagnForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word amMaxSize = 0x320;
static const Byte amMinSize = 0x96;
extern PACKAGE bool Closing;
extern PACKAGE bool Showed;
extern PACKAGE bool acIsDragging;

}	/* namespace Acmagn */
using namespace Acmagn;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acMagn
