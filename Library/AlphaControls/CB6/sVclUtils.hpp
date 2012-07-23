// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sVclUtils.pas' rev: 6.00

#ifndef sVclUtilsHPP
#define sVclUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Buttons.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
#include <sCheckBox.hpp>	// Pascal unit
#include <sMonthCalendar.hpp>	// Pascal unit
#include <sRadioButton.hpp>	// Pascal unit
#include <sCustomComboEdit.hpp>	// Pascal unit
#include <sDateUtils.hpp>	// Pascal unit
#include <sCurrEdit.hpp>	// Pascal unit
#include <sTooledit.hpp>	// Pascal unit
#include <sComboBox.hpp>	// Pascal unit
#include <sMemo.hpp>	// Pascal unit
#include <sEdit.hpp>	// Pascal unit
#include <acThdTimer.hpp>	// Pascal unit
#include <acDials.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <acSBUtils.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Svclutils
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TOutputWindow;
class PASCALIMPLEMENTATION TOutputWindow : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TWMEraseBkgnd &Message);
	
protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	
public:
	__fastcall virtual TOutputWindow(Classes::TComponent* AOwner);
	__property Canvas ;
public:
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TOutputWindow(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TOutputWindow(HWND ParentWindow) : Controls::TCustomControl(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TacHideTimer;
class PASCALIMPLEMENTATION TacHideTimer : public Acthdtimer::TacThreadedTimer 
{
	typedef Acthdtimer::TacThreadedTimer inherited;
	
public:
	Acdials::TacDialogWnd* Dlg;
	Sskinprovider::TsSkinProvider* sp;
	HDC DC;
	Forms::TForm* Form;
	#pragma pack(push, 1)
	tagSIZE FBmpSize;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TPoint FBmpTopLeft;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	_BLENDFUNCTION FBlend;
	#pragma pack(pop)
	
	double dx;
	double dy;
	double l;
	double t;
	double r;
	double b;
	int StartBlendValue;
	int i;
	int StepCount;
	Sconst::TacAnimType AnimType;
	int DelayValue;
	double Trans;
	double p;
	Graphics::TBitmap* SrcBmp;
	Graphics::TBitmap* DstBmp;
	void __fastcall Anim_Init(void);
	void __fastcall Anim_DoNext(void);
	void __fastcall Anim_GoToNext(void);
	void __fastcall OnTimerProc(System::TObject* Sender);
	__fastcall virtual ~TacHideTimer(void);
public:
	#pragma option push -w-inl
	/* TacThreadedTimer.Create */ inline __fastcall virtual TacHideTimer(Classes::TComponent* AOwner) : Acthdtimer::TacThreadedTimer(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacThreadedTimer.CreateOwned */ inline __fastcall virtual TacHideTimer(Classes::TComponent* AOwner, bool ChangeEvent) : Acthdtimer::TacThreadedTimer(AOwner, ChangeEvent) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int AlignToInt[3];
extern PACKAGE TOutputWindow* ow;
extern PACKAGE bool InAnimationProcess;
extern PACKAGE bool acGraphPainting;
extern PACKAGE unsigned uxthemeLib;
extern PACKAGE HRESULT __stdcall (*Ac_SetWindowTheme)(HWND hwnd, wchar_t * pszSubAppName, wchar_t * pszSubIdList);
extern PACKAGE TacHideTimer* acHideTimer;
extern PACKAGE Types::TPoint __fastcall acMousePos();
extern PACKAGE bool __fastcall LeftToRight(Controls::TControl* Control, bool NormalAlignment = true);
extern PACKAGE void __fastcall AddToAdapter(Controls::TWinControl* Frame);
extern PACKAGE void __fastcall BroadCastMsg(HWND Ctrl, const Messages::TMessage &Message);
extern PACKAGE void __fastcall SkinPaintTo(const Graphics::TBitmap* Bmp, const Controls::TControl* Ctrl, int Left = 0x0, int Top = 0x0, Classes::TComponent* SkinProvider = (Classes::TComponent*)(0x0));
extern PACKAGE void __fastcall AnimShowForm(Sskinprovider::TsSkinProvider* sp, Word wTime = (Word)(0x0), int MaxTransparency = 0xff, Sconst::TacAnimType AnimType = (Sconst::TacAnimType)(0x1));
extern PACKAGE void __fastcall AnimHideForm(System::TObject* SkinProvider);
extern PACKAGE void __fastcall PrindDlgClient(Acdials::TacDialogWnd* ListSW, Graphics::TBitmap* acDstBmp, bool CopyScreen = false);
extern PACKAGE void __fastcall AnimHideDlg(Acdials::TacDialogWnd* ListSW);
extern PACKAGE void __fastcall AnimShowDlg(Acdials::TacDialogWnd* ListSW, Word wTime = (Word)(0x0), int MaxTransparency = 0xff, Sconst::TacAnimType AnimType = (Sconst::TacAnimType)(0x1));
extern PACKAGE void __fastcall PrepareForAnimation(Controls::TWinControl* Ctrl);
extern PACKAGE void __fastcall AnimShowControl(Controls::TWinControl* Ctrl, Word wTime = (Word)(0x0), int MaxTransparency = 0xff, Sconst::TacAnimType AnimType = (Sconst::TacAnimType)(0x0));
extern PACKAGE void __fastcall SetParentUpdated(Controls::TWinControl* wc)/* overload */;
extern PACKAGE void __fastcall SetParentUpdated(HWND pHwnd)/* overload */;
extern PACKAGE Graphics::TColor __fastcall GetControlColor(Controls::TControl* Control)/* overload */;
extern PACKAGE Graphics::TColor __fastcall GetControlColor(unsigned Handle)/* overload */;
extern PACKAGE bool __fastcall AllEditSelected(Stdctrls::TCustomEdit* Ctrl);
extern PACKAGE Controls::TControl* __fastcall GetControlByName(Controls::TWinControl* ParentControl, const AnsiString CtrlName);
extern PACKAGE void __fastcall PaintControls(HDC DC, Controls::TWinControl* OwnerControl, bool ChangeCache, const Types::TPoint &Offset, unsigned AHandle = (unsigned)(0x0), bool CheckVisible = true);
extern PACKAGE int __fastcall SendAMessage(HWND Handle, int Cmd, int LParam = 0x0)/* overload */;
extern PACKAGE int __fastcall SendAMessage(Controls::TControl* Control, int Cmd, unsigned LParam = (unsigned)(0x0))/* overload */;
extern PACKAGE void __fastcall SetBoolMsg(HWND Handle, unsigned Cmd, bool Value);
extern PACKAGE bool __fastcall GetBoolMsg(Controls::TWinControl* Control, unsigned Cmd)/* overload */;
extern PACKAGE bool __fastcall GetBoolMsg(HWND CtrlHandle, unsigned Cmd)/* overload */;
extern PACKAGE void __fastcall RepaintsGraphicControls(Controls::TWinControl* WinControl);
extern PACKAGE bool __fastcall ControlIsReady(Controls::TControl* Control);
extern PACKAGE Forms::TCustomForm* __fastcall GetOwnerForm(Classes::TComponent* Component);
extern PACKAGE Forms::TCustomFrame* __fastcall GetOwnerFrame(Classes::TComponent* Component);
extern PACKAGE void __fastcall SetPanelFocus(Controls::TWinControl* Panel);
extern PACKAGE void __fastcall SetControlsEnabled(Controls::TWinControl* Parent, bool Value);
extern PACKAGE bool __fastcall CheckPanelFilled(Extctrls::TCustomPanel* Panel);
extern PACKAGE int __fastcall GetStringFlags(Controls::TControl* Control, Classes::TAlignment al);
extern PACKAGE void __fastcall RepaintsControls(Controls::TWinControl* Owner, bool BGChanged);
extern PACKAGE void __fastcall AlphaBroadCast(Controls::TWinControl* Control, void *Message)/* overload */;
extern PACKAGE void __fastcall AlphaBroadCast(HWND Handle, void *Message)/* overload */;
extern PACKAGE void __fastcall SendToProvider(Forms::TCustomForm* Form, void *Message);
extern PACKAGE int __fastcall GetCtrlRange(Controls::TWinControl* Ctl, int nBar);
extern PACKAGE Types::TRect __fastcall ACClientRect(HWND Handle);
extern PACKAGE void __fastcall TrySetSkinSection(Controls::TControl* Control, const AnsiString SectionName);
extern PACKAGE int __fastcall GetAlignShift(Controls::TWinControl* Ctrl, Controls::TAlign Align, bool GraphCtrlsToo = false);
extern PACKAGE HWND __fastcall GetParentFormHandle(const HWND CtrlHandle);

}	/* namespace Svclutils */
using namespace Svclutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sVclUtils
