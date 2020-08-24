program kmshell;

uses
  Winapi.Windows,
  comobj,
  Forms,
  SysUtils,
  ActiveX,
  Dialogs,
  initprog in 'main\initprog.pas',
  RegistryKeys in '..\..\global\delphi\general\RegistryKeys.pas',
  Registry,
  UfrmMain in 'main\UfrmMain.pas' {frmMain},
  kmint in 'util\kmint.pas',
  GetOsVersion in '..\..\global\delphi\general\GetOsVersion.pas',
  DebugPaths in '..\..\global\delphi\general\DebugPaths.pas',
  VersionInfo in '..\..\global\delphi\general\VersionInfo.pas',
  UfrmHTML in 'main\UfrmHTML.pas' {frmHTML},
  HotkeyUtils in '..\..\global\delphi\general\HotkeyUtils.pas',
  Unicode in '..\..\global\delphi\general\Unicode.pas',
  exceptionw in '..\..\global\delphi\general\exceptionw.pas',
  utilkmshell in 'util\utilkmshell.pas',
  custinterfaces in '..\..\global\delphi\cust\custinterfaces.pas',
  UfrmInstallKeyboard in 'install\UfrmInstallKeyboard.pas' {frmInstallKeyboard},
  MessageIdentifiers in '..\..\global\delphi\cust\MessageIdentifiers.pas',
  KeyNames in '..\..\global\delphi\general\KeyNames.pas',
  klog in '..\..\global\delphi\general\klog.pas',
  keymanapi_TLB in '..\..\engine\kmcomapi\keymanapi_TLB.pas',
  UfrmSplash in 'startup\UfrmSplash.pas' {frmSplash},
  UfrmKeymanBase in '..\..\global\delphi\ui\UfrmKeymanBase.pas' {frmKeymanBase},
  httpuploader in '..\..\global\delphi\general\httpuploader.pas',
  httpuploader_messageprocessor_forms in '..\..\global\delphi\general\httpuploader_messageprocessor_forms.pas',
  utildir in '..\..\global\delphi\general\utildir.pas',
  XMLRenderer in '..\..\global\delphi\ui\XMLRenderer.pas',
  KeyboardListXMLRenderer in 'render\KeyboardListXMLRenderer.pas',
  OptionsXMLRenderer in 'render\OptionsXMLRenderer.pas',
  HotkeysXMLRenderer in 'render\HotkeysXMLRenderer.pas',
  SupportXMLRenderer in 'render\SupportXMLRenderer.pas',
  LanguagesXMLRenderer in 'render\LanguagesXMLRenderer.pas',
  utilhttp in '..\..\global\delphi\general\utilhttp.pas',
  UfrmChangeHotkey in 'main\UfrmChangeHotkey.pas' {frmChangeHotkey},
  utilhotkey in '..\..\global\delphi\general\utilhotkey.pas',
  InterfaceHotkeys in '..\..\global\delphi\general\InterfaceHotkeys.pas',
  utilsystem in '..\..\global\delphi\general\utilsystem.pas',
  Upload_Settings in '..\..\global\delphi\general\Upload_Settings.pas',
  UfrmOnlineUpdateNewVersion in 'main\UfrmOnlineUpdateNewVersion.pas' {frmOnlineUpdateNewVersion},
  OnlineUpdateCheck in 'main\OnlineUpdateCheck.pas',
  utilxml in '..\..\global\delphi\general\utilxml.pas',
  UfrmInstallKeyboardFromWeb in 'install\UfrmInstallKeyboardFromWeb.pas' {frmInstallKeyboardFromWeb},
  UfrmWebContainer in '..\..\global\delphi\ui\UfrmWebContainer.pas' {frmWebContainer},
  MessageIdentifierConsts in '..\..\global\delphi\cust\MessageIdentifierConsts.pas',
  Keyman.UI.UfrmProgress in '..\..\global\delphi\general\Keyman.UI.UfrmProgress.pas' {frmProgress},
  kmcomapi_errors in '..\..\global\delphi\general\kmcomapi_errors.pas',
  GenericXMLRenderer in 'render\GenericXMLRenderer.pas',
  help in 'main\help.pas',
  UfrmProxyConfiguration in 'main\UfrmProxyConfiguration.pas' {frmProxyConfiguration: TTntForm},
  OnlineUpdateCheckMessages in 'main\OnlineUpdateCheckMessages.pas',
  WelcomeXMLRenderer in 'render\WelcomeXMLRenderer.pas',
  ValidateKeymanInstalledSystemKeyboards in 'main\ValidateKeymanInstalledSystemKeyboards.pas',
  OnlineConstants in '..\..\global\delphi\productactivation\OnlineConstants.pas',
  uninstall in 'install\uninstall.pas',
  KeymanControlMessages in '..\..\global\delphi\general\KeymanControlMessages.pas',
  HintConsts in '..\..\global\delphi\hints\HintConsts.pas',
  UfrmTextEditor in 'startup\help\UfrmTextEditor.pas' {frmTextEditor: TTntForm},
  ttinfo in '..\..\global\delphi\general\ttinfo.pas',
  findfonts in '..\..\global\delphi\general\findfonts.pas',
  KMShellHints in 'util\KMShellHints.pas',
  UfrmHint in '..\..\global\delphi\hints\UfrmHint.pas' {frmHint: TTntForm},
  KeymanTextEditorRichEdit in '..\..\global\delphi\comp\KeymanTextEditorRichEdit.pas',
  Hints in '..\..\global\delphi\hints\Hints.pas',
  utilcheckfonts in '..\..\global\delphi\general\utilcheckfonts.pas',
  wininet5 in '..\..\global\delphi\general\wininet5.pas',
  GlobalProxySettings in '..\..\global\delphi\general\GlobalProxySettings.pas',
  UFixupMissingFile in '..\..\global\delphi\ui\UFixupMissingFile.pas',
  UImportOlderVersionKeyboards in 'main\UImportOlderVersionKeyboards.pas',
  UImportOlderKeyboardUtils in 'main\UImportOlderKeyboardUtils.pas',
  utiluac in '..\..\global\delphi\general\utiluac.pas',
  UserMessages in '..\..\global\delphi\general\UserMessages.pas',
  UILanguages in 'util\UILanguages.pas',
  utilmsxml in '..\..\global\delphi\general\utilmsxml.pas',
  UfrmKeyboardOptions in 'main\UfrmKeyboardOptions.pas' {frmKeyboardOptions},
  UfrmOnlineUpdateIcon in 'main\UfrmOnlineUpdateIcon.pas' {frmOnlineUpdateIcon},
  KeymanTrayIcon in '..\..\engine\keyman\KeymanTrayIcon.pas',
  UImportOlderVersionKeyboards10 in 'main\UImportOlderVersionKeyboards10.pas',
  VisualKeyboard in '..\..\global\delphi\visualkeyboard\VisualKeyboard.pas',
  VKeyChars in '..\..\global\delphi\general\VKeyChars.pas',
  UfrmPrintOSK in 'util\UfrmPrintOSK.pas' {frmPrintOSK},
  VisualKeyboardExportHTML in '..\..\global\delphi\visualkeyboard\VisualKeyboardExportHTML.pas',
  VisualKeyboardExportXML in '..\..\global\delphi\visualkeyboard\VisualKeyboardExportXML.pas',
  VisualKeyboardParameters in '..\..\global\delphi\visualkeyboard\VisualKeyboardParameters.pas',
  MSXML2_TLB in '..\..\global\delphi\tlb\MSXML2_TLB.pas',
  VKeys in '..\..\global\delphi\general\VKeys.pas',
  ExtShiftState in '..\..\global\delphi\comp\ExtShiftState.pas',
  UImportOlderVersionSettings in 'main\UImportOlderVersionSettings.pas',
  KeymanMutex in '..\..\global\delphi\general\KeymanMutex.pas',
  ErrorControlledRegistry in '..\..\global\delphi\vcl\ErrorControlledRegistry.pas',
  MSXMLDomCreate in '..\..\global\delphi\general\MSXMLDomCreate.pas',
  utilexecute in '..\..\global\delphi\general\utilexecute.pas',
  KeymanVersion in '..\..\global\delphi\general\KeymanVersion.pas',
  UfrmScriptError in '..\..\global\delphi\general\UfrmScriptError.pas' {frmScriptError},
  BaseKeyboards in '..\..\global\delphi\general\BaseKeyboards.pas',
  LoadIndirectStringUnit in '..\..\engine\keyman\langswitch\LoadIndirectStringUnit.pas',
  Glossary in '..\..\global\delphi\general\Glossary.pas',
  UfrmInstallKeyboardLanguage in 'install\UfrmInstallKeyboardLanguage.pas' {frmInstallKeyboardLanguage},
  UfrmBaseKeyboard in 'main\UfrmBaseKeyboard.pas' {frmBaseKeyboard},
  UnicodeBlocks in '..\..\global\delphi\general\UnicodeBlocks.pas',
  TempFileManager in '..\..\global\delphi\general\TempFileManager.pas',
  keyman_msctf in '..\..\global\delphi\winapi\keyman_msctf.pas',
  utiltsf in '..\..\global\delphi\general\utiltsf.pas',
  utilolepicture in '..\..\engine\kmcomapi\util\utilolepicture.pas',
  kmxfile in '..\..\global\delphi\general\kmxfile.pas',
  utilfiletypes in '..\..\global\delphi\general\utilfiletypes.pas',
  CRC32 in '..\..\global\delphi\general\CRC32.pas',
  input_installlayoutortip in '..\..\global\delphi\winapi\input_installlayoutortip.pas',
  KPInstallPackageStartMenu in '..\..\global\delphi\general\KPInstallPackageStartMenu.pas',
  kmpinffile in '..\..\global\delphi\general\kmpinffile.pas',
  PackageFileFormats in '..\..\global\delphi\general\PackageFileFormats.pas',
  PackageInfo in '..\..\global\delphi\general\PackageInfo.pas',
  utilstr in '..\..\global\delphi\general\utilstr.pas',
  utilwow64 in '..\..\global\delphi\general\utilwow64.pas',
  KPUninstallPackageStartMenu in '..\..\global\delphi\general\KPUninstallPackageStartMenu.pas',
  KPInstallFontKMShell in 'util\KPInstallFontKMShell.pas',
  UpgradeMnemonicLayout in 'install\UpgradeMnemonicLayout.pas',
  UfrmKeepInTouch in 'main\UfrmKeepInTouch.pas' {frmKeepInTouch},
  UtilCheckOnline in 'util\UtilCheckOnline.pas',
  KeyboardTIPCheck in 'main\KeyboardTIPCheck.pas',
  utilfocusappwnd in 'util\utilfocusappwnd.pas',
  UImportOlderVersionKeyboards8 in 'main\UImportOlderVersionKeyboards8.pas',
  KeymanPaths in '..\..\global\delphi\general\KeymanPaths.pas',
  StockFileNames in '..\..\global\delphi\cust\StockFileNames.pas',
  KeymanEngineControl in '..\..\global\delphi\general\KeymanEngineControl.pas',
  KeymanOptionNames in '..\..\global\delphi\general\KeymanOptionNames.pas',
  VisualKeyboardLoaderBinary in '..\..\global\delphi\visualkeyboard\VisualKeyboardLoaderBinary.pas',
  VisualKeyboardLoaderXML in '..\..\global\delphi\visualkeyboard\VisualKeyboardLoaderXML.pas',
  VisualKeyboardSaverBinary in '..\..\global\delphi\visualkeyboard\VisualKeyboardSaverBinary.pas',
  VisualKeyboardSaverXML in '..\..\global\delphi\visualkeyboard\VisualKeyboardSaverXML.pas',
  UtilWaitForTSF in 'util\UtilWaitForTSF.pas',
  BCP47Tag in '..\..\global\delphi\general\BCP47Tag.pas',
  JsonUtil in '..\..\global\delphi\general\JsonUtil.pas',
  Keyman.System.LanguageCodeUtils in '..\..\global\delphi\general\Keyman.System.LanguageCodeUtils.pas',
  Keyman.System.Standards.ISO6393ToBCP47Registry in '..\..\global\delphi\standards\Keyman.System.Standards.ISO6393ToBCP47Registry.pas',
  Keyman.System.Standards.LCIDToBCP47Registry in '..\..\global\delphi\standards\Keyman.System.Standards.LCIDToBCP47Registry.pas',
  kmxfileconsts in '..\..\global\delphi\general\kmxfileconsts.pas',
  Keyman.System.UpdateCheckResponse in '..\..\global\delphi\general\Keyman.System.UpdateCheckResponse.pas',
  Keyman.System.Standards.BCP47SubtagRegistry in '..\..\global\delphi\standards\Keyman.System.Standards.BCP47SubtagRegistry.pas',
  Keyman.System.Standards.NRSIAllTagsRegistry in '..\..\global\delphi\standards\Keyman.System.Standards.NRSIAllTagsRegistry.pas',
  Keyman.System.CanonicalLanguageCodeUtils in '..\..\global\delphi\general\Keyman.System.CanonicalLanguageCodeUtils.pas',
  Keyman.System.Standards.BCP47SuppressScriptRegistry in '..\..\global\delphi\standards\Keyman.System.Standards.BCP47SuppressScriptRegistry.pas',
  UImportOlderVersionKeyboards9 in 'main\UImportOlderVersionKeyboards9.pas',
  Keyman.System.UpgradeRegistryKeys in '..\..\global\delphi\general\Keyman.System.UpgradeRegistryKeys.pas',
  UImportOlderVersionKeyboards9Plus in 'main\UImportOlderVersionKeyboards9Plus.pas',
  Keyman.Configuration.UI.MitigationForWin10_1803 in 'install\Keyman.Configuration.UI.MitigationForWin10_1803.pas',
  Keyman.System.CEFManager in '..\..\global\delphi\chromium\Keyman.System.CEFManager.pas',
  Keyman.UI.UframeCEFHost in '..\..\global\delphi\chromium\Keyman.UI.UframeCEFHost.pas',
  UfrmHelp in 'help\UfrmHelp.pas' {frmHelp},
  Sentry.Client in '..\..\ext\sentry\Sentry.Client.pas',
  Sentry.Client.Vcl in '..\..\ext\sentry\Sentry.Client.Vcl.pas',
  sentry in '..\..\ext\sentry\sentry.pas',
  Keyman.System.KeymanSentryClient in '..\..\global\delphi\general\Keyman.System.KeymanSentryClient.pas',
  Keyman.Configuration.UI.UfrmDiagnosticTests in 'util\Keyman.Configuration.UI.UfrmDiagnosticTests.pas' {frmDiagnosticTests},
  Keyman.Configuration.System.UmodWebHttpServer in 'web\Keyman.Configuration.System.UmodWebHttpServer.pas' {modWebHttpServer: TDataModule},
  Keyman.Configuration.System.HttpServer.App in 'web\Keyman.Configuration.System.HttpServer.App.pas',
  Keyman.System.HttpServer.Base in '..\..\global\delphi\web\Keyman.System.HttpServer.Base.pas',
  Keyman.Configuration.System.HttpServer.SharedData in 'web\Keyman.Configuration.System.HttpServer.SharedData.pas',
  Keyman.Configuration.System.HttpServer.App.OnlineUpdate in 'web\Keyman.Configuration.System.HttpServer.App.OnlineUpdate.pas',
  Keyman.System.LocaleStrings in '..\..\global\delphi\cust\Keyman.System.LocaleStrings.pas',
  Keyman.Configuration.System.HttpServer.App.InstallKeyboard in 'web\Keyman.Configuration.System.HttpServer.App.InstallKeyboard.pas',
  Keyman.Configuration.System.HttpServer.App.ProxyConfiguration in 'web\Keyman.Configuration.System.HttpServer.App.ProxyConfiguration.pas',
  Keyman.Configuration.System.HttpServer.App.ConfigMain in 'web\Keyman.Configuration.System.HttpServer.App.ConfigMain.pas',
  Keyman.Configuration.UI.InstallFile in 'install\Keyman.Configuration.UI.InstallFile.pas',
  Keyman.Configuration.UI.KeymanProtocolHandler in 'install\Keyman.Configuration.UI.KeymanProtocolHandler.pas',
  Keyman.Configuration.System.KeymanUILanguageManager in 'main\Keyman.Configuration.System.KeymanUILanguageManager.pas',
  Keyman.System.UILanguageManager in '..\..\global\delphi\general\Keyman.System.UILanguageManager.pas',
  Keyman.Configuration.System.TIPMaintenance in 'install\Keyman.Configuration.System.TIPMaintenance.pas',
  UfrmDownloadProgress in 'util\UfrmDownloadProgress.pas' {frmDownloadProgress};

{$R VERSION.RES}
{$R manifest.res}

// CEF3 needs to set the LARGEADDRESSAWARE flag which allows 32-bit processes to use up to 3GB of RAM.
// If you don't add this flag the rederer process will crash when you try to load large images.
{$SetPEFlags IMAGE_FILE_LARGE_ADDRESS_AWARE}

const
  LOGGER_DESKTOP_KMSHELL = TKeymanSentryClient.LOGGER_DESKTOP + '.kmshell';
begin
  TKeymanSentryClient.Start(TSentryClientVcl, kscpDesktop, LOGGER_DESKTOP_KMSHELL);
  try
    CoInitFlags := COINIT_APARTMENTTHREADED;
    FInitializeCEF := TCEFManager.Create;
    try
      if FInitializeCEF.Start then
      try
        Application.Initialize;
        Application.Title := 'Keyman Configuration';
        Application.CreateForm(TmodWebHttpServer, modWebHttpServer);
  try
          Run;
        finally
          FreeAndNil(modWebHttpServer);
        end;
      except
        on E:Exception do
          SentryHandleException(E);
      end;
    finally
      FInitializeCEF.Free;
    end;
  finally
    TKeymanSentryClient.Stop;
  end;
end.

