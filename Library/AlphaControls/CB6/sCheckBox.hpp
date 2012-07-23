// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCheckBox.pas' rev: 6.00

#ifndef sCheckBoxHPP
#define sCheckBoxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <sFade.hpp>	// Pascal unit
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

namespace Scheckbox
{
//-- type declarations -------------------------------------------------------
typedef int TsImageIndex;

class DELPHICLASS TsCheckBox;
class PASCALIMPLEMENTATION TsCheckBox : public Stdctrls::TCustomCheckBox 
{
	typedef Stdctrls::TCustomCheckBox inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	Sconst::TsDisabledKind FDisabledKind;
	Graphics::TBitmap* FGlyphUnChecked;
	Graphics::TBitmap* FGlyphChecked;
	int FTextIndent;
	bool FPressed;
	bool FShowFocus;
	int FMargin;
	Sfade::TsFadeTimer* FadeTimer;
	Imglist::TCustomImageList* FImages;
	int FImgChecked;
	int FImgUnchecked;
	Sconst::TacAnimatEvents FAnimatEvents;
	bool FWordWrap;
	void __fastcall SetWordWrap(const bool Value);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	void __fastcall SetGlyphChecked(const Graphics::TBitmap* Value);
	void __fastcall SetGlyphUnChecked(const Graphics::TBitmap* Value);
	void __fastcall SetTextIndent(const int Value);
	void __fastcall SetShowFocus(const bool Value);
	void __fastcall SetMargin(const int Value);
	void __fastcall SetReadOnly(const bool Value);
	void __fastcall SetImageChecked(const int Value);
	void __fastcall SetImages(const Imglist::TCustomImageList* Value);
	void __fastcall SetImageUnChecked(const int Value);
	
protected:
	bool FReadOnly;
	virtual bool __fastcall GetReadOnly(void);
	virtual bool __fastcall CanAutoSize(int &NewWidth, int &NewHeight);
	DYNAMIC void __fastcall ActionChange(System::TObject* Sender, bool CheckDefaults);
	virtual void __fastcall SetChecked(bool Value);
	HIDESBASE void __fastcall PaintHandler(const Messages::TWMPaint &M);
	void __fastcall PaintControl(HDC DC);
	void __fastcall DrawCheckText(void);
	void __fastcall DrawCheckArea(void);
	void __fastcall DrawSkinGlyph(int i);
	void __fastcall PaintGlyph(Graphics::TBitmap* Bmp, const int Index);
	int __fastcall SkinGlyphWidth(int i);
	int __fastcall SkinGlyphHeight(int i);
	Types::TRect __fastcall SkinCheckRect(int i);
	Graphics::TBitmap* __fastcall Glyph(void);
	Types::TRect __fastcall CheckRect();
	int __fastcall GlyphWidth(void);
	int __fastcall GlyphHeight(void);
	short __fastcall GlyphMaskIndex(Stdctrls::TCheckBoxState State);
	void __fastcall PrepareCache(void);
	
public:
	DYNAMIC Classes::TAlignment __fastcall GetControlsAlignment(void);
	virtual void __fastcall AfterConstruction(void);
	__fastcall virtual TsCheckBox(Classes::TComponent* AOwner);
	__fastcall virtual ~TsCheckBox(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Caption ;
	__property Action ;
	__property Align  = {default=0};
	__property Alignment  = {default=1};
	__property AllowGrayed  = {default=0};
	__property Anchors  = {default=3};
	__property AutoSize  = {default=1};
	__property BiDiMode ;
	__property Checked  = {default=0};
	__property Color  = {default=-2147483643};
	__property Constraints ;
	__property Ctl3D ;
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=1};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property State  = {default=0};
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property int Margin = {read=FMargin, write=SetMargin, default=2};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property Graphics::TBitmap* GlyphChecked = {read=FGlyphChecked, write=SetGlyphChecked};
	__property Graphics::TBitmap* GlyphUnChecked = {read=FGlyphUnChecked, write=SetGlyphUnChecked};
	__property int ImgChecked = {read=FImgChecked, write=SetImageChecked, nodefault};
	__property int ImgUnchecked = {read=FImgUnchecked, write=SetImageUnChecked, nodefault};
	__property Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, default=0};
	__property bool ShowFocus = {read=FShowFocus, write=SetShowFocus, default=1};
	__property int TextIndent = {read=FTextIndent, write=SetTextIndent, default=0};
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, default=0};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsCheckBox(HWND ParentWindow) : Stdctrls::TCustomCheckBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int PaintState;

}	/* namespace Scheckbox */
using namespace Scheckbox;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCheckBox
