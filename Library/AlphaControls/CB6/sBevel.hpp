// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sBevel.pas' rev: 6.00

#ifndef sBevelHPP
#define sBevelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Sbevel
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsBevel;
class PASCALIMPLEMENTATION TsBevel : public Extctrls::TBevel 
{
	typedef Extctrls::TBevel inherited;
	
private:
	Scommondata::TsCommonData* FCommonData;
	
protected:
	Extctrls::TBevelStyle StoredBevel;
	Extctrls::TBevelShape StoredShape;
	virtual void __fastcall Paint(void);
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	
public:
	__fastcall virtual TsBevel(Classes::TComponent* AOwner);
	__fastcall virtual ~TsBevel(void);
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Invalidate(void);
	void __fastcall CheckSkinSection(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sbevel */
using namespace Sbevel;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sBevel
