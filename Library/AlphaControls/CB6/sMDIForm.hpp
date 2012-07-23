// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sMDIForm.pas' rev: 6.00

#ifndef sMDIFormHPP
#define sMDIFormHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <acSBUtils.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
#include <sSkinProvider.hpp>	// Pascal unit
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

namespace Smdiform
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsMDIForm;
class PASCALIMPLEMENTATION TsMDIForm : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
public:
	Forms::TCustomForm* FForm;
	Acsbutils::TacScrollWnd* ListSW;
	Sskinprovider::TsSkinProvider* SkinProvider;
	void __fastcall ConnectToClient(void);
	__fastcall TsMDIForm(Classes::TPersistent* AOwner);
	__fastcall virtual ~TsMDIForm(void);
	Menus::TMenuItem* __fastcall MakeChildIconItem(void);
	void __fastcall UpdateMDIIconItem(void);
	void __fastcall RefreshMDIScrolls(void);
	void __fastcall DestroyScrolls(void);
	void __fastcall RestoreClick(System::TObject* Sender);
	void __fastcall MinClick(System::TObject* Sender);
	void __fastcall CloseClick(System::TObject* Sender);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Smdiform */
using namespace Smdiform;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sMDIForm
