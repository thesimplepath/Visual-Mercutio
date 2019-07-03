//## begin module%364419D90317.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%364419D90317.cm

//## begin module%364419D90317.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%364419D90317.cp

//## Module: ZAApp%364419D90317; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZPROCESS\ZAApp.h

#ifndef ZAApp_h
#define ZAApp_h 1

// ZAMApp
#include "ZAMApp.h"

#include "DocWrite.h"

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

// Forward declaration
class ZIMainFrame;
class ZVOutputWorkspace;
class ZVProcessWorkspace;
class ZVPropertiesWorkspace;
class ZDWorkspaceEnvDocument;
class ZBWorkspaceEnv;
class ZDProcessGraphModelDoc;
class ZBWorkspaceWizardTemplateMg;
class ZDUserEntityDocument;
class ZBUserGroupEntity;
class ZDLogicalSystemDocument;
class ZBLogicalSystemEntity;

// JMR-MODIF - Le 7 octobre 2005 - Ajout des classes du nouvel espace de travail des prestations.
class ZDLogicalPrestationsDocument;
class ZBLogicalPrestationsEntity;

// JMR-MODIF - Le 15 novembre 2006 - Ajout des classes du nouvel espace de travail des règles.
class ZDLogicalRulesDocument;
class ZBLogicalRulesEntity;

// JMR-MODIF - Le 8 juillet 2007 - Ajout des classes de la nouvelle propriété Risques.
class ZVRiskTypeContainer;
class ZVRiskImpactContainer;
class ZVRiskProbabilityContainer;

// derive from the abstract CGXAppAdapter
class ZBGridAppAdapter : public CGXAppAdapter
{
public:

    ZBGridAppAdapter();
    virtual ~ZBGridAppAdapter();
    virtual CDocTemplate* GetDocTemplate( CRuntimeClass* pViewClass, CRuntimeClass* pDocClass );

protected:

    CMultiDocTemplate* m_pDocTemplate;
};

class ZAApp : public ZAMainApp, public ZBGridAppAdapter
{
    //## begin ZAApp%36441921033A.initialDeclarations preserve=yes
    public:

    DECLARE_DYNAMIC( ZAApp )

    // Inherited feature
    typedef ZAMainApp inherited;

    ZIMainFrame*            GetMainFrame();
    ZVOutputWorkspace*        GetOutputWorkspace();
    ZVProcessWorkspace*        GetProcessWorkspace();
    ZVPropertiesWorkspace*    GetPropertiesWorkspace();

    ZIProjectBar* GetProjectWindowBar();
    PSS_TipOfDayBar* GetwndTipOfDayBar();

    // Workspace functions
    ZBWorkspaceEnv*            GetCurrentWorkspaceEnvironment();
    bool                     WorkspaceEnvironmentExist();
    bool                    IsWorkspaceEnvironmentLoaded();
    bool                    IsWorkspaceEnvironmentModified();
    bool                    CloseCurrentWorkspace( bool AskClosingDocument = false );
    bool                    CloseCurrentAndAllocateNewWorkspace();
    bool                    SaveCurrentWorkspace();

    // User group functions
    ZBUserGroupEntity* GetMainUserGroup();

    CString GetUserGroupFilename() const
    {
        return m_UserGroupFilename;
    }

    // Logical system functions
    ZBLogicalSystemEntity* GetMainLogicalSystem();

    CString GetLogicalSystemFilename() const
    {
        return m_LogicalSystemFilename;
    }

    // ********************************************************************************
    // Fonctions concernant l'espace de travail des prestations

    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction GetMainLogicalPrestations.
    ZBLogicalPrestationsEntity* GetMainLogicalPrestations();

    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction GetPrestationsFilename.
    CString GetPrestationsFilename() const
    {
        return m_PrestationsFilename;
    }
    // ********************************************************************************

    // ********************************************************************************
    // Fonctions concernant l'espace de travail des règles

    // JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction GetMainLogicalRules.
    ZBLogicalRulesEntity* GetMainLogicalRules();

    // JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction GetRulesFilename.
    CString GetRulesFilename() const
    {
        return m_RulesFilename;
    }
    // ********************************************************************************

    // ********************************************************************************
    // JMR-MODIF - Le 8 juillet 2007 - Ajout des fonctions concernant les risques.

    ZVRiskTypeContainer* GetRiskTypeContainer()
    {
        return m_pRiskTypeContainer;
    }

    BOOL LoadTypeRiskFile();

    ZVRiskImpactContainer* GetRiskImpactContainer()
    {
        return m_pRiskImpactContainer;
    }

    BOOL LoadImpactRiskFile();

    ZVRiskProbabilityContainer* GetRiskProbabilityContainer()
    {
        return m_pRiskProbabilityContainer;
    }

    BOOL LoadProbabilityRiskFile();
    // ********************************************************************************

    ZDProcessGraphModelDoc* FileNewModel();

    // View functions
    ZIView* GetMainView()
    {
        return ( GetActiveDocument() ) ? GetActiveDocument()->GetMainView() : NULL;
    }

    virtual void RefreshCurrentSchema()
    {
        GetActiveDocument()->RefreshCurrentSchema();
    }

    virtual BOOL IsWorkingLocaly() const
    {
        return TRUE;
    }

    virtual BOOL ReadOnlyDocuments() const
    {
        return FALSE;
    }

    // Open the field repository in read only mode
    virtual BOOL OpenFieldRepositoryReadOnly() const
    {
        return TRUE;
    }

    virtual eApplicationType GetApplicationType() const
    {
        return zProcess;
    }

    // Return true if the system needs to authenticate the user before
    // starting the application
    virtual BOOL UserAuthenticationRequired() const
    {
        return FALSE;
    }

    // Return true if the system needs to load the user file
    virtual BOOL LoadUserFile() const
    {
        return FALSE;
    }

    virtual BOOL ExitAppl();

    virtual void SetVisualToolObject( const CString& sClassName );

    // Get the global ini file. This function is pure virtual.
    virtual CString GetGlobalIniFile ();

    // Set the global ini file. This function is virtual.
    virtual void SetGlobalIniFile( CString& value );

    CString GetWorkspaceFilename() const
    {
        return m_WorkspaceFilename;
    }

    // JMR-MODIF - Le 29 juillet 2007 - Cette fonction retourne le nom du fichier d'initialisation de l'application.
    CString GetApplicationIniFilename() const
    {
        return m_pszProfileName;
    }

public:
    
    //## Constructors (generated)
    ZAApp();
    
    //## Destructor (generated)
    ~ZAApp();

    // JMR-MODIF - Le 23 août 2005 - Ajout de la fonction Release.
    void Release();

    // JMR-MODIF - Le 29 juillet 2007 - Cette fonction permet de mettre à jour le dernier fichier chargé.
    void UpdateLastLoadedFile(const CString& filename )
    {
        SetLastLoadedFile(filename);
    }

    //## Other Operations (specified)
    //## Operation: GetApplicationName%910434300
    //    Return the application name.
    virtual CString GetApplicationName() const;

    // Return the application registry key
    virtual CString GetApplicationRegistryKey() const
    {
        return _T( "SOFTWARE\\ProcessSoft\\Mercutio - Conceptor" );
    }

    //## Operation: InitInstance%910434301
    virtual BOOL InitInstance();

    //## Operation: ExitInstance%910434302
    virtual int ExitInstance();

    //## Operation: IsCursorCapturedValid%910434304
    //    Check if the cursor capture still valid.
    virtual BOOL IsCursorCapturedValid( const CPoint& point, ZIView* pView );

    //## Operation: GetCurrentDocument%910434306
    //    Returns the current document pointer.
    ZDDocumentReadWrite* GetCurrentDocument() const;

    //## Operation: OnIdle%910633441
    //    This function is used to not use a timer
    //    When the drawing function draw with red
    //    color fields that have changed
    //    When this function is calle
    virtual BOOL OnIdle( LONG lCount );

    //## Operation: ZAGetApp%910716403
    //    Return the pointer to the global application.
    static ZAApp* ZAGetApp();

    //## Operation: LoadApplicationOptions%912537584
    //    Load the application options.
    virtual BOOL LoadApplicationOptions();

    //## Operation: SaveApplicationOptions%912537585
    //    Load the application options.
    virtual BOOL SaveApplicationOptions();

    CDocument* OpenWorkspaceFile( LPCSTR Filename );
    void SaveWorkspaceFile( LPCSTR Filename );

    // JMR-MODIF - Le 28 décembre 2006 - Ajout des fonctions DoRefreshProperties et DoRefreshSymbolsAndProperties.
    void DoRefreshProperties();
    void DoRefreshSymbolsAndProperties();

protected:

    /////////////////////////////////////////////////////////////////////////////
    // Additional Template operations
    virtual CDocument*    OnOpenAdditionalTemplateFile( LPCSTR Filename );
    virtual void        OnSaveAdditionalTemplateFile( LPCSTR Filename );

    // Register the additional template not covered by CDocTemplate
    virtual bool OnRegisterAdditionalTemplate();

    /////////////////////////////////////////////////////////////////////////////
    // Open Save call-back operations
    virtual void OnAfterOpenDocument(CDocument* pDoc, const CString& filename);
    virtual void OnAfterSaveDocument(CDocument* pDoc);

    // Called by the framework when a server has been chosen
    virtual void OnServerChanged();
    virtual void OnServerHasBeenOpened();

    virtual BOOL InitAppl();
    virtual BOOL PostInitAppl();

    // The derived application must return the right help filename
    virtual CString OnBuildHelpFilename();

    //{{AFX_MSG( ZAApp )
    afx_msg void OnAppAbout();
    afx_msg void OnHelpSupport();
    afx_msg void OnAppExit();
    afx_msg void OnOptions();
    afx_msg void OnChooseServer();
    afx_msg void OnFileNewModel();
    afx_msg void OnFileOpenModel();
    afx_msg void OnUpdateFileOpenModel(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileNewModel(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnFileSaveAll();
    afx_msg void OnUpdadeFileSaveAll(CCmdUI* pCmdUI);
    afx_msg void OnNewWorkspace();
    afx_msg void OnOpenWorkspace();
    afx_msg void OnSaveWorkspace();
    afx_msg void OnUpdateSaveWorkspace(CCmdUI* pCmdUI);
    afx_msg void OnCloseWorkspace();
    afx_msg void OnUpdateCloseWorkspace(CCmdUI* pCmdUI);
    afx_msg void OnFileOpen();
    afx_msg void OnProcessFileOpen();
    afx_msg void OnWksNewGroup();
    afx_msg void OnUpdateWksNewGroup(CCmdUI* pCmdUI);
    afx_msg void OnWksDeleteGroup();
    afx_msg void OnUpdateWksDeleteGroup(CCmdUI* pCmdUI);
    afx_msg void OnWksRenameGroup();
    afx_msg void OnUpdateWksRenameGroup(CCmdUI* pCmdUI);
    afx_msg void OnWksAddFile();
    afx_msg void OnUpdateWksAddFile(CCmdUI* pCmdUI);
    afx_msg void OnWksDeleteFile();
    afx_msg void OnUpdateWksDeleteFile(CCmdUI* pCmdUI);
    afx_msg void OnWksOpenFile();
    afx_msg void OnUpdateWksOpenFile(CCmdUI* pCmdUI);
    afx_msg void OnAddCurrentFileToProject();
    afx_msg void OnUpdateAddCurrentFileToProject(CCmdUI* pCmdUI);
    afx_msg void OnWksProperties();
    afx_msg void OnUpdateWksProperties(CCmdUI* pCmdUI);
    afx_msg void OnUgpAddGroup();
    afx_msg void OnUpdateUgpAddGroup(CCmdUI* pCmdUI);
    afx_msg void OnUgpDeleteGroup();
    afx_msg void OnUpdateUgpDeleteGroup(CCmdUI* pCmdUI);
    afx_msg void OnUgpRenameGroup();
    afx_msg void OnUpdateUgpRenameGroup(CCmdUI* pCmdUI);
    afx_msg void OnUgpProperties();
    afx_msg void OnUpdateUgpProperties(CCmdUI* pCmdUI);
    afx_msg void OnUgpAddRole();
    afx_msg void OnUpdateUgpAddRole(CCmdUI* pCmdUI);
    afx_msg void OnUgpDeleteRole();
    afx_msg void OnUpdateUgpDeleteRole(CCmdUI* pCmdUI);
    afx_msg void OnUgpRenameRole();
    afx_msg void OnUpdateUgpRenameRole(CCmdUI* pCmdUI);
    afx_msg void OnAddLogicalSystem();
    afx_msg void OnUpdateAddLogicalSystem(CCmdUI* pCmdUI);
    afx_msg void OnDeleteLogicalSystem();
    afx_msg void OnUpdateDeleteLogicalSystem(CCmdUI* pCmdUI);
    afx_msg void OnRenameLogicalSystem();
    afx_msg void OnUpdateRenameLogicalSystem(CCmdUI* pCmdUI);
    afx_msg void OnLogicalSystemProperties();
    afx_msg void OnUpdateLogicalSystemProperties(CCmdUI* pCmdUI);
    afx_msg void OnAddPrestation();
    afx_msg void OnUpdateAddPrestation(CCmdUI* pCmdUI);
    afx_msg void OnDeletePrestation();
    afx_msg void OnUpdateDeletePrestation(CCmdUI* pCmdUI);
    afx_msg void OnRenamePrestation();
    afx_msg void OnUpdateRenamePrestation(CCmdUI* pCmdUI);
    afx_msg void OnPrestationProperties();
    afx_msg void OnUpdatePrestationProperties(CCmdUI* pCmdUI);
    afx_msg void OnAddRule();
    afx_msg void OnUpdateAddRule(CCmdUI* pCmdUI);
    afx_msg void OnDeleteRule();
    afx_msg void OnUpdateDeleteRule(CCmdUI* pCmdUI);
    afx_msg void OnRenameRule();
    afx_msg void OnUpdateRenameRule(CCmdUI* pCmdUI);
    afx_msg void OnRuleProperties();
    afx_msg void OnUpdateRuleProperties(CCmdUI* pCmdUI);
    afx_msg void OnGenerateCheckReport();
    afx_msg void OnUpdateGenerateCheckReport(CCmdUI* pCmdUI);
    afx_msg void OnGenerateMercutioReport();
    afx_msg void OnUpdateGenerateMercutioReport(CCmdUI* pCmdUI);
    afx_msg void OnGenerateConceptorReport();
    afx_msg void OnUpdateGenerateConceptorReport(CCmdUI* pCmdUI);
    afx_msg void OnGenerateSesterceReport();
    afx_msg void OnUpdateGenerateSesterceReport(CCmdUI* pCmdUI);
    afx_msg void OnGenerateSesterceUnitReport();
    afx_msg void OnGenerateSesterceConsolidatedReport();
    afx_msg void OnGeneratePrestationsReport();
    afx_msg void OnUpdateGeneratePrestationsReport(CCmdUI* pCmdUI);
    afx_msg void OnFileProperty();
    afx_msg void OnUpdateFileProperty(CCmdUI* pCmdUI);
    afx_msg void OnAssignCurrentSystemdef();
    afx_msg void OnAssignCurrentUserdef();
    afx_msg void OnAssignCurrentPrestationsDef();
    afx_msg void OnAssignCurrentRulesDef();
    afx_msg void OnUpdateAssignCurrentSystemdef(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAssignCurrentUserdef(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAssignCurrentPrestationsDef(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAssignCurrentRulesDef(CCmdUI* pCmdUI);
    afx_msg void OnSymbolReassignUsergroup();
    afx_msg void OnUpdateSymbolReassignUsergroup(CCmdUI* pCmdUI);
    afx_msg void OnSymbolReassignLogicalsys();
    afx_msg void OnUpdateSymbolReassignLogicalsys(CCmdUI* pCmdUI);
    afx_msg void OnSymbolReassignPrestations();
    afx_msg void OnUpdateSymbolReassignPrestations(CCmdUI* pCmdUI);
    afx_msg void OnSymbolReassignRules();
    afx_msg void OnUpdateSymbolReassignRules(CCmdUI* pCmdUI);
    afx_msg void OnPublishToMessenger();
    afx_msg void OnUpdatePublishToMessenger(CCmdUI* pCmdUI);
    afx_msg void OnDynamicAttributesDisplay();
    afx_msg void OnUpdateDynamicAttributesDisplay(CCmdUI* pCmdUI);
    afx_msg void OnExportModelToHTMLFile();
    afx_msg void OnUpdateExportModelToHTMLFile(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFilePrintPreview(CCmdUI *pCmdUI);
    afx_msg void OnUpdateFilePrint(CCmdUI *pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    bool LoadUserGroupFile();
    bool SaveUserGroupFile( bool AskBeforeSave = true );

    bool LoadLogicalSystemFile();
    bool SaveLogicalSystemFile( bool AskBeforeSave = true );

    // JMR-MODIF - Le 7 octobre 2005 - Ajout des fonctions LoadPrestationsFile et SavePrestationsFile.
    bool LoadPrestationsFile();
    bool SavePrestationsFile( bool AskBeforeSave = true );

    // JMR-MODIF - Le 15 novembre 2006 - Ajout des fonctions LoadRulesFile et SaveRulesFile.
    bool LoadRulesFile();
    bool SaveRulesFile( bool AskBeforeSave = true );

private:

    ZAApp( const ZAApp &right );
    const ZAApp & operator=( const ZAApp &right );

private:

    CString                            m_GlobalIniFile;
    CString                            m_WorkspaceFilename;
    CString                            m_UserGroupFilename;
    CString                            m_LogicalSystemFilename;
    // JMR-MODIF - Le 7 octobre 2005 - Ajout de la variable m_PrestationsFilename.
    CString                            m_PrestationsFilename;
    // JMR-MODIF - Le 15 novembre 2006 - Ajout de la variable m_RulesFilename.
    CString                            m_RulesFilename;
    CString                            m_GlobalHistoricValueFilename;

    ZDWorkspaceEnvDocument*            m_pWorkspaceEnvDocument;

    ZBWorkspaceWizardTemplateMg*    m_pWorkspaceTemplateManager;

    ZDUserEntityDocument*            m_pUserEntityDocument;

    ZDLogicalSystemDocument*        m_pLogicalSystemDocument;

    // JMR-MODIF - Le 7 octobre 2005 - Ajout de la variable m_pPrestationsDocument.
    ZDLogicalPrestationsDocument*    m_pPrestationsDocument;

    // JMR-MODIF - 15 novembre 2006 - Ajout de la variable m_pRulesDocument.
    ZDLogicalRulesDocument*            m_pRulesDocument;

    // JMR-MODIF - Le 8 juillet 2007 - Ajout de la variable m_RiskTypeContainer.
    ZVRiskTypeContainer*            m_pRiskTypeContainer;

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de la variable m_pRiskImpactContainer.
    ZVRiskImpactContainer*            m_pRiskImpactContainer;

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de la variable m_pRiskProbabilityContainer.
    ZVRiskProbabilityContainer*        m_pRiskProbabilityContainer;
};

//## begin ZAApp%36441921033A.postscript preserve=yes
//## end ZAApp%36441921033A.postscript

// Class ZAApp

//## Other Operations (inline)
inline CString ZAApp::GetApplicationName() const
{
    //## begin ZAApp::GetApplicationName%910434300.body preserve=yes
    return( _T( "ProcessSoft-Conceptor" ) );
    //## end ZAApp::GetApplicationName%910434300.body
}

inline ZDDocumentReadWrite* ZAApp::GetCurrentDocument() const
{
    //## begin ZAApp::GetCurrentDocument%910434306.body preserve=yes
    return (ZDDocumentReadWrite*)m_pCurrentDocument;
    //## end ZAApp::GetCurrentDocument%910434306.body
}

inline ZAApp* ZAApp::ZAGetApp()
{
    //## begin ZAApp::ZAGetApp%910716403.body preserve=yes
    return (ZAApp*)AfxGetApp();
    //## end ZAApp::ZAGetApp%910716403.body
}

//## begin module%364419D90317.epilog preserve=yes
inline void ZAApp::SetGlobalIniFile ( CString& value )
{
    m_GlobalIniFile = value;
}

//## end module%364419D90317.epilog
#endif