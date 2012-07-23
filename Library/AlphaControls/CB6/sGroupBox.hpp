// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sGroupBox.pas' rev: 6.00

#ifndef sGroupBoxHPP
#define sGroupBoxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <sRadioButton.hpp>	// Pascal unit
#include <sCommonData.hpp>	// Pascal unit
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

namespace Sgroupbox
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TsCaptionLayout { clTopLeft, clTopCenter, clTopRight };
#pragma option pop

class DELPHICLASS TsGroupBox;
class PASCALIMPLEMENTATION TsGroupBox : public Stdctrls::TGroupBox 
{
	typedef Stdctrls::TGroupBox inherited;
	
private:
	TsCaptionLayout FCaptionLayout;
	int FCaptionYOffset;
	Scommondata::TsCommonData* FCommonData;
	AnsiString FCaptionSkin;
	void __fastcall SetCaptionLayout(const TsCaptionLayout Value);
	void __fastcall SetCaptionYOffset(const int Value);
	MESSAGE void __fastcall WMFontChanged(Messages::TMessage &Message);
	void __fastcall SetCaptionSkin(const AnsiString Value);
	
protected:
	virtual void __fastcall AdjustClientRect(Types::TRect &Rect);
	int __fastcall TextHeight(void);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	virtual void __fastcall AfterConstruction(void);
	virtual void __fastcall Loaded(void);
	Types::TRect __fastcall CaptionRect();
	__fastcall virtual TsGroupBox(Classes::TComponent* AOwner);
	__fastcall virtual ~TsGroupBox(void);
	virtual void __fastcall Paint(void);
	void __fastcall PaintToDC(HDC DC);
	void __fastcall PrepareCache(void);
	void __fastcall WriteText(const Types::TRect &R, const Sconst::TCacheInfo &CI);
	
__published:
	__property TsCaptionLayout CaptionLayout = {read=FCaptionLayout, write=SetCaptionLayout, default=0};
	__property int CaptionYOffset = {read=FCaptionYOffset, write=SetCaptionYOffset, default=0};
	__property Scommondata::TsCommonData* SkinData = {read=FCommonData, write=FCommonData};
	__property AnsiString CaptionSkin = {read=FCaptionSkin, write=SetCaptionSkin};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsGroupBox(HWND ParentWindow) : Stdctrls::TGroupBox(ParentWindow) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TacIndexChangingEvent)(System::TObject* Sender, int NewIndex, bool &AllowChange);

class DELPHICLASS TsRadioGroup;
class PASCALIMPLEMENTATION TsRadioGroup : public TsGroupBox 
{
	typedef TsGroupBox inherited;
	
private:
	TacIndexChangingEvent FOnChanging;
	Classes::TStrings* FItems;
	Sconst::TacAnimatEvents FAnimatEvents;
	int FItemIndex;
	int FColumns;
	bool FReading;
	bool FUpdating;
	void __fastcall ArrangeButtons(void);
	void __fastcall ButtonClick(System::TObject* Sender);
	void __fastcall ItemsChange(System::TObject* Sender);
	void __fastcall SetButtonCount(int Value);
	void __fastcall SetColumns(int Value);
	void __fastcall SetItemIndex(int Value);
	void __fastcall UpdateButtons(void);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	Sradiobutton::TsRadioButton* __fastcall GetButtons(int Index);
	void __fastcall SetItems(Classes::TStrings* Value);
	
protected:
	virtual void __fastcall ReadState(Classes::TReader* Reader);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	Classes::TList* FButtons;
	virtual void __fastcall Loaded(void);
	virtual bool __fastcall CanModify(int NewIndex);
	__fastcall virtual TsRadioGroup(Classes::TComponent* AOwner);
	__fastcall virtual ~TsRadioGroup(void);
	DYNAMIC void __fastcall FlipChildren(bool AllLevels);
	DYNAMIC void __fastcall GetChildren(Classes::TGetChildProc Proc, Classes::TComponent* Root);
	__property Sradiobutton::TsRadioButton* Buttons[int Index] = {read=GetButtons};
	
__published:
	__property Sconst::TacAnimatEvents AnimatEvents = {read=FAnimatEvents, write=FAnimatEvents, default=16};
	__property int Columns = {read=FColumns, write=SetColumns, default=1};
	__property int ItemIndex = {read=FItemIndex, write=SetItemIndex, default=-1};
	__property Classes::TStrings* Items = {read=FItems, write=SetItems};
	__property TacIndexChangingEvent OnChanging = {read=FOnChanging, write=FOnChanging};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsRadioGroup(HWND ParentWindow) : TsGroupBox(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Sgroupbox */
using namespace Sgroupbox;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sGroupBox
