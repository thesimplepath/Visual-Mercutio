/****************************************************************************
 * ==> PSS_App -------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the main application                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AppH
#define PSS_AppH

// processsoft
#include "PSS_MainApp.h"
#include "PSS_DocumentReadWrite.h"

// class name mapping
#ifndef PSS_WorkspaceEnv
    #define PSS_WorkspaceEnv ZBWorkspaceEnv
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_WorkspaceWizardTemplateManager
    #define PSS_WorkspaceWizardTemplateManager ZBWorkspaceWizardTemplateMg
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class ZIMainFrame;
class PSS_OutputWorkspace;
class PSS_ProcessWorkspace;
class ZVPropertiesWorkspace;
class PSS_WorkspaceEnvDocument;
class PSS_WorkspaceEnv;
class PSS_ProcessGraphModelDoc;
class PSS_WorkspaceWizardTemplateManager;
class PSS_UserEntityDocument;
class PSS_UserGroupEntity;
class PSS_LogicalSystemDocument;
class PSS_LogicalSystemEntity;
class PSS_LogicalPrestationsDocument;
class PSS_LogicalPrestationsEntity;
class PSS_LogicalRulesDocument;
class PSS_LogicalRulesEntity;
class PSS_RiskTypeContainer;
class PSS_RiskImpactContainer;
class PSS_RiskProbabilityContainer;

/**
* Application grid adapter
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_AppGridAdapter : public CGXAppAdapter
{
    public:
        PSS_AppGridAdapter();
        virtual ~PSS_AppGridAdapter();

        /**
        * Gets the document template
        *@param pViewClass - the view class type
        *@param pDocClass - the document class type
        *@return the document template
        */
        virtual CDocTemplate* GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass);

    protected:
        CMultiDocTemplate* m_pDocTemplate;
};

/**
* Main application
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_App : public PSS_MainApp, public PSS_AppGridAdapter
{
    DECLARE_DYNAMIC(PSS_App)

    public:
        typedef PSS_MainApp inherited;

        PSS_App();
        virtual ~PSS_App();

        /**
        * Gets the application instance
        *@return the application instance, NULL on error
        */
        static inline PSS_App* GetApp();

        /**
        * Initializes the instance
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitInstance();

        /**
        * Exits the instance
        *@return the instance result code
        */
        virtual int ExitInstance();

        /**
        * Releases the application
        */
        virtual void Release();

        /**
        * Updates the last loaded file name
        *@param fileName - the last loaded file name
        */
        virtual inline void UpdateLastLoadedFileName(const CString& fileName);

        /**
        * Gets the application name
        *@return the application name
        */
        virtual inline CString GetApplicationName() const;

        /**
        * Gets the application registry key
        *@return the application registry key
        */
        virtual inline CString GetApplicationRegistryKey() const;

        /**
        * Checks if the cursor capture is still valid
        *@param point - the cursor position
        *@param pView - the view
        *@return TRUE if the cursor capture is still valid, otherwise FALSE
        */
        virtual BOOL IsCursorCapturedValid(const CPoint& point, PSS_View* pView);

        /**
        * Gets the current document
        *@return the current document
        */
        virtual inline PSS_DocumentReadWrite* GetCurrentDocument() const;

        /**
        * Loads the application options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadApplicationOptions();

        /**
        * Saves the application options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveApplicationOptions();

        /**
        * Opens the workspace file
        *@param pFileName - the file name
        *@return the opened workspace document, NULL on error
        */
        virtual CDocument* OpenWorkspaceFile(LPCSTR pFileName);

        /**
        * Saves the workspace file
        *@param pFileName - the file name
        */
        virtual void SaveWorkspaceFile(LPCSTR pFileName);

        /**
        * Called when the properties should be refreshed
        */
        virtual void DoRefreshProperties();

        /**
        * Called when the symbols and properties should be refreshed
        */
        virtual void DoRefreshSymbolsAndProperties();

        /**
        * Gets the main frame
        *@return the main frame
        */
        virtual PSS_MainFrame* GetMainFrame();

        /**
        * Gets the output workspace
        *@return the output workspace
        */
        virtual PSS_OutputWorkspace* GetOutputWorkspace();

        /**
        * Gets the process workspace
        *@return the process workspace
        */
        virtual PSS_ProcessWorkspace* GetProcessWorkspace();

        /**
        * Gets the properties workspace
        *@return the properties workspace
        */
        virtual ZVPropertiesWorkspace* GetPropertiesWorkspace();

        /**
        * Gets the project window bar
        *@return the project window bar
        */
        virtual PSS_ProjectBar* GetProjectWindowBar();

        /**
        * Gets the tip of the day bar
        *@return the tip of the day bar
        */
        virtual PSS_TipOfDayBar* GetWndTipOfDayBar();

        /**
        * Gets the current workspace environment
        *@return the current workspace environment
        */
        virtual PSS_WorkspaceEnv* GetCurrentWorkspaceEnvironment();

        /**
        * Checks if the workspace environment exists
        *@return true if the workspace environment exists, otherwise false
        */
        virtual bool WorkspaceEnvironmentExist();

        /**
        * Checks if the workspace environment is loaded
        *@return true if the workspace environment is loaded, otherwise false
        */
        virtual bool IsWorkspaceEnvironmentLoaded();

        /**
        * Checks if the workspace environment was modified
        *@return true if the workspace environment was modified, otherwise false
        */
        virtual bool IsWorkspaceEnvironmentModified();

        /**
        * Closes the current workspace
        *@param askClosingDocument - if true, the user will be prompted before closing the document
        *@return true on success, otherwise false
        */
        virtual bool CloseCurrentWorkspace(bool askClosingDocument = false);

        /**
        * Closes the current workspace and allocates a new one
        *@return true on success, otherwise false
        */
        virtual bool CloseCurrentAndAllocateNewWorkspace();

        /**
        * Saves the current workspace
        *@return true on success, otherwise false
        */
        virtual bool SaveCurrentWorkspace();

        /**
        * Gets the user main group
        *@return the user main group
        */
        virtual PSS_UserGroupEntity* GetMainUserGroup();

        /**
        * Gets the user group file name
        *@return the user group file name
        */
        virtual inline CString GetUserGroupFileName() const;

        /**
        * Gets the logical system
        *@return the logical system
        */
        virtual PSS_LogicalSystemEntity* GetMainLogicalSystem();

        /**
        * Gets the logical system file name
        *@return the logical system file name
        */
        virtual inline CString GetLogicalSystemFileName() const;

        /**
        * Gets the logical prestations
        *@return the logical prestations
        */
        virtual PSS_LogicalPrestationsEntity* GetMainLogicalPrestations();

        /**
        * Gets the logical prestations file name
        *@return the logical prestations file name
        */
        virtual inline CString GetPrestationsFileName() const;

        /**
        * Gets the logical rules
        *@return the logical rules
        */
        virtual PSS_LogicalRulesEntity* GetMainLogicalRules();

        /**
        * Gets the logical rules file name
        *@return the logical rules file name
        */
        virtual inline CString GetRulesFileName() const;

        /**
        * Gets the risk type container
        *@return the risk type container
        */
        virtual inline PSS_RiskTypeContainer* GetRiskTypeContainer();

        /**
        * Loads the risk type file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadTypeRiskFile();

        /**
        * Gets the risk impact container
        *@return the risk impact container
        */
        virtual inline PSS_RiskImpactContainer* GetRiskImpactContainer();

        /**
        * Loads the risk impact file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadImpactRiskFile();

        /**
        * Gets the risk probability container
        *@return the risk probability container
        */
        virtual inline PSS_RiskProbabilityContainer* GetRiskProbabilityContainer();

        /**
        * Loads the risk probability file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadProbabilityRiskFile();

        /**
        * Gets the new model from the opened file
        *@return the new model document, NULL on error
        */
        virtual PSS_ProcessGraphModelDoc* FileNewModel();

        /**
        * Gets the main view
        *@return the main view
        */
        virtual inline PSS_View* GetMainView();

        /**
        * Refreshes the current schema
        */
        virtual inline void RefreshCurrentSchema();

        /**
        * Checks if the document is working locally
        *@return TRUE if the document is working locally, otherwise FALSE
        */
        virtual inline BOOL IsWorkingLocaly() const;

        /**
        * Checks if the document is read-only
        *@return TRUE if the document is read-only, otherwise FALSE
        */
        virtual inline BOOL ReadOnlyDocuments() const;

        /**
        * Opens the field repository in read only mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL OpenFieldRepositoryReadOnly() const;

        /**
        * Gets the application type
        *@return the application type
        */
        virtual inline PSS_Global::IEApplicationType GetApplicationType() const;

        /**
        * Checks if the system needs to authenticate the user before starting the application
        *@return TRUE if the system needs to authenticate the user before starting the application, otherwise FALSE
        */
        virtual inline BOOL UserAuthenticationRequired() const;

        /**
        * Gets if the system needs to load the user file
        *@return TRUE if the system needs to load the user file, otherwise FALSE
        */
        virtual inline BOOL LoadUserFile() const;

        /**
        * Exits the application
        *@return TRUE if the application is allowed to close, otherwise FALSE
        */
        virtual BOOL ExitApp();

        /**
        * Sets the visual tool object
        *@param className - the class name
        */
        virtual void SetVisualToolObject(const CString& className);

        /**
        * Gets the global ini file
        *@return the global ini file
        *@note This function is pure virtual
        */
        virtual CString GetGlobalIniFile() const;

        /**
        * Sets the global ini file
        *@return the global ini file
        *@note This function is pure virtual
        */
        virtual inline void SetGlobalIniFile(const CString& value);

        /**
        * Gets the workspace file name
        *@return the workspace file name
        */
        virtual inline CString GetWorkspaceFileName() const;

        /**
        * Gets the application ini file name
        *@return the application ini file name
        */
        virtual inline CString GetApplicationIniFileName() const;

        /**
        * Called when the application is idle
        *@param count - the idle time count in milliseconds
        *@return TRUE if the event handler has finished its background processing, otherwise FALSE
        */
        virtual BOOL OnIdle(LONG count);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_App)
        afx_msg void OnAppAbout();
        afx_msg void OnHelpSupport();
        afx_msg void OnAppExit();
        afx_msg void OnOptions();
        afx_msg void OnSelectServer();
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
        afx_msg void OnAssignCurrentSystemDef();
        afx_msg void OnUpdateAssignCurrentSystemDef(CCmdUI* pCmdUI);
        afx_msg void OnAssignCurrentUserDef();
        afx_msg void OnUpdateAssignCurrentUserDef(CCmdUI* pCmdUI);
        afx_msg void OnAssignCurrentPrestationsDef();
        afx_msg void OnUpdateAssignCurrentPrestationsDef(CCmdUI* pCmdUI);
        afx_msg void OnAssignCurrentRulesDef();
        afx_msg void OnUpdateAssignCurrentRulesDef(CCmdUI* pCmdUI);
        afx_msg void OnSymbolReassignUserGroup();
        afx_msg void OnUpdateSymbolReassignUserGroup(CCmdUI* pCmdUI);
        afx_msg void OnSymbolReassignLogicalSys();
        afx_msg void OnUpdateSymbolReassignLogicalSys(CCmdUI* pCmdUI);
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

        /**
        * Initializes the application
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitApp();

        /**
        * Post-initializes the application
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PostInitApp();

        /**
        * Loads the user group file
        *@return true on success, otherwise false
        */
        virtual bool LoadUserGroupFile();

        /**
        * Saves the user group file
        *@param askBeforeSave - if true, the user will be prompted before saving
        *@return true on success, otherwise false
        */
        virtual bool SaveUserGroupFile(bool askBeforeSave = true);

        /**
        * Loads the logical system file
        *@return true on success, otherwise false
        */
        virtual bool LoadLogicalSystemFile();

        /**
        * Saves the logical system file
        *@param askBeforeSave - if true, the user will be prompted before saving
        *@return true on success, otherwise false
        */
        virtual bool SaveLogicalSystemFile(bool askBeforeSave = true);

        /**
        * Loads the prestations file
        *@return true on success, otherwise false
        */
        virtual bool LoadPrestationsFile();

        /**
        * Saves the prestations file
        *@param askBeforeSave - if true, the user will be prompted before saving
        *@return true on success, otherwise false
        */
        virtual bool SavePrestationsFile(bool askBeforeSave = true);

        /**
        * Loads the rules file
        *@return true on success, otherwise false
        */
        virtual bool LoadRulesFile();

        /**
        * Saves the rules file
        *@param askBeforeSave - if true, the user will be prompted before saving
        *@return true on success, otherwise false
        */
        virtual bool SaveRulesFile(bool askBeforeSave = true);

        /**
        * Called when an additional template is opened
        *@param pFileName - the template file name
        *@return the opened template document
        */
        virtual CDocument* OnOpenAdditionalTemplateFile(LPCSTR pFileName);

        /**
        * Called when an additional template is saved
        *@param pFileName - the template file name
        */
        virtual void OnSaveAdditionalTemplateFile(LPCSTR pFileName);

        /**
        * Called when an additional template is registered
        *@return true on success, otherwise false
        */
        virtual bool OnRegisterAdditionalTemplate();

        /**
        * Called after the document is opened
        *@param pDoc - the document
        *@param fileName - the document file name
        */
        virtual void OnAfterOpenDocument(CDocument* pDoc, const CString& fileName);

        /**
        * Called after the document is saved
        *@param pDoc - the document
        */
        virtual void OnAfterSaveDocument(CDocument* pDoc);

        /**
        * Called when a server was selected
        */
        virtual void OnServerChanged();

        /**
        * Called when a server was opened
        */
        virtual void OnServerHasBeenOpened();

        /**
        * Called when the help file name is required
        *@return the help file name
        */
        virtual CString OnBuildHelpFileName();

    private:
        PSS_WorkspaceEnvDocument*           m_pWorkspaceEnvDocument;
        PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
        PSS_UserEntityDocument*             m_pUserEntityDocument;
        PSS_LogicalSystemDocument*          m_pLogicalSystemDocument;
        PSS_LogicalPrestationsDocument*     m_pPrestationsDocument;
        PSS_LogicalRulesDocument*           m_pRulesDocument;
        PSS_RiskTypeContainer*              m_pRiskTypeContainer;
        PSS_RiskImpactContainer*            m_pRiskImpactContainer;
        PSS_RiskProbabilityContainer*       m_pRiskProbabilityContainer;
        CString                             m_GlobalIniFile;
        CString                             m_WorkspaceFileName;
        CString                             m_UserGroupFileName;
        CString                             m_LogicalSystemFileName;
        CString                             m_PrestationsFileName;
        CString                             m_RulesFileName;
        CString                             m_GlobalHistoricValueFileName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_App(const PSS_App& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_App& operator = (const PSS_App& other);

        /**
        * Logs the start time to the output logs view
        */
        void LogStartTime();

        /**
        * Logs the end time to the output logs view
        */
        void LogEndTime();
};

//---------------------------------------------------------------------------
// PSS_App
//---------------------------------------------------------------------------
PSS_App* PSS_App::GetApp()
{
    return dynamic_cast<PSS_App*>(::AfxGetApp());
}
//---------------------------------------------------------------------------
void PSS_App::UpdateLastLoadedFileName(const CString& fileName)
{
    SetLastLoadedFileName(fileName);
}
//---------------------------------------------------------------------------
CString PSS_App::GetApplicationName() const
{
    return(_T("ProcessSoft-Conceptor"));
}
//---------------------------------------------------------------------------
CString PSS_App::GetApplicationRegistryKey() const
{
    return _T("SOFTWARE\\ProcessSoft\\Mercutio - Conceptor");
}
//---------------------------------------------------------------------------
PSS_DocumentReadWrite* PSS_App::GetCurrentDocument() const
{
    return (PSS_DocumentReadWrite*)m_pCurrentDocument;
}
//---------------------------------------------------------------------------
CString PSS_App::GetUserGroupFileName() const
{
    return m_UserGroupFileName;
}
//---------------------------------------------------------------------------
CString PSS_App::GetLogicalSystemFileName() const
{
    return m_LogicalSystemFileName;
}
//---------------------------------------------------------------------------
CString PSS_App::GetPrestationsFileName() const
{
    return m_PrestationsFileName;
}
//---------------------------------------------------------------------------
CString PSS_App::GetRulesFileName() const
{
    return m_RulesFileName;
}
//---------------------------------------------------------------------------
PSS_RiskTypeContainer* PSS_App::GetRiskTypeContainer()
{
    return m_pRiskTypeContainer;
}
//---------------------------------------------------------------------------
PSS_RiskImpactContainer* PSS_App::GetRiskImpactContainer()
{
    return m_pRiskImpactContainer;
}
//---------------------------------------------------------------------------
PSS_RiskProbabilityContainer* PSS_App::GetRiskProbabilityContainer()
{
    return m_pRiskProbabilityContainer;
}
//---------------------------------------------------------------------------
PSS_View* PSS_App::GetMainView()
{
    PSS_Document* pDoc = GetActiveDocument();

    if (!pDoc)
        return NULL;

    return pDoc->GetMainView();
}
//---------------------------------------------------------------------------
void PSS_App::RefreshCurrentSchema()
{
    PSS_Document* pDoc = GetActiveDocument();

    if (!pDoc)
        return;

    pDoc->RefreshCurrentSchema();
}
//---------------------------------------------------------------------------
BOOL PSS_App::IsWorkingLocaly() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::ReadOnlyDocuments() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::OpenFieldRepositoryReadOnly() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
PSS_Global::IEApplicationType PSS_App::GetApplicationType() const
{
    return PSS_Global::IE_AT_Process;
}
//---------------------------------------------------------------------------
BOOL PSS_App::UserAuthenticationRequired() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::LoadUserFile() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_App::SetGlobalIniFile(const CString& value)
{
    m_GlobalIniFile = value;
}
//---------------------------------------------------------------------------
CString PSS_App::GetWorkspaceFileName() const
{
    return m_WorkspaceFileName;
}
//---------------------------------------------------------------------------
CString PSS_App::GetApplicationIniFileName() const
{
    return m_pszProfileName;
}
//---------------------------------------------------------------------------

#endif
