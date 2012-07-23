unit sRegDB;
{$I sDefs.inc}

interface

uses
  Classes;

procedure Register;

implementation

uses sDBEdit, sDBMemo, sDBComboBox, sDBLookupComboBox, sDBText, sDBRadioGroup, sDBRichEdit,
  sDBLookupListBox, sDBListBox, sDBCheckBox, sDBNavigator, sDBDateEdit,
  sDBCalcEdit, acDBTextFX, acDBCtrlGrid, acDBGrid;

procedure Register;
begin
  RegisterComponents('AlphaDBControls', [
    TsDBEdit, TsDBMemo, TsDBComboBox, TsDBLookupComboBox, TsDBText, TsDBListBox,
    TsDBLookupListBox, TsDBCheckBox, TsDBNavigator, TsDBDateEdit, TsDBRadioGroup,
    TsDBCalcEdit, TsDBRichEdit, TsDBTextFX, TsDBCtrlGrid, TsDBGrid]);
end;

end.
