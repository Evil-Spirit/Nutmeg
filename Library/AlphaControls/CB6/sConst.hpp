// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sConst.pas' rev: 6.00

#ifndef sConstHPP
#define sConstHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Dialogs.hpp>	// Pascal unit
#include <Consts.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sconst
{
//-- type declarations -------------------------------------------------------
typedef AnsiString ACString;

typedef char ACChar;

typedef char *PACChar;

typedef char OldChar;

typedef char *POldChar;

typedef AnsiString OldString;

typedef AnsiString *POldString;

typedef AnsiString *PACString;

typedef DynamicArray<Types::TRect >  TAOR;

typedef void __fastcall (__closure *TPaintEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas);

typedef void __fastcall (__closure *TBmpPaintEvent)(System::TObject* Sender, Graphics::TBitmap* Bmp);

typedef AnsiString TsSkinName;

typedef AnsiString TsDirectory;

typedef AnsiString TsSkinSection;

typedef AnsiString TacRoot;

typedef AnsiString TacStrValue;

#pragma option push -b-
enum TFadeDirection { fdNone, fdUp, fdDown };
#pragma option pop

#pragma option push -b-
enum TacAnimType { atFading, atAero };
#pragma option pop

#pragma option push -b-
enum TacBtnEvent { beMouseEnter, beMouseLeave, beMouseDown, beMouseUp };
#pragma option pop

typedef Set<TacBtnEvent, beMouseEnter, beMouseUp>  TacBtnEvents;

#pragma option push -b-
enum TacCtrlType { actGraphic };
#pragma option pop

#pragma option push -b-
enum TacAnimatEvent { aeMouseEnter, aeMouseLeave, aeMouseDown, aeMouseUp, aeGlobalDef };
#pragma option pop

typedef Set<TacAnimatEvent, aeMouseEnter, aeGlobalDef>  TacAnimatEvents;

#pragma option push -b-
enum TacImgType { itisaBorder, itisaTexture, itisaGlyph, itisaGlow, itisaPngGlyph };
#pragma option pop

#pragma option push -b-
enum TacFillMode { fmTiled, fmStretched, fmTiledHorz, fmTiledVert, fmStretchHorz, fmStretchVert, fmTileHorBtm, fmTileVertRight, fmStretchHorBtm, fmStretchVertRight, fmDisTiled, fmDiscHorTop, fmDiscVertLeft, fmDiscHorBottom, fmDiscVertRight };
#pragma option pop

class DELPHICLASS TsHackedControl;
class PASCALIMPLEMENTATION TsHackedControl : public Controls::TControl 
{
	typedef Controls::TControl inherited;
	
public:
	__property ParentColor  = {default=1};
	__property Color  = {default=-2147483643};
	__property ParentFont  = {default=1};
	__property PopupMenu ;
	__property Font ;
	__property WindowText ;
public:
	#pragma option push -w-inl
	/* TControl.Create */ inline __fastcall virtual TsHackedControl(Classes::TComponent* AOwner) : Controls::TControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TControl.Destroy */ inline __fastcall virtual ~TsHackedControl(void) { }
	#pragma option pop
	
};


struct TacBGInfo;
typedef TacBGInfo *PacBGInfo;

#pragma option push -b-
enum TacBGType { btUnknown, btFill, btCache };
#pragma option pop

#pragma pack(push, 4)
struct TacBGInfo
{
	Graphics::TBitmap* Bmp;
	Graphics::TColor Color;
	Types::TPoint Offset;
	Types::TRect R;
	TacBGType BgType;
	bool PleaseDraw;
	HDC DrawDC;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TCacheInfo
{
	Graphics::TBitmap* Bmp;
	int X;
	int Y;
	Graphics::TColor FillColor;
	bool Ready;
} ;
#pragma pack(pop)

typedef DynamicArray<Types::TPoint >  TPoints;

typedef TPoints *PPoints;

typedef Shortint TPercent;

typedef Set<Byte, 1, 255>  TsCodes;

#pragma option push -b-
enum TsHintStyle { hsSimply, hsComics, hsEllipse, hsBalloon, hsStandard, hsNone };
#pragma option pop

#pragma option push -b-
enum TsHintsPredefinitions { shSimply, shGradient, shTransparent, shEllipse, shBalloon, shComicsGradient, shComicsTransparent, shStandard, shNone, shCustom };
#pragma option pop

#pragma option push -b-
enum TGradientTypes { gtTopBottom, gtLeftRight, gtAsBorder };
#pragma option pop

#pragma option push -b-
enum TsShadowingShape { ssRectangle, ssEllipse };
#pragma option pop

#pragma option push -b-
enum TsWindowShowMode { soHide, soNormal, soShowMinimized, soMaximize, soShowNoActivate, soShow, soMinimize, soShowMinNoActive, soShowNA, soRestore, soDefault };
#pragma option pop

#pragma pack(push, 1)
struct TsRGB
{
	Byte B;
	Byte G;
	Byte R;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TsRGBA
{
	Byte B;
	Byte G;
	Byte R;
	Byte A;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TsColor
{
	
	union
	{
		struct 
		{
			TsRGB RGB;
			Byte MASK;
			
		};
		struct 
		{
			TsRGBA sBGRA;
			
		};
		struct 
		{
			int I;
			
		};
		struct 
		{
			Byte R;
			Byte G;
			Byte B;
			Byte A;
			
		};
		struct 
		{
			Graphics::TColor C;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TsColor_
{
	
	union
	{
		struct 
		{
			TsRGB BGR;
			Byte MASK;
			
		};
		struct 
		{
			TsRGBA sBGRA;
			
		};
		struct 
		{
			int I;
			
		};
		struct 
		{
			Byte B;
			Byte G;
			Byte R;
			Byte A;
			
		};
		struct 
		{
			Graphics::TColor C;
			
		};
		
	};
} ;
#pragma pack(pop)

typedef TsColor_ TRGBAArray[100001];

typedef TsColor_ *PRGBAArray;

typedef TsRGB TRGBArray[100001];

typedef TsRGB *PRGBArray;

#pragma option push -b-
enum sConst__2 { dgBlended, dgGrayed };
#pragma option pop

typedef Set<sConst__2, dgBlended, dgGrayed>  TsDisabledGlyphKind;

#pragma option push -b-
enum sConst__3 { dkBlended, dkGrayed };
#pragma option pop

typedef Set<sConst__3, dkBlended, dkGrayed>  TsDisabledKind;

typedef TsDisabledKind *PsDisabledKind;

#pragma pack(push, 4)
struct TsGradPie
{
	Graphics::TColor Color1;
	Graphics::TColor Color2;
	TPercent Percent;
	int Mode1;
	int Mode2;
} ;
#pragma pack(pop)

typedef DynamicArray<TsGradPie >  TsGradArray;

typedef AnsiString sConst__4[2];

#pragma option push -b-
enum TsCaptionLayout { sclLeft, sclTopLeft, sclTopCenter, sclTopRight };
#pragma option pop

typedef Set<Comctrls::TCalDayOfWeek, dowMonday, dowLocaleDefault>  TDaysOfWeek;

#pragma option push -b-
enum TDateOrder { doMDY, doDMY, doYMD };
#pragma option pop

#pragma option push -b-
enum TPopupWindowAlign { pwaRight, pwaLeft };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
#define CompatibleSkinVersion  (6.000000E+00)
#define MaxCompSkinVersion  (7.990000E+00)
static const Shortint ExceptTag = 0xffffff9e;
static const char TexChar = '\x7e';
static const char ZeroChar = '\x30';
static const char CharQuest = '\x3f';
static const char CharDiez = '\x23';
static const char CharExt = '\x21';
static const char CharGlyph = '\x40';
static const char CharMask = '\x5e';
static const Shortint ACS_FAST = 0x1;
static const Word ACS_PRINTING = 0x200;
static const Word ACS_MNUPDATING = 0x400;
static const Word ACS_LOCKED = 0x800;
static const Word ACS_FOCUSCHANGING = 0x1000;
static const Shortint BGT_NONE = 0x0;
static const Shortint BGT_GRADIENTHORZ = 0x1;
static const Shortint BGT_GRADIENTVERT = 0x2;
static const Shortint BGT_TEXTURE = 0x4;
static const Shortint BGT_TEXTURELEFT = 0x10;
static const Shortint BGT_TEXTURETOP = 0x20;
static const Shortint BGT_TEXTURERIGHT = 0x40;
static const Byte BGT_TEXTUREBOTTOM = 0x80;
static const Word BTG_TOPLEFT = 0x100;
static const Word BGT_TOPRIGHT = 0x200;
static const Word BGT_BOTTOMLEFT = 0x400;
static const Word BGT_BOTTOMRIGHT = 0x800;
static const Shortint ACT_RELCAPT = 0xffffffff;
#define s_PreviewKey "/acpreview"
#define s_EditorCapt "AlphaSkins Editor"
static const Shortint ASE_CLOSE = 0x1;
static const Shortint ASE_UPDATE = 0x2;
static const Shortint ASE_HELLO = 0x3;
static const Shortint ASE_ALIVE = 0x4;
static const Word ASE_MSG = 0xa400;
#define MasterBmpName "Master.bmp"
#define OptionsDatName "Options.dat"
#define acSkinExt "asz"
#define acPngExt "png"
#define acIcoExt "ico"
#define s_MinusOne "-1"
#define s_TrueStr "TRUE"
#define s_FalseStr "FALSE"
#define s_NewFolder "New folder"
#define s_SkinSelectItemName "SkinSelectItem"
static const char s_Slash = '\x5c';
static const char s_Space = '\x20';
static const char s_Comma = '\x2c';
static const Shortint BDM_STRETCH = 0x1;
static const Shortint BDM_ACTIVEONLY = 0x2;
static const Shortint BDM_FILL = 0x4;
static const Shortint HTSB_LEFT_BUTTON = 0x64;
static const Shortint HTSB_RIGHT_BUTTON = 0x65;
static const Shortint HTSB_TOP_BUTTON = 0x66;
static const Shortint HTSB_BOTTOM_BUTTON = 0x67;
static const Shortint HTSB_H_SCROLL = 0x68;
static const Shortint HTSB_HB_SCROLL = 0x69;
static const Shortint HTSB_V_SCROLL = 0x6a;
static const Shortint HTSB_VB_SCROLL = 0x6b;
static const Shortint HTCHILDCLOSE = 0x65;
static const Shortint HTCHILDMAX = 0x66;
static const Shortint HTCHILDMIN = 0x67;
static const Shortint EmptyRgn = 0x0;
static const Shortint acTimerInterval = 0xc;
extern PACKAGE TacImgType acImgTypes[5];
extern PACKAGE TacFillMode acFillModes[15];
extern PACKAGE Stdctrls::TScrollCode aScrollCodes[9];
extern PACKAGE TsHintStyle aHintStyles[6];
extern PACKAGE TacBtnEvent acBtnEvents[5];
static const Shortint COC_TsCustom = 0x1;
static const Shortint COC_TsSpinEdit = 0x2;
static const Shortint COC_TsEdit = 0x3;
static const Shortint COC_TsCustomMaskEdit = 0x4;
static const Shortint COC_TsMemo = 0x7;
static const Shortint COC_TsCustomListBox = 0x8;
static const Shortint COC_TsListBox = 0x8;
static const Shortint COC_TsColorBox = 0x9;
static const Shortint COC_TsListView = 0xa;
static const Shortint COC_TsCustomComboBox = 0xb;
static const Shortint COC_TsComboBox = 0xd;
static const Shortint COC_TsComboBoxEx = 0x12;
static const Shortint COC_TsFrameBar = 0x13;
static const Shortint COC_TsBarTitle = 0x14;
static const Shortint COC_TsCheckBox = 0x20;
static const Shortint COC_TsDBCheckBox = 0x20;
static const Shortint COC_TsRadioButton = 0x21;
static const Shortint COC_TsCurrencyEdit = 0x29;
static const Shortint COC_TsPanel = 0x33;
static const Shortint COC_TsPanelLow = 0x34;
static const Shortint COC_TsCoolBar = 0x35;
static const Shortint COC_TsToolBar = 0x36;
static const Shortint COC_TsDragBar = 0x38;
static const Shortint COC_TsTabSheet = 0x39;
static const Shortint COC_TsScrollBox = 0x3a;
static const Shortint COC_TsMonthCalendar = 0x3b;
static const Shortint COC_TsDBNavigator = 0x3c;
static const Shortint COC_TsCustomPanel = 0x44;
static const Shortint COC_TsGrip = 0x49;
static const Shortint COC_TsGroupBox = 0x4a;
static const Shortint COC_TsSplitter = 0x4b;
static const Shortint COC_TsDBEdit = 0x4c;
static const Shortint COC_TsDBMemo = 0x4e;
static const Shortint COC_TsDBComboBox = 0x51;
static const Shortint COC_TsDBLookupComboBox = 0x52;
static const Shortint COC_TsDBListBox = 0x53;
static const Shortint COC_TsDBLookupListBox = 0x54;
static const Shortint COC_TsDBGrid = 0x55;
static const Shortint COC_TsSpeedButton = 0x5c;
static const Shortint COC_TsButton = 0x5d;
static const Shortint COC_TsBitBtn = 0x5e;
static const Shortint COC_TsColorSelect = 0x5f;
static const Shortint COC_TsTreeView = 0x60;
static const Shortint COC_TsNavButton = 0x62;
static const Shortint COC_TsBevel = 0x6e;
static const Byte COC_TsCustomComboEdit = 0x83;
static const Byte COC_TsFileDirEdit = 0x84;
static const Byte COC_TsFilenameEdit = 0x85;
static const Byte COC_TsDirectoryEdit = 0x86;
static const Byte COC_TsCustomDateEdit = 0x89;
static const Byte COC_TsComboEdit = 0x8a;
static const Byte COC_TsDateEdit = 0x8c;
static const Byte COC_TsPageControl = 0x8d;
static const Byte COC_TsScrollBar = 0x8e;
static const Byte COC_TsTabControl = 0x8f;
static const Byte COC_TsStatusBar = 0x97;
static const Byte COC_TsHeaderControl = 0x98;
static const Byte COC_TsGauge = 0xa1;
static const Byte COC_TsTrackBar = 0xa5;
static const Byte COC_TsHintManager = 0xd3;
static const Byte COC_TsSkinProvider = 0xe0;
static const Byte COC_TsMDIForm = 0xe1;
static const Byte COC_TsFrameAdapter = 0xe2;
static const Byte COC_TsAdapter = 0xe3;
static const Byte COC_Unknown = 0xfa;
extern PACKAGE TsCodes sForbidMouse;
extern PACKAGE TsCodes sCanNotBeHot;
extern PACKAGE TsCodes sEditCtrls;
extern PACKAGE AnsiString sBoolArray[2];
extern PACKAGE unsigned acPreviewHandle;
extern PACKAGE bool acPreviewNeeded;
extern PACKAGE bool acSkinPreviewUpdating;
extern PACKAGE int acScrollBtnLength;
extern PACKAGE bool AppShowHint;
extern PACKAGE bool ShowHintStored;
extern PACKAGE TCacheInfo EmptyCI;
extern PACKAGE bool FadingForbidden;
extern PACKAGE int acAnimCount;
extern PACKAGE void *TempControl;
extern PACKAGE bool x64woAero;
extern PACKAGE Controls::TImageList* LargeShellImages;
extern PACKAGE Controls::TImageList* SmallShellImages;
extern PACKAGE bool fGlobalFlag;
extern PACKAGE Controls::TWinControl* acMagnForm;
extern PACKAGE TsColor sFuchsia;
extern PACKAGE bool StdTransparency;
extern PACKAGE bool ac_KeepOwnFont;
extern PACKAGE bool ac_ChangeThumbPreviews;
extern PACKAGE bool MouseForbidden;
extern PACKAGE bool DrawSkinnedMDIWall;
extern PACKAGE bool DrawSkinnedMDIScrolls;
extern PACKAGE bool acOldGlyphsOrder;
static const Word SC_DRAGMOVE = 0xf012;
extern PACKAGE AnsiString acs_MsgDlgOK;
extern PACKAGE AnsiString acs_MsgDlgCancel;
extern PACKAGE AnsiString acs_MsgDlgHelp;
extern PACKAGE AnsiString acs_RestoreStr;
extern PACKAGE AnsiString acs_MoveStr;
extern PACKAGE AnsiString acs_SizeStr;
extern PACKAGE AnsiString acs_MinimizeStr;
extern PACKAGE AnsiString acs_MaximizeStr;
extern PACKAGE AnsiString acs_CloseStr;
extern PACKAGE AnsiString acs_FileOpen;
extern PACKAGE AnsiString acs_AvailSkins;
extern PACKAGE AnsiString acs_InternalSkin;
extern PACKAGE AnsiString acs_ErrorSettingCount;
extern PACKAGE AnsiString acs_ListBoxMustBeVirtual;
extern PACKAGE AnsiString acs_ColorDlgAdd;
extern PACKAGE AnsiString acs_ColorDlgDefine;
extern PACKAGE AnsiString acs_ColorDlgMainPal;
extern PACKAGE AnsiString acs_ColorDlgAddPal;
extern PACKAGE AnsiString acs_ColorDlgTitle;
extern PACKAGE AnsiString acs_ColorDlgRed;
extern PACKAGE AnsiString acs_ColorDlgGreen;
extern PACKAGE AnsiString acs_ColorDlgBlue;
extern PACKAGE AnsiString acs_ColorDlgDecimal;
extern PACKAGE AnsiString acs_ColorDlgHex;
extern PACKAGE AnsiString acs_FrameAdapterError1;
extern PACKAGE AnsiString acs_HintDsgnTitle;
extern PACKAGE AnsiString acs_HintDsgnPreserved;
extern PACKAGE AnsiString acs_HintDsgnStyle;
extern PACKAGE AnsiString acs_HintDsgnBevelWidth;
extern PACKAGE AnsiString acs_Blur;
extern PACKAGE AnsiString acs_HintDsgnArrowLength;
extern PACKAGE AnsiString acs_HintDsgnHorizMargin;
extern PACKAGE AnsiString acs_HintDsgnVertMargin;
extern PACKAGE AnsiString acs_HintDsgnRadius;
extern PACKAGE AnsiString acs_HintDsgnMaxWidth;
extern PACKAGE AnsiString acs_HintDsgnPauseHide;
extern PACKAGE AnsiString acs_Percent;
extern PACKAGE AnsiString acs_HintDsgnOffset;
extern PACKAGE AnsiString acs_HintDsgnTransparency;
extern PACKAGE AnsiString acs_HintDsgnNoPicture;
extern PACKAGE AnsiString acs_Font;
extern PACKAGE AnsiString acs_Texture;
extern PACKAGE AnsiString acs_HintDsgnLoad;
extern PACKAGE AnsiString acs_HintDsgnSave;
extern PACKAGE AnsiString acs_HintDsgnColor;
extern PACKAGE AnsiString acs_HintDsgnBorderTop;
extern PACKAGE AnsiString acs_HintDsgnBorderBottom;
extern PACKAGE AnsiString acs_Shadow;
extern PACKAGE AnsiString acs_Background;
extern PACKAGE AnsiString acs_Gradient;
extern PACKAGE AnsiString acs_PreviewHint;
extern PACKAGE AnsiString acs_Root;
extern PACKAGE AnsiString acs_SelectDir;
extern PACKAGE AnsiString acs_Create;
extern PACKAGE void __fastcall InitShellImageLists(bool Large, bool Small);

}	/* namespace Sconst */
using namespace Sconst;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sConst
