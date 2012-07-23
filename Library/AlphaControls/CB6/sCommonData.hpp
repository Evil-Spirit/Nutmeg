// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sCommonData.pas' rev: 6.00

#ifndef sCommonDataHPP
#define sCommonDataHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sLabel.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <acntUtils.hpp>	// Pascal unit
#include <sSkinManager.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Scommondata
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TsCommonData;
class PASCALIMPLEMENTATION TsCommonData : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	AnsiString FSkinSection;
	bool FCustomFont;
	bool FCustomColor;
	int FHUEOffset;
	int FSaturation;
	void __fastcall SetSkinSection(const AnsiString Value);
	bool __fastcall GetUpdating(void);
	void __fastcall SetUpdating(const bool Value);
	void __fastcall SetCustomColor(const bool Value);
	void __fastcall SetCustomFont(const bool Value);
	Sskinmanager::TsSkinManager* __fastcall GetSkinManager(void);
	void __fastcall SetSkinManager(const Sskinmanager::TsSkinManager* Value);
	void __fastcall SetHUEOffset(const int Value);
	void __fastcall SetSaturation(const int Value);
	
public:
	int GlowID;
	bool FUpdating;
	Sskinmanager::TsSkinManager* FSkinManager;
	int BorderIndex;
	int SkinIndex;
	int Texture;
	int HotTexture;
	void *GraphControl;
	bool UrgentPainting;
	bool BGChanged;
	bool HalfVisible;
	Controls::TControl* FOwnerControl;
	System::TObject* FOwnerObject;
	Graphics::TBitmap* FCacheBmp;
	HRGN FRegion;
	int COC;
	bool FFocused;
	bool FMouseAbove;
	Word CtrlSkinState;
	Word BGType;
	HDC PrintDC;
	#pragma pack(push, 1)
	Types::TRect InvalidRectH;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	Types::TRect InvalidRectV;
	#pragma pack(pop)
	
	__property bool Updating = {read=GetUpdating, write=SetUpdating, default=0};
	__fastcall TsCommonData(System::TObject* AOwner, bool CreateCacheBmp);
	__fastcall virtual ~TsCommonData(void);
	void __fastcall UpdateIndexes(void);
	void __fastcall Loaded(void);
	bool __fastcall RepaintIfMoved(void);
	bool __fastcall ManagerStored(void);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(bool Repaint = false);
	void __fastcall Invalidate(void);
	bool __fastcall Skinned(bool CheckSkinActive = false);
	__property int HUEOffset = {read=FHUEOffset, write=SetHUEOffset, default=0};
	__property int Saturation = {read=FSaturation, write=SetSaturation, default=0};
	
__published:
	__property bool CustomColor = {read=FCustomColor, write=SetCustomColor, default=0};
	__property bool CustomFont = {read=FCustomFont, write=SetCustomFont, default=0};
	__property Sskinmanager::TsSkinManager* SkinManager = {read=GetSkinManager, write=SetSkinManager, stored=ManagerStored};
	__property AnsiString SkinSection = {read=FSkinSection, write=SetSkinSection};
};


class DELPHICLASS TsCtrlSkinData;
class PASCALIMPLEMENTATION TsCtrlSkinData : public TsCommonData 
{
	typedef TsCommonData inherited;
	
__published:
	__property HUEOffset  = {default=0};
	__property Saturation  = {default=0};
public:
	#pragma option push -w-inl
	/* TsCommonData.Create */ inline __fastcall TsCtrlSkinData(System::TObject* AOwner, bool CreateCacheBmp) : TsCommonData(AOwner, CreateCacheBmp) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TsCommonData.Destroy */ inline __fastcall virtual ~TsCtrlSkinData(void) { }
	#pragma option pop
	
};


class DELPHICLASS TsBoundLabel;
class PASCALIMPLEMENTATION TsBoundLabel : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FMaxWidth;
	AnsiString FText;
	Sconst::TsCaptionLayout FLayout;
	Graphics::TFont* FFont;
	int FIndent;
	void __fastcall SetActive(const bool Value);
	void __fastcall SetLayout(const Sconst::TsCaptionLayout Value);
	void __fastcall SetMaxWidth(const int Value);
	void __fastcall SetText(const AnsiString Value);
	void __fastcall SetFont(const Graphics::TFont* Value);
	void __fastcall SetIndent(const int Value);
	Graphics::TFont* __fastcall GetFont(void);
	void __fastcall UpdateAlignment(void);
	bool __fastcall GetUseSkin(void);
	void __fastcall SetUseSkin(const bool Value);
	
public:
	bool FActive;
	Slabel::TsEditLabel* FTheLabel;
	TsCommonData* FCommonData;
	void __fastcall AlignLabel(void);
	__fastcall TsBoundLabel(System::TObject* AOwner, TsCommonData* CommonData);
	__fastcall virtual ~TsBoundLabel(void);
	
__published:
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property AnsiString Caption = {read=FText, write=SetText};
	__property int Indent = {read=FIndent, write=SetIndent, nodefault};
	__property Graphics::TFont* Font = {read=GetFont, write=SetFont};
	__property Sconst::TsCaptionLayout Layout = {read=FLayout, write=SetLayout, nodefault};
	__property int MaxWidth = {read=FMaxWidth, write=SetMaxWidth, nodefault};
	__property bool UseSkinColor = {read=GetUseSkin, write=SetUseSkin, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Sconst::TsColor C1;
extern PACKAGE Sconst::TsColor C2;
extern PACKAGE bool RestrictDrawing;
extern PACKAGE bool __fastcall IsCached(TsCommonData* SkinData);
extern PACKAGE bool __fastcall IsCacheRequired(TsCommonData* SkinData);
extern PACKAGE void __fastcall InitBGInfo(const TsCommonData* SkinData, const Sconst::PacBGInfo PBGInfo, const int State, unsigned Handle = (unsigned)(0x0));
extern PACKAGE Graphics::TColor __fastcall GetBGColor(const TsCommonData* SkinData, const int State, unsigned Handle = (unsigned)(0x0));
extern PACKAGE int __fastcall GetFontIndex(const Controls::TControl* Ctrl, const int DefSkinIndex, const Sskinmanager::TsSkinManager* SkinManager);
extern PACKAGE bool __fastcall ParentTextured(const TsCommonData* SkinData);
extern PACKAGE void __fastcall ShowGlowingIfNeeded(const TsCommonData* SkinData, bool Clicked = false, HWND CtrlHandle = (HWND)(0x0));
extern PACKAGE void __fastcall InitCacheBmp(TsCommonData* SkinData);
extern PACKAGE int __fastcall SkinBorderMaxWidth(TsCommonData* SkinData);
extern PACKAGE Sconst::TCacheInfo __fastcall GetParentCache(TsCommonData* SkinData);
extern PACKAGE Sconst::TCacheInfo __fastcall GetParentCacheHwnd(HWND cHwnd);
extern PACKAGE void __fastcall UpdateData(TsCommonData* SkinData);
extern PACKAGE void __fastcall UpdateSkinState(const TsCommonData* SkinData, bool UpdateChildren = true);
extern PACKAGE bool __fastcall ControlIsActive(TsCommonData* SkinData);
extern PACKAGE bool __fastcall BgIsTransparent(TsCommonData* CommonData);
extern PACKAGE void __fastcall AlignShadow(TsCommonData* SkinData);
extern PACKAGE bool __fastcall CommonMessage(Messages::TMessage &Message, TsCommonData* SkinData);
extern PACKAGE bool __fastcall CommonWndProc(Messages::TMessage &Message, TsCommonData* SkinData);
extern PACKAGE void __fastcall CopyWinControlCache(Controls::TWinControl* Control, TsCommonData* SkinData, const Types::TRect &SrcRect, const Types::TRect &DstRect, HDC DstDC, bool UpdateCorners, int OffsetX = 0x0, int OffsetY = 0x0)/* overload */;
extern PACKAGE void __fastcall CopyHwndCache(unsigned hwnd, TsCommonData* SkinData, const Types::TRect &SrcRect, const Types::TRect &DstRect, HDC DstDC, bool UpdateCorners, int OffsetX = 0x0, int OffsetY = 0x0)/* overload */;

}	/* namespace Scommondata */
using namespace Scommondata;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sCommonData
