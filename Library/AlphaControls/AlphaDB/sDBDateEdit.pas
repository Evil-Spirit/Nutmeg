unit sDBDateEdit;
{$I sDefs.inc}

interface

uses
  SysUtils, Classes, Controls, StdCtrls, Mask, sCustomComboEdit, sTooledit,
  DBCtrls, DB, Windows, Messages;

type
  TsDBDateEdit = class(TsCustomDateEdit) 
  private
    FDataLink: TFieldDataLink;
    procedure DataChange(Sender: TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender: TObject);
    procedure AfterPopup(Sender: TObject; var Date: TDateTime; var Action: Boolean);
    function GetDataField: string;
    function GetDataSource: TDataSource;
    procedure SetDataField(const Value: string);
    procedure SetDataSource(const Value: TDataSource);
    function GetField: TField;
    procedure WMCut(var Message: TMessage); message WM_CUT;
    procedure WMPaste(var Message: TMessage); message WM_PASTE;
    procedure CMExit(var Message: TCMExit); message CM_EXIT;
    procedure CMGetDataLink(var Message: TMessage); message CM_GETDATALINK;
    procedure WMPaint(var Message: TWMPaint); message WM_PAINT;
    function GetReadOnly: Boolean; reintroduce;
    procedure SetReadOnly(const Value: Boolean); reintroduce;
  protected
    procedure ApplyDate(Value: TDateTime); override;
    procedure Change; override;
    function EditCanModify: Boolean; override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure KeyPress(var Key: Char); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure Reset; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Field: TField read GetField;
  published
    property CheckOnExit;
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

implementation

uses acntUtils;

{ TsDBDateEdit }

procedure TsDBDateEdit.AfterPopup(Sender: TObject; var Date: TDateTime; var Action: Boolean);
var
  DataSet : TDataSet;
begin
  if (DataSource <> nil) then DataSet := DataSource.DataSet else DataSet := nil;
  Action := Action and (DataSet <> nil) and DataSet.Active and DataSet.CanModify;
  if Action then Action := EditCanModify;
end;

procedure TsDBDateEdit.ApplyDate(Value: TDateTime);
begin
  FDataLink.Edit;
  inherited ApplyDate(Value);
end;

procedure TsDBDateEdit.Change;
begin
  if Assigned(FDataLink) and not Formatting then FDataLink.Modified;
  SkinData.BGChanged := True;
  inherited;
end;

procedure TsDBDateEdit.CMExit(var Message: TCMExit);
begin
  try
    if not (csDesigning in ComponentState) and CheckOnExit then
      CheckValidDate;
    FDataLink.UpdateRecord;
  except
    SelectAll;
    if CanFocus then SetFocus;
    raise;
  end;
  CheckCursor;
  DoExit;
end;

procedure TsDBDateEdit.CMGetDataLink(var Message: TMessage);
begin
  Message.Result := Integer(FDataLink);
end;

constructor TsDBDateEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable];
  FDataLink := TFieldDataLink.Create;
  FDataLink.Control := Self;
  FDataLink.OnDataChange := DataChange;
  FDataLink.OnEditingChange := EditingChange;
  FDataLink.OnUpdateData := UpdateData;
  OnAcceptDate := AfterPopup;
  UpdateMask;
end;

procedure TsDBDateEdit.DataChange(Sender: TObject);
begin
  if FDataLink.Field <> nil then begin
    EditMask := GetDateMask;
    Self.Date := FDataLink.Field.AsDateTime;
  end
  else begin
    if csDesigning in ComponentState then begin
      EditMask := '';
      EditText := Name;
    end
    else begin
      EditMask := GetDateMask;
      if DefaultToday then Date := SysUtils.Date
      else Date := 0;
    end;
  end;
end;

destructor TsDBDateEdit.Destroy;
begin
  FDataLink.Free;
  FDataLink := nil;
  inherited;
end;

function TsDBDateEdit.EditCanModify: Boolean;
begin
  Result := FDataLink.Edit;
end;

procedure TsDBDateEdit.EditingChange(Sender: TObject);
begin
  if FDataLink.Editing and DefaultToday and (FDataLink.Field <> nil) and (FDataLink.Field.AsDateTime = 0) then
    FDataLink.Field.AsDateTime := SysUtils.Date;
end;

function TsDBDateEdit.GetDataField: string;
begin
  if Assigned(FDataLink) then Result := FDataLink.FieldName else Result := '';
end;

function TsDBDateEdit.GetDataSource: TDataSource;
begin
  if Assigned(FDataLink) and Assigned(FDataLink.DataSource) then Result := FDataLink.DataSource else Result := nil;
end;

function TsDBDateEdit.GetField: TField;
begin
  if Assigned(FDataLink) then Result := FDataLink.Field else Result := nil;
end;

function TsDBDateEdit.GetReadOnly: Boolean;
begin
  if Assigned(FDataLink) then Result := FDataLink.ReadOnly else Result := True;
end;

procedure TsDBDateEdit.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited;
  if not ReadOnly and ((Key = VK_DELETE) or ((Key = VK_INSERT) and (ssShift in Shift))) then FDataLink.Edit;
end;

procedure TsDBDateEdit.KeyPress(var Key: Char);
begin
  inherited;
  if CharInSet(Key, [#32..#255]) and (FDataLink.Field <> nil) and not CharInSet(Key, ['0'..'9']) and (Key <> DateSeparator) then begin
    SysUtils.Beep;
    Key := #0;
  end;
  case Key of
    ^H, ^V, ^X, '0'..'9': FDataLink.Edit;
    #27: begin
      Reset;
      Key := #0;
    end;
  end;
end;

procedure TsDBDateEdit.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited;
  if (Operation = opRemove) and (FDataLink <> nil) and (AComponent = DataSource) then DataSource := nil;
end;

procedure TsDBDateEdit.Reset;
begin
  FDataLink.Reset;
  SelectAll;
end;

procedure TsDBDateEdit.SetDataField(const Value: string);
begin
  FDataLink.FieldName := Value;
end;

procedure TsDBDateEdit.SetDataSource(const Value: TDataSource);
begin
  if not (FDataLink.DataSourceFixed and (csLoading in ComponentState)) then FDataLink.DataSource := Value;
  if Value <> nil then Value.FreeNotification(Self);
end;

procedure TsDBDateEdit.SetReadOnly(const Value: Boolean);
begin
  FDataLink.ReadOnly := Value;
end;

procedure TsDBDateEdit.UpdateData(Sender: TObject);
var
  D: TDateTime;
begin
  ValidateEdit;
  D := Self.Date;
  if D <> 0
    then FDataLink.Field.AsDateTime := D{ + Frac(FDataLink.Field.AsDateTime) v6.68 }
    else FDataLink.Field.Clear;
end;

procedure TsDBDateEdit.WMCut(var Message: TMessage);
begin
  FDataLink.Edit;
  inherited;
end;

procedure TsDBDateEdit.WMPaint(var Message: TWMPaint);
var
  S: string;
begin
  if (csPaintCopy in ControlState) and (FDataLink.Field <> nil) then begin
    if FDataLink.Field.IsNull then begin
      S := GetDateFormat;
    end
    else
      S := FormatDateTime(GetDateFormat, FDataLink.Field.AsDateTime);
  end else S := EditText;
  inherited;
end;

procedure TsDBDateEdit.WMPaste(var Message: TMessage);
begin
  FDataLink.Edit;
  inherited;
end;

end.
