//## begin module%334FC4630329.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC4630329.cm

//## begin module%334FC4630329.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC4630329.cp

//## Module: ZAMApp%334FC4630329; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZAMApp.h

#ifndef ZAMApp_h
#define ZAMApp_h 1

//## begin module%334FC4630329.additionalIncludes preserve=no
//## end module%334FC4630329.additionalIncludes

//## begin module%334FC4630329.includes preserve=yes
#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "zBaseLib\ZDDoc.h"
#include "mainfrm.h"
#include "PSS_ModifyView.h"
#include "planfin.hdf"
#include "zEvent\ActLog.h"

// Contains obsolete class for PLFN hierarchy
#include "zBaseLib\PSS_PlanFinObsoleteObjects.h"

#include <CTYPE.H>
#include <locale.h>

#include "zBaseLib\PSS_DocTemplateEx.h"
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"

#ifdef _ZCHECKINFO
#include "zBaseLib\ZBCriptedFileApplicationTypeInfo.h"
#endif

#include "zBaseLib\PSS_SingleInstanceApplication.h"

#include "stbox.h"

#ifndef _WIN32

extern "C" extern void WINAPI InitZResDLL();
extern "C" extern void WINAPI InitZWinUtilDLL();

// Three external functions to enable 3d controls
#ifdef __cplusplus
extern "C" {
#endif
    int FAR PASCAL Ctl3dRegister(HANDLE);
    int FAR PASCAL Ctl3dAutoSubclass(HANDLE);
    int FAR PASCAL Ctl3dUnregister(HANDLE);
#ifdef __cplusplus
}
#endif

#endif

#include "zBaseLib\ZISubject.h"

// ZBServer
#include "zBaseLib\PSS_Server.h"

//## end module%334FC4630329.includes

// ZAFontMg
#include "zBaseLib\PSS_FontManager.h"

// ZAStylMg
#include "zBaseLib\PSS_StyleManager.h"

// TmplMng
#include "zBaseLib\PSS_TemplateManager.h"

// AppOpt
#include "zBaseLib\PSS_ApplicationOption.h"

// FieldRep
#include "zBaseLib\PSS_FieldRepository.h"

// GFldDoc
#include "zBaseLib\PSS_GlobalFieldDocument.h"
#include "zBaseLib\PSS_Global.h"
#include "ZTTemplateDocument.h"

// JMR-MODIF - Le 24 avril 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

// JMR-MODIF - Le 31 décembre 2006 - Modification de la hiérarchie de classes pour la prise en charge par le médiateur.
class ZAMainApp : public PSS_SingleInstanceApplication,
    public ZISubject,
    public ZTTemplateDocument<_TemplateFunctionNoopAccessor>
{
    DECLARE_DYNAMIC(ZAMainApp)
    typedef ZTTemplateDocument<_TemplateFunctionNoopAccessor> _ThisClass;

public:

    // Inherited feature
    typedef PSS_SingleInstanceApplication inherited;

    // Component windows
    PSS_StatusBar& GetStatusBar()
    {
        return((ZIMainFrame*)AfxGetMainWnd())->GetStatusBar();
    }

    virtual void SetVisualToolObject(const CString& sClassName) = 0;
    virtual BOOL OpenFieldRepositoryReadOnly() const = 0;
    virtual PSS_Global::IEApplicationType GetApplicationType() const = 0;

    // Return true if the system needs to authenticate the user before
    // starting the application
    virtual BOOL UserAuthenticationRequired() const = 0;

    // Return true if the system needs to load the user file
    virtual BOOL LoadUserFile() const = 0;

    // Return the application directory
    CString GetApplicationDir() const;

#ifdef _ZCHECKINFO
    // Return the application directory
    ZBCriptedFileApplicationTypeInfo::ApplicationInfoType GetApplicationInfoType() const;
    CString GetProductKeyFileInfo() const
    {
        return m_ProductKeyFileInfo;
    };
#endif

    // Open a document file, also called from the DDE
    virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);

    // Saves all modified document without prompting for save
    // except for new document without names
    virtual bool SaveAllModifiedNoPrompt();

    BOOL ChooseServer();
    BOOL BuildTemplateName(CString& str, PSS_Stamp& Stamp);

    // JMR-MODIF - Le 14 juillet 2005 - Supprimé les fonctions de modification des paramètres de l'imprimante,
    // car ces fonctions sont maintenant gérées ailleurs dans le programme.
//    void     SetPrinterOrientation    ( BOOL bInPortrait );
//    void    SetPrinterPaperSize        ( short Format );
//    void    SetPrinterSettings        ( short Orientation, short Format );

    // Generic Application Options
    BOOL ShowWelcomeScreen()
    {
        return GetApplicationOptions().GetShowWelcomeScreen();
    }

    void SetShowWelcomeScreen(const BOOL value)
    {
        GetApplicationOptions().SetShowWelcomeScreen(value);
    }

    BOOL MaximizeFormOnOpen()
    {
        return GetApplicationOptions().GetMaximizeFormOnOpen();
    }

    BOOL IsAutoCalculate()
    {
        return GetApplicationOptions().GetAutoCalculate();
    }

    BOOL GoNextEdit()
    {
        return GetApplicationOptions().GetGoNextEdit();
    }

    BOOL ShowCalculateField()
    {
        return GetApplicationOptions().GetShowCalculateField();
    }

    BOOL ShowHiddenField()
    {
        return GetApplicationOptions().GetShowHiddenField();
    }

    BOOL ShowBoundsRect()
    {
        return GetApplicationOptions().GetShowBoundsRect();
    }

    BOOL ShowAnimation()
    {
        return GetApplicationOptions().GetShowAnimation();
    }

    BOOL ShowCreateFormsOnStartup()
    {
        return GetApplicationOptions().GetCreateOnStartup();
    }

    BOOL MustOpenLastLoadedFile()
    {
        return GetApplicationOptions().GetOpenLastLoadedFile();
    }

    const CString GetLastLoadedFile()
    {
        return GetApplicationOptions().GetLastLoadedFileName();
    }

    BOOL AutomaticFieldNameCreation()
    {
        return GetApplicationOptions().GetAutomaticFieldNameCreation();
    }

    void SetLastLoadedFile(const CString value)
    {
        GetApplicationOptions().SetLastLoadedFileName(value);
    }

    const CString GetExportSchemaName()
    {
        return GetApplicationOptions().GetExportSchemaName();
    }

    const int GetExportPropagationMode()
    {
        return GetApplicationOptions().GetExportPropagationMode();
    }

    BOOL GetEmptyWhenZero()
    {
        return GetApplicationOptions().GetEmptyWhenZero();
    }

    BOOL ForceNetworkConnection()
    {
        return GetApplicationOptions().GetForceNetworkConnection();
    }

    void SetForceNetworkConnection(const BOOL value)
    {
        GetApplicationOptions().SetForceNetworkConnection(value);
    }

    BOOL DontShowToolTip()
    {
        return GetApplicationOptions().GetDontShowToolTip();
    }

    void SetDontShowToolTip(const BOOL value)
    {
        GetApplicationOptions().SetDontShowToolTip(value);
    }

    BOOL DontShowTaskList()
    {
        return GetApplicationOptions().GetDontShowTaskList();
    }

    void SetDontShowTaskList(const BOOL value)
    {
        GetApplicationOptions().SetDontShowTaskList(value);
    }

    CString GetRegisteredUserName()
    {
        return GetApplicationOptions().GetRegisteredUserName();
    }

    void SetRegisteredUserName(CString value)
    {
        GetApplicationOptions().SetRegisteredUserName(value);
    }

    CString GetRegisteredCompanyName()
    {
        return GetApplicationOptions().GetRegisteredCompanyName();
    }

    void SetRegisteredCompanyName(CString value)
    {
        GetApplicationOptions().SetRegisteredCompanyName(value);
    }

    CString GetRegisteredProductKey()
    {
        return GetApplicationOptions().GetRegisteredProductKey();
    }

    void SetRegisteredProductKey(CString value)
    {
        GetApplicationOptions().SetRegisteredProductKey(value);
    }

    // Server Options
    CString GetFileDirectory()
    {
        return GetServer().GetFileDirectory();
    }

    void SetFileDirectory(const CString value)
    {
        GetServer().SetFileDirectory(value);
    }

    CString GetTemplateDirectory()
    {
        return GetServer().GetTemplateDirectory();
    }

    void SetTemplateDirectory(const CString value)
    {
        GetServer().SetTemplateDirectory(value);
    }

    void TemplateDirectoryHasChanged();

    // Return the name of the Normal Template.
    CString GetNormalTemplate()
    {
        return GetServer().GetNormalTemplate();
    }

    CString GetProcessTemplateDirectory()
    {
        return GetServer().GetProcessTemplateDirectory();
    }

    void SetProcessTemplateDirectory(const CString value)
    {
        GetServer().SetProcessTemplateDirectory(value);
    }

    void ProcessTemplateDirectoryHasChanged();

    // Return the name of the Normal Process Template.
    CString GetNormalProcessTemplate()
    {
        return GetServer().GetNormalProcessTemplate();
    }

    CString GetModelTemplateDirectory()
    {
        return GetServer().GetModelTemplateDirectory();
    }

    void SetModelTemplateDirectory(const CString value)
    {
        GetServer().SetModelTemplateDirectory(value);
    }

    void ModelTemplateDirectoryHasChanged();

    // Return the name of the Normal Model Template.
    CString GetNormalModelTemplate()
    {
        return GetServer().GetNormalModelTemplate();
    }

    CString GetModelUnitDirectory()
    {
        return GetServer().GetModelUnitDirectory();
    }

    void SetModelUnitDirectory(const CString value)
    {
        GetServer().SetModelUnitDirectory(value);
    }

    CString GetRootDirectory()
    {
        return GetServer().GetRootPath();
    }

    void SetRootDirectory(const CString value)
    {
        GetServer().SetRootPath(value);
    }

    // Internal directories
    CString GetSystemDirectory()
    {
        return GetServer().GetSystemDirectory();
    }

    CString GetEventDirectory()
    {
        return GetServer().GetEventDirectory();
    }

    CString GetInterfaceDirectory()
    {
        return GetServer().GetInterfaceDirectory();
    }

    CString GetLogDirectory()
    {
        return GetServer().GetLogDirectory();
    }

    CString GetUserDirectory()
    {
        return GetServer().GetUserDirectory();
    }

    CString GetUserDefinitionFile()
    {
        return GetServer().GetUserDefinitionFile();
    }

    CString GetGlobalFieldNameRepository()
    {
        return GetServer().GetGlobalFieldNameRepository();
    }

    void SetGlobalFieldNameRepository(const CString value)
    {
        GetServer().SetGlobalFieldNameRepository(value);
    }

    CString GetLogFile()
    {
        return GetServer().GetLogFile();
    }

    CString GetLogDatabaseFile()
    {
        return GetServer().GetLogDatabaseFile();
    }

    BOOL GetUseLogTextFile()
    {
        return GetServer().GetUseLogTextFile();
    }

    void SetUseLogTextFile(BOOL value)
    {
        GetServer().SetUseLogTextFile(value);
    }

    BOOL GetUseLogDatabaseFile()
    {
        return GetServer().GetUseLogDatabaseFile();
    }

    void SetUseLogDatabaseFile(BOOL value)
    {
        GetServer().SetUseLogDatabaseFile(value);
    }

    const BOOL GetUseFolderNameAsFile()
    {
        return GetServer().GetUseFolderNameAsFile();
    }

    void SetUseFolderNameAsFile(BOOL value)
    {
        GetServer().SetUseFolderNameAsFile(value);
    }

    const BOOL GetStoreUserFileByUser()
    {
        return GetServer().GetStoreUserFileByUser();
    }

    void SetStoreUserFileByUser(BOOL value)
    {
        GetServer().SetStoreUserFileByUser(value);
    }

    virtual void RefreshCurrentSchema()
    {}

    // Advanced: virtual access to m_pMainWnd
    virtual ZIMainFrame* GetMainWindow()
    {
        return (ZIMainFrame*)m_pMainWnd;
    }

    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

    // Virtual method which allows derived class to change the m_pszProfileName variable
    virtual void OnChangeWinIniFilename()
    {}

public:

    ZAMainApp();
    ~ZAMainApp();

    virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

    // Return the application name.
    virtual CString GetApplicationName() const;

    // Return the application registry key
    virtual CString GetApplicationRegistryKey() const
    {
        return _T("");
    }

    // Return the application registry key for the product ID
    virtual CString GetApplicationRegistryProductEntryKey() const
    {
        return _T("PID");
    }

    BOOL ShouldSaveDesign() const;

    BOOL ShouldPrintLine() const;

    virtual BOOL InitInstance();

    virtual int ExitInstance();

    // Returns the active CDocument pointer.
    CDocument* GetActiveCDocument();

    // Return the casted active document.
    ZDDocument* GetActiveDocument();

    // Return the casted active base document.
    PSS_BaseDocument* GetActiveBaseDocument();

    //## Operation: GetStyleManager%870446010
    // Return the style manager of the current document.
    PSS_StyleManager& GetStyleManager();

    //## Operation: GetFontManager%870446011
    // Return the Font Manager of the current document.
    PSS_FontManager& GetFontManager();

    //## Operation: DisplaySampleText%870643929
    // Display a text using the font or the style passed in parameter.
    void DisplaySampleText(CDC*            pDC,
                           const CString&    sValue,
                           CRect            Rect,
                           PSS_Font::Handle        hFont = g_NoFontDefined,
                           PSS_Style::Handle        hStyle = g_NoStyleDefined);

    //## Operation: DisplaySampleText%870643928
    // Display a text using the font or the style passed in
    // parameter.
    void DisplaySampleText(CDC*            pDC,
                           const CString&    sValue,
                           CRect            Rect,
                           PSS_Font*            pFont = NULL,
                           PSS_Style*        pStyle = NULL);

    //## Operation: IsCursorCapturedValid%908554843
    // Check if the cursor capture still valid.
    virtual BOOL IsCursorCapturedValid(const CPoint& point, ZIView* pView);

    //## Operation: GetFieldRepository%910104706
    PSS_FieldRepository* GetFieldRepository();

    //## Operation: SetCurrentDocument%910434288
    // Sets the current document.
    void SetCurrentDocument(ZDDocument* pDoc);

    //## Operation: GetCurrentDocument%910434289
    // Returns the current document pointer.
    ZDDocument* GetCurrentDocument() const;

    //## Operation: GetServerIniFile%912537579
    // Get the global ini file. This function is pure virtual.
    virtual CString GetServerIniFile();

    //## Operation: ExitAppl%912537580
    virtual BOOL ExitAppl();

    //## Operation: LoadApplicationOptions%912623191
    // Load the application options.
    virtual BOOL LoadApplicationOptions() = 0;

    //## Operation: SaveApplicationOptions%912623192
    // Load the application options.
    virtual BOOL SaveApplicationOptions() = 0;

    //## Operation: SetServerIniFile%912623195
    // Set the global ini file. This function is virtual.
    virtual void SetServerIniFile(const CString& value);

    //## Operation: GetDocumentList%928442320
    // Fill the document list with open document.
    void GetDocumentList(CObList& DocList);
    void GetDocumentArrayName(CStringArray& FileArray);

    //## Operation: IsDocumentOpen%928442321
    // Returns true if the document is already open.
    BOOL IsDocumentOpen(const CString Filename);

    //## Operation: ReadOnlyDocuments%934529054
    // return TRUE if the documents should be open in read-only mode.
    virtual BOOL ReadOnlyDocuments() const = 0;

    //## Operation: IsWorkingLocaly%934529055
    // return TRUE is the application is working locally.
    virtual BOOL IsWorkingLocaly() const = 0;

    //## Get and Set Operations for Class Attributes (generated)

    //## Attribute: Server%36643CEB0064
    // Implements the Global Options.
    PSS_CltServer& GetServer();

    //## Attribute: ActivityLog%369BC5AC0258
    // Has an activity log utility class.
    ZUActivityLog& GetActivityLog();

    //## Attribute: ApplicationOptions%3705D2C00105
    // Is the application options class.
    PSS_ApplicationOption& GetApplicationOptions();

    virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

    void DisplayWarningOnCommand();

protected:

    /////////////////////////////////////////////////////////////////////////////
    // Additional Template operations
    void RegisterAdditionalTemplate(UINT nIDRes);

    virtual CDocument* OnOpenAdditionalTemplateFile(LPCSTR Filename)
    {
        return NULL;
    }

    virtual void OnSaveAdditionalTemplateFile(LPCSTR Filename)
    {}

    // Register the additional template not covered by
    // CDocTemplate
    virtual bool OnRegisterAdditionalTemplate();

    /////////////////////////////////////////////////////////////////////////////
    // Open Save call-back operations
    // JMR-MODIF - Le 24 avril 2006 - Ajout de la variable Filename dans la déclaration.
    virtual void OnAfterOpenDocument(CDocument* pDoc, CString Filename)
    {}

    virtual void OnAfterSaveDocument(CDocument* pDoc)
    {}

    // The derived application must return the right help filename
    virtual CString OnBuildHelpFilename()
    {
        return _T("");
    }

    virtual BOOL InitAppl();

    // Used to open a server session
    virtual BOOL OpenServerSession();

    // Called by the framework when a server has been chosen
    virtual void OnServerChanged();

    virtual void OnServerHasBeenOpened()
    {
        // Do nothing
    }

    //## Operation: RegisterShellFileTypes%910089417

    // Bug correction with short executable filename
    void EnableShellOpen();

    // Register the standard extention files.
    // Add the icon facility.
    void RegisterShellFileTypes(BOOL bCompat = FALSE);
    void RegisterAdditionalTemplateShellFileTypes(BOOL bCompat = FALSE);

    //## Operation: PostInitAppl%910716404
    virtual BOOL PostInitAppl();

    //## Operation: LoadAllUsers%934529052
    //    Load all users and initialize the connected user.
    BOOL LoadAllUsers();

    BOOL DoPromptFileName(CString&            fileName,
                          const CString&    initialDir,
                          UINT                nIDSTitle,
                          DWORD            lFlags,
                          BOOL                bOpenFileDialog,
                          CDocTemplate*    pTemplate);

    void AppendFilterSuffix(CString& filter, OPENFILENAME& ofn, CDocTemplate* pTemplate, CString* pstrDefaultExt);

    //{{AFX_MSG(ZAMainApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // JMR-MODIF - Le 23 août 2005 - Ajout de la fonction Release.
    void Release();

protected:

    ZDDocument*            m_pCurrentDocument;

    PSS_PlanFinObject*     m_pOldSelectedObj;

    PSS_ApplicationOption m_ApplicationOptions;

    PSS_FieldRepository*  m_FieldRepository;

    CString                m_HelpFile;

    DWORD                m_numHelpIDs;

    UINT                m_IDD_Splash;
    UINT                m_IDD_About;
    UINT                m_IDD_Support;
    //## end ZAMainApp%334FC462021D.protected

private:

    //## Constructors (generated)
    ZAMainApp(const ZAMainApp &right);

    //## Assignment Operation (generated)
    const ZAMainApp & operator=(const ZAMainApp &right);

#ifdef _ZCHECKINFO
    // Load the application type doing anything
    void LoadApplicationInfoType();
#endif

    //## Other Operations (specified)
    //## Operation: LoadGlobalFieldRepository%910019984
    //    Load the global repository of fields.
    BOOL LoadGlobalFieldRepository();

    // Data Members for Class Attributes
private:

    //## begin ZAMainApp::Server%36643CEB0064.attr preserve=no  public: ZBCltServer {U}
    PSS_CltServer        m_Server;

    //## end ZAMainApp::Server%36643CEB0064.attr

    //## begin ZAMainApp::ActivityLog%369BC5AC0258.attr preserve=no  public: ZUActivityLog {U}
    ZUActivityLog    m_ActivityLog;

    //## end ZAMainApp::ActivityLog%369BC5AC0258.attr

#ifdef _ZCHECKINFO
    ZBCriptedFileApplicationTypeInfo::ApplicationInfoType    m_ApplicationInfoType;
    CString                                                    m_ProductKeyFileInfo;
#endif
};

//## begin ZAMainApp%334FC462021D.postscript preserve=yes
//## end ZAMainApp%334FC462021D.postscript

// Class ZAMainApp 

//## Other Operations (inline)
inline CString ZAMainApp::GetApplicationName() const
{
    //## begin ZAMainApp::GetApplicationName%834216953.body preserve=yes
    return(_T("Plan Financier"));
    //## end ZAMainApp::GetApplicationName%834216953.body
}

inline BOOL ZAMainApp::ShouldSaveDesign() const
{
    //## begin ZAMainApp::ShouldSaveDesign%834216956.body preserve=yes
    return FALSE;
    //## end ZAMainApp::ShouldSaveDesign%834216956.body
}

inline BOOL ZAMainApp::ShouldPrintLine() const
{
    return m_ApplicationOptions.GetPrintLine();
}

inline CDocument* ZAMainApp::GetActiveCDocument()
{
    if (AfxGetMainWnd() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument())
    {
        return ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
    }

    return NULL;
}

inline ZDDocument* ZAMainApp::GetActiveDocument()
{
    //## begin ZAMainApp::GetActiveDocument%853735838.body preserve=yes
    if (AfxGetMainWnd() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument() &&
        ISA(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument(), ZDDocument))
    {
        return (ZDDocument*)(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument());
    }

    return NULL;
    //## end ZAMainApp::GetActiveDocument%853735838.body
}

inline PSS_BaseDocument* ZAMainApp::GetActiveBaseDocument()
{
    if (AfxGetMainWnd() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame() &&
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument() &&
        ISA(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument(), PSS_BaseDocument))
    {
        return (PSS_BaseDocument*)(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument());
    }

    return NULL;
}

inline PSS_StyleManager& ZAMainApp::GetStyleManager()
{
    //## begin ZAMainApp::GetStyleManager%870446010.body preserve=yes
    // Must have a current document
    ASSERT(GetActiveDocument());
    return GetActiveDocument()->GetStyleManager();
    //## end ZAMainApp::GetStyleManager%870446010.body
}

inline PSS_FontManager& ZAMainApp::GetFontManager()
{
    //## begin ZAMainApp::GetFontManager%870446011.body preserve=yes
    // Must have a current document
    ASSERT(GetActiveDocument());
    return GetActiveDocument()->GetFontManager();
    //## end ZAMainApp::GetFontManager%870446011.body
}

inline PSS_FieldRepository* ZAMainApp::GetFieldRepository()
{
    //## begin ZAMainApp::GetFieldRepository%910104706.body preserve=yes
    if (m_FieldRepository != NULL)
    {
        return ((m_FieldRepository->IsValid()) ? m_FieldRepository : NULL);
    }
    else return NULL;
    //## end ZAMainApp::GetFieldRepository%910104706.body
}

inline void ZAMainApp::SetCurrentDocument(ZDDocument* pDoc)
{
    //## begin ZAMainApp::SetCurrentDocument%910434288.body preserve=yes
    m_pCurrentDocument = pDoc;
    //## end ZAMainApp::SetCurrentDocument%910434288.body
}

inline ZDDocument* ZAMainApp::GetCurrentDocument() const
{
    //## begin ZAMainApp::GetCurrentDocument%910434289.body preserve=yes
    return (ZDDocument*)m_pCurrentDocument;
    //## end ZAMainApp::GetCurrentDocument%910434289.body
}

inline CString ZAMainApp::GetServerIniFile()
{
    return GetApplicationOptions().GetServerIniFileName();
}

inline void ZAMainApp::SetServerIniFile(const CString& value)
{
    GetApplicationOptions().SetServerIniFileName(value);
}

//## Get and Set Operations for Has Relationships (inline)

//## Get and Set Operations for Class Attributes (inline)

inline PSS_CltServer& ZAMainApp::GetServer()
{
    //## begin ZAMainApp::GetServer%36643CEB0064.get preserve=no
    return m_Server;
    //## end ZAMainApp::GetServer%36643CEB0064.get
}

inline ZUActivityLog& ZAMainApp::GetActivityLog()
{
    //## begin ZAMainApp::GetActivityLog%369BC5AC0258.get preserve=no
    return m_ActivityLog;
    //## end ZAMainApp::GetActivityLog%369BC5AC0258.get
}

inline PSS_ApplicationOption& ZAMainApp::GetApplicationOptions()
{
    return m_ApplicationOptions;
}

#ifdef _ZCHECKINFO
inline ZBCriptedFileApplicationTypeInfo::ApplicationInfoType ZAMainApp::GetApplicationInfoType() const
{
    return m_ApplicationInfoType;
}
#endif

#endif