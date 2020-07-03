(*
  Name:             UfrmInstallOptions
  Copyright:        Copyright (C) 2003-2017 SIL International.
  Documentation:    
  Description:      
  Create Date:      30 Dec 2010

  Modified Date:    30 Dec 2010
  Authors:          mcdurdin
  Related Files:    
  Dependencies:     

  Bugs:             
  Todo:             
  Notes:            
  History:          30 Dec 2010 - mcdurdin - I2562 - Install options now a single dialog (new unit)
*)
unit UfrmInstallOptions;

interface

uses
  System.Classes,
  System.SysUtils,
  System.Variants,
  Vcl.Controls,
  Vcl.Dialogs,
  Vcl.ExtCtrls,
  Vcl.Forms,
  Vcl.Graphics,
  Vcl.StdCtrls,
  Winapi.Messages,
  Winapi.Windows,

  Keyman.Setup.System.InstallInfo;

type
  TfrmInstallOptions = class(TForm)
    chkStartWithWindows: TCheckBox;
    chkStartAfterInstall: TCheckBox;
    chkCheckForUpdates: TCheckBox;
    chkUpgradeKeyman7: TCheckBox;
    cmdOK: TButton;
    cmdCancel: TButton;
    chkAutomaticallyReportUsage: TCheckBox;
    sbTargets: TScrollBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure cmdOKClick(Sender: TObject);
  private
    type TPackageControl = record
  //      PackageLanguage: ;
      Package: TInstallInfoPackage;
      Location: TInstallInfoPackageFileLocation;
      Panel: TPanel;
      CheckBox: TCheckBox;
      ComboBox: TComboBox;
      function IsValid: Boolean;
    end;
  private
    chkInstallKeyman: TCheckBox;
    FPackages: array of TPackageControl;
    function GetCanUpgradeKeyman7: Boolean;
    function GetCheckForUpdates: Boolean;
    function GetStartAfterInstall: Boolean;
    function GetStartWithWindows: Boolean;
    function GetUpgradeKeyman7: Boolean;
    procedure SetCanUpgradeKeyman7(const Value: Boolean);
    procedure SetCheckForUpdates(const Value: Boolean);
    procedure SetStartAfterInstall(const Value: Boolean);
    procedure SetStartWithWindows(const Value: Boolean);
    procedure SetUpgradeKeyman7(const Value: Boolean);
    function GetAutomaticallyReportUsage: Boolean;
    procedure SetAutomaticallyReportUsage(const Value: Boolean);
    procedure SetupDynamicOptions;
    procedure cbInstallKeyboardClick(Sender: TObject);
    procedure chkInstallKeyboardClick(Sender: TObject);
    procedure chkInstallKeymanClick(Sender: TObject);
    procedure EnableControls;
    { Private declarations }
  public
    { Public declarations }
    property StartWithWindows: Boolean read GetStartWithWindows write SetStartWithWindows;
    property StartAfterInstall: Boolean read GetStartAfterInstall write SetStartAfterInstall;
    property CheckForUpdates: Boolean read GetCheckForUpdates write  SetCheckForUpdates;
    property UpgradeKeyman: Boolean read GetUpgradeKeyman7 write SetUpgradeKeyman7;
    property CanUpgradeKeyman: Boolean read GetCanUpgradeKeyman7 write SetCanUpgradeKeyman7;
    property AutomaticallyReportUsage: Boolean read GetAutomaticallyReportUsage write SetAutomaticallyReportUsage;
  end;

implementation

{$R *.dfm}

uses
  bootstrapmain,
  SetupStrings;

{ TfrmInstallOptions }

procedure TfrmInstallOptions.FormCreate(Sender: TObject);
begin
  Caption := FInstallInfo.Text(ssOptionsTitle);
  chkStartWithWindows.Caption := FInstallInfo.Text(ssOptionsStartWithWindows);
  chkStartAfterInstall.Caption := FInstallInfo.Text(ssOptionsStartAfterInstall);
  chkCheckForUpdates.Caption := FInstallInfo.Text(ssOptionsCheckForUpdates);
  // Keyman 11 and later version keyboards will always automatically update
  chkUpgradeKeyman7.Caption := FInstallInfo.Text(ssOptionsUpgradeKeyboards);
  chkAutomaticallyReportUsage.Caption := FInstallInfo.Text(ssOptionsAutomaticallyReportUsage);

  SetupDynamicOptions;
end;

function TfrmInstallOptions.GetAutomaticallyReportUsage: Boolean;
begin
  Result := chkAutomaticallyReportUsage.Checked;
end;

function TfrmInstallOptions.GetCanUpgradeKeyman7: Boolean;
begin
  Result := chkUpgradeKeyman7.Enabled;
end;

function TfrmInstallOptions.GetCheckForUpdates: Boolean;
begin
  Result := chkCheckForUpdates.Checked;
end;

function TfrmInstallOptions.GetStartAfterInstall: Boolean;
begin
  Result := chkStartAfterInstall.Checked;
end;

function TfrmInstallOptions.GetStartWithWindows: Boolean;
begin
  Result := chkStartWithWindows.Checked;
end;

function TfrmInstallOptions.GetUpgradeKeyman7: Boolean;
begin
  Result := chkUpgradeKeyman7.Checked;
end;

procedure TfrmInstallOptions.SetAutomaticallyReportUsage(const Value: Boolean);
begin
  chkAutomaticallyReportUsage.Checked := Value;
end;

procedure TfrmInstallOptions.SetCanUpgradeKeyman7(const Value: Boolean);
begin
  chkUpgradeKeyman7.Enabled := Value;
end;

procedure TfrmInstallOptions.SetCheckForUpdates(const Value: Boolean);
begin
  chkCheckForUpdates.Checked := Value;
end;

procedure TfrmInstallOptions.SetStartAfterInstall(const Value: Boolean);
begin
  chkStartAfterInstall.Checked := Value;
end;

procedure TfrmInstallOptions.SetStartWithWindows(const Value: Boolean);
begin
  chkStartWithWindows.Checked := Value;
end;

procedure TfrmInstallOptions.SetUpgradeKeyman7(const Value: Boolean);
begin
  chkUpgradeKeyman7.Checked := Value;
end;

procedure TfrmInstallOptions.SetupDynamicOptions;
var
  pack: TInstallInfoPackage;
  packLocation: TInstallInfoPackageFileLocation;
  chk: TCheckBox;
  pt: TPoint;
  cb: TComboBox;
  pan: TPanel;
  n: Integer;
  Text: string;
  selectedLang, lang: TInstallInfoPackageLanguage;
begin
  pt.x := 0;
  pt.y := 0;

  if FInstallInfo.IsNewerAvailable then
  begin
    if not FInstallInfo.IsInstalled then
      case FInstallInfo.BestMsi.LocationType of
        iilLocal:  Text := 'Install Keyman Desktop '+FInstallInfo.BestMsi.Version;
        iilOnline: Text := 'Download and install Keyman Desktop '+FInstallInfo.BestMsi.Version+' ('+IntToStr(FInstallInfo.BestMsi.Size div 1024 div 1024)+' MB)';
      end
    else
      case FInstallInfo.BestMsi.LocationType of
        iilLocal:  Text := 'Upgrade Keyman Desktop '+FInstallInfo.BestMsi.Version;
        iilOnline: Text := 'Download and upgrade Keyman Desktop to '+FInstallInfo.BestMsi.Version+' ('+IntToStr(FInstallInfo.BestMsi.Size div 1024 div 1024)+' MB)';
      end;
  end
  else if FInstallInfo.IsInstalled then
  begin
    Text := 'Keyman Desktop '+FInstallInfo.InstalledVersion.Version+' is already installed'; //TODO: Localize?
  end
  else
  begin
    // This is an error condition. We should not get here because the pre-installation checks should have forbidden it
    Assert(False, 'Offline, Keyman is not installed, and no msi is available');
  end;

  cb := TComboBox.Create(Self);
  pan := TPanel.Create(Self);
  pan.Left := pt.X;
  pan.Top := pt.Y;
  pan.Width := sbTargets.ClientWidth - GetSystemMetrics(SM_CXVSCROLL);
  pan.Height := cb.Height + 1;
  pan.BevelKind := bkNone; //bkTile;
  pan.BevelOuter := bvNone;

  sbTargets.InsertControl(pan);
  cb.Free; // Just to get the height ... todo: clean this up?

  chkInstallKeyman := TCheckBox.Create(Self);
  chkInstallKeyman.Left := 2;
  chkInstallKeyman.Top := 4;
  chkInstallKeyman.Width := pan.ClientWidth - 2;
  chkInstallKeyman.Caption := Text;
  chkInstallKeyman.Checked := FInstallInfo.ShouldInstallKeyman;
  chkInstallKeyman.Enabled := FInstallInfo.IsNewerAvailable and FInstallInfo.IsInstalled;
  chkInstallKeyman.OnClick := chkInstallKeymanClick;
  pan.InsertControl(chkInstallKeyman);

  Inc(pt.Y, pan.Height - 2);

  n := 0;
  SetLength(FPackages, FInstallInfo.Packages.Count);
  for pack in FInstallInfo.Packages do
  begin
    packLocation := pack.GetBestLocation;
    if Assigned(packLocation) then
    begin
      case packLocation.LocationType of
        iilLocal:  Text := 'Install '+packLocation.GetNameOrID(pack.ID)+' '+packLocation.Version; // TODO: localize
        iilOnline: Text := 'Download and install '+packLocation.GetNameOrID(pack.ID)+' '+packLocation.Version+' ('+IntToStr(packLocation.Size div 1024 div 1024)+' MB)'; // TODO: localize; fixup size string
      end;

      pan := TPanel.Create(Self);
      chk := TCheckBox.Create(Self);
      cb := TComboBox.Create(Self);

      pan.Left := pt.X;
      pan.Top := pt.Y;
      pan.Width := sbTargets.ClientWidth - GetSystemMetrics(SM_CXVSCROLL);
      pan.Height := cb.Height + 1;
      pan.BevelKind := bkNone; // bkTile;
      pan.BevelOuter := bvNone;

      sbTargets.InsertControl(pan);

      chk.Tag := n;
      chk.Left := 2;
      chk.Top := 4;
      chk.Width := 2 * sbTargets.ClientWidth div 3 + 1;
      chk.Caption := Text;
      chk.Checked := pack.ShouldInstall;
      chk.OnClick := chkInstallKeyboardClick;

      cb.Tag := n;
      cb.Left := pan.ClientWidth - pan.ClientWidth div 3 - 1;
      cb.Top := 0;
      cb.Width := pan.ClientWidth div 3;
      cb.Style := csDropDownList;
      cb.OnClick := cbInstallKeyboardClick;
      cb.Hint := 'Select the language that you wish to associate with '+Text+' keyboard'; // TODO: Localize
      cb.ShowHint := True;

      pan.InsertControl(chk);
      pan.InsertControl(cb);

      selectedLang := nil;
      for lang in packLocation.Languages do
      begin
        cb.Items.AddObject(lang.Name + ' ('+lang.BCP47+')', lang);
        if SameText(pack.BCP47, lang.BCP47) then selectedLang := lang;
      end;

      if cb.Items.Count = 0 then
        cb.Items.AddObject('Default language', nil); // TODO: Localize

      cb.Sorted := True;
      cb.ItemIndex := cb.Items.IndexOfObject(selectedLang);
      if cb.ItemIndex < 0 then
        cb.ItemIndex := 0;

      Inc(pt.Y, pan.Height - 2);

      FPackages[n].Package := pack;
      FPackages[n].Location := packLocation;
      FPackages[n].Panel := pan;
      FPackages[n].CheckBox := chk;
      FPackages[n].ComboBox := cb;
      Inc(n);
    end;
  end;
  EnableControls;
end;

procedure TfrmInstallOptions.cmdOKClick(Sender: TObject);
var
  pack: TPackageControl;
begin
  FInstallInfo.ShouldInstallKeyman := chkInstallKeyman.Checked;

  for pack in FPackages do
    if pack.IsValid then
    begin
      pack.Package.ShouldInstall := pack.CheckBox.Checked;
      if (pack.ComboBox.ItemIndex < 0) or
          not Assigned(pack.ComboBox.Items.Objects[pack.ComboBox.ItemIndex])
        then pack.Package.BCP47 := ''
        else pack.Package.BCP47 := (
          pack.ComboBox.Items.Objects[pack.ComboBox.ItemIndex]
          as TInstallInfoPackageLanguage).BCP47;
    end;

  ModalResult := mrOk;
end;

procedure TfrmInstallOptions.chkInstallKeymanClick(Sender: TObject);
begin
  EnableControls;
end;

procedure TfrmInstallOptions.chkInstallKeyboardClick(Sender: TObject);
begin
  EnableControls;
end;

procedure TfrmInstallOptions.cbInstallKeyboardClick(Sender: TObject);
begin
  EnableControls;
end;

procedure TfrmInstallOptions.EnableControls;
var
  i: Integer;
  e: Boolean;
begin
  e := chkInstallKeyman.Checked;
  for i := 0 to High(FPackages) do
  begin
    if FPackages[i].IsValid then
    begin
      FPackages[i].ComboBox.Enabled := FPackages[i].CheckBox.Checked;
      e := e or FPackages[i].CheckBox.Checked;
    end;
  end;
//  cmdInstall.Enabled := e;
end;

{ TfrmInstallOptions.TPackageControl }

function TfrmInstallOptions.TPackageControl.IsValid: Boolean;
begin
  Result := Assigned(Package);
end;

end.
