/****************************************************************************
 * ==> PSS_App -------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the main application                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_App.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_MessageDlg.h"
#include "zBaseLib\PSS_VisualTool.h"
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_ObjectUtility.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_BaseMDIPage.h"
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_WorkspaceEnvDocument.h"
#include "zBaseLib\PSS_WorkspaceObserverMsg.h"
#include "zBaseLib\PSS_WorkspaceWizardTemplateManager.h"
#include "zBaseLib\PSS_ObjectUtility.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zWinUtil32\PSS_NewFormDialog.h"
#include "zWinUtil32\PSS_FolderInfoDialog.h"
#include "zWinUtil32\PSS_SystemOptionSheet.h"
#include "zResMgr\PSS_ResourceManager.h"
#include "zPtyMgr\PSS_SelectPropertyDlg.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphChildFrame.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_ProcessGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "zModel\PSS_SelectModelSymbolDlg.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zModel\PSS_UserEntityDocument.h"
#include "zModel\PSS_UserGroupObserverMsg.h"
#include "zModel\PSS_LogicalSystemDocument.h"
#include "zModel\PSS_LogicalSystemObserverMsg.h"
#include "zModel\PSS_LogicalPrestationsDocument.h"
#include "zModel\PSS_LogicalPrestationsObserverMsg.h"
#include "zModel\PSS_LogicalRulesDocument.h"
#include "zModel\PSS_LogicalRulesObserverMsg.h"
#include "zModel\PSS_ModelGlobal.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_ProcessGraphModelControllerBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_PublishToMessengerWizard.h"
#include "zModelBP\PSS_RiskTypeContainer.h"
#include "zModelBP\PSS_RiskImpactContainer.h"
#include "zModelBP\PSS_RiskProbabilityContainer.h"
#include "zModelWeb\PSS_PublishModelToHTML.h"
#include "zReport\PSS_GridReportChildFrame.h"
#include "zReport\PSS_GridReportDocument.h"
#include "zReport\PSS_GridReportView.h"
#include "zReportBP\PSS_CheckReportGenerator.h"
#include "zReportBP\PSS_MercutioReportGenerator.h"
#include "zReportBP\PSS_SesterceReportGenerator.h"
#include "zReportBP\PSS_SesterceUnitReportGenerator.h"
#include "zReportBP\PSS_SesterceConsolidatedReportGenerator.h"
#include "zReportBP\PSS_PrestationsReportGenerator.h"
#include "zReportBP\PSS_ReportCreationWizard.h"
#include "zReportBP\PSS_ConceptorReportGenerator.h"
#include "zReportWeb\PSS_PublishReportToHTML.h"
#include "zWeb\PSS_HtmlDialog.h"
#include "PSS_WelcomeProcessDlg.h"
#include "PSS_ModifyView.h"
#include "PSS_ModelWorkflowOptionsWizard.h"
#include "PSS_ConceptorReportOptionsDlg.h"
#include "PSS_ProcessWorkspace.h"
#include "PSS_OutputWorkspace.h"
#include "PSS_WorkspaceCreationWizard.h"

// stingray studio
#ifdef _OVDLL
    // define the Objective Views GUIDs. The GUIDs are declared in OdGuids.h.
    // Including initguid.h before OdGuids.h forces the GUIDs to be defined
    // in this module. Skip this if statically linking to the Objective Views
    // library, because the GUIDs will be linked into the app from the library
    #include "initguid.h"
    #include "Views\OdGuids.h"
    #include "Foundation\Compatibility\Common\CmnGuids.h"
#endif

// resources
#include "Resources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global instances
//---------------------------------------------------------------------------
PSS_App NEAR     g_App;
CODPropertyCache g_PropCache;
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static bool g_FirstTimeChangeServerDirectory = false;
//---------------------------------------------------------------------------
// PSS_AppGridAdapter
//---------------------------------------------------------------------------
PSS_AppGridAdapter::PSS_AppGridAdapter()
{
    m_pDocTemplate = NULL;
}
//---------------------------------------------------------------------------
PSS_AppGridAdapter::~PSS_AppGridAdapter()
{
    if (m_pDocTemplate)
    {
        m_pDocTemplate->CloseAllDocuments(TRUE);
        delete m_pDocTemplate;
    }
}
//---------------------------------------------------------------------------
CDocTemplate* PSS_AppGridAdapter::GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass)
{
    if (m_pDocTemplate)
        return m_pDocTemplate;

    m_pDocTemplate = new CMultiDocTemplate(IDR_MERCUTIOREPORT,
                                           RUNTIME_CLASS(PSS_GridReportDocument),
                                           RUNTIME_CLASS(PSS_GridReportChildFrame),
                                           RUNTIME_CLASS(PSS_GridReportView));

    return m_pDocTemplate;
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_App, PSS_MainApp)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_App, PSS_MainApp)
    //{{AFX_MSG_MAP(PSS_App)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(ID_HELP_SUPPORT, OnHelpSupport)
    ON_COMMAND(ID_APP_EXIT, OnAppExit)
    ON_COMMAND(ID_OPTIONS, OnOptions)
    ON_COMMAND(ID_SELECT_SERVER, OnSelectServer)
    ON_COMMAND(ID_FILE_NEWMODEL, OnFileNewModel)
    ON_COMMAND(ID_FILE_OPENMODEL, OnFileOpenModel)
    ON_UPDATE_COMMAND_UI(ID_FILE_NEWMODEL, OnUpdateFileNewModel)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_ALL, OnUpdadeFileSaveAll)
    ON_COMMAND(ID_NEW_WORKSPACE, OnNewWorkspace)
    ON_COMMAND(ID_OPEN_WORKSPACE, OnOpenWorkspace)
    ON_COMMAND(ID_SAVE_WORKSPACE, OnSaveWorkspace)
    ON_UPDATE_COMMAND_UI(ID_SAVE_WORKSPACE, OnUpdateSaveWorkspace)
    ON_COMMAND(ID_CLOSE_WORKSPACE, OnCloseWorkspace)
    ON_UPDATE_COMMAND_UI(ID_CLOSE_WORKSPACE, OnUpdateCloseWorkspace)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
    ON_COMMAND(ID_PROCESS_FILEOPEN, OnProcessFileOpen)
    ON_COMMAND(ID_WKS_NEWGROUP, OnWksNewGroup)
    ON_UPDATE_COMMAND_UI(ID_WKS_NEWGROUP, OnUpdateWksNewGroup)
    ON_COMMAND(ID_WKS_DELETEGROUP, OnWksDeleteGroup)
    ON_UPDATE_COMMAND_UI(ID_WKS_DELETEGROUP, OnUpdateWksDeleteGroup)
    ON_COMMAND(ID_WKS_RENAMEGROUP, OnWksRenameGroup)
    ON_UPDATE_COMMAND_UI(ID_WKS_RENAMEGROUP, OnUpdateWksRenameGroup)
    ON_COMMAND(ID_WKS_ADDFILE, OnWksAddFile)
    ON_UPDATE_COMMAND_UI(ID_WKS_ADDFILE, OnUpdateWksAddFile)
    ON_COMMAND(ID_WKS_DELETEFILE, OnWksDeleteFile)
    ON_UPDATE_COMMAND_UI(ID_WKS_DELETEFILE, OnUpdateWksDeleteFile)
    ON_COMMAND(ID_WKS_OPENFILE, OnWksOpenFile)
    ON_UPDATE_COMMAND_UI(ID_WKS_OPENFILE, OnUpdateWksOpenFile)
    ON_COMMAND(ID_WKS_ADD_CURRENTFILE, OnAddCurrentFileToProject)
    ON_UPDATE_COMMAND_UI(ID_WKS_ADD_CURRENTFILE, OnUpdateAddCurrentFileToProject)
    ON_COMMAND(ID_WKS_PROPERTIES, OnWksProperties)
    ON_UPDATE_COMMAND_UI(ID_WKS_PROPERTIES, OnUpdateWksProperties)
    ON_COMMAND(ID_UGP_ADDGROUP, OnUgpAddGroup)
    ON_UPDATE_COMMAND_UI(ID_UGP_ADDGROUP, OnUpdateUgpAddGroup)
    ON_COMMAND(ID_UGP_DELETEGROUP, OnUgpDeleteGroup)
    ON_UPDATE_COMMAND_UI(ID_UGP_DELETEGROUP, OnUpdateUgpDeleteGroup)
    ON_COMMAND(ID_UGP_RENAMEGROUP, OnUgpRenameGroup)
    ON_UPDATE_COMMAND_UI(ID_UGP_RENAMEGROUP, OnUpdateUgpRenameGroup)
    ON_COMMAND(ID_UGP_PROPERTIES, OnUgpProperties)
    ON_UPDATE_COMMAND_UI(ID_UGP_PROPERTIES, OnUpdateUgpProperties)
    ON_COMMAND(ID_UGP_ADDROLE, OnUgpAddRole)
    ON_UPDATE_COMMAND_UI(ID_UGP_ADDROLE, OnUpdateUgpAddRole)
    ON_COMMAND(ID_UGP_DELETEROLE, OnUgpDeleteRole)
    ON_UPDATE_COMMAND_UI(ID_UGP_DELETEROLE, OnUpdateUgpDeleteRole)
    ON_COMMAND(ID_UGP_RENAMEROLE, OnUgpRenameRole)
    ON_UPDATE_COMMAND_UI(ID_UGP_RENAMEROLE, OnUpdateUgpRenameRole)
    ON_COMMAND(ID_LS_ADDLOGICALSYSTEM, OnAddLogicalSystem)
    ON_UPDATE_COMMAND_UI(ID_LS_ADDLOGICALSYSTEM, OnUpdateAddLogicalSystem)
    ON_COMMAND(ID_LS_DELLOGICALSYSTEM, OnDeleteLogicalSystem)
    ON_UPDATE_COMMAND_UI(ID_LS_DELLOGICALSYSTEM, OnUpdateDeleteLogicalSystem)
    ON_COMMAND(ID_LS_RENAMELOGICALSYSTEM, OnRenameLogicalSystem)
    ON_UPDATE_COMMAND_UI(ID_LS_RENAMELOGICALSYSTEM, OnUpdateRenameLogicalSystem)
    ON_COMMAND(ID_LS_PROPLOGICALSYSTEM, OnLogicalSystemProperties)
    ON_UPDATE_COMMAND_UI(ID_LS_PROPLOGICALSYSTEM, OnUpdateLogicalSystemProperties)
    ON_COMMAND(ID_PR_ADDPRESTATION, OnAddPrestation)
    ON_UPDATE_COMMAND_UI(ID_PR_ADDPRESTATION, OnUpdateAddPrestation)
    ON_COMMAND(ID_PR_DELPRESTATION, OnDeletePrestation)
    ON_UPDATE_COMMAND_UI(ID_PR_DELPRESTATION, OnUpdateDeletePrestation)
    ON_COMMAND(ID_PR_RENAMEPRESTATION, OnRenamePrestation)
    ON_UPDATE_COMMAND_UI(ID_PR_RENAMEPRESTATION, OnUpdateRenamePrestation)
    ON_COMMAND(ID_PR_PROPPRESTATION, OnPrestationProperties)
    ON_UPDATE_COMMAND_UI(ID_PR_PROPPRESTATION, OnUpdatePrestationProperties)
    ON_COMMAND(ID_PR_ADDRULE, OnAddRule)
    ON_UPDATE_COMMAND_UI(ID_PR_ADDRULE, OnUpdateAddRule)
    ON_COMMAND(ID_PR_DELRULE, OnDeleteRule)
    ON_UPDATE_COMMAND_UI(ID_PR_DELRULE, OnUpdateDeleteRule)
    ON_COMMAND(ID_PR_RENAMERULE, OnRenameRule)
    ON_UPDATE_COMMAND_UI(ID_PR_RENAMERULE, OnUpdateRenameRule)
    ON_COMMAND(ID_PR_PROPRULE, OnRuleProperties)
    ON_UPDATE_COMMAND_UI(ID_PR_PROPRULE, OnUpdateRuleProperties)
    ON_COMMAND(ID_GENERATE_REPORT_CHECK, OnGenerateCheckReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_CHECK, OnUpdateGenerateCheckReport)
    ON_COMMAND(ID_GENERATE_REPORT_MERCUTIO, OnGenerateMercutioReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_MERCUTIO, OnUpdateGenerateMercutioReport)
    ON_COMMAND(ID_GENERATE_REPORT_CONCEPTOR, OnGenerateConceptorReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_CONCEPTOR, OnUpdateGenerateConceptorReport)
    ON_COMMAND(ID_GENERATE_REPORT_SESTERCE, OnGenerateSesterceReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_SESTERCE, OnUpdateGenerateSesterceReport)
    ON_COMMAND(ID_GENERATE_REPORT_SESTERCE_UNIT, OnGenerateSesterceUnitReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_SESTERCE_UNIT, OnUpdateGenerateSesterceReport)
    ON_COMMAND(ID_GENERATE_REPORT_SESTERCE_CONSOLIDATED, OnGenerateSesterceConsolidatedReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_SESTERCE_CONSOLIDATED, OnUpdateGenerateSesterceReport)
    ON_COMMAND(ID_GENERATE_REPORT_PRESTATIONS, OnGeneratePrestationsReport)
    ON_UPDATE_COMMAND_UI(ID_GENERATE_REPORT_PRESTATIONS, OnUpdateGeneratePrestationsReport)
    ON_COMMAND(ID_FILE_PROPERTY, OnFileProperty)
    ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTY, OnUpdateFileProperty)
    ON_COMMAND(ID_ASSIGN_CURRENTSYSTEMDEF, OnAssignCurrentSystemDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTSYSTEMDEF, OnUpdateAssignCurrentSystemDef)
    ON_COMMAND(ID_ASSIGN_CURRENTUSERDEF, OnAssignCurrentUserDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTUSERDEF, OnUpdateAssignCurrentUserDef)
    ON_COMMAND(ID_ASSIGN_CURRENTPRESTATIONSDEF, OnAssignCurrentPrestationsDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTPRESTATIONSDEF, OnUpdateAssignCurrentPrestationsDef)
    ON_COMMAND(ID_ASSIGN_CURRENTRULESDEF, OnAssignCurrentRulesDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTRULESDEF, OnUpdateAssignCurrentRulesDef)
    ON_COMMAND(ID_SYMBOL_REASSIGN_USERGROUP, OnSymbolReassignUserGroup)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_USERGROUP, OnUpdateSymbolReassignUserGroup)
    ON_COMMAND(ID_SYMBOL_REASSIGN_LOGICALSYS, OnSymbolReassignLogicalSys)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_LOGICALSYS, OnUpdateSymbolReassignLogicalSys)
    ON_COMMAND(ID_SYMBOL_REASSIGN_PRESTATIONS, OnSymbolReassignPrestations)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_PRESTATIONS, OnUpdateSymbolReassignPrestations)
    ON_COMMAND(ID_SYMBOL_REASSIGN_RULES, OnSymbolReassignRules)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_RULES, OnUpdateSymbolReassignRules)
    ON_COMMAND(ID_PUBLISH_TOMESSENGER, OnPublishToMessenger)
    ON_UPDATE_COMMAND_UI(ID_PUBLISH_TOMESSENGER, OnUpdatePublishToMessenger)
    ON_COMMAND(ID_DYNATTR_DISPLAY, OnDynamicAttributesDisplay)
    ON_UPDATE_COMMAND_UI(ID_DYNATTR_DISPLAY, OnUpdateDynamicAttributesDisplay)
    ON_COMMAND(ID_EXPORTHTML, OnExportModelToHTMLFile)
    ON_UPDATE_COMMAND_UI(ID_EXPORTHTML, OnUpdateExportModelToHTMLFile)
    ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
    ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_App
//---------------------------------------------------------------------------
PSS_App::PSS_App() :
    PSS_MainApp(),
    PSS_AppGridAdapter(),
    m_pWorkspaceEnvDocument(NULL),
    m_pWorkspaceTemplateManager(NULL),
    m_pUserEntityDocument(NULL),
    m_pLogicalSystemDocument(NULL),
    m_pPrestationsDocument(NULL),
    m_pRulesDocument(NULL),
    m_pRiskTypeContainer(NULL),
    m_pRiskImpactContainer(NULL),
    m_pRiskProbabilityContainer(NULL)
{
    m_SplashID  = IDB_SPLASHLOGO_2000;
    m_AboutID   = IDB_SPLASHLOGO;
    m_SupportID = IDB_SPLASHLOGO;

    // assign DDE names
    m_CppServerName = _T("DDE_ZPROCESS_NAME");
    m_CppTopicName  = _T("DDE_ZPROCESS_TOPIC");

    PSS_Application* pApplication = PSS_Application::Instance();

    if (!pApplication)
        throw new std::runtime_error("Application instance could not be created");

    // register this class in the mediator
    pApplication->RegisterMainForm(this);
}
//---------------------------------------------------------------------------
PSS_App::PSS_App(const PSS_App& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_App::~PSS_App()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function during destruction
    PSS_App::Release();

    PSS_Application* pApplication = PSS_Application::Instance();

    if (!pApplication)
        ::OutputDebugString("Application instance was no longer accessible on destruction");

    if (pApplication)
    {
        pApplication->UnregisterMainForm();
        pApplication->Release();
    }
}
//---------------------------------------------------------------------------
const PSS_App& PSS_App::operator = (const PSS_App& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_App::InitInstance()
{
    return PSS_MainApp::InitInstance();
}
//---------------------------------------------------------------------------
int PSS_App::ExitInstance()
{
    return PSS_MainApp::ExitInstance();
}
//---------------------------------------------------------------------------
void PSS_App::Release()
{
    if (m_pWorkspaceEnvDocument)
    {
        delete m_pWorkspaceEnvDocument;
        m_pWorkspaceEnvDocument = NULL;
    }

    if (m_pWorkspaceTemplateManager)
    {
        delete m_pWorkspaceTemplateManager;
        m_pWorkspaceTemplateManager = NULL;
    }

    if (m_pUserEntityDocument)
    {
        delete m_pUserEntityDocument;
        m_pUserEntityDocument = NULL;
    }

    if (m_pLogicalSystemDocument)
    {
        delete m_pLogicalSystemDocument;
        m_pLogicalSystemDocument = NULL;
    }

    if (m_pPrestationsDocument)
    {
        delete m_pPrestationsDocument;
        m_pPrestationsDocument = NULL;
    }

    if (m_pRulesDocument)
    {
        delete m_pRulesDocument;
        m_pRulesDocument = NULL;
    }

    if (m_pRiskTypeContainer)
    {
        delete m_pRiskTypeContainer;
        m_pRiskTypeContainer = NULL;
    }

    if (m_pRiskImpactContainer)
    {
        delete m_pRiskImpactContainer;
        m_pRiskImpactContainer = NULL;
    }

    if (m_pRiskProbabilityContainer)
    {
        delete m_pRiskProbabilityContainer;
        m_pRiskProbabilityContainer = NULL;
    }

    // cleanup the strings otherwise memory leaks may happen
    m_GlobalIniFile.Empty();
    m_WorkspaceFileName.Empty();
    m_UserGroupFileName.Empty();
    m_LogicalSystemFileName.Empty();
    m_PrestationsFileName.Empty();
    m_RulesFileName.Empty();
    m_GlobalHistoricValueFileName.Empty();

    // release the static objets
    PSS_Global::Release();
    PSS_ModelGlobal::Release();
    PSS_ObjectUtility::Release();
    PSS_ResourceManager::Release();
    PSS_FloatingToolBar::Release();

    // call the function in the base class
    PSS_MainApp::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_App::IsCursorCapturedValid(const CPoint& point, PSS_View* pView)
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::LoadApplicationOptions()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::SaveApplicationOptions()
{
    return TRUE;
}
//---------------------------------------------------------------------------
CDocument* PSS_App::OpenWorkspaceFile(LPCSTR pFileName)
{
    if (!CloseCurrentAndAllocateNewWorkspace())
        return NULL;

    // open the new workspace
    if (!m_pWorkspaceEnvDocument->ReadFromFile(pFileName))
        // todo -cFeature -oJean: show error message
        return NULL;

    PSS_WorkspaceEnv* pEnv = GetCurrentWorkspaceEnvironment();

    if (!pEnv)
        // todo -cFeature -oJean: show error message
        return NULL;

    // set the new workspace file name
    m_WorkspaceFileName = pFileName;

    // notify observers about the workspace initialisation
    PSS_WorkspaceObserverMsg msg(UM_INITWORKSPACE, pEnv);
    NotifyAllObservers(&msg);

    return m_pWorkspaceEnvDocument;
}
//---------------------------------------------------------------------------
void PSS_App::SaveWorkspaceFile(LPCSTR pFileName)
{
    ASSERT(m_pWorkspaceEnvDocument);

    // save the workspace document
    m_pWorkspaceEnvDocument->SaveToFile(pFileName);

    // reset the modified flag
    m_pWorkspaceEnvDocument->SetModifiedFlag(FALSE);
}
//---------------------------------------------------------------------------
void PSS_App::DoRefreshProperties()
{
    PSS_ProcessModelDocTmpl* pDocTmpl = PSS_Global::GetProcessModelDocumentTemplate();

    if (!pDocTmpl)
        return;

    POSITION pPosition = pDocTmpl->GetFirstDocPosition();

    while (pPosition)
    {
        PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocTmpl->GetNextDoc(pPosition));

        if (!pGraphModelDoc)
            continue;

        PSS_ProcessGraphModelView* pGraphModelView = pGraphModelDoc->GetFirstModelView();

        if (!pGraphModelView)
            continue;

        PSS_ProcessGraphModelController* pModelController = pGraphModelView->GetModelController();

        if (!pModelController)
            continue;

        pModelController->RefreshSelectionProperties();
    }
}
//---------------------------------------------------------------------------
void PSS_App::DoRefreshSymbolsAndProperties()
{
    PSS_ProcessModelDocTmpl* pDocTmpl = PSS_Global::GetProcessModelDocumentTemplate();

    if (!pDocTmpl)
        return;

    POSITION pPosition = pDocTmpl->GetFirstDocPosition();

    while (pPosition)
    {
        PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocTmpl->GetNextDoc(pPosition));

        if (!pGraphModelDoc)
            continue;

        PSS_ProcessGraphModelView* pGraphModelView = pGraphModelDoc->GetFirstModelView();

        if (!pGraphModelView)
            continue;

        PSS_ProcessGraphModelController* pModelController = pGraphModelView->GetModelController();

        if (!pModelController)
            continue;

        pModelController->RefreshAllSymbols();
        pModelController->RefreshSelectionProperties();
    }
}
//---------------------------------------------------------------------------
PSS_MainFrame* PSS_App::GetMainFrame()
{
    return dynamic_cast<PSS_MainFrame*>(::AfxGetMainWnd());
}
//---------------------------------------------------------------------------
PSS_OutputWorkspace* PSS_App::GetOutputWorkspace()
{
    PSS_MainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return pFrame->GetOutputWorkspace();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessWorkspace* PSS_App::GetProcessWorkspace()
{
    PSS_MainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return pFrame->GetWorkspace();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertiesWorkspace* PSS_App::GetPropertiesWorkspace()
{
    PSS_MainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return pFrame->GetPropertiesWorkspace();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProjectBar* PSS_App::GetProjectWindowBar()
{
    PSS_MainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return &pFrame->GetProjectWindowBar();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_TipOfDayBar* PSS_App::GetWndTipOfDayBar()
{
    PSS_MainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return &pFrame->GetwndTipOfDayBar();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_WorkspaceEnv* PSS_App::GetCurrentWorkspaceEnvironment()
{
    return (m_pWorkspaceEnvDocument ? &m_pWorkspaceEnvDocument->GetWorkspaceEnvironment() : NULL);
}
//---------------------------------------------------------------------------
bool PSS_App::WorkspaceEnvironmentExist()
{
    return m_pWorkspaceEnvDocument;
}
//---------------------------------------------------------------------------
bool PSS_App::IsWorkspaceEnvironmentLoaded()
{
    return (m_pWorkspaceEnvDocument && m_pWorkspaceEnvDocument->IsLoaded());
}
//---------------------------------------------------------------------------
bool PSS_App::IsWorkspaceEnvironmentModified()
{
    // return the flag of the document and the environement
    if (m_pWorkspaceEnvDocument)
        return m_pWorkspaceEnvDocument->IsModified();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_App::CloseCurrentWorkspace(bool askClosingDocument)
{
    if (WorkspaceEnvironmentExist())
    {
        if (IsWorkspaceEnvironmentLoaded())
        {
            if (!SaveCurrentWorkspace())
                return false;

            if (askClosingDocument)
            {
                PSS_MsgBox mBox;

                if (mBox.Show(IDS_CONF_CLOSEALLDOCS_CURRENT_WKSPACE, MB_YESNO) == IDYES)
                {
                    // save all modified documents
                    if (!SaveAllModified())
                        return false;

                    if (GetOutputWorkspace())
                        GetOutputWorkspace()->DetachAllObservers();

                    // close all documents
                    CloseAllDocuments(FALSE);
                }
            }
            else
            {
                // save all modified documents
                if (!SaveAllModified())
                    return false;

                if (GetOutputWorkspace())
                    GetOutputWorkspace()->DetachAllObservers();

                // close all documents
                CloseAllDocuments(TRUE);
            }
        }

        // before deleting the workspace environment, set the last open file to the workspace file name
        if (m_pWorkspaceEnvDocument)
        {
            SetLastLoadedFileName(m_pWorkspaceEnvDocument->GetPathName());
            delete m_pWorkspaceEnvDocument;
        }

        m_pWorkspaceEnvDocument = NULL;

        // notify observers about the workspace closing
        PSS_WorkspaceObserverMsg msg(UM_CLOSEWORKSPACE);
        NotifyAllObservers(&msg);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::CloseCurrentAndAllocateNewWorkspace()
{
    // check if the workspace is already opened
    if (WorkspaceEnvironmentExist())
        // ask before closing all open documents
        if (!CloseCurrentWorkspace(true))
            return false;

    // allocate a new workspace
    m_pWorkspaceEnvDocument = new PSS_WorkspaceEnvDocument();

    return m_pWorkspaceEnvDocument;
}
//---------------------------------------------------------------------------
bool PSS_App::SaveCurrentWorkspace()
{
    bool result = true;

    if (WorkspaceEnvironmentExist() && IsWorkspaceEnvironmentLoaded())
    {
        ASSERT(m_pWorkspaceEnvDocument);

        // set the loaded files
        if (GetCurrentWorkspaceEnvironment())
        {
            CStringArray fileArray;
            GetDocumentArrayName(fileArray);
            GetCurrentWorkspaceEnvironment()->SetOpenedFiles(fileArray);
        }

        // save the document
        if (!m_pWorkspaceEnvDocument->SaveToFile(m_WorkspaceFileName))
            result = false;

        // reset the modified flag
        m_pWorkspaceEnvDocument->SetModifiedFlag(FALSE);

        // set the last open file as the workspace file name
        SetLastLoadedFileName(m_pWorkspaceEnvDocument->GetPathName());
    }

    return result;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_App::GetMainUserGroup()
{
    return (m_pUserEntityDocument ? &m_pUserEntityDocument->GetUserGroupEnvironment() : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_App::GetMainLogicalSystem()
{
    return (m_pLogicalSystemDocument ? &m_pLogicalSystemDocument->GetLogicalSystemEnvironment() : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_App::GetMainLogicalPrestations()
{
    return (m_pPrestationsDocument ? &m_pPrestationsDocument->GetPrestationsEnvironment() : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_App::GetMainLogicalRules()
{
    return (m_pRulesDocument ? &m_pRulesDocument->GetRulesEnvironment() : NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_App::LoadTypeRiskFile()
{
    if (!m_pRiskTypeContainer)
    {
        m_pRiskTypeContainer = new PSS_RiskTypeContainer();

        if (!m_pRiskTypeContainer->LoadFile(GetApplicationOptions().GetRiskTypeFileName()))
            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::LoadImpactRiskFile()
{
    if (!m_pRiskImpactContainer)
    {
        m_pRiskImpactContainer = new PSS_RiskImpactContainer();

        if (!m_pRiskImpactContainer->LoadFile(GetApplicationOptions().GetRiskImpactFileName()))
            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::LoadProbabilityRiskFile()
{
    if (!m_pRiskProbabilityContainer)
    {
        m_pRiskProbabilityContainer = new PSS_RiskProbabilityContainer();

        if (!m_pRiskProbabilityContainer->LoadFile(GetApplicationOptions().GetRiskProbabilityFileName()))
            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc* PSS_App::FileNewModel()
{
    ASSERT(PSS_Global::GetProcessModelDocumentTemplate());

    CWaitCursor cursor;

    PSS_ProcessGraphModelDoc* pNewFile =
            dynamic_cast<PSS_ProcessGraphModelDoc*>(PSS_Global::GetProcessModelDocumentTemplate()->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NORMALTEMPLATE_NF, MB_OK);
        return NULL;
    }

    PSS_DocumentPageSetup* pPageSetup = pNewFile->GetPrinterPageSize();

    if (pPageSetup)
        if (pPageSetup->IsCancelled())
        {
            pNewFile->OnCloseDocument();
            return NULL;
        }

    PSS_ModelWorkflowOptionsWizard wizard(FALSE, pNewFile);

    if (wizard.DoModal() == IDCANCEL)
    {
        pNewFile->OnCloseDocument();
        return NULL;
    }

    switch (pNewFile->GetNotation())
    {
        case E_MN_Beryl:
        {
            // get the language assigned to the document
            const ELanguage language = pNewFile->GetLanguage();
            pNewFile->SetNewModel(new PSS_ProcessGraphModelMdlBP(pNewFile->GetTitle()));

            // set the language to the document
            pNewFile->SetLanguage(language);
            break;
        }

        case E_MN_ABC: break;
        case E_MN_UML: break;
        default:       break;
    }

    // set the type for Template
    pNewFile->SetFileType(PSS_Stamp::IE_FD_TemplateType);

    // set the path name to empty (NOTE no path name yet)
    pNewFile->ClearPathName();

    // assign the main user group
    pNewFile->AssignMainUserGroup(GetMainUserGroup());

    // assign the main logical system
    pNewFile->AssignMainLogicalSystem(GetMainLogicalSystem());

    // Assign the prestations system
    pNewFile->AssignMainLogicalPrestations(GetMainLogicalPrestations());

    // assign the rules system
    pNewFile->AssignMainLogicalRules(GetMainLogicalRules());

    // assign the current system def, user def, prestations def, and rules def
    pNewFile->AssignCurrentSystemDefGUID();
    pNewFile->AssignCurrentUserDefGUID();
    pNewFile->AssignCurrentPrestationsDefGUID();
    pNewFile->AssignCurrentRulesDefGUID();

    // set the background image
    if (pPageSetup)
        if (!pPageSetup->GetBackgroundFileName().IsEmpty())
            pNewFile->GetFirstModelView()->GetViewport()-> GetModelController()->SetImage(pPageSetup->GetBackgroundFileName(),
                                                                                          FALSE);

    return pNewFile;
}
//---------------------------------------------------------------------------
BOOL PSS_App::ExitApp()
{
    if (!PSS_Global::SaveToFileHistoricValue(m_GlobalHistoricValueFileName))
    {
        // todo -cFeature -oJean: Warn the user
    }

    // save the global state for model
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);
    PSS_ModelGlobal::SaveGlobalPropertyAttributes();

    // close the current workspace
    if (!CloseCurrentWorkspace())
        return FALSE;

    // save the user group file
    if (!SaveUserGroupFile())
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_USERGROUPFILE, MB_OK);
        return FALSE;
    }

    // save the logical system file
    if (!SaveLogicalSystemFile())
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_LOGICALSYSTEMFILE, MB_OK);
        return FALSE;
    }

    // save the prestations file
    if (!SavePrestationsFile())
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_PRESTATIONSFILE, MB_OK);
        return FALSE;
    }

    // save the rules file
    if (!SaveRulesFile())
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_RULESFILE, MB_OK);
        return FALSE;
    }

    PSS_ApplicationOption& appOptions = GetApplicationOptions();

    // set the risk files
    appOptions.SetRiskTypeFileName(m_pRiskTypeContainer->GetFileName());
    appOptions.SetRiskImpactFileName(m_pRiskImpactContainer->GetFileName());
    appOptions.SetRiskProbabilityFileName(m_pRiskProbabilityContainer->GetFileName());

    return PSS_MainApp::ExitApp();
}
//---------------------------------------------------------------------------
void PSS_App::SetVisualToolObject(const CString& className)
{
    // find the class
    const CStringArray& strArray   = PSS_ObjectUtility::GetClassNameArray();
    int                 index      = 0;
    const int           arrayCount = strArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
    {
        index = i;

        if (className == strArray.GetAt(i))
            break;
    }

    // set the appropriate tool
    switch (index)
    {
        case 0:  PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IE_TT_VToolSelect; break;
        default: PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IE_TT_VToolEdit;   break;
    }
}
//---------------------------------------------------------------------------
CString PSS_App::GetGlobalIniFile() const
{
    return m_GlobalIniFile;
}
//---------------------------------------------------------------------------
BOOL PSS_App::OnIdle(LONG count)
{
    // todo FIXME -cBug -oJean: There is a strange bug here, sometimes when all
    //                          the children documents are closed on the MDI frame,
    //                          an access violation happens here. This seems related
    //                          to the multithreading and the usage of the m_pMainWnd
    //                          variable
    if (!count)
        if (m_pMainWnd)
        {
            // look for any top-level windows owned by this class. NOTE handlers are used to
            // avoid generation of too many temporary CWnds
            for (HWND hWnd = ::GetWindow(m_pMainWnd->m_hWnd, GW_HWNDFIRST); hWnd; hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT))
                if (::GetParent(hWnd) == m_pMainWnd->m_hWnd)
                {
                    // if owned window is active, move the activation to the application window
                    if (GetActiveWindow() == hWnd && !::GetCapture())
                        m_pMainWnd->SetActiveWindow();

                    // update the buttons for the top-level window
                    ::SendMessage(hWnd, WM_IDLEUPDATECMDUI, WPARAM(TRUE), 0L);
                }
        }

    return CWinApp::OnIdle(count);
}
//---------------------------------------------------------------------------
void PSS_App::OnAppAbout()
{
    PSS_HtmlDialog about(IDR_ABOUT_CONCEPTOR_02);
    about.SetSize(600, 600);
    about.DoModal();
}
//---------------------------------------------------------------------------
void PSS_App::OnHelpSupport()
{
    PSS_HtmlDialog about(IDR_SUPPORT_CONCEPTOR_02);
    about.SetSize(600, 600);
    about.DoModal();
}
//---------------------------------------------------------------------------
void PSS_App::OnAppExit()
{
    PSS_MainFrame* pMainFrame = GetMainWindow();

    // close the window. To go out the Windows pump message, post again the close message
    if (pMainFrame && pMainFrame->PointerWindowIsVisible())
    {
        pMainFrame->HidePointerWindow();
        pMainFrame->PostMessage(WM_CLOSE);
        return;
    }

    CWinApp::OnAppExit();
}
//---------------------------------------------------------------------------
void PSS_App::OnOptions()
{
    PSS_SystemOptionSheet systemOptionsSheet(&GetApplicationOptions(),
                                             PSS_SystemOptionSheet::IEOptionPage(PSS_SystemOptionSheet::IE_OP_General     |
                                                                                 PSS_SystemOptionSheet::IE_OP_Calculation |
                                                                                 PSS_SystemOptionSheet::IE_OP_Navigation  |
                                                                                 PSS_SystemOptionSheet::IE_OP_ViewReduced));

    // options have changed?
    if (systemOptionsSheet.DoModal() == IDOK)
    {
        // refresh the views
        CObList docList;
        GetDocumentList(docList);

        // iterate through the list in head-to-tail order
        for (POSITION pPos = docList.GetHeadPosition(); pPos;)
        {
            CDocument* pDocument = dynamic_cast<CDocument*>(docList.GetNext(pPos));

            if (pDocument)
                pDocument->UpdateAllViews(NULL);
        }

        // save options immediately
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnSelectServer()
{
    SelectServer();
}
//---------------------------------------------------------------------------
void PSS_App::OnFileNewModel()
{
    // call the file creation function
    FileNewModel();

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();
}
//---------------------------------------------------------------------------
void PSS_App::OnFileOpenModel()
{
    ASSERT(PSS_Global::GetProcessModelDocumentTemplate() != NULL);

    // prompt the user (with all document templates)
    CString       newName;
    const CString initialDirectory = (g_FirstTimeChangeServerDirectory ? _T("") : GetModelTemplateDirectory());

    if (!DoPromptFileName(newName,
                          initialDirectory,
                          AFX_IDS_OPENFILE,
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                          TRUE,
                          PSS_Global::GetProcessModelDocumentTemplate()))
        // open cancelled
        return;

    CWaitCursor cursor;

    PSS_ProcessGraphModelDoc* pOpenFile = dynamic_cast<PSS_ProcessGraphModelDoc*>(OpenDocumentFile(newName));

    if (pOpenFile)
    {
        // add the opened file to recent file list
        PSS_Global::GetProcessModelDocumentTemplate()->AddToRecentFileList(newName);

        // set the last loaded file
        SetLastLoadedFileName(newName);
    }

    g_FirstTimeChangeServerDirectory = true;
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFileOpenModel(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFileNewModel(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    CDocument* pDocument = GetActiveCDocument();

    pCmdUI->Enable(pDocument && pDocument->IsModified());
}
//---------------------------------------------------------------------------
void PSS_App::OnFileSaveAll()
{
    // save the user group file
    if (!SaveUserGroupFile(false))
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_USERGROUPFILE, MB_OK);
    }

    // save the logical system file
    if (!SaveLogicalSystemFile(false))
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_LOGICALSYSTEMFILE, MB_OK);
    }

    // save the prestations file
    if (!SavePrestationsFile(false))
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_PRESTATIONSFILE, MB_OK);
    }

    // save the rules file
    if (!SaveRulesFile(false))
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_RULESFILE, MB_OK);
    }

    // a strange error message is shown if the file name is empty. To avoid that, this situation is also handled
    if (!m_GlobalHistoricValueFileName.IsEmpty())
        // save all historic values
        if (!PSS_Global::SaveToFileHistoricValue(m_GlobalHistoricValueFileName))
        {
            // warn the user
            PSS_MsgBox mBox;
            mBox.Show(IDS_FAILSAVE_INTERNALDEFINITION, MB_OK);
        }

    // save the current workspace
    if (!SaveCurrentWorkspace())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_WORKSPACE, MB_OK);
    }

    // save all modified documents
    if (!SaveAllModifiedNoPrompt())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_OPENDOCUMENT, MB_OK);
    }

    // save the global state for model
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);
    PSS_ModelGlobal::SaveGlobalPropertyAttributes();

    // save the application options
    if (!GetApplicationOptions().SaveOption())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_INTERNALDEFINITION, MB_OK);
    }

    if (!SaveApplicationOptions())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_INTERNALDEFINITION, MB_OK);
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdadeFileSaveAll(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_App::OnNewWorkspace()
{
    if (!CloseCurrentAndAllocateNewWorkspace())
        return;

    // start wizard for new workspace
    PSS_WorkspaceCreationWizard workspaceCreation(m_pWorkspaceTemplateManager, GetModelTemplateDirectory(), g_WorkspaceExtension);

    if (workspaceCreation.DoModal() == IDOK)
    {
        PSS_ProcessGraphModelDoc* pNewFile = NULL;
        CString                   modelFileName;

        if (workspaceCreation.GetWorkspaceName() == _T("Projet vide"))
        {
            // nothing to create
        }
        else
        if (workspaceCreation.GetWorkspaceName() == _T("Projet de base") ||
            workspaceCreation.GetWorkspaceName() == _T("Projet Sesterce"))
        {
            // create the basic workspace
            pNewFile = FileNewModel();

            if (pNewFile)
            {
                // set the file name
                modelFileName  = PSS_Directory::NormalizeDirectory(workspaceCreation.GetDirectory()) + _T("\\");
                modelFileName += workspaceCreation.GetWorkspaceName();
                modelFileName += g_ModelExtension;

                pNewFile->SetPathName(modelFileName);
                pNewFile->SetModifiedFlag(TRUE);

                // save the file name
                pNewFile->DoFileSave();
            }
            else
            {
                // todo -cFeature -oJean: show error
            }

            // only for sesterce project
            if (workspaceCreation.GetWorkspaceName() == _T("Projet Sesterce"))
            {
                // todo -cFeature -oJean: show error
            }
        }

        PSS_WorkspaceEnv* pEnv = GetCurrentWorkspaceEnvironment();

        if (pEnv)
        {
            // set the environment name
            pEnv->SetEntityName(workspaceCreation.GetWorkspaceName());

            CString str;

            // Create the model group
            str.LoadString(IDS_WKS_GROUP_MODEL);

            CStringArray strArray;
            strArray.Add(g_ModelExtensionNoDot);
            pEnv->AddGroup(str, &strArray);

            if (pNewFile)
                // add the new create model file
                pEnv->AddFile(modelFileName, str);

            // create the report group
            str.LoadString(IDS_WKS_GROUP_REPORT);
            strArray.RemoveAll();
            strArray.Add(g_ReportExtensionNoDot);
            pEnv->AddGroup(str, &strArray);

            // create the document group
            str.LoadString(IDS_WKS_GROUP_DOCUMENT);
            strArray.RemoveAll();
            strArray.Add(_T("doc"));
            strArray.Add(_T("xls"));
            strArray.Add(_T("ppt"));
            strArray.Add(_T("htm"));
            strArray.Add(_T("html"));
            strArray.Add(_T("pdf"));
            pEnv->AddGroup(str, &strArray);

            // notify observers about the workspace initialisation
            PSS_WorkspaceObserverMsg msg(UM_INITWORKSPACE, pEnv);
            NotifyAllObservers(&msg);
        }

        // set the workspace file name
        m_WorkspaceFileName = workspaceCreation.GetWorkspaceFileName();
        m_pWorkspaceEnvDocument->SetLoaded(true);

        // save it
        SaveCurrentWorkspace();
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnOpenWorkspace()
{
    if (!CloseCurrentAndAllocateNewWorkspace())
        return;

    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return;

    CString title;
    VERIFY(title.LoadString(IDS_WORKSPACE_FILEOPEN_T));

    // set the "*.klf" files filter
    CString filter;
    VERIFY(filter.LoadString(IDS_WORKSPACEFILE_FILTER));
    filter += (char)'\0';
    filter += _T("*.klf");
    filter += (char)'\0';

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 2, pApp->GetModelTemplateDirectory());

    if (fileDialog.DoModal() == IDOK)
    {
        CWaitCursor Cursor;
        OpenWorkspaceFile(fileDialog.GetFileName());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnSaveWorkspace()
{
    CWaitCursor cursor;
    SaveCurrentWorkspace();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateSaveWorkspace(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(WorkspaceEnvironmentExist()    &&
                   IsWorkspaceEnvironmentLoaded() &&
                   IsWorkspaceEnvironmentModified());
}
//---------------------------------------------------------------------------
void PSS_App::OnCloseWorkspace()
{
    // ask before closing all open documents
    CloseCurrentWorkspace(true);
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateCloseWorkspace(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(WorkspaceEnvironmentExist() && IsWorkspaceEnvironmentLoaded());
}
//---------------------------------------------------------------------------
void PSS_App::OnFileOpen()
{
    PSS_MainApp::OnFileOpen();
}
//---------------------------------------------------------------------------
void PSS_App::OnProcessFileOpen()
{
    ASSERT(FALSE);
    return;
}
//---------------------------------------------------------------------------
void PSS_App::OnWksNewGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    pTreeCtrl->OnWksNewGroup();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksNewGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pTreeCtrl->GetSelectedGroup() || pTreeCtrl->IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_App::OnWksDeleteGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_CONF_WKS_DELETEGROUP, MB_YESNO) == IDNO)
        return;

    pTreeCtrl->OnWksDeleteGroup();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksDeleteGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(BOOL(pTreeCtrl->GetSelectedGroup()));
}
//---------------------------------------------------------------------------
void PSS_App::OnWksRenameGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    pTreeCtrl->OnWksRenameGroup();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksRenameGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(BOOL(pTreeCtrl->GetSelectedGroup()));
}
//---------------------------------------------------------------------------
void PSS_App::OnWksAddFile()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    pTreeCtrl->OnWksAddFile();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksAddFile(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pTreeCtrl->GetSelectedGroup() || pTreeCtrl->IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_App::OnWksDeleteFile()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_CONF_WKS_DELETEFILE, MB_YESNO) == IDNO)
        return;

    pTreeCtrl->OnWksDeleteFile();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksDeleteFile(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(BOOL(pTreeCtrl->GetSelectedFile()));
}
//---------------------------------------------------------------------------
void PSS_App::OnWksOpenFile()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    pTreeCtrl->OnWksOpenFile();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksOpenFile(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(BOOL(pTreeCtrl->GetSelectedFile()));
}
//---------------------------------------------------------------------------
void PSS_App::OnAddCurrentFileToProject()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    CDocument*    pDoc            = GetActiveCDocument();
    const CString currentFileName = (pDoc ? pDoc->GetPathName() : _T(""));

    if (currentFileName.IsEmpty())
        return;

    // if the file is modified, save it first
    if (pDoc && pDoc->IsModified())
        if (!pDoc->OnSaveDocument(currentFileName))
            // Warn the user
            return;

    pTreeCtrl->OnAddFileToProject(currentFileName);
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAddCurrentFileToProject(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    CDocument*    pDoc            = GetActiveCDocument();
    const CString currentFileName = (pDoc ? pDoc->GetPathName() : _T(""));

    pCmdUI->Enable(!currentFileName.IsEmpty() && pTreeCtrl->CanAddCurrentFileToProject(currentFileName));
}
//---------------------------------------------------------------------------
void PSS_App::OnWksProperties()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
        return;

    pTreeCtrl->OnWksProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateWksProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_WorkspaceTreeCtrl* pTreeCtrl = pWorkspace->GetWorkspaceView();

    if (!pTreeCtrl)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pTreeCtrl->GetSelectedEntity() || pTreeCtrl->IsRootSelected());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpAddGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnAddGroup();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpAddGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanAddGroup());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpDeleteGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnDeleteGroup();
    DoRefreshSymbolsAndProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpDeleteGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanDeleteGroup());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpRenameGroup()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnRenameGroup();
    DoRefreshSymbolsAndProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpRenameGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanRenameGroup());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpProperties()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanProperties());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpAddRole()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnAddRole();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpAddRole(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanAddRole());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpDeleteRole()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnDeleteRole();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpDeleteRole(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanDeleteRole());
}
//---------------------------------------------------------------------------
void PSS_App::OnUgpRenameRole()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
        return;

    pUserGroup->OnRenameRole();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateUgpRenameRole(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_UserGroupView* pUserGroup = pWorkspace->GetUserView();

    if (!pUserGroup)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pUserGroup->CanRenameRole());
}
//---------------------------------------------------------------------------
void PSS_App::OnAddLogicalSystem()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
        return;

    pLogicalSystemView->OnAddSystem();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAddLogicalSystem(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pLogicalSystemView->CanAddSystem());
}
//---------------------------------------------------------------------------
void PSS_App::OnDeleteLogicalSystem()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
        return;

    pLogicalSystemView->OnDeleteSystem();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateDeleteLogicalSystem(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pLogicalSystemView->CanDeleteSystem());
}
//---------------------------------------------------------------------------
void PSS_App::OnRenameLogicalSystem()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
        return;

    pLogicalSystemView->OnRenameSystem();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateRenameLogicalSystem(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pLogicalSystemView->CanRenameSystem());
}
//---------------------------------------------------------------------------
void PSS_App::OnLogicalSystemProperties()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
        return;

    pLogicalSystemView->OnProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateLogicalSystemProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_LogicalSystemView* pLogicalSystemView = pWorkspace->GetLogicalSystemView();

    if (!pLogicalSystemView)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pLogicalSystemView->CanProperties());
}
//---------------------------------------------------------------------------
void PSS_App::OnAddPrestation()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
        return;

    pPrestations->OnAddPrestation();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAddPrestation(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pPrestations->CanAddPrestation());
}
//---------------------------------------------------------------------------
void PSS_App::OnDeletePrestation()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
        return;

    pPrestations->OnDeletePrestation();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateDeletePrestation(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pPrestations->CanDeletePrestation());
}
//---------------------------------------------------------------------------
void PSS_App::OnRenamePrestation()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
        return;

    GetProcessWorkspace()->GetPrestationsView()->OnRenamePrestation();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateRenamePrestation(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pPrestations->CanRenamePrestation());
}
//---------------------------------------------------------------------------
void PSS_App::OnPrestationProperties()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
        return;

    pPrestations->OnProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdatePrestationProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_PrestationsView* pPrestations = pWorkspace->GetPrestationsView();

    if (!pPrestations)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pPrestations->CanProperties());
}
//---------------------------------------------------------------------------
void PSS_App::OnAddRule()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
        return;

    pRules->OnAddRule();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAddRule(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pRules->CanAddRule());
}
//---------------------------------------------------------------------------
void PSS_App::OnDeleteRule()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
        return;

    pRules->OnDeleteRule();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateDeleteRule(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pRules->CanDeleteRule());
}
//---------------------------------------------------------------------------
void PSS_App::OnRenameRule()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
        return;

    pRules->OnRenameRule();
    DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateRenameRule(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pRules->CanRenameRule());
}
//---------------------------------------------------------------------------
void PSS_App::OnRuleProperties()
{
    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
        return;

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
        return;

    pRules->OnProperties();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateRuleProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessWorkspace* pWorkspace = GetProcessWorkspace();

    if (!pWorkspace)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    PSS_RulesView* pRules = pWorkspace->GetRulesView();

    if (!pRules)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pRules->CanProperties());
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateCheckReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate());

    LogStartTime();

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    CWaitCursor cursor;

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    // an empty grid report is now available
    pNewFile->SetNewReportGridGenerator(new PSS_CheckReportGenerator(pNewFile, pModel, pCurrentDoc));

    PSS_File file(pCurrentDoc->GetPathName());

    CString str;
    str.LoadString(IDS_CHECKREPORT_FILENAME);

    CString extension;
    PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

    pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

    // update the frame title with the newly built file name
    pNewFile->UpdateFrameTitle();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateGenerateCheckReport(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pGraphModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pGraphModelDoc->GetNotation() == E_MN_Beryl);
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateMercutioReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate());

    LogStartTime();

    CWaitCursor cursor;

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    // an empty grid report is now available, prompt the user to select the sub-process filter object classes
    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_SelectModelSymbolDlg selectModelDlg(pModel,
                                            IDS_MERCUTIOREP_SELECTPROCESS,
                                            g_Selectable_Model | g_Selectable_GraphPage,
                                            &rtClasses);

    if (selectModelDlg.DoModal() == IDOK)
    {
        PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(selectModelDlg.GetSelectedSymbol());

        if (pProcess)
        {
            PSS_ProcessGraphModelMdlBP* pChildModel =
                dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetChildModel());

            if (pChildModel)
            {
                CWaitCursor waitCursor;

                std::unique_ptr<PSS_MercutioReportGenerator> pMercutioReportGenerator
                        (new PSS_MercutioReportGenerator(pNewFile, pChildModel, pCurrentDoc));

                pNewFile->SetNewReportGridGenerator(pMercutioReportGenerator.get());
                pMercutioReportGenerator.release();

                CODSymbolComponent* pComponent = selectModelDlg.GetSelectedSymbol();

                if (pComponent)
                {
                    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComponent);

                    if (pSymbol)
                    {
                        PSS_File file(pCurrentDoc->GetPathName());

                        CString extension;
                        PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

                        pNewFile->SetPathName(file.GetFilePath()       +
                                              pSymbol->GetSymbolName() +
                                              _T(" - ")                +
                                              file.GetFileTitle()      +
                                              extension);

                        // update the frame title with the newly built file name
                        pNewFile->UpdateFrameTitle();

                        return;
                    }
                }
            }
        }
    }

    // close the document
    pNewFile->SetModifiedFlag(FALSE);
    pNewFile->OnCloseDocument();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateGenerateMercutioReport(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pGraphModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pGraphModelDoc->GetNotation() == E_MN_Beryl);
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateConceptorReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate());

    LogStartTime();

    CWaitCursor cursor;

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    PSS_ConceptorReportOptionsDlg optionsDlg;

    if (optionsDlg.DoModal() == IDOK)
    {
        CWaitCursor waitCursor;

        std::unique_ptr<PSS_ConceptorReportGenerator> pReportGenerator(new PSS_ConceptorReportGenerator(pNewFile,
                                                                                                        pModel,
                                                                                                        pCurrentDoc,
                                                                                                        TRUE,
                                                                                                        optionsDlg.GetDetails(),
                                                                                                        optionsDlg.GetDeliverables()));

        pNewFile->SetNewReportGridGenerator(pReportGenerator.get());
        pReportGenerator.release();

        PSS_File file(pCurrentDoc->GetPathName());

        CString str;
        str.LoadString(IDS_CONCEPTORREPORT_FILENAME);

        CString extension;
        PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

        pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

        // update the frame title with the newly built file name
        pNewFile->UpdateFrameTitle();

        return;
    }

    // close the document
    pNewFile->SetModifiedFlag(FALSE);
    pNewFile->OnCloseDocument();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateGenerateConceptorReport(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pGraphModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pGraphModelDoc->GetNotation() == E_MN_Beryl);
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateSesterceReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate());

    LogStartTime();

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    CWaitCursor cursor;

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    std::unique_ptr< PSS_SesterceReportGenerator> pReportGenerator(new PSS_SesterceReportGenerator(pNewFile,
                                                                                                   pModel,
                                                                                                   pCurrentDoc));

    // an empty grid report is now available
    pNewFile->SetNewReportGridGenerator(pReportGenerator.get());
    pReportGenerator.release();

    PSS_File file(pCurrentDoc->GetPathName());

    CString str;
    str.LoadString(IDS_SESTERCES_FILENAME);

    CString extension;
    PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

    pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

    // update the frame title with the newly built file name
    pNewFile->UpdateFrameTitle();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateGenerateSesterceReport(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pGraphModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pGraphModelDoc->GetIntegrateCostSimulation() && pGraphModelDoc->GetNotation() == E_MN_Beryl);
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateSesterceUnitReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

    LogStartTime();

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    // show the report creation wizard
    PSS_ReportCreationWizard wizard(true, false);

    if (wizard.DoModal() == IDCANCEL)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    CWaitCursor cursor;

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    // an empty grid report is now available
    pNewFile->SetNewReportGridGenerator(new PSS_SesterceUnitReportGenerator(pNewFile,
                                                                            pModel,
                                                                            pCurrentDoc,
                                                                            wizard.IncludeMonthDetail()));

    PSS_File file(pCurrentDoc->GetPathName());

    CString str;
    str.LoadString(IDS_SESTERCESUNIT_FILENAME);

    CString extension;
    PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

    pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

    // update the frame title with the newly built file name
    pNewFile->UpdateFrameTitle();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnGenerateSesterceConsolidatedReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate());

    LogStartTime();

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    // show the report creation wizard
    PSS_ReportCreationWizard wizard(true, false);

    if (wizard.DoModal() == IDCANCEL)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    CWaitCursor cursor;

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    // an empty grid report is now available
    pNewFile->SetNewReportGridGenerator(new PSS_SesterceConsolidatedReportGenerator(pNewFile,
                                                                                    pModel,
                                                                                    pCurrentDoc,
                                                                                    wizard.IncludeMonthDetail()));

    PSS_File file(pCurrentDoc->GetPathName());

    CString str;
    str.LoadString(IDS_SESTERCESCONSOLIDATED_FILENAME);

    CString extension;
    PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

    pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

    // update the frame title with the newly built file name
    pNewFile->UpdateFrameTitle();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnGeneratePrestationsReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

    LogStartTime();

    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
    {
        LogEndTime();
        return;
    }

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel());

    if (!pModel)
    {
        LogEndTime();
        return;
    }

    // show the report creation wizard
    PSS_ReportCreationWizard wizard(true, false);

    if (wizard.DoModal() == IDCANCEL)
    {
        LogEndTime();
        return;
    }

    CMultiDocTemplate* pDocTemplate = PSS_Global::GetReportDocumentTemplate();

    if (!pDocTemplate)
    {
        LogEndTime();
        return;
    }

    CWaitCursor cursor;

    // create an empty report document file
    PSS_GridReportDocument* pNewFile = dynamic_cast<PSS_GridReportDocument*>(pDocTemplate->OpenDocumentFile(NULL));

    if (!pNewFile)
    {
        LogEndTime();
        return;
    }

    // an empty grid report is now available
    pNewFile->SetNewReportGridGenerator(new PSS_PrestationsReportGenerator(pNewFile,
                                                                           pModel,
                                                                           pCurrentDoc,
                                                                           wizard.IncludeMonthDetail()));

    PSS_File file(pCurrentDoc->GetPathName());

    CString str;
    str.LoadString(IDS_PRESTATIONSREPORT_FILENAME);

    CString extension;
    PSS_Global::GetReportDocumentTemplate()->GetDocString(extension, CDocTemplate::filterExt);

    pNewFile->SetPathName(file.GetFilePath() + str + file.GetFileTitle() + extension);

    // update the frame title with the newly built file name
    pNewFile->UpdateFrameTitle();

    LogEndTime();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateGeneratePrestationsReport(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pGraphModelDoc)
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(pGraphModelDoc->GetIntegrateCostSimulation() && pGraphModelDoc->GetNotation() == E_MN_Beryl);
}
//---------------------------------------------------------------------------
void PSS_App::OnFileProperty()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
        return;

    PSS_ModelWorkflowOptionsWizard wizard(true, pCurrentDoc);

    // file properties changed?
    if (wizard.DoModal() == IDOK)
    {
        // get and update the newly selected resource language
        PSS_ResourceManager::ChangeLanguage(wizard.GetLanguage());

        // set modified flag
        pCurrentDoc->SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFileProperty(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnAssignCurrentSystemDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
        pCurrentDoc->AssignCurrentSystemDefGUID();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAssignCurrentSystemDef(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnAssignCurrentUserDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
        pCurrentDoc->AssignCurrentUserDefGUID();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAssignCurrentUserDef(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnAssignCurrentPrestationsDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
        pCurrentDoc->AssignCurrentPrestationsDefGUID();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAssignCurrentPrestationsDef(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnAssignCurrentRulesDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
        pCurrentDoc->AssignCurrentRulesDefGUID();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateAssignCurrentRulesDef(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnSymbolReassignUserGroup()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

        if (pOutputWorkspace)
            pCurrentDoc->ReassignUnit(pOutputWorkspace->GetLogView());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateSymbolReassignUserGroup(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnSymbolReassignLogicalSys()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

        if (pOutputWorkspace)
            pCurrentDoc->ReassignSystem(pOutputWorkspace->GetLogView());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateSymbolReassignLogicalSys(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnSymbolReassignPrestations()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

        if (pOutputWorkspace)
            pCurrentDoc->ReassignPrestations(pOutputWorkspace->GetLogView());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateSymbolReassignPrestations(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnSymbolReassignRules()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

        if (pOutputWorkspace)
            pCurrentDoc->ReassignRules(pOutputWorkspace->GetLogView());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateSymbolReassignRules(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnPublishToMessenger()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

        if (pOutputWorkspace)
        {
            // activate the log tab first
            pOutputWorkspace->ActivateWorkflowLogTab();

            PSS_PublishToMessengerWizard wizard(pCurrentDoc, pOutputWorkspace->GetWorkflowLogView(), m_pszProfileName);
            wizard.DoModal();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdatePublishToMessenger(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnDynamicAttributesDisplay()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc)
        return;

    PSS_Properties::IPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(pCurrentDoc->GetModel(), propSet);

    PSS_SelectPropertyDlg select(&propSet,
                                 2,
                                 false,
                                 true,
                                 false,
                                 pCurrentDoc->GetDynamicPropertiesManager(),
                                 pCurrentDoc->GetModel());

    select.DoModal();

    // remove all properties
    PSS_Properties::IPropertyIterator it(&propSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateDynamicAttributesDisplay(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    BOOL                      enable = FALSE;
    PSS_ProcessGraphModelDoc* pDoc   = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pDoc && pDoc->HasDynamicPropertiesManager())
        enable = TRUE;

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_App::OnExportModelToHTMLFile()
{
    std::unique_ptr<PSS_PublishReportInfo> pReportInfo(new PSS_PublishReportInfo());

    if (pReportInfo)
    {
        PSS_ProcessGraphModelDoc* pBaseDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

        if (!pBaseDoc)
            return;

        PSS_PublishModelToHTML::ExportModelToHTMLFile(pBaseDoc,
                                                      pBaseDoc->GetFirstModelView(),
                                                      pReportInfo.get(),
                                                      m_pszProfileName);

        PSS_PublishReportToHTML::ExportReportToHTMLFile(pBaseDoc, pReportInfo.get());

        if (pReportInfo->m_DoLaunchBrowser)
            PSS_PublishModelToHTML::LaunchBrowser(pReportInfo->m_IndexName);

        // restore the original language
        PSS_ResourceManager::ChangeLanguage(pBaseDoc->GetLanguage());
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateExportModelToHTMLFile(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(BOOL(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())));
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    CWinApp* pApp = ::AfxGetApp();

    if (!pApp)
        return;

    // get the data from the driver. This is quicker and most efficient than get the data
    // from the CanPrint() function in the document
    std::unique_ptr<PRINTDLG> pPrintDlg(new PRINTDLG());

    // search for the default printer
    if (pApp->GetPrinterDeviceDefaults(pPrintDlg.get()))
    {
        // get the printer names
        DEVNAMES FAR* pDevNames = (DEVNAMES FAR*)::GlobalLock(pPrintDlg->hDevNames);

        if (!pDevNames)
            return;

        // get the printer mode
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock(pPrintDlg->hDevMode);

        if (!pDevMode)
        {
            ::GlobalUnlock(pPrintDlg->hDevNames);
            return;
        }

        try
        {
            // get the info from the driver
            const CString driver(LPTSTR(pDevNames) + pDevNames->wDriverOffset);
            const CString device(LPTSTR(pDevNames) + pDevNames->wDeviceOffset);
            const CString output(LPTSTR(pDevNames) + pDevNames->wOutputOffset);

            CDC pDC;

            // get the printer device context
            pDC.CreateDC(driver, device, output, pDevMode);

            // if the context is invalid, the printer is unavailable. This is the case e.g for the Adobe Distiller printer
            if (!pDC)
                pCmdUI->Enable(FALSE);
            else
            {
                pCmdUI->Enable(TRUE);
                pDC.DeleteDC();
            }
        }
        catch (...)
        {
            ::GlobalUnlock(pPrintDlg->hDevNames);
            ::GlobalUnlock(pPrintDlg->hDevMode);
            throw;
        }

        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);
    }
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_App::OnUpdateFilePrint(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    CWinApp* pApp = ::AfxGetApp();

    if (!pApp)
        return;

    // get the data from the driver. This is quicker and most efficient than get the data
    // from the CanPrint() function in the document
    std::unique_ptr<PRINTDLG> pPrintDlg(new PRINTDLG());

    // search for the default printer
    if (pApp->GetPrinterDeviceDefaults(pPrintDlg.get()))
    {
        // get the printer names
        DEVNAMES FAR* pDevNames = (DEVNAMES FAR*)::GlobalLock(pPrintDlg->hDevNames);

        if (!pDevNames)
            return;

        // get the printer mode
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)::GlobalLock(pPrintDlg->hDevMode);

        if (!pDevMode)
        {
            ::GlobalUnlock(pPrintDlg->hDevNames);
            return;
        }

        try
        {
            // get the info from the driver
            const CString driver(LPTSTR(pDevNames) + pDevNames->wDriverOffset);
            const CString device(LPTSTR(pDevNames) + pDevNames->wDeviceOffset);
            const CString output(LPTSTR(pDevNames) + pDevNames->wOutputOffset);

            CDC pDC;

            // get the printer device context
            pDC.CreateDC(driver, device, output, pDevMode);

            // if the context is invalid, the printer is unavailable. This is the case e.g for the Adobe Distiller printer
            if (!pDC)
                pCmdUI->Enable(FALSE);
            else
            {
                pCmdUI->Enable(TRUE);
                pDC.DeleteDC();
            }
        }
        catch (...)
        {
            ::GlobalUnlock(pPrintDlg->hDevNames);
            ::GlobalUnlock(pPrintDlg->hDevMode);
            throw;
        }

        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);
    }
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
BOOL PSS_App::InitApp()
{
    #ifdef CHECK_INFO
        // check the application type. zProcess is only available in Entreprise edition
        if (GetApplicationInfoType() != PSS_CryptedFileApplicationTypeInfo::IE_AT_EntrepriseEdition)
        {
            PSS_MessageDlg message;
            message.ShowMessage(IDS_APPINFO_INCOMP, IDS_APPINFO_INCOMP_TITLE);
            return FALSE;
        }
    #endif

    // grid initialization
    GXInit();
    GXSetNewGridLineMode(TRUE);
    GXGetEngineState()->SetDefaultWorksheetFunctions();

    // create the main MDI frame window
    std::unique_ptr<PSS_MainFrame> pMainFrame(new PSS_MainFrame());

    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;

    m_pMainWnd = pMainFrame.get();
    pMainFrame.release();

    // register the application document templates. The document templates
    // acts as the connection between documents, frame windows and views
    std::unique_ptr<PSS_DocTemplateEx> pDocTemplate(new PSS_DocTemplateEx(IDR_MDIPAGE,
                                                                          RUNTIME_CLASS(PSS_DocumentReadWrite),
                                                                          RUNTIME_CLASS(PSS_BaseMDIPage),
                                                                          RUNTIME_CLASS(PSS_ModifyView),
                                                                          ID_FILE_MRU_FORMS1));

    AddDocTemplate(pDocTemplate.get());
    PSS_Global::SetDocTemplate(pDocTemplate.get());
    pDocTemplate.release();

    // register the report application document templates. The document templates
    // acts as the connection between documents, frame windows and views
    std::unique_ptr<CGXMultiDocTemplate> pReportDocTemplate(new CGXMultiDocTemplate(IDR_MERCUTIOREPORT,
                                                                                    RUNTIME_CLASS(PSS_GridReportDocument),
                                                                                    RUNTIME_CLASS(PSS_GridReportChildFrame),
                                                                                    RUNTIME_CLASS(PSS_GridReportView)));

    AddDocTemplate(pReportDocTemplate.get());
    PSS_Global::SetReportDocumentTemplate(pReportDocTemplate.get());
    pReportDocTemplate.release();

    // register the application document templates. The document templates
    // acts as the connection between documents, frame windows and views
    std::unique_ptr<PSS_ProcessModelDocTmpl> pProcessModelDocumentTemplate
            (new PSS_ProcessModelDocTmpl(IDR_MODEL,
                                         RUNTIME_CLASS(PSS_ProcessGraphModelDoc),
                                         RUNTIME_CLASS(PSS_ProcessGraphChildFrame),
                                         RUNTIME_CLASS(PSS_ProcessGraphModelView),
                                         ID_FILE_MRU_MODEL1));

    AddDocTemplate(pProcessModelDocumentTemplate.get());
    PSS_Global::SetProcessModelDocumentTemplate(pProcessModelDocumentTemplate.get());
    pProcessModelDocumentTemplate.release();

    // create the visual tools
    static PSS_VisualToolEdit visualToolEdit;

    PSS_ResourceManager::LoadFromDirectory(PSS_Directory::NormalizeDirectory(GetApplicationDir()) + _T("\\resdll"));
    PSS_ResourceManager::ChangeLanguage(E_LN_French);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_App::PostInitApp()
{
    if (!PSS_MainApp::PostInitApp())
        return FALSE;

    // set the global historic value file name
    m_GlobalHistoricValueFileName = GetSystemDirectory() + _T("\\global.xml");

    // read it
    if (!PSS_Global::ReadFromFileHistoricValue(m_GlobalHistoricValueFileName))
    {
        // todo -cFeature -oJean: Warn the user
    }

    // initialize the model global state
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);

    PSS_ProcessWorkspace* pProcessWorkspace = GetProcessWorkspace();

    // attach the process workspace observers
    if (pProcessWorkspace)
        AttachObserver(pProcessWorkspace);

    PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

    // attach the output workspace observers
    if (pOutputWorkspace)
        AttachObserver(pOutputWorkspace);

    PSS_PropertiesWorkspace* pPropsWorkspace = GetPropertiesWorkspace();

    if (pPropsWorkspace)
    {
        // attach the properties workspace observers
        AttachObserver(pPropsWorkspace);

        PSS_PropertiesView* pPropView = pPropsWorkspace->GetPropertyView();

        // set the ini file to the property view
        if (pPropView)
            pPropView->LoadStateFromIniFile(m_pszProfileName);
    }

    // initialize the workspace template manager. It's processed manually since a template manager tool is written
    m_pWorkspaceTemplateManager = new PSS_WorkspaceWizardTemplateManager();
    ASSERT(m_pWorkspaceTemplateManager);

    std::unique_ptr<PSS_WorkspaceWizardTemplateItem> pTmpItem0
            (new PSS_WorkspaceWizardTemplateItem(_T("Projet vide"),
                                                 _T("Ce projet ne contient aucun document. Uniquement la structure des dossiers")));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem0.get());
    pTmpItem0.release();

    std::unique_ptr<PSS_WorkspaceWizardTemplateItem> pTmpItem1
            (new PSS_WorkspaceWizardTemplateItem(_T("Projet de base"), _T("Ce projet inclus uniquement un modèle")));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem1.get());
    pTmpItem1.release();

    std::unique_ptr<PSS_WorkspaceWizardTemplateItem> pTmpItem2
            (new PSS_WorkspaceWizardTemplateItem(_T("Projet Sesterce"),
                                                 _T("Ce projet inclus uniquement un modèle et un rapport Sesterce de base")));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem2.get());
    pTmpItem2.release();

    if (!LoadUserGroupFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_USERGROUPFILE, MB_OK);
    }

    if (!LoadLogicalSystemFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_LOGICALSYSTEMFILEFILE, MB_OK);
    }

    if (!LoadPrestationsFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_PRESTATIONSFILE, MB_OK);
    }

    if (!LoadRulesFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RULESFILE, MB_OK);
    }

    if (!LoadTypeRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKTYPEFILE, MB_OK);
    }

    if (!LoadImpactRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKIMPACTFILE, MB_OK);
    }

    if (!LoadProbabilityRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKPROBABILITYFILE, MB_OK);
    }

    // simple command line parsing
    if (m_lpCmdLine[0] == '\0')
    {
        if (ShowWelcomeScreen())
        {
            PSS_WelcomeProcessDlg welcomeDialog(&GetApplicationOptions());

            switch (welcomeDialog.DoModal())
            {
                case ID_WELCOME_CREATE_NEWMODEL:   OnFileNewModel();  break;
                case ID_WELCOME_CREATE_NEWPROJECT: OnNewWorkspace();  break;
                case ID_WELCOME_OPENMODEL:         OnFileOpenModel(); break;
                case ID_WELCOME_OPENPROJECT:       OnOpenWorkspace(); break;
                case ID_WELCOME_LASTFILE:
                    if (!GetLastLoadedFileName().IsEmpty())
                        OpenDocumentFile(GetLastLoadedFileName());

                    break;
            }
        }
        else
        if (MustOpenLastLoadedFile())
        {
            const CString lastLoadedFile = GetLastLoadedFileName();

            // should reload the last opened file
            if (!lastLoadedFile.IsEmpty())
                OpenDocumentFile(lastLoadedFile);
        }
    }
    else
        // open an existing document
        OpenDocumentFile(m_lpCmdLine);

    const CString modelTemplateDir = GetModelTemplateDirectory();

    // set the model directory
    if (!modelTemplateDir.IsEmpty())
        PSS_Directory::ChangeCurrentDirectory(modelTemplateDir);

    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_App::LoadUserGroupFile()
{
    // read the user group file
    m_UserGroupFileName = GetSystemDirectory() + _T("\\Userdef.xml");

    // if allocated, delete it first
    if (m_pUserEntityDocument)
        delete m_pUserEntityDocument;

    m_pUserEntityDocument = new PSS_UserEntityDocument();

    if (!m_pUserEntityDocument)
        return false;

    if (!m_pUserEntityDocument->ReadFromFile(m_UserGroupFileName))
    {
        // if not exists, initialize by default
        m_pUserEntityDocument->GetUserGroupEnvironment().SetEntityName(_T("Entreprise XYZ"));
        m_pUserEntityDocument->GetUserGroupEnvironment().SetEntityDescription(_T("Entreprise de ..."));
    }

    if (m_pUserEntityDocument->GetDocumentStamp().GetInternalVersion() < 19)
    {
        // during the beta2 initialization, the format is changed, so save it
        m_pUserEntityDocument->SetModifiedFlag();
        SaveUserGroupFile(false);
    }

    PSS_File file(m_UserGroupFileName);

    // notify observers about the user group initialization
    PSS_UserGroupObserverMsg msg(g_InitUserGroup,
                                 &m_pUserEntityDocument->GetUserGroupEnvironment(),
                                 file.GetFileName());

    NotifyAllObservers(&msg);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::SaveUserGroupFile(bool askBeforeSave)
{
    if (!m_pUserEntityDocument)
        return true;

    // if the file has changed
    if (!m_pUserEntityDocument->IsModified())
        return true;

    // do ask for save?
    if (askBeforeSave)
    {
        PSS_MsgBox mBox;

        switch (mBox.Show(IDS_CONF_SAVE_USERGROUP_DOC, MB_YESNOCANCEL))
        {
            case IDYES:
                // break the switch to save the file
                break;

            case IDNO:
                // just return true and don't save the modifications
                return true;

            case IDCANCEL:
                // just return false and nothing more
                return false;
        }
    }

    // save the document and return true
    if (!m_pUserEntityDocument->SaveToFile(m_UserGroupFileName))
    {
        CString str;
        str.Format(IDS_UNABLETOSAVE_USERGROUP, m_UserGroupFileName);

        PSS_MsgBox mBox;
        mBox.Show(str, MB_OK);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::LoadLogicalSystemFile()
{
    // read the user group file
    m_LogicalSystemFileName = GetSystemDirectory() + _T("\\Systemdef.xml");

    // if allocated, delete it first
    if (m_pLogicalSystemDocument)
        delete m_pLogicalSystemDocument;

    m_pLogicalSystemDocument = new PSS_LogicalSystemDocument();

    if (!m_pLogicalSystemDocument)
        return false;

    if (!m_pLogicalSystemDocument->ReadFromFile(m_LogicalSystemFileName))
    {
        // if not exists, initialize by default
        m_pLogicalSystemDocument->GetLogicalSystemEnvironment().SetEntityName(_T("Systèmes Logiques"));
        m_pLogicalSystemDocument->GetLogicalSystemEnvironment().SetEntityDescription(_T("Systèmes Logiques ..."));
    }

    PSS_File file(m_LogicalSystemFileName);

    // notify observers about the logical system initialisation
    PSS_LogicalSystemObserverMsg msg(g_InitLogicalSystem,
                                     &m_pLogicalSystemDocument->GetLogicalSystemEnvironment(),
                                     file.GetFileName());

    NotifyAllObservers(&msg);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::SaveLogicalSystemFile(bool askBeforeSave)
{
    if (!m_pLogicalSystemDocument)
        return true;

    // if the file has changed
    if (m_pLogicalSystemDocument->IsModified())
    {
        if (askBeforeSave)
        {
            // ask for save
            PSS_MsgBox mBox;

            switch (mBox.Show(IDS_CONF_SAVE_LOGICALSYSTEM_DOC, MB_YESNOCANCEL))
            {
                case IDYES:
                    // break the switch to save the file
                    break;

                case IDNO:
                    // just return true and don't save the modifications
                    return true;

                case IDCANCEL:
                    // just return false and nothing more
                    return false;
            }
        }

        // save the document and return true
        if (!m_pLogicalSystemDocument->SaveToFile(m_LogicalSystemFileName))
        {
            CString str;
            str.Format(IDS_UNABLETOSAVE_LOGSYSTEM, m_LogicalSystemFileName);

            PSS_MsgBox mBox;
            mBox.Show(str, MB_OK);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::LoadPrestationsFile()
{
    // read the prestations group file
    m_PrestationsFileName = GetSystemDirectory() + _T("\\Prestationsdef.xml");

    // if allocated, delete it first
    if (m_pPrestationsDocument)
        delete m_pPrestationsDocument;

    m_pPrestationsDocument = new PSS_LogicalPrestationsDocument();

    if (!m_pPrestationsDocument)
        return false;

    if (!m_pPrestationsDocument->ReadFromFile(m_PrestationsFileName))
    {
        // if does not exists, initialize by default
        m_pPrestationsDocument->GetPrestationsEnvironment().SetEntityName(_T("Gamme des prestations"));
        m_pPrestationsDocument->GetPrestationsEnvironment().SetEntityDescription(_T("Gamme des prestations."));
    }

    PSS_File file(m_PrestationsFileName);

    // notify observers about the user group initialisation
    PSS_LogicalPrestationsObserverMsg msg(g_InitPrestations,
                                          &m_pPrestationsDocument->GetPrestationsEnvironment(),
                                          file.GetFileName());

    NotifyAllObservers(&msg);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::SavePrestationsFile(bool askBeforeSave)
{
    if (!m_pPrestationsDocument)
        return true;

    // if the file has changed
    if (m_pPrestationsDocument->IsModified())
    {
        if (askBeforeSave)
        {
            // ask for save
            PSS_MsgBox mBox;

            switch (mBox.Show(IDS_CONF_SAVE_PRESTATIONS_DOC, MB_YESNOCANCEL))
            {
                case IDYES:
                    // break the switch to save the file
                    break;

                case IDNO:
                    // just return true and don't save the modifications
                    return true;

                case IDCANCEL:
                    // just return false and nothing more
                    return false;
            }
        }

        // save the document and return true
        if (!m_pPrestationsDocument->SaveToFile(m_PrestationsFileName))
        {
            CString str;
            str.Format(IDS_UNABLETOSAVE_PRESTATIONS, m_PrestationsFileName);

            PSS_MsgBox mBox;
            mBox.Show(str, MB_OK);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::LoadRulesFile()
{
    // read the rules group file
    m_RulesFileName = GetSystemDirectory() + _T("\\Rulesdef.xml");

    // if allocated, delete it first
    if (m_pRulesDocument)
        delete m_pRulesDocument;

    m_pRulesDocument = new PSS_LogicalRulesDocument();

    if (!m_pRulesDocument)
        return false;

    if (!m_pRulesDocument->ReadFromFile(m_RulesFileName))
    {
        // if not exists, initialize by default
        m_pRulesDocument->GetRulesEnvironment().SetEntityName(_T("Recueil des règles"));
        m_pRulesDocument->GetRulesEnvironment().SetEntityDescription(_T("Entrée du recueil des règles."));
    }

    PSS_File file(m_RulesFileName);

    // notify observers about the user group initialisation
    PSS_LogicalRulesObserverMsg msg(g_InitRules,
                                    &m_pRulesDocument->GetRulesEnvironment(),
                                    file.GetFileName());

    NotifyAllObservers(&msg);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_App::SaveRulesFile(bool askBeforeSave)
{
    if (!m_pRulesDocument)
        return true;

    // if the file has changed
    if (m_pRulesDocument->IsModified())
    {
        if (askBeforeSave)
        {
            // ask for save
            PSS_MsgBox mBox;

            switch (mBox.Show(IDS_CONF_SAVE_RULES_DOC, MB_YESNOCANCEL))
            {
                case IDYES:
                    // break the switch to save the file
                    break;

                case IDNO:
                    // just return true and don't save the modifications
                    return true;

                case IDCANCEL:
                    // just return false and nothing more
                    return false;
            }
        }

        // save the document and return true
        if (!m_pRulesDocument->SaveToFile(m_RulesFileName))
        {
            CString str;
            str.Format(IDS_UNABLETOSAVE_RULES, m_RulesFileName);

            PSS_MsgBox mBox;
            mBox.Show(str, MB_OK);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
CDocument* PSS_App::OnOpenAdditionalTemplateFile(LPCSTR pFileName)
{
    if (!pFileName)
        return NULL;

    switch (GetTemplateIDByFileName(pFileName))
    {
        case IDR_WORKSPACE_REG: return OpenWorkspaceFile(pFileName);
        default:                break;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_App::OnSaveAdditionalTemplateFile(LPCSTR pFileName)
{
    if (!pFileName)
        return;

    switch (GetTemplateIDByFileName(pFileName))
    {
        case IDR_WORKSPACE_REG: SaveWorkspaceFile(pFileName); break;
        default:                                              break;
    }
}
//---------------------------------------------------------------------------
bool PSS_App::OnRegisterAdditionalTemplate()
{
    // set additionnal document type, these documents have no views attached.
    // It's necessary to specify callbacks function for file open
    RegisterAdditionalTemplate(IDR_WORKSPACE_REG);
    return true;
}
//---------------------------------------------------------------------------
void PSS_App::OnAfterOpenDocument(CDocument* pDoc, const CString& fileName)
{
    ASSERT(pDoc);

    PSS_ProcessGraphModelDoc* pProcessGraphMdlDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc);

    if (!pProcessGraphMdlDoc)
        return;

    std::unique_ptr<PSS_File> pFile(new PSS_File(fileName));

    if (!pFile->Exist())
        pProcessGraphMdlDoc->SetReadOnly(FALSE);
    else
    if (!pFile->IsReadOnly())
    {
        // lock the model while opened
        pFile->SetReadOnly(TRUE);
        pProcessGraphMdlDoc->SetReadOnly(FALSE);
    }
    else
    {
        PSS_MsgBox mBox;

        // change the cancel button to the unlock one
        mBox.DoChangeCancelBtnToUnlockBtn();

        // warn the user
        switch (mBox.Show(IDS_FILE_READONLY, MB_YESNOCANCEL))
        {
            case IDYES:
                // the user wants to open the model in read-only mode
                pProcessGraphMdlDoc->SetReadOnly(TRUE);
                break;

            case IDCANCEL:
            {
                PSS_MsgBox mWarnBox;

                // allow the user to unlock the file
                if (mWarnBox.Show(IDS_FILE_WARN_UNLOCK, MB_YESNO) == IDNO)
                {
                    pProcessGraphMdlDoc->SetReadOnly(TRUE);
                    pDoc->OnCloseDocument();

                    return;
                }

                // allow the file to be unlocked
                pFile->SetReadOnly(TRUE);
                pProcessGraphMdlDoc->SetReadOnly(FALSE);

                break;
            }

            default:
                // the user wan't open the model in read-only mode
                pProcessGraphMdlDoc->SetReadOnly(TRUE);
                pDoc->OnCloseDocument();
                return;
        }
    }

    // assign the main user group
    pProcessGraphMdlDoc->AssignMainUserGroup(GetMainUserGroup());

    // assign the main logical system
    pProcessGraphMdlDoc->AssignMainLogicalSystem(GetMainLogicalSystem());

    // assign the main prestations
    pProcessGraphMdlDoc->AssignMainLogicalPrestations(GetMainLogicalPrestations());

    // assign the main rules
    pProcessGraphMdlDoc->AssignMainLogicalRules(GetMainLogicalRules());

    // call the post open document
    pProcessGraphMdlDoc->OnPostOpenDocument();

    // request the resource language change
    PSS_ResourceManager::ChangeLanguage(dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetLanguage());
}
//---------------------------------------------------------------------------
void PSS_App::OnAfterSaveDocument(CDocument* pDoc)
{}
//---------------------------------------------------------------------------
void PSS_App::OnServerChanged()
{
    PSS_MainApp::OnServerChanged();

    // save all the files
    OnFileSaveAll();

    // close the current workspace
    CloseCurrentWorkspace();

    // load the user group file
    if (!LoadUserGroupFile())
    {
        // warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_USERGROUPFILE, MB_OK);
    }

    // load the logical system file
    if (!LoadLogicalSystemFile())
    {
        // warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_LOGICALSYSTEMFILEFILE, MB_OK);
    }

    // load the prestations file
    if (!LoadPrestationsFile())
    {
        // warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_PRESTATIONSFILEFILE, MB_OK);
    }

    // load the rules file
    if (!LoadRulesFile())
    {
        // warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RULESFILE, MB_OK);
    }
}
//---------------------------------------------------------------------------
void PSS_App::OnServerHasBeenOpened()
{
    PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

    if (!pOutputWorkspace)
        return;

    PSS_OutputSymbolLogView* pLogView = pOutputWorkspace->GetLogView();

    // set message on the log window
    if (pLogView)
    {
        CString str;
        str.Format(IDS_LOCALSERVER_OPEN, GetServerIniFile());

        PSS_GenericSymbolErrorLine e(str);
        pLogView->AddLine(e);
    }

    g_FirstTimeChangeServerDirectory = false;
}
//---------------------------------------------------------------------------
CString PSS_App::OnBuildHelpFileName()
{
    HINSTANCE hInstance = AfxGetResourceHandle();

    if (!hInstance)
        return _T("");

    // build the help file name
    CString helpFile;
    LPTSTR  pModule = new TCHAR[_MAX_PATH];

    try
    {
        if (GetModuleFileName(hInstance, pModule, _MAX_PATH))
        {
            PSS_File file(pModule);
            helpFile = PSS_Directory::NormalizeDirectory(file.GetFilePath()) + _T("\\zConceptor.chm");
        }
    }
    catch (...)
    {
        delete[] pModule;
        throw;
    }

    delete[] pModule;

    return helpFile;
}
//---------------------------------------------------------------------------
void PSS_App::LogStartTime()
{
    #ifdef _DEBUG
        COleDateTime         start      = COleDateTime::GetCurrentTime();
        PSS_OutputWorkspace* pWorkspace = GetOutputWorkspace();

        if (!pWorkspace)
            return;

        PSS_OutputSymbolLogView* pLogView = pWorkspace->GetLogView();

        if (!pLogView)
            return;

        PSS_GenericSymbolErrorLine e((const char*)start.Format(_T("Start time = %H:%M:%S")));
        pLogView->AddLine(e);
    #endif
}
//---------------------------------------------------------------------------
void PSS_App::LogEndTime()
{
    #ifdef _DEBUG
        COleDateTime         end        = COleDateTime::GetCurrentTime();
        PSS_OutputWorkspace* pWorkspace = GetOutputWorkspace();

        if (!pWorkspace)
            return;

        PSS_OutputSymbolLogView* pLogView = pWorkspace->GetLogView();

        if (!pLogView)
            return;

        PSS_GenericSymbolErrorLine e((const char*)end.Format(_T("End time = %H:%M:%S")));
        pLogView->AddLine(e);
    #endif
}
//---------------------------------------------------------------------------
