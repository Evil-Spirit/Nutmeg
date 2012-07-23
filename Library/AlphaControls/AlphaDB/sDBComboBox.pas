unit sDBComboBox;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, DBCtrls, sConst, acntUtils, sGraphUtils, sGlyphUtils, math, sCommonData,
  sDefaults{$IFDEF LOGGED}, sDebugMsgs{$ENDIF};

type
  TsDBComboBox = class(TDBComboBox)
  private
    FAlignment : TAlignment;
    FButtonMargin: integer;
    FBoundLabel: TsBoundLabel;
    FCommonData: TsCommonData;
    FDisabledKind: TsDisabledKind;

    procedure SetAlignment(const Value: TAlignment);
    procedure SetButtonMargin(const Value: integer);
    procedure SetDisabledKind(const Value: TsDisabledKind);
  protected
    FActive : boolean;
    FCharsInCode : integer;
    FUseItemIndex : boolean;
    BorderStyle : TFormBorderStyle;
    FDefBmpName : string;

    procedure DropDown; override;

    procedure PaintBorder(ADC : HDC);
    procedure PrepareCache;
    procedure PaintText;
    procedure DrawSkinItem(Index: Integer; Rect: TRect; State: TOwnerDrawState);

    procedure WndProc (var Message: TMessage); override;
    procedure CreateWnd; override;
    procedure WMMouseWheel(var Message: TMessage); message WM_MOUSEWHEEL;
  public
    FDefListProc: Pointer;
    FListHandle: HWND;
    FListInstance: Pointer;
    FDropDown : boolean;

    procedure AfterConstruction; override;
    constructor Create(AOwner:TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;

    property Color;
    procedure Invalidate; override;
    procedure InvalidateSelection;
    procedure PaintButton;
    function ButtonRect: TRect;
    function ButtonHeight : integer;

    procedure WriteText;
    function Focused: Boolean; override;
    property Alignment : TAlignment read FAlignment write SetAlignment;
    property CharsInCode:integer read FCharsInCode write FCharsInCode;
    property UseItemIndex : boolean read FUseItemIndex write FUseItemIndex;
    property ButtonMargin : integer read FButtonMargin write SetButtonMargin default 2;
  published
    property BoundLabel : TsBoundLabel read FBoundLabel write FBoundLabel;
    property DisabledKind : TsDisabledKind read FDisabledKind write SetDisabledKind default DefDisabledKind;
    property DropDownCount default 16;
    property SkinData : TsCommonData read FCommonData write FCommonData;
  end;

implementation

uses sMessages, sMaskData, sStyleSimply, sSkinProps, sVCLUtils, sAlphaGraph;

const
  BordWidth = 3;
    
{ TsDBComboBox }

procedure TsDBComboBox.AfterConstruction;
begin
  inherited AfterConstruction;
  FCommonData.Loaded;
end;

function TsDBComboBox.ButtonHeight: integer;
var
  i : integer;
begin
  if FCommonData.Skinned then begin
    i := FCommonData.SkinManager.GetMaskIndex(FCommonData.SkinIndex, FCommonData.SkinSection, s_ItemGlyph);
    if FCommonData.SkinManager.ma[i].Bmp = nil
      then Result := HeightOf(FCommonData.SkinManager.ma[i].R) div (1 + FCommonData.SkinManager.ma[i].MaskType)
      else Result := FCommonData.SkinManager.ma[i].Bmp.Height div 2;
  end
  else begin
    Result := 16;
  end;
end;

function TsDBComboBox.ButtonRect: TRect;
var
  w : integer;
begin
  if (Style <> csSimple) then w := GetSystemMetrics(SM_CXVSCROLL) else w := 0;
  if UseRightToLeftAlignment then Result.Left := 3 else Result.Left := Width - w - 3;
  Result.Top := 3;
  Result.Right := Result.Left + w;
  Result.Bottom := Height - 3;
end;

constructor TsDBComboBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle - [csFixedHeight, csFramed, csOpaque];
  TControlCanvas(Canvas).Control := self;
  FDropDown := False;

  ParentColor := False;

  FCommonData := TsCommonData.Create(Self, True);
  FCommonData.COC := COC_TsEdit;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := s_ComboBox;
  FDisabledKind := DefDisabledKind;

  FBoundLabel := TsBoundLabel.Create(Self, FCommonData);
  FButtonMargin := 2;

  FDefListProc := nil;
  ItemHeight := 13;

  CharsInCode := 0;
  UseItemIndex := False;
  DropDownCount := 16;
  DoubleBuffered := True;
end;

procedure TsDBComboBox.CreateWnd;
begin
  inherited;
end;

destructor TsDBComboBox.Destroy;
begin
  FreeAndNil(FBoundLabel);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited Destroy;
end;

procedure TsDBComboBox.DrawSkinItem(Index: Integer; Rect: TRect; State: TOwnerDrawState);
var
  Offset : integer;
begin
  if not Assigned(OnDrawItem) then begin
    FCommonData.FCacheBmp.Canvas.Font.Assign(Font);
    FCommonData.FCacheBmp.Canvas.Font.Color := Font.Color;
    FCommonData.FCacheBmp.Canvas.Brush.Color := Color;
    FCommonData.FCacheBmp.Canvas.Brush.Style := bsClear;
    if Text <> '' then begin
      Offset := integer(Style <> csDropDown);
      FCommonData.FCacheBmp.Canvas.TextRect(Rect, Rect.Left + Offset, Rect.Top + Offset, Text);
    end;
  end;
  if odFocused in State then FCommonData.FCacheBmp.Canvas.DrawFocusRect(Rect);
end;

procedure TsDBComboBox.DropDown;
begin
  FDropDown := True;
  inherited;
end;

function TsDBComboBox.Focused: Boolean;
var
  FocusedWnd: HWND;
begin
  Result := False;
  if HandleAllocated then begin
    FocusedWnd := GetFocus;
    Result := (FocusedWnd <> 0) and ((FocusedWnd = EditHandle) or (FocusedWnd = FListHandle));
  end;
end;

procedure TsDBComboBox.Invalidate;
begin
  if Focused then FCommonData.FFocused := True;
  inherited Invalidate;
end;

procedure TsDBComboBox.InvalidateSelection;
begin
//
end;

procedure TsDBComboBox.Loaded;
begin
  inherited Loaded;
  FCommonData.Loaded;
  if FCommonData.Skinned then begin
    if not FCommonData.CustomColor then Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
    if not FCommonData.CustomFont then Font.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
  end;
end;

procedure TsDBComboBox.PaintBorder(ADC : HDC);
var
  DC, SavedDC: HDC;
  R : TRect;
begin
  SavedDC := 0;
  if ADC = 0 then begin
    DC := GetWindowDC(Handle);
    SavedDC := SaveDC(DC);
  end
  else begin
    DC := ADC;
    MoveWindowOrg(DC, -BordWidth, -BordWidth);
    SelectClipRgn(DC,0);
  end;
  try
    PrepareCache;
    UpdateCorners(FCommonData, 0);

    BitBlt(DC, 0, 0, Width, BordWidth, FCommonData.FCacheBmp.Canvas.Handle, 0, 0, SRCCOPY);
    BitBlt(DC, 0, BordWidth, BordWidth, Height, FCommonData.FCacheBmp.Canvas.Handle, 0, BordWidth, SRCCOPY);
    BitBlt(DC, BordWidth, Height - BordWidth, Width - BordWidth, BordWidth, FCommonData.FCacheBmp.Canvas.Handle, BordWidth, Height - BordWidth, SRCCOPY);
    BitBlt(DC, Width - BordWidth, BordWidth, BordWidth, Height - BordWidth, FCommonData.FCacheBmp.Canvas.Handle, Width - BordWidth, BordWidth, SRCCOPY);
    R := ButtonRect;
    BitBlt(DC, R.Left, R.Top, WidthOf(R), HeightOf(R), FCommonData.FCacheBmp.Canvas.Handle, R.Left, R.TOp, SRCCOPY);

{$IFDEF DYNAMICCACHE}
    if Assigned(FCommonData.FCacheBmp) then FreeAndNil(FCommonData.FCacheBmp);
{$ENDIF}
  finally
    if SavedDC > 0 then begin
      RestoreDC(DC, SavedDC);
      ReleaseDC(Handle, DC);
    end
    else MoveWindowOrg(DC, BordWidth, BordWidth);
  end;
end;

procedure TsDBComboBox.PaintButton;
var
  R : TRect;
  Mode : integer;
  c : TsColor;
  glIndex : integer;
  TmpBtn : TBitmap;
begin
  if FDropDown then Mode := 2 else if ControlIsActive(FCommonData) then Mode := 1 else Mode := 0;
  R := ButtonRect;

  if (FCommonData.SkinManager.ConstData.ComboBtnIndex > -1) and (Mode <> 0) then begin
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

    DrawSkinGlyph(FCommonData.FCacheBmp, Point(R.Left + (WidthOf(R) - WidthOf(FCommonData.SkinManager.ma[glIndex].R) div FCommonData.SkinManager.ma[glIndex].ImageCount) div 2,
      (Height - ButtonHeight) div 2), Mode, 1, FCommonData.SkinManager.ma[FCommonData.SkinManager.ConstData.ComboGlyph], MakeCacheInfo(FCommonData.FCacheBmp));
  end;
end;

procedure TsDBComboBox.PaintText;
var
  R : TRect;
begin
  FCommonData.FCacheBMP.Canvas.Font.Assign(Font);
  R := Rect(3, 3, Width - 3, Height - 3);
  WriteTextEx(FCommonData.FCacheBMP.Canvas, PChar(Text), True, R, DT_NOPREFIX or DT_TOP or DT_SINGLELINE or DT_WORDBREAK or GetStringFlags(Self, Alignment),
              FCommonData, ControlIsActive(FCommonData));
end;

procedure TsDBComboBox.PrepareCache;
var
  R : TRect;
  State : TOwnerDrawState;
begin
  InitCacheBmp(FCommonData);
  PaintItem(FCommonData, GetParentCache(FCommonData), True, integer(ControlIsActive(FCommonData)), Rect(0, 0, Width, Height), Point(Left, top), FCommonData.FCacheBmp, False);
  if Style <> csSimple then PaintButton;
  R := Rect(BordWidth, BordWidth, ButtonRect.Left, Height - BordWidth);
  State := [odComboBoxEdit];
  if (Focused or SkinData.FFocused) and not (Style in [csDropDown, csSimple]) and Enabled then State := State + [odFocused, odSelected];
  DrawSkinItem(ItemIndex, R, State);

  if not Enabled then BmpDisabledKind(FCommonData.FCacheBmp, FDisabledKind, Parent, GetParentCache(FCommonData), Point(Left, Top));
  FCommonData.BGChanged := False;
end;

procedure TsDBComboBox.SetAlignment(const Value: TAlignment);
begin
  if FAlignment <> Value then begin
    FAlignment := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBComboBox.SetButtonMargin(const Value: integer);
begin
  if FButtonMargin <> Value then begin
    FButtonMargin := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBComboBox.SetDisabledKind(const Value: TsDisabledKind);
begin
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;

var
  bFlag : boolean = False;

procedure TsDBComboBox.WMMouseWheel(var Message: TMessage);
begin
  if not FDropDown then begin // If not dropped down
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

procedure TsDBComboBox.WndProc(var Message: TMessage);
var
  PS : TPaintStruct;
begin
{$IFDEF LOGGED}
  AddToLog(Message);
{$ENDIF}
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end;
    AC_REMOVESKIN : begin
      CommonWndProc(Message, FCommonData);
      Color := clWindow;
      RecreateWnd;
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
      Message.WParamLo := integer(DroppedDown);
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.Updating := False;
      Repaint;
      Exit
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    case Message.Msg of
      WM_DRAWITEM :;
      WM_SETFOCUS, CM_ENTER : if CanFocus and not bFlag then begin
        bFlag := True;
        FCommonData.FFocused := True;
        FCommonData.FMouseAbove := False;
        FCommonData.BGChanged := True;
        inherited;
        bFlag := False;
        Exit;
      end;
      WM_KILLFOCUS, CM_EXIT: if not bFlag then begin
        bFlag := True;
        DroppedDown := False;
        FCommonData.FFocused := False;
        FCommonData.FMouseAbove := False;
        FCommonData.BGChanged := True;
        inherited;
        bFlag := False;
        Exit;
      end;
      CM_INVALIDATE, CM_FOCUSCHANGED : if not bFlag then begin
        bFlag := True;
        inherited;
        bFlag := False;
        Exit;
      end;
      WM_PRINT : begin
        ControlState := ControlState + [csPaintCopy];
        if not FCommonData.CustomColor then Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
        if not FCommonData.CustomFont then Font.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
        SendMessage(Handle, WM_PAINT, Message.WParam, 0);
        ControlState := ControlState - [csPaintCopy];
      end;
      WM_NCPAINT : begin
        PaintBorder(0);
        Exit;
      end;
      WM_PAINT : begin
        if bFlag then begin
          BeginPaint(Handle, PS);
          EndPaint(Handle, PS);
        end
        else inherited;
        PaintBorder(TWMPaint(Message).DC);
        Exit
      end;
      CM_MOUSEENTER, CM_MOUSELEAVE : begin
        inherited;
        FCommonData.FMouseAbove := Message.Msg = CM_MOUSEENTER;
        FCommonData.BGChanged := True;
        PaintBorder(0);
        Exit;
      end;
      CN_COMMAND : begin
        FDropDown := False;
        Repaint;
      end;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of CM_VISIBLECHANGED, CM_ENABLEDCHANGED, WM_SETFONT : FCommonData.Invalidate; end;
  end;
  // Aligning of the bound label
  if Assigned(BoundLabel) and Assigned(BoundLabel.FtheLabel) then case Message.Msg of
    WM_SIZE, WM_WINDOWPOSCHANGED : BoundLabel.AlignLabel;
    CM_VISIBLECHANGED : begin BoundLabel.FtheLabel.Visible := Visible; BoundLabel.AlignLabel end;
    CM_ENABLEDCHANGED : begin BoundLabel.FtheLabel.Enabled := Enabled or not (dkBlended in DisabledKind); BoundLabel.AlignLabel end;
    CM_BIDIMODECHANGED : begin BoundLabel.FtheLabel.BiDiMode := BiDiMode; BoundLabel.AlignLabel end;
  end;
end;

procedure TsDBComboBox.WriteText;
var
  Flags: Longint;
  R : TRect;
begin
  if Text <> '' then begin
    Flags := 0;
    Canvas.Font.Assign(Font);
    R := ClientRect;
    dec(R.Left);
    dec(R.Top);
    dec(R.Right, ButtonRect.Left);

    case Alignment of
      taLeftJustify : Flags := DT_LEFT;
      taRightJustify : Flags := DT_RIGHT;
      taCenter : Flags := DT_CENTER;
    end;
    Flags := Flags or DT_EXPANDTABS or DT_VCENTER or DT_SINGLELINE;
    Flags := DrawTextBiDiModeFlags(Flags);

    Canvas.Pen.Style := psSolid;
    Canvas.Brush.Style := bsClear;
    DrawText(Canvas.Handle, PChar(Text), Length(Text), R, Flags);
  end;
end;

end.
