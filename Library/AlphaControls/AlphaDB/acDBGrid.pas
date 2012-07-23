unit acDBGrid;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids, DBGrids, DB, acsbUtils, 
  sConst, sDefaults, sCommonData, sMessages, sScrollBar {$IFDEF LOGGED}, sDebugMsgs{$ENDIF};

type
  TsDBGrid = class;

  TColumnSortOrder = (csoNone, csoAsc, csoDesc);

  { TacColumnTitle }
  
  TacColumnTitle = class(TColumnTitle)
  private
    function GetCaption: string;
    function IsCaptionStored: boolean;
  protected
    procedure SetCaption(const Value: string);
  published
    property Caption: string read GetCaption write SetCaption stored IsCaptionStored;
  end;

  { TacDBColumn }

  TacDBColumn = class (TColumn)
  private
    FMinWidth: integer;
    FTableSpacePercent: double;
    FSortOrder: TColumnSortOrder;

    function GetSortOrder: TColumnSortOrder;
    procedure SetSortOrder(Value: TColumnSortOrder);
    procedure SetWidth(const Value: integer);
    function GetWidth: integer;
    procedure SetVisible(Value: Boolean);
    function GetVisible: Boolean;
    function CanBeSorted: boolean;
  protected
    function CreateTitle: TColumnTitle; override;
    procedure ChangedTitle(DoRebuild: boolean);
  public
    constructor Create(Collection: TCollection); override;
    procedure Assign(Source: TPersistent); override;
  published
    property Width: integer read GetWidth write SetWidth;
    property Visible: Boolean read GetVisible write SetVisible;
    property MinWidth: integer read FMinWidth write FMinWidth default 0;
    property SortOrder: TColumnSortOrder read GetSortOrder write SetSortOrder default csoNone;
  end;

  { TacDBGridColumns }

  TacDBGridColumns = class(TDBGridColumns)
  private
    function GetColumn(Index: Integer): TacDBColumn;
    procedure SetColumn(Index: Integer; Value: TacDBColumn);
    procedure ColumnAdded;
  public
    property Items[Index: Integer]: TacDBColumn read GetColumn write SetColumn; default;
  end;

  TGridDrawStateEx = set of (geHighlight, geActiveRow, geMultiSelected);

  TGetCellParamsEvent = procedure (Sender: TObject; Field: TField;
    AFont: TFont; var Background: TColor; State: TGridDrawState; StateEx: TGridDrawStateEx) of object;

  TsDBGrid = class(TDBGrid)
  private
    FDefaultDrawing: boolean;
    FOnGetCellParams: TGetCellParamsEvent;
    FExecSorting: boolean;
    FExecColAjust: boolean;
    FActiveRowSelected: boolean;
    FTitleButtonDown: integer;
    FTitleBarUp: boolean;
    FOldTitleButtonDown: integer;
    FCellButtonDown: integer;
    FCellButtonRow: integer;
    FCellButtonCol: integer;
    FCellButtonPressed: boolean;
    FCellButtonRect: TRect;
    FCellButtonBRect: TRect;
    FLevelDelimiterChar: char;
    FColumnStretch : boolean;
    FColumnSort : boolean;

    FCommonData: TsCommonData;
    procedure UpdateHeaderHeight;
    procedure DrawButton(X, Y: integer; State: boolean);
    function IsOnButton(X, Y: integer): boolean;
    function GetButtonRect(Cell: TGridCoord): TRect;
    procedure SetLevelDelimiterChar(const Value: char);
    function CalcFilterBar(Column: TColumn): TRect;
    function MouseInLowerstLevel(X, Y: integer; Column: TColumn = nil): boolean;

    procedure CalcTableSpacePercent;
    function GetColumns: TacDBGridColumns;
    procedure SetColumns(const Value: TacDBGridColumns);
  protected
    FHeaderHeight: integer;
    FExecSizing: boolean;
    ListSW : TacScrollWnd;

    function CreateEditor: TInplaceEdit; override;
    procedure PaintWindow(DC: HDC); override;
    function GetClientRect: TRect; override;
    procedure Loaded; override;
    function CreateColumns: TDBGridColumns; override;

    procedure ColWidthsChanged; override;
    procedure Resize; override;
    procedure ResizeColumns(ResizedColumn: integer = -1);

    procedure DrawColumnCell(const Rect: TRect; DataCol: integer; Column: TColumn; State: TGridDrawState); override;
    procedure GetCellProps(Field: TField; AFont: TFont; var Background: TColor; State: TGridDrawState; StateEx:TGridDrawStateEx); dynamic;
    procedure DrawCell(ACol, ARow: Longint; ARect: TRect; AState: TGridDrawState); override;

    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: integer); override;

    function CanEditShow: boolean; override;
    procedure TopLeftChanged; override;
    procedure WMMouseWheel(var Message: TWMMouseWheel); message WM_MOUSEWHEEL;
    procedure TitleClick(Column: TColumn); override;
    procedure LayoutChanged; override;
    property DefaultRowHeight;
    property DataLink;
    procedure WndProc (var Message: TMessage); override;
  public
    procedure AfterConstruction; override;
    function GetGridSize: integer;
    constructor Create(Owner: TComponent); override;
    destructor Destroy; override;
    property SelectedRows;
    procedure CalcTitleLevel(Level: integer; var aRect: TRect);
    function GetTitleLevel(Level: integer): TRect;
    procedure AdjustColumns;
  published
    property SkinData : TsCommonData read FCommonData write FCommonData;
    property DefaultDrawing: boolean read FDefaultDrawing write FDefaultDrawing default True;
    property LevelDelimiterChar: char read FLevelDelimiterchar write SetLevelDelimiterchar default '|';
    property OnGetCellParams: TGetCellParamsEvent read FOnGetCellParams write FOnGetCellParams;
    property Columns: TacDBGridColumns read GetColumns write SetColumns stored False;
  end;

implementation


uses
  Math, sStyleSimply, acntUtils, sVclUtils, sMaskData, sGraphUtils, sSkinProps,
  sAlphaGraph, sSkinManager{$IFNDEF DELPHI5}, types{$ENDIF};

var
  DrawBitmap: TBitmap;
  UserCount: integer;

type
  _TCustomControl = class(TWinControl)
  private
    FCanvas: TCanvas;
  end;

  TInthernalEdit = class(TEdit)
  end;

{$IFNDEF CLR}
  _TCustomGrid = class(TCustomGrid)
  end;
{$ENDIF}

procedure RefreshGridScrolls(SkinData : TsCommonData; var ListSW : TacScrollWnd);
begin
  if SkinData.Skinned then begin
    if (ListSW <> nil) and ListSW.Destroyed then FreeAndNil(ListSW);
    if ListSW = nil then ListSW := TacEditWnd.Create(TWinControl(SkinData.FOwnerControl).Handle, SkinData, SkinData.SkinManager, SkinData.SkinSection);
  end
  else begin
    if ListSW <> nil then FreeAndNil(ListSW);
  end;
end;

procedure UsesBitmap;
begin
  if UserCount = 0 then DrawBitmap := TBitmap.Create;
  Inc(UserCount);
end;

procedure ReleaseBitmap;
begin
  Dec(UserCount);
  if UserCount = 0 then DrawBitmap.Free;
end;

function GetCaptionDepth(const Str: string; Delim: char): integer;
var
  i: integer;
  St: string;
begin
  Result := 0;
  if Str = '' then Exit;
  Result := 1;
  i := Pos(Delim, Str);
  St := Str;
  while i > 0 do begin
    Inc(Result);
    St[i] := #255;
    i := Pos(Delim, St);
  end;
end;

function GetCaptionLevel(const Str: string; Level: integer; Delim: char): string;
var
  i,j: integer;
  St: string;
begin
  j := 0;
  Result := '';
  if Str = '' then
    Exit;
  i := Pos(Delim, Str);
  St := Str;
  while (Level > 0) and (I > 0) do begin
    Dec(Level);
    St[i] := #255;
    if Level <= -2 then begin
      Result := Copy(St, j + 1, i - 1);
      exit;
    end;
    j := i;
    i := Pos(Delim, St);
  end;
  if Level <= 0 then begin
    if i = 0 then i := Length(St) + j else Dec(i);
    Result := Copy(Str, j + 1, i - j);
    exit;
  end;
end;

{ TacColumnTitle }

function TacColumnTitle.GetCaption: string;
begin
  Result := inherited Caption;
end;

function TacColumnTitle.IsCaptionStored: boolean;
begin
  Result := (cvTitleCaption in Column.AssignedValues) and (Caption <> DefaultCaption);
end;

procedure TacColumnTitle.SetCaption(const Value: string);
begin
  if Value <> inherited Caption then begin
    inherited Caption := Value;
    TacDBColumn(Column).ChangedTitle(True);
  end;
end;

{ TacDBColumn }

function TacDBColumn.GetSortOrder: TColumnSortOrder;
begin
  Result := FSortOrder;
end;

procedure TacDBColumn.SetSortOrder(Value: TColumnSortOrder);
begin
  if not CanBeSorted then Exit;
  FSortOrder := Value;
end;

procedure TacDBColumn.Assign(Source: TPersistent);
begin
  if Source is TacDBColumn then begin
    if Assigned(Collection) then Collection.BeginUpdate;
    inherited Assign(Source);
    try
      FMinWidth := TacDBColumn(Source).FMinWidth;
    finally
      if Assigned(Collection) then Collection.EndUpdate;
    end;
  end
  else inherited Assign(Source);
end;

function TacDBColumn.CanBeSorted: boolean;
begin
  if Assigned(Field) then Result := (Field.FieldKind = fkData) and not (Field.DataType in [ftFmtMemo, ftMemo{$IFNDEF VER4}, ftOraClob {$ENDIF}]) else Result := False;
end;

procedure TacDBColumn.ChangedTitle(DoRebuild: boolean);
begin
  if DoRebuild then if Assigned(Grid) then TsDBGrid(Grid).LayoutChanged;
end;

function TacDBColumn.CreateTitle: TColumnTitle;
begin
  Result := TacColumnTitle.Create(Self);
end;

constructor TacDBColumn.Create(Collection: TCollection);
begin
  inherited;
  FMinWidth := 0;
  TacDBGridColumns(Collection).ColumnAdded;
end;

procedure TacDBColumn.SetWidth(const Value: integer);
begin
  if Value > FMinWidth then inherited Width := Value else inherited Width := FMinWidth
end;

function TacDBColumn.GetWidth: integer;
begin
  Result := inherited Width;
end;

procedure TacDBColumn.SetVisible(Value: Boolean);
var
  OldVisible: boolean;
begin
  OldVisible := inherited Visible;
  inherited Visible := Value;
  if (OldVisible <> Value) and Assigned(Grid) and TsDBGrid(Grid).FColumnStretch and (not TsDBGrid(Grid).FExecSizing) then begin
    TsDBGrid(Grid).FExecSizing := True;
    TsDBGrid(Grid).ResizeColumns;
    TsDBGrid(Grid).FExecSizing := False;
  end;
end;

function TacDBColumn.GetVisible: Boolean;
begin
  Result := inherited Visible;
end;

{ TacDBGridColumns }

function TacDBGridColumns.GetColumn(Index: Integer): TacDBColumn;
begin
  Result := TacDBColumn(inherited Items[Index]);
end;

procedure TacDBGridColumns.SetColumn(Index: Integer; Value: TacDBColumn);
begin
  inherited Items[Index] := Value;
end;

procedure TacDBGridColumns.ColumnAdded;
begin
  TsDBGrid(Grid).CalcTableSpacePercent;
end;

{ TsDBGrid }

constructor TsDBGrid.Create(Owner: TComponent);
begin
  inherited Create(Owner);
  Columns.State := csDefault;
  UsesBitmap;
  FLevelDelimiterChar := '|';
  inherited DefaultDrawing := False; 
  FDefaultDrawing := True;
  FColumnStretch := false;
  FColumnSort := false;
  FExecSizing := False;
  FTitleButtonDown := -1;
  FOldTitleButtonDown := -1;
  FCellButtonDown := -1;

  FCommonData := TsCommonData.Create(Self, True);
  FCommonData.COC := COC_TsDBGrid;
end;

destructor TsDBGrid.Destroy;
begin
  if ListSW <> nil then FreeAndNil(ListSW);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  ReleaseBitmap;
  inherited;
end;

procedure TsDBGrid.Loaded;
var
  Stretched: Boolean;
begin
  Stretched := FColumnStretch;
  FColumnStretch := false;
  inherited Loaded;
  try
    FCommonData.Loaded;
  except
    Application.HandleException(Self);
  end;
  FColumnStretch := Stretched;
  CalcTableSpacePercent;
end;

procedure TsDBGrid.AfterConstruction;
begin
  inherited AfterConstruction;
  try
    FCommonData.Loaded;
  except
    Application.HandleException(Self);
  end;
end;

function TsDBGrid.CreateColumns: TDBGridColumns;
begin
  Result := TacDBGridColumns.Create(Self, TacDBColumn);
end;

procedure TsDBGrid.Resize;
begin
  inherited;
  if FColumnStretch and not (csLoading in ComponentState) and (not FExecSizing) then begin
    FExecSizing := True;
    try
      ResizeColumns;
    finally
      FExecSizing := False;
    end;
  end;
end;

procedure TsDBGrid.ColWidthsChanged;
var
  i: integer;
  ResizedColumn: integer;
begin
  if FColumnStretch and not (csLoading in ComponentState) and (not FExecSizing) then begin
    FExecSizing := True;
    ResizedColumn := -1;
    for i := 0 to Columns.Count - 1 do if ColWidths[i + IndicatorOffset] <> Columns[i].Width then begin
      ResizedColumn := i;
      break;
    end;
    if ResizedColumn <> -1 then begin
      if ColWidths[ResizedColumn + IndicatorOffset] <= TacDBColumn(Columns[ResizedColumn]).MinWidth then ColWidths[ResizedColumn + IndicatorOffset] := TacDBColumn(Columns[ResizedColumn]).MinWidth;
      ResizeColumns(ResizedColumn);
    end;
    FExecSizing := False;
  end
  else if not (csLoading in ComponentState) and (not FExecSizing) then CalcTableSpacePercent;
  inherited;
end;

function  TsDBGrid.GetGridSize: integer;
begin
  Result := ClientWidth - 1;
  if dgIndicator in Options then Dec(Result, IndicatorWidth);
  if dgColLines in Options then Dec(Result, Columns.Count * GridLineWidth);
end;

procedure TsDBGrid.ResizeColumns(ResizedColumn: integer);
const
  MinWidth = 10;
var
  i: integer;
  GridSize, ColumnsSize:integer;
  UnresizedSize: integer;
  K: double;
  Curr,Prev: double;
  Width: integer;
  MinimizeRest: boolean;
  VisiblePercent: double;
begin
  if Columns.Count = 0 then Exit;

  GridSize := ClientWidth - 1;
  if dgIndicator in Options then Dec(GridSize, IndicatorWidth);
  if dgColLines in Options then for i := 0 to Columns.Count - 1 do if TacDBColumn(Columns[i]).Visible then Dec(GridSize, GridLineWidth);

  if ResizedColumn > -1 then begin
    ColumnsSize := 0;
    UnresizedSize := 0;
    MinimizeRest := False;
    for i := 0 to Columns.Count - 1 do begin
      if i <= ResizedColumn then begin
        Inc(UnresizedSize, ColWidths[i + IndicatorOffset]);
        if i = ResizedColumn then
          if ColumnsSize + ColWidths[i + IndicatorOffset] + (Columns.Count - i) * MinWidth > GridSize then begin
            ColWidths[i + IndicatorOffset] := GridSize - ColumnsSize - (Columns.Count - i - 1) * MinWidth;
            MinimizeRest := True;
          end
          else if i = Columns.Count - 1 then ColWidths[i + IndicatorOffset] := GridSize - ColumnsSize;
      end
      else if MinimizeRest then ColWidths[i + IndicatorOffset] := MinWidth;

      Inc(ColumnsSize, ColWidths[i + IndicatorOffset]);
    end;

    if ColumnsSize = UnresizedSize then Exit;

    K := (GridSize - UnresizedSize) / (ColumnsSize - UnresizedSize);

    ColumnsSize := 0;
    Prev := 0;
    for i := 0 to Columns.Count - 1 do begin
      if i <= ResizedColumn then Curr := Prev + ColWidths[i + IndicatorOffset] else begin
        Curr := Prev + ColWidths[i + IndicatorOffset]*K;
        if i < Columns.Count - 1 then Width := Round(Curr - Prev) else Width := GridSize - ColumnsSize;
        if Width < TacDBColumn(Columns[i]).MinWidth then Width := TacDBColumn(Columns[i]).MinWidth;
        ColWidths[i + IndicatorOffset] := Width;
      end;
      Inc(ColumnsSize, ColWidths[i + IndicatorOffset]);
      Prev := Curr;
    end;
    CalcTableSpacePercent;
  end
  else begin // for a full resize
    Inc(GridSize, 2);
    if FColumnStretch then begin
      VisiblePercent := 0;
      for i := 0 to Columns.Count - 1 do
        if TacDBColumn(Columns[i]).Visible then VisiblePercent := VisiblePercent + TacDBColumn(Columns[i]).FTableSpacePercent;
      if VisiblePercent < 0.0001 then VisiblePercent := 1;
    end
    else VisiblePercent := 1;
    for i := 0 to Columns.Count - 1 do ColWidths[i + IndicatorOffset] := Trunc(TacDBColumn(Columns[i]).FTableSpacePercent * GridSize / VisiblePercent);
  end;
end;

{ Grid drawing }

procedure TsDBGrid.GetCellProps(Field: TField; AFont: TFont; var Background: TColor; State: TGridDrawState; StateEx: TGridDrawStateEx);
begin
  if Assigned(FOnGetCellParams) then FOnGetCellParams(Self, Field, AFont, Background, State, StateEx);
end;

procedure WriteText(ACanvas: TCanvas; ARect: TRect; DX, DY: integer; const Text: string; Alignment: TAlignment; ARightToLeft: boolean);
const
  AlignFlags : array [TAlignment] of integer = (DT_LEFT or DT_WORDBREAK or DT_EXPANDTABS or DT_NOPREFIX, DT_RIGHT or DT_WORDBREAK or DT_EXPANDTABS or DT_NOPREFIX, DT_CENTER or DT_WORDBREAK or DT_EXPANDTABS or DT_NOPREFIX);
  RTL: array [boolean] of integer = (0, DT_RTLREADING);
var
  B, R: TRect;
  Hold, Left: integer;
  I: TColorRef;
begin
  I := ColorToRGB(ACanvas.Brush.Color);
  if GetNearestColor(ACanvas.Handle, I) = I then begin
    { In BiDi, because we changed the window origin, the text that does not
      change alignment, actually gets its alignment changed. }
    if (ACanvas.CanvasOrientation = coRightToLeft) and (not ARightToLeft) then ChangeBiDiModeAlignment(Alignment);
    case Alignment of
      taLeftJustify: Left := ARect.Left + DX;
      taRightJustify: Left := ARect.Right - ACanvas.TextWidth(Text) - 3;
      else Left := ARect.Left + (ARect.Right - ARect.Left) shr 1 - (ACanvas.TextWidth(Text) shr 1);
    end;
    acTextRect(ACanvas, ARect, Left, ARect.Top + DY, Text);
  end
  else begin                  { Use FillRect and Drawtext for different colors }
    if ACanvas.Brush.Style <> bsClear then begin
      DrawBitmap.Canvas.Lock;
      try
        with DrawBitmap, ARect do begin{ Use offscreen bitmap to eliminate flicker and brush origin tics in painting / scrolling.    }
          Width := Max(Width, Right - Left);
          Height := Max(Height, Bottom - Top);
          R := Rect(DX, DY, Right - Left - 1, Bottom - Top - 1);
          B := Rect(0, 0, Right - Left, Bottom - Top);
        end;
        with DrawBitmap.Canvas do begin
          Font := ACanvas.Font;
          Font.Color := ACanvas.Font.Color;
          Brush := ACanvas.Brush;
          Brush.Style := bsSolid;
          FillRect(B);
          SetBkMode(Handle, TRANSPARENT);
          if (ACanvas.CanvasOrientation = coRightToLeft) then ChangeBiDiModeAlignment(Alignment);
          acDrawText(Handle, PacChar(Text), R, AlignFlags[Alignment] or RTL[ARightToLeft]);
        end;
        if (ACanvas.CanvasOrientation = coRightToLeft) then begin
          Hold := ARect.Left;
          ARect.Left := ARect.Right;
          ARect.Right := Hold;
        end;
        ACanvas.CopyRect(ARect, DrawBitmap.Canvas, B);
      finally
        DrawBitmap.Canvas.Unlock;
      end;
    end
    else begin
    end;
  end;
end;

function TsDBGrid.GetButtonRect(Cell: TGridCoord): TRect;
var
  aCellRect: TRect;
begin
  aCellRect := CellRect(Cell.X, Cell.Y);
  if (aCellRect.Right - aCellRect.Left < aCellRect.Bottom - aCellRect.Top + 5) then begin
    Result := Rect(0, 0, 0, 0);
    exit;
  end;
  Result.Left := aCellRect.Right - (aCellRect.Bottom - aCellRect.Top)+1;
  Result.Right := aCellRect.Right-1;
  Result.Top := aCellRect.Top+1;
  Result.Bottom := aCellRect.Bottom-1;
end;

function TsDBGrid.IsOnButton(X, Y: integer): boolean;
var
  Cell: TGridCoord;
  Column: TColumn;
  aCellRect: TRect;
  ButtonRect: TRect;
begin
  Cell := MouseCoord(X,Y);
  Column := Columns[RawToDataColumn(Cell.X)];
  // detecting - is there a button on cell?
  if Assigned(Column.Field) then Result := Column.Field.DataType in [ftMemo,ftFmtMemo {$IFNDEF VER4}, ftOraClob {$ENDIF}] else Result := False;
  aCellRect := CellRect(Cell.X, Cell.Y);
  if Result and (aCellRect.Right - aCellRect.Left < aCellRect.Bottom - aCellRect.Top + 5) then Result := False;
  if Result then begin // button present
    ButtonRect := GetButtonRect(Cell);
    Result := PtInRect(ButtonRect,Point(X,Y))
  end
  else { there is no button on cell } Result := False;
end;

procedure TsDBGrid.DrawButton(X, Y: integer; State: boolean);
var
  ButtonRect: TRect;
  Cell: TGridCoord;
  Hi, i, Diam: integer;
  Flag: integer;
begin
  Cell.X := X; Cell.Y := Y;
  ButtonRect := GetButtonRect(Cell);
  Canvas.Brush.Style := bsSolid;
  Canvas.Brush.Color := clBtnFace;
  Canvas.FillRect(ButtonRect);
  Canvas.Pen.Color := clBlack;
  Canvas.Pen.Style := psSolid;
  Canvas.Brush.Color := clBlack;

  if State then Flag := BDR_SUNKENINNER else Flag := BDR_RAISEDINNER;

  DrawEdge(Canvas.Handle, ButtonRect, Flag, BF_TOPLEFT );
  InflateRect(ButtonRect, -1, -1);
  DrawEdge(Canvas.Handle, ButtonRect, Flag, BF_BOTTOMRIGHT);
  InflateRect(ButtonRect, 1, 1);
  Canvas.MoveTo(ButtonRect.Left, ButtonRect.Bottom - 1);
  Canvas.LineTo(ButtonRect.Right - 1, ButtonRect.Bottom - 1);
  Canvas.LineTo(ButtonRect.Right - 1, ButtonRect.Top - 1);

  Diam := (ButtonRect.Bottom - ButtonRect.Top) div 7;
  Hi := (ButtonRect.Bottom - ButtonRect.Top - Diam) div 2;
  inc(ButtonRect.Left,Diam * 2 - 1);
  if State then begin
    inc(ButtonRect.Left);
    inc(ButtonRect.Top);
  end;
  for i := 0 to 2 do Canvas.Ellipse(ButtonRect.Left + i * Diam * 2 ,ButtonRect.Top + Hi, ButtonRect.Left + i * Diam * 2 + Diam, ButtonRect.Top + Hi + Diam);
end;

procedure TsDBGrid.DrawColumnCell(const Rect: TRect; DataCol: integer; Column: TColumn; State: TGridDrawState);
const
  ThreeDot = '...';
var
  NewBackgrnd: TColor;
  Field: TField;
  Value: string;
  TextWidth: integer;
  ThreeDotWidth: integer;
  Alignment: TAlignment;
  ColWidth, SelNdx: integer;
  StateEx: TGridDrawStateEx;
  TextMargin: integer;
  i: integer;
  isDrawButton: boolean;
  OldCanvasFont : TFont;
  CI : TCacheInfo;
begin
  inherited DrawColumnCell(Rect, DataCol, Column, State);
  Field := Column.Field;
  if Assigned(Column.Field) then begin
    Value := Column.Field.DisplayText;
    isDrawButton := Column.Field.DataType in [ftMemo, ftFmtMemo {$IFNDEF VER4}, ftOraClob {$ENDIF}];
  end
  else begin
    Value := '';
    isDrawButton := False;
  end;

  isDrawButton := isDrawButton and (gdSelected in State) and not (dgRowSelect in Options);
  if isDrawButton and (Rect.Right - Rect.Left < Rect.Bottom - Rect.Top + 5) then isDrawButton := False;
//  if Column.Alignment = taLeftJustify then Alignment := Column.Title.Alignment else
  Alignment := Column.Alignment;

  if Alignment = taRightJustify then TextMargin:= 4 else TextMargin := 2;

  ThreeDotWidth := Canvas.TextWidth(ThreeDot);
  TextWidth := Canvas.TextWidth(Value) + TextMargin;

  OldCanvasFont := TFont.Create;
  OldCanvasFont.Assign(Canvas.Font);
  try
    ColWidth := Column.Width;  // changes font and brush
    Canvas.Font.Assign(OldCanvasFont);
  finally
    OldCanvasFont.Free;
  end;

  if isDrawButton then ColWidth := ColWidth - (Rect.Bottom - Rect.Top);
  if TextWidth > ColWidth then begin
    if Field is TNumericField then begin
      for i := 1 to Length(Value) do if (Value[i] >= '0') and (Value[i] <= '9') then Value[i] := '#';
    end
    else begin
      while (TextWidth > ColWidth) and (Length(Value) > 1) do begin
        SetLength(Value, Length(Value) - 1);
        TextWidth := Canvas.TextWidth(Value) + TextMargin + ThreeDotWidth;
      end;
      Value := Value + ThreeDot;
    end;
    Alignment := taLeftJustify;
  end;

  if HighlightCell(Col, Row, Value, State) then begin
    Include(StateEx, geHighlight);
    if not FActiveRowSelected then Include(StateEx, geMultiSelected);
  end;
  if FActiveRowSelected then Include(StateEx, geActiveRow);

  if HighlightCell(Col, Row, Value, State) then begin
    Canvas.Brush.Color := clHighlight;
    Canvas.Font.Color := clHighlightText;
  end;

  if Enabled then begin
    NewBackgrnd := Canvas.Brush.Color;
    GetCellProps(Field, Canvas.Font, NewBackgrnd, State, StateEx);
    Canvas.Brush.Color := NewBackgrnd;
  end
  else Canvas.Font.Color := clGrayText;

  if FDefaultDrawing then begin
    if ([gdSelected, gdFocused] = State) and Focused and SkinData.Skinned then begin
      SelNdx := SkinData.SkinManager.GetSkinIndex(s_Selection);
      CI.FillColor := Color;
      CI.Ready := False;
      PaintItem(SelNdx, s_Selection, CI, True, 1, Rect, Point(0, 0), Canvas.Handle, SkinData.SkinManager);
      Canvas.Brush.Style := bsClear;
      Canvas.Font.Color := SkinData.SkinManager.GetHighLightFontColor;
    end;
    WriteText(Canvas, Rect, 2, 2, Value, Alignment, UseRightToLeftAlignmentForField(Column.Field, Alignment));
    if (gdSelected in State) and ((dgAlwaysShowSelection in Options) or Focused) and not (csDesigning in ComponentState)
      and not (dgRowSelect in Options) and (UpdateLock = 0) and (ValidParentForm(Self).ActiveControl = Self) then Windows.DrawFocusRect(Canvas.Handle, Rect);
  end;

  inherited DrawColumnCell(Rect, DataCol, Column, State);
  if isDrawButton then begin
    if FCellButtonDown > -1 then DrawButton(Col, Row, FCellButtonPressed) else DrawButton(COl, Row, False);
  end;
end;

function  TsDBGrid.GetTitleLevel(Level: integer): TRect;
begin
  if Columns.Count = 0 then begin
    Result := Rect(0, 0, 0, 0);
    Exit;
  end;
  Result.Top    := Level*(DefaultRowHeight + 1);
  Result.Bottom := Result.Top + (DefaultRowHeight + 1);
  Result.Left   := 0;
  Result.Right  := 0;
  if dgRowLines in Options then dec(Result.Bottom);
end;

procedure TsDBGrid.CalcTitleLevel(Level: integer; var aRect: TRect);
var
  X: TRect;
begin
  if Columns.Count = 0 then begin
    aRect.Top   := 0;
    aRect.Bottom:= 0;
    Exit;
  end;
  X := GetTitleLevel(Level);
  aRect.Top    := X.Top;
  aRect.Bottom := X.Bottom;
end;

procedure TsDBGrid.DrawCell(ACol,ARow: longint; ARect: TRect; AState: TGridDrawState);
var
  FrameOffs: Byte;
  // Std mode
  procedure DrawTitleCell(ACol, ARow: integer; Column: TColumn; var AState: TGridDrawState);
  const
    ScrollArrows: array [boolean, boolean] of integer = ((DFCS_SCROLLRIGHT, DFCS_SCROLLLEFT), (DFCS_SCROLLLEFT, DFCS_SCROLLRIGHT));
  var
    MasterCol: TColumn;
    CellRect: TRect;
    TitleRect, TextRect: TRect;
    Caption: string;
    CaptionWidth: integer;
    CurLevel: integer;
    CurCaption: string;
    lvCheckLeft, lvCheckRight, lvShowCaption, lvUpBorder, lvDownBorder, lvLeftBorder, lvRightBorder, lvCheckTextWidth : boolean;
    TmpCaption: string;
    lvTmpCol: TColumn;
    lvTmpColIndex: integer;
    lvCaptionXOffset: integer;
    lvCaptionAligment : TAlignment;
    CellFlag: cardinal;
    CaptionDepth: integer;
    PressOffset: integer;
  begin
    CellRect  := CalcTitleRect(Column, ARow, MasterCol);
    TitleRect := CellRect;

    if MasterCol = nil then begin
      Canvas.FillRect(ARect);
      Exit;
    end;

    Canvas.Font := MasterCol.Title.Font;
    Canvas.Brush.Color := MasterCol.Title.Color;
    Canvas.FillRect(ARect);
    TextRect := TitleRect;

    Caption := MasterCol.Title.Caption;
    lvCheckLeft  := True;
    lvCheckRight := True;
    lvShowCaption:= True;
    lvLeftBorder := True;
    lvRightBorder:= True;
    if TacColumnTitle(MasterCol.Title).IsCaptionStored then CaptionDepth := GetCaptionDepth(Caption,FLevelDelimiterChar) else CaptionDepth := 1;
    FrameOffs := 1;
    if (Column.Index = FTitleButtonDown) and (dgRowLines in Options) then PressOffset := 1 else PressOffset := 0;
    for CurLevel := 0 to FHeaderHeight - 1 do begin
      // Check dependencies
      if TacColumnTitle(MasterCol.Title).IsCaptionStored then
        CurCaption := GetCaptionLevel(Caption,CurLevel,FLevelDelimiterChar)
      else
        if CurLevel = 0 then CurCaption := Caption else CurCaption := '';
      lvDownBorder := (FHeaderHeight - 1 = CurLevel) or (GetCaptionLevel(Caption,CurLevel+1,FLevelDelimiterChar)<>'');
      lvUpBorder   := (CurCaption <> '');
      lvCaptionXOffset := 0;
      if CurCaption <> '' then begin
        if lvCheckLeft then begin
          lvLeftBorder := True;
          lvShowCaption:= True;
          if (Column.Index = 0) or (CurLevel = (CaptionDepth-1)) then lvCheckLeft := False else begin
            lvTmpColIndex := Column.Index-1;
            while lvTmpColIndex >= 0 do begin
              lvTmpCol := TColumn(MasterCol.Collection.Items[lvTmpColIndex]);
              tmpCaption := GetCaptionLevel(lvTmpCol.Title.Caption,CurLevel,FLevelDelimiterChar);
              if UpperCase(tmpCaption) <> UpperCase(CurCaption) then begin
                if lvTmpColIndex = Column.Index - 1 then lvCheckLeft := False;
                break;
              end
              else begin
                lvShowCaption := False;
                lvLeftBorder := False;
                inc(lvCaptionXOffset, lvTmpCol.Width);
                if dgColLines in Options then
                  inc(lvCaptionXOffset);
                dec(lvTmpColIndex)
              end;
            end;
          end;
        end;
        if lvCheckRight then begin
          lvRightBorder := True;
          if (Column.Index = MasterCol.Collection.Count - 1) or (CurLevel = (CaptionDepth-1)) then
            lvCheckRight := False
          else begin
            lvTmpColIndex := Column.Index+1;
            lvTmpCol := TColumn(MasterCol.Collection.Items[lvTmpColIndex]);
            tmpCaption := GetCaptionLevel(lvTmpCol.Title.Caption,CurLevel,FLevelDelimiterChar);
            if UpperCase(tmpCaption) <> UpperCase(CurCaption) then lvCheckRight := False else lvRightBorder := False;
          end;
        end;
      end;

      //Check if we need to control caption width
      if Column.Index = MasterCol.Collection.Count - 1 then lvCheckTextWidth := True else begin
        lvTmpColIndex := Column.Index+1;
        lvTmpCol := TColumn(MasterCol.Collection.Items[lvTmpColIndex]);
        tmpCaption := GetCaptionLevel(lvTmpCol.Title.Caption,CurLevel,FLevelDelimiterChar);
        if UpperCase(tmpCaption) <> UpperCase(CurCaption) then lvCheckTextWidth := True else lvCheckTextWidth := False;
      end;

      // draw text for level
      TitleRect := CellRect;
      CalcTitleLevel(CurLevel,TitleRect);
      TextRect := TitleRect;
      InflateRect(TextRect,-1,-1);

      if not lvRightBorder then begin
        inc(TextRect.Right);
        if (dgColLines in Options) then inc(TextRect.Right);
      end;

      if CurLevel <> (CaptionDepth-1) then begin
        Canvas.Font := Self.TitleFont;
        Canvas.Brush.Color := Self.FixedColor;
        lvCaptionAligment := taLeftJustify;
       end
       else begin
        Canvas.Font := MasterCol.Title.Font;
        Canvas.Brush.Color := MasterCol.Title.Color;
        lvCaptionAligment := MasterCol.Title.Alignment;
       end;
       Canvas.FillRect(TextRect);

      if lvShowCaption then begin
        CaptionWidth := Canvas.TextWidth(CurCaption);
        if lvCheckTextWidth and (CaptionWidth > TextRect.Right - TextRect.Left) then begin
          while (CaptionWidth > TextRect.Right - TextRect.Left) and (Length(CurCaption) > 1) do begin
            SetLength(CurCaption, Length(CurCaption) - 1);
            CaptionWidth := Canvas.TextWidth(CurCaption) + Canvas.TextWidth('...');
          end;
          CurCaption := CurCaption + '...';
        end;
        WriteText(Canvas, TextRect, FrameOffs + PressOffset, FrameOffs + PressOffset, CurCaption, lvCaptionAligment, IsRightToLeft);
      end
      else
        if CurCaption = '' then
          WriteText(Canvas, TextRect, FrameOffs, FrameOffs, '', lvCaptionAligment, IsRightToLeft)
        else begin // mean there is coninue of previous column
          if dgColLines in Options then begin
            dec(TextRect.Left,1);
            dec(lvCaptionXOffset,1);
          end;
        CaptionWidth := Canvas.TextWidth(CurCaption) - lvCaptionXOffset;
        if lvCheckTextWidth and (CaptionWidth > TextRect.Right - TextRect.Left) then begin
          while (CaptionWidth > TextRect.Right - TextRect.Left) and (Length(CurCaption) > 1) do begin
            SetLength(CurCaption, Length(CurCaption) - 1);
            CaptionWidth := Canvas.TextWidth(CurCaption) + Canvas.TextWidth('...') - lvCaptionXOffset;
          end;
          CurCaption := CurCaption + '...';
        end;
        WriteText(Canvas, TextRect, FrameOffs - lvCaptionXOffset, FrameOffs, CurCaption, lvCaptionAligment,
            IsRightToLeft);
        end;
      // draw borders for level

      CellFlag := BDR_RAISEDINNER;
      if (FTitleButtonDown = Column.Index)and(CurLevel >= CaptionDepth-1) then
        CellFlag := BDR_SUNKENINNER;
      if not lvDownBorder then begin
        Inc(TitleRect.Bottom,1);
        Canvas.Pen.Color := clBtnFace;
        Canvas.MoveTo(TitleRect.Left,TitleRect.Bottom - 2);
        Canvas.LineTo(TitleRect.Right + 1, TitleRect.Bottom - 2);
        if dgRowLines in Options then begin
          Canvas.MoveTo(TitleRect.Left, TitleRect.Bottom - 1);
          Canvas.LineTo(TitleRect.Right + 1, TitleRect.Bottom - 1);
        end;
      end;
      if not lvUpBorder then begin
        Canvas.Pen.Color := clBtnFace;
        Canvas.MoveTo(TitleRect.Left, TitleRect.Top);
        Canvas.LineTo(TitleRect.Right + 1, TitleRect.Top);
      end;
      if lvRightBorder then begin
        if (dgRowLines in Options) and (dgColLines in Options) then DrawEdge(Canvas.Handle, TitleRect, CellFlag, BF_RIGHT);
      end
      else Inc(TitleRect.Right,1);
      if dgColLines in Options then begin
        Canvas.Pen.Color := clBlack;
        Canvas.MoveTo(TitleRect.Right, TitleRect.Top);
        Canvas.LineTo(TitleRect.Right, TitleRect.Bottom + 1);
      end;
      if lvDownBorder and ((dgRowLines in Options) and (dgColLines in Options)) then DrawEdge(Canvas.Handle, TitleRect, CellFlag, BF_BOTTOM);
      if dgRowLines in Options then begin
        Canvas.Pen.Color := clBlack;
        Canvas.MoveTo(TitleRect.Left,TitleRect.Bottom);
        Canvas.LineTo(TitleRect.Right + 1,TitleRect.Bottom);
      end;
      if lvUpBorder and ((dgRowLines in Options) and (dgColLines in Options)) then DrawEdge(Canvas.Handle, TitleRect, CellFlag, BF_TOP);
      if lvLeftBorder and ((dgRowLines in Options) and (dgColLines in Options)) then DrawEdge(Canvas.Handle, TitleRect, CellFlag, BF_LEFT);
    end;
    AState := AState - [gdFixed];  // prevent box drawing later
  end;

  procedure ColumnSkinPaint(ControlRect : TRect; cIndex : Integer);
  var
    CI : TCacheInfo;
    R, TextRC   : TRect;
    TempBmp : Graphics.TBitmap;
    State, si : integer;

    R1 : TRect;
    Mode : integer;
    c : TsColor;
    Size : TSize;
    BtnIndex : integer;
    Alignment: TAlignment;
  begin
    try
      TempBmp := CreateBmp32(WidthOf(ControlRect), HeightOf(ControlRect));
      CI := MakeCacheInfo(FCommonData.FCacheBmp, ControlRect.Left, ControlRect.Top);
      R := Rect(0, 0, TempBmp.Width, TempBmp.Height);
      State := 0;
      if FTitleButtonDown > -1 then if cIndex = FTitleButtonDown then State := 2;
      si := FCommonData.SkinManager.GetSkinIndex(s_ColHeader);
      if FCommonData.SkinManager.IsValidSkinIndex(si) then begin
        PaintItem(si, s_ColHeader, Ci, True, State, r, Point(0, 0), TempBmp)
      end
      else begin
        si := FCommonData.SkinManager.GetSkinIndex(s_Button);
        PaintItem(si, s_Button, Ci, True, State, r, Point(0, 0), TempBmp)
      end;

      TempBmp.Canvas.Font.Assign(Font);
      TextRC := R;
      InflateRect(TextRC, -1, -1);
      TextRc.Left := TextRc.Left + 4 + integer(State = 2);
      TextRc.Right := TextRc.Right - TextRc.Left - 4 + integer(State = 2);
      TextRc.Top := TextRc.Top + integer(State = 2);
      TextRc.Bottom := TextRc.Bottom + integer(State = 2);

      TempBmp.Canvas.Brush.Style := bsClear;
      if cIndex >= 0 then begin
        if (Columns[cIndex].Field = nil) or (Columns[cIndex].Alignment = Columns[cIndex].Field.Alignment) then Alignment := Columns[cIndex].Title.Alignment else Alignment := Columns[cIndex].Alignment;
        WriteTextEx(TempBmp.Canvas, PChar(Columns[cIndex].Title.Caption), True, TextRc,
          DrawTextBiDiModeFlags(DT_EXPANDTABS or DT_WORDBREAK or GetStringFlags(Self, Alignment)),
          si, (State <> 0), SkinData.SkinManager);
      end
      else begin
        if FActiveRowSelected then begin // Indicator
          if (DataLink <> nil) and DataLink.Active and DataLink.Editing then begin
            TempBmp.Canvas.Font.Assign(Font);
            TempBmp.Canvas.Font.Color := FCommonData.SkinManager.gd[si].Props[0].FontColor.Color;
            TempBmp.Canvas.Font.Name := 'Courier';
            Size := acTextExtent(TempBmp.Canvas, 'I');
            TempBmp.Canvas.TextOut(R.Left + (WidthOf(R) - Size.cx) div 2 - 1, R.Top + (HeightOf(R) - Size.cy) div 2, 'I');
          end
          else begin
            BtnIndex := FCommonData.SkinManager.GetMaskIndex(FCommonData.SkinIndex, s_ScrollBtnRight, s_ItemGlyph);
            if FCommonData.SkinManager.IsValidImgIndex(BtnIndex) then begin
              if ControlIsActive(FCommonData) then c.C := FCommonData.SkinManager.gd[FCommonData.SkinIndex].HotColor else c.C := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
              R1 := R;
              R1.Top := R1.Top + 4;
              if ControlIsActive(FCommonData) then Mode := 1 else Mode := 0;
              DrawSkinGlyph(TempBmp, Point(R1.Left + (WidthOf(R1) - WidthOfImage(FCommonData.SkinManager.ma[BtnIndex])) div 2, R1.Top), Mode, 1, FCommonData.SkinManager.ma[BtnIndex], MakeCacheInfo(TempBmp));
            end;
          end;
        end;
      end;

      BitBlt(Canvas.Handle, ControlRect.Left, ControlRect.Top, R.Right, R.Bottom, TempBmp.Canvas.Handle, 0, 0, SRCCOPY);
      TempBmp.Free
    except
      Application.HandleException(Self);
    end;
  end;
var
  DrawColumn: TColumn;
begin
  if FCommonData.Skinned then begin
    if (ARow = 0) and (dgTitles in Options) then begin
      FActiveRowSelected := false;
      ARect.Right := ARect.Right + 1;
      ARect.Bottom := ARect.Bottom + 1;
      ColumnSkinPaint(ARect, ACol - IndicatorOffset);
    end
    else begin
      if DataLink.Active then
        if dgTitles in Options then
          FActiveRowSelected := ARow - 1 = DataLink.ActiveRecord
        else
          FActiveRowSelected := ARow = DataLink.ActiveRecord
      else
        FActiveRowSelected := False;

      if (ACol - IndicatorOffset) < 0 then begin
        ARect.Right := ARect.Right + 1;
        ARect.Bottom := ARect.Bottom + 1;
        ColumnSkinPaint(ARect, ACol - IndicatorOffset);
      end
      else inherited DrawCell(ACol, ARow, ARect, AState);
    end;
  end
  else begin
    if (ARow = 0) and (dgTitles in Options) then begin
      if ACol >= IndicatorOffset then begin
        DrawColumn := Columns[ACol - IndicatorOffset];
        DrawTitleCell(ACol - IndicatorOffset, ARow, DrawColumn, AState);
      end
      else begin
        inherited DrawCell(ACol, ARow, ARect, AState);
      end
    end
    else begin
      if DataLink.Active then
        if dgTitles in Options then FActiveRowSelected := ARow - 1 = DataLink.ActiveRecord else FActiveRowSelected := ARow = DataLink.ActiveRecord
      else FActiveRowSelected := False;

      inherited DrawCell(ACol, ARow, ARect, AState);

      if gdFixed in AState then begin
        if dgColLines in Options then begin
          Canvas.Pen.color := clBlack;
          Canvas.Pen.style := psSolid;
          Canvas.MoveTo(aRect.Right, aRect.Top);
          Canvas.LineTo(aRect.Right, aRect.Bottom + 1);
        end;
        if dgRowLines in Options then begin
          Canvas.Pen.color := clBlack;
          Canvas.Pen.style := psSolid;
          Canvas.MoveTo(aRect.Left, aRect.Bottom);
          Canvas.LineTo(aRect.Right, aRect.Bottom);
        end;
      end;
    end;
  end;
end;

procedure TsDBGrid.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: integer);
var
  State: TGridState;
  DrawInfo: TGridDrawInfo;
  Index: longint;
  Pos, Ofs: integer;
  OldActive: integer;
  Cell: TGridCoord;
  i: integer;
  Column: TColumn;
  Value: string;
  ColWidth, ValueWidth: integer;
begin
  FExecColAjust := False;

  if FGridState = gsNormal then begin
    CalcDrawInfo(DrawInfo);
    CalcSizingState(X, Y, State, Index, Pos, Ofs, DrawInfo);
  end
  else State := FGridState;

  if not (State in [gsColSizing]) and DataLink.Active then begin
    if (Button = mbLeft) and (dgTitles in Options) then begin
      Cell := MouseCoord(X,Y);
      if Cell.X >= IndicatorOffset then begin
        if not (dgRowSelect in Options) and (Cell.Y >= FixedRows) and (TopRow  + Cell.Y - FixedRows = Row) and IsOnButton(X,Y) then begin
          FCellButtonDown := RawToDataColumn(Cell.X);
          FCellButtonRow := Cell.Y;
          FCellButtonCol := Cell.X;
          FCellButtonBRect := GetButtonRect(Cell);
          FCellButtonRect := CellRect(Cell.X,Cell.Y);
          HideEditor;
          DrawButton(Cell.X,Cell.Y,PtInRect(FCellButtonBRect,Point(x,y)));
          FCellButtonPressed := True;
          Exit;
        end;
        if DataLink.Active and (Cell.Y < FixedRows) and FColumnSort and MouseInLowerstLevel(X, Y, nil) then begin
          i := FTitleButtonDown;
          FTitleButtonDown := RawToDataColumn(Cell.X);
          FOldTitleButtonDown := FTitleButtonDown;
          if i > -1 then InvalidateCol(i+1);
          invalidatecol(FTitleButtonDown+1);
        end;
      end;
    end;
  end;

  if (mbLeft = Button) and (State = gsColSizing) and DataLink.Active then begin
    if ssDouble in Shift then begin
      Index := Min(RawToDataColumn(MouseCoord(X, Y).X), RawToDataColumn(MouseCoord(X - 7, Y).X));
      if Index < 0 then Index := Columns.Count - 1;
      Column := Columns[Index];
      ColWidth := 0;
      OldActive := DataLink.ActiveRecord;
      try
        for i := TopRow - 1 to VisibleRowCount - 1 do begin
          Datalink.ActiveRecord := i;
          if Assigned(Column.Field) then Value := Column.Field.DisplayText else Value := '';
          ValueWidth := Canvas.TextWidth(Value);
          if ValueWidth > ColWidth then ColWidth := ValueWidth;
        end;
      finally
        DataLink.ActiveRecord := OldActive;
      end;
      ColWidths[Index + IndicatorOffset] := ColWidth + 4;
      FExecColAjust := True;
    end;
  end;
  inherited;
end;

procedure TsDBGrid.MouseMove(Shift: TShiftState; X, Y: integer);
var
  State: TGridState;
  DrawInfo: TGridDrawInfo;
  Index: Longint;
  Pos, Ofs: integer;
  Rect: TRect;
  Col: TColumn;
begin
  inherited;

  if FGridState = gsNormal then begin
    CalcDrawInfo(DrawInfo);
    CalcSizingState(X, Y, State, Index, Pos, Ofs, DrawInfo);
  end
  else State := FGridState;
  if FCellButtonDown > -1 then begin
    FCellButtonPressed := PtInRect(FCellButtonBRect,Point(x,y));
    DrawButton(FCellButtonCol,FCellButtonRow,FCellButtonPressed);
  end;
  if (ssLeft in Shift) and (FOldTitleButtonDown > -1) then begin
    Rect := CalcTitleRect(Columns[FOldTitleButtonDown], 0, Col);
    if (FTitleButtonDown = -1) and PtInRect(Rect,Point(X,Y)) then begin
      FTitleButtonDown := FOldTitleButtonDown;
      InvalidateCol(FTitleButtonDown + 1);
    end
    else if (FTitleButtonDown > -1) and ((Y < Rect.Top) or (Y > Rect.Bottom) or ((X < Self.Left) and
            (Columns[FTitleButtonDown].Index = 0)) or ((X > Self.Left + Self.Width) and (Columns[FTitleButtonDown].Index = Columns.Count - 1))) then begin
      Index := FTitleButtonDown + 1;
      FTitleButtonDown := -1;
      InvalidateCol(Index)
    end;
  end;
end;

procedure TsDBGrid.MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: integer);
var
  State: TGridState;
  DrawInfo: TGridDrawInfo;
  Index, i: Longint;
  Pos, Ofs: integer;
  Column: TColumn;
  Cell: TGridCoord;
  LastBtn: integer;
  Widths: array of integer;
begin
  if FGridState = gsNormal then begin
    CalcDrawInfo(DrawInfo);
    CalcSizingState(X, Y, State, Index, Pos, Ofs, DrawInfo);
  end
  else State := FGridState;
  FTitleBarUp := False;
  if not (State in [gsColSizing]) and DataLink.Active and not FExecColAjust then begin
    Cell := MouseCoord(X,Y);

    if not (dgRowSelect in Options) then if FCellButtonDown > -1 then begin
      DrawButton(Cell.X,Cell.Y,False);
      if FCellButtonDown = RawToDataColumn(Cell.X) then if FCellButtonPressed then begin
        FCellButtonDown := -1;
        FCellButtonRow := -1;
        FCellButtonCol := -1;
        invalidate;
      end;
    end;
    FCellButtonDown := -1;
    FCellButtonRow := -1;
    FCellButtonCol := -1;
    LastBtn := FTitleButtonDown;
    FOldTitleButtonDown := -1;
    if FTitleButtonDown > -1 then begin
      invalidatecol(FTitleButtonDown + 1);
      FTitleButtonDown := - 1;
    end;

    if (Button = mbLeft) and (Cell.Y = 0) and (dgTitles in Options) then begin
      if Cell.X >= IndicatorOffset then begin
        Column := Columns[RawToDataColumn(Cell.X)];
        FTitleBarUp := True;
        if TacDBColumn(Column).CanBeSorted and FColumnSort and MouseInLowerstLevel(X,Y,Column) and (LastBtn = Column.Index) then begin
          FExecSorting := True;
          BeginLayout;
          try
            SetLength(Widths, Columns.Count);
            for i := 0 to Columns.Count - 1 do Widths[i] := Columns[i].Width;
          finally
            EndLayout;
            for i := 0 to Columns.Count - 1 do Columns[i].Width := Widths[i];
            FExecSorting := False;
          end;
        end;
      end
    end;
  end;
  inherited;
  FTitleBarUp := False;
end;

procedure TsDBGrid.UpdateHeaderHeight;
var
  Cur, i: integer;
  aHeight: integer;
begin
  if not (dgTitles in Options) then begin
    RowHeights[0]:= DefaultRowHeight;
    Exit;
  end;
  FHeaderHeight := 1;
  for i := 0 to Columns.Count - 1 do begin
    if TacColumnTitle(Columns[i].Title).IsCaptionStored then Cur := GetCaptionDepth(Columns[i].Title.Caption,FLevelDelimiterChar) else Cur := 1;
    if Cur > FHeaderHeight then FHeaderHeight := Cur;
  end;
  aHeight := (DefaultRowHeight + 1) * FHeaderHeight;
  RowHeights[0]:= aHeight - 1;
end;

function TsDBGrid.GetClientRect: TRect;
begin
  Result := inherited GetClientRect;
  if dgRowLines in options then Inc(Result.Bottom);
end;

procedure TsDBGrid.LayoutChanged;
begin
  inherited;
  UpdateHeaderHeight;
end;

procedure TsDBGrid.SetLevelDelimiterChar(const Value: char);
begin
  FLevelDelimiterChar := Value;
end;

function TsDBGrid.CalcFilterBar(Column: TColumn): TRect;
var
  Rect: TRect;
  MasterCol: TColumn;
  aRow: integer;
begin
  aRow := 0;
  Rect := CalcTitleRect(Column, aRow, MasterCol);
  Rect.Top := Rect.Bottom - (DefaultRowHeight + 9);
  Result := Rect;
end;

function TsDBGrid.MouseInLowerstLevel(X, Y: integer; Column: TColumn = nil): boolean;
var
  Index: integer;
  Rect: TRect;
  MasterCol: TColumn;
begin
  Result := False;
  if Column = nil then begin
    Index   := RawToDataColumn(MouseCoord(X, Y).X);
    if Index < 0 then exit;
    Column  := Columns[Index];
  end;
  Index := 0;
  Rect    := CalcTitleRect(Column, Index, MasterCol);
  Index   := GetCaptionDepth(Column.Title.Caption, FLevelDelimiterChar);
  if Index > 0 then begin
    Index   := (Index-1) * (DefaultRowHeight + 1);
    Rect.Top := Index;
    Rect.Bottom := CalcFilterBar(Column).top;
    Result  := PtInRect(Rect, Point(X, Y));
  end
  else Result := True;
end;

procedure TsDBGrid.CalcTableSpacePercent;
var
  ColumnsSize, i: integer;
begin
  ColumnsSize := 0;
  for i := 0 to Columns.count - 1 do
    if ColWidths[i + IndicatorOffset] > 0 then ColumnsSize := ColumnsSize + ColWidths[i + IndicatorOffset];
  for i := 0 to Columns.Count - 1 do
    if ColumnsSize > 0 then TacDBColumn(Columns[i]).FTableSpacePercent := ColWidths[i + IndicatorOffset] / ColumnsSize;
end;

function TsDBGrid.CanEditShow: boolean;
begin
  if (Columns.Count > 0) and Assigned(SelectedField) and (SelectedField is TMemoField) then Result := False else Result := inherited CanEditShow;
end;

procedure TsDBGrid.TopLeftChanged;
{$IFDEF VER4}
var
  R: TRect;
  DrawInfo: TGridDrawInfo;
{$ENDIF}
begin
  inherited;
{$IFDEF VER4}
  if HandleAllocated and (dgTitles in Options) then begin
    CalcFixedInfo(DrawInfo);
    R := Rect(0, 0, Width, DrawInfo.Vert.FixedBoundary);
    InvalidateRect(Handle, {$IFNDEF CLR}@{$ENDIF}R, False);
  end;
{$ENDIF}
end;

procedure TsDBGrid.AdjustColumns;
var
  Width: array of integer;
  i, j, OldActive: integer;
  CurWidth: Integer;
begin
  if not DataLink.Active then Exit;
  SetLength(Width, Columns.Count);
  OldActive := DataLink.ActiveRecord;
  try
    for i := TopRow - 1 to VisibleRowCount - 1 do begin
      Datalink.ActiveRecord := i;
      for j := 0 to Columns.Count - 1 do begin
        if Assigned(Columns[j].Field) then CurWidth := Canvas.TextWidth(Columns[j].Field.DisplayText) else CurWidth := 0;
        if CurWidth > Width[j] then Width[j] := CurWidth;
      end;
    end;
  finally
    DataLink.ActiveRecord := OldActive;
  end;
  for i := 0 to Columns.Count - 1 do begin
    CurWidth := Canvas.TextWidth(Columns[i].Title.Caption);
    if CurWidth > Width[i] then ColWidths[i + IndicatorOffset] := CurWidth + 4 else ColWidths[i + IndicatorOffset] := Width[i] + 4;
  end;
end;

function TsDBGrid.GetColumns: TacDBGridColumns;
begin
  Result := TacDBGridColumns(inherited Columns);
end;

procedure TsDBGrid.SetColumns(const Value: TacDBGridColumns);
begin
  inherited Columns.Assign(Value);
end;

procedure TsDBGrid.WMMouseWheel(var Message: TWMMouseWheel);
begin
  if Message.WheelDelta > 0 then SendMessage(Handle, WM_KEYDOWN, VK_UP, 0) else SendMessage(Handle, WM_KEYDOWN, VK_DOWN, 0); // ?
end;

procedure TsDBGrid.TitleClick(Column: TColumn);
begin
  if FTitleBarUp then inherited TitleClick(Column);
end;

procedure TsDBGrid.WndProc(var Message: TMessage);
var
  SavedDC{, DC} : hdc;
begin
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end;
    AC_SETNEWSKIN : if (LongWord(Message.LParam) = LongWord(SkinData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      exit
    end;
    AC_REFRESH : if (LongWord(Message.LParam) = LongWord(SkinData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      if FCommonData.Skinned and not (csLoading in ComponentState) then begin
        RefreshGridScrolls(SkinData, ListSW);
        RedrawWindow(Handle, nil, 0, RDW_FRAME or RDW_INVALIDATE or RDW_UPDATENOW);
      end;
      Exit;
    end;
    AC_REMOVESKIN : if (LongWord(Message.LParam) = LongWord(SkinData.SkinManager)) and (SkinData.FOwnerControl <> nil) and (SkinData.FOwnerControl is TCustomGrid) then begin
      Color := clWindow;
      SkinData.SkinIndex := -1;
      RedrawWindow(Handle, nil, 0, RDW_FRAME or RDW_INVALIDATE or RDW_UPDATENOW);
      SetWindowPos(Handle, 0, 0, 0, 0, 0, SWP_NOSIZE or SWP_NOMOVE or SWP_NOZORDER or SWP_NOCOPYBITS or SWP_NOSENDCHANGING or SWP_NOREPOSITION or SWP_FRAMECHANGED);
    end;
  end;
  case Message.Msg of
    WM_ERASEBKGND : if SkinData.Skinned then begin
      SkinData.FUpdating := SkinData.Updating;
      Message.Result := 1;
      Exit;
    end;

    WM_PRINT : if SkinData.Skinned then begin
      SkinData.CtrlSkinState := SkinData.CtrlSkinState or ACS_PRINTING;
      if ListSW = nil then RefreshGridScrolls(SkinData, ListSW);
      InitCtrlData(Handle, ListSW.ParentWnd, ListSW.WndRect, ListSW.ParentRect, ListSW.WndSize, ListSW.WndPos, ListSW.Caption);
      SkinData.Updating := False;
      SkinData.BGChanged := True;

      if not ListSW.ParamsChanged then ListSW.SetSkinParams;
      PrepareCache(SkinData, Handle, False);

      SavedDC := SaveDC(TWMPaint(Message).DC);
      try
        SendMessage(Handle, WM_PRINTCLIENT, longint(TWMPaint(Message).DC), PRF_CLIENT or PRF_OWNED);
        Message.Result := Ac_NCPaint(ListSW, Handle, Message.wParam, Message.lParam, -1, TWMPaint(Message).DC);
      finally
        RestoreDC(TWMPaint(Message).DC, SavedDC);
      end;
      BitBltBorder(TWMPaint(Message).DC, 0, 0, SkinData.FCacheBmp.Width, SkinData.FCacheBmp.Height, SkinData.FCacheBmp.Canvas.Handle, 0, 0, ListSW.cxLeftEdge);
      SkinData.CtrlSkinState := SkinData.CtrlSkinState and not ACS_PRINTING;
      Message.Result := 2;
      Exit;
    end;

  end;
  CommonWndProc(Message, FCommonData);
  inherited;
  if ControlIsReady(Self) and FCommonData.Skinned then begin
    case Message.Msg of
      CM_SHOWINGCHANGED : RefreshGridScrolls(SkinData, ListSW);
    end;
  end;
end;

procedure TsDBGrid.PaintWindow(DC: HDC);
var
  SavedCanvas : TCanvas;
  bWidth : integer;
  Bmp : TBitmap;
  R : TRect;
begin
  if FCommonData.Skinned then begin
    if not (csDestroying in ComponentState) then begin
      SavedCanvas := _TCustomControl(Self).FCanvas;
      Bmp := CreateBmp32(Width, Height);
      _TCustomControl(Self).FCanvas := Bmp.Canvas;
      try
        GetClipBox(DC, R);
        Paint;
        if (SkinData.CtrlSkinState and ACS_PRINTING = ACS_PRINTING) then bWidth := 2 else bWidth := 0;
        BitBlt(DC, bWidth, bWidth, Width, Height, Bmp.Canvas.Handle, 0, 0, SRCCOPY);
      finally
        _TCustomControl(Self).FCanvas := SavedCanvas;
        Bmp.Free;
      end;
    end
  end
  else inherited;
end;

function TsDBGrid.CreateEditor: TInplaceEdit;
begin
  Result := inherited CreateEditor;
  Repaint;
end;

end.
