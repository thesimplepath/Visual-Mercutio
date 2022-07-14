; This setup script is compiled with Inno Setup Compiler version 6.2.1
; See: http://www.jrsoftware.org/
#define AppName           "Visual Mercutio"
#define AppPublisher      "The Simple Path"
#define UninstallID       AppName
#define MainAppFileName   "ZProcess32.exe"
#define IconSrcFileName   "icon2.ico"
#define AppVersion        GetVersionNumbersString("..\Visual Mercutio\exeR\" + MainAppFileName)
#define AppVersionStr     "2022 SP 1"
#define KeyCompanyName    "TheSimplePath"
#define KeyAppName        "VisualMercutio"
#define KeyAppDescription "Processes within everyone's reach."

; comment this line to allow the user to perform the file associations
#define DO_NOT_SELECT_FILE_ASSOC

[Setup]
;IMPORTANT NOTE don't add a space between the = and the value, otherwise this may create side effects while the value is used later
AppVersion              ="{#AppVersion}"
AppName                 ="{#AppName}"
AppVerName              ="{#AppName} {#AppVersionStr}"
AppCopyright            ="The MIT License - {#AppPublisher}"
AppPublisher            ="{#AppPublisher}"
AppPublisherURL         ="https://thesimplepath.ch/"
VersionInfoVersion      ="{#AppVersion}"
DefaultDirName          ="{commonpf}\{#AppName}"
DefaultGroupName        ="{#AppName}"
SetupLogging            =yes
DirExistsWarning        =no
DisableStartupPrompt    =yes
DisableWelcomePage      =no
DisableDirPage          =yes
DisableProgramGroupPage =yes
DisableFinishedPage     =no
SourceDir               ="."
OutputBaseFilename      ="VisualMercutioSetup"
OutputDir               ="..\Visual Mercutio\exeR\"
UninstallDisplayIcon    ={commonpf}\{#AppName}\{#MainAppFileName}
UninstallDisplayName    ="{#UninstallID}"
MinVersion              =6.1
ArchitecturesAllowed    =x64 x86
PrivilegesRequired      =admin
ChangesAssociations     =yes
WizardImageFile         =VisualMercutio100.bmp,VisualMercutio125.bmp,VisualMercutio150.bmp,VisualMercutio175.bmp,VisualMercutio200.bmp,VisualMercutio225.bmp,VisualMercutio250.bmp
WizardSmallImageFile    =TheSimplePath100.bmp,TheSimplePath125.bmp,TheSimplePath150.bmp,TheSimplePath175.bmp,TheSimplePath200.bmp,TheSimplePath225.bmp,TheSimplePath250.bmp
WizardImageStretch      =no
SetupIconFile           ="..\Visual Mercutio\zProcess32\res\{#IconSrcFileName}"
ShowLanguageDialog      =no
CloseApplications       =no
; more space saving compression
LZMAAlgorithm           =1
Compression             =lzma2/ultra64

[Languages]
Name: en; MessagesFile: "compiler:Default.isl";

[CustomMessages]
LanguageID            =en
WelcomeTitle          =Welcome to the {#AppName} Installer!
WelcomeDescLine       ={#AppName} {#AppVersionStr} will be installed on your computer.
SelectExtTitle        =Select the extensions to associate
SelectExtDescLine     =Please select below which extensions you will associate with the application.
SelectExtAssocCaption =Make {#AppName} the default application for the following extensions:
AllCaption            =All extensions
KlfCaption            =Mercutio Conceptor Project (.klf)
MlfCaption            =Mercutio Conceptor Model (.mlf)
RlfCaption            =Mercutio Conceptor Report (.rlf)
LaunchProgram         =Launch {#AppName}
AppIsInstalled        ={#AppName} is installed!

[Run]
; show the Launch Program checkbox after the installation
Filename: {commonpf32}\{#AppName}\{#MainAppFileName}; Description: {cm:LaunchProgram}; Flags: nowait postinstall skipifsilent runascurrentuser

[Code]
{**
* Called when the installation wizard is initialized and before it is executed
*}
procedure InitializeWizard;
begin
  // change the texts on the Welcome page
  WizardForm.WelcomeLabel1.Caption := ExpandConstant('{cm:WelcomeTitle}');
  WizardForm.WelcomeLabel2.Caption := ExpandConstant('{cm:WelcomeDescLine}');

  #ifndef DO_NOT_SELECT_FILE_ASSOC
    // change the task list main panel position and size
    WizardForm.TasksList.Top              := 0;
    WizardForm.TasksList.Height           := ScaleY(220);
    WizardForm.TasksList.Offset           := ScaleX(10);
    WizardForm.TasksList.MinItemHeight    := ScaleY(10);
    WizardForm.SelectTasksLabel.Visible   := False;
  #endif

  // change the title on the finished page, hide the main text
  WizardForm.FinishedHeadingLabel.Caption := ExpandConstant('{cm:AppIsInstalled}');
  WizardForm.FinishedLabel.Visible        := False;
end;

{**
* Called when the current page changed
*@param CurPageID - current page identifier
*}
procedure CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = wpSelectTasks then
  begin
    WizardForm.PageNameLabel.Caption        := ExpandConstant('{cm:SelectExtTitle}');
    WizardForm.PageDescriptionLabel.Caption := ExpandConstant('{cm:SelectExtDescLine}');
  end;
end;

[Tasks]
#ifndef DO_NOT_SELECT_FILE_ASSOC
  Name: "AssociateAll";              Description: {cm:AllCaption}; GroupDescription: {cm:SelectExtAssocCaption}
  Name: "AssociateAll\AssociateKlf"; Description: {cm:KlfCaption}; GroupDescription: {cm:SelectExtAssocCaption}
  Name: "AssociateAll\AssociateMlf"; Description: {cm:MlfCaption}; GroupDescription: {cm:SelectExtAssocCaption}
  Name: "AssociateAll\AssociateRlf"; Description: {cm:RlfCaption}; GroupDescription: {cm:SelectExtAssocCaption}
#endif

[Dirs]

[Files]
; x64/x86
; main app exe
Source: "..\Visual Mercutio\exeR\{#MainAppFileName}"; DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete

; external libraries
Source: "..\Visual Mercutio\exeR\CJ60Lib.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ddao35.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\easysoap.dll"; DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\libexpat.dll"; DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\mfc140.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\msvcp71.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\msvcr71.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete

; Visual Mercutio specific libraries
Source: "..\Visual Mercutio\exeR\og904as.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\OT804as.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\OV804as.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\RWUXThemeS.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\sfl204as.dll";    DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\vc6-re200l.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZBaseLib.dll";    DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zBaseSym.dll";    DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zConversion.dll"; DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zDB.dll";         DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZEvent.dll";      DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zMediator.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zModel.dll";      DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zModelBP.dll";    DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zModelWeb.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zProperty.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zPtyMgr.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zReport.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zReportBP.dll";   DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zReportWeb.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZRes32.dll";      DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zResMgr.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zScty.dll";       DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zSOAP.dll";       DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZSplash.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZSplRes.dll";     DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ztip.dll";        DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZWeb.dll";        DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\ZWinUtil32.dll";  DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zWkf.dll";        DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\zXML.dll";        DestDir: "{commonpf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete

; resource dlls
Source: "..\Visual Mercutio\exeR\resdll\zRBPropEn.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\resdll\zRBPropFr.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\resdll\zRBPropGr.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\resdll\zRMdlBPEn.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\resdll\zRMdlBPFr.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\resdll\zRMdlBPGr.dll"; DestDir: "{commonpf32}\{#AppName}\resdll"; Flags: ignoreversion restartreplace uninsrestartdelete

; documents
Source: "..\Visual Mercutio\exeR\Documents\*"; DestDir: "{commonpf32}\{#AppName}\Documents"; Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete

; risks dir
Source: "..\Visual Mercutio\exeR\Risks\*"; DestDir: "{commonpf32}\{#AppName}\Risks"; Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete

; web dir
Source: "..\Visual Mercutio\exeR\Web\*"; DestDir: "{commonpf32}\{#AppName}\Web"; Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete

; referentials
Source: "..\Visual Mercutio\exeR\LocalRef\*";                                        DestDir: "{commonpf32}\{#AppName}\LocalRef";                                        Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\Ref à copier et renommer au nom de votre projet\*"; DestDir: "{commonpf32}\{#AppName}\Ref à copier et renommer au nom de votre projet"; Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete
Source: "..\Visual Mercutio\exeR\Ref Exemple 2009\*";                                DestDir: "{commonpf32}\{#AppName}\Ref Exemple 2009";                                Flags: recursesubdirs ignoreversion restartreplace uninsrestartdelete

[Icons]
Name: "{group}\{#AppName}"; Filename: "{commonpf32}\{#AppName}\{#MainAppFileName}"; WorkingDir: "{commonpf32}\{#AppName}"

// FIXME check if the icon should be added to the Desktop, and how to link that with a "Install icon on Desktop" checkbox
// FIXME add also the 64 bit version
Name: "{commondesktop}\{#AppName}"; Filename: "{commonpf32}\{#AppName}\{#MainAppFileName}";

; Adding the Uninstall App item in the Windows Start Menu doesn't work well since Windows 8. The item is automatically removed after a short time, probably due to an automatic cleanup system,
; which may not be disabled. See the following link for further details: https://stackoverflow.com/questions/39371607/inno-setup-start-menu-uninstall-shortcut-is-not-shown-on-windows-10
;Name: "{group}\Uninstall {#AppName}"; Filename: "{uninstallexe}";

[Registry]
#ifndef DO_NOT_SELECT_FILE_ASSOC
  ; create the application capability key. The key will be located at: Computer\HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\UrsaMinor (for 64 bit OS). NOTE HKA	equals HKLM in administrative install mode, HKCU otherwise
  Root: HKA; Subkey: "Software\{#KeyCompanyName}";                                                                                                                                                     Flags: uninsdeletekeyifempty
  Root: HKA; Subkey: "Software\{#KeyCompanyName}\{#KeyAppName}";                                                                                                                                       Flags: uninsdeletekeyifempty
  Root: HKA; Subkey: "Software\{#KeyCompanyName}\{#KeyAppName}\Capability"; ValueType: string; ValueName: "ApplicationDescription"; ValueData: "{#KeyAppDescription}";                                 Flags: uninsdeletevalue
  Root: HKA; Subkey: "Software\{#KeyCompanyName}\{#KeyAppName}\Capability"; ValueType: string; ValueName: "ApplicationName";        ValueData: "{#AppName}";                                           Flags: uninsdeletevalue

  ; add capability key to registered applications list. The key will be located at: Computer\HKEY_LOCAL_MACHINE\SOFTWARE\RegisteredApplications
  Root: HKA; Subkey: "Software\RegisteredApplications";                     ValueType: string; ValueName: "{#AppName}";             ValueData: "Software\{#KeyCompanyName}\{#KeyAppName}\Capability";  Flags: uninsdeletevalue

  ; declare the verb to execute when an "Open with" command is sent to the application. The key will be located at: Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Classes\VisualMercutio. NOTE in the "Software\Classes\{#KeyAppName}" key,
  ; the ValueData value will replace the file type info shown in Windows Explorer. For that reason this value remains empty to preserve the original file type
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}";
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}";                      ValueType: string; ValueName: "";                       ValueData: "";                                                     Flags: uninsdeletekey
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\DefaultIcon";
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\DefaultIcon";          ValueType: string; ValueName: "";                       ValueData: "{commonpf32}\{#AppName}\{#MainAppFileName},0"
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\shell";
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\shell\open";
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\shell\open\command";
  Root: HKA; Subkey: "Software\Classes\{#KeyAppName}\shell\open\command";   ValueType: string; ValueName: "";                       ValueData: """{commonpf32}\{#AppName}\{#MainAppFileName}"" ""%1"""

  ; register .klf extension (Computer\HKEY_CLASSES_ROOT\.klf)
  Root: HKA; Subkey: "Software\Classes\.klf";
  Root: HKA; Subkey: "Software\Classes\.klf\OpenWithProgids";
  Root: HKA; Subkey: "Software\Classes\.klf\OpenWithProgids";                           ValueType: string; ValueName: "{#KeyAppName}"; ValueData: ""; Flags: uninsdeletevalue; Tasks: "AssociateAll\AssociateKlf"
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes"; ValueType: string; ValueName: ".klf";          ValueData: "";                          Tasks: "AssociateAll\AssociateKlf"

  ; register .mlf extension (Computer\HKEY_CLASSES_ROOT\.mlf)
  Root: HKA; Subkey: "Software\Classes\.mlf";
  Root: HKA; Subkey: "Software\Classes\.mlf\OpenWithProgids";
  Root: HKA; Subkey: "Software\Classes\.mlf\OpenWithProgids";                           ValueType: string; ValueName: "{#KeyAppName}"; ValueData: ""; Flags: uninsdeletevalue; Tasks: "AssociateAll\AssociateMlf"
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes"; ValueType: string; ValueName: ".mlf";          ValueData: "";                          Tasks: "AssociateAll\AssociateMlf"

  ; register .rlf extension (Computer\HKEY_CLASSES_ROOT\.rlf)
  Root: HKA; Subkey: "Software\Classes\.rlf";
  Root: HKA; Subkey: "Software\Classes\.rlf\OpenWithProgids";
  Root: HKA; Subkey: "Software\Classes\.rlf\OpenWithProgids";                           ValueType: string; ValueName: "{#KeyAppName}"; ValueData: ""; Flags: uninsdeletevalue; Tasks: "AssociateAll\AssociateRlf"
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes";
  Root: HKA; Subkey: "Software\Classes\Applications\{#MainAppFileName}\SupportedTypes"; ValueType: string; ValueName: ".rlf";          ValueData: "";                          Tasks: "AssociateAll\AssociateRlf"
#endif
