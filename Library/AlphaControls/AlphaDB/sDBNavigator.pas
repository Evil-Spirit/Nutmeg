unit sDBNavigator;
{$I sDefs.inc}
{$R SDBRES.RES}

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, sPanel, dbctrls, sconst, db, dbconsts, math, sSpeedButton, ImgList;

type
  TsNavButton = class;
  TsNavDataLink = class;
{$IFDEF D2006}
  TButtonSet = set of TNavigateBtn;
{$ENDIF}

  TsDBNavigator = class(TsPanel)
  private
    FDataLink: TsNavDataLink;
    FVisibleButtons: TButtonSet;
    FHints: TStrings;
    FDefHints: TStrings;
    MinBtnSize: TPoint;
    FOnNavClick: ENavClick;
    FBeforeAction: ENavClick;
    FocusedButton: TNavigateBtn;
    FConfirmDelete: Boolean;
    FFirstImageIndex: integer;
    FImages: TCustomImageList;
    FNumGlyphs: integer;
    function ButtonWidth : integer;
    function ButtonsCount : integer;
    procedure BtnMouseDown (Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure ClickHandler(Sender: TObject);
    function GetDataSource: TDataSource;
    function GetHints: TStrings;
    procedure HintsChanged(Sender: TObject);
    procedure InitButtons;
    procedure InitHints;
    procedure SetDataSource(Value: TDataSource);
    procedure SetHints(Value: TStrings);
    procedure SetSize(var W: Integer; var H: Integer);
    procedure SetVisible(Value: TButtonSet);
    procedure WMSize(var Message: TWMSize);  message WM_SIZE;
    procedure WMSetFocus(var Message: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Message: TWMKillFocus); message WM_KILLFOCUS;
    procedure WMGetDlgCode(var Message: TWMGetDlgCode); message WM_GETDLGCODE;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure WMWindowPosChanging(var Message: TWMWindowPosChanging); message WM_WINDOWPOSCHANGING;
    procedure SetFirstImageIndex(const Value: integer);
    procedure SetImages(const Value: TCustomImageList);
    procedure SetNumGlyphs(const Value: integer);
  protected
    procedure DataChanged;
    procedure EditingChanged;
    procedure ActiveChanged;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure CalcMinSize(var W, H: Integer);
    function MarginWidth : integer;
    property NumGlyphs : integer read FNumGlyphs Write SetNumGlyphs default 1;
  public
    Buttons: array[TNavigateBtn] of TsNavButton;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure GetChildren(Proc: TGetChildProc; Root: TComponent); override;
    procedure WndProc (var Message: TMessage); override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
    procedure BtnClick(Index: TNavigateBtn); virtual;
    procedure Loaded; override;
  published
    property Images : TCustomImageList read FImages write SetImages;
    property FirstImageIndex : integer read FFirstImageIndex write SetFirstImageIndex default 0;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property VisibleButtons: TButtonSet read FVisibleButtons write SetVisible default [nbFirst, nbPrior, nbNext,
                                  nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh];
    property Hints: TStrings read GetHints write SetHints;
    property ConfirmDelete: Boolean read FConfirmDelete write FConfirmDelete default True;
    property BeforeAction: ENavClick read FBeforeAction write FBeforeAction;
    property OnClick: ENavClick read FOnNavClick write FOnNavClick;
    property Width default 240;
    property Height default 25;
  end;

{ TsNavButton }

  TsNavButton = class(TsSpeedButton)
  private
    FIndex: TNavigateBtn;
    FNavStyle: TNavButtonStyle;
    FRepeatTimer: TTimer;
    procedure TimerExpired(Sender: TObject);
  protected
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
  public
    constructor Create (AOwner: TComponent); override;
    destructor Destroy; override;
    property NavStyle: TNavButtonStyle read FNavStyle write FNavStyle;
    procedure Paint; override;
    property Index : TNavigateBtn read FIndex write FIndex;
  end;

{ TsNavDataLink }

  TsNavDataLink = class(TDataLink)
  private
    FNavigator: TsDBNavigator;
  protected
    procedure EditingChanged; override;
    procedure DataSetChanged; override;
    procedure ActiveChanged; override;
  public
    constructor Create(ANav: TsDBNavigator);
    destructor Destroy; override;
  end;

implementation

uses sDefaults, sMessages, sSkinProps, sDialogs;

resourcestring
  SFirstRecord = 'First record';
  SPriorRecord = 'Prior record';
  SNextRecord = 'Next record';
  SLastRecord = 'Last record';
  SInsertRecord = 'Insert record';
  SDeleteRecord = 'Delete record';
  SEditRecord = 'Edit record';
  SPostEdit = 'Post edit';
  SCancelEdit = 'Cancel edit';
  SRefreshRecord = 'Refresh data';
  SDeleteRecordQuestion = 'Delete record?';

var
  BtnTypeName: array[TNavigateBtn] of PChar = ('FIRST', 'PRIOR', 'NEXT',
    'LAST', 'INSERT', 'DELETE', 'EDIT', 'POST', 'CANCEL', 'REFRESH');
  BtnHintId: array[TNavigateBtn] of Pointer = (@SFirstRecord, @SPriorRecord,
    @SNextRecord, @SLastRecord, @SInsertRecord, @SDeleteRecord, @SEditRecord,
    @SPostEdit, @SCancelEdit, @SRefreshRecord);

  SDBN_FIRST, SDBN_PRIOR, SDBN_NEXT, SDBN_LAST, SDBN_INSERT, SDBN_DELETE, SDBN_EDIT,
  SDBN_POST, SDBN_CANCEL, SDBN_REFRESH : TBitmap;

{ TsDBNavigator }

procedure LoadGlyph(Btn : TsNavButton; TypeName : string);
begin
  if TypeName = 'FIRST' then Btn.Glyph.Assign(SDBN_FIRST)
  else if TypeName = 'PRIOR' then Btn.Glyph.Assign(SDBN_PRIOR)
  else if TypeName = 'NEXT' then Btn.Glyph.Assign(SDBN_NEXT)
  else if TypeName = 'LAST' then Btn.Glyph.Assign(SDBN_LAST)
  else if TypeName = 'INSERT' then Btn.Glyph.Assign(SDBN_INSERT)
  else if TypeName = 'DELETE' then Btn.Glyph.Assign(SDBN_DELETE)
  else if TypeName = 'EDIT' then Btn.Glyph.Assign(SDBN_EDIT)
  else if TypeName = 'POST' then Btn.Glyph.Assign(SDBN_POST)
  else if TypeName = 'CANCEL' then Btn.Glyph.Assign(SDBN_CANCEL)
  else if TypeName = 'REFRESH' then Btn.Glyph.Assign(SDBN_REFRESH);
end;

procedure TsDBNavigator.ActiveChanged;
var
  I: TNavigateBtn;
begin
  if not (Enabled and FDataLink.Active) then for I := Low(Buttons) to High(Buttons) do Buttons[I].Enabled := False else begin
    DataChanged;
    EditingChanged;
  end;
end;

procedure TsDBNavigator.BtnClick(Index: TNavigateBtn);
begin
  if (DataSource <> nil) and (DataSource.State <> dsInactive) then begin
    if not (csDesigning in ComponentState) and Assigned(FBeforeAction) then FBeforeAction(Self, Index);
    with DataSource.DataSet do case Index of
      nbPrior: Prior;
      nbNext: Next;
      nbFirst: First;
      nbLast: Last;
      nbInsert: Insert;
      nbEdit: Edit;
      nbCancel: Cancel;
      nbPost: Post;
      nbRefresh: Refresh;
      nbDelete:
        if not FConfirmDelete or (sMessageDlg(SDeleteRecordQuestion, mtConfirmation, mbOKCancel, 0) <> idCancel) then Delete;
    end;
  end;
  if not (csDesigning in ComponentState) and Assigned(FOnNavClick) then FOnNavClick(Self, Index);
end;

procedure TsDBNavigator.BtnMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  OldFocus: TNavigateBtn;
begin
  OldFocus := FocusedButton;
  FocusedButton := TsNavButton (Sender).Index;
  if TabStop and (GetFocus <> Handle) and CanFocus then
  begin
    SetFocus;
    if (GetFocus <> Handle) then
      Exit;
  end
  else if TabStop and (GetFocus = Handle) and (OldFocus <> FocusedButton) then
  begin
    Buttons[OldFocus].Invalidate;
    Buttons[FocusedButton].Invalidate;
  end;
end;

function TsDBNavigator.ButtonsCount: integer;
var
  i : TNavigateBtn;
begin
  Result := 0;
  for I := Low(Buttons) to High(Buttons) do begin
    if Buttons[I].Visible then begin
      Inc(Result);
    end;
  end;
  if Result = 0 then Inc(Result);
end;

function TsDBNavigator.ButtonWidth: Integer;
begin
  ButtonWidth := (Width - 2 * MarginWidth) div ButtonsCount;
end;

procedure TsDBNavigator.CalcMinSize(var W, H: Integer);
begin
  if (csLoading in ComponentState) then Exit;
  if Buttons[nbFirst] = nil then Exit;

  W := Max(W, ButtonsCount * MinBtnSize.X + 2 * MarginWidth);
  H := Max(H, MinBtnSize.Y + 2 * MarginWidth);
end;

procedure TsDBNavigator.ClickHandler(Sender: TObject);
begin
  BtnClick(TsNavButton(Sender).Index);
end;

procedure TsDBNavigator.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  if not (csLoading in ComponentState) then
    ActiveChanged;
end;

constructor TsDBNavigator.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  SkinData.COC := COC_TsToolBar;
  ControlStyle := ControlStyle - [csAcceptsControls, csSetCaption] + [csOpaque];
  FDataLink := TsNavDataLink.Create(Self);
  FVisibleButtons := [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh];
  FHints := TStringList.Create;
  TStringList(FHints).OnChange := HintsChanged;
  InitButtons;
  InitHints;
  Width := 240;
  Height := 25;
  FocusedButton := nbFirst;
  FConfirmDelete := True;
  FullRepaint := False;
  FNumGlyphs := 1;
  FFirstImageIndex := 0;
end;

procedure TsDBNavigator.DataChanged;
var
  UpEnable, DnEnable: Boolean;
begin
  UpEnable := Enabled and FDataLink.Active and not FDataLink.DataSet.BOF;
  DnEnable := Enabled and FDataLink.Active and not FDataLink.DataSet.EOF;
  Buttons[nbFirst].Enabled := UpEnable;
  Buttons[nbPrior].Enabled := UpEnable;
  Buttons[nbNext].Enabled := DnEnable;
  Buttons[nbLast].Enabled := DnEnable;
  Buttons[nbDelete].Enabled := Enabled and FDataLink.Active and
    FDataLink.DataSet.CanModify and
    not (FDataLink.DataSet.BOF and FDataLink.DataSet.EOF);
end;

destructor TsDBNavigator.Destroy;
begin
  FDefHints.Free;
  FDataLink.Free;
  FHints.Free;
  FDataLink := nil;
  inherited Destroy;
end;

procedure TsDBNavigator.EditingChanged;
var
  CanModify: Boolean;
begin
  CanModify := Enabled and FDataLink.Active and FDataLink.DataSet.CanModify;
  Buttons[nbInsert].Enabled := CanModify;
  Buttons[nbEdit].Enabled := CanModify and not FDataLink.Editing;
  Buttons[nbPost].Enabled := CanModify and FDataLink.Editing;
  Buttons[nbCancel].Enabled := CanModify and FDataLink.Editing;
  Buttons[nbRefresh].Enabled := CanModify;
end;

procedure TsDBNavigator.GetChildren(Proc: TGetChildProc; Root: TComponent);
begin
end;

function TsDBNavigator.GetDataSource: TDataSource;
begin
  if Assigned(FDataLink) and Assigned(FDataLink.DataSource) then Result := FDataLink.DataSource else Result := nil;
end;

function TsDBNavigator.GetHints: TStrings;
begin
  if (csDesigning in ComponentState) and not (csWriting in ComponentState) and
     not (csReading in ComponentState) and (FHints.Count = 0) then
    Result := FDefHints else
    Result := FHints;
end;

procedure TsDBNavigator.HintsChanged(Sender: TObject);
begin
  InitHints;
end;

procedure TsDBNavigator.InitButtons;
var
  I: TNavigateBtn;
  Btn: TsNavButton;
  X: Integer;
begin
  MinBtnSize := Point(6, 6);
  X := MarginWidth;
  for I := Low(Buttons) to High(Buttons) do begin
    Btn := TsNavButton.Create(Self);
    Btn.Flat := True;
    Btn.Index := I;
    Btn.Visible := I in FVisibleButtons;
    Btn.Enabled := True;
    Btn.SetBounds (X, MarginWidth, MinBtnSize.X, Height - 2 * MarginWidth);
    LoadGlyph(Btn, BtnTypeName[I]);
    Btn.Glyph.PixelFormat := pf24bit;
    Btn.OnClick := ClickHandler;
    Btn.OnMouseDown := BtnMouseDown;
    Btn.Parent := Self;
    Buttons[I] := Btn;
    X := X + MinBtnSize.X;
  end;
  Buttons[nbPrior].NavStyle := Buttons[nbPrior].NavStyle + [nsAllowTimer];
  Buttons[nbNext].NavStyle  := Buttons[nbNext].NavStyle + [nsAllowTimer];
end;

procedure TsDBNavigator.InitHints;
var
  I: Integer;
  J: TNavigateBtn;
begin
  if not Assigned(FDefHints) then begin
    FDefHints := TStringList.Create;
    for J := Low(Buttons) to High(Buttons) do FDefHints.Add(LoadResString(BtnHintId[J]));
  end;
  for J := Low(Buttons) to High(Buttons) do Buttons[J].Hint := FDefHints[Ord(J)];
  J := Low(Buttons);
  for I := 0 to (FHints.Count - 1) do begin
    if FHints.Strings[I] <> '' then Buttons[J].Hint := FHints.Strings[I];
    if J = High(Buttons) then Exit;
    Inc(J);
  end;
end;

procedure TsDBNavigator.KeyDown(var Key: Word; Shift: TShiftState);
var
  NewFocus: TNavigateBtn;
  OldFocus: TNavigateBtn;
begin
  OldFocus := FocusedButton;
  case Key of
    VK_RIGHT:
      begin
        NewFocus := FocusedButton;
        repeat
          if NewFocus < High(Buttons) then
            NewFocus := Succ(NewFocus);
        until (NewFocus = High(Buttons)) or (Buttons[NewFocus].Visible);
        if NewFocus <> FocusedButton then
        begin
          FocusedButton := NewFocus;
          Buttons[OldFocus].Invalidate;
          Buttons[FocusedButton].Invalidate;
        end;
      end;
    VK_LEFT:
      begin
        NewFocus := FocusedButton;
        repeat
          if NewFocus > Low(Buttons) then
            NewFocus := Pred(NewFocus);
        until (NewFocus = Low(Buttons)) or (Buttons[NewFocus].Visible);
        if NewFocus <> FocusedButton then
        begin
          FocusedButton := NewFocus;
          Buttons[OldFocus].Invalidate;
          Buttons[FocusedButton].Invalidate;
        end;
      end;
    VK_SPACE:
      begin
        if Buttons[FocusedButton].Enabled then
          Buttons[FocusedButton].Click;
      end;
  end;
end;

procedure TsDBNavigator.Loaded;
var
  W, H, n: Integer;
  I: TNavigateBtn;
begin
  inherited Loaded;
  n := 0;
    for I := Low(Buttons) to High(Buttons) do begin
      if Assigned(Images) then Buttons[I].ImageIndex := FFirstImageIndex + n;
      Buttons[I].SkinData.SkinManager := SkinData.SkinManager;

      inc(n);
    end;
  W := Width;
  H := Height;
  SetSize(W, H);
  InitHints;
  ActiveChanged;
end;

function TsDBNavigator.MarginWidth: integer;
begin
  Result := integer(BorderStyle = bsSingle) * (1 + 3 * integer(Ctl3d)) + BorderWidth +
            integer(BevelOuter <> bvNone) * BevelWidth +
            integer(BevelInner <> bvNone) * BevelWidth;
end;

procedure TsDBNavigator.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) then begin
    if (FDataLink <> nil) and (AComponent = DataSource) then DataSource := nil
    else if AComponent = Images then Images := nil;
  end;
end;

procedure TsDBNavigator.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
var
  W, H: Integer;
begin
  W := AWidth;
  H := AHeight;
  if not HandleAllocated then begin
    SetSize(W, H);
  end;
  inherited SetBounds(ALeft, ATop, aWidth, aHeight);
end;

procedure TsDBNavigator.SetDataSource(Value: TDataSource);
begin
  FDataLink.DataSource := Value;
  if not (csLoading in ComponentState) then
    ActiveChanged;
  if Value <> nil then Value.FreeNotification(Self);
end;

procedure TsDBNavigator.SetFirstImageIndex(const Value: integer);
var
  I: TNavigateBtn;
  Index : integer;
begin
  if FFirstImageIndex <> Value then begin
    FFirstImageIndex := Value;
    Index := Value;
    for I := Low(Buttons) to High(Buttons) do begin
      Buttons[I].ImageIndex := Index;
      Inc(Index);
    end;
  end;
end;

procedure TsDBNavigator.SetHints(Value: TStrings);
begin
  if Value.Text = FDefHints.Text then
    FHints.Clear else
    FHints.Assign(Value);
end;

procedure TsDBNavigator.SetImages(const Value: TCustomImageList);
var
  I: TNavigateBtn;
begin
  if FImages <> Value then begin
    FImages := Value;
    for I := Low(Buttons) to High(Buttons) do begin
      Buttons[I].Images := Value;
      if Value <> nil then begin
        Buttons[I].Glyph.Assign(nil);
        Buttons[I].NumGlyphs := 1;
      end
      else begin
        LoadGlyph(Buttons[I], BtnTypeName[I]);
      end;
    end;
  end;
end;

procedure TsDBNavigator.SetNumGlyphs(const Value: integer);
var
  I: TNavigateBtn;
begin
  if FNumGlyphs <> Value then begin
    FNumGlyphs := Value;//max(1, Value);
    for I := Low(Buttons) to High(Buttons) do begin
      Buttons[I].NumGlyphs := Value;
    end;
  end;
end;

procedure TsDBNavigator.SetSize(var W, H: Integer);
var
  I: TNavigateBtn;
  Space, Temp, Remain: Integer;
  X: Integer;
begin
  if (csLoading in ComponentState) or (Parent = nil) then Exit;
  if Buttons[nbFirst] = nil then Exit;

  Temp := ButtonsCount * ButtonWidth;
  if Align = alNone then W := Temp + 2 * MarginWidth;

  X := MarginWidth;
  Remain := Width - 2 * MarginWidth - Temp;
  Temp := ButtonsCount div 2;
  for I := Low(Buttons) to High(Buttons) do begin
    if Buttons[I].Visible then begin
      Space := 0;
      if Remain <> 0 then begin
        Dec(Temp, Remain);
        if Temp < 0 then begin
          Inc(Temp, ButtonsCount);
          Space := 1;
        end;
      end;
      Buttons[I].SetBounds(X, MarginWidth, ButtonWidth + Space, Height - 2 * MarginWidth - 1);
      Inc(X, ButtonWidth + Space);
    end
    else
      Buttons[I].SetBounds(Width + 1, MarginWidth, ButtonWidth, Height - 2 * MarginWidth - 1);
  end;
end;

procedure TsDBNavigator.SetVisible(Value: TButtonSet);
var
  I: TNavigateBtn;
  W, H: Integer;
begin
  W := Width;
  H := Height;
  FVisibleButtons := Value;
  for I := Low(Buttons) to High(Buttons) do Buttons[I].Visible := I in FVisibleButtons;
  SetSize(W, H);
  Invalidate;
end;

procedure TsDBNavigator.WMGetDlgCode(var Message: TWMGetDlgCode);
begin
  Message.Result := DLGC_WANTARROWS;
end;

procedure TsDBNavigator.WMKillFocus(var Message: TWMKillFocus);
begin
  Buttons[FocusedButton].Invalidate;
end;

procedure TsDBNavigator.WMSetFocus(var Message: TWMSetFocus);
begin
  Buttons[FocusedButton].Invalidate;
end;

procedure TsDBNavigator.WMSize(var Message: TWMSize);
var
  W, H: Integer;
begin
  inherited;
  W := Width;
  H := Height;
  SetSize(W, H);
//  if csDesigning in ComponentState then SkinData.Invalidate;
end;

procedure TsDBNavigator.WMWindowPosChanging(var Message: TWMWindowPosChanging);
begin
  inherited;
  if (SWP_NOSIZE and Message.WindowPos.Flags) = 0 then
    CalcMinSize(Message.WindowPos.cx, Message.WindowPos.cy);
end;

procedure TsDBNavigator.WndProc(var Message: TMessage);
var
  i : TNavigateBtn;
begin
  inherited;
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_SETNEWSKIN, AC_REFRESH, AC_REMOVESKIN : for i := Low(Buttons) to High(Buttons) do begin
      Buttons[i].Perform(Message.Msg, Message.WParam, Message.LParam);
    end;
  end;
end;

{ TsNavButton }

constructor TsNavButton.Create(AOwner: TComponent);
begin
  inherited;
  ShowCaption := False;
  SkinData.SkinManager := TsPanel(AOwner).SkinData.FSkinManager;
  SkinData.SkinSection := s_TOOLBUTTON;
  Self.DisabledGlyphKind := Self.DisabledGlyphKind + [dgBlended];
  Self.DisabledKind := Self.DisabledKind + [dkBlended];
end;

destructor TsNavButton.Destroy;
begin
  if FRepeatTimer <> nil then FRepeatTimer.Free;
  inherited Destroy;
end;

procedure TsNavButton.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited MouseDown (Button, Shift, X, Y);
  if nsAllowTimer in FNavStyle then begin
    if FRepeatTimer = nil then FRepeatTimer := TTimer.Create(Self);

    FRepeatTimer.OnTimer := TimerExpired;
    FRepeatTimer.Interval := InitRepeatPause;
    FRepeatTimer.Enabled  := True;
  end;
end;

procedure TsNavButton.MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseUp (Button, Shift, X, Y);
  if FRepeatTimer <> nil then FRepeatTimer.Enabled  := False;
end;

procedure TsNavButton.Paint;
begin
  if (csDestroying in ComponentState) or (csLoading in ComponentState) then Exit;
  if (GetFocus = Parent.Handle) and (FIndex = TsDBNavigator (Parent).FocusedButton) then SkinData.FFocused := True;
  inherited Paint;
  SkinData.FFocused := False;
end;

procedure TsNavButton.TimerExpired(Sender: TObject);
begin
  FRepeatTimer.Interval := RepeatPause;
  if Down and MouseCapture then begin
    try
      Click;
    except
      FRepeatTimer.Enabled := False;
      raise;
    end;
  end;
end;

{ TsNavDataLink }

procedure TsNavDataLink.ActiveChanged;
begin
  if FNavigator <> nil then FNavigator.ActiveChanged;
end;

constructor TsNavDataLink.Create(ANav: TsDBNavigator);
begin
  inherited Create;
  FNavigator := ANav;
  VisualControl := True;
end;

procedure TsNavDataLink.DataSetChanged;
begin
  if FNavigator <> nil then FNavigator.DataChanged;
end;

destructor TsNavDataLink.Destroy;
begin
  FNavigator := nil;
  inherited Destroy;
end;

procedure TsNavDataLink.EditingChanged;
begin
  if FNavigator <> nil then FNavigator.EditingChanged;
end;

initialization
  SDBN_FIRST := TBitmap.Create; SDBN_FIRST.LoadFromResourceName(hInstance, 'SDBN_FIRST');
  SDBN_PRIOR := TBitmap.Create; SDBN_PRIOR.LoadFromResourceName(hInstance, 'SDBN_PRIOR');
  SDBN_NEXT := TBitmap.Create; SDBN_NEXT.LoadFromResourceName(hInstance, 'SDBN_NEXT');
  SDBN_LAST := TBitmap.Create; SDBN_LAST.LoadFromResourceName(hInstance, 'SDBN_LAST');
  SDBN_INSERT := TBitmap.Create; SDBN_INSERT.LoadFromResourceName(hInstance, 'SDBN_INSERT');
  SDBN_DELETE := TBitmap.Create; SDBN_DELETE.LoadFromResourceName(hInstance, 'SDBN_DELETE');
  SDBN_EDIT := TBitmap.Create; SDBN_EDIT.LoadFromResourceName(hInstance, 'SDBN_EDIT');
  SDBN_POST := TBitmap.Create; SDBN_POST.LoadFromResourceName(hInstance, 'SDBN_POST');
  SDBN_CANCEL := TBitmap.Create; SDBN_CANCEL.LoadFromResourceName(hInstance, 'SDBN_CANCEL');
  SDBN_REFRESH := TBitmap.Create; SDBN_REFRESH.LoadFromResourceName(hInstance, 'SDBN_REFRESH');

finalization
  FreeAndNil(SDBN_FIRST );
  FreeAndNil(SDBN_PRIOR );
  FreeAndNil(SDBN_NEXT  );
  FreeAndNil(SDBN_LAST  );
  FreeAndNil(SDBN_INSERT);
  FreeAndNil(SDBN_DELETE);
  FreeAndNil(SDBN_EDIT  );
  FreeAndNil(SDBN_POST  );
  FreeAndNil(SDBN_CANCEL);
  FreeAndNil(SDBN_REFRESH);
end.










