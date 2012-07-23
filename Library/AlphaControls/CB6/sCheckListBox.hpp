// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCheckListBox.pas' rev: 6.00

#ifndef sCheckListBoxHPP
#define sCheckListBoxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sListBox.hpp>	// Pascal unit
#include <CheckLst.hpp>	// Pascal unit
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

namespace Schecklistbox
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsCheckListBox;
class PASCALIMPLEMENTATION TsCheckListBox : public Slistbox::TsListBox 
{
	typedef Slistbox::TsListBox inherited;
	
private:
	bool FAllowGrayed;
	Classes::TNotifyEvent FOnClickCheck;
	Classes::TList* FSaveStates;
	Graphics::TColor FHeaderColor;
	Graphics::TColor FHeaderBackgroundColor;
	AnsiString FHeaderSkin;
	void __fastcall DrawCheck(const Types::TRect &R, Stdctrls::TCheckBoxState AState, bool AEnabled, Graphics::TBitmap* Bmp, const Sconst::TCacheInfo &CI)/* overload */;
	void __fastcall DrawCheck(const Types::TRect &R, Stdctrls::TCheckBoxState AState, bool AEnabled, Graphics::TCanvas* C)/* overload */;
	void __fastcall SetChecked(int Index, bool Checked);
	bool __fastcall GetChecked(int Index);
	void __fastcall SetState(int Index, Stdctrls::TCheckBoxState AState);
	Stdctrls::TCheckBoxState __fastcall GetState(int Index);
	void __fastcall ToggleClickCheck(int Index);
	void __fastcall InvalidateCheck(int Index);
	System::TObject* __fastcall CreateWrapper(int Index);
	System::TObject* __fastcall ExtractWrapper(int Index);
	System::TObject* __fastcall GetWrapper(int Index);
	bool __fastcall HaveWrapper(int Index);
	HIDESBASE MESSAGE void __fastcall WMDestroy(Messages::TWMNoParams &Msg);
	bool __fastcall GetItemEnabled(int Index);
	void __fastcall SetItemEnabled(int Index, const bool Value);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMLButtonDblClick(Messages::TWMMouse &Message);
	bool __fastcall GetHeader(int Index);
	void __fastcall SetHeader(int Index, const bool Value);
	void __fastcall SetHeaderBackgroundColor(const Graphics::TColor Value);
	void __fastcall SetHeaderColor(const Graphics::TColor Value);
	void __fastcall SetHeaderSkin(const AnsiString Value);
	
protected:
	virtual void __fastcall DrawItem(int Index, const Types::TRect &Rect, Windows::TOwnerDrawState State);
	DYNAMIC int __fastcall InternalGetItemData(int Index);
	DYNAMIC void __fastcall InternalSetItemData(int Index, int AData);
	DYNAMIC void __fastcall SetItemData(int Index, int AData);
	DYNAMIC int __fastcall GetItemData(int Index);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	DYNAMIC void __fastcall KeyPress(char &Key);
	DYNAMIC void __fastcall ResetContent(void);
	DYNAMIC void __fastcall DeleteString(int Index);
	DYNAMIC void __fastcall ClickCheck(void);
	virtual void __fastcall DestroyWnd(void);
	int __fastcall GetCheckWidth(void);
	
public:
	__fastcall virtual TsCheckListBox(Classes::TComponent* AOwner);
	virtual void __fastcall CreateWnd(void);
	__fastcall virtual ~TsCheckListBox(void);
	__property bool Checked[int Index] = {read=GetChecked, write=SetChecked};
	__property bool ItemEnabled[int Index] = {read=GetItemEnabled, write=SetItemEnabled};
	__property Stdctrls::TCheckBoxState State[int Index] = {read=GetState, write=SetState};
	__property bool Header[int Index] = {read=GetHeader, write=SetHeader};
	
__published:
	__property Classes::TNotifyEvent OnClickCheck = {read=FOnClickCheck, write=FOnClickCheck};
	__property bool AllowGrayed = {read=FAllowGrayed, write=FAllowGrayed, default=0};
	__property Graphics::TColor HeaderColor = {read=FHeaderColor, write=SetHeaderColor, default=-2147483625};
	__property Graphics::TColor HeaderBackgroundColor = {read=FHeaderBackgroundColor, write=SetHeaderBackgroundColor, default=-2147483624};
	__property AnsiString HeaderSkin = {read=FHeaderSkin, write=SetHeaderSkin};
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property BiDiMode ;
	__property BorderStyle  = {default=0};
	__property Color  = {default=-2147483643};
	__property Columns  = {default=0};
	__property Constraints ;
	__property Ctl3D ;
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property ImeMode  = {default=3};
	__property ImeName ;
	__property IntegralHeight  = {default=0};
	__property ItemHeight ;
	__property Items ;
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property Sorted  = {default=0};
	__property Style  = {default=0};
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property TabWidth  = {default=0};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDrawItem ;
	__property OnEndDock ;
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
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCheckListBox(HWND ParentWindow) : Slistbox::TsListBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Schecklistbox */
using namespace Schecklistbox;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCheckListBox
