unit sDBEdit;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask, DBCtrls, sConst, sDefaults, acSBUtils, sCommonData{$IFDEF LOGGED}, sDebugMsgs{$ENDIF};

type
  TsDBEdit = class(TDBEdit)
  private
    FCommonData: TsCommonData;
    FBoundLabel: TsBoundLabel;
    FDisabledKind: TsDisabledKind;
    procedure SetDisabledKind(const Value: TsDisabledKind);
  protected
    procedure WndProc (var Message: TMessage); override;
  public
    ListSW : TacScrollWnd;
    procedure AfterConstruction; override;
    constructor Create(AOwner:TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;
  published
    property DisabledKind : TsDisabledKind read FDisabledKind write SetDisabledKind default DefDisabledKind;
    property SkinData : TsCommonData read FCommonData write FCommonData;
    property BoundLabel : TsBoundLabel read FBoundLabel write FBoundLabel;
  end;

implementation

uses sSkinProps, sMaskData, sVCLUtils, sMessages, acntUtils, sGraphUtils, sAlphaGraph;

{ TsDBEdit }

procedure TsDBEdit.AfterConstruction;
begin
  inherited AfterConstruction;
  FCommonData.Loaded;
end;

constructor TsDBEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FCommonData := TsCommonData.Create(Self, True);
  FCommonData.COC := COC_TsDBEdit;
  FDisabledKind := DefDisabledKind;
  FBoundLabel := TsBoundLabel.Create(Self, FCommonData);
end;

destructor TsDBEdit.Destroy;
begin
  if ListSW <> nil then FreeAndNil(ListSW);
  FreeAndNil(FBoundLabel);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited Destroy;
end;

procedure TsDBEdit.Loaded;
begin
  inherited Loaded;
  FCommonData.Loaded;
  RefreshEditScrolls(SkinData, ListSW);
end;

procedure TsDBEdit.SetDisabledKind(const Value: TsDisabledKind);
begin
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBEdit.WndProc(var Message: TMessage);
var
  DC, SavedDC : hdc;
begin
{$IFDEF LOGGED}
  AddToLog(Message);
{$ENDIF}
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end; // AlphaSkins supported
    AC_REMOVESKIN : begin
      if ListSW <> nil then FreeAndNil(ListSW);
      CommonWndProc(Message, FCommonData);
      RecreateWnd;
      exit
    end;
    AC_REFRESH : begin
      CommonWndProc(Message, FCommonData);
      if not InAnimationProcess then RedrawWindow(Handle, nil, 0, RDW_INVALIDATE or RDW_ERASE or RDW_FRAME);
      RefreshEditScrolls(SkinData, ListSW);
      exit
    end;
    AC_SETNEWSKIN : begin
      CommonWndProc(Message, FCommonData);
      exit
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.FUpdating := False;
      Perform(WM_NCPAINT, 0, 0);
      Exit
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    case Message.Msg of
      CM_MOUSEENTER, CM_MOUSELEAVE : if FCommonData.SkinManager.gd[FCommonData.Skinindex].ReservedBoolean then begin
        FCommonData.FMouseAbove := Message.Msg = CM_MOUSEENTER;
        FCommonData.BGChanged := True;
        Repaint;
      end;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of
      CM_SHOWINGCHANGED : RefreshEditScrolls(SkinData, ListSW);
      CM_TEXTCHANGED, CM_VISIBLECHANGED, CM_ENABLEDCHANGED, WM_SETFONT : begin
        FCommonData.Invalidate;
      end;
      WM_PRINT : begin
        DC := TWMPaint(Message).DC;
        SavedDC := SaveDC(DC);
        ControlState := ControlState + [csPaintCopy];
        MoveWindowOrg(DC, 2, 2);
        IntersectClipRect(DC, 0, 0,
                          SkinData.FCacheBmp.Width - 2 * 2,
                          SkinData.FCacheBmp.Height - 2 * 2);
        SendMessage(Handle, WM_PAINT, longint(DC), Message.lParam);
        ControlState := ControlState - [csPaintCopy];
        RestoreDC(DC, SavedDC);
      end;
    end;
  end;
  // Aligning of the bound label
  if Assigned(BoundLabel) and Assigned(BoundLabel.FtheLabel) then case Message.Msg of
    WM_SIZE, WM_WINDOWPOSCHANGED : BoundLabel.AlignLabel;
    CM_VISIBLECHANGED : begin BoundLabel.FtheLabel.Visible := Visible; BoundLabel.AlignLabel end;
    CM_ENABLEDCHANGED : begin BoundLabel.FtheLabel.Enabled := Enabled or not (dkBlended in DisabledKind); BoundLabel.AlignLabel end;
    CM_BIDIMODECHANGED : begin BoundLabel.FtheLabel.BiDiMode := BiDiMode; BoundLabel.AlignLabel end;
  end;
end;

end.
