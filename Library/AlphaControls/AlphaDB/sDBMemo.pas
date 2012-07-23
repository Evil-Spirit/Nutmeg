unit sDBMemo;
{$I sDefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, DBCtrls, sConst, sCommonData, sDefaults, acSBUtils;

type
  TsDBMemo = class(TDBMemo)
  private
    FOnVScroll: TNotifyEvent;
    FOnScrollCaret: TNotifyEvent;
    FBoundLabel: TsBoundLabel;
    FCommonData: TsCommonData;
    FDisabledKind: TsDisabledKind;
    FOldDataChange : TNotifyEvent;
    procedure SetDisabledKind(const Value: TsDisabledKind);
    procedure DataChange(Sender: TObject);
  protected
    procedure WndProc (var Message: TMessage); override;
  public
    ListSW : TacScrollWnd;
    procedure AfterConstruction; override;
    constructor Create(AOwner:TComponent); override;
    destructor Destroy; override;
    procedure Loaded; override;
  published
    property BoundLabel : TsBoundLabel read FBoundLabel write FBoundLabel;
    property CharCase;
    property DisabledKind : TsDisabledKind read FDisabledKind write SetDisabledKind default DefDisabledKind;
    property SkinData : TsCommonData read FCommonData write FCommonData;
  end;

implementation

uses sMaskData, sStyleSimply, acntUtils, sMessages, sSKinProps, sVCLUtils, sGraphUtils, sAlphaGraph;

type

  _TDBMemo = class(TCustomMemo)
  private
    FDataLink: TFieldDataLink;
  end;

{ TsDBMemo }
//var
//  ScrollsUpdating : boolean = False;

procedure TsDBMemo.AfterConstruction;
begin
  inherited AfterConstruction;
  FCommonData.Loaded;
end;

constructor TsDBMemo.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle - [csOpaque];
  FCommonData := TsCommonData.Create(Self, {$IFDEF DYNAMICCACHE} False {$ELSE} True {$ENDIF});
  FCommonData.COC := COC_TsMemo;
  if FCommonData.SkinSection = '' then FCommonData.SkinSection := s_Edit;
  FDisabledKind := DefDisabledKind;
  FBoundLabel := TsBoundLabel.Create(Self, FCommonData);

  ParentColor := False;

  FOldDataChange := _TDBMemo(Self).FDataLink.OnDataChange;
  _TDBMemo(Self).FDataLink.OnDataChange := DataChange;
end;

procedure TsDBMemo.DataChange(Sender: TObject);
begin
  FOldDataChange(Sender);
end;

destructor TsDBMemo.Destroy;
begin
  if ListSW <> nil then FreeAndNil(ListSW);
  FreeAndNil(FBoundLabel);
  if Assigned(FCommonData) then FreeAndNil(FCommonData);
  inherited Destroy;
end;

procedure TsDBMemo.Loaded;
begin
  inherited Loaded;
  FCommonData.Loaded;
  RefreshEditScrolls(SkinData, ListSW);
end;

procedure TsDBMemo.SetDisabledKind(const Value: TsDisabledKind);
begin
  if FDisabledKind <> Value then begin
    FDisabledKind := Value;
    FCommonData.Invalidate;
  end;
end;

procedure TsDBMemo.WndProc(var Message: TMessage);
begin
  if Message.Msg = SM_ALPHACMD then case Message.WParamHi of
    AC_CTRLHANDLED : begin Message.Result := 1; Exit end; // AlphaSkins supported
    AC_SETNEWSKIN : begin
      CommonWndProc(Message, FCommonData);
      exit
    end;
    AC_REMOVESKIN : begin
      if ListSW <> nil then FreeAndNil(ListSW);
      CommonWndProc(Message, FCommonData);
      RecreateWnd;
      exit
    end;
    AC_REFRESH : begin
      CommonWndProc(Message, FCommonData);
      Repaint;
      RefreshEditScrolls(SkinData, ListSW);
      exit
    end;
    AC_ENDPARENTUPDATE : if FCommonData.Updating then begin
      FCommonData.Updating := False;
      Perform(WM_NCPAINT, 0, 0);
      Exit
    end;
  end;
  if not ControlIsReady(Self) or not FCommonData.Skinned then inherited else begin
    CommonWndProc(Message, FCommonData);
    inherited;
    case Message.Msg of
      CM_SHOWINGCHANGED : RefreshEditScrolls(SkinData, ListSW);
      EM_SETSEL : if Assigned(FOnScrollCaret) then FOnScrollCaret(Self);
      WM_HSCROLL, WM_VSCROLL : begin
        if (Message.Msg = WM_VSCROLL) and Assigned(FOnVScroll) then begin
          FOnVScroll(Self);
        end;
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
