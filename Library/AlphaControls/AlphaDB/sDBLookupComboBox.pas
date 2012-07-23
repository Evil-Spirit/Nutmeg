unit sDBLookupComboBox;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, DBCtrls, sConst, acntUtils, sGraphUtils, sCommonData, sDefaults,
  sGlyphUtils, math, acSBUtils{$IFDEF LOGGED}, sDebugMsgs{$ENDIF};

type
  TsDBLookupComboBox = class(TDBLookupComboBox)
  private
    FAlignment : TAlignment;
    FButtonMargin: integer;
    FBoundLabel: TsBoundLabel;
    FCommonData: TsCommonData;
    FDisabledKind: TsDisabledKind;

    function ButtonRect: TRect;
    procedure SetAlignment(const Value: TAlignment);
    procedure SetButtonMargin(const Value: integer);
    procedure SetDisabledKind(const Value: TsDisabledKind);
  protected
    lboxhandle : hwnd;
    ListSW : TacScrollWnd;

    procedure PaintBorder;
    procedure PrepareCache;
    procedure PaintText;
    procedure OurPaintHandler;
    procedure WndProc (var Message: TMessage); override;
    procedure WMMouseWheel(var Message: TMessage); message WM_MOUSEWHEEL;
  public
    procedure AfterConstruction; override;
    constructor Create(AOwner:TComponent); override;
    destructor Destroy; override;
    procedure DropDown; override;
    function CanFocus: Boolean; override;
    procedure Loaded; override;

    property Color;
    procedure Invalidate; override;
    procedure PaintButton;
    function ButtonHeight : integer;

    function Focused: Boolean; override;
    property Alignment : TAlignment read FAlignment write SetAlignment;
    property ButtonMargin : integer read FButtonMargin write SetButtonMargin default 2;
  published
    property BoundLabel : TsBoundLabel read FBoundLabel write FBoundLabel;
    property DisabledKind : TsDisabledKind read FDisabledKind write SetDisabledKind default DefDisabledKind;
    property SkinData : TsCommonData read FCommonData write FCommonData;
  end;

implementation

uses sMessages, sMaskData, sStyleSimply, sSkinProps, sVCLUtils, sAlphaGraph;

type
{$HINTS OFF}
  TsDBLookupComboBox_ = class(TDBLookupControl)
  private
    FDataList: TPopupDataList;
    FButtonWidth: Integer;
    FText: string;
    FDropDownRows: Integer;
    FDropDownWidth: Integer;
    FDropDownAlign: TDropDownAlign;
    FListVisible: Boolean;
  end;
{$HINTS ON}

{ TsDBLookupComboBox }

procedure TsDBLookupComboBox.AfterConstruction;
begin
  inherited AfterConstruction;
  FCommonData.Loaded;
end;

function TsDBLookupComboBox.ButtonHeight: integer;
begin
  if FCommonData.Skinned and (FCommonData.SkinManager.ConstData.ComboGlyph > -1)
    then Result := HeightOf(FCommonData.SkinManager.ma[FCommonData.SkinManager.ConstData.ComboGlyph].R) div (1 + FCommonData.SkinManager.ma[FCommonData.SkinManager.ConstData.ComboGlyph].MaskType)
    else Result := 16;
end;

function TsDBLookupComboBox.ButtonRect: TRect;
var
  w : integer;
begin
  w := GetSystemMetrics(SM_CXVSCROLL);
  if UseRightToLeftAlignment then Result.Left := 2 else Result.Left := Width - w - 2;
  Result.Top := 2;
  Result.Right := Result.Left + w;
  Result.Bottom := Height - 2;
end;

function TsDBLookupComboBox.CanFocus: Boolean;
begin
  Result := False;
  if Visible then Result := inherited CanFocus;
end;

constructor TsDBLookupComboBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle - [csFixedHeight, csFramed, csOpaque];
  TControlCanvas(Canvas).Control := self;

  ParentColor := False;

  FCommonData := TsCommonData.Create(Self, {$IFDEF DYNAMICCACHE} False {$ELSE} True {$ENDIF});
  FCommonData.COC := COC_TsEdit;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := s_ComboBox;
  FDisabledKind := DefDisabledKind;

  FBoundLabel := TsBoundLabel.Create(Self, FCommonData);
  FButtonMargin := 2;
  lBoxHandle := 0;

  DoubleBuffered := True;
end;

destructor TsDBLookupComboBox.Destroy;
begin
  if lBoxHandle <> 0 then begin
    SetWindowLong(lBoxHandle, GWL_STYLE, GetWindowLong(lBoxHandle, GWL_STYLE) and not WS_THICKFRAME or WS_BORDER);
    UninitializeACScroll(lBoxHandle, True, False, ListSW);
    lBoxHandle := 0;
  end;
  if Assigned(ListSW) then FreeAndNil(ListSW);
  FreeAndNil(FBoundLabel);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited Destroy;
end;

procedure TsDBLookupComboBox.DropDown;
begin
  if SkinData.Skinned and (TsDBLookupComboBox_(Self).FDataList <> nil) and (ListSW = nil) then begin
    lBoxHandle := TsDBLookupComboBox_(Self).FDataList.Handle;
    ListSW := TacComboListWnd.Create(TsDBLookupComboBox_(Self).FDataList.Handle, nil, SkinData.SkinManager, s_Edit, False);
    TacComboListWnd(ListSW).SimplyBox := False;
    ListSW.Tag := ACT_RELCAPT;
  end;
  inherited;
end;

function TsDBLookupComboBox.Focused: Boolean;
var
  FocusedWnd: HWND;
begin
  Result := False;
  if HandleAllocated then begin
    FocusedWnd := GetFocus;
    Result := (FocusedWnd <> 0) and ((FocusedWnd = Handle) or (FocusedWnd = lBoxHandle));
  end;
end;

procedure TsDBLookupComboBox.Invalidate;
begin
  if Focused then FCommonData.FFocused := True;
  inherited Invalidate;
end;

procedure TsDBLookupComboBox.Loaded;
begin
  inherited Loaded;
  FCommonData.Loaded;
  if FCommonData.Skinned then begin
    if not FCommonData.CustomColor then Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
    if not FCommonData.CustomFont then Font.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
  end;
end;

procedure TsDBLookupComboBox.OurPaintHandler;
const
  BordWidth = 3;
var
  DC, SavedDC : hdc;
  PS : TPaintStruct;
begin
  BeginPaint(Handle, PS);
  DC := GetWindowDC(Handle);
  SavedDC := SaveDC(DC);
  try
    if not FCommonData.Updating then begin
      FCommonData.BGChanged := FCommonData.BGChanged or FCommonData.HalfVisible or GetBoolMsg(Parent, AC_GETHALFVISIBLE);
      FCommonData.HalfVisible := not RectInRect(Parent.ClientRect, BoundsRect);

      if FCommonData.BGChanged then begin
        InitCacheBmp(FCommonData);
        PrepareCache
      end;
      UpdateCorners(FCommonData, 0);

      BitBlt(DC, 0, 0, Width, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY)
{$IFDEF DYNAMICCACHE}
    if Assigned(FCommonData.FCacheBmp) then FreeAndNil(FCommonData.FCacheBmp);
{$ENDIF}
    end else FCommonData.Updating := True;
  finally
    RestoreDC(DC, SavedDC);
    ReleaseDC(Handle, DC);
    EndPaint(Handle, PS);
  end;
end;

procedure TsDBLookupComboBox.PaintBorder;
const
  BordWidth = 3;
var
  DC, SavedDC: HDC;
begin
  DC := GetWindowDC(Handle);
  SavedDC := SaveDC(DC);
  try
    if FCommonData.BGChanged then begin
      InitCacheBmp(FCommonData);
      PrepareCache
    end;
    UpdateCorners(FCommonData, 0);

    BitBlt(DC, 0, 0, Width, BordWidth, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
    BitBlt(DC, 0, BordWidth, BordWidth, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, BordWidth, SRCCOPY);
    BitBlt(DC, BordWidth, Height - BordWidth, Width - BordWidth, BordWidth, FCommonData.FCacheBmp.Canvas.Handle, BordWidth, Height - BordWidth, SRCCOPY);
    BitBlt(DC, Width - BordWidth, BordWidth, BordWidth, Height - BordWidth, FCommonData.FCacheBmp.Canvas.Handle, Width - BordWidth, BordWidth, SRCCOPY);
{$IFDEF DYNAMICCACHE}
    if Assigned(FCommonData.FCacheBmp) then FreeAndNil(FCommonData.FCacheBmp);
{$ENDIF}
  finally
    RestoreDC(DC, SavedDC);
    ReleaseDC(Handle, DC);
  end;
end;

procedure TsDBLookupComboBox.PaintButton;
var
  R : TRect;
  Mode : integer;
  c : TsColor;
  glIndex : integer;
  TmpBtn : TBitmap;
begin
  if ListVisible then Mode := 2 else if ControlIsActive(FCommonData) then Mode := 1 else Mode := 0;
  R := ButtonRect;

  if FCommonData.SkinManager.ConstData.ComboBtnIndex > -1 then begin
    TmpBtn := CreateBmpLike(FCommonData.FCacheBmp);
    BitBlt(TmpBtn.Canvas.Handle, 0, 0, TmpBtn.Width, TmpBtn.Height, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
    PaintItem(FCommonData.SkinManager.ConstData.ComboBtnIndex, s_ComboBtn, MakeCacheInfo(TmpBtn),
      True, Mode, R, Point(R.Left, R.Top), FCommonData.FCacheBmp, FCommonData.SkinManager, FCommonData.SkinManager.ConstData.ComboBtnBG, FCommonData.SkinManager.ConstData.ComboBtnBGHot);
    FreeAndNil(TmpBtn);
  end;
  glIndex := FCommonData.SkinManager.ConstData.ComboGlyph;
  if glIndex > -1 then begin
    if ControlIsActive(FCommonData)
      then c.C := FCommonData.SkinManager.gd[FCommonData.SkinIndex].HotColor
      else c.C := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;

    DrawSkinGlyph(FCommonData.FCacheBmp,
      Point(R.Left + (WidthOf(R) - WidthOf(FCommonData.SkinManager.ma[glIndex].R) div FCommonData.SkinManager.ma[glIndex].ImageCount) div 2,
            (Height - ButtonHeight) div 2), Mode, 1, FCommonData.SkinManager.ma[FCommonData.SkinManager.ConstData.ComboGlyph], MakeCacheInfo(FCommonData.FCacheBmp));
  end;
end;

procedure TsDBLookupComboBox.PaintText;
var
  R : TRect;
begin
  R := Rect(4, 3, ButtonRect.Left, Height - 3);
  FCommonData.FCacheBMP.Canvas.Font.Assign(Font);
  if Focused then begin
    FCommonData.FCacheBMP.Canvas.Brush.Color := clHighLight;
    FCommonData.FCacheBMP.Canvas.FillRect(R);
    FCommonData.FCacheBMP.Canvas.Font.Color := colortoRGB(clHighLightText);
    FCommonData.FCacheBMP.Canvas.TextRect(R, R.Left + 1, R.Top + 1, Text);
    FCommonData.FCacheBMP.Canvas.DrawFocusRect(R);
  end
  else WriteTextEx(FCommonData.FCacheBMP.Canvas, PChar(Text), True, R, DT_NOPREFIX or DT_TOP or DT_SINGLELINE or DT_WORDBREAK or GetStringFlags(Self, Alignment),
              FCommonData, ControlIsActive(FCommonData));
end;

procedure TsDBLookupComboBox.PrepareCache;
begin
  InitCacheBmp(FCommonData);
  PaintItem(FCommonData,
                GetParentCache(FCommonData), True,
                integer(ControlIsActive(FCommonData)),
                Rect(0, 0, Width, Height),
                Point(Left, top), FCommonData.FCacheBmp, False);
  PaintText;
  PaintButton;

  if not Enabled then BmpDisabledKind(FCommonData.FCacheBmp, FDisabledKind, Parent, GetParentCache(FCommonData), Point(Left, Top));
end;

procedure TsDBLookupComboBox.SetAlignment(const Value: TAlignment);
begin
  if FAlignment <> Value then begin
    FAlignment := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBLookupComboBox.SetButtonMargin(const Value: integer);
begin
  if FButtonMargin <> Value then begin
    FButtonMargin := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBLookupComboBox.SetDisabledKind(const Value: TsDisabledKind);
begin
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBLookupComboBox.WMMouseWheel(var Message: TMessage);
begin
  if (lBoxHandle = 0) then begin // If not dropped down
    case Message.Msg of
      WM_MOUSEWHEEL: begin
        Message.Msg := WM_KEYDOWN;
        Message.lParam := 0;
        if SmallInt(Message.wParamHi) > 0 then Message.wParam := VK_UP else Message.wParam := VK_DOWN;
        MainWndProc(Message);
      end;
    end;
  end
  else inherited;
end;

procedure TsDBLookupComboBox.WndProc(var Message: TMessage);
begin
{$IFDEF LOGGED}
  AddToLog(Message);
{$ENDIF}
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end;
    AC_REMOVESKIN : begin
      CommonWndProc(Message, FCommonData);
      Color := clWindow;
      if lBoxHandle <> 0 then begin
        SetWindowLong(lBoxHandle, GWL_STYLE, GetWindowLong(lBoxHandle, GWL_STYLE) and not WS_THICKFRAME or WS_BORDER);
        UninitializeACScroll(lBoxHandle, True, False, ListSW);
        lBoxHandle := 0;
      end;
      exit
    end;
    AC_REFRESH : begin
      CommonWndProc(Message, FCommonData);
      if FCommonData.Skinned then begin
        if not FCommonData.CustomColor then Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
        if not FCommonData.CustomFont then Font.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
      end;
      Repaint;
      exit
    end;
    AC_SETNEWSKIN : begin
      CommonWndProc(Message, FCommonData);
      exit
    end;
    AC_DROPPEDDOWN : begin
      Message.WParamLo := integer(ListVisible);
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.FUpdating := False;
      Repaint;
      Exit;
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    case Message.Msg of
      WM_CTLCOLOREDIT, WM_ERASEBKGND : Exit;
      WM_SETFOCUS, CM_ENTER : if CanFocus then begin
        FCommonData.FFocused := True;
        FCommonData.FMouseAbove := False;
        FCommonData.BGChanged := True;
        if not ListVisible then inherited;
        Exit
      end;
      WM_KILLFOCUS, CM_EXIT: begin
        FCommonData.FFocused := False;
        FCommonData.FMouseAbove := False;
        FCommonData.BGChanged := True;
        if IsWindowVisible(Handle)
          then inherited
          else begin
            if TsDBLookupComboBox_(Self).FDataList.Handle <> 0 then ShowWindow(TsDBLookupComboBox_(Self).FDataList.Handle, SW_HIDE);
            TsDBLookupComboBox_(Self).FListVisible := False;
          end;
        Exit
      end;
      WM_NCPAINT : begin
        PaintBorder;
        Exit;
      end;
      WM_PAINT : begin
        if Focused then inherited;
        OurPaintHandler;
        Exit
      end;
      CM_MOUSEENTER, CM_MOUSELEAVE : begin
        FCommonData.FMouseAbove := Message.Msg = CM_MOUSEENTER;
        FCommonData.BGChanged := True;
      end;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of
      CM_VISIBLECHANGED, CM_ENABLEDCHANGED, WM_SETFONT : begin
        FCommonData.Invalidate;
      end;
    end;
  end;
  // Aligning the bound label
  if Assigned(BoundLabel) and Assigned(BoundLabel.FtheLabel) then case Message.Msg of
    WM_SIZE, WM_WINDOWPOSCHANGED : BoundLabel.AlignLabel;
    CM_VISIBLECHANGED : begin BoundLabel.FtheLabel.Visible := Visible; BoundLabel.AlignLabel end;
    CM_ENABLEDCHANGED : begin BoundLabel.FtheLabel.Enabled := Enabled or not (dkBlended in DisabledKind); BoundLabel.AlignLabel end;
    CM_BIDIMODECHANGED : begin BoundLabel.FtheLabel.BiDiMode := BiDiMode; BoundLabel.AlignLabel end;
  end;
end;

end.
