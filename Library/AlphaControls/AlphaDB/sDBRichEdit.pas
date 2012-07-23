unit sDBRichEdit;
{$I sDefs.inc}
{.$DEFINE LOGGED}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, sConst, sCommonData, sDefaults, dbctrls, acSBUtils;

type
  TsDBRichEdit = class(TDBRichEdit)
{$IFNDEF NOTFORHELP}
  private
    FCommonData: TsCommonData;
    FDisabledKind: TsDisabledKind;

    FBoundLabel: TsBoundLabel;
    procedure SetDisabledKind(const Value: TsDisabledKind);
  public
    ListSW : TacScrollWnd;
    procedure AfterConstruction; override;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;
    procedure WndProc (var Message: TMessage); override;
  published
    property CharCase;
    property Text;
{$ENDIF} // NOTFORHELP
    property BoundLabel : TsBoundLabel read FBoundLabel write FBoundLabel;
    property SkinData : TsCommonData read FCommonData write FCommonData;
    property DisabledKind : TsDisabledKind read FDisabledKind write SetDisabledKind default DefDisabledKind;
  end;

implementation

uses sStyleSimply, sVCLUtils, sMessages, sMaskData, acntUtils, sGraphUtils, sAlphaGraph,
  sSkinProps{$IFDEF LOGGED}, sDebugMsgs{$ENDIF}, richedit;

{ TsDBRichEdit }

procedure TsDBRichEdit.AfterConstruction;
begin
  inherited AfterConstruction;
  UpdateData(FCommonData);
end;

constructor TsDBRichEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable];
  FCommonData := TsCommonData.Create(Self, {$IFDEF DYNAMICCACHE} False {$ELSE} True {$ENDIF});
  FCommonData.COC := COC_TsMemo;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := s_Edit;
  FDisabledKind := DefDisabledKind;
  FBoundLabel := TsBoundLabel.Create(Self, FCommonData);
  Perform(EM_EXLIMITTEXT, 0, $7FFFFFF0);
end;

destructor TsDBRichEdit.Destroy;
begin
  if ListSW <> nil then FreeAndNil(ListSW);
  FreeAndNil(FBoundLabel);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited Destroy;
end;

procedure TsDBRichEdit.Loaded;
begin
  inherited Loaded;
  FCommonData.Loaded;
  RefreshEditScrolls(SkinData, ListSW);
end;

procedure TsDBRichEdit.SetDisabledKind(const Value: TsDisabledKind);
begin
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBRichEdit.WndProc(var Message: TMessage);
begin
{$IFDEF LOGGED}
  AddToLog(Message);
{$ENDIF}
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end; // AlphaSkins supported
    AC_REMOVESKIN : if not (csDestroying in ComponentState) then begin
      if ListSW <> nil then FreeAndNil(ListSW);
      CommonWndProc(Message, FCommonData);
      if not FCommonData.CustomFont then begin
        DefAttributes.Color := Font.Color;
      end;
      RecreateWnd;
      exit
    end;
    AC_REFRESH : if Visible then begin
      CommonWndProc(Message, FCommonData);
      if FCommonData.Skinned then begin
        if not FCommonData.CustomFont then begin
          DefAttributes.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
        end;
      end;
      SendMessage(Handle, WM_NCPaint, 0, 0);
      RefreshEditScrolls(SkinData, ListSW);
      exit
    end;
    AC_SETNEWSKIN : begin
      CommonWndProc(Message, FCommonData);
      exit
    end
  end;
  if not ControlIsReady(Self) or not Assigned(FCommonData) or not FCommonData.Skinned then inherited else begin
    if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
      AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
        FCommonData.Updating := False;
        Perform(WM_NCPAINT, 0, 0); Exit
      end;
    end
    else case Message.Msg of
      WM_PRINT : begin
        Perform(WM_PAINT, Message.WParam, Message.LParam);
        Perform(WM_NCPAINT, Message.WParam, Message.LParam);
        Exit;
      end;
      WM_ENABLE : Exit;
    end;
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of
      CM_SHOWINGCHANGED : RefreshEditScrolls(SkinData, ListSW);
      CM_ENABLEDCHANGED : begin
        if not FCommonData.CustomColor then Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].Color;
        if not FCommonData.CustomFont then begin
          if not Enabled then begin
            Font.Color := AverageColor(FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1], Color);
            DefAttributes.Color := Font.Color;
          end
          else begin
            Font.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
            DefAttributes.Color := FCommonData.SkinManager.gd[FCommonData.SkinIndex].FontColor[1];
          end;
        end;
      end;
    end;
  end;
  // Aligning of the bound label
  if Assigned(BoundLabel) and Assigned(BoundLabel.FtheLabel) then case Message.Msg of
    WM_SIZE, WM_WINDOWPOSCHANGED : begin BoundLabel.AlignLabel end;
    CM_VISIBLECHANGED : begin BoundLabel.FtheLabel.Visible := Visible; BoundLabel.AlignLabel end;
    CM_ENABLEDCHANGED : begin BoundLabel.FtheLabel.Enabled := Enabled or not (dkBlended in DisabledKind); BoundLabel.AlignLabel end;
    CM_BIDIMODECHANGED : begin BoundLabel.FtheLabel.BiDiMode := BiDiMode; BoundLabel.AlignLabel end;
  end;
end;

end.
