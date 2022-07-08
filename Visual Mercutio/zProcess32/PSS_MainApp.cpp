/****************************************************************************
 * ==> PSS_MainApp ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic main application interface              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MainApp.h"

// this was previously required because Visual Mercutio was a commercial product before being open source, but now...
// uncomment the line below to re-enable the product key protection
//#define EVALUATION_VERSION

// uncomment the line below to remove the splash screen on opening
//#define NO_SPLASH

// windows
#ifdef _WIN32
    #include <WinSpool.h>
#endif
#include <ctype.h>
#include <locale.h>
#include <htmlhelp.h>

// processsoft
#include "zBaseLib\PSS_PlanFinObjects.h"
#include "zBaseLib\PSS_PLFNAutoNumbered.h"
#include "zBaseLib\PSS_PLFNBitmap.h"
#include "zBaseLib\PSS_PLFNBoundText.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Edit.h"
#include "zBaseLib\PSS_UserLoader.h"
#include "zBaseLib\PSS_MessageDlg.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_ObjectUtility.h"
#include "zBaseLib\PSS_PaintResources.h"
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_RegisterSetup.h"
#include "zWinUtil32\PSS_SelectServerWizard.h"
#ifdef EVALUATION_VERSION
    #include "zScty\PSS_Security.h"
    #include "zScty\PSS_SecurityCheck.h"
#endif
#include "zSplash\PSS_SplashController.h"
#include "PSS_RegistryDefs.h"
#include "PSS_ZEvent.h"
#include "zHelpContext.h"
#include "planfin.hdf"

// resources
#include "resource.h"
#include "zRes32\zRes.h"

// external functions
extern "C" extern void WINAPI InitZSplResDLL();
extern "C" extern void WINAPI InitZRes32DLL();

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_FirstUseEntry         _T("First Use")
#define M_SubDirectoryNameEntry _T("Ref Sub Directory Name")
#define M_Default_Icon_Index    0
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static const DWORD g_MenuHelpIDs[] =
{
    ID_FILE_NEW,           IDH_FILE_NEW,
    ID_FILE_OPEN,          IDH_FILE_OPEN,
    ID_FILE_SAVE,          IDH_FILE_SAVE,
    ID_EDIT_CUT,           IDH_EDIT_CUT,
    ID_EDIT_COPY,          IDH_EDIT_COPY,
    ID_EDIT_PASTE,         IDH_EDIT_PASTE,
    ID_FILE_PRINT,         IDH_FILE_PRINT,
    ID_APP_ABOUT,          IDH_APP_ABOUT,
    ID_FILE_PRINT_PREVIEW, IDH_FILE_PRINT_PREVIEW,
    0,                     0
};

static char BASED_CODE      g_DefaultIcon[]          = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR g_AfxShellOpenFmt[]      = _T("%s\\shell\\open\\%s");
AFX_STATIC_DATA const TCHAR g_AfxShellPrintFmt[]     = _T("%s\\shell\\print\\%s");
AFX_STATIC_DATA const TCHAR g_AfxShellPrintToFmt[]   = _T("%s\\shell\\printto\\%s");
AFX_STATIC_DATA const TCHAR g_AfxDefaultIconFmt[]    = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR g_AfxShellNewFmt[]       = _T("%s\\ShellNew");
AFX_STATIC_DATA const TCHAR g_AfxIconIndexFmt[]      = _T(",%d");
AFX_STATIC_DATA const TCHAR g_AfxCommand[]           = _T("command");
AFX_STATIC_DATA const TCHAR g_AfxOpenArg[]           = _T(" \"%1\"");
AFX_STATIC_DATA const TCHAR g_AfxPrintArg[]          = _T(" /p \"%1\"");
AFX_STATIC_DATA const TCHAR g_AfxPrintToArg[]        = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const TCHAR g_AfxDDEArg[]            = _T(" /dde");
AFX_STATIC_DATA const TCHAR g_AfxDDEExec[]           = _T("ddeexec");
AFX_STATIC_DATA const TCHAR g_AfxDDEOpen[]           = _T("[open(\"%1\")]");
AFX_STATIC_DATA const TCHAR g_AfxDDEPrint[]          = _T("[print(\"%1\")]");
AFX_STATIC_DATA const TCHAR g_AfxDDEPrintTo[]        = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");
AFX_STATIC_DATA const TCHAR g_AfxShellNewValueName[] = _T("NullFile");
AFX_STATIC_DATA const TCHAR g_AfxShellNewValue[]     = _T("");
//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
/**
* Writes or updates a key/value pair in the registry when the application starts
*@param pKey - the key
*@param pValue - the value
*@param pValueName - the value name
*@return TRUE on success, otherwise FALSE
*/
AFX_STATIC BOOL AFXAPI SetRegKey(LPCTSTR pKey, LPCTSTR pValue, LPCTSTR pValueName = NULL)
{
    if (!pValueName)
    {
        if (::RegSetValue(HKEY_CLASSES_ROOT,
                          pKey,
                          REG_SZ,
                          pValue,
                          lstrlen(pValue) * sizeof(TCHAR)) != ERROR_SUCCESS)
        {
            TRACE1("Warning - registration database update failed for key '%s'.\n", pKey);
            return FALSE;
        }

        return TRUE;
    }
    else
    {
        HKEY hKey;

        if (::RegCreateKey(HKEY_CLASSES_ROOT, pKey, &hKey) == ERROR_SUCCESS)
        {
            const LONG result = ::RegSetValueEx(hKey,
                                                pValueName,
                                                0,
                                                REG_SZ,
                                                (CONST BYTE*)pValue,
                                                (lstrlen(pValue) + 1) * sizeof(TCHAR));

            if (::RegCloseKey(hKey) == ERROR_SUCCESS && result == ERROR_SUCCESS)
                return TRUE;
        }

        TRACE1("Warning: registration database update failed for key '%s'.\n", pKey);
        return FALSE;
    }
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_MainApp, PSS_SingleInstanceApplication)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MainApp, PSS_SingleInstanceApplication)
    //{{AFX_MSG_MAP(PSS_MainApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MainApp
//---------------------------------------------------------------------------
PSS_MainApp::PSS_MainApp() :
    PSS_SingleInstanceApplication(),
    PSS_Subject(),
    PSS_TemplateDocument<PSS_TemplateFunctionNoopAccessor>(),
    m_pCurrentDocument(NULL),
    m_pOldSelectedObj(NULL),
    m_pFieldRepository(NULL),
    m_NumHelpIDs(0),
    m_SplashID(0),
    m_AboutID(0),
    m_SupportID(0)
    #ifdef CHECK_INFO
        ,
        m_ApplicationInfoType(PSS_CryptedFileApplicationTypeInfo::IE_AT_Unknown)
    #endif
{
    PSS_Global::StartInitialization();

    m_pFieldRepository = new PSS_FieldRepository();
}
//---------------------------------------------------------------------------
PSS_MainApp::PSS_MainApp(const PSS_MainApp& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MainApp::~PSS_MainApp()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_MainApp::Release();
}
//---------------------------------------------------------------------------
const PSS_MainApp& PSS_MainApp::operator = (const PSS_MainApp& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::InitInstance()
{
    if (!::AfxOleInit())
    {
        ::AfxMessageBox(_T("Ole Initialization failed"));
        return FALSE;
    }

    // check DDE
    if (!PSS_SingleInstanceApplication::InitInstance())
        return false;

    // force the resource dll to be loaded
    InitZSplResDLL();
    InitZRes32DLL();

    // allow derived class to change the m_pszProfileName variable
    OnChangeWinIniFileName();

    // get the help file name
    m_HelpFile = OnBuildHelpFileName();

    // assign globally the application directory
    PSS_Global::SetApplicationDirectory(GetApplicationDir());

    #ifndef NO_SPLASH
        // start the splash
        PSS_SplashController splash;

        if (m_SplashID)
            splash.Show(m_SplashID, 5);
    #endif

    ::AfxEnableControlContainer();

    // standard initialization. If these featrues aren't used and the
    // final executable size should be reduced, the following init
    // functions may be removed if not required
    #ifdef _AFXDLL
        // called when MFC is linked from a shared DLL
        Enable3dControls();
    #else
        // called when MFC is linked statically
        Enable3dControlsStatic();
    #endif

    // load the standard ini file options (including MRU)
    LoadStdProfileSettings(0);

    #ifdef CHECK_INFO
        // load the application type
        LoadApplicationInfoType();

        if (GetApplicationInfoType() == PSS_CryptedFileApplicationTypeInfo::IE_AT_Unknown)
        {
            #ifndef NO_SPLASH
                // hide the splash
                if (m_SplashID)
                    splash.Hide();
            #endif

            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_APPINFO_MISSING, IDS_APPINFO_MISSING_TITLE);

            return FALSE;
        }

        #ifndef NO_SPLASH
            // set the progress
            if (m_SplashID)
            {
                splash.SetProgress(10);
                splash.SetText(IDS_SPL_LOADOPTIONS);
            }
        #endif
    #endif

    // initialize the application options
    GetApplicationOptions().Create(m_pszProfileName, GetApplicationDir());

    if (!GetApplicationOptions().LoadOption())
        return FALSE;

    if (!LoadApplicationOptions())
    {
        #ifndef NO_SPLASH
            // hide the splash
            if (m_SplashID)
                splash.Hide();
        #endif

        return FALSE;
    }

    #ifdef CHECK_INFO
        // check the product key
        if (GetProductKeyFileInfo() != GetRegisteredProductKey())
        {
            #ifndef NO_SPLASH
                // hide the splash
                if (m_SplashID)
                    splash.Hide();
            #endif

            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_APPINFO_WRONGKEY, IDS_APPINFO_WRONGKEY_TITLE);

            return FALSE;
        }
    #endif

    #ifndef NO_SPLASH
        BYTE pKeyState[256];
        ::GetKeyboardState((LPBYTE)&pKeyState);

        // if the Shift key is pressed, the splash screen isn't visible, so hide it
        if (pKeyState[VK_SHIFT] & 0x80)
            if (m_SplashID)
                splash.Hide();
    #endif

    // initialize the application
    if (!InitApp())
    {
        #ifndef NO_SPLASH
            // hide the splash
            if (m_SplashID)
                splash.Hide();
        #endif

        return FALSE;
    }

    // the main window has been initialized, show and update it
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    CWinApp* pApp = ::AfxGetApp();

    if (!pApp)
        return FALSE;

    // check if first use
    const CString firstLoad = pApp->GetProfileString(ApplicationConfigSectionName, M_FirstUseEntry, _T("0"));

    if (firstLoad == _T("1"))
    {
        const CString subDirectory = pApp->GetProfileString(ApplicationConfigSectionName,
                                                            M_SubDirectoryNameEntry,
                                                            _T(""));

        const CString serverDirectory = PSS_Directory::NormalizeDirectory(GetApplicationDir()) + _T("\\") + subDirectory;
        const CString serverIniFile   = GetServer().CreateInitialEnvironment(serverDirectory);

        // ask the server to create an initial environement
        if (serverIniFile.IsEmpty())
        {
            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_ONFIRSTUSE_FAIL, IDS_ONFIRSTUSE_FAIL_TITLE);

            return FALSE;
        }

        // assign the new server ini file
        SetServerIniFile(serverIniFile);
    }

    if (GetServerIniFile().IsEmpty())
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_NOSERVERDEFINED, MB_YESNO) == IDNO)
        {
            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }

        if (!SelectServer())
        {
            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }
    }

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
        {
            splash.SetProgress(20);
            splash.SetText(IDS_SPL_OPENSERVER);
        }
    #endif

    // if no server session was opened, quit the application
    if (!OpenServerSession())
        return FALSE;

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
        {
            splash.SetProgress(40);
            splash.SetText(IDS_SPL_LOADUSERS);
        }
    #endif

    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return FALSE;

    #ifdef CHECK_INFO
        // only load users for entreprise edition
        if (GetApplicationInfoType() == PSS_CryptedFileApplicationTypeInfo::IE_AT_EntrepriseEdition)
    #endif
            // check if the user file should be loaded
            if (LoadUserFile())
            {
                if (!LoadAllUsers())
                {
                    PSS_MessageDlg messageDlg;
                    messageDlg.ShowMessage(IDS_LOADUSERSFAIL_T, IDS_LOADUSERSFAIL_WT);
                    return FALSE;
                }

                // check if the user should be authenticated
                if (UserAuthenticationRequired())
                {
                    PSS_Global::InitializeNetwork();

                    // not a registered user
                    if (!PSS_Global::GetConnectedUser())
                    {
                        PSS_MessageDlg messageDlg;
                        messageDlg.ShowMessage(IDS_USERNOTREGISTERED_T, IDS_USERNOTREGISTERED_WT);

                        return FALSE;
                    }
                }

                // notify observers about the loaded user manager
                pWnd->SendMessageToDescendants(UM_INITIALIZE_USERMANAGER, 0, LPARAM(&PSS_Global::GetUserManager()));
            }

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
        {
            splash.SetProgress(60);
            splash.SetText(IDS_SPL_LOADTMPL);
        }
    #endif

    // create the template manager
    PSS_Global::GetTemplateManager().Create(GetTemplateDirectory(), PSS_Global::GetFileExtension());

    pWnd->SendMessageToDescendants(UM_INITIALIZE_TEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetTemplateManager()));

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
        {
            splash.SetProgress(70);
            splash.SetText(IDS_SPL_LOADPROCTMPL);
        }
    #endif

    // create the process template manager
    PSS_Global::GetProcessTemplateManager().Create(GetProcessTemplateDirectory(),
                                                   PSS_Global::GetProcessFileExtension());

    pWnd->SendMessageToDescendants(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetTemplateManager()));

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
        {
            splash.SetProgress(80);
            splash.SetText(IDS_SPL_LOADMODELTMPL);
        }
    #endif

    // create the model template manager
    PSS_Global::GetModelTemplateManager().Create(GetModelTemplateDirectory(), PSS_Global::GetModelFileExtension());

    pWnd->SendMessageToDescendants(UM_INITIALIZE_MODELTEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetModelTemplateManager()));

    // enable file manager drag/drop and DDE open execute
    PSS_MainApp::EnableShellOpen();

    // register the additional templates
    OnRegisterAdditionalTemplate();

    // register all the templates
    PSS_MainApp::RegisterShellFileTypes(TRUE);

    m_pMainWnd->DragAcceptFiles();

    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR) || defined(_ZWRITER) || defined(_ZPROCESS)
        #ifndef NO_SPLASH
            // set the progress
            if (m_SplashID)
            {
                splash.SetProgress(90);
                splash.SetText(IDS_SPL_LOADFIELD);
            }
        #endif

        if (!LoadGlobalFieldRepository())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NOGFIELDFILEVALUE, MB_OK);
        }

        pWnd->SendMessageToDescendants(UM_INITIALIZE_FIELDREPOSITORY, 0, LPARAM(GetFieldRepository()));

        // initialize object definition
        PSS_ObjectUtility::InitializeDefinition(GetServer().GetFieldDefinitionIniFile());

        // initialize the painting resources
        PSS_PaintResources::Initialize();

        // initialize the global definitions
        PSS_Global::Initialize(&GetServer(),
                               GetApplicationType(),
                               FALSE,
                               ShowAnimation(),
                               MaximizeFormOnOpen(),
                               GetFileDirectory(),
                               GetEventDirectory());
    #endif

    // because PSS_Style is in zUtil and if not defined here, the linker will not include this class
    // and the serialization may not run properly, because the class does not exists
    std::unique_ptr<PSS_Style> pStyle(new PSS_Style());
    pStyle.reset();

    // only in 16bit
    #ifndef _WIN32
        // enable 3d controls. Install it after clearing the logo. On issue with the installation,
        // the message can appear and it will not be hidden by the startup logo
        ::Ctl3dRegister(::AfxGetInstanceHandle());
        ::Ctl3dAutoSubclass(::AfxGetInstanceHandle());

        ClearLogo();
    #endif

    #ifndef NO_SPLASH
        // set the progress
        if (m_SplashID)
            splash.SetProgress(100);
    #endif

    #ifdef EVALUATION_VERSION
        // create the security check class
        PSS_SecurityCheck securityCheck;

        securityCheck.Create(szSecurityFileName,
                             100,
                             2000,
                             2,
                             GetApplicationRegistryKey(),
                             GetApplicationRegistryProductEntryKey());

        // uncomment this line to create a new security file
        //securityCheck.CreateSecurityFile();

        BOOL stop = FALSE;

        // save the new date
        if (!stop && !securityCheck.SetLastUseDate(CTime::GetCurrentTime()))
            stop = TRUE;

        // increment the use counter
        if (!stop && !securityCheck.IncrementCounter())
            stop = TRUE;

        // check if the user is allowed to continue to use the program
        if (!stop && !securityCheck.Check())
            stop = TRUE;

        if (stop)
        {
            #ifndef NO_SPLASH
                // hide the splash
                if (m_SplashID)
                    splash.Hide();
            #endif

            securityCheck.ShowStopWnd();

            // todo -cCheck -oJean: security was disabled for test purpose
            return FALSE;
            //return TRUE;
        }
    #endif

    #ifndef NO_SPLASH
        // hide the splash
        if (m_SplashID)
            splash.Hide();
    #endif

    // activate the application window
    m_pMainWnd->SetActiveWindow();
    m_pMainWnd->SetForegroundWindow();

    // if the application was initialized correctly, notify the user and reset the flag
    if (firstLoad == _T("1"))
    {
        // reset parameters in the application ini file
        pApp->WriteProfileString(ApplicationConfigSectionName, M_FirstUseEntry,         _T("0"));
        pApp->WriteProfileString(ApplicationConfigSectionName, M_SubDirectoryNameEntry, _T(""));

        PSS_MessageDlg messageDlg;
        messageDlg.ShowMessage(IDS_ONFIRSTUSE_SUCCESS, IDS_ONFIRSTUSE_SUCCESS_TITLE);

        // save all newly modified parameters
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();
    }

    if (!PostInitApp())
        return FALSE;

    // initialization process is terminated
    PSS_Global::EndInitialization();

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_MainApp::ExitInstance()
{
    // only in 16bit
    #ifndef _WIN32
        ::Ctl3dUnregister(::AfxGetInstanceHandle());
    #endif

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ExitApp()
{
    PSS_FieldRepository* pRepository = GetFieldRepository();

    // if the field repository exists, close the session properly
    if (pRepository)
        pRepository->CloseRepository();

    // close the existing server session
    GetServer().CloseSession();

    return GetApplicationOptions().SaveOption() || SaveApplicationOptions();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::SelectServer()
{
    // save the previous server directory
    const CString prevServerDir = GetServerIniFile();
    const CString iniFile       = (IsWorkingLocaly() ? g_LocalIniFileName : g_GlobalIniFileName);

    PSS_SelectServerWizard selectLocalServer(iniFile, IsWorkingLocaly());

    if (selectLocalServer.Execute())
    {
        SetServerIniFile(selectLocalServer.GetIniFile());

        // close the current session
        GetServer().CloseSession();

        // open the new server session
        if (!OpenServerSession())
        {
            // the server cannot be reached
            PSS_MessageDlg messageDlg;
            messageDlg.ShowMessage(IDS_SERVERCANNOTBEOPEN, IDS_NOSERVER_SELECTED_TITLE);

            return FALSE;
        }

        // check if the server directory has changed
        if (prevServerDir != GetServerIniFile())
            OnServerChanged();

        CString prompt;
        AfxFormatString1(prompt, IDS_SERVER_CHOOSED, selectLocalServer.GetServerDirectory());

        CString title;
        title.LoadString(IDS_NF_SELECTSERVER_TITLE);

        PSS_MessageDlg message;
        message.ShowMessage(prompt, title);

        // save the new parameters
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();

        #ifndef _ZDESIGNER
            // set the server directory to the registry
            PSS_RegisterSetup registry;

            registry.CreateEntry(HKEY_LOCAL_MACHINE,
                                 REGKEY_SCRIPTORROOT,
                                 REGKEY_SERVERPATH,
                                 PSS_Directory::NormalizeDirectory(selectLocalServer.GetServerDirectory()));

            registry.CreateEntry(HKEY_LOCAL_MACHINE, REGKEY_SCRIPTORROOT, REGKEY_SERVERINI, GetServerIniFile());
        #endif

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetApplicationDir() const
{
    HINSTANCE hInstance = ::AfxGetInstanceHandle();

    if (!hInstance)
        return _T("");

    LPTSTR  pModule = new TCHAR[_MAX_PATH];
    CString appDir;

    try
    {
        if (::GetModuleFileName(hInstance, pModule, _MAX_PATH))
        {
            PSS_File file(pModule);
            appDir = PSS_Directory::NormalizeDirectory(file.GetFilePath());
        }
    }
    catch (...)
    {
        delete[] pModule;
        throw;
    }

    delete[] pModule;

    return appDir;
}
//---------------------------------------------------------------------------
CDocument* PSS_MainApp::OpenDocumentFile(LPCTSTR pFileName)
{
    if (!pFileName)
        return NULL;

    ITemplateMapCollection::ITemplateEntry* pEntry = GetTemplateEntryByFileName(pFileName);
    CDocument*                              pDoc   = NULL;

    if (pEntry)
        pDoc = OnOpenAdditionalTemplateFile(pFileName);
    else
        pDoc = CWinApp::OpenDocumentFile(pFileName);

    if (pDoc)
        OnAfterOpenDocument(pDoc, pFileName);

    return pDoc;
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::IsDocumentOpen(const CString& fileName)
{
    CObList docList;
    GetDocumentList(docList);

    POSITION   pPos;
    CDocument* pDocument;

    // iterate through the list in head-to-tail order
    for (pPos = docList.GetHeadPosition(); pPos;)
    {
        pDocument = static_cast<CDocument*>(docList.GetNext(pPos));

        // found the matching document?
        if (pDocument && pDocument->GetPathName() == fileName)
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_MainApp::SaveAllModifiedNoPrompt()
{
    CObList docList;
    GetDocumentList(docList);

    POSITION   pPos;
    CDocument* pDocument;
    bool       result = true;

    // iterate through the list in head-to-tail order
    for (pPos = docList.GetHeadPosition(); pPos;)
    {
        pDocument = static_cast<CDocument*>(docList.GetNext(pPos));

        if (pDocument && pDocument->IsModified())
            if (!pDocument->DoFileSave())
                result = false;
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::BuildTemplateName(CString& name, PSS_Stamp& stamp)
{
    BOOL correctTemplate = FALSE;

    // check if the template directory is the same as the template file
    if (stamp.GetTemplate().Left(GetTemplateDirectory().GetLength()) != GetTemplateDirectory())
    {
        correctTemplate = TRUE;

        char drive    [_MAX_DRIVE];
        char dir      [_MAX_DIR];
        char fileName [_MAX_FNAME];
        char extension[_MAX_EXT];

        // remove the directory from the file name
        _splitpath(stamp.GetTemplate(), drive, dir, fileName, extension);
        name = GetTemplateDirectory() + _T("\\") + fileName + extension;
    }
    else
        name = stamp.GetTemplate();

    return correctTemplate;
}
//---------------------------------------------------------------------------
void PSS_MainApp::TemplateDirectoryHasChanged()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    pWnd->SendMessageToDescendants(UM_INITIALIZE_TEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetTemplateManager()));
    pWnd->SendMessageToDescendants(UM_INITIALIZE_FIELDREPOSITORY, 0, LPARAM(GetFieldRepository()));
}
//---------------------------------------------------------------------------
void PSS_MainApp::ProcessTemplateDirectoryHasChanged()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    pWnd->SendMessageToDescendants(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetTemplateManager()));
}
//---------------------------------------------------------------------------
void PSS_MainApp::ModelTemplateDirectoryHasChanged()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    pWnd->SendMessageToDescendants(UM_INITIALIZE_MODELTEMPLATEMANAGER, 1, LPARAM(&PSS_Global::GetModelTemplateManager()));
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ProcessMessageFilter(int code, LPMSG pMsg)
{
    CWnd* pModalDialogWnd = PSS_Global::GetModalDialogCWnd();

    // check if the modal dialog box is up
    if (pModalDialogWnd)
        if (pMsg && (pMsg->hwnd == pModalDialogWnd->GetSafeHwnd() || ::IsChild(pModalDialogWnd->GetSafeHwnd(), pMsg->hwnd)))
        {
            // use the global IsChild() function to get messages destined for the dialog controls.
            // Perform customized message processing here
            if (code == MSGF_DIALOGBOX)
            {
                MSG msg = *pMsg;

                if (pModalDialogWnd->IsWindowEnabled() && pModalDialogWnd->PreTranslateMessage(&msg))
                    return TRUE;
            }
        }

    return CWinApp::ProcessMessageFilter(code, pMsg);
}
//---------------------------------------------------------------------------
void PSS_MainApp::DrawSampleText(CDC*              pDC,
                                 const CString&    value,
                                 const CRect&      rect,
                                 PSS_Font::Handle  hFont,
                                 PSS_Style::Handle hStyle)
{
    if (!pDC)
        return;

    PSS_Font* pFont = NULL;

    if (hFont != g_NoFontDefined)
        pFont = GetFontManager().GetFont(hFont);

    PSS_Style* pStyle = NULL;

    if (hStyle != g_NoStyleDefined)
        pStyle = GetStyleManager().GetStyle(hStyle);

    DrawSampleText(pDC, value, rect, pFont, pStyle);
}
//---------------------------------------------------------------------------
void PSS_MainApp::DrawSampleText(CDC* pDC, const CString& value, const CRect& rect, PSS_Font* pFont, PSS_Style* pStyle)
{
    CFont*   pOldFont;
    CBrush   newBrush;
    COLORREF col;
    UINT     justify = DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE;

    // configure the text to be drawn
    if (pFont)
    {
        pOldFont = pDC->SelectObject(pFont);
        col      = pFont->GetFontColor();
        newBrush.CreateSolidBrush(defCOLOR_WHITE);
    }
    else
    if (pStyle)
    {
        newBrush.CreateSolidBrush((pStyle->GetBackColor() != -1) ? pStyle->GetBackColor() : defCOLOR_WHITE);

        PSS_Font* pStyleFont = GetFontManager().GetFont(pStyle->GetFontHandle());

        if (!pStyleFont)
            return;

        pOldFont = pDC->SelectObject(pStyleFont);
        col      = pStyleFont->GetFontColor();
        justify  = pStyle->GetJustify();
    }
    else
        return;

    CPen newPen   (PS_SOLID, 1, defCOLOR_BLACK);
    CPen shadowPen(PS_SOLID, 1, defCOLOR_GRAY);

    CPen*   pOldPen   = pDC->SelectObject(&newPen);
    CBrush* pOldBrush = pDC->SelectObject(&newBrush);

    CRect textRect = rect;
    textRect.InflateRect(-2, -2);

    // draw the text
    pDC->Rectangle(rect);
    pDC->MoveTo(rect.left  + 1, rect.bottom);
    pDC->LineTo(rect.right + 1, rect.bottom);
    pDC->MoveTo(rect.right,     rect.top    + 1);
    pDC->LineTo(rect.right,     rect.bottom + 1);
    pDC->SelectObject(&shadowPen);
    pDC->MoveTo(rect.left  + 2, rect.bottom + 1);
    pDC->LineTo(rect.right + 2, rect.bottom + 1);
    pDC->MoveTo(rect.right + 1, rect.top    + 2);
    pDC->LineTo(rect.right + 1, rect.bottom + 2);
    pDC->SetTextColor(col);
    pDC->SetBkColor(defCOLOR_WHITE);
    pDC->SetTextAlign(0);
    pDC->SetBkMode(TRANSPARENT);
    pDC->DrawText(value, -1, &textRect, justify);

    // restore the previous gdi state
    pDC->SelectObject(pOldFont);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::IsCapturedCursorValid(const CPoint& point, PSS_View* pView)
{
    if (!pView)
        return FALSE;

    PSS_Document* pDoc = pView->GetDocument();

    // no document, not a valid capture
    if (!pDoc)
        return FALSE;

    BOOL captureValid = TRUE;

    // get the special help window to check if the cursor is on it
    PSS_Edit* pEdit = pDoc->GetEditControl();

    if (pEdit)
    {
        if (pEdit->IsWindowVisible())
        {
            CRect editRect;
            pEdit->GetClientRect(editRect);
            pView->ClientToDoc(editRect);

            if (editRect.PtInRect(point))
                captureValid = FALSE;
        }

        PSS_SpecialHelpWnd* pWnd = pEdit->GetSpecialHelp();

        if (captureValid && pWnd && pWnd->IsWindowVisible())
        {
            CRect helperRect;
            pWnd->GetClientRect(&helperRect);
            pWnd->MapWindowPoints(pView, &helperRect);
            pView->ClientToDoc(helperRect);

            if (helperRect.PtInRect(point))
                captureValid = FALSE;
        }
    }

    // check the cursor is inside the client area
    CRect rect;
    pView->GetClientRect(&rect);
    pView->ClientToDoc(rect);

    if (!rect.PtInRect(point))
        captureValid = FALSE;

    return captureValid;
}
//---------------------------------------------------------------------------
void PSS_MainApp::GetDocumentList(CObList& docList) const
{
    #ifdef _WIN32
        PSS_Assert(docList.IsEmpty());
        POSITION pPos = GetFirstDocTemplatePosition();

        while (pPos)
        {
            CDocTemplate* pTemplate = GetNextDocTemplate(pPos);
            POSITION      pDocPos   = pTemplate->GetFirstDocPosition();

            while (pDocPos)
            {
                CDocument* pDocument;

                if ((pDocument = pTemplate->GetNextDoc(pDocPos)) != NULL)
                    docList.AddHead(pDocument);
            }
        }
    #endif
}
//---------------------------------------------------------------------------
void PSS_MainApp::GetDocumentArrayName(CStringArray& fileArray)
{
    #ifdef _WIN32
        // empty the file array
        fileArray.RemoveAll();

        POSITION pPos = GetFirstDocTemplatePosition();

        while (pPos)
        {
            CDocTemplate* pTemplate = GetNextDocTemplate(pPos);
            POSITION      pDocPos   = pTemplate->GetFirstDocPosition();

            while (pDocPos)
            {
                CDocument* pDocument;

                if ((pDocument = pTemplate->GetNextDoc(pDocPos)) != NULL)
                    fileArray.Add(pDocument->GetPathName());
            }
        }
    #endif
}
//---------------------------------------------------------------------------
/*
void PSS_MainApp::WinHelp(DWORD data, UINT cmd)
{
    if (m_HelpFile.IsEmpty())
        return;

    switch (cmd)
    {
        case HELP_CONTEXT:
            // if it's a help context command, search for the control ID in the array
            for (DWORD i = 0; i < m_NumHelpIDs * 2; i += 2)
                if (g_MenuHelpIDs[i] == LOWORD(data))
                {
                    // pass the help context id to HTMLHelp
                    ++i;

                    // todo FIXME -cBug -oJean: This no longer works with Visual Studio 2017. Find why and fix
                    //HtmlHelp(m_pMainWnd->m_hWnd, m_HelpFile, HH_HELP_CONTEXT, aMenuHelpIDs[i]);
                    return;
                }

        default:
            // todo FIXME -cBug -oJean: This no longer works with Visual Studio 2017. Find why and fix
            // if the control ID cannot be found, show the default topic
            //HtmlHelp(m_pMainWnd->m_hWnd, m_HelpFile, HH_DISPLAY_TOPIC, 0);
            break;
    }
}
*/
//---------------------------------------------------------------------------
void PSS_MainApp::ShowWarningOnCommand()
{
    #ifdef EVALUATION_VERSION
        CWnd* pWnd = ::AfxGetMainWnd();

        if (!pWnd)
            return;

        CString title;
        title.LoadString(IDS_WARNINGEVALVER);

        CString text;
        text.LoadString(IDS_UNABLECOMMANDEVALVER);

        pWnd->MessageBox(text, title);
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    BOOL result = CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

    if (result)
        return TRUE;

    if (m_pDocManager)
    {
        POSITION pPos = m_pDocManager->GetFirstDocTemplatePosition();

        while (pPos)
        {
            CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pPos);
            ASSERT_KINDOF(CDocTemplate, pTemplate);

            PSS_DocTemplateEx* pTemplateEx = dynamic_cast<PSS_DocTemplateEx*>(pTemplate);

            if (pTemplateEx)
                if ((nID >= pTemplateEx->GetMenuID()) && (nID <= pTemplateEx->GetMenuID() + M_MRU_RANGE))
                    result |= pTemplate->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_MainApp::OnChangeWinIniFileName()
{}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::InitApp()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::PostInitApp()
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MainApp::Release()
{
    if (m_pFieldRepository)
    {
        delete m_pFieldRepository;
        m_pFieldRepository = NULL;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::OpenServerSession()
{
    // open the server session
    switch (GetServer().OpenSession(GetServerIniFile()))
    {
        case M_Srv_NotFound:
        {
            // the server cannot be found, ask the user to select another one
            PSS_MsgBox mBox;

            if (mBox.Show(IDS_DEFAULTSERVERCANNOTBEOPEN, MB_YESNO) == IDNO)
            {
                PSS_MessageDlg message;
                message.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                return FALSE;
            }

            if (!SelectServer())
            {
                PSS_MessageDlg message;
                message.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                return FALSE;
            }

            break;
        }

        case M_Srv_EmptyStruct:
        case M_Srv_Moved:
        case M_Srv_Corrupted:
        {
            // check if the network connection should be forced and if the server selection succeeded
            if (ForceNetworkConnection() && GetServer().OpenSessionForceNetwork(GetServerIniFile()) == M_Srv_Success)
                break;

            // on the first use the do modify the referential dialog bog shouldn't appear
            if (!GetApplicationOptions().GetFirstUse())
            {
                PSS_MsgBox mBox;

                if (mBox.Show(IDS_SERVERISEMPTYORMOVED_INIT, MB_YESNO) == IDNO)
                {
                    PSS_MessageDlg message;
                    message.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }
            }

            // initialize the server with default values
            PSS_File      file(GetServerIniFile());
            const CString serverIniFile = GetServer().CreateInitialEnvironment(file.GetFilePath());

            // ask the server to create an initial environment
            if (serverIniFile.IsEmpty())
            {
                PSS_MessageDlg message;
                message.ShowMessage(IDS_ONSERVEREMPTYINIT_FAIL, IDS_ONSERVEREMPTYINIT_FAIL_TITLE);

                return FALSE;
            }

            // check if can be opened
            if (GetServer().OpenSession(GetServerIniFile()) != M_Srv_Success)
            {
                // the server cannot be reached
                PSS_MessageDlg messageDlg;
                messageDlg.ShowMessage(IDS_SERVERCANNOTBEOPEN, IDS_NOSERVER_SELECTED_TITLE);

                PSS_MsgBox mBox;

                if (mBox.Show(IDS_DEFAULTSERVERCANNOTBEOPEN, MB_YESNO) == IDNO)
                {
                    PSS_MessageDlg messageDlg;
                    messageDlg.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }

                if (!SelectServer())
                {
                    PSS_MessageDlg messageDlg;
                    messageDlg.ShowMessage(IDS_NOSERVER_SELECTED, IDS_NOSERVER_SELECTED_TITLE);

                    return FALSE;
                }
            }

            break;
        }

        case M_Srv_Success:
            // server was opened with success
            OnServerHasBeenOpened();
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_MainApp::RegisterAdditionalTemplate(UINT resID)
{
    RegisterTemplate(resID);
}
//---------------------------------------------------------------------------
void PSS_MainApp::RegisterAdditionalTemplateShellFileTypes(BOOL compat)
{
    HINSTANCE hInstance = ::AfxGetInstanceHandle();

    if (!hInstance)
        return;

    CString pathName;
    ::AfxGetModuleShortFileName(hInstance, pathName);

    CString   tempStr;
    CString   mustBeRegistered;
    CString   iconIndex;
    CString   filterExt;
    CString   fileTypeId;
    CString   fileTypeName;
    const int count = GetTemplateCount();

    for (int i = 0; i < count; ++i)
    {
        IClassInfo::ITemplateMapCollection::ITemplateEntry* pEntry = GetTemplateAt(i);

        if (!pEntry)
            continue;

        CString openCommandLine        = pathName;
        CString printCommandLine       = pathName;
        CString printToCommandLine     = pathName;
        CString defaultIconCommandLine = pathName;

        // check if the template must be registered
        if (pEntry->GetTemplateString(mustBeRegistered, (int)IClassInfo::IEStringIndex::IE_SI_TemplateMustBeRegisteredPosition) &&
            !mustBeRegistered.IsEmpty())
            // if equal to zero, do not register
            if (!std::atoi(mustBeRegistered))
                continue;

        if (pEntry->GetTemplateString(fileTypeId, (int)IClassInfo::IEStringIndex::IE_SI_RegFileTypeId) && !fileTypeId.IsEmpty())
        {
            if (compat)
                if (pEntry->GetTemplateString(iconIndex, (int)IClassInfo::IEStringIndex::IE_SI_DefaultIconPosition) && !iconIndex.IsEmpty())
                {
                    const int index = std::atoi(iconIndex);
                    HICON     hIcon = ::ExtractIcon(hInstance, pathName, index);
                    CString   icon;

                    if (hIcon)
                    {
                        icon.Format(g_AfxIconIndexFmt, index);
                        ::DestroyIcon(hIcon);
                    }
                    else
                        // register with the first available icon
                        icon.Format(g_AfxIconIndexFmt, M_Default_Icon_Index);

                    defaultIconCommandLine += icon;
                }

            // enough info to register it?
            if (!pEntry->GetTemplateString(fileTypeName, (int)IClassInfo::IEStringIndex::IE_SI_RegFileTypeName))
                // use id name
                fileTypeName = fileTypeId;

            // no spaces allowed
            PSS_Assert(fileTypeId.Find(' ') == -1);

            // register the server type ID
            if (!SetRegKey(fileTypeId, fileTypeName))
                continue;

            if (compat)
            {
                // path\defaultIcon = path, 1
                tempStr.Format(g_AfxDefaultIconFmt, LPCTSTR(fileTypeId));

                if (!SetRegKey(tempStr, defaultIconCommandLine))
                    continue;
            }

            // if MDI application
            if (!pEntry->GetTemplateString(tempStr, (int)IClassInfo::IEStringIndex::IE_SI_WindowTitle) || tempStr.IsEmpty())
            {
                // path\shell\open\ddeexec = [open("%1")]
                tempStr.Format(g_AfxShellOpenFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                if (!SetRegKey(tempStr, g_AfxDDEOpen))
                    continue;

                if (compat)
                {
                    // path\shell\print\ddeexec = [print("%1")]
                    tempStr.Format(g_AfxShellPrintFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                    if (!SetRegKey(tempStr, g_AfxDDEPrint))
                        continue;

                    // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                    tempStr.Format(g_AfxShellPrintToFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                    if (!SetRegKey(tempStr, g_AfxDDEPrintTo))
                        continue;

                    // path\shell\open\command    = path /dde
                    // path\shell\print\command   = path /dde
                    // path\shell\printto\command = path /dde
                    openCommandLine    += g_AfxDDEArg;
                    printCommandLine   += g_AfxDDEArg;
                    printToCommandLine += g_AfxDDEArg;
                }
                else
                    openCommandLine += g_AfxOpenArg;
            }
            else
            {
                // path\shell\open\command    = path filename
                // path\shell\print\command   = path /p filename
                // path\shell\printto\command = path /pt filename printer driver port
                openCommandLine += g_AfxOpenArg;

                if (compat)
                {
                    printCommandLine   += g_AfxPrintArg;
                    printToCommandLine += g_AfxPrintToArg;
                }
            }

            // path\shell\open\command = path filename
            tempStr.Format(g_AfxShellOpenFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

            if (!SetRegKey(tempStr, openCommandLine))
                continue;

            if (compat)
            {
                // path\shell\print\command = path /p filename
                tempStr.Format(g_AfxShellPrintFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

                if (!SetRegKey(tempStr, printCommandLine))
                    continue;

                // path\shell\printto\command = path /pt filename printer driver port
                tempStr.Format(g_AfxShellPrintToFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

                if (!SetRegKey(tempStr, printToCommandLine))
                    continue;
            }

            pEntry->GetTemplateString(filterExt, (int)IClassInfo::IEStringIndex::IE_SI_FilterExt);

            if (!filterExt.IsEmpty())
            {
                PSS_Assert(filterExt[0] == '.');

                LONG       size   = _MAX_PATH * 2;
                const LONG result = ::RegQueryValue(HKEY_CLASSES_ROOT, filterExt, tempStr.GetBuffer(size), &size);

                tempStr.ReleaseBuffer();

                if (result != ERROR_SUCCESS || tempStr.IsEmpty() || tempStr == fileTypeId)
                {
                    // no association for that suffix
                    if (!SetRegKey(filterExt, fileTypeId))
                        continue;

                    if (compat)
                    {
                        tempStr.Format(g_AfxShellNewFmt, LPCTSTR(filterExt));
                        (void)SetRegKey(tempStr, g_AfxShellNewValue, g_AfxShellNewValueName);
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MainApp::RegisterShellFileTypes(BOOL compat)
{
    HINSTANCE hInstance = ::AfxGetInstanceHandle();

    if (!hInstance)
        return;

    // register additional template
    RegisterAdditionalTemplateShellFileTypes(compat);

    CString pathName;
    ::AfxGetModuleShortFileName(hInstance, pathName);

    CString  tempStr;
    CString  mustBeRegistered;
    CString  iconIndex;
    CString  filterExt;
    CString  fileTypeId;
    CString  fileTypeName;
    POSITION pPos = GetFirstDocTemplatePosition();

    while (pPos)
    {
        CDocTemplate* pTemplate              = GetNextDocTemplate(pPos);
        CString       openCommandLine        = pathName;
        CString       printCommandLine       = pathName;
        CString       printToCommandLine     = pathName;
        CString       defaultIconCommandLine = pathName;

        // check if the template must be registered
        if (pTemplate->GetDocString(mustBeRegistered,
                                    CDocTemplate::DocStringIndex(IClassInfo::IEStringIndex::IE_SI_TemplateMustBeRegisteredPosition)) &&
            !mustBeRegistered.IsEmpty())
            // if equal to zero, do not register
            if (!std::atoi(mustBeRegistered))
                continue;

        if (pTemplate->GetDocString(fileTypeId, CDocTemplate::regFileTypeId) && !fileTypeId.IsEmpty())
        {
            if (compat)
            {
                if (pTemplate->GetDocString(iconIndex,
                                            CDocTemplate::DocStringIndex(IClassInfo::IEStringIndex::IE_SI_DefaultIconPosition)) &&
                    !iconIndex.IsEmpty())
                {
                    const int index = std::atoi(iconIndex);
                    HICON     hIcon = ::ExtractIcon(hInstance, pathName, index);
                    CString   icon;

                    if (hIcon)
                    {
                        icon.Format(g_AfxIconIndexFmt, index);
                        DestroyIcon(hIcon);
                    }
                    else
                        // register with the first icon
                        icon.Format(g_AfxIconIndexFmt, M_Default_Icon_Index);

                    defaultIconCommandLine += icon;
                }
            }

            // enough info to register it
            if (!pTemplate->GetDocString(fileTypeName, CDocTemplate::regFileTypeName))
                // use id name
                fileTypeName = fileTypeId;

            // no spaces allowed
            PSS_Assert(fileTypeId.Find(' ') == -1);

            // register the server type ID
            if (!SetRegKey(fileTypeId, fileTypeName))
                continue;

            if (compat)
            {
                // path\defaultIcon = path, 1
                tempStr.Format(g_AfxDefaultIconFmt, LPCTSTR(fileTypeId));

                if (!SetRegKey(tempStr, defaultIconCommandLine))
                    continue;
            }

            // if MDI application
            if (!pTemplate->GetDocString(tempStr, CDocTemplate::windowTitle) || tempStr.IsEmpty())
            {
                // path\shell\open\ddeexec = [open("%1")]
                tempStr.Format(g_AfxShellOpenFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                if (!SetRegKey(tempStr, g_AfxDDEOpen))
                    continue;

                if (compat)
                {
                    // path\shell\print\ddeexec = [print("%1")]
                    tempStr.Format(g_AfxShellPrintFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                    if (!SetRegKey(tempStr, g_AfxDDEPrint))
                        continue;

                    // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
                    tempStr.Format(g_AfxShellPrintToFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxDDEExec));

                    if (!SetRegKey(tempStr, g_AfxDDEPrintTo))
                        continue;

                    // path\shell\open\command    = path /dde
                    // path\shell\print\command   = path /dde
                    // path\shell\printto\command = path /dde
                    openCommandLine    += g_AfxDDEArg;
                    printCommandLine   += g_AfxDDEArg;
                    printToCommandLine += g_AfxDDEArg;
                }
                else
                    openCommandLine += g_AfxOpenArg;
            }
            else
            {
                // path\shell\open\command    = path filename
                // path\shell\print\command   = path /p filename
                // path\shell\printto\command = path /pt filename printer driver port
                openCommandLine += g_AfxOpenArg;

                if (compat)
                {
                    printCommandLine   += g_AfxPrintArg;
                    printToCommandLine += g_AfxPrintToArg;
                }
            }

            // path\shell\open\command = path filename
            tempStr.Format(g_AfxShellOpenFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

            if (!SetRegKey(tempStr, openCommandLine))
                continue;

            if (compat)
            {
                // path\shell\print\command = path /p filename
                tempStr.Format(g_AfxShellPrintFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

                if (!SetRegKey(tempStr, printCommandLine))
                    continue;

                // path\shell\printto\command = path /pt filename printer driver port
                tempStr.Format(g_AfxShellPrintToFmt, LPCTSTR(fileTypeId), LPCTSTR(g_AfxCommand));

                if (!SetRegKey(tempStr, printToCommandLine))
                    continue;
            }

            pTemplate->GetDocString(filterExt, CDocTemplate::filterExt);

            if (!filterExt.IsEmpty())
            {
                PSS_Assert(filterExt[0] == '.');

                LONG       size   = _MAX_PATH * 2;
                const LONG result = ::RegQueryValue(HKEY_CLASSES_ROOT, filterExt, tempStr.GetBuffer(size), &size);

                tempStr.ReleaseBuffer();

                if (result != ERROR_SUCCESS || tempStr.IsEmpty() || tempStr == fileTypeId)
                {
                    // no association for that suffix
                    if (!SetRegKey(filterExt, fileTypeId))
                        continue;

                    if (compat)
                    {
                        tempStr.Format(g_AfxShellNewFmt, LPCTSTR(filterExt));
                        (void)SetRegKey(tempStr, g_AfxShellNewValue, g_AfxShellNewValueName);
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MainApp::EnableShellOpen()
{
    PSS_Assert(!m_atomApp && !m_atomSystemTopic);

    TCHAR longPathName[_MAX_PATH];
    ::GetModuleFileName(m_hInstance, longPathName, _MAX_PATH);

    CString shortName;

    if (!::GetShortPathName(longPathName, shortName.GetBuffer(_MAX_PATH), _MAX_PATH))
        // rare failure case (especially on not-so-modern file systems)
        shortName = longPathName;

    shortName.ReleaseBuffer();

    int pos = shortName.ReverseFind('\\');

    if (pos != -1)
        shortName = shortName.Right(shortName.GetLength() - pos - 1);

    pos = shortName.ReverseFind('.');

    if (pos != -1)
        shortName = shortName.Left(pos);

    m_atomApp         = ::GlobalAddAtom(shortName);
    m_atomSystemTopic = ::GlobalAddAtom(_T("system"));
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::LoadAllUsers()
{
    // load all users
    PSS_UserLoader userLoader;
    userLoader.Create(&PSS_Global::GetUserManager(), GetUserDefinitionFile());

    return userLoader.LoadAllUsers();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::DoPromptFileName(const CString& fileName,
                                   const CString& initialDir,
                                   UINT           titleID,
                                   DWORD          flags,
                                   BOOL           openFileDialog,
                                   CDocTemplate*  pTemplate)
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return FALSE;

    CFileDialog dlgFile(openFileDialog);

    CString title;
    VERIFY(title.LoadString(titleID));

    dlgFile.m_ofn.Flags |= flags;

    CString filter;
    CString defaultExt;

    if (pTemplate)
    {
        ASSERT_VALID(pTemplate);
        AppendFilterSuffix(filter, dlgFile.m_ofn, pTemplate, &defaultExt);
    }
    else
    {
        // do for all the doc template
        #ifndef _WIN32
            POSITION pPos = m_templateList.GetHeadPosition();
        #else
            POSITION pPos = GetFirstDocTemplatePosition();
        #endif

        while (pPos)
            #ifndef _WIN32
                AppendFilterSuffix(filter, dlgFile.m_ofn, (CDocTemplate*)m_templateList.GetNext(pPos), NULL);
            #else
                AppendFilterSuffix(filter, dlgFile.m_ofn, GetNextDocTemplate(pPos), NULL);
            #endif
    }

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';
    dlgFile.m_ofn.nMaxCustFilter++;

    dlgFile.m_ofn.lpstrFilter = filter;
    dlgFile.m_ofn.hwndOwner   = pWnd->GetSafeHwnd();
    dlgFile.m_ofn.lpstrTitle  = title;

    CString initialDirName = fileName;

    // set the initial directory
    dlgFile.m_ofn.nMaxFile        = _MAX_PATH;
    dlgFile.m_ofn.lpstrFile       = initialDirName.GetBuffer(_MAX_PATH);
    dlgFile.m_ofn.lpstrInitialDir = initialDir;

    const BOOL result = dlgFile.DoModal() == IDOK ? TRUE : FALSE;

    #ifdef _DEBUG
        if (!result)
            DWORD error = ::CommDlgExtendedError();
    #endif

    initialDirName.ReleaseBuffer();

    return result;
}
//---------------------------------------------------------------------------
void PSS_MainApp::AppendFilterSuffix(CString& filter, OPENFILENAME& ofn, CDocTemplate* pTemplate, CString* pDefaultExt)
{
    ASSERT_VALID(pTemplate);

    CString filterExt;
    CString filterName;

    if (pTemplate->GetDocString(filterExt, CDocTemplate::filterExt)   &&
        !filterExt.IsEmpty()                                          &&
        pTemplate->GetDocString(filterName, CDocTemplate::filterName) &&
        !filterName.IsEmpty())
    {
        // a file based document template, add it to filter list
        PSS_Assert(filterExt[0] == '.');

        if (pDefaultExt)
        {
            // set the default extension. NOTE skip the '.'
            *pDefaultExt      = ((const char*)filterExt) + 1;
             ofn.lpstrDefExt  = LPSTR((const char*)(*pDefaultExt));
             ofn.nFilterIndex = ofn.nMaxCustFilter + 1;
        }

        // add to filter. NOTE must have a file type name
        filter += filterName;
        PSS_Assert(!filter.IsEmpty());
        filter += (char)'\0';
        filter += _T("*") + filterExt;
        filter += (char)'\0';
        ++ofn.nMaxCustFilter;
    }
}
//---------------------------------------------------------------------------
void PSS_MainApp::OnServerChanged()
{
    TemplateDirectoryHasChanged();
    ProcessTemplateDirectoryHasChanged();
    ModelTemplateDirectoryHasChanged();
}
//---------------------------------------------------------------------------
void PSS_MainApp::OnServerHasBeenOpened()
{}
//---------------------------------------------------------------------------
bool PSS_MainApp::OnRegisterAdditionalTemplate()
{
    return true;
}
//---------------------------------------------------------------------------
CDocument* PSS_MainApp::OnOpenAdditionalTemplateFile(LPCSTR pFileName)
{
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_MainApp::OnSaveAdditionalTemplateFile(LPCSTR pFileName)
{}
//---------------------------------------------------------------------------
void PSS_MainApp::OnAfterOpenDocument(CDocument* pDoc, const CString& fileName)
{}
//---------------------------------------------------------------------------
void PSS_MainApp::OnAfterSaveDocument(CDocument* pDoc)
{}
//---------------------------------------------------------------------------
CString PSS_MainApp::OnBuildHelpFileName()
{
    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::LoadGlobalFieldRepository()
{
    if (!m_pFieldRepository)
        return FALSE;

    return m_pFieldRepository->OpenRepository(GetGlobalFieldNameRepository(), OpenFieldRepositoryReadOnly());
}
//---------------------------------------------------------------------------
#ifdef CHECK_INFO
    void PSS_MainApp::LoadApplicationInfoType()
    {
        const CString appDir = GetApplicationDirectory();

        if (appDir.IsEmpty())
            return;

        CString                            appInfoFile = appDir + _T("\\zAppInfo.inf");
        PSS_CryptedFileApplicationTypeInfo appInfo(appInfoFile);

        m_ApplicationInfoType = appInfo.LoadApplicationType();
        m_ProductKeyFileInfo  = appInfo.LoadProductKey();
    }
#endif
//---------------------------------------------------------------------------
