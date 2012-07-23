unit acDBCtrlGrid;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, DBCtrls, DB, dbcgrids, sConst, acntUtils, sGraphUtils, sGlyphUtils, math,
  sCommonData, sDefaults, acSBUtils;

type
  TsDBCtrlGrid = class;

{ TsDBCtrlPanel }

  TsDBCtrlPanel = class(TDBCtrlPanel)
  private
    FDisabledKind: TsDisabledKind;
    DrawIndex : integer;
    procedure WMPaint(var Message: TWMPaint); message WM_PAINT;
    function GetDBCtrlGrid: TsDBCtrlGrid;
  protected
    procedure PaintWindow(DC: HDC); override;
    procedure WndProc (var Message: TMessage); override;
    procedure PrepareCache(pR : TPoint);
  public
    FCommonData: TsCommonData;
    constructor CreateLinked2(DBCtrlGrid: TDBCtrlGrid);
    destructor Destroy; override;
    procedure Loaded; override;
    property DBCtrlGrid : TsDBCtrlGrid read GetDBCtrlGrid;
  end;

{ TsDBCtrlGrid }

  TsDBCtrlGrid = class(TDBCtrlGrid)
  private
    FBitmapCount: Integer;
    FPanelBitmap: HBitmap;
    FSaveBitmap: HBitmap;
    FPanelDC: HDC;
    FCommonData: TsCommonData;
    FPanelSkin: TsSkinSection;
    procedure SetDisabledKind(const Value: TsDisabledKind);
    function GetDataLink: TDataLink;
    function GetDisabledKind: TsDisabledKind;
    procedure SetPanelSkin(const Value: TsSkinSection);
  protected
    procedure CreatePanelBitmap;
    procedure DestroyPanelBitmap;
    function GetPanelBounds(Index: Integer): TRect;
    procedure DrawPanel(DC: HDC; Index: Integer);
    procedure DrawPanelBackground(DC: HDC; const R: TRect; Erase, Selected: Boolean);
    procedure PaintWindow(DC: HDC); override;
    procedure WndProc (var Message: TMessage); override;
    procedure PrepareCache;
  public
    ListSW : TacScrollWnd;
    ScrollsUpdating : boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;
    procedure AfterConstruction; override;
    property DataLink : TDataLink read GetDataLink;
    property Panel;
  published
    property DisabledKind : TsDisabledKind read GetDisabledKind write SetDisabledKind default DefDisabledKind;
    property SkinData : TsCommonData read FCommonData write FCommonData;
    property PanelSkin : TsSkinSection read FPanelSkin write SetPanelSkin;
  end;

implementation

uses sMessages, sMaskData, sStyleSimply, sSkinProps, sVCLUtils,
  sAlphaGraph{$IFDEF LOGGED}, sDebugMsgs{$ENDIF};

type

  TDBCtrlGrid_ = class(TWinControl)
  private
    FDataLink: TDBCtrlGridLink;
    FPanel: TDBCtrlPanel;
  end;

  TDBCtrlPanel_ = class(TWinControl)
  private
    FDBCtrlGrid: TDBCtrlGrid;
  end;

{ TsDBCtrlPanel }

constructor TsDBCtrlPanel.CreateLinked2(DBCtrlGrid: TDBCtrlGrid);
begin
  inherited CreateLinked(DBCtrlGrid);
  DrawIndex := -1;
  ParentColor := False;
  FCommonData := TsCommonData.Create(Self, True);
  FCommonData.COC := COC_TsCustom;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := TsDBCtrlGrid(DBCtrlGrid).PanelSkin;
  FDisabledKind := DefDisabledKind;
end;

destructor TsDBCtrlPanel.Destroy;
begin
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited;
end;

function TsDBCtrlPanel.GetDBCtrlGrid: TsDBCtrlGrid;
begin
  Result := TDBCtrlPanel_(Self).FDBCtrlGrid as TsDBCtrlGrid;
end;

procedure TsDBCtrlPanel.Loaded;
begin
  inherited Loaded;
  try
    FCommonData.Loaded;
  except
    Application.HandleException(Self);
  end;
end;

procedure TsDBCtrlPanel.PaintWindow(DC: HDC);
var
  R: TRect;
  Selected: Boolean;
begin
  Selected := False;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    if DrawIndex = -1
      then R := DBCtrlGrid.GetPanelBounds(DBCtrlGrid.PanelIndex)
      else R := DBCtrlGrid.GetPanelBounds(DrawIndex);

    PrepareCache(Point(R.Left,R.Top));
    UpdateCorners(FCommonData, 0);

    with DBCtrlGrid do begin
      if DataLink.Active then begin
        Selected := (DataLink.ActiveRecord = PanelIndex);

        FCommonData.FCacheBmp.Canvas.Font := Font;
        FCommonData.FCacheBmp.Canvas.Brush.Style := bsSolid;
        FCommonData.FCacheBmp.Canvas.Brush.Color := Color;
        PaintPanel(DataLink.ActiveRecord);
      end
    end;
    SetParentUpdated(Self);
    BitBlt(DC, 0, 0, Width, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
    if DBCtrlGrid.ShowFocus and DBCtrlGrid.Focused and Selected then DrawFocusRect(DC, Rect(2, 2, Width - 2, Height - 2));
  end;
end;

procedure TsDBCtrlPanel.PrepareCache(pR : TPoint);
begin
  DBCtrlGrid.PrepareCache;
  InitCacheBmp(FCommonData);
  PaintItem(FCommonData, GetParentCache(FCommonData), False, 0, Rect(0, 0, Width, Height), pR, FCommonData.FCacheBmp, True);
  FCommonData.BGChanged := False;
end;

procedure TsDBCtrlPanel.WMPaint(var Message: TWMPaint);
var
  DC: HDC;
  PS: TPaintStruct;
  i : integer;
begin
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    if Message.DC = 0 then begin
      for i := 0 to ControlCount - 1 do Controls[i].ControlState := Controls[i].ControlState + [csPaintCopy];
      DBCtrlGrid.CreatePanelBitmap;
      try
        Message.DC := DBCtrlGrid.FPanelDC;
        PaintHandler(Message);
        Message.DC := 0;
        DC := BeginPaint(Handle, PS);
        BitBlt(DC, 0, 0, Width, Height, DBCtrlGrid.FPanelDC, 0, 0, SRCCOPY);
        EndPaint(Handle, PS);
      finally
        DBCtrlGrid.DestroyPanelBitmap;
      end;
      for i := 0 to ControlCount - 1 do Controls[i].ControlState := Controls[i].ControlState - [csPaintCopy];
    end
    else PaintHandler(Message);
  end;
end;

procedure TsDBCtrlPanel.WndProc(var Message: TMessage);
begin
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end; // AlphaSkins supported
    AC_REMOVESKIN : if LongWord(Message.LParam) = LongWord(FCommonData.SkinManager) then begin
      CommonWndProc(Message, FCommonData);
      AlphaBroadCast(Self,Message);
      Exit;
    end;
    AC_SETNEWSKIN : if (LongWord(Message.LParam) = LongWord(FCommonData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      AlphaBroadCast(Self,Message);
      exit;
    end;
    AC_REFRESH : if (LongWord(Message.LParam) = LongWord(FCommonData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      AlphaBroadCast(Self,Message);
      if FCommonData.Skinned then Perform(WM_NCPAINT, 0, 0);
      Exit;
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.Updating := False;
      Perform(WM_NCPAINT, 0, 0);
    end;
    AC_GETBG : begin
      if DBCtrlGrid.FCommonData.BGChanged then DBCtrlGrid.PrepareCache;
      PacBGInfo(Message.LParam)^.Offset := Point(0, 0);
      PacBGInfo(Message.LParam)^.Bmp := DBCtrlGrid.FCommonData.FCacheBmp;
      PacBGInfo(Message.LParam)^.BgType := btCache;

{    PacBGInfo(Message.LParam)^.DrawDC := 0;
    PacBGInfo(Message.LParam)^.PleaseDraw := False;
    GetBGInfo(PacBGInfo(Message.LParam), DBCtrlGrid);}

      if DrawIndex > - 1
        then inc(PacBGInfo(Message.LParam)^.Offset.Y, DBCtrlGrid.GetPanelBounds(DrawIndex).Top)
        else inc(PacBGInfo(Message.LParam)^.Offset.Y, DBCtrlGrid.GetPanelBounds(DBCtrlGrid.PanelIndex).Top);
      Exit;
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    case Message.Msg of
      WM_PRINT : if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
        Perform(WM_PAINT, Message.WParam, Message.LParam);
        Perform(WM_NCPAINT, Message.WParam, Message.LParam);
        Exit;
      end;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
  end;
end;

{ TsDBCtrlGrid }

constructor TsDBCtrlGrid.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

  FCommonData := TsCommonData.Create(Self, True);
  FCommonData.COC := COC_TsCustom;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := s_CheckBox;
  if FPanelSkin = '' then FPanelSkin := s_GroupBox;

  FreeAndNil(TDBCtrlGrid_(Self).FPanel);
  TDBCtrlGrid_(Self).FPanel := TsDBCtrlPanel.CreateLinked2(Self);
  AdjustSize;
end;

procedure TsDBCtrlGrid.Loaded;
begin
  inherited Loaded;
  try
    FCommonData.Loaded;
    TsDBCtrlPanel(Panel).Loaded;
  except
    Application.HandleException(Self);
  end;
  RefreshScrolls(FCommonData, ListSW);
end;

destructor TsDBCtrlGrid.Destroy;
begin
  if ListSW <> nil then FreeAndNil(ListSW);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited;
end;

procedure TsDBCtrlGrid.DrawPanel(DC: HDC; Index: Integer);
var
  SaveActive: Integer;
  R: TRect;
begin
  R := GetPanelBounds(Index);
  if Index < PanelCount then begin
    SaveActive := DataLink.ActiveRecord;
    DataLink.ActiveRecord := Index;
    TsDBCtrlPanel(Panel).DrawIndex := Index;
    if Index <> PanelIndex then begin
      Panel.PaintTo(FPanelDC, 0, 0);
    end;
    DataLink.ActiveRecord := SaveActive;
  end
  else DrawPanelBackground(FPanelDC, Panel.ClientRect, True, False);
  BitBlt(DC, R.Left, R.Top, R.Right - R.Left, R.Bottom - R.Top, FPanelDC, 0, 0, SRCCOPY);
//  UpdateScrolls(ListSW, True); 
end;

procedure TsDBCtrlGrid.DrawPanelBackground(DC: HDC; const R: TRect; Erase, Selected: Boolean);
begin
  TsDBCtrlPanel(Panel).PrepareCache(Point(R.Left, R.Top));
  PaintItem(TsDBCtrlPanel(Panel).FCommonData, GetParentCache(TsDBCtrlPanel(Panel).FCommonData), False, 0, Panel.ClientRect,
                   Point(R.Left, R.Top), TsDBCtrlPanel(Panel).FCommonData.FCacheBmp, True);
  BitBlt(DC, R.Left, R.Top, R.Right - R.Left, R.Bottom - R.Top, TsDBCtrlPanel(Panel).FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
end;

function TsDBCtrlGrid.GetPanelBounds(Index: Integer): TRect;
var
  Col, Row: Integer;
begin
  if Orientation = goVertical then begin
    Col := Index mod ColCount;
    Row := Index div ColCount;
  end
  else begin
    Col := Index div RowCount;
    Row := Index mod RowCount;
  end;
  Result.Left := PanelWidth * Col;
  Result.Top := PanelHeight * Row;
  Result.Right := Result.Left + PanelWidth;
  Result.Bottom := Result.Top + PanelHeight;
end;

procedure TsDBCtrlGrid.PaintWindow(DC: HDC);
var
  I: Integer;
  Brush: HBrush;
  M : TMessage;
begin
  if not (Panel is TsDBCtrlPanel and TsDBCtrlPanel(Panel).FCommonData.Skinned) then inherited else begin
    if csDesigning in ComponentState then begin
      Panel.Update;
      Brush := CreateHatchBrush(HS_BDIAGONAL, ColorToRGB(clBtnShadow));
      SetBkColor(DC, ColorToRGB(Color));
      FillRect(DC, ClientRect, Brush);
      DeleteObject(Brush);
      for I := 1 to ColCount * RowCount - 1 do DrawPanelBackground(DC, GetPanelBounds(I), False, DataLink.Active and (I = DataLink.ActiveRecord));
    end
    else begin
      CreatePanelBitmap;
      try
        for I := 0 to ColCount * RowCount - 1 do begin
          m := MakeMessage(SM_ALPHACMD, MakeWParam(1, AC_SETBGCHANGED), 0, 0);
          Panel.Broadcast(m);

          if (PanelCount <> 0) and (I = PanelIndex) then begin
            TsDBCtrlPanel(Panel).DrawIndex := -1;
            RedrawWindow(Panel.Handle, nil, 0, RDW_INVALIDATE or RDW_UPDATENOW or RDW_ALLCHILDREN);
          end
          else begin
            DrawPanel(DC, I);
          end;
        end;
      finally
        TsDBCtrlPanel(Panel).DrawIndex := -1;
        DestroyPanelBitmap;
      end;
    end;
    { When width or height are not evenly divisible by panel size, fill the gaps }
    if HandleAllocated then begin
      if (Height <> Panel.Height * RowCount) then BitBlt(DC, 0, Panel.Height * RowCount, Width, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
      if (Width <> Panel.Width * ColCount) then BitBlt(DC, Panel.Width * ColCount, 0, Width, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
    end;
  end;
end;

procedure TsDBCtrlGrid.SetDisabledKind(const Value: TsDisabledKind);
begin
  with TsDBCtrlPanel(Panel) do
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;


function TsDBCtrlGrid.GetDisabledKind: TsDisabledKind;
begin
  with TsDBCtrlPanel(Panel) do
    result := FDisabledKind;
end;

procedure TsDBCtrlGrid.PrepareCache;
var
  CI : TCacheInfo;
begin
  InitCacheBmp(FCommonData);
  CI := GetParentCache(FCommonData);
  PaintItem(FCommonData, CI, False, 0, Rect(0, 0, Width, Height), Point(Left, Top), FCommonData.FCacheBmp, False);
  FCommonData.BGChanged := False;
end;

procedure TsDBCtrlGrid.WndProc(var Message: TMessage);
begin
{$IFDEF LOGGED}
  AddToLog(Message);
{$ENDIF}
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end; // AlphaSkins supported
    AC_REMOVESKIN : if LongWord(Message.LParam) = LongWord(FCommonData.SkinManager) then begin
      if ListSW <> nil then begin
        FreeAndNil(ListSW);
      end;
      CommonWndProc(Message, FCommonData);
      AlphaBroadCast(Self,Message);
      RecreateWnd;
      Exit;
    end;
    AC_SETNEWSKIN : if (LongWord(Message.LParam) = LongWord(FCommonData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      AlphaBroadCast(Self,Message);
      exit;
    end;
    AC_REFRESH : if (LongWord(Message.LParam) = LongWord(FCommonData.SkinManager)) then begin
      CommonWndProc(Message, FCommonData);
      RefreshScrolls(FCommonData, ListSW);
      AlphaBroadCast(Self,Message);
      RedrawWindow(Handle, nil, 0, RDW_FRAME or RDW_INVALIDATE or RDW_UPDATENOW or RDW_ALLCHILDREN);
      Exit;
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.Updating := False;
      Perform(WM_NCPAINT, 0, 0);
    end;
    AC_GETBG : begin
      if (SkinData.BGChanged or SkinData.HalfVisible) and not SkinData.Updating then PrepareCache;

      PacBGInfo(Message.LParam)^.Offset := Point(0, 0);
      PacBGInfo(Message.LParam)^.Bmp := FCommonData.FCacheBmp;
      PacBGInfo(Message.LParam)^.BgType := btCache;

      if (WidthOf(ClientRect) <> Width) and (PacBGInfo(Message.LParam)^.BgType = btCache) and not PacBGInfo(Message.LParam)^.PleaseDraw then begin
        inc(PacBGInfo(Message.LParam)^.Offset.X, BorderWidth + BevelWidth * (integer(BevelInner <> bvNone) + integer(BevelOuter <> bvNone)));
        inc(PacBGInfo(Message.LParam)^.Offset.Y, BorderWidth + BevelWidth * (integer(BevelInner <> bvNone) + integer(BevelOuter <> bvNone)));
      end;
      Exit;
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    case Message.Msg of
      WM_PRINT : begin
        Perform(WM_PAINT, Message.WParam, Message.LParam);
        Ac_NCPaint(ListSW, Handle, Message.wParam, Message.lParam, -1, hdc(Message.WParam));
        Exit;
      end;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of
      WM_SETFONT, CM_ENABLEDCHANGED, CM_VISIBLECHANGED : begin
        FCommonData.Invalidate;
      end;
      WM_SIZE, WM_MOVE : UpdateScrolls(ListSW, True);
      WM_PASTE, WM_CUT, WM_CLEAR, WM_UNDO, WM_SETTEXT : UpdateScrolls(ListSW, True);
      WM_HSCROLL, WM_VSCROLL : begin
        UpdateScrolls(ListSW, True);
      end;
      CM_CANCELMODE, CM_CHANGED, CN_KEYDOWN, CN_KEYUP : UpdateScrolls(ListSW, True);
      WM_PARENTNOTIFY: if (Message.WParam and $FFFF = WM_CREATE) or (Message.WParam and $FFFF = WM_DESTROY) then begin
        RefreshScrolls(FCommonData, ListSW);
      end;
      WM_MOUSEWHEEL, CM_CONTROLLISTCHANGE, CM_CONTROLCHANGE : if not SkinData.Updating then begin
        UpdateScrolls(ListSW, True);
      end;
    end;
  end;   
end;

function TsDBCtrlGrid.GetDataLink: TDataLink;
begin
  Result := TDBCtrlGrid_(Self).FDataLink;
end;

procedure TsDBCtrlGrid.CreatePanelBitmap;
var
  DC: HDC;
begin
  if FBitmapCount = 0 then
  begin
    DC := GetDC(0);
    FPanelBitmap := CreateCompatibleBitmap(DC, Panel.Width, Panel.Height);
    ReleaseDC(0, DC);
    FPanelDC := CreateCompatibleDC(0);
    FSaveBitmap := SelectObject(FPanelDC, FPanelBitmap);
  end;
  Inc(FBitmapCount);
end;

procedure TsDBCtrlGrid.DestroyPanelBitmap;
begin
  Dec(FBitmapCount);
  if FBitmapCount = 0 then
  begin
    SelectObject(FPanelDC, FSaveBitmap);
    DeleteDC(FPanelDC);
    DeleteObject(FPanelBitmap);
  end;
end;

procedure TsDBCtrlGrid.AfterConstruction;
begin
  inherited AfterConstruction;
  FCommonData.Loaded;
  if HandleAllocated then RefreshScrolls(FCommonData, ListSW);
end;

procedure TsDBCtrlGrid.SetPanelSkin(const Value: TsSkinSection);
begin
  if FPanelSkin <> Value then begin
    FPanelSkin := Value;
    TsDBCtrlPanel(TDBCtrlGrid_(Self).FPanel).FCommonData.SkinSection := Value;
    FCommonData.BGChanged := True;
    RedrawWindow(Handle, nil, 0, RDW_FRAME + RDW_INVALIDATE + RDW_UPDATENOW + RDW_ALLCHILDREN);
  end;
end;

end.
