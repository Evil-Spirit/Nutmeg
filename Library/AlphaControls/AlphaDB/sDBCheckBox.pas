unit sDBCheckBox;
{$I sDefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  sCheckbox, DBCtrls, sConst, db, stdctrls, dbconsts;

type

  TsDBCheckBox = class(TsCheckBox)
  private
    FDataLink: TFieldDataLink;
    FValueCheck: string;
    FValueUncheck: string;
    FPaintControl: TPaintControl;
    procedure DataChange(Sender: TObject);
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetField: TField;
    function GetFieldState: TCheckBoxState;
    procedure SetDataField(const Value: string);
    procedure SetDataSource(Value: TDataSource);
    procedure SetValueCheck(const Value: string);
    procedure SetValueUncheck(const Value: string);
    procedure UpdateData(Sender: TObject);
    function ValueMatch(const ValueList, Value: string): Boolean;
    procedure CMExit(var Message: TCMExit); message CM_EXIT;
    procedure CMGetDataLink(var Message: TMessage); message CM_GETDATALINK;
  protected
    procedure Toggle; override;
    procedure KeyPress(var Key: Char); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    function GetReadOnly: Boolean; reintroduce;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function ExecuteAction(Action: TBasicAction): Boolean; override;
    function UpdateAction(Action: TBasicAction): Boolean; override;
    function UseRightToLeftAlignment: Boolean; override;
    procedure WndProc(var Message: TMessage); override;
    property Checked;
    property Field: TField read GetField;
    property State;
  published
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ValueChecked: string read FValueCheck write SetValueCheck;
    property ValueUnchecked: string read FValueUncheck write SetValueUncheck;
  end;

implementation

uses acntUtils;

{ TsDBCheckBox }

procedure TsDBCheckBox.CMExit(var Message: TCMExit);
begin
  try
    if Assigned(FDataLink) then FDataLink.UpdateRecord;
  except
    SetFocus;
    raise;
  end;
  inherited;
end;

procedure TsDBCheckBox.CMGetDataLink(var Message: TMessage);
begin
  if Assigned(FDataLink) then Message.Result := Integer(FDataLink) else Message.Result := 0;
end;

constructor TsDBCheckBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable];
  State := cbUnchecked;
  FValueCheck := STextTrue;
  FValueUncheck := STextFalse;

  FDataLink := TFieldDataLink.Create;
  FDataLink.Control := Self;
  FDataLink.OnDataChange := DataChange;
  FDataLink.OnUpdateData := UpdateData;
  FPaintControl := TPaintControl.Create(Self, 'BUTTON');
  FPaintControl.Ctl3DButton := True;
end;

procedure TsDBCheckBox.DataChange(Sender: TObject);
begin
  State := GetFieldState;
end;

destructor TsDBCheckBox.Destroy;
begin
  FPaintControl.Free;
{  FDataLink.DataSource := nil;
  FDataLink.Control := nil;
  FDataLink.OnDataChange := nil;
  FDataLink.OnUpdateData := nil;}
  FreeAndNil(FDataLink);
  inherited Destroy;
end;

function TsDBCheckBox.ExecuteAction(Action: TBasicAction): Boolean;
begin
  Result := inherited ExecuteAction(Action) or (FDataLink <> nil) and FDataLink.ExecuteAction(Action);
end;

function TsDBCheckBox.GetDataField: string;
begin
  if Assigned(FDataLink) then Result := FDataLink.FieldName else Result := '';
end;

function TsDBCheckBox.GetDataSource: TDataSource;
begin
  if Assigned(FDataLink) and Assigned(FDataLink.DataSource) then Result := FDataLink.DataSource else Result := nil;
end;

function TsDBCheckBox.GetField: TField;
begin
  if Assigned(FDataLink) then Result := FDataLink.Field else Result := nil;
end;

function TsDBCheckBox.GetFieldState: TCheckBoxState;
var
  Text: string;
begin
  if FDatalink.Field <> nil then
    if FDataLink.Field.IsNull then
      Result := cbGrayed
    else if FDataLink.Field.DataType = ftBoolean then
      if FDataLink.Field.AsBoolean then
        Result := cbChecked
      else
        Result := cbUnchecked
    else
    begin
      Result := cbGrayed;
      Text := FDataLink.Field.Text;
      if ValueMatch(FValueCheck, Text) then Result := cbChecked else
        if ValueMatch(FValueUncheck, Text) then Result := cbUnchecked;
    end
  else
    Result := cbUnchecked;
end;

function TsDBCheckBox.GetReadOnly: Boolean;
begin
  if Assigned(FDataLink) {and Assigned(FDataLink.DataSource) and Assigned(FDataLink.DataSource.DataSet)} then
    Result := not FDataLink.CanModify
  else Result := False;
end;

procedure TsDBCheckBox.KeyPress(var Key: Char);
begin
  inherited KeyPress(Key);
  if Assigned(FDataLink) then
    case Key of
      #8, ' ': FDataLink.Edit;
      #27: FDataLink.Reset;
    end;
end;

procedure TsDBCheckBox.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (FDataLink <> nil) and (AComponent = DataSource) then DataSource := nil;
end;

procedure TsDBCheckBox.SetDataField(const Value: string);
begin
  if Assigned(FDataLink) then FDataLink.FieldName := Value;
end;

procedure TsDBCheckBox.SetDataSource(Value: TDataSource);
begin
  if not Assigned(FDataLink) then Exit;
  if not (FDataLink.DataSourceFixed and (csLoading in ComponentState)) then FDataLink.DataSource := Value;
  if Value <> nil then Value.FreeNotification(Self);
end;

procedure TsDBCheckBox.SetValueCheck(const Value: string);
begin
  FValueCheck := Value;
  DataChange(Self);
end;

procedure TsDBCheckBox.SetValueUncheck(const Value: string);
begin
  FValueUncheck := Value;
  DataChange(Self);
end;

procedure TsDBCheckBox.Toggle;
begin
  if Assigned(FDataLink) then begin
    if FDataLink.Edit then begin
      inherited Toggle;
      FDataLink.Modified;
    end;
  end;
end;

function TsDBCheckBox.UpdateAction(Action: TBasicAction): Boolean;
begin
  Result := inherited UpdateAction(Action) or (FDataLink <> nil) and FDataLink.UpdateAction(Action);
end;

procedure TsDBCheckBox.UpdateData(Sender: TObject);
var
  Pos: Integer;
  S: string;
begin
  if Assigned(FDataLink) then begin
    if State = cbGrayed then
      FDataLink.Field.Clear
    else
      if FDataLink.Field.DataType = ftBoolean then
        FDataLink.Field.AsBoolean := Checked
      else begin
        if Checked then S := FValueCheck else S := FValueUncheck;
        Pos := 1;
        FDataLink.Field.Text := ExtractFieldName(S, Pos);
      end;
  end;
end;

function TsDBCheckBox.UseRightToLeftAlignment: Boolean;
begin
  Result := False;
end;

function TsDBCheckBox.ValueMatch(const ValueList, Value: string): Boolean;
var
  Pos: Integer;
begin
  Result := False;
  Pos := 1;
  while Pos <= Length(ValueList) do begin
    if AnsiCompareText(ExtractFieldName(ValueList, Pos), Value) = 0 then begin
      Result := True;
      Break;
    end;
  end;
end;

procedure TsDBCheckBox.WndProc(var Message: TMessage);
begin
  with Message do
    if (Msg = WM_CREATE) or (Msg = WM_WINDOWPOSCHANGED) or
      (Msg = CM_TEXTCHANGED) or (Msg = CM_FONTCHANGED) then
      FPaintControl.DestroyHandle;

  if not (csPaintCopy in ControlState) or (Message.Msg <> WM_PAINT) or (csDesigning in componentState) then inherited else begin
    if SkinData.Skinned then begin
      PaintState := Ord(GetFieldState);
//      SendMessage(Handle, BM_SETCHECK, Ord(GetFieldState), 0);
      PaintHandler(TWMPaint(Message));
      PaintState := -1;

//      SendMessage(Handle, WM_PAINT, TWMPaint(Message).DC, 0);
    end
    else begin
      SendMessage(FPaintControl.Handle, BM_SETCHECK, Ord(GetFieldState), 0);
      SendMessage(FPaintControl.Handle, WM_PAINT, longint(TWMPaint(Message).DC), 0);
    end;
  end;
end;

end.

