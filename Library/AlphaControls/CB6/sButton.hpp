// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sButton.pas' rev: 6.00

#ifndef sButtonHPP
#define sButtonHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ActnList.hpp>	// Pascal unit
#include <sFade.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
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

namespace Sbutton
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TButtonStyle { bsPushButton, bsCommandLink, bsSplitButton };
#pragma option pop

#pragma option push -b-
enum TImageAlignment { iaLeft, iaRight, iaTop, iaBottom, iaCenter };
#pragma option pop

class DELPHICLASS TImageMargins;
class PASCALIMPLEMENTATION TImageMargins : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FRight;
	int FBottom;
	int FTop;
	int FLeft;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetMargin(int Index, int Value);
	
protected:
	virtual void __fastcall Change(void);
	
public:
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property int Left = {read=FLeft, write=SetMargin, index=0, default=0};
	__property int Top = {read=FTop, write=SetMargin, index=1, default=0};
	__property int Right = {read=FRight, write=SetMargin, index=2, default=0};
	__property int Bottom = {read=FBottom, write=SetMargin, index=3, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TImageMargins(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TImageMargins(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TPushButtonActionLink;
class PASCALIMPLEMENTATION TPushButtonActionLink : public Stdctrls::TButtonActionLink 
{
	typedef Stdctrls::TButtonActionLink inherited;
	
protected:
	virtual bool __fastcall IsImageIndexLinked(void);
	virtual void __fastcall SetImageIndex(int Value);
public:
	#pragma option push -w-inl
	/* TBasicActionLink.Create */ inline __fastcall virtual TPushButtonActionLink(System::TObject* AClient) : Stdctrls::TButtonActionLink(AClient) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TBasicActionLink.Destroy */ inline __fastcall virtual ~TPushButtonActionLink(void) { }
	#pragma option pop
	
};


class DELPHICLASS TsButton;
class PASCALIMPLEMENTATION TsButton : public Stdctrls::TButton 
{
	typedef Stdctrls::TButton inherited;
	
private:
	Scommondata::TsCtrlSkinData* FCommonData;
	bool FMouseClicked;
	bool FDown;
	bool RegionChanged;
	int FFocusMargin;
	Sconst::TsDisabledKind FDisabledKind;
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseLeave;
	Sfade::TsFadeTimer* FadeTimer;
	Sconst::TacAnimatEvents FAnimatEvents;
	#pragma pack(push, 1)
	Types::TRect LastRect;
	#pragma pack(pop)
	
	bool FShowFocus;
	bool FReflected;
	TButtonStyle FStyle;
	int FContentMargin;
	AnsiString FCommandLinkHint;
	Imglist::TChangeLink* FImageChangeLink;
	Imglist::TCustomImageList* FImages;
	TImageAlignment FImageAlignment;
	Imglist::TImageIndex FSelectedImageIndex;
	Imglist::TImageIndex FDisabledImageIndex;
	Imglist::TImageIndex FHotImageIndex;
	Imglist::TImageIndex FImageIndex;
	Imglist::TImageIndex FPressedImageIndex;
	TImageMargins* FImageMargins;
	bool FWordWrap;
	void __fastcall SetWordWrap(const bool Value);
	void __fastcall SetDown(const bool Value);
	void __fastcall SetFocusMargin(const int Value);
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	HIDESBASE MESSAGE void __fastcall WMKeyUp(Messages::TWMKey &Message);
	MESSAGE void __fastcall CNMeasureItem(Messages::TWMMeasureItem &Message);
	bool __fastcall GetDown(void);
	void __fastcall SetShowFocus(const bool Value);
	void __fastcall SetReflected(const bool Value);
	MESSAGE void __fastcall CNDrawItem(Messages::TWMDrawItem &Message);
	void __fastcall SetStyle(const TButtonStyle Value);
	void __fastcall SetContentMargin(const int Value);
	void __fastcall ImageListChange(System::TObject* Sender);
	bool __fastcall IsImageIndexStored(void);
	void __fastcall SetCommandLinkHint(const AnsiString Value);
	void __fastcall SetDisabledImageIndex(const Imglist::TImageIndex Value);
	void __fastcall SetHotImageIndex(const Imglist::TImageIndex Value);
	void __fastcall SetImageAlignment(const TImageAlignment Value);
	void __fastcall SetImageIndex(const Imglist::TImageIndex Value);
	void __fastcall SetImageMargins(const TImageMargins* Value);
	void __fastcall SetImages(const Imglist::TCustomImageList* Value);
	void __fastcall SetPressedImageIndex(const Imglist::TImageIndex Value);
	void __fastcall SetSelectedImageIndex(const Imglist::TImageIndex Value);
	void __fastcall ImageMarginsChange(System::TObject* Sender);
	
protected:
	bool IsFocused;
	HRGN FRegion;
	void __fastcall StdDrawItem(const tagDRAWITEMSTRUCT &DrawItemStruct);
	virtual void __fastcall SetButtonStyle(bool ADefault);
	DYNAMIC void __fastcall ActionChange(System::TObject* Sender, bool CheckDefaults);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall OurPaintHandler(HDC aDC);
	DYNAMIC void __fastcall DrawCaption(Graphics::TCanvas* Canvas = (Graphics::TCanvas*)(0x0));
	DYNAMIC Types::TRect __fastcall CaptionRect();
	DYNAMIC void __fastcall DrawGlyph(Graphics::TCanvas* Canvas = (Graphics::TCanvas*)(0x0));
	bool __fastcall GlyphExist(void);
	void __fastcall PrepareCache(void);
	
public:
	bool Active;
	__fastcall virtual TsButton(Classes::TComponent* AOwner);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	int __fastcall CurrentState(void);
	int __fastcall GlyphIndex(void);
	Types::TRect __fastcall GlyphRect();
	__fastcall virtual ~TsButton(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
__published:
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Scommondata::TsCtrlSkinData* SkinData = {read=FCommonData, write=FCommonData};
	__property bool ShowFocus = {read=FShowFocus, write=SetShowFocus, default=1};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property bool Down = {read=GetDown, write=SetDown, default=0};
	__property int FocusMargin = {read=FFocusMargin, write=SetFocusMargin, default=1};
	__property AnsiString CommandLinkHint = {read=FCommandLinkHint, write=SetCommandLinkHint};
	__property Imglist::TImageIndex DisabledImageIndex = {read=FDisabledImageIndex, write=SetDisabledImageIndex, default=-1};
	__property Imglist::TImageIndex HotImageIndex = {read=FHotImageIndex, write=SetHotImageIndex, default=-1};
	__property Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property TImageAlignment ImageAlignment = {read=FImageAlignment, write=SetImageAlignment, default=0};
	__property Imglist::TImageIndex ImageIndex = {read=FImageIndex, write=SetImageIndex, stored=IsImageIndexStored, default=-1};
	__property TImageMargins* ImageMargins = {read=FImageMargins, write=SetImageMargins};
	__property Imglist::TImageIndex PressedImageIndex = {read=FPressedImageIndex, write=SetPressedImageIndex, default=-1};
	__property Imglist::TImageIndex SelectedImageIndex = {read=FSelectedImageIndex, write=SetSelectedImageIndex, default=-1};
	__property int ContentMargin = {read=FContentMargin, write=SetContentMargin, default=6};
	__property TButtonStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property bool Reflected = {read=FReflected, write=SetReflected, default=0};
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, default=1};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsButton(HWND ParentWindow) : Stdctrls::TButton(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sbutton */
using namespace Sbutton;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sButton
