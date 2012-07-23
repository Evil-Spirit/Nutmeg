// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sTrackBar.pas' rev: 6.00

#ifndef sTrackBarHPP
#define sTrackBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sFade.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <sDefaults.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sGraphUtils.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Consts.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
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

namespace Strackbar
{
//-- type declarations -------------------------------------------------------
typedef DynamicArray<Types::TPoint >  TAPoint;

class DELPHICLASS TsTrackBar;
class PASCALIMPLEMENTATION TsTrackBar : public Comctrls::TTrackBar 
{
	typedef Comctrls::TTrackBar inherited;
	
private:
	Sconst::TsDisabledKind FDisabledKind;
	Classes::TNotifyEvent FOnUserChange;
	Scommondata::TsCommonData* FCommonData;
	Graphics::TCanvas* FCanvas;
	Sconst::TacAnimatEvents FAnimatEvents;
	Sfade::TsFadeTimer* FadeTimer;
	bool FShowFocus;
	Sconst::TPaintEvent FOnSkinPaint;
	Graphics::TBitmap* FThumbGlyph;
	void __fastcall SetDisabledKind(const Sconst::TsDisabledKind Value);
	void __fastcall SetShowFocus(const bool Value);
	void __fastcall SetThumbGlyph(const Graphics::TBitmap* Value);
	
protected:
	bool AppShowHint;
	virtual void __fastcall PaintWindow(HDC DC);
	__property Graphics::TCanvas* Canvas = {read=FCanvas};
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall UserChanged(void);
	
public:
	int TickHeight;
	double iStep;
	Graphics::TBitmap* Thumb;
	int TrackBarNdx;
	void __fastcall PaintBody(void);
	virtual void __fastcall PaintBar(void);
	void __fastcall PaintTicksHor(void);
	void __fastcall PaintTicksVer(void);
	void __fastcall PaintTick(const Types::TPoint &P, bool Horz);
	void __fastcall PaintThumb(int i);
	Types::TRect __fastcall ThumbRect();
	Types::TRect __fastcall ChannelRect();
	int __fastcall TickPos(int i);
	int __fastcall TickCount(void);
	TAPoint __fastcall TicksArray();
	__fastcall virtual TsTrackBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TsTrackBar(void);
	void __fastcall Paint(void);
	void __fastcall PrepareCache(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	int __fastcall Mode(void);
	
__published:
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property ThumbLength  = {default=23};
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property Sconst::TsDisabledKind DisabledKind = {read=FDisabledKind, write=SetDisabledKind, default=1};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property bool ShowFocus = {read=FShowFocus, write=SetShowFocus, default=0};
	__property Graphics::TBitmap* ThumbGlyph = {read=FThumbGlyph, write=SetThumbGlyph};
	__property Classes::TNotifyEvent OnUserChange = {read=FOnUserChange, write=FOnUserChange};
	__property Sconst::TPaintEvent OnSkinPaint = {read=FOnSkinPaint, write=FOnSkinPaint};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsTrackBar(HWND ParentWindow) : Comctrls::TTrackBar(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Strackbar */
using namespace Strackbar;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sTrackBar
