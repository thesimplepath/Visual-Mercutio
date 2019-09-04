// **************************************************************************************************************
// *                                                Classe ZAMainApp                                            *
// **************************************************************************************************************
// * Cette classe est la classe de base de l'application. Elle prend en charge les opérations basiques sur les    *
// * fichiers, la gestion de base des documents, des serveurs, de la base de registre, etc...                    *
// **************************************************************************************************************

//## begin module%334FC4630327.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC4630327.cm

//## begin module%334FC4630327.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC4630327.cp

//## Module: ZAMApp%334FC4630327; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZAMApp.cpp

//## begin module%334FC4630327.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC4630327.additionalIncludes

//## begin module%334FC4630327.includes preserve=yes
#include "planfin.hdf"
#include "mainfrm.h"
#include "zBaseLib\PSS_PlanFinObj.h"
#include "zBaseLib\ZANumbrd.h"
#include "zBaseLib\PSS_PLFNBitmap.h"
#include "zBaseLib\PSS_PLFNBoundText.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Edit.h"

#include "Resource.h"
#include "zRes32\zRes.h"

// UserLd
#include "zBaseLib\PSS_UserLoader.h"

#include "zWinUtil32\PSS_SelectServerWizard.h"
#include "zBaseLib\ZMessage.h"

// this was previoulsy necessary because Visual Mercutio was a commercial product before being open source, but now...
// uncomment the libe below to re-enable the product key protection
//#define _EVALUATION_VERSION

#ifdef _EVALUATION_VERSION
#include "zScty\security.h"
#include "zScty\secuchk.h"
#endif // _EVALUATION_VERSION

// FileDlg
#include "zBaseLib\PSS_FileDialog.h"
// BObjUtil
#include "zBaseLib\PSS_ObjectUtility.h"

#include "ZEvent.h"

// PaintRes
#include "zBaseLib\PSS_PaintResources.h"

#ifdef _WIN32
#include <WinSpool.h>
#endif

#include "zBaseLib\ZDirectory.h"

#include "zSplash\PSS_SplashController.h"

// Used to access predefined registry keys
#include "RegistryDef.h"
#include "zBaseLib\PSS_RegisterSetup.h"

#include <CTYPE.H>
#include <locale.h>

// ZAMApp
#include "ZAMApp.h"

// Includes html help constants
#include <htmlhelp.h>
#include "ZHelpContext.h"

extern "C" extern void WINAPI InitZSplResDLL();
extern "C" extern void WINAPI InitZRes32DLL();

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 20 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **************************************************************************************************************
// *                                                Help ID Mapping                                                *
// **************************************************************************************************************

static const DWORD aMenuHelpIDs[] =
{
    ID_FILE_NEW,            IDH_FILE_NEW,
    ID_FILE_OPEN,            IDH_FILE_OPEN,
    ID_FILE_SAVE,            IDH_FILE_SAVE,
    ID_EDIT_CUT,            IDH_EDIT_CUT,
    ID_EDIT_COPY,            IDH_EDIT_COPY,
    ID_EDIT_PASTE,            IDH_EDIT_PASTE,
    ID_FILE_PRINT,            IDH_FILE_PRINT,
    ID_APP_ABOUT,            IDH_APP_ABOUT,
    ID_FILE_PRINT_PREVIEW,    IDH_FILE_PRINT_PREVIEW,
    0,                        0
};

// **************************************************************************************************************
// *                                           Ini global entry keys ZAMApp                                        *
// **************************************************************************************************************

#define    szFirstUseEntry            _T( "First Use" )
#define    szSubDirectoryNameEntry _T( "Ref Sub Directory Name" )

#define DEFAULT_ICON_INDEX        0

static char BASED_CODE            szDefaultIcon[] = _T("%s\\DefaultIcon");

AFX_STATIC_DATA const TCHAR        _afxShellOpenFmt[] = _T("%s\\shell\\open\\%s");
AFX_STATIC_DATA const TCHAR        _afxShellPrintFmt[] = _T("%s\\shell\\print\\%s");
AFX_STATIC_DATA const TCHAR        _afxShellPrintToFmt[] = _T("%s\\shell\\printto\\%s");
AFX_STATIC_DATA const TCHAR        _afxDefaultIconFmt[] = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR        _afxShellNewFmt[] = _T("%s\\ShellNew");

AFX_STATIC_DATA const TCHAR        _afxIconIndexFmt[] = _T(",%d");
AFX_STATIC_DATA const TCHAR        _afxCommand[] = _T("command");
AFX_STATIC_DATA const TCHAR        _afxOpenArg[] = _T(" \"%1\"");
AFX_STATIC_DATA const TCHAR        _afxPrintArg[] = _T(" /p \"%1\"");
AFX_STATIC_DATA const TCHAR        _afxPrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const TCHAR        _afxDDEArg[] = _T(" /dde");

AFX_STATIC_DATA const TCHAR        _afxDDEExec[] = _T("ddeexec");
AFX_STATIC_DATA const TCHAR        _afxDDEOpen[] = _T("[open(\"%1\")]");
AFX_STATIC_DATA const TCHAR        _afxDDEPrint[] = _T("[print(\"%1\")]");
AFX_STATIC_DATA const TCHAR        _afxDDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

AFX_STATIC_DATA const TCHAR        _afxShellNewValueName[] = _T("NullFile");
AFX_STATIC_DATA const TCHAR        _afxShellNewValue[] = _T("");

// **************************************************************************************************************
// *                                   Fonctions de gestion de la base de registres                                *
// **************************************************************************************************************

// Cette fonction inscrit ou mets à jour une paire clé-valeur dans le registre au démarrage de l'application.
AFX_STATIC BOOL AFXAPI _zSetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
{
    if (lpszValueName == NULL)
    {
        if (::RegSetValue(HKEY_CLASSES_ROOT,
                          lpszKey,
                          REG_SZ,
                          lpszValue,
                          lstrlen(lpszValue) * sizeof(TCHAR)) != ERROR_SUCCESS)
        {
            TRACE1(_T("Warning: registration database update failed for key '%s'.\n"), lpszKey);
            return FALSE;
        }

        return TRUE;
    }
    else
    {
        HKEY hKey;

        if (::RegCreateKey(HKEY_CLASSES_ROOT, lpszKey, &hKey) == ERROR_SUCCESS)
        {
            LONG lResult = ::RegSetValueEx(hKey,
                                           lpszValueName,
                                           0,
                                           REG_SZ,
                                           (CONST BYTE*)lpszValue,
                                           (lstrlen(lpszValue) + 1) * sizeof(TCHAR));

            if (::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS)
            {
                return TRUE;
            }
        }

        TRACE1(_T("Warning: registration database update failed for key '%s'.\n"), lpszKey);
        return FALSE;
    }
}

// **************************************************************************************************************
// *                                                Classe ZAMainApp                                            *
// **************************************************************************************************************

IMPLEMENT_DYNAMIC(ZAMainApp, CWinApp)

BEGIN_MESSAGE_MAP(ZAMainApp, PSS_SingleInstanceApplication)
    //{{AFX_MSG_MAP(ZAApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// **************************************************************************************************************
// *                                           Construction / Destruction                                        *
// **************************************************************************************************************

ZAMainApp::ZAMainApp()
    : m_pOldSelectedObj(NULL),
    m_pCurrentDocument(NULL),
    m_FieldRepository(NULL)
#ifdef _ZCHECKINFO
    , m_ApplicationInfoType(ZBCriptedFileApplicationTypeInfo::Unknown)
#endif
{
    ZAGlobal::StartInitialization();

    m_pCurrentDocument = NULL;
    m_IDD_Splash = 0;
    m_IDD_About = 0;
    m_IDD_Support = 0;

    // JMR-MODIF - Le 23 août 2005 - Gestion dynamique des objets.
    m_FieldRepository = new PSS_FieldRepository();
}

ZAMainApp::~ZAMainApp()
{}

// **************************************************************************************************************
// *                                Gestionnaires des messages de la classe ZAMAinApp                            *
// **************************************************************************************************************

BOOL ZAMainApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    BOOL bResult = CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

    if (bResult)
    {
        return TRUE;
    }

    if (m_pDocManager)
    {
        POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();

        while (pos != NULL)
        {
            CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
            ASSERT_KINDOF(CDocTemplate, pTemplate);

            if (pTemplate->IsKindOf(RUNTIME_CLASS(PSS_DocTemplateEx)))
            {
                if ((nID >= ((PSS_DocTemplateEx*)pTemplate)->GetMenuID()) &&
                    (nID <= ((PSS_DocTemplateEx*)pTemplate)->GetMenuID() + M_MRU_RANGE))
                {
                    bResult |= pTemplate->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
                }
            }
        }
    }

    return bResult;
}

bool ZAMainApp::OnRegisterAdditionalTemplate()
{
    // In the base class do nothing
    return true;
}

void ZAMainApp::OnServerChanged()
{
    TemplateDirectoryHasChanged();
    ProcessTemplateDirectoryHasChanged();
    ModelTemplateDirectoryHasChanged();
}

// **************************************************************************************************************
// *                                        Fonctions de la classe ZAMainApp                                    *
// **************************************************************************************************************

// ***************************************** Initialisation et désallocation ************************************

// Cette fonction est appelée lorsque l'application s'initialise.
BOOL ZAMainApp::InitAppl()
{
    // No errors
    return(TRUE);
}

// Cette fonction est appelée lorsque l'initialisation a été effectuée, mais avant que le programme débute.
BOOL ZAMainApp::PostInitAppl()
{
    //## begin ZAMainApp::PostInitAppl%910716404.body preserve=yes
    return TRUE;
    //## end ZAMainApp::PostInitAppl%910716404.body
}

// Cette fonction est appelée lorsqu'une instance de l'application doit être initialisée.
BOOL ZAMainApp::InitInstance()
{
    if (!AfxOleInit())
    {
        AfxMessageBox(_T("Ole Initialization failed"));
        return FALSE;
    }

    // Check DDE
    if (!PSS_SingleInstanceApplication::InitInstance())
    {
        return false;
    }

    // Force load of resource dlls
    InitZSplResDLL();
    InitZRes32DLL();

    // Call the virtual method which allows derived class to change the
    // m_pszProfileName variable
    OnChangeWinIniFilename();

    // Retreive the right help filename
    m_HelpFile = OnBuildHelpFilename();

    // Assigns globally the application directory
    ZAGlobal::SetApplicationDirectory(GetApplicationDir());

#ifndef _ZNOSPLASH
    // Start Splash
    PSS_SplashController Splash;

    if (m_IDD_Splash != 0)
    {
        Splash.Show(m_IDD_Splash, 5);
    }
#endif

    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();            // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();    // Call this when linking to MFC statically
#endif

// Standard initialization
// If you are not using these features and wish to reduce the size
// of your final executable, you should remove from the following
// the specific initialization routines you do not need.

// JMR-MODIF - Le 20 octobre 2005 - Fonction obsolète, remplacée par un traitement de l'évenement CTLCOLOR
// directement dans les boîtes de dialogues.
//    SetDialogBkColor();                // Set dialog background color to gray
    LoadStdProfileSettings(0);    // Load standard INI file options (including MRU)

#ifdef _ZCHECKINFO
    // Load the application type
    LoadApplicationInfoType();

    if (GetApplicationInfoType() == ZBCriptedFileApplicationTypeInfo::Unknown)
    {
    #ifndef _ZNOSPLASH
        if (m_IDD_Splash != 0)
        {
            // End the splash display
            Splash.EndDisplay();
        }
    #endif

        ZIMessage Message;
        Message.DisplayMessage(IDS_APPINFO_MISSING, IDS_APPINFO_MISSING_TITLE);

        return FALSE;
    }

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(10);
        Splash.SetText(IDS_SPL_LOADOPTIONS);
    }
#endif

#endif

    // JMR-MODIF - Le 15 avril 2007 - Ajouté GetApplicationDirectory() dans la variable Create.
    // initialize the application options
    GetApplicationOptions().Create(m_pszProfileName, GetApplicationDir());

    if (!GetApplicationOptions().LoadOption())
        return FALSE;

    if (!LoadApplicationOptions())
    {
    #ifndef _ZNOSPLASH
        if (m_IDD_Splash != 0)
        {
            // End the splash display
            Splash.Hide();
        }
    #endif

        return FALSE;
    }

#ifdef _ZCHECKINFO
    // Check the product key
    if (GetProductKeyFileInfo() != GetRegisteredProductKey())
    {
    #ifndef _ZNOSPLASH
        if (m_IDD_Splash != 0)
        {
            // End the splash display
            Splash.EndDisplay();
        }
    #endif

        ZIMessage Message;
        Message.DisplayMessage(IDS_APPINFO_WRONGKEY, IDS_APPINFO_WRONGKEY_TITLE);

        return FALSE;
    }

#endif // _ZCHECKINFO

    // Call the initializer for the application
    if (!InitAppl())
    {
    #ifndef _ZNOSPLASH
        if (m_IDD_Splash != 0)
        {
            // End the splash display
            Splash.Hide();
        }
    #endif
        return FALSE;
    }

    // The main window has been initialized, so show and update it.
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    // Check if first use
    CString FirstLoad = AfxGetApp()->GetProfileString(ApplicationConfigSectionName, szFirstUseEntry, _T("0"));

    if (FirstLoad == _T("1"))
    {
        const CString subDirectory = AfxGetApp()->GetProfileString(ApplicationConfigSectionName,
                                                                   szSubDirectoryNameEntry,
                                                                   _T(""));

        const CString serverDirectory = ZDirectory::NormalizeDirectory(GetApplicationDir()) + _T("\\") + subDirectory;
        const CString serverIniFile = GetServer().CreateInitialEnvironment(serverDirectory);

        // then asks the server to create an initial environement
        if (serverIniFile.IsEmpty())
        {
            ZIMessage Message;
            Message.DisplayMessage(IDS_ONFIRSTUSE_FAIL, IDS_ONFIRSTUSE_FAIL_TITLE);

            return FALSE;
        }
        // Assign the new server ini file
        SetServerIniFile(serverIniFile);
    }

    if (GetServerIniFile().IsEmpty())
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_NOSERVERDEFINED, MB_YESNO) == IDNO)
        {
            ZIMessage Message;
            Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }

        if (!ChooseServer())
        {
            ZIMessage Message;
            Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }
    }

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(20);
        Splash.SetText(IDS_SPL_OPENSERVER);
    }
#endif

    // If we can't open a server session, then
    // quit the application
    if (!OpenServerSession())
    {
        return FALSE;
    }

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(40);
        Splash.SetText(IDS_SPL_LOADUSERS);
    }
#endif

#ifdef _ZCHECKINFO
    // Load users only for EntrepriseEdition
    if (GetApplicationInfoType() == ZBCriptedFileApplicationTypeInfo::EntrepriseEdition)
    {
    #endif // _ZCHECKINFO

        // Check if required to load the user file
        if (LoadUserFile())
        {
            if (!LoadAllUsers())
            {
                ZIMessage Message;
                Message.DisplayMessage(IDS_LOADUSERSFAIL_T, IDS_LOADUSERSFAIL_WT);
                return FALSE;
            }

            // Check if required to authenticate the user
            if (UserAuthenticationRequired())
            {
                ZAGlobal::InitializeNetwork();

                // Not a registered user
                if (ZAGlobal::GetConnectedUser() == NULL)
                {
                    ZIMessage Message;
                    Message.DisplayMessage(IDS_USERNOTREGISTERED_T, IDS_USERNOTREGISTERED_WT);

                    return FALSE;
                }
            }

            // Advise for user manager loaded
            AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_USERMANAGER,
                                                      0, // Nothing
                                                      (LPARAM)&ZAGlobal::GetUserManager());
        }

    #ifdef _ZCHECKINFO
    }
#endif // _ZCHECKINFO

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(60);
        Splash.SetText(IDS_SPL_LOADTMPL);
    }
#endif

    // Create the template manager
    ZAGlobal::GetTemplateManager().Create(GetTemplateDirectory(), ZAGlobal::GetFileExtension());

    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_TEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetTemplateManager());

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(70);
        Splash.SetText(IDS_SPL_LOADPROCTMPL);
    }
#endif

    // Create the process template manager
    ZAGlobal::GetProcessTemplateManager().Create(GetProcessTemplateDirectory(),
                                                 ZAGlobal::GetProcessFileExtension());

    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_PROCESSTEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetTemplateManager());

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(80);
        Splash.SetText(IDS_SPL_LOADMODELTMPL);
    }
#endif

    // Create the model template manager
    ZAGlobal::GetModelTemplateManager().Create(GetModelTemplateDirectory(), ZAGlobal::GetModelFileExtension());

    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_MODELTEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetModelTemplateManager());

    // enable file manager drag/drop and DDE Execute open
    ZAMainApp::EnableShellOpen();

    // Call the virtual function for registering
    // additional templates
    OnRegisterAdditionalTemplate();

    // Now register all the templates
    ZAMainApp::RegisterShellFileTypes(TRUE);

    m_pMainWnd->DragAcceptFiles();

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR ) || defined( _ZWRITER ) || defined( _ZPROCESS )

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(90);
        Splash.SetText(IDS_SPL_LOADFIELD);
    }
#endif

    if (!LoadGlobalFieldRepository())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NOGFIELDFILEVALUE, MB_OK);
    }

    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_FIELDREPOSITORY,
                                              0,
                                              (LPARAM)GetFieldRepository());

    // Initialize object definition
    PSS_ObjectUtility::InitializeDefinition(GetServer().GetFieldDefinitionIniFile());

    // initialize the painting resources
    PSS_PaintResources::Initialize();

    // Initialize the global definitions
    ZAGlobal::Initialize(&GetServer(),
                         GetApplicationType(),
                         FALSE,
                         ShowAnimation(),
                         MaximizeFormOnOpen(),
                         GetFileDirectory(),
                         GetEventDirectory());
#endif // _ZDESIGNER // _ZWRITER  // _ZPROCESS

    // Because ZAStyle is in ZUtil and if not defined here, the linker does not include this class
    // and the serialization does not run properly, because the class does not exists.
    ZAStyle* pStyle = new ZAStyle;
    delete pStyle;

#ifndef _WIN32
    // Enable 3d controls
    // Install it after clearing
    // the logo. If problem with the installation
    // the message can appears and he is not
    // hidden by the startup logo.
    Ctl3dRegister(AfxGetInstanceHandle());
    Ctl3dAutoSubclass(AfxGetInstanceHandle());
#endif // Only in 16bit

#ifndef _WIN32
    ClearLogo();
#endif

#ifndef _ZNOSPLASH
    if (m_IDD_Splash != 0)
    {
        // Set the progress
        Splash.SetProgress(100);
    }
#endif

#ifdef _EVALUATION_VERSION

    // Create the class for the security
    ZASecurityCheck SecurityCheck;

    SecurityCheck.Create(szSecurityFilename,
                         100,                                        // Day max
                         2000,                                        // Counter max
                         2,                                        // Counter min
                         GetApplicationRegistryKey(),
                         GetApplicationRegistryProductEntryKey());

    // ********************************************************
    // Uncomment this line if you would like to create a new
    // security file

//    SecurityCheck.CreateSecurityFile();
    // ********************************************************

    BOOL bStop = FALSE;

    // Save the new date
    if (!bStop && !SecurityCheck.SetLastUseDate(CTime::GetCurrentTime()))
    {
        bStop = TRUE;
    }

    // Increment the use counter
    if (!bStop && !SecurityCheck.IncrementCounter())
    {
        bStop = TRUE;
    }

    // Check if the user can continue to use the program
    if (!bStop && !SecurityCheck.Check())
    {
        bStop = TRUE;
    }

    if (bStop)
    {
        SecurityCheck.DisplayStopWnd();

        //Security has been disabled for test purpose
        // rs 10.08.2004
        return FALSE;
        //return TRUE;
    }
#endif

#ifndef _ZNOSPLASH
    // End the splash
    if (m_IDD_Splash != 0)
    {
        Splash.Hide();
    }
#endif

    // Activate the application window
    m_pMainWnd->SetActiveWindow();
    m_pMainWnd->SetForegroundWindow();

    // If we did correctly the first use initialization,
    // advise the user and reset the flag
    if (FirstLoad == _T("1"))
    {
        // Reset parameters in the application's ini file
        AfxGetApp()->WriteProfileString(ApplicationConfigSectionName, szFirstUseEntry, _T("0"));
        AfxGetApp()->WriteProfileString(ApplicationConfigSectionName, szSubDirectoryNameEntry, _T(""));

        ZIMessage Message;
        Message.DisplayMessage(IDS_ONFIRSTUSE_SUCCESS, IDS_ONFIRSTUSE_SUCCESS_TITLE);

        // Saves all new modifed parameters
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();
    }

    if (!PostInitAppl())
    {
        return FALSE;
    }

    // Initialization process is finished
    ZAGlobal::EndInitialization();

    return TRUE;
}

// Cette fonction est appelée lorsque l'instance de l'application doit être fermée.
int ZAMainApp::ExitInstance()
{
#ifndef _WIN32
    Ctl3dUnregister(AfxGetInstanceHandle());
#endif // Only in 16bit

    // No errors
    return(0);
}

// Cette fonction est appelée lorsque le programme est quitté.
BOOL ZAMainApp::ExitAppl()
{
    //## begin ZAMainApp::ExitAppl%912537580.body preserve=yes
    // If the field repository exists, close session properly
    if (GetFieldRepository() != NULL)
    {
        GetFieldRepository()->CloseRepository();
    }

    // Close the existing server session
    GetServer().CloseSession();

    return GetApplicationOptions().SaveOption() | SaveApplicationOptions();
    //## end ZAMainApp::ExitAppl%912537580.body
}

// JMR-MODIF - Le 23 août 2005 - Ajout de la fonction Release pour permettre le nettoyage de la mémoire.
void ZAMainApp::Release()
{
    if (m_FieldRepository != NULL)
    {
        delete m_FieldRepository;
        m_FieldRepository = NULL;
    }
}

// ************************************************** Fichiers **************************************************

CString ZAMainApp::GetApplicationDir() const
{
    HINSTANCE hInstance = AfxGetInstanceHandle();
    CString   appDir;

    if (hInstance != NULL)
    {
        LPTSTR lpszModule = new TCHAR[_MAX_PATH];

        if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
        {
            PSS_File File(lpszModule);
            appDir = ZDirectory::NormalizeDirectory(File.GetFilePath());
        }

        delete[]lpszModule;
    }

    return appDir;
}

#ifdef _ZCHECKINFO
void ZAMainApp::LoadApplicationInfoType()
{
    CString    AppDir = GetApplicationDirectory();

    if (AppDir.IsEmpty())
    {
        return;
    }

    CString    AppInfoFile = AppDir + _T("\\zAppInfo.inf");
    ZBCriptedFileApplicationTypeInfo AppInfo(AppInfoFile);

    m_ApplicationInfoType = AppInfo.LoadApplicationType();
    m_ProductKeyFileInfo = AppInfo.LoadProductKey();
}
#endif

BOOL ZAMainApp::LoadGlobalFieldRepository()
{
    //## begin ZAMainApp::LoadGlobalFieldRepository%910019984.body preserve=yes
    CString CompleteFile = GetGlobalFieldNameRepository();

    if (m_FieldRepository != NULL)
    {
        return m_FieldRepository->OpenRepository(CompleteFile, OpenFieldRepositoryReadOnly());
    }
    else return FALSE;
    //## end ZAMainApp::LoadGlobalFieldRepository%910019984.body
}

void ZAMainApp::EnableShellOpen()
{
    ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

    CString strShortName;
    TCHAR szLongPathName[_MAX_PATH];
    ::GetModuleFileName(m_hInstance, szLongPathName, _MAX_PATH);

    if (::GetShortPathName(szLongPathName, strShortName.GetBuffer(_MAX_PATH), _MAX_PATH) == 0)
    {
        // Rare failure case (especially on not-so-modern file systems)
        strShortName = szLongPathName;
    }

    strShortName.ReleaseBuffer();

    int nPos = strShortName.ReverseFind('\\');

    if (nPos != -1)
    {
        strShortName = strShortName.Right(strShortName.GetLength() - nPos - 1);
    }

    nPos = strShortName.ReverseFind('.');

    if (nPos != -1)
    {
        strShortName = strShortName.Left(nPos);
    }

    m_atomApp = ::GlobalAddAtom(strShortName);
    m_atomSystemTopic = ::GlobalAddAtom(_T("system"));
}

void ZAMainApp::RegisterShellFileTypes(BOOL bCompat /*= FALSE*/)
{
    // bCompat is TRUE for print and drag/drop to printer

    // Register additional template
    RegisterAdditionalTemplateShellFileTypes(bCompat);

    CString strPathName, strTemp;
    AfxGetModuleShortFileName(AfxGetInstanceHandle(), strPathName);

    CString strMustBeRegistered;
    CString strIconIndex;
    CString strFilterExt;
    CString strFileTypeId;
    CString strFileTypeName;

    POSITION pos = GetFirstDocTemplatePosition();

    while (pos != NULL)
    {
        CDocTemplate*    pTemplate = GetNextDocTemplate(pos);
        CString            strOpenCommandLine = strPathName;
        CString            strPrintCommandLine = strPathName;
        CString            strPrintToCommandLine = strPathName;
        CString            strDefaultIconCommandLine = strPathName;

        // Check if the template must be registered
        if (pTemplate->GetDocString(strMustBeRegistered,
            (CDocTemplate::DocStringIndex)_ThisClass::TemplateMustBeRegisteredPosition) &&
            !strMustBeRegistered.IsEmpty())
        {
            // If equal to zero, do not register
            if (atoi(strMustBeRegistered) == 0)
            {
                continue;
            }
        }

        if (pTemplate->GetDocString(strFileTypeId, CDocTemplate::regFileTypeId) && !strFileTypeId.IsEmpty())
        {
            if (bCompat)
            {
                if (pTemplate->GetDocString(strIconIndex,
                    (CDocTemplate::DocStringIndex)_ThisClass::DefaultIconPosition) &&
                    !strIconIndex.IsEmpty())
                {
                    CString strIcon;
                    HICON hIcon = ::ExtractIcon(AfxGetInstanceHandle(), strPathName, atoi(strIconIndex));

                    if (hIcon != NULL)
                    {
                        strIcon.Format(_afxIconIndexFmt, atoi(strIconIndex));
                        DestroyIcon(hIcon);
                    }
                    else
                    {
                        // Otherwise, register with the first icon
                        strIcon.Format(_afxIconIndexFmt, DEFAULT_ICON_INDEX);
                    }

                    strDefaultIconCommandLine += strIcon;
                }
            }

            // enough info to register it
            if (!pTemplate->GetDocString(strFileTypeName, CDocTemplate::regFileTypeName))
            {
                // Use id name
                strFileTypeName = strFileTypeId;
            }

            // No spaces allowed
            ASSERT(strFileTypeId.Find(' ') == -1);

            // first register the type ID of our server
            if (!_zSetRegKey(strFileTypeId, strFileTypeName))
            {
                // Just skip it
                continue;
            }

            if (bCompat)
            {
                // path\DefaultIcon = path,1
                strTemp.Format(_afxDefaultIconFmt, (LPCTSTR)strFileTypeId);

                if (!_zSetRegKey(strTemp, strDefaultIconCommandLine))
                {
                    // Just skip it
                    continue;
                }
            }

            // If MDI Application
            if (!pTemplate->GetDocString(strTemp, CDocTemplate::windowTitle) || strTemp.IsEmpty())
            {
                // path\shell\open\ddeexec = [open("%1")]
                strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                if (!_zSetRegKey(strTemp, _afxDDEOpen))
                {
                    // Just skip it
                    continue;
                }

                if (bCompat)
                {
                    // path\shell\print\ddeexec = [print("%1")]
                    strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                    if (!_zSetRegKey(strTemp, _afxDDEPrint))
                    {
                        // Just skip it
                        continue;
                    }

                    // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                    strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                    if (!_zSetRegKey(strTemp, _afxDDEPrintTo))
                    {
                        // just skip it
                        continue;
                    }

                    // path\shell\open\command = path /dde
                    // path\shell\print\command = path /dde
                    // path\shell\printto\command = path /dde
                    strOpenCommandLine += _afxDDEArg;
                    strPrintCommandLine += _afxDDEArg;
                    strPrintToCommandLine += _afxDDEArg;
                }
                else
                {
                    strOpenCommandLine += _afxOpenArg;
                }
            }
            else
            {
                // path\shell\open\command = path filename
                // path\shell\print\command = path /p filename
                // path\shell\printto\command = path /pt filename printer driver port
                strOpenCommandLine += _afxOpenArg;

                if (bCompat)
                {
                    strPrintCommandLine += _afxPrintArg;
                    strPrintToCommandLine += _afxPrintToArg;
                }
            }

            // path\shell\open\command = path filename
            strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

            if (!_zSetRegKey(strTemp, strOpenCommandLine))
            {
                // Just skip it
                continue;
            }

            if (bCompat)
            {
                // path\shell\print\command = path /p filename
                strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

                if (!_zSetRegKey(strTemp, strPrintCommandLine))
                {
                    // Just skip it
                    continue;
                }

                // path\shell\printto\command = path /pt filename printer driver port
                strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

                if (!_zSetRegKey(strTemp, strPrintToCommandLine))
                {
                    // Just skip it
                    continue;
                }
            }

            pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt);

            if (!strFilterExt.IsEmpty())
            {
                ASSERT(strFilterExt[0] == '.');

                LONG lSize = _MAX_PATH * 2;

                LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT,
                                               strFilterExt,
                                               strTemp.GetBuffer(lSize),
                                               &lSize);

                strTemp.ReleaseBuffer();

                if (lResult != ERROR_SUCCESS || strTemp.IsEmpty() || strTemp == strFileTypeId)
                {
                    // no association for that suffix
                    if (!_zSetRegKey(strFilterExt, strFileTypeId))
                    {
                        continue;
                    }

                    if (bCompat)
                    {
                        strTemp.Format(_afxShellNewFmt, (LPCTSTR)strFilterExt);
                        (void)_zSetRegKey(strTemp, _afxShellNewValue, _afxShellNewValueName);
                    }
                }
            }
        }
    }
}

void ZAMainApp::RegisterAdditionalTemplateShellFileTypes(BOOL bCompat /*= FALSE*/)
{
    CString strPathName;
    CString strTemp;

    AfxGetModuleShortFileName(AfxGetInstanceHandle(), strPathName);

    CString strMustBeRegistered;
    CString strIconIndex;
    CString strFilterExt;
    CString strFileTypeId;
    CString strFileTypeName;

    int Count = GetTemplateNumEntries();

    for (int i = 0; i < Count; ++i)
    {
        _ThisClass::_TemplateMapCollection::_TemplateEntry* pEntry = GetTemplateAt(i);

        if (!pEntry)
        {
            continue;
        }

        CString strOpenCommandLine = strPathName;
        CString strPrintCommandLine = strPathName;
        CString strPrintToCommandLine = strPathName;
        CString strDefaultIconCommandLine = strPathName;

        // Check if the template must be registered
        if (pEntry->GetTemplateString(strMustBeRegistered, _ThisClass::TemplateMustBeRegisteredPosition) &&
            !strMustBeRegistered.IsEmpty())
        {
            // If equal to zero, do not register
            if (atoi(strMustBeRegistered) == 0)
            {
                continue;
            }
        }

        if (pEntry->GetTemplateString(strFileTypeId, _ThisClass::regFileTypeId) && !strFileTypeId.IsEmpty())
        {
            if (bCompat)
            {
                if (pEntry->GetTemplateString(strIconIndex, _ThisClass::DefaultIconPosition) &&
                    !strIconIndex.IsEmpty())
                {
                    CString strIcon;
                    HICON hIcon = ::ExtractIcon(AfxGetInstanceHandle(), strPathName, atoi(strIconIndex));

                    if (hIcon != NULL)
                    {
                        strIcon.Format(_afxIconIndexFmt, atoi(strIconIndex));
                        DestroyIcon(hIcon);
                    }
                    else
                    {
                        // Otherwise, register with the first icon
                        strIcon.Format(_afxIconIndexFmt, DEFAULT_ICON_INDEX);
                    }

                    strDefaultIconCommandLine += strIcon;
                }
            }

            // enough info to register it
            if (!pEntry->GetTemplateString(strFileTypeName, _ThisClass::regFileTypeName))
            {
                // Use id name
                strFileTypeName = strFileTypeId;
            }

            // No spaces allowed
            ASSERT(strFileTypeId.Find(' ') == -1);

            // first register the type ID of our server
            if (!_zSetRegKey(strFileTypeId, strFileTypeName))
            {
                // Just skip it
                continue;
            }

            if (bCompat)
            {
                // path\DefaultIcon = path,1
                strTemp.Format(_afxDefaultIconFmt, (LPCTSTR)strFileTypeId);

                if (!_zSetRegKey(strTemp, strDefaultIconCommandLine))
                {
                    // Just skip it
                    continue;
                }
            }

            // If MDI Application
            if (!pEntry->GetTemplateString(strTemp, _ThisClass::windowTitle) || strTemp.IsEmpty())
            {
                // path\shell\open\ddeexec = [open("%1")]
                strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                if (!_zSetRegKey(strTemp, _afxDDEOpen))
                {
                    // Just skip it
                    continue;
                }

                if (bCompat)
                {
                    // path\shell\print\ddeexec = [print("%1")]
                    strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                    if (!_zSetRegKey(strTemp, _afxDDEPrint))
                    {
                        // Just skip it
                        continue;
                    }

                    // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                    strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxDDEExec);

                    if (!_zSetRegKey(strTemp, _afxDDEPrintTo))
                    {
                        // Just skip it
                        continue;
                    }

                    // path\shell\open\command = path /dde
                    // path\shell\print\command = path /dde
                    // path\shell\printto\command = path /dde
                    strOpenCommandLine += _afxDDEArg;
                    strPrintCommandLine += _afxDDEArg;
                    strPrintToCommandLine += _afxDDEArg;
                }
                else
                {
                    strOpenCommandLine += _afxOpenArg;
                }
            }
            else
            {
                // path\shell\open\command = path filename
                // path\shell\print\command = path /p filename
                // path\shell\printto\command = path /pt filename printer driver port
                strOpenCommandLine += _afxOpenArg;

                if (bCompat)
                {
                    strPrintCommandLine += _afxPrintArg;
                    strPrintToCommandLine += _afxPrintToArg;
                }
            }

            // path\shell\open\command = path filename
            strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

            if (!_zSetRegKey(strTemp, strOpenCommandLine))
            {
                // Just skip it
                continue;
            }

            if (bCompat)
            {
                // path\shell\print\command = path /p filename
                strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

                if (!_zSetRegKey(strTemp, strPrintCommandLine))
                {
                    // Just skip it
                    continue;
                }

                // path\shell\printto\command = path /pt filename printer driver port
                strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId, (LPCTSTR)_afxCommand);

                if (!_zSetRegKey(strTemp, strPrintToCommandLine))
                {
                    // Just skip it
                    continue;
                }
            }

            pEntry->GetTemplateString(strFilterExt, _ThisClass::filterExt);

            if (!strFilterExt.IsEmpty())
            {
                ASSERT(strFilterExt[0] == '.');

                LONG lSize = _MAX_PATH * 2;

                LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT,
                                               strFilterExt,
                                               strTemp.GetBuffer(lSize),
                                               &lSize);

                strTemp.ReleaseBuffer();

                if (lResult != ERROR_SUCCESS || strTemp.IsEmpty() || strTemp == strFileTypeId)
                {
                    // no association for that suffix
                    if (!_zSetRegKey(strFilterExt, strFileTypeId))
                    {
                        continue;
                    }

                    if (bCompat)
                    {
                        strTemp.Format(_afxShellNewFmt, (LPCTSTR)strFilterExt);
                        (void)_zSetRegKey(strTemp, _afxShellNewValue, _afxShellNewValueName);
                    }
                }
            }
        }
    }
}

// prompt for file name - used for open and save as has been rewritten due to the fact I need an initial
// directory for templates.
BOOL ZAMainApp::DoPromptFileName(CString&            fileName,
                                 const CString&    initialDir,
                                 UINT                nIDSTitle,
                                 DWORD                lFlags,
                                 BOOL                bOpenFileDialog,
                                 CDocTemplate*        pTemplate)
{
    // if pTemplate==NULL => all document templates

    CFileDialog dlgFile(bOpenFileDialog);

    CString title;
    VERIFY(title.LoadString(nIDSTitle));

    dlgFile.m_ofn.Flags |= lFlags;

    CString strFilter;
    CString strDefault;

    if (pTemplate != NULL)
    {
        ASSERT_VALID(pTemplate);
        AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
    }
    else
    {
        // do for all doc template
    #ifndef _WIN32
        POSITION pos = m_templateList.GetHeadPosition();
    #else
        POSITION pos = GetFirstDocTemplatePosition();
    #endif
        while (pos != NULL)
        {
        #ifndef _WIN32
            AppendFilterSuffix(strFilter,
                               dlgFile.m_ofn,
                               (CDocTemplate*)m_templateList.GetNext(pos),
                               NULL);
        #else
            AppendFilterSuffix(strFilter,
                               dlgFile.m_ofn,
                               GetNextDocTemplate(pos),
                               NULL);
        #endif
        }
    }

    // Append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += allFilter;
    strFilter += (char)'\0';        // Next string please
    strFilter += _T("*.*");
    strFilter += (char)'\0';        // Last string
    dlgFile.m_ofn.nMaxCustFilter++;

    dlgFile.m_ofn.lpstrFilter = strFilter;
    dlgFile.m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
    dlgFile.m_ofn.lpstrTitle = title;

    // Set the initial directory
    dlgFile.m_ofn.nMaxFile = _MAX_PATH;
    dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
    dlgFile.m_ofn.lpstrInitialDir = initialDir;

    BOOL bRet = dlgFile.DoModal() == IDOK ? TRUE : FALSE;

#ifdef _DEBUG
    if (bRet == FALSE)
    {
        DWORD err = CommDlgExtendedError();
    }
#endif

    fileName.ReleaseBuffer();

    return bRet;
}

void ZAMainApp::AppendFilterSuffix(CString&        filter,
                                   OPENFILENAME&    ofn,
                                   CDocTemplate*    pTemplate,
                                   CString*        pstrDefaultExt)
{
    ASSERT_VALID(pTemplate);
    ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplate)));

    CString strFilterExt;
    CString strFilterName;

    if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
        !strFilterExt.IsEmpty() &&
        pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
        !strFilterName.IsEmpty())
    {
        // A file based document template - add to filter list
        ASSERT(strFilterExt[0] == '.');

        if (pstrDefaultExt != NULL)
        {
            // set the default extension
            *pstrDefaultExt = ((const char*)strFilterExt) + 1;    // skip the '.'
            ofn.lpstrDefExt = (LPSTR)(const char*)(*pstrDefaultExt);
            ofn.nFilterIndex = ofn.nMaxCustFilter + 1;                // 1 based number
        }

        // Add to filter
        filter += strFilterName;
        ASSERT(!filter.IsEmpty());    // must have a file type name
        filter += (char)'\0';            // next string please
        filter += _T("*") + strFilterExt;
        filter += (char)'\0';            // next string please
        ofn.nMaxCustFilter++;
    }
}

void ZAMainApp::TemplateDirectoryHasChanged()
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_TEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetTemplateManager());

    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_FIELDREPOSITORY,
                                              0,
                                              (LPARAM)GetFieldRepository());
}

void ZAMainApp::ProcessTemplateDirectoryHasChanged()
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_PROCESSTEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetTemplateManager());
}

void ZAMainApp::ModelTemplateDirectoryHasChanged()
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZE_MODELTEMPLATEMANAGER,
                                              1, // Show file
                                              (LPARAM)&ZAGlobal::GetModelTemplateManager());
}

// ********************************************* Documents et modèles *******************************************

BOOL ZAMainApp::BuildTemplateName(CString& str, PSS_Stamp& Stamp)
{
    BOOL bCorrectTemplate = FALSE;

    // Check if the template directory is the
    // same that the template file
    if (Stamp.GetTemplate().Left(GetTemplateDirectory().GetLength()) != GetTemplateDirectory())
    {
        bCorrectTemplate = TRUE;

        // Remove the directory from the filename
        char szDrive[_MAX_DRIVE];
        char szDir[_MAX_DIR];
        char szFname[_MAX_FNAME];
        char szExt[_MAX_EXT];

        _splitpath(Stamp.GetTemplate(), szDrive, szDir, szFname, szExt);
        str = GetTemplateDirectory() + _T("\\") + szFname + szExt;
    }
    else str = Stamp.GetTemplate();

    return bCorrectTemplate;
}

void ZAMainApp::RegisterAdditionalTemplate(UINT nIDRes)
{
    RegisterTemplate(nIDRes);
}

CDocument* ZAMainApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
    _TemplateMapCollection::_TemplateEntry* pEntry = GetTemplateEntryByFilename(lpszFileName);
    CDocument* pDoc = NULL;

    if (pEntry)
    {
        pDoc = OnOpenAdditionalTemplateFile(lpszFileName);
    }
    else
    {
        pDoc = CWinApp::OpenDocumentFile(lpszFileName);
    }

    if (pDoc)
    {
        // JMR-MODIF - Le 24 avril 2006 - Ajout du nom du fichier dans la fonction pour le test de la lecture seule.
        OnAfterOpenDocument(pDoc, lpszFileName);
    }

    return pDoc;
}

BOOL ZAMainApp::IsDocumentOpen(const CString Filename)
{
    //## begin ZAMainApp::IsDocumentOpen%928442321.body preserve=yes
    CObList DocList;
    GetDocumentList(DocList);

    // Iterate through the list in head-to-tail order.
    POSITION    pos;
    CDocument*    pDocument;

    for (pos = DocList.GetHeadPosition(); pos != NULL; )
    {
        pDocument = (CDocument*)DocList.GetNext(pos);

        if (pDocument && pDocument->GetPathName() == Filename)
        {
            return TRUE;
        }
    }

    return FALSE;
    //## end ZAMainApp::IsDocumentOpen%928442321.body
}

void ZAMainApp::GetDocumentList(CObList& DocList)
{
    //## begin ZAMainApp::GetDocumentList%928442320.body preserve=yes
#ifdef _WIN32
    ASSERT(DocList.IsEmpty());
    POSITION pos = GetFirstDocTemplatePosition();

    while (pos)
    {
        CDocTemplate*    pTemplate = (CDocTemplate*)GetNextDocTemplate(pos);
        POSITION        pos2 = pTemplate->GetFirstDocPosition();

        while (pos2)
        {
            CDocument* pDocument;

            if ((pDocument = pTemplate->GetNextDoc(pos2)) != NULL)
            {
                DocList.AddHead(pDocument);
            }
        }
    }
#endif
    //## end ZAMainApp::GetDocumentList%928442320.body
}

void ZAMainApp::GetDocumentArrayName(CStringArray& FileArray)
{
#ifdef _WIN32
    // Empty the file array
    FileArray.RemoveAll();

    POSITION pos = GetFirstDocTemplatePosition();

    while (pos)
    {
        CDocTemplate*    pTemplate = (CDocTemplate*)GetNextDocTemplate(pos);
        POSITION        pos2 = pTemplate->GetFirstDocPosition();

        while (pos2)
        {
            CDocument*    pDocument;

            if ((pDocument = pTemplate->GetNextDoc(pos2)) != NULL)
                FileArray.Add(pDocument->GetPathName());
        }
    }
#endif
}

bool ZAMainApp::SaveAllModifiedNoPrompt()
{
    bool bRetValue = true;

    CObList DocList;
    GetDocumentList(DocList);

    // Iterate through the list in head-to-tail order.
    POSITION    pos;
    CDocument*    pDocument;

    for (pos = DocList.GetHeadPosition(); pos != NULL; )
    {
        pDocument = (CDocument*)DocList.GetNext(pos);

        if (pDocument && pDocument->IsModified() == TRUE)
        {
            if (!pDocument->DoFileSave())
            {
                bRetValue = false;
            }
        }
    }

    return bRetValue;
}

// ******************************************* Gestion des utilisateurs *****************************************

BOOL ZAMainApp::LoadAllUsers()
{
    // Load all users
    PSS_UserLoader UserLoader;

    // Load all users
    UserLoader.Create(&ZAGlobal::GetUserManager(), GetUserDefinitionFile());

    return UserLoader.LoadAllUsers();
}

// ************************************* Messages, textes et infos utilisateur **********************************

void ZAMainApp::DisplayWarningOnCommand()
{
#ifdef _EVALUATION_VERSION
    CString sTitle;
    sTitle.LoadString(IDS_WARNINGEVALVER);

    CString sText;
    sText.LoadString(IDS_UNABLECOMMANDEVALVER);

    AfxGetMainWnd()->MessageBox(sText, sTitle);
#endif
}

void ZAMainApp::DisplaySampleText(CDC*                pDC,
                                  const CString&    sValue,
                                  CRect            Rect,
                                  PSS_Font::FontHandle        hFont,
                                  HandleStyle        hStyle)
{
    //## begin ZAMainApp::DisplaySampleText%870643929.body preserve=yes
    PSS_Font* pFont = NULL;

    if (hFont != g_NoFontDefined)
    {
        pFont = GetFontManager().GetFont(hFont);
    }

    ZAStyle* pStyle = NULL;

    if (hStyle != NoStyleDefined)
    {
        pStyle = GetStyleManager().GetStyle(hStyle);
    }

    DisplaySampleText(pDC, sValue, Rect, pFont, pStyle);
    //## end ZAMainApp::DisplaySampleText%870643929.body
}

void ZAMainApp::DisplaySampleText(CDC* pDC, const CString& sValue, CRect Rect, PSS_Font* pFont, ZAStyle* pStyle)
{
    //## begin ZAMainApp::DisplaySampleText%870643928.body preserve=yes
    // Display the appearance of text
    CFont*        OldFont;
    CPen*        OldPen;
    CPen        NewPen(PS_SOLID, 1, defCOLOR_BLACK);
    CPen        ShadowPen(PS_SOLID, 1, defCOLOR_GRAY);
    CBrush*        OldBrush;
    CBrush        NewBrush;
    COLORREF    col;
    UINT        Justify = DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE;

    if (pFont)
    {
        OldFont = pDC->SelectObject(pFont);
        col = pFont->GetFontColor();
        NewBrush.CreateSolidBrush(defCOLOR_WHITE);
    }
    else if (pStyle)
    {
        NewBrush.CreateSolidBrush((pStyle->GetBackColor() != -1) ? pStyle->GetBackColor() : defCOLOR_WHITE);
        PSS_Font* pStyleFont = GetFontManager().GetFont(pStyle->GethFont());

        if (!pStyleFont)
        {
            return;
        }

        OldFont = pDC->SelectObject(pStyleFont);
        col = pStyleFont->GetFontColor();
        Justify = pStyle->GetJustify();
    }
    else return;

    OldPen = pDC->SelectObject(&NewPen);
    OldBrush = pDC->SelectObject(&NewBrush);

    pDC->Rectangle(Rect);
    pDC->MoveTo(Rect.left + 1, Rect.bottom);
    pDC->LineTo(Rect.right + 1, Rect.bottom);
    pDC->MoveTo(Rect.right, Rect.top + 1);
    pDC->LineTo(Rect.right, Rect.bottom + 1);
    pDC->SelectObject(&ShadowPen);
    pDC->MoveTo(Rect.left + 2, Rect.bottom + 1);
    pDC->LineTo(Rect.right + 2, Rect.bottom + 1);
    pDC->MoveTo(Rect.right + 1, Rect.top + 2);
    pDC->LineTo(Rect.right + 1, Rect.bottom + 2);
    pDC->SetTextColor(col);
    pDC->SetBkColor(defCOLOR_WHITE);
    Rect.InflateRect(-2, -2);
    pDC->SetTextAlign(0);
    pDC->SetBkMode(TRANSPARENT);
    pDC->DrawText(sValue, -1, &Rect, Justify);
    pDC->SelectObject(OldFont);
    pDC->SelectObject(OldPen);
    pDC->SelectObject(OldBrush);
    //## end ZAMainApp::DisplaySampleText%870643928.body
}

BOOL ZAMainApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
    // Check to see if the modal dialog box is up
    if (ZAGlobal::GetModalDialogCWnd() != NULL)
    {
        if (lpMsg->hwnd == ZAGlobal::GetModalDialogCWnd()->GetSafeHwnd() ||
            ::IsChild(ZAGlobal::GetModalDialogCWnd()->GetSafeHwnd(), lpMsg->hwnd))
        {
            // Use the global IsChild() function to get
            // messages destined for the dialog's controls
            // Perform customized message processing here
            if (code == MSGF_DIALOGBOX)
            {
                MSG msg = *lpMsg;

                if (ZAGlobal::GetModalDialogCWnd()->IsWindowEnabled() &&
                    ZAGlobal::GetModalDialogCWnd()->PreTranslateMessage(&msg))
                {
                    return TRUE;
                }
            }
        }
    }

    return CWinApp::ProcessMessageFilter(code, lpMsg);
}

// *************************************************** Curseur **************************************************

BOOL ZAMainApp::IsCursorCapturedValid(const CPoint& point, ZIView* pView)
{
    //## begin ZAMainApp::IsCursorCapturedValid%908554843.body preserve=yes
    if (!pView)
    {
        return FALSE;
    }

    BOOL        bCaptureValid = TRUE;
    ZDDocument*    pDoc = pView->GetDocument();

    // No document, not a valid capture
    if (!pDoc)
    {
        return FALSE;
    }

    // Retrieve the window of the special help
    // to check if the cursor is on the window
    PSS_Edit* pEdit = pDoc->GetEditControl();

    if (pEdit)
    {
        if (pEdit->IsWindowVisible())
        {
            CRect EditRect;
            pEdit->GetClientRect(EditRect);
            pView->ClientToDoc(EditRect);

            if (EditRect.PtInRect(point))
            {
                bCaptureValid = FALSE;
            }
        }

        PSS_SpecialHelpWnd* pWnd = pEdit->GetSpecialHelp();

        if (bCaptureValid && pWnd && pWnd->IsWindowVisible())
        {
            CRect HelperRect;
            pWnd->GetClientRect(&HelperRect);
            pWnd->MapWindowPoints(pView, &HelperRect);
            pView->ClientToDoc(HelperRect);

            if (HelperRect.PtInRect(point))
            {
                bCaptureValid = FALSE;
            }
        }
    }

    // Check the cursor is inside the client area
    CRect rect;
    pView->GetClientRect(&rect);
    pView->ClientToDoc(rect);

    if (!rect.PtInRect(point))
    {
        bCaptureValid = FALSE;
    }

    return bCaptureValid;
    //## end ZAMainApp::IsCursorCapturedValid%908554843.body
}

// ******************************************** Fonctions d'impression ******************************************

// JMR-MODIF - Le 14 juillet 2005 - Supprimé les fonctions de modification des paramètres de l'imprimante,
// car ces fonctions sont maintenant gérées ailleurs dans le programme.
/*
// Cette fonction modifie l'orientation du papier par défaut dans les paramètres d'impression.
void ZAMainApp::SetPrinterOrientation( BOOL bInPortrait )
{
#ifdef _WIN32
    // Get default printer settings.
    PRINTDLG pd;

    pd.lStructSize = (DWORD) sizeof( PRINTDLG );

    if (GetPrinterDeviceDefaults( &pd ))
    {
        // Lock memory handle.
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock( m_hDevMode );
        LPDEVNAMES lpDevNames;
        LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE hPrinter;

        if (pDevMode)
        {
            // Change printer settings in here.
            pDevMode->dmOrientation = bInPortrait ? DMORIENT_PORTRAIT : DMORIENT_LANDSCAPE;

            // Unlock memory handle.
            lpDevNames = (LPDEVNAMES)GlobalLock( pd.hDevNames );
            lpszDriverName = (LPTSTR)lpDevNames + lpDevNames->wDriverOffset;
            lpszDeviceName = (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset;
            lpszPortName   = (LPTSTR)lpDevNames + lpDevNames->wOutputOffset;

            OpenPrinter( lpszDeviceName, &hPrinter, NULL );
            DocumentProperties( NULL, hPrinter, lpszDeviceName, pDevMode,
                               pDevMode, DM_IN_BUFFER | DM_OUT_BUFFER );

            // Sync the pDevMode.
            // See SDK help for DocumentProperties for more info.
            ClosePrinter( hPrinter );
            GlobalUnlock( pd.hDevNames );
            GlobalUnlock( m_hDevMode );
        }
    }

#endif // _WIN32
}

// Cette fonction modifie la taille du papier par défaut dans les paramètres d'impression.
void ZAMainApp::SetPrinterPaperSize( short Format )
{
#ifdef _WIN32
    // Get default printer settings.
    PRINTDLG pd;

    pd.lStructSize = (DWORD) sizeof( PRINTDLG );

    if (GetPrinterDeviceDefaults( &pd ))
    {
        // Lock memory handle.
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock( m_hDevMode );
        LPDEVNAMES lpDevNames;
        LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE hPrinter;

        if (pDevMode)
        {
            // Change printer settings in here.
            pDevMode->dmPaperSize = Format;

            // Unlock memory handle.
            lpDevNames = (LPDEVNAMES)GlobalLock( pd.hDevNames );
            lpszDriverName = (LPTSTR)lpDevNames + lpDevNames->wDriverOffset;
            lpszDeviceName = (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset;
            lpszPortName   = (LPTSTR)lpDevNames + lpDevNames->wOutputOffset;

            OpenPrinter( lpszDeviceName, &hPrinter, NULL );
            DocumentProperties( NULL, hPrinter, lpszDeviceName, pDevMode,
                               pDevMode, DM_IN_BUFFER | DM_OUT_BUFFER );

            // Sync the pDevMode.
            // See SDK help for DocumentProperties for more info.
            ClosePrinter( hPrinter );
            GlobalUnlock( pd.hDevNames );
            GlobalUnlock( m_hDevMode );
        }
    }

#endif // _WIN32
}

// Cette fonction modifie les paramètres par défaut pour l'impression.
void ZAMainApp::SetPrinterSettings( short Orientation, short Format )
{
#ifdef _WIN32
    // Get default printer settings.
    PRINTDLG pd;

    pd.lStructSize = (DWORD) sizeof( PRINTDLG );

    if (GetPrinterDeviceDefaults( &pd ))
    {
        // Lock memory handle.
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock( m_hDevMode );
        LPDEVNAMES lpDevNames;
        LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE hPrinter;

        if (pDevMode)
        {
            // Change printer settings in here.
            pDevMode->dmOrientation    = Orientation;
            pDevMode->dmPaperSize    = Format;

            // Unlock memory handle.
            lpDevNames = (LPDEVNAMES)GlobalLock( pd.hDevNames );
            lpszDriverName = (LPTSTR)lpDevNames + lpDevNames->wDriverOffset;
            lpszDeviceName = (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset;
            lpszPortName   = (LPTSTR)lpDevNames + lpDevNames->wOutputOffset;

            OpenPrinter( lpszDeviceName, &hPrinter, NULL );
            DocumentProperties( NULL, hPrinter, lpszDeviceName, pDevMode,
                               pDevMode, DM_IN_BUFFER | DM_OUT_BUFFER );

            // Sync the pDevMode.
            // See SDK help for DocumentProperties for more info.
            ClosePrinter( hPrinter );
            GlobalUnlock( pd.hDevNames );
            GlobalUnlock( m_hDevMode );
        }
    }

#endif // _WIN32
}
*/

// *************************************************** Serveurs *************************************************

BOOL ZAMainApp::ChooseServer()
{
    // save the previous server directory
    const CString prevServerDir = GetServerIniFile();
    const CString iniFile = (IsWorkingLocaly() ? g_LocalIniFileName : g_GlobalIniFileName);

    PSS_SelectServerWizard selectLocalServer(iniFile, IsWorkingLocaly());

    if (selectLocalServer.Execute())
    {
        SetServerIniFile(selectLocalServer.GetIniFile());

        // close the session first
        GetServer().CloseSession();

        // open the new server session
        if (!OpenServerSession())
        {
            // the server cannot be reached
            ZIMessage Message;
            Message.DisplayMessage(IDS_SERVERCANNOTBEOPEN, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }

        // check if the server directory has changed
        if (prevServerDir != GetServerIniFile())
            OnServerChanged();

        CString prompt;
        AfxFormatString1(prompt, IDS_SERVER_CHOOSED, selectLocalServer.GetServerDirectory());

        CString title;
        title.LoadString(IDS_NF_SELECTSERVER_TITLE);

        ZIMessage message;
        message.DisplayMessage(prompt, title);

        // save the new parameters
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();

    #ifndef _ZDESIGNER
        // set the server directory to the registry
        PSS_RegisterSetup registry;

        registry.CreateEntry(HKEY_LOCAL_MACHINE,
                             REGKEY_SCRIPTORROOT,
                             REGKEY_SERVERPATH,
                             ZDirectory::NormalizeDirectory(selectLocalServer.GetServerDirectory()));

        registry.CreateEntry(HKEY_LOCAL_MACHINE, REGKEY_SCRIPTORROOT, REGKEY_SERVERINI, GetServerIniFile());
    #endif

        return TRUE;
    }

    return FALSE;
}

BOOL ZAMainApp::OpenServerSession()
{
    // Open the server session
    switch (GetServer().OpenSession(GetServerIniFile()))
    {
        case _SRV_NOTFOUND:
        {
            // The server cannot be found,
            // asks the user to select another one
            PSS_MsgBox mBox;

            if (mBox.Show(IDS_DEFAULTSERVERCANNOTBEOPEN, MB_YESNO) == IDNO)
            {
                ZIMessage Message;
                Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                return FALSE;
            }

            if (!ChooseServer())
            {
                ZIMessage Message;
                Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                return FALSE;
            }

            break;
        }

        case _SRV_EMPTYSTRUCT:
        case _SRV_MOVED:
        case _SRV_CORRUPTED:
        {
            // Check if we need to force the network connection and
            // if the selection of the server succeed.
            if (ForceNetworkConnection() &&
                GetServer().OpenSessionForceNetwork(GetServerIniFile()) == _SRV_SUCCESS)
            {
                break;
            }

            // JMR-MODIF - Le 15 avril 2007 - Lors de la première utilisation, la boîte de dialogue signalant la
            // modification du référentiel ne doit pas apparaître.
            if (GetApplicationOptions().GetFirstUse() == FALSE)
            {
                PSS_MsgBox mBox;

                if (mBox.Show(IDS_SERVERISEMPTYORMOVED_INIT, MB_YESNO) == IDNO)
                {
                    ZIMessage Message;
                    Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }
            }

            // Initialize the server with default values
            PSS_File file(GetServerIniFile());
            CString ServerIniFile = GetServer().CreateInitialEnvironment(file.GetFilePath());

            // Then asks the server to create an initial environement
            if (ServerIniFile.IsEmpty())
            {
                ZIMessage Message;
                Message.DisplayMessage(IDS_ONSERVEREMPTYINIT_FAIL, IDS_ONSERVEREMPTYINIT_FAIL_TITLE);

                return FALSE;
            }

            // Check if can be opened
            if (GetServer().OpenSession(GetServerIniFile()) != _SRV_SUCCESS)
            {
                // The server cannot be reached
                ZIMessage Message;
                Message.DisplayMessage(IDS_SERVERCANNOTBEOPEN, IDS_NOSERVER_SELECTED_TITLE);

                PSS_MsgBox mBox;

                if (mBox.Show(IDS_DEFAULTSERVERCANNOTBEOPEN, MB_YESNO) == IDNO)
                {
                    ZIMessage Message;
                    Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }

                if (!ChooseServer())
                {
                    ZIMessage Message;
                    Message.DisplayMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }
            }

            break;
        }

        // Server is open with sucess
        case _SRV_SUCCESS:
        {
            // Notify about the server opening
            OnServerHasBeenOpened();
            break;
        }
    }

    return TRUE;
}

// ***************************************************** Aide ***************************************************

void ZAMainApp::WinHelp(DWORD dwData, UINT nCmd)
{
    if (m_HelpFile.IsEmpty())
    {
        return;
    }

    switch (nCmd)
    {
        case HELP_CONTEXT:
        {
            // If it is a help context command, search for the
            // control ID in the array.
            for (DWORD i = 0; i < m_numHelpIDs * 2; i += 2)
            {
                if (aMenuHelpIDs[i] == LOWORD(dwData))
                {
                    i++;  // pass the help context id to HTMLHelp
                    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//                    HtmlHelp ( m_pMainWnd->m_hWnd, m_HelpFile, HH_HELP_CONTEXT, aMenuHelpIDs[i] );
                    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    return;
                }
            }
        }

        default:
        {
            // If the control ID cannot be found,
            // display the default topic.
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//            HtmlHelp( m_pMainWnd->m_hWnd, m_HelpFile, HH_DISPLAY_TOPIC, 0 );
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            break;
        }
    }
}
