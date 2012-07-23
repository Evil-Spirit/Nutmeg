// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sSplitter.pas' rev: 6.00

#ifndef sSplitterHPP
#define sSplitterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
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

namespace Ssplitter
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsSplitter;
class PASCALIMPLEMENTATION TsSplitter : public Extctrls::TSplitter 
{
	typedef Extctrls::TSplitter inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	bool FSizing;
	Classes::TNotifyEvent FOnMouseLeave;
	Classes::TNotifyEvent FOnMouseEnter;
	Graphics::TBitmap* FGlyph;
	void __fastcall SetGlyph(const Graphics::TBitmap* Value);
	
protected:
	virtual void __fastcall Paint(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	
public:
	__fastcall virtual TsSplitter(Classes::TComponent* AOwner);
	__fastcall virtual ~TsSplitter(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	
__published:
	__property Enabled  = {default=1};
	__property Color  = {default=-2147483643};
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property ParentColor  = {default=1};
	__property Hint ;
	__property ParentShowHint  = {default=1};
	__property ShowHint ;
	__property Visible  = {default=1};
	__property Width  = {default=6};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property OnMouseUp ;
	__property OnResize ;
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Ssplitter */
using namespace Ssplitter;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sSplitter
