// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acShellCtrls.pas' rev: 6.00

#ifndef acShellCtrlsHPP
#define acShellCtrlsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <sListView.hpp>	// Pascal unit
#include <sConst.hpp>	// Pascal unit
#include <sTreeView.hpp>	// Pascal unit
#include <sComboBoxes.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <CommCtrl.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <acAlphaImageList.hpp>	// Pascal unit
#include <SyncObjs.hpp>	// Pascal unit
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

namespace Acshellctrls
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TacRootFolder { rfDesktop, rfMyComputer, rfNetwork, rfRecycleBin, rfAppData, rfCommonDesktopDirectory, rfCommonPrograms, rfCommonStartMenu, rfCommonStartup, rfControlPanel, rfDesktopDirectory, rfFavorites, rfFonts, rfInternet, rfPersonal, rfPrinters, rfPrintHood, rfPrograms, rfRecent, rfSendTo, rfStartMenu, rfStartup, rfTemplates };
#pragma option pop

#pragma option push -b-
enum TacShellFolderCapability { fcCanCopy, fcCanDelete, fcCanLink, fcCanMove, fcCanRename, fcDropTarget, fcHasPropSheet };
#pragma option pop

typedef Set<TacShellFolderCapability, fcCanCopy, fcHasPropSheet>  TacShellFolderCapabilities;

#pragma option push -b-
enum TacShellFolderProperty { fpCut, fpIsLink, fpReadOnly, fpShared, fpFileSystem, fpFileSystemAncestor, fpRemovable, fpValidate };
#pragma option pop

typedef Set<TacShellFolderProperty, fpCut, fpValidate>  TacShellFolderProperties;

#pragma option push -b-
enum TacShellObjectType { otFolders, otNonFolders, otHidden };
#pragma option pop

typedef Set<TacShellObjectType, otFolders, otHidden>  TacShellObjectTypes;

#pragma option push -b-
enum TacShowExtension { seSystem, seShow, seHide };
#pragma option pop

__interface IacShellCommandVerb;
typedef System::DelphiInterface<IacShellCommandVerb> _di_IacShellCommandVerb;
__interface INTERFACE_UUID("{7D2A7245-2376-4D33-8008-A130935A2E8B}") IacShellCommandVerb  : public IInterface 
{
	
public:
	virtual void __fastcall ExecuteCommand(AnsiString Verb, bool &Handled) = 0 ;
	virtual void __fastcall CommandCompleted(AnsiString Verb, bool Succeeded) = 0 ;
};

__interface IShellDetails;
typedef System::DelphiInterface<IShellDetails> _di_IShellDetails;
__interface INTERFACE_UUID("{000214EC-0000-0000-C000-000000000046}") IShellDetails  : public IInterface 
{
	
public:
	virtual HRESULT __stdcall GetDetailsOf(Shlobj::PItemIDList pidl, unsigned iColumn, _SHELLDETAILS &pDetails) = 0 ;
	virtual HRESULT __stdcall ColumnClick(unsigned iColumn) = 0 ;
};

__interface IDetInterface;
typedef System::DelphiInterface<IDetInterface> _di_IDetInterface;
__interface INTERFACE_UUID("{00000000-0000-0000-C000-000000000046}") IDetInterface  : public IInterface 
{
	
public:
	HIDESBASE virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj) = 0 ;
	HIDESBASE virtual int __stdcall _AddRef(void) = 0 ;
	HIDESBASE virtual int __stdcall _Release(void) = 0 ;
};

class DELPHICLASS TacShellFolder;
class PASCALIMPLEMENTATION TacShellFolder : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	_ITEMIDLIST *FPIDL;
	_ITEMIDLIST *FFullPIDL;
	TacShellFolder* FParent;
	_di_IShellFolder FIShellFolder;
	_di_IShellFolder2 FIShellFolder2;
	_di_IShellDetails FIShellDetails;
	_di_IDetInterface FDetailInterface;
	int FLevel;
	unsigned FViewHandle;
	Classes::TStrings* FDetails;
	_di_IDetInterface __fastcall GetDetailInterface();
	_di_IShellDetails __fastcall GetShellDetails();
	_di_IShellFolder2 __fastcall GeTacShellFolder2();
	AnsiString __fastcall GetDetails(int Index);
	void __fastcall SetDetails(int Index, const AnsiString Value);
	void __fastcall LoadColumnDetails(TacShellFolder* RootFolder, unsigned Handle, int ColumnCount);
	
public:
	__fastcall virtual TacShellFolder(TacShellFolder* AParent, Shlobj::PItemIDList ID, _di_IShellFolder SF);
	__fastcall virtual ~TacShellFolder(void);
	TacShellFolderCapabilities __fastcall Capabilities(void);
	AnsiString __fastcall DisplayName(TacShowExtension ShowExt);
	int __fastcall ExecuteDefault(void);
	int __fastcall ImageIndex(bool LargeIcon);
	bool __fastcall IsFolder(const AnsiString Name = "", bool OpenZipFiles = true);
	bool __fastcall IsFileFolder(void);
	bool __fastcall IsFile(const AnsiString Name = "", bool OpenZipFiles = true);
	bool __fastcall IsReadOnly(void);
	_di_IShellFolder __fastcall ParenTacShellFolder();
	AnsiString __fastcall PathName();
	TacShellFolderProperties __fastcall Properties(void);
	bool __fastcall Rename(const WideString NewName);
	bool __fastcall SubFolders(void);
	__property Shlobj::PItemIDList AbsoluteID = {read=FFullPIDL};
	__property AnsiString Details[int Index] = {read=GetDetails, write=SetDetails};
	__property int Level = {read=FLevel, nodefault};
	__property TacShellFolder* Parent = {read=FParent};
	__property Shlobj::PItemIDList RelativeID = {read=FPIDL};
	__property _di_IShellFolder ShellFolder = {read=FIShellFolder};
	__property _di_IShellFolder2 ShellFolder2 = {read=GeTacShellFolder2};
	__property _di_IShellDetails ShellDetails = {read=GetShellDetails};
	__property unsigned ViewHandle = {read=FViewHandle, write=FViewHandle, nodefault};
};


#pragma option push -b-
enum TacNotifyFilter { nfFileNameChange, nfDirNameChange, nfAttributeChange, nfSizeChange, nfWriteChange, nfSecurityChange };
#pragma option pop

typedef Set<TacNotifyFilter, nfFileNameChange, nfSecurityChange>  TacNotifyFilters;

class DELPHICLASS TacShellChangeThread;
class PASCALIMPLEMENTATION TacShellChangeThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	int FMutex;
	int FWaitHandle;
	Classes::TThreadMethod FChangeEvent;
	AnsiString FDirectory;
	bool FWatchSubTree;
	bool FWaitChanged;
	unsigned FNotifyOptionFlags;
	Syncobjs::TEvent* FStopEvent;
	Syncobjs::TEvent* FActive;
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	__fastcall virtual TacShellChangeThread(Classes::TThreadMethod ChangeEvent);
	__fastcall virtual ~TacShellChangeThread(void);
	void __fastcall SetDirectoryOptions(const AnsiString Directory, bool WatchSubTree, unsigned NotifyOptionFlags);
	__property Classes::TThreadMethod ChangeEvent = {read=FChangeEvent, write=FChangeEvent};
};


class DELPHICLASS TacCustomShellChangeNotifier;
class PASCALIMPLEMENTATION TacCustomShellChangeNotifier : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TacNotifyFilters FFilters;
	bool FWatchSubTree;
	AnsiString FRoot;
	TacShellChangeThread* FThread;
	Classes::TThreadMethod FOnChange;
	void __fastcall SetRoot(const AnsiString Value);
	void __fastcall SetWatchSubTree(const bool Value);
	void __fastcall SetFilters(const TacNotifyFilters Value);
	void __fastcall SetOnChange(const Classes::TThreadMethod Value);
	
protected:
	void __fastcall Change(void);
	void __fastcall Start(void);
	
public:
	__fastcall virtual TacCustomShellChangeNotifier(Classes::TComponent* AOwner);
	__fastcall virtual ~TacCustomShellChangeNotifier(void);
	__property TacNotifyFilters NotifyFilters = {read=FFilters, write=SetFilters, nodefault};
	__property AnsiString Root = {read=FRoot, write=SetRoot};
	__property bool WatchSubTree = {read=FWatchSubTree, write=SetWatchSubTree, nodefault};
	__property Classes::TThreadMethod OnChange = {read=FOnChange, write=SetOnChange};
};


class DELPHICLASS TacShellChangeNotifier;
class PASCALIMPLEMENTATION TacShellChangeNotifier : public TacCustomShellChangeNotifier 
{
	typedef TacCustomShellChangeNotifier inherited;
	
__published:
	__property NotifyFilters ;
	__property Root ;
	__property WatchSubTree ;
	__property OnChange ;
public:
	#pragma option push -w-inl
	/* TacCustomShellChangeNotifier.Create */ inline __fastcall virtual TacShellChangeNotifier(Classes::TComponent* AOwner) : TacCustomShellChangeNotifier(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacCustomShellChangeNotifier.Destroy */ inline __fastcall virtual ~TacShellChangeNotifier(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TacAddFolderEvent)(System::TObject* Sender, TacShellFolder* AFolder, bool &CanAdd);

typedef void __fastcall (__closure *TacGetImageIndexEvent)(System::TObject* Sender, int Index, int &ImageIndex);

class DELPHICLASS TacCustomShellTreeView;
class DELPHICLASS TacCustomShellComboBox;
class DELPHICLASS TacCustomShellListView;
class PASCALIMPLEMENTATION TacCustomShellListView : public Slistview::TsCustomListView 
{
	typedef Slistview::TsCustomListView inherited;
	
private:
	AnsiString FOldRoot;
	AnsiString FRoot;
	TacShellFolder* FRootFolder;
	bool FAutoContext;
	bool FAutoRefresh;
	bool FAutoNavigate;
	bool FSorted;
	TacShellObjectTypes FObjectTypes;
	int FLargeImages;
	int FSmallImages;
	TacAddFolderEvent FOnAddFolder;
	TacCustomShellTreeView* FTreeView;
	TacCustomShellComboBox* FComboBox;
	TacShellChangeNotifier* FNotifier;
	Comctrls::TLVEditingEvent FOnEditing;
	bool FSettingRoot;
	AnsiString FSavePath;
	AnsiString FMask;
	TacShowExtension FShowExtension;
	void __fastcall EnumColumns(void);
	TacShellFolder* __fastcall GetFolder(int Index);
	void __fastcall SetAutoRefresh(const bool Value);
	void __fastcall SetSorted(const bool Value);
	void __fastcall SetTreeView(TacCustomShellTreeView* Value);
	void __fastcall SetComboBox(TacCustomShellComboBox* Value);
	void __fastcall SynchPaths(void);
	void __fastcall SetMask(const AnsiString Value);
	bool __fastcall GetUpdating(void);
	
protected:
	Classes::TList* FFolders;
	void __fastcall ClearItems(void);
	void __fastcall CreateRoot(void);
	virtual void __fastcall DestroyWnd(void);
	DYNAMIC void __fastcall DblClick(void);
	DYNAMIC void __fastcall DoContextPopup(const Types::TPoint &MousePos, bool &Handled);
	void __fastcall EditText(void);
	DYNAMIC void __fastcall Edit(const tagLVITEMA &Item);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual bool __fastcall OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request);
	virtual int __fastcall OwnerDataFind(Comctrls::TItemFind Find, const AnsiString FindString, const Types::TPoint &FindPosition, void * FindData, int StartIndex, Comctrls::TSearchDirection Direction, bool Wrap);
	virtual void __fastcall Populate(void);
	void __fastcall SetObjectTypes(TacShellObjectTypes Value);
	void __fastcall SetRoot(const AnsiString Value);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	bool FUpdating;
	void __fastcall RootChanged(void);
	void __fastcall SetPathFromID(Shlobj::PItemIDList ID);
	void __fastcall TreeUpdate(Shlobj::PItemIDList NewRoot);
	__fastcall virtual TacCustomShellListView(Classes::TComponent* AOwner);
	virtual void __fastcall InitControl(const bool Skinned);
	__fastcall virtual ~TacCustomShellListView(void);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall Loaded(void);
	void __fastcall Back(void);
	HIDESBASE void __fastcall Refresh(void);
	void __fastcall MakeNewFolder(void);
	TacShellFolder* __fastcall SelectedFolder(void);
	void __fastcall CommandCompleted(AnsiString Verb, bool Succeeded);
	void __fastcall ExecuteCommand(AnsiString Verb, bool &Handled);
	__property TacShellFolder* Folders[int Index] = {read=GetFolder};
	__property TacShellFolder* RootFolder = {read=FRootFolder};
	__property Items ;
	__property Columns ;
	__property AnsiString Mask = {read=FMask, write=SetMask};
	__property bool AutoContextMenus = {read=FAutoContext, write=FAutoContext, default=1};
	__property bool AutoRefresh = {read=FAutoRefresh, write=SetAutoRefresh, default=0};
	__property bool AutoNavigate = {read=FAutoNavigate, write=FAutoNavigate, default=1};
	__property TacShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property AnsiString Root = {read=FRoot, write=SetRoot};
	__property TacCustomShellTreeView* ShellTreeView = {read=FTreeView, write=SetTreeView};
	__property TacCustomShellComboBox* ShellComboBox = {read=FComboBox, write=SetComboBox};
	__property bool Sorted = {read=FSorted, write=SetSorted, nodefault};
	__property bool Updating = {read=GetUpdating, nodefault};
	__property TacShowExtension ShowExt = {read=FShowExtension, write=FShowExtension, nodefault};
	__property TacAddFolderEvent OnAddFolder = {read=FOnAddFolder, write=FOnAddFolder};
	__property Comctrls::TLVEditingEvent OnEditing = {read=FOnEditing, write=FOnEditing};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TacCustomShellListView(HWND ParentWindow) : Slistview::TsCustomListView(ParentWindow) { }
	#pragma option pop
	
private:
	void *__IacShellCommandVerb;	/* Acshellctrls::IacShellCommandVerb */
	
public:
	operator IacShellCommandVerb*(void) { return (IacShellCommandVerb*)&__IacShellCommandVerb; }
	
};


class PASCALIMPLEMENTATION TacCustomShellComboBox : public Scomboboxes::TsCustomComboBoxEx 
{
	typedef Scomboboxes::TsCustomComboBoxEx inherited;
	
private:
	int FImageHeight;
	int FImageWidth;
	Imglist::TCustomImageList* FImageList;
	AnsiString FOldRoot;
	AnsiString FRoot;
	TacShellFolder* FRootFolder;
	TacCustomShellTreeView* FTreeView;
	TacCustomShellListView* FListView;
	TacShellObjectTypes FObjectTypes;
	bool FUseShellImages;
	bool FUpdating;
	TacGetImageIndexEvent FOnGetImageIndex;
	void __fastcall ClearItems(void);
	TacShellFolder* __fastcall GetFolder(int Index);
	AnsiString __fastcall GetPath();
	void __fastcall SetPath(const AnsiString Value);
	void __fastcall SetPathFromID(Shlobj::PItemIDList ID);
	void __fastcall SetRoot(const AnsiString Value);
	void __fastcall SetTreeView(TacCustomShellTreeView* Value);
	void __fastcall SetListView(TacCustomShellListView* Value);
	void __fastcall SetUseShellImages(const bool Value);
	int __fastcall GetShellImageIndex(TacShellFolder* AFolder);
	bool __fastcall GetUpdating(void);
	
protected:
	void __fastcall AddItems(int Index, TacShellFolder* ParentFolder);
	DYNAMIC void __fastcall Click(void);
	void __fastcall CreateRoot(void);
	virtual void __fastcall DestroyWnd(void);
	virtual void __fastcall Init(void);
	TacShellFolder* __fastcall InitItem(TacShellFolder* ParentFolder, Shlobj::PItemIDList ID);
	void __fastcall RootChanged(void);
	void __fastcall TreeUpdate(Shlobj::PItemIDList NewPath);
	virtual void __fastcall SetObjectTypes(TacShellObjectTypes Value);
	
public:
	bool ExtUpdating;
	__fastcall virtual TacCustomShellComboBox(Classes::TComponent* AOwner);
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall CreateWnd(void);
	int __fastcall IndexFromID(Shlobj::PItemIDList AbsoluteID);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	__fastcall virtual ~TacCustomShellComboBox(void);
	virtual void __fastcall Loaded(void);
	__property Items ;
	__property AnsiString Path = {read=GetPath, write=SetPath};
	__property TacShellFolder* Folders[int Index] = {read=GetFolder};
	__property AnsiString Root = {read=FRoot, write=SetRoot};
	__property TacShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property TacCustomShellTreeView* ShellTreeView = {read=FTreeView, write=SetTreeView};
	__property TacCustomShellListView* ShellListView = {read=FListView, write=SetListView};
	__property bool Updating = {read=GetUpdating, nodefault};
	__property bool UseShellImages = {read=FUseShellImages, write=SetUseShellImages, default=1};
	__property TacGetImageIndexEvent OnGetImageIndex = {read=FOnGetImageIndex, write=FOnGetImageIndex};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TacCustomShellComboBox(HWND ParentWindow) : Scomboboxes::TsCustomComboBoxEx(ParentWindow) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TacCustomShellTreeView : public Streeview::TsTreeView 
{
	typedef Streeview::TsTreeView inherited;
	
public:
	TacShellFolder* operator[](int Index) { return Folders[Index]; }
	
private:
	AnsiString FRoot;
	AnsiString FOldRoot;
	TacShellFolder* FRootFolder;
	TacShellObjectTypes FObjectTypes;
	bool FLoadingRoot;
	bool FAutoContext;
	bool FUpdating;
	TacCustomShellComboBox* FComboBox;
	TacCustomShellListView* FListView;
	bool FAutoRefresh;
	bool FImageListChanging;
	bool FUseShellImages;
	TacShellChangeNotifier* FNotifier;
	TacAddFolderEvent FOnAddFolder;
	AnsiString FSavePath;
	Comctrls::TTreeNode* FNodeToMonitor;
	TacShowExtension FShowExtension;
	Comctrls::TTreeNode* __fastcall FolderExists(Shlobj::PItemIDList FindID, Comctrls::TTreeNode* InNode);
	TacShellFolder* __fastcall GetFolder(int Index);
	AnsiString __fastcall GetPath();
	void __fastcall SetComboBox(TacCustomShellComboBox* Value);
	void __fastcall SetListView(const TacCustomShellListView* Value);
	void __fastcall SetPath(const AnsiString Value);
	void __fastcall SetPathFromID(Shlobj::PItemIDList ID);
	void __fastcall SetRoot(const AnsiString Value);
	void __fastcall SetUseShellImages(const bool Value);
	void __fastcall SetAutoRefresh(const bool Value);
	bool __fastcall GetUpdating(void);
	void __fastcall DefferedRefreshEvent(void);
	MESSAGE void __fastcall OnDefferedRefreshEvent(Messages::TMessage &Message);
	
protected:
	void __fastcall CreateRoot(void);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall DestroyWnd(void);
	DYNAMIC void __fastcall DoContextPopup(const Types::TPoint &MousePos, bool &Handled);
	DYNAMIC void __fastcall Edit(const tagTVITEMA &Item);
	virtual void __fastcall GetImageIndex(Comctrls::TTreeNode* Node);
	virtual void __fastcall GetSelectedIndex(Comctrls::TTreeNode* Node);
	void __fastcall InitNode(Comctrls::TTreeNode* NewNode, Shlobj::PItemIDList ID, Comctrls::TTreeNode* ParentNode);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall Delete(Comctrls::TTreeNode* Node);
	Comctrls::TTreeNode* __fastcall NodeFromAbsoluteID(Comctrls::TTreeNode* StartNode, Shlobj::PItemIDList ID);
	Comctrls::TTreeNode* __fastcall NodeFromRelativeID(Comctrls::TTreeNode* ParentNode, Shlobj::PItemIDList ID);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	DYNAMIC bool __fastcall CanChange(Comctrls::TTreeNode* Node);
	DYNAMIC bool __fastcall CanExpand(Comctrls::TTreeNode* Node);
	void __fastcall PopulateNode(Comctrls::TTreeNode* Node);
	void __fastcall RootChanged(void);
	virtual void __fastcall SetObjectTypes(TacShellObjectTypes Value);
	HIDESBASE virtual void __fastcall WMDestroy(Messages::TWMNoParams &Message);
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	void __fastcall ClearItems(void);
	void __fastcall RefreshEvent(void);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TMessage &Message);
	
public:
	__fastcall virtual TacCustomShellTreeView(Classes::TComponent* AOwner);
	__fastcall virtual ~TacCustomShellTreeView(void);
	HIDESBASE void __fastcall Refresh(Comctrls::TTreeNode* Node);
	TacShellFolder* __fastcall SelectedFolder(void);
	__property bool AutoRefresh = {read=FAutoRefresh, write=SetAutoRefresh, nodefault};
	__property TacShellFolder* Folders[int Index] = {read=GetFolder/*, default*/};
	__property Items ;
	__property AnsiString Path = {read=GetPath, write=SetPath};
	__property bool AutoContextMenus = {read=FAutoContext, write=FAutoContext, default=1};
	__property TacShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property AnsiString Root = {read=FRoot, write=SetRoot};
	__property TacCustomShellComboBox* ShellComboBox = {read=FComboBox, write=SetComboBox};
	__property TacCustomShellListView* ShellListView = {read=FListView, write=SetListView};
	__property bool UseShellImages = {read=FUseShellImages, write=SetUseShellImages, nodefault};
	__property bool Updating = {read=GetUpdating, nodefault};
	__property TacShowExtension ShowExt = {read=FShowExtension, write=FShowExtension, nodefault};
	__property TacAddFolderEvent OnAddFolder = {read=FOnAddFolder, write=FOnAddFolder};
	void __fastcall CommandCompleted(AnsiString Verb, bool Succeeded);
	void __fastcall ExecuteCommand(AnsiString Verb, bool &Handled);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TacCustomShellTreeView(HWND ParentWindow) : Streeview::TsTreeView(ParentWindow) { }
	#pragma option pop
	
private:
	void *__IacShellCommandVerb;	/* Acshellctrls::IacShellCommandVerb */
	
public:
	operator IacShellCommandVerb*(void) { return (IacShellCommandVerb*)&__IacShellCommandVerb; }
	
};


class DELPHICLASS TsShellTreeView;
class PASCALIMPLEMENTATION TsShellTreeView : public TacCustomShellTreeView 
{
	typedef TacCustomShellTreeView inherited;
	
__published:
	__property OnAddFolder ;
	__property OnGetImageIndex ;
	__property OnGetSelectedIndex ;
	__property OnClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnStartDrag ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnDblClick ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnChanging ;
	__property OnChange ;
	__property OnExpanding ;
	__property OnCollapsing ;
	__property OnCollapsed ;
	__property OnExpanded ;
	__property OnEditing ;
	__property OnEdited ;
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property BorderStyle  = {default=1};
	__property Color  = {default=-2147483643};
	__property Ctl3D ;
	__property Cursor  = {default=0};
	__property DragCursor  = {default=-12};
	__property DragMode  = {default=0};
	__property Enabled  = {default=1};
	__property Font ;
	__property HideSelection  = {default=1};
	__property Images ;
	__property Indent ;
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property RightClickSelect  = {default=1};
	__property ShowButtons  = {default=1};
	__property ShowHint ;
	__property ShowLines  = {default=1};
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property ChangeDelay  = {default=0};
	__property ShowRoot  = {default=1};
	__property StateImages ;
	__property AutoContextMenus  = {default=1};
	__property ObjectTypes ;
	__property Root ;
	__property ShellComboBox ;
	__property ShellListView ;
	__property UseShellImages ;
	__property AutoRefresh ;
	__property ShowExt ;
public:
	#pragma option push -w-inl
	/* TacCustomShellTreeView.Create */ inline __fastcall virtual TsShellTreeView(Classes::TComponent* AOwner) : TacCustomShellTreeView(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacCustomShellTreeView.Destroy */ inline __fastcall virtual ~TsShellTreeView(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsShellTreeView(HWND ParentWindow) : TacCustomShellTreeView(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsShellComboBox;
class PASCALIMPLEMENTATION TsShellComboBox : public TacCustomShellComboBox 
{
	typedef TacCustomShellComboBox inherited;
	
public:
	__property Path ;
	
__published:
	__property OnGetImageIndex ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDropDown ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property Anchors  = {default=3};
	__property BiDiMode ;
	__property Color  = {default=-2147483643};
	__property Constraints ;
	__property Ctl3D ;
	__property DragCursor  = {default=-12};
	__property DragKind  = {default=0};
	__property DragMode  = {default=0};
	__property DropDownCount ;
	__property Enabled  = {default=1};
	__property Font ;
	__property ImeMode  = {default=3};
	__property ImeName ;
	__property MaxLength  = {default=0};
	__property ParentBiDiMode  = {default=1};
	__property ParentColor  = {default=0};
	__property ParentCtl3D  = {default=1};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property Images ;
	__property Root ;
	__property ShellTreeView ;
	__property ShellListView ;
	__property UseShellImages  = {default=1};
public:
	#pragma option push -w-inl
	/* TacCustomShellComboBox.Create */ inline __fastcall virtual TsShellComboBox(Classes::TComponent* AOwner) : TacCustomShellComboBox(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacCustomShellComboBox.Destroy */ inline __fastcall virtual ~TsShellComboBox(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsShellComboBox(HWND ParentWindow) : TacCustomShellComboBox(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsShellListView;
class PASCALIMPLEMENTATION TsShellListView : public TacCustomShellListView 
{
	typedef TacCustomShellListView inherited;
	
__published:
	__property OnChange ;
	__property OnChanging ;
	__property OnColumnClick ;
	__property OnContextPopup ;
	__property OnEnter ;
	__property OnExit ;
	__property OnInsert ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property DragCursor  = {default=-12};
	__property OnStartDrag ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property BorderStyle  = {default=1};
	__property Color  = {default=-2147483643};
	__property ColumnClick  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property Ctl3D ;
	__property DragMode  = {default=0};
	__property ReadOnly  = {default=1};
	__property Enabled  = {default=1};
	__property Font ;
	__property GridLines  = {default=0};
	__property Sorted ;
	__property HideSelection  = {default=1};
	__property HotTrack  = {default=0};
	__property IconOptions ;
	__property AllocBy  = {default=0};
	__property MultiSelect  = {default=0};
	__property RowSelect  = {default=0};
	__property ParentColor  = {default=0};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property ShowHint ;
	__property PopupMenu ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=1};
	__property Visible  = {default=1};
	__property ViewStyle  = {default=0};
	__property OnEditing ;
	__property OnAddFolder ;
	__property AutoContextMenus  = {default=1};
	__property AutoRefresh  = {default=0};
	__property AutoNavigate  = {default=1};
	__property ObjectTypes ;
	__property Root ;
	__property ShellTreeView ;
	__property ShellComboBox ;
	__property ShowExt ;
	__property Mask ;
	__property ShowColumnHeaders  = {default=1};
public:
	#pragma option push -w-inl
	/* TacCustomShellListView.Create */ inline __fastcall virtual TsShellListView(Classes::TComponent* AOwner) : TacCustomShellListView(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacCustomShellListView.Destroy */ inline __fastcall virtual ~TsShellListView(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsShellListView(HWND ParentWindow) : TacCustomShellListView(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TsDlgShellListView;
class PASCALIMPLEMENTATION TsDlgShellListView : public TsShellListView 
{
	typedef TsShellListView inherited;
	
protected:
	DYNAMIC void __fastcall DblClick(void);
public:
	#pragma option push -w-inl
	/* TacCustomShellListView.Create */ inline __fastcall virtual TsDlgShellListView(Classes::TComponent* AOwner) : TsShellListView(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TacCustomShellListView.Destroy */ inline __fastcall virtual ~TsDlgShellListView(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TsDlgShellListView(HWND ParentWindow) : TsShellListView(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word WM_DEFFERED_REFRESH = 0x401;
extern PACKAGE bool DontFoldersGenerate;
extern PACKAGE bool UseAllFolderAttributes;
extern PACKAGE unsigned SysSmallImages;
extern PACKAGE Acalphaimagelist::TsAlphaImageList* SysSmallImageList;
#define SRFDesktop "rfDesktop"
#define SCmdVerbOpen "open"
#define SCmdVerbRename "rename"
#define SCmdVerbDelete "delete"
#define SCmdVerbPaste "paste"
#define SShellNoDetails "Unable to retrieve folder details for \"%s\". Error code "\
	"$%x"
#define NTFolders (System::Set<TacRootFolder, rfDesktop, rfTemplates> () << TacRootFolder(5) << TacRootFolder(6) << TacRootFolder(7) << TacRootFolder(8) )
extern PACKAGE int nFolder[23];
extern PACKAGE void __fastcall DisposePIDL(Shlobj::PItemIDList PIDL);
extern PACKAGE _di_IShellFolder __fastcall DesktopShellFolder();
extern PACKAGE int __fastcall GetShellImage(Shlobj::PItemIDList PIDL, bool Large, bool Open);
extern PACKAGE AnsiString __fastcall GetDisplayName(_di_IShellFolder Parentfolder, Shlobj::PItemIDList PIDL, unsigned Flags, TacShowExtension ShowExt);
extern PACKAGE void __fastcall InvokeContextMenu(Controls::TWinControl* Owner, TacShellFolder* AFolder, int X, int Y);
extern PACKAGE TacShellFolder* __fastcall CreateRootFromPIDL(Shlobj::PItemIDList Value);
extern PACKAGE bool __fastcall G_ValidateMask(const AnsiString S, const AnsiString Mask, char MaskChar = '\x58');
extern PACKAGE bool __fastcall G_ValidateWildText(const AnsiString S, const AnsiString Mask, char MaskChar = '\x3f', char WildCard = '\x2a');
extern PACKAGE int __fastcall G_CharPos(char C, const AnsiString S, int StartPos = 0x1)/* overload */;

}	/* namespace Acshellctrls */
using namespace Acshellctrls;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acShellCtrls
