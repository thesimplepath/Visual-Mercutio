#include <StdAfx.h>
#include "ZAApp.h"

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
#include "zPtyMgr\ZVChoosePropertyDlg.h"
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
#include "zModelBP\ZVPublishToMessengerWizard.h"
#include "zModelBP\ZVRiskTypeContainer.h"
#include "zModelBP\ZVRiskImpactContainer.h"
#include "zModelBP\ZVRiskProbabilityContainer.h"
#include "zModelWeb\PSS_PublishModelToHTML.h"
#include "zReport\ZVGridReportChildFrm.h"
#include "zReport\ZDGridReportDoc.h"
#include "zReport\ZVGridReportView.h"
#include "zReportBP\ZBCheckReportGenerator.h"
#include "zReportBP\ZBMercutioReportGenerator.h"
#include "zReportBP\ZBSesterceReportGenerator.h"
#include "zReportBP\ZBSesterceUnitReportGenerator.h"
#include "zReportBP\ZBSesterceConsolidatedReportGenerator.h"
#include "zReportBP\ZBPrestationsReportGenerator.h"
#include "zReportBP\ZVReportCreationWizard.h"
#include "zReportBP\ZBConceptorReportGenerator.h"
#include "zReportWeb\ZUPublishReportToHTML.h"
#include "zWeb\PSS_HtmlDialog.h"
#include "WelcomP.h"
#include "PSS_ModifyView.h"
#include "MdlWkfOpt.h"
#include "ZVConceptorReportOptions.h"
#include "ZVProcessWorkspace.h"
#include "ZVOutputWorkspace.h"
#include "ZVWorkspaceCreationWizard.h"

// stingray studio
#ifdef _OVDLL
    // Define the Objective Views GUIDs. The GUIDs are declared in OdGuids.h.
    // Including initguid.h before OdGuids.h forces the GUIDs to be defined
    // in this module. Skip this if statically linking to the Objective Views
    // library, because the GUIDs will be linked into the app from the library
#include "initguid.h"
#include "Views\OdGuids.h"
#include "Foundation\Compatibility\Common\CmnGuids.h"
#include "ZAApp.h"
#endif

// resources
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 3 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// The one and only ZAApp object

ZAApp NEAR theApp;

// Used to load the StBox library
static HINSTANCE     mhInstance;

static HMODULE        hModule = NULL;

static bool         gFirstTimeChangeServerDirectory = false;

/////////////////////////////////////////////////////////////////////////////
// Objective Views property cache

// The property cache decreases memory overhead by caching property objects.

CODPropertyCache thePropCache;

// Implementation of ZBGridAppAdapter, the application adapter for this application

ZBGridAppAdapter::ZBGridAppAdapter()
{
    m_pDocTemplate = NULL;
}

ZBGridAppAdapter::~ZBGridAppAdapter()
{
    if (m_pDocTemplate != NULL)
    {
        m_pDocTemplate->CloseAllDocuments(TRUE);
        delete m_pDocTemplate;
    }
}

// you have to override this function and return a CDoctemplate class that is appropriate for this 
// view and document. The frame is unimportant. Please note that you have to keep track of and 
// delete all instances of CDocTemplates that you create here
CDocTemplate* ZBGridAppAdapter::GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass)
{
    if (m_pDocTemplate != NULL)
    {
        return m_pDocTemplate;
    }

    m_pDocTemplate = new CMultiDocTemplate(IDR_MERCUTIOREPORT,
                                           RUNTIME_CLASS(ZDGridReportDocument),
                                           RUNTIME_CLASS(ZVGridReportChildFrame),    // custom MDI child frame
                                           RUNTIME_CLASS(ZVGridReportView));

    return m_pDocTemplate;
}

// **************************************************************************************************************
// *                                                  Classe ZAApp                                                *
// **************************************************************************************************************

IMPLEMENT_DYNAMIC(ZAApp, ZAMainApp)

// **************************************************************************************************************
// *                                                  Message map                                                *
// **************************************************************************************************************

BEGIN_MESSAGE_MAP(ZAApp, ZAMainApp)
    //{{AFX_MSG_MAP(ZAApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(ID_HELP_SUPPORT, OnHelpSupport)
    ON_COMMAND(ID_APP_EXIT, OnAppExit)
    ON_COMMAND(ID_OPTIONS, OnOptions)
    ON_COMMAND(ID_CHOOSE_SERVER, OnChooseServer)
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
    ON_COMMAND(ID_ASSIGN_CURRENTSYSTEMDEF, OnAssignCurrentSystemdef)
    ON_COMMAND(ID_ASSIGN_CURRENTUSERDEF, OnAssignCurrentUserdef)
    ON_COMMAND(ID_ASSIGN_CURRENTPRESTATIONSDEF, OnAssignCurrentPrestationsDef)
    ON_COMMAND(ID_ASSIGN_CURRENTRULESDEF, OnAssignCurrentRulesDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTSYSTEMDEF, OnUpdateAssignCurrentSystemdef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTUSERDEF, OnUpdateAssignCurrentUserdef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTPRESTATIONSDEF, OnUpdateAssignCurrentPrestationsDef)
    ON_UPDATE_COMMAND_UI(ID_ASSIGN_CURRENTRULESDEF, OnUpdateAssignCurrentRulesDef)
    ON_COMMAND(ID_SYMBOL_REASSIGN_USERGROUP, OnSymbolReassignUsergroup)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_USERGROUP, OnUpdateSymbolReassignUsergroup)
    ON_COMMAND(ID_SYMBOL_REASSIGN_LOGICALSYS, OnSymbolReassignLogicalsys)
    ON_UPDATE_COMMAND_UI(ID_SYMBOL_REASSIGN_LOGICALSYS, OnUpdateSymbolReassignLogicalsys)
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

// **************************************************************************************************************
// *                                           Construction/Destruction                                            *
// **************************************************************************************************************

// Constructeur par défaut de la classe ZAApp.
ZAApp::ZAApp()
    : m_pWorkspaceEnvDocument(NULL),
    m_pWorkspaceTemplateManager(NULL),
    m_pUserEntityDocument(NULL),
    m_pLogicalSystemDocument(NULL),
    m_pPrestationsDocument(NULL),    // JMR-MODIF - Le 7 octobre 2005 - Initialise le pointeur du document.
    m_pRulesDocument(NULL),    // JMR-MODIF - Le 15 novembre 2006 - Initialise le pointeur du document.
    m_pRiskTypeContainer(NULL),    // JMR-MODIF - Le 8 juillet 2007 - Initialise le pointeur de type de risque.
    m_pRiskImpactContainer(NULL),    // JMR-MODIF - Le 11 juillet 2007 - Initialise le pointeur d'impact.
    m_pRiskProbabilityContainer(NULL)    // JMR-MODIF - Le 11 juillet 2007 - Initialise le pointeur de probabilités.
{
    m_IDD_Splash = IDB_SPLASHLOGO_2000;
    m_IDD_About = IDB_SPLASHLOGO;
    m_IDD_Support = IDB_SPLASHLOGO;

    // Assigns DDE names
    m_CppServerName = _T("DDE_ZPROCESS_NAME");
    m_CppTopicName = _T("DDE_ZPROCESS_TOPIC");

    // JMR-MODIF - Le 1er janvier 2007 - Ajout de l'inscription de cette classe dans le médiateur.
    PSS_Application::Instance()->RegisterMainForm(this);
}

// Destructeur de la classe ZAApp.
ZAApp::~ZAApp()
{
    Release();

    PSS_Application::Instance()->UnregisterMainForm();
    PSS_Application::Instance()->Release();
}

// **************************************************************************************************************
// *                                          Nettoyage de la mémoire                                            *
// **************************************************************************************************************

// JMR-MODIF - Le 23 août 2005 - Ajout de la fonction Release, pour permettre le nettoyage final de l'application.
void ZAApp::Release()
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

    // JMR-MODIF - Le 10 octobre 2005 - Ajout du code de destruction du document de prestations.
    if (m_pPrestationsDocument)
    {
        delete m_pPrestationsDocument;
        m_pPrestationsDocument = NULL;
    }

    // JMR-MODIF - Le 15 novembre 2006 - Ajout du code de destruction du document de règles.
    if (m_pRulesDocument)
    {
        delete m_pRulesDocument;
        m_pRulesDocument = NULL;
    }

    // JMR-MODIF - Le 8 juillet 2007 - Ajout du code de destruction des types de risques en mémoire.
    if (m_pRiskTypeContainer)
    {
        delete m_pRiskTypeContainer;
        m_pRiskTypeContainer = NULL;
    }

    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code de destruction des impacts des risques en mémoire.
    if (m_pRiskImpactContainer)
    {
        delete m_pRiskImpactContainer;
        m_pRiskImpactContainer = NULL;
    }

    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code de destruction des probabilités des risques en mémoire.
    if (m_pRiskProbabilityContainer)
    {
        delete m_pRiskProbabilityContainer;
        m_pRiskProbabilityContainer = NULL;
    }

    // Ces chaînes doivent être vidées après utilisation, pour ne pas générer de memory leaks.
    m_GlobalIniFile.Empty();
    m_WorkspaceFileName.Empty();
    m_UserGroupFileName.Empty();
    m_LogicalSystemFileName.Empty();
    // JMR-MODIF - Le 2 février 2006 - Ajout du code de nettoyage pour la variable m_PrestationsFileName.
    m_PrestationsFileName.Empty();
    // JMR-MODIF - Le 15 novembre 2006 - Ajout du code de nettoyage pour la variable m_RulesFileName.
    m_RulesFileName.Empty();
    m_GlobalHistoricValueFileName.Empty();

    // Désallocation des objets statiques.
    PSS_Global::Release();
    PSS_ModelGlobal::Release();
    PSS_ObjectUtility::Release();
    PSS_ResourceManager::Release();
    PSS_FloatingToolBar::Release();

    // Appel à la fonction Release de la classe de base.
    ZAMainApp::Release();
}

// **************************************************************************************************************
// *                                            Ouverture de l'application                                        *
// **************************************************************************************************************

BOOL ZAApp::InitInstance()
{
    if (!ZAMainApp::InitInstance())
    {
        return FALSE;
    }

    return TRUE;
}

BOOL ZAApp::InitAppl()
{
#ifdef _ZCHECKINFO
    // Check the application type. ZProcess is only available in Entreprise edition
    if (GetApplicationInfoType() != ZBCriptedFileApplicationTypeInfo::EntrepriseEdition)
    {
        PSS_MessageDlg message;
        message.ShowMessage(IDS_APPINFO_INCOMP, IDS_APPINFO_INCOMP_TITLE);
        return FALSE;
    }
#endif // _ZCHECKINFO

    // Grid initialization
    GXInit();
    GXSetNewGridLineMode(TRUE);
    GXGetEngineState()->SetDefaultWorksheetFunctions();

    // Create main MDI Frame window
    ZIMainFrame* pMainFrame = new ZIMainFrame;
    m_pMainWnd = pMainFrame;

    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        return FALSE;
    }

    // Register the application's document templates. Document templates
    // serve as the connection between documents, frame windows and views.
    PSS_DocTemplateEx* pDocTemplate = new PSS_DocTemplateEx(IDR_MDIPAGE,
                                                            RUNTIME_CLASS(ZDDocumentReadWrite),
                                                            RUNTIME_CLASS(PSS_BaseMDIPage),
                                                            RUNTIME_CLASS(PSS_ModifyView),
                                                            ID_FILE_MRU_FORMS1);

    AddDocTemplate(pDocTemplate);
    PSS_Global::SetDocTemplate(pDocTemplate);

    // Register the report application's document templates. Document templates
    // serve as the connection between documents, frame windows and views.
    CGXMultiDocTemplate* pReportDocTemplate;
    pReportDocTemplate = new CGXMultiDocTemplate(IDR_MERCUTIOREPORT,
                                                 RUNTIME_CLASS(ZDGridReportDocument),
                                                 RUNTIME_CLASS(ZVGridReportChildFrame),    // custom MDI child frame
                                                 RUNTIME_CLASS(ZVGridReportView));

    AddDocTemplate(pReportDocTemplate);
    PSS_Global::SetReportDocumentTemplate(pReportDocTemplate);

    // Register the application's document templates. Document templates
    //  serve as the connection between documents, frame windows and views.
    PSS_ProcessModelDocTmpl* pProcessModelDocumentTemplate =
        new PSS_ProcessModelDocTmpl(IDR_MODEL,
                                    RUNTIME_CLASS(PSS_ProcessGraphModelDoc),
                                    RUNTIME_CLASS(PSS_ProcessGraphChildFrame),                // custom MDI child frame
                                    RUNTIME_CLASS(PSS_ProcessGraphModelView),
                                    ID_FILE_MRU_MODEL1);

    AddDocTemplate(pProcessModelDocumentTemplate);

    PSS_Global::SetProcessModelDocumentTemplate(pProcessModelDocumentTemplate);

    // Creation of Visual Tools
    static PSS_VisualToolEdit VisualToolEdit;

    PSS_ResourceManager::LoadFromDirectory(PSS_Directory::NormalizeDirectory(GetApplicationDir()) + _T("\\resdll"));
    PSS_ResourceManager::ChangeLanguage(E_LN_French);

    // No errors
    return(TRUE);
}

BOOL ZAApp::PostInitAppl()
{
    if (!ZAMainApp::PostInitAppl())
    {
        return FALSE;
    }

    // Sets the global historic value file name
    m_GlobalHistoricValueFileName = GetSystemDirectory() + _T("\\global.xml");

    // Read it
    if (!PSS_Global::ReadFromFileHistoricValue(m_GlobalHistoricValueFileName))
    {
        // Warn the user
    }

    // Initialize the global state for model
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);

    // Attach the necessary observers
    if (GetProcessWorkspace())
    {
        AttachObserver(GetProcessWorkspace());
    }

    if (GetOutputWorkspace())
    {
        AttachObserver(GetOutputWorkspace());
    }

    if (GetPropertiesWorkspace())
    {
        AttachObserver(GetPropertiesWorkspace());
    }

    // Sets the right inifile to the propertyview
    if (GetPropertiesWorkspace() && GetPropertiesWorkspace()->GetPropertyView())
    {
        GetPropertiesWorkspace()->GetPropertyView()->LoadStateFromIniFile(m_pszProfileName);
    }

    // Initialize the workspace template manager 
    // It is done manually, since a template manager tool is written
    m_pWorkspaceTemplateManager = new PSS_WorkspaceWizardTemplateManager();
    ASSERT(m_pWorkspaceTemplateManager != NULL);

    PSS_WorkspaceWizardTemplateItem* pTmpItem0 =
        new PSS_WorkspaceWizardTemplateItem(_T("Projet vide"),
                                            _T("Ce projet ne contient aucun document. Uniquement la structure des dossiers"));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem0);

    PSS_WorkspaceWizardTemplateItem* pTmpItem1 =
        new PSS_WorkspaceWizardTemplateItem(_T("Projet de base"), _T("Ce projet inclus uniquement un modèle"));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem1);

    PSS_WorkspaceWizardTemplateItem* pTmpItem2 =
        new PSS_WorkspaceWizardTemplateItem(_T("Projet Sesterce"),
                                            _T("Ce projet inclus uniquement un modèle et un rapport Sesterce de base"));

    m_pWorkspaceTemplateManager->AddTemplateItem(pTmpItem2);

    if (!LoadUserGroupFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_USERGROUPFILE, MB_OK);
    }

    if (!LoadLogicalSystemFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_LOGICALSYSTEMFILEFILE, MB_OK);
    }

    // JMR-MODIF - Le 7 octobre 2005 - Ajout de l'appel à la nouvelle fonction d'ouverture du formulaire de prestations.
    if (!LoadPrestationsFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_PRESTATIONSFILE, MB_OK);
    }

    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'appel à la nouvelle fonction d'ouverture du formulaire des règles.
    if (!LoadRulesFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RULESFILE, MB_OK);
    }

    // JMR-MODIF - Le 8 juillet 2007 - Ajout de l'appel à la nouvelle fonction d'ouverture des types de risques.
    if (!LoadTypeRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKTYPEFILE, MB_OK);
    }

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de l'appel à la nouvelle fonction d'ouverture des impacts des risques.
    if (!LoadImpactRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKIMPACTFILE, MB_OK);
    }

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de l'appel à la nouvelle fonction d'ouverture des probabilités des risques.
    if (!LoadProbabilityRiskFile())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RISKPROBABILITYFILE, MB_OK);
    }

    // Simple command line parsing
    if (m_lpCmdLine[0] == '\0')
    {
        if (ShowWelcomeScreen())
        {
            ZIWelcomeProcess WelcomeDialog(&GetApplicationOptions());

            switch (WelcomeDialog.DoModal())
            {
                case ID_WELCOME_CREATE_NEWMODEL:
                {
                    OnFileNewModel();
                    break;
                }

                case ID_WELCOME_CREATE_NEWPROJECT:
                {
                    OnNewWorkspace();
                    break;
                }

                case ID_WELCOME_OPENMODEL:
                {
                    OnFileOpenModel();
                    break;

                }

                case ID_WELCOME_OPENPROJECT:
                {
                    OnOpenWorkspace();
                    break;
                }

                case ID_WELCOME_LASTFILE:
                {
                    if (!GetLastLoadedFile().IsEmpty())
                    {
                        OpenDocumentFile(GetLastLoadedFile());
                    }

                    break;
                }
            }
        }
        else
        {
            // Must reload the last opened file
            if (MustOpenLastLoadedFile())
            {
                if (!GetLastLoadedFile().IsEmpty())
                {
                    OpenDocumentFile(GetLastLoadedFile());
                }
            }
        }
    }
    else
    {
        // open an existing document
        OpenDocumentFile(m_lpCmdLine);
    }

    // Set to the model directory
    if (!GetModelTemplateDirectory().IsEmpty())
    {
        PSS_Directory::ChangeCurrentDirectory(GetModelTemplateDirectory());
    }

    return TRUE;
}

// **************************************************************************************************************
// *                                            Fermeture de l'application                                        *
// **************************************************************************************************************

int ZAApp::ExitInstance()
{
    return ZAMainApp::ExitInstance();
}

BOOL ZAApp::ExitAppl()
{
    if (!PSS_Global::SaveToFileHistoricValue(m_GlobalHistoricValueFileName))
    {
        // Warn the user
    }

    // Saves the global state for model
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);
    PSS_ModelGlobal::SaveGlobalPropertyAttributes();

    // Close the current workspace
    if (!CloseCurrentWorkspace())
    {
        return FALSE;
    }

    // Saves the user group file
    if (!SaveUserGroupFile())
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_USERGROUPFILE, MB_OK);
        return FALSE;
    }

    // Saves the logical system file
    if (!SaveLogicalSystemFile())
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_LOGICALSYSTEMFILE, MB_OK);
        return FALSE;
    }

    // JMR-MODIF - Le 10 octobre 2005 - Sauvegarde le fichier de prestations.
    if (!SavePrestationsFile())
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_PRESTATIONSFILE, MB_OK);
        return FALSE;
    }

    // JMR-MODIF - Le 15 novembre 2006 - Sauvegarde le fichier de règles.
    if (!SaveRulesFile())
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_RULESFILE, MB_OK);
        return FALSE;
    }

    // JMR-MODIF - Le 14 juillet 2007 - Mets à jour le nom des fichiers des listes pour les règles.
    GetApplicationOptions().SetRiskTypeFileName(m_pRiskTypeContainer->GetFileName());
    GetApplicationOptions().SetRiskImpactFileName(m_pRiskImpactContainer->GetFileName());
    GetApplicationOptions().SetRiskProbabilityFileName(m_pRiskProbabilityContainer->GetFileName());

    if (!ZAMainApp::ExitAppl())
    {
        return FALSE;
    }

    return TRUE;
}

// **************************************************************************************************************
// *                                                     Options                                                *
// **************************************************************************************************************

BOOL ZAApp::LoadApplicationOptions()
{
    //## begin ZAApp::LoadApplicationOptions%912537584.body preserve=yes
    return TRUE;
    //## end ZAApp::LoadApplicationOptions%912537584.body
}

BOOL ZAApp::SaveApplicationOptions()
{
    //## begin ZAApp::SaveApplicationOptions%912537585.body preserve=yes
    return TRUE;
    //## end ZAApp::SaveApplicationOptions%912537585.body
}

// **************************************************************************************************************
// *                                 Fonctions de rafraîchissement de l'affichage                                *
// **************************************************************************************************************

// JMR-MODIF - Le 28 décembre 2006 - Cette fonction ordonne le rafraîchissement des symboles et des propriétés.
void ZAApp::DoRefreshSymbolsAndProperties()
{
    PSS_ProcessModelDocTmpl* m_pDocTmpl = PSS_Global::GetProcessModelDocumentTemplate();
    POSITION myPosition = m_pDocTmpl->GetFirstDocPosition();

    while (myPosition != NULL)
    {
        CDocument* m_pDoc = m_pDocTmpl->GetNextDoc(myPosition);
        PSS_ProcessGraphModelDoc*  m_pGraphModelDoc = (PSS_ProcessGraphModelDoc*)m_pDoc;
        PSS_ProcessGraphModelView* m_pGraphModelView = m_pGraphModelDoc->GetFirstModelView();
        PSS_ProcessGraphModelController* m_pModelController = m_pGraphModelView->GetModelController();

        m_pModelController->RefreshAllSymbols();
        m_pModelController->RefreshSelectionProperties();
    }
}

// JMR-MODIF - Le 28 décembre 2006 - Cette fonction ordonne le rafraîchissement des propriétés.
void ZAApp::DoRefreshProperties()
{
    PSS_ProcessModelDocTmpl* m_pDocTmpl = PSS_Global::GetProcessModelDocumentTemplate();
    POSITION myPosition = m_pDocTmpl->GetFirstDocPosition();

    while (myPosition != NULL)
    {
        CDocument* m_pDoc = m_pDocTmpl->GetNextDoc(myPosition);
        PSS_ProcessGraphModelDoc*  m_pGraphModelDoc = (PSS_ProcessGraphModelDoc*)m_pDoc;
        PSS_ProcessGraphModelView* m_pGraphModelView = m_pGraphModelDoc->GetFirstModelView();
        PSS_ProcessGraphModelController* m_pModelController = m_pGraphModelView->GetModelController();

        m_pModelController->RefreshSelectionProperties();
    }
}

// **************************************************************************************************************
// *            Fonctions de gestion des fichiers .xml (UserDef.xml / SystemDef.xml / PrestationsDef.xml)        *
// **************************************************************************************************************

bool ZAApp::LoadUserGroupFile()
{
    // Read the user group file
    m_UserGroupFileName = GetSystemDirectory() + _T("\\Userdef.xml");

    // If allocated, then delete it first
    if (m_pUserEntityDocument)
    {
        delete m_pUserEntityDocument;
    }

    m_pUserEntityDocument = new PSS_UserEntityDocument();

    if (m_pUserEntityDocument)
    {
        if (!m_pUserEntityDocument->ReadFromFile(m_UserGroupFileName))
        {
            // If does not exists, initialize by default
            m_pUserEntityDocument->GetUserGroupEnvironment().SetEntityName(_T("Entreprise XYZ"));
            m_pUserEntityDocument->GetUserGroupEnvironment().SetEntityDescription(_T("Entreprise de ..."));
        }

        if (m_pUserEntityDocument->GetDocumentStamp().GetInternalVersion() < 19)
        {
            // For Beta2, during initialization we changed the format, saves it
            m_pUserEntityDocument->SetModifiedFlag();
            SaveUserGroupFile(false);
        }

        PSS_File file(m_UserGroupFileName);

        // Notify observers about the user group initialisation
        PSS_UserGroupObserverMsg msg(g_InitUserGroup,
                                     &m_pUserEntityDocument->GetUserGroupEnvironment(),
                                     file.GetFileName());

        NotifyAllObservers(&msg);

        return true;
    }

    return false;
}

bool ZAApp::SaveUserGroupFile(bool AskBeforeSave /*= true*/)
{
    if (m_pUserEntityDocument)
    {
        // If the file has changed
        if (m_pUserEntityDocument->IsModified())
        {
            if (AskBeforeSave)
            {
                // Asks for save
                PSS_MsgBox mBox;
                switch (mBox.Show(IDS_CONF_SAVE_USERGROUP_DOC, MB_YESNOCANCEL))
                {
                    case IDYES:
                    {
                        // Break the switch to save the file
                        break;
                    }

                    case IDNO:
                    {
                        // just return true and don't save the modifications
                        return true;
                    }

                    case IDCANCEL:
                    {
                        // just return false and nothing more
                        return false;
                    }
                }
            }

            // save the document and return true
            if (!m_pUserEntityDocument->SaveToFile(m_UserGroupFileName))
            {
                PSS_MsgBox mBox;
                CString s;
                s.Format(IDS_UNABLETOSAVE_USERGROUP, m_UserGroupFileName);
                mBox.Show(s, MB_OK);
            }
        }
    }

    return true;
}

bool ZAApp::LoadLogicalSystemFile()
{
    // Read the user group file
    m_LogicalSystemFileName = GetSystemDirectory() + _T("\\Systemdef.xml");

    // If allocated, then delete it first
    if (m_pLogicalSystemDocument)
    {
        delete m_pLogicalSystemDocument;
    }

    m_pLogicalSystemDocument = new PSS_LogicalSystemDocument();

    if (m_pLogicalSystemDocument)
    {
        if (!m_pLogicalSystemDocument->ReadFromFile(m_LogicalSystemFileName))
        {
            // If does not exists, initialize by default
            m_pLogicalSystemDocument->GetLogicalSystemEnvironment().SetEntityName(_T("Systèmes Logiques"));
            m_pLogicalSystemDocument->GetLogicalSystemEnvironment().SetEntityDescription(_T("Systèmes Logiques ..."));
        }

        PSS_File file(m_LogicalSystemFileName);

        // Notify observers about the logical system initialisation
        PSS_LogicalSystemObserverMsg Msg(g_InitLogicalSystem,
                                       &m_pLogicalSystemDocument->GetLogicalSystemEnvironment(),
                                       file.GetFileName());

        NotifyAllObservers(&Msg);

        return true;
    }

    return false;
}

bool ZAApp::SaveLogicalSystemFile(bool AskBeforeSave /*= true*/)
{
    if (m_pLogicalSystemDocument)
    {
        // If the file has changed
        if (m_pLogicalSystemDocument->IsModified())
        {
            if (AskBeforeSave)
            {
                // Asks for save
                PSS_MsgBox mBox;

                switch (mBox.Show(IDS_CONF_SAVE_LOGICALSYSTEM_DOC, MB_YESNOCANCEL))
                {
                    case IDYES:
                    {
                        // Break the switch to save the file
                        break;
                    }
                    case IDNO:
                    {
                        // just return true and don't save the modifications
                        return true;
                    }
                    case IDCANCEL:
                    {
                        // just return false and nothing more
                        return false;
                    }
                }
            }

            // save the document and return true
            if (!m_pLogicalSystemDocument->SaveToFile(m_LogicalSystemFileName))
            {
                PSS_MsgBox mBox;
                CString s;
                s.Format(IDS_UNABLETOSAVE_LOGSYSTEM, m_LogicalSystemFileName);
                mBox.Show(s, MB_OK);
            }
        }
    }

    return true;
}

// JMR-MODIF - Le 7 octobre 2005 - Ajout de la fonction LoadPrestationsFile.
bool ZAApp::LoadPrestationsFile()
{
    // Read the prestations group file
    m_PrestationsFileName = GetSystemDirectory() + _T("\\Prestationsdef.xml");

    // If allocated, then delete it first
    if (m_pPrestationsDocument)
    {
        delete m_pPrestationsDocument;
    }

    m_pPrestationsDocument = new PSS_LogicalPrestationsDocument();

    if (m_pPrestationsDocument)
    {
        if (!m_pPrestationsDocument->ReadFromFile(m_PrestationsFileName))
        {
            // If does not exists, initialize by default
            m_pPrestationsDocument->GetPrestationsEnvironment().SetEntityName(_T("Gamme des prestations"));
            m_pPrestationsDocument->GetPrestationsEnvironment().SetEntityDescription(_T("Gamme des prestations."));
        }

        PSS_File file(m_PrestationsFileName);

        // Notify observers about the user group initialisation
        PSS_LogicalPrestationsObserverMsg Msg(g_InitPrestations,
                                            &m_pPrestationsDocument->GetPrestationsEnvironment(),
                                            file.GetFileName());

        NotifyAllObservers(&Msg);

        return true;
    }

    return false;
}

// JMR-MODIF - Le 7 octobre 2005 - Ajout de la fonction SavePrestationsFile.
bool ZAApp::SavePrestationsFile(bool AskBeforeSave /*= true*/)
{
    if (m_pPrestationsDocument)
    {
        // If the file has changed
        if (m_pPrestationsDocument->IsModified())
        {
            if (AskBeforeSave)
            {
                // Asks for save
                PSS_MsgBox mBox;

                switch (mBox.Show(IDS_CONF_SAVE_PRESTATIONS_DOC, MB_YESNOCANCEL))
                {
                    case IDYES:
                    {
                        // Break the switch to save the file
                        break;
                    }
                    case IDNO:
                    {
                        // just return true and don't save the modifications
                        return true;
                    }
                    case IDCANCEL:
                    {
                        // just return false and nothing more
                        return false;
                    }
                }
            }

            // Save the document and return true
            if (!m_pPrestationsDocument->SaveToFile(m_PrestationsFileName))
            {
                PSS_MsgBox mBox;
                CString s;
                s.Format(IDS_UNABLETOSAVE_PRESTATIONS, m_PrestationsFileName);
                mBox.Show(s, MB_OK);
            }
        }
    }

    return true;
}

// JMR-MODIF - Le 15 novembre 2006 - Ajout de la fonction LoadRulesFile.
bool ZAApp::LoadRulesFile()
{
    // Read the Rules group file
    m_RulesFileName = GetSystemDirectory() + _T("\\Rulesdef.xml");

    // If allocated, then delete it first
    if (m_pRulesDocument)
    {
        delete m_pRulesDocument;
    }

    m_pRulesDocument = new PSS_LogicalRulesDocument();

    if (m_pRulesDocument)
    {
        if (!m_pRulesDocument->ReadFromFile(m_RulesFileName))
        {
            // If does not exists, initialize by default
            m_pRulesDocument->GetRulesEnvironment().SetEntityName(_T("Recueil des règles"));
            m_pRulesDocument->GetRulesEnvironment().SetEntityDescription(_T("Entrée du recueil des règles."));
        }

        PSS_File file(m_RulesFileName);

        // Notify observers about the user group initialisation
        PSS_LogicalRulesObserverMsg Msg(g_InitRules,
                                      &m_pRulesDocument->GetRulesEnvironment(),
                                      file.GetFileName());

        NotifyAllObservers(&Msg);

        return true;
    }

    return false;
}

// JMR-MODIF - Le 15 novembre 2006 - Ajout de la fonction SaveRulesFile.
bool ZAApp::SaveRulesFile(bool AskBeforeSave /*= true*/)
{
    if (m_pRulesDocument)
    {
        // If the file has changed
        if (m_pRulesDocument->IsModified())
        {
            if (AskBeforeSave)
            {
                // Asks for save
                PSS_MsgBox mBox;

                switch (mBox.Show(IDS_CONF_SAVE_RULES_DOC, MB_YESNOCANCEL))
                {
                    case IDYES:
                    {
                        // Break the switch to save the file
                        break;
                    }
                    case IDNO:
                    {
                        // just return true and don't save the modifications
                        return true;
                    }
                    case IDCANCEL:
                    {
                        // just return false and nothing more
                        return false;
                    }
                }
            }

            // Save the document and return true
            if (!m_pRulesDocument->SaveToFile(m_RulesFileName))
            {
                PSS_MsgBox mBox;
                CString s;
                s.Format(IDS_UNABLETOSAVE_RULES, m_RulesFileName);
                mBox.Show(s, MB_OK);
            }
        }
    }

    return true;
}

// JMR-MODIF - Le 8 juillet 2007 - Cette fonction charge en mémoire le fichier des types de risques.
BOOL ZAApp::LoadTypeRiskFile()
{
    if (m_pRiskTypeContainer == NULL)
    {
        m_pRiskTypeContainer = new ZVRiskTypeContainer();

        if (!m_pRiskTypeContainer->LoadFile(GetApplicationOptions().GetRiskTypeFileName()))
            return FALSE;
    }

    return TRUE;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction charge en mémoire le fichier des impacts des risques.
BOOL ZAApp::LoadImpactRiskFile()
{
    if (m_pRiskImpactContainer == NULL)
    {
        m_pRiskImpactContainer = new ZVRiskImpactContainer();

        if (!m_pRiskImpactContainer->LoadFile(GetApplicationOptions().GetRiskImpactFileName()))
            return FALSE;
    }

    return TRUE;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction charge en mémoire le fichier des probabilités des risques.
BOOL ZAApp::LoadProbabilityRiskFile()
{
    if (m_pRiskProbabilityContainer == NULL)
    {
        m_pRiskProbabilityContainer = new ZVRiskProbabilityContainer();

        if (!m_pRiskProbabilityContainer->LoadFile(GetApplicationOptions().GetRiskProbabilityFileName()))
            return FALSE;
    }

    return TRUE;
}

// **************************************************************************************************************
// *                                                    MainFrame                                                *
// **************************************************************************************************************

ZIMainFrame* ZAApp::GetMainFrame()
{
    if (AfxGetMainWnd() && ISA(AfxGetMainWnd(), ZIMainFrame))
    {
        return (ZIMainFrame*)AfxGetMainWnd();
    }

    return NULL;
}

// **************************************************************************************************************
// *                                                  GlobalIniFile                                                *
// **************************************************************************************************************

CString ZAApp::GetGlobalIniFile()
{
    return m_GlobalIniFile;
}

// **************************************************************************************************************
// *                                        Espace de travail principal                                            *
// **************************************************************************************************************

// ******************************************** Obtention du pointeur *******************************************

PSS_WorkspaceEnv* ZAApp::GetCurrentWorkspaceEnvironment()
{
    return (m_pWorkspaceEnvDocument) ? &m_pWorkspaceEnvDocument->GetWorkspaceEnvironment() : NULL;
}

// ********************************************* Ouverture / Fermeture ******************************************

bool ZAApp::CloseCurrentAndAllocateNewWorkspace()
{
    // First, check a a workspace is already open
    if (WorkspaceEnvironmentExist())
    {
        // Ask before closing all open documents
        if (!CloseCurrentWorkspace(true))
        {
            return false;
        }
    }

    // Allocate a new workspace
    m_pWorkspaceEnvDocument = new PSS_WorkspaceEnvDocument();

    return (m_pWorkspaceEnvDocument != NULL) ? true : false;
}

bool ZAApp::CloseCurrentWorkspace(bool AskClosingDocument /*= false*/)
{
    if (WorkspaceEnvironmentExist())
    {
        if (IsWorkspaceEnvironmentLoaded())
        {
            if (!SaveCurrentWorkspace())
            {
                return false;
            }

            if (AskClosingDocument)
            {
                PSS_MsgBox mBox;

                if (mBox.Show(IDS_CONF_CLOSEALLDOCS_CURRENT_WKSPACE, MB_YESNO) == IDYES)
                {
                    // First, try to save all modified documents
                    if (!SaveAllModified())
                    {
                        return false;
                    }

                    if (GetOutputWorkspace())
                    {
                        GetOutputWorkspace()->DetachAllObservers();
                    }

                    // Close all documents without ending session to true
                    CloseAllDocuments(FALSE);
                }
            }
            else
            {
                // First, try to save all modified documents
                if (!SaveAllModified())
                {
                    return false;
                }

                if (GetOutputWorkspace())
                {
                    GetOutputWorkspace()->DetachAllObservers();
                }

                // Close all documents without ending session to true
                CloseAllDocuments(TRUE);
            }
        }

        // Before deleting the workspace environement,
        // sets the last open file as the workspace file name
        if (m_pWorkspaceEnvDocument)
        {
            SetLastLoadedFile(m_pWorkspaceEnvDocument->GetPathName());
            delete m_pWorkspaceEnvDocument;
        }

        m_pWorkspaceEnvDocument = NULL;

        // Notify observers about the workspace closing
        PSS_WorkspaceObserverMsg msg(UM_CLOSEWORKSPACE);
        NotifyAllObservers(&msg);
    }

    return true;
}

// ************************************************** Fichiers **************************************************

CDocument* ZAApp::OpenWorkspaceFile(LPCSTR fileName)
{
    if (!CloseCurrentAndAllocateNewWorkspace())
    {
        return NULL;
    }

    // Open the new workspace
    if (!m_pWorkspaceEnvDocument->ReadFromFile(fileName))
    {
        // Display error message
        return NULL;
    }

    PSS_WorkspaceEnv* pEnv = GetCurrentWorkspaceEnvironment();

    if (!pEnv)
    {
        // Display error message
        return NULL;
    }

    // Set the new workspace file name
    m_WorkspaceFileName = fileName;

    // Notify observers about the workspace initialisation
    PSS_WorkspaceObserverMsg msg(UM_INITWORKSPACE, pEnv);
    NotifyAllObservers(&msg);

    return m_pWorkspaceEnvDocument;
}

void ZAApp::SaveWorkspaceFile(LPCSTR fileName)
{
    ASSERT(m_pWorkspaceEnvDocument != NULL);

    // And save it
    m_pWorkspaceEnvDocument->SaveToFile(fileName);

    // Reset the modified flag
    m_pWorkspaceEnvDocument->SetModifiedFlag(FALSE);
}

bool ZAApp::SaveCurrentWorkspace()
{
    bool bRetValue = true;

    if (WorkspaceEnvironmentExist() && IsWorkspaceEnvironmentLoaded())
    {
        ASSERT(m_pWorkspaceEnvDocument != NULL);

        // Sets the loaded files
        if (GetCurrentWorkspaceEnvironment())
        {
            CStringArray FileArray;
            GetDocumentArrayName(FileArray);
            GetCurrentWorkspaceEnvironment()->SetOpenedFiles(FileArray);
        }

        // And save it
        if (!m_pWorkspaceEnvDocument->SaveToFile(m_WorkspaceFileName))
        {
            bRetValue = false;
        }

        // Reset the modified flag
        m_pWorkspaceEnvDocument->SetModifiedFlag(FALSE);

        // Sets the last open file as the workspace file name
        SetLastLoadedFile(m_pWorkspaceEnvDocument->GetPathName());
    }

    return bRetValue;
}

// ************************************************ Informations ************************************************

bool ZAApp::WorkspaceEnvironmentExist()
{
    return (m_pWorkspaceEnvDocument) ? true : false;
}

bool ZAApp::IsWorkspaceEnvironmentLoaded()
{
    return (m_pWorkspaceEnvDocument && m_pWorkspaceEnvDocument->IsLoaded()) ? true : false;
}

bool ZAApp::IsWorkspaceEnvironmentModified()
{
    if (m_pWorkspaceEnvDocument)
    {
        // return the flag of the document and the environement
        return (m_pWorkspaceEnvDocument->IsModified()) ? true : false;
    }

    return false;
}

// **************************************************************************************************************
// *                                      Espaces de travail auxiliaires                                        *
// **************************************************************************************************************

// ************************************************* Processus **************************************************

// Cette fonction permet d'obtenir le pointeur sur l'espace de travail de la fenêtre des processus.
ZVProcessWorkspace* ZAApp::GetProcessWorkspace()
{
    ZIMainFrame* pFrame = GetMainFrame();

    if (pFrame)
    {
        return pFrame->GetWorkspace();
    }

    return NULL;
}

// ************************************************** Messages **************************************************

// Cette fonction permet d'obtenir le pointeur sur l'espace de travail de la fenêtre des messages.
ZVOutputWorkspace* ZAApp::GetOutputWorkspace()
{
    ZIMainFrame* pFrame = GetMainFrame();

    if (pFrame)
    {
        return pFrame->GetOutputWorkspace();
    }

    return NULL;
}

// ************************************************* Propriétés *************************************************

// Cette fonction permet d'obtenir le pointeur sur l'espace de travail de la fenêtre des propriétés.
ZVPropertiesWorkspace* ZAApp::GetPropertiesWorkspace()
{
    ZIMainFrame* pFrame = GetMainFrame();

    if (pFrame)
    {
        return pFrame->GetPropertiesWorkspace();
    }

    return NULL;
}

// ********************************************* Project Window Bar *********************************************

// Cette fonction permet d'obtenir le pointeur sur l'espace de travail de la barre d'outils des projets.
PSS_ProjectBar* ZAApp::GetProjectWindowBar()
{
    ZIMainFrame* pFrame = GetMainFrame();

    if (pFrame)
        return &pFrame->GetProjectWindowBar();

    return NULL;
}

// ************************************************* Tip of day *************************************************

// Cette fonction permet d'obtenir le pointeur sur l'espace de travail de la fenêtre "Tip of day".
PSS_TipOfDayBar* ZAApp::GetwndTipOfDayBar()
{
    ZIMainFrame* pFrame = GetMainFrame();

    if (pFrame)
    {
        return &pFrame->GetwndTipOfDayBar();
    }

    return NULL;
}
// ************************************************ User Groups *************************************************

// Cette fonction permet d'obtenir le pointeur sur l'environnement de travail des utilisateurs.
PSS_UserGroupEntity* ZAApp::GetMainUserGroup()
{
    return (m_pUserEntityDocument) ? &m_pUserEntityDocument->GetUserGroupEnvironment() : NULL;
}

// ********************************************** Logical systems ***********************************************

// Cette fonction permet d'obtenir le pointeur sur l'environnement de travail des systèmes logiques.
PSS_LogicalSystemEntity* ZAApp::GetMainLogicalSystem()
{
    return (m_pLogicalSystemDocument) ? &m_pLogicalSystemDocument->GetLogicalSystemEnvironment() : NULL;
}

// ************************************************ Prestations *************************************************

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la fonction GetMainLogicalPrestations.
// Cette fonction permet d'obtenir le pointeur sur l'environnement de travail des prestations.
PSS_LogicalPrestationsEntity* ZAApp::GetMainLogicalPrestations()
{
    return (m_pPrestationsDocument) ? &m_pPrestationsDocument->GetPrestationsEnvironment() : NULL;
}

// ************************************************** Règles ****************************************************

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la fonction GetMainLogicalRules.
// Cette fonction permet d'obtenir le pointeur sur l'environnement de travail des règles.
PSS_LogicalRulesEntity* ZAApp::GetMainLogicalRules()
{
    return (m_pRulesDocument) ? &m_pRulesDocument->GetRulesEnvironment() : NULL;
}

// **************************************************************************************************************
// *                                                    Fonctions                                                *
// **************************************************************************************************************

void ZAApp::SetVisualToolObject(const CString& sClassName)
{
    // find the class
    const CStringArray& Array = PSS_ObjectUtility::GetClassNameArray();

    int index = 0;

    for (int i = 0; i < Array.GetSize(); ++i)
    {
        index = i;

        if (sClassName == Array.GetAt(i))
            break;
    }

    // set the appropriate tool
    switch (index)
    {
        case 0:  PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IE_TT_VToolSelect; break;
        default: PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IE_TT_VToolEdit;   break;
    }
}

// Cette fonction effectue les opérations nécessaires à  la création d'un nouveau modèle
PSS_ProcessGraphModelDoc* ZAApp::FileNewModel()
{
    ASSERT(PSS_Global::GetProcessModelDocumentTemplate() != NULL);

    CWaitCursor Cursor;

    PSS_ProcessGraphModelDoc* pNewFile =
        (PSS_ProcessGraphModelDoc*)PSS_Global::GetProcessModelDocumentTemplate()->OpenDocumentFile(NULL);

    if (!pNewFile)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NORMALTEMPLATE_NF, MB_OK);
        return NULL;
    }

    // JMR-MODIF - Le 14 juillet 2005 - Teste si l'utiliateur a abandonné le processus.
    PSS_DocumentPageSetup* m_pPageSetup = pNewFile->GetPrinterPageSize();

    if (m_pPageSetup != NULL)
    {
        if (m_pPageSetup->IsCancelled())
        {
            pNewFile->OnCloseDocument();
            return NULL;
        }
    }

    ZVModelWorkflowOptions Opt(FALSE, pNewFile);

    if (Opt.DoModal() == IDCANCEL)
    {
        pNewFile->OnCloseDocument();
        return NULL;
    }

    switch (pNewFile->GetNotation())
    {
        case E_MN_Beryl:
        {
            // Retrieve the language assigned to the document
            ELanguage lang = pNewFile->GetLanguage();
            pNewFile->SetNewModel(new PSS_ProcessGraphModelMdlBP(pNewFile->GetTitle()));

            // Sets the language to the document
            pNewFile->SetLanguage(lang);
            break;
        }

        case E_MN_ABC:
            break;

        case E_MN_UML:
            break;

        case E_MN_Unknown:
        default:
        {
            break;
        }
    }

    // Set the type for Template
    pNewFile->SetFileType(PSS_Stamp::IE_FD_TemplateType);

    // Set the path name to empty
    pNewFile->ClearPathName();    // no path name yet

    // Assigns the Main User Group
    pNewFile->AssignMainUserGroup(GetMainUserGroup());

    // Assigns the Main Logical System
    pNewFile->AssignMainLogicalSystem(GetMainLogicalSystem());

    // JMR-MODIF - Le 26 janvier 2006 - Assigne le système de prestations.
    pNewFile->AssignMainLogicalPrestations(GetMainLogicalPrestations());

    // JMR-MODIF - Le 19 novembre 2006 - Assigne le système de règles.
    pNewFile->AssignMainLogicalRules(GetMainLogicalRules());

    // Assigns the current systemdef, userdef and prestationsdef
    pNewFile->AssignCurrentSystemDefGUID();
    pNewFile->AssignCurrentUserDefGUID();
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de l'appel à la fonction AssignCurrentPrestationsDefGUID.
    pNewFile->AssignCurrentPrestationsDefGUID();
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'appel à la fonction AssignCurrentRulesDefGUID.
    pNewFile->AssignCurrentRulesDefGUID();

    // JMR-MODIF - Le 20 juillet 2005 - Attribue la trame de fond à la nouvelle page.
    if (m_pPageSetup != NULL)
    {
        if (m_pPageSetup->GetBackgroundFileName() != _T(""))
        {
            pNewFile->GetFirstModelView()->GetViewport()->
                GetModelController()->SetImage(m_pPageSetup->GetBackgroundFileName(), FALSE);
        }
    }

    return pNewFile;
}

BOOL ZAApp::IsCursorCapturedValid(const CPoint& point, PSS_View* pView)
{
    return TRUE;
}

// **************************************************************************************************************
// *                                                      Evénements                                            *
// **************************************************************************************************************

// ******************************************************* Document *********************************************

// JMR-MODIF - Le 24 avril 2006 - Ajout du nom du fichier dans la fonction pour le test de la lecture seule.
void ZAApp::OnAfterOpenDocument(CDocument* pDoc, const CString& fileName)
{
    ASSERT(pDoc);

    if (ISA(pDoc, PSS_ProcessGraphModelDoc))
    {
        // ******************************************************************************************************
        // JMR-MODIF - Le 24 avril 2006 - Teste si le fichier est en lecture seule.
        PSS_File* theFile = new PSS_File(fileName);

        if (theFile != NULL)
        {
            if (theFile->Exist())
            {
                if (theFile->IsReadOnly() == TRUE)
                {
                    PSS_MsgBox mBox;

                    // JMR-MODIF - Le 7 novembre 2006 - Change le bouton Cancel en bouton déverrouiller.
                    mBox.DoChangeCancelBtnToUnlockBtn();

                    // Warn the user
                    switch (mBox.Show(IDS_FILE_READONLY, MB_YESNOCANCEL))
                    {
                        // L'utilisateur souhaite continuer avec un modèle en lecture seule.
                        case IDYES:
                        {
                            dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(TRUE);
                            break;
                        }

                        // JMR-MODIF - Le 7 novembre 2006 - Autorise le déverrouillage du fichier.
                        case IDCANCEL:
                        {
                            PSS_MsgBox mWarnBox;

                            if (mWarnBox.Show(IDS_FILE_WARN_UNLOCK, MB_YESNO) == IDNO)
                            {
                                dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(TRUE);
                                pDoc->OnCloseDocument();

                                delete theFile;
                                theFile = NULL;

                                return;
                            }
                            else
                            {
                                theFile->SetReadOnly(TRUE);
                                dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(FALSE);
                            }

                            break;
                        }

                        // L'utilisateur ne souhaite pas continuer avec un modèle en lecture seule.
                        default:
                        case IDNO:
                        {
                            dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(TRUE);
                            pDoc->OnCloseDocument();

                            delete theFile;
                            theFile = NULL;

                            return;
                        }
                    }
                }
                else
                {
                    // Sinon, on verrouille le modèle tant que l'utilisateur travaille avec.
                    theFile->SetReadOnly(TRUE);
                    dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(FALSE);
                }
            }
            else
            {
                dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(FALSE);
            }

            delete theFile;
            theFile = NULL;
        }
        else
        {
            dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->SetReadOnly(FALSE);
        }
        // ******************************************************************************************************

        // Assigns the Main User Group
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->AssignMainUserGroup(GetMainUserGroup());

        // Assigns the Main Logical System
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->AssignMainLogicalSystem(GetMainLogicalSystem());

        // JMR-MODIF - Le 2 février 2006 - Ajout du code d'assignement pour les prestations
        // Assigns the Main Prestations
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->AssignMainLogicalPrestations(GetMainLogicalPrestations());

        // JMR-MODIF - Le 19 novembre 2006 - Ajout du code d'assignement pour les règles
        // Assigns the Main Rules
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->AssignMainLogicalRules(GetMainLogicalRules());

        // Call the post open document
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->OnPostOpenDocument();

        // Request the change of the resource language
        PSS_ResourceManager::ChangeLanguage(dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetLanguage());
    }
}

void ZAApp::OnAfterSaveDocument(CDocument* pDoc)
{}

// ******************************************************** Options *********************************************

void ZAApp::OnOptions()
{
    PSS_SystemOptionSheet systemOptionsSheet(&GetApplicationOptions(),
                                             PSS_SystemOptionSheet::IEOptionPage(PSS_SystemOptionSheet::IE_OP_General |
                                                                                 PSS_SystemOptionSheet::IE_OP_Calculation |
                                                                                 PSS_SystemOptionSheet::IE_OP_Navigation |
                                                                                 PSS_SystemOptionSheet::IE_OP_ViewReduced));

    // options have changed?
    if (systemOptionsSheet.DoModal() == IDOK)
    {
        // refresh the views
        CObList docList;
        GetDocumentList(docList);

        // iterate through the list in head-to-tail order.
        for (POSITION pPos = docList.GetHeadPosition(); pPos;)
        {
            CDocument* pDocument = (CDocument*)docList.GetNext(pPos);

            if (pDocument)
                pDocument->UpdateAllViews(NULL);
        }

        // save options immediatly
        GetApplicationOptions().SaveOption();
        SaveApplicationOptions();
    }
}

// ******************************************************** Server **********************************************

void ZAApp::OnChooseServer()
{
    ChooseServer();
}

void ZAApp::OnServerHasBeenOpened()
{
    // Put message on the log window
    if (GetOutputWorkspace()->GetLogView())
    {
        CString s;
        s.Format(IDS_LOCALSERVER_OPEN, GetServerIniFile());
        PSS_GenericSymbolErrorLine e(s);
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }

    gFirstTimeChangeServerDirectory = false;
}

void ZAApp::OnServerChanged()
{
    ZAMainApp::OnServerChanged();

    // Save all files first
    OnFileSaveAll();

    // Close the current workspace
    CloseCurrentWorkspace();

    // Releoad the user group file, the system file, the prestations file and the Rules file.
    if (!LoadUserGroupFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_USERGROUPFILE, MB_OK);
    }

    if (!LoadLogicalSystemFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_LOGICALSYSTEMFILEFILE, MB_OK);
    }

    // JMR-MODIF - Le 2 février 2006 - Ajout de l'appel à LoadPrestationsFile
    if (!LoadPrestationsFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_PRESTATIONSFILEFILE, MB_OK);
    }

    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'appel à LoadRulesFile
    if (!LoadRulesFile())
    {
        // Warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILOPEN_RULESFILE, MB_OK);
    }
}

// ****************************************************** Templates *********************************************

bool ZAApp::OnRegisterAdditionalTemplate()
{
    // Set Additionnal document type
    // these documents have no views attached
    // It is necessary to specify call-backs function for FileOpen
    RegisterAdditionalTemplate(IDR_WORKSPACE_REG);
    return true;
}

CDocument* ZAApp::OnOpenAdditionalTemplateFile(LPCSTR fileName)
{
    switch (GetTemplateIDByFileName(fileName))
    {
        case IDR_WORKSPACE_REG:
        {
            return OpenWorkspaceFile(fileName);
        }

        default:
        {
            break;
        }
    }

    return NULL;
}

void ZAApp::OnSaveAdditionalTemplateFile(LPCSTR fileName)
{
    switch (GetTemplateIDByFileName(fileName))
    {
        case IDR_WORKSPACE_REG:
        {
            SaveWorkspaceFile(fileName);
            break;
        }

        default:
        {
            break;
        }
    }
}

// **************************************** Evénements du formulaire UserGroup **********************************

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Ajouter un groupe" du menu contxtuel.
void ZAApp::OnUgpAddGroup()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnAddGroup();
    }
}

// Cette fonction est appelée lorsque l'entrée "Ajouter un groupe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpAddGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanAddGroup() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Supprimer un groupe" du menu contxtuel.
void ZAApp::OnUgpDeleteGroup()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnDeleteGroup();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des symboles et des propriétés.
        DoRefreshSymbolsAndProperties();
    }
}

// Cette fonction est appelée lorsque l'entrée "Supprimer un groupe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpDeleteGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanDeleteGroup() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Renommer un groupe" du menu contxtuel.
void ZAApp::OnUgpRenameGroup()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnRenameGroup();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des symboles et des propriétés.
        DoRefreshSymbolsAndProperties();
    }
}

// Cette fonction est appelée lorsque l'entrée "Renommer un groupe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpRenameGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanRenameGroup() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Ajouter une équipe" du menu contxtuel.
void ZAApp::OnUgpAddRole()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnAddRole();
    }
}

// Cette fonction est appelée lorsque l'entrée "Ajouter une équipe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpAddRole(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanAddRole() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Supprimer l'équipe" du menu contxtuel.
void ZAApp::OnUgpDeleteRole()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnDeleteRole();
    }
}

// Cette fonction est appelée lorsque l'entrée "Supprimer l'équipe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpDeleteRole(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanDeleteRole() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Renommer l'équipe" du menu contxtuel.
void ZAApp::OnUgpRenameRole()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnRenameRole();
    }
}

// Cette fonction est appelée lorsque l'entrée "Renommer l'équipe" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpRenameRole(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanRenameRole() == true);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur l'option "Propriétés" du menu contxtuel.
void ZAApp::OnUgpProperties()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetUserView())
    {
        GetProcessWorkspace()->GetUserView()->OnProperties();
    }
}

// Cette fonction est appelée lorsque l'entrée "Propriétés" du menu contextuel doit être construite.
void ZAApp::OnUpdateUgpProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetUserView() &&
                   GetProcessWorkspace()->GetUserView()->CanProperties() == true);
}

// *************************************** Evénements du formulaire Logical System **************************************

void ZAApp::OnAddLogicalSystem()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetLogicalSystemView())
    {
        GetProcessWorkspace()->GetLogicalSystemView()->OnAddSystem();
    }
}

void ZAApp::OnUpdateAddLogicalSystem(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetLogicalSystemView() &&
                   GetProcessWorkspace()->GetLogicalSystemView()->CanAddSystem() == true);
}

void ZAApp::OnDeleteLogicalSystem()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetLogicalSystemView())
    {
        GetProcessWorkspace()->GetLogicalSystemView()->OnDeleteSystem();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateDeleteLogicalSystem(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetLogicalSystemView() &&
                   GetProcessWorkspace()->GetLogicalSystemView()->CanDeleteSystem() == true);
}

void ZAApp::OnRenameLogicalSystem()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetLogicalSystemView())
    {
        GetProcessWorkspace()->GetLogicalSystemView()->OnRenameSystem();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateRenameLogicalSystem(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetLogicalSystemView() &&
                   GetProcessWorkspace()->GetLogicalSystemView()->CanRenameSystem() == true);
}

void ZAApp::OnLogicalSystemProperties()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetLogicalSystemView())
    {
        GetProcessWorkspace()->GetLogicalSystemView()->OnProperties();
    }
}

void ZAApp::OnUpdateLogicalSystemProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetLogicalSystemView() &&
                   GetProcessWorkspace()->GetLogicalSystemView()->CanProperties() == true);
}

// ******************* JMR-MODIF - Le 13 octobre 2005 - Ajout des événements du formulaire de prestations ***************
// ************************************** Evénements du formulaire de prestations ***************************************

void ZAApp::OnAddPrestation()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetPrestationsView())
    {
        GetProcessWorkspace()->GetPrestationsView()->OnAddPrestation();
    }
}

void ZAApp::OnUpdateAddPrestation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetPrestationsView() &&
                   GetProcessWorkspace()->GetPrestationsView()->CanAddPrestation() == true);
}

void ZAApp::OnDeletePrestation()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetPrestationsView())
    {
        GetProcessWorkspace()->GetPrestationsView()->OnDeletePrestation();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateDeletePrestation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetPrestationsView() &&
                   GetProcessWorkspace()->GetPrestationsView()->CanDeletePrestation() == true);
}

void ZAApp::OnRenamePrestation()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetPrestationsView())
    {
        GetProcessWorkspace()->GetPrestationsView()->OnRenamePrestation();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateRenamePrestation(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetPrestationsView() &&
                   GetProcessWorkspace()->GetPrestationsView()->CanRenamePrestation() == true);
}

void ZAApp::OnPrestationProperties()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetPrestationsView())
    {
        GetProcessWorkspace()->GetPrestationsView()->OnProperties();
    }
}

void ZAApp::OnUpdatePrestationProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetPrestationsView() &&
                   GetProcessWorkspace()->GetPrestationsView()->CanProperties() == true);
}

// ******************** JMR-MODIF - Le 25 novembre 2006 - Ajout des événements du formulaire des règles *****************
// **************************************** Evénements du formulaire de règles ******************************************

void ZAApp::OnAddRule()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetRulesView())
    {
        GetProcessWorkspace()->GetRulesView()->OnAddRule();
    }
}

void ZAApp::OnUpdateAddRule(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetRulesView() &&
                   GetProcessWorkspace()->GetRulesView()->CanAddRule() == true);
}

void ZAApp::OnDeleteRule()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetRulesView())
    {
        GetProcessWorkspace()->GetRulesView()->OnDeleteRule();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateDeleteRule(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetRulesView() &&
                   GetProcessWorkspace()->GetRulesView()->CanDeleteRule() == true);
}

void ZAApp::OnRenameRule()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetRulesView())
    {
        GetProcessWorkspace()->GetRulesView()->OnRenameRule();

        // JMR-MODIF - Le 28 décembre 2006 - Ajout du code pour la mise à jour des propriétés.
        DoRefreshProperties();
    }
}

void ZAApp::OnUpdateRenameRule(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetRulesView() &&
                   GetProcessWorkspace()->GetRulesView()->CanRenameRule() == true);
}

void ZAApp::OnRuleProperties()
{
    if (GetProcessWorkspace() && GetProcessWorkspace()->GetRulesView())
    {
        GetProcessWorkspace()->GetRulesView()->OnProperties();
    }
}

void ZAApp::OnUpdateRuleProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetRulesView() &&
                   GetProcessWorkspace()->GetRulesView()->CanProperties() == true);
}

// ******************************************************** Divers **********************************************

BOOL ZAApp::OnIdle(LONG lCount)
{
    //## begin ZAApp::OnIdle%910633441.body preserve=yes
    if (lCount == 0)
    {
        if (m_pMainWnd != NULL)
        {
            // look for any top-level windows owned by us
            // we use 'HWND's to avoid generation of too many temporary CWnds
            for (HWND hWnd = ::GetWindow(m_pMainWnd->m_hWnd, GW_HWNDFIRST);
                 hWnd != NULL; hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT))
            {
                if (::GetParent(hWnd) == m_pMainWnd->m_hWnd)
                {
                    // if owned window is active, move the activation to the
                    //   application window
                    if (GetActiveWindow() == hWnd && (::GetCapture() == NULL))
                    {
                        m_pMainWnd->SetActiveWindow();
                    }

                    // also update the buttons for the top-level window
                    SendMessage(hWnd, WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0L);
                }
            }
        }
    }

    return CWinApp::OnIdle(lCount);
    //## end ZAApp::OnIdle%910633441.body
}

CString ZAApp::OnBuildHelpFileName()
{
    // Build the help file
    CString HelpFile;

    HINSTANCE hInstance = AfxGetResourceHandle();

    if (hInstance != NULL)
    {
        LPTSTR lpszModule = new TCHAR[_MAX_PATH];

        if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
        {
            PSS_File File(lpszModule);

            HelpFile = PSS_Directory::NormalizeDirectory(File.GetFilePath()) + _T("\\zConceptor.chm");
        }

        delete[]lpszModule;
    }

    return HelpFile;
}

// ********************************************* Fermeture de l'application *************************************

void ZAApp::OnAppExit()
{
    // First close the Pointer window.
    // To go out the pump message of the Pointer window,
    // Posts again the close message
    if (GetMainWindow()->PointerWindowIsVisible())
    {
        GetMainWindow()->HidePointerWindow();
        GetMainWindow()->PostMessage(WM_CLOSE);
        return;
    }

    CWinApp::OnAppExit();
}

// **************************************************************************************************************
// *                                                 Evénements des menus                                        *
// **************************************************************************************************************

// ***************************************************** Menu Fichier *******************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Nouveau projet".
void ZAApp::OnNewWorkspace()
{
    if (!CloseCurrentAndAllocateNewWorkspace())
    {
        return;
    }

    // Start wizard for new workspace
    ZVWorkspaceCreationWizard WksCreation(m_pWorkspaceTemplateManager,
                                          GetModelTemplateDirectory(),
                                          g_WorkspaceExtension);

    if (WksCreation.DoModal() == IDOK)
    {
        PSS_ProcessGraphModelDoc* pNewFile = NULL;
        CString modelFileName = _T("");

        if (WksCreation.GetWorkspaceName() == _T("Projet vide"))
        {
            // Nothing necessary to be created
        }
        else if (WksCreation.GetWorkspaceName() == _T("Projet de base") ||
                 WksCreation.GetWorkspaceName() == _T("Projet Sesterce"))
        {
            // Now create the basic workspace
            pNewFile = FileNewModel();

            if (pNewFile)
            {
                // Set the file name
                modelFileName  = PSS_Directory::NormalizeDirectory(WksCreation.GetDirectory()) + _T("\\");
                modelFileName += WksCreation.GetWorkspaceName();
                modelFileName += g_ModelExtension;

                pNewFile->SetPathName(modelFileName);
                pNewFile->SetModifiedFlag(TRUE);

                // Save the file name
                pNewFile->DoFileSave();
            }
            else
            {
                // Display error
            }

            // Only for sesterce project
            if (WksCreation.GetWorkspaceName() == _T("Projet Sesterce"))
            {
            }
        }

        PSS_WorkspaceEnv* pEnv = GetCurrentWorkspaceEnvironment();

        if (pEnv)
        {
            // Sets the environment's name
            pEnv->SetEntityName(WksCreation.GetWorkspaceName());
            CString s;
            CStringArray a;

            // Create the model group
            s.LoadString(IDS_WKS_GROUP_MODEL);
            a.Add(g_ModelExtensionNoDot);
            pEnv->AddGroup(s, &a);

            if (pNewFile)
            {
                // And add the new create model file
                pEnv->AddFile(modelFileName, s);
            }

            // Create the report group
            s.LoadString(IDS_WKS_GROUP_REPORT);
            a.RemoveAll();
            a.Add(g_ReportExtensionNoDot);
            pEnv->AddGroup(s, &a);

            // Create the document group
            s.LoadString(IDS_WKS_GROUP_DOCUMENT);
            a.RemoveAll();
            a.Add(_T("doc"));
            a.Add(_T("xls"));
            a.Add(_T("ppt"));
            a.Add(_T("htm"));
            a.Add(_T("html"));
            a.Add(_T("pdf"));
            pEnv->AddGroup(s, &a);

            // Notify observers about the workspace initialisation
            PSS_WorkspaceObserverMsg msg(UM_INITWORKSPACE, pEnv);
            NotifyAllObservers(&msg);
        }

        // Set the workspace file name
        m_WorkspaceFileName = WksCreation.GetWorkspaceFileName();
        m_pWorkspaceEnvDocument->SetLoaded(true);

        // And save it
        SaveCurrentWorkspace();
    }
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Ouvrir un projet".
void ZAApp::OnOpenWorkspace()
{
    if (!CloseCurrentAndAllocateNewWorkspace())
    {
        return;
    }

    CString title;
    VERIFY(title.LoadString(IDS_WORKSPACE_FILEOPEN_T));

    // set the "*.klf" files filter
    CString strFilter;
    VERIFY(strFilter.LoadString(IDS_WORKSPACEFILE_FILTER));
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.klf");
    strFilter += (char)'\0';        // last string

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += allFilter;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.*");
    strFilter += (char)'\0';        // last string

    PSS_FileDialog fileDialog(title, strFilter, 2, ZAApp::ZAGetApp()->GetModelTemplateDirectory());

    if (fileDialog.DoModal() == IDOK)
    {
        CWaitCursor Cursor;
        OpenWorkspaceFile(fileDialog.GetFileName());
    }
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Sauvegarder le projet".
void ZAApp::OnSaveWorkspace()
{
    CWaitCursor Cursor;
    SaveCurrentWorkspace();
}

// Cette fonction est appelée lorsque l'entrée "Sauvegarder le projet" doit être mise à jour.
void ZAApp::OnUpdateSaveWorkspace(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(WorkspaceEnvironmentExist() &&
                   IsWorkspaceEnvironmentLoaded() &&
                   IsWorkspaceEnvironmentModified());
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Fermer le projet".
void ZAApp::OnCloseWorkspace()
{
    // Ask before closing all open documents
    CloseCurrentWorkspace(true);
}

// Cette fonction est appelée lorsque l'entrée "Fermer le projet" doit être mise à jour.
void ZAApp::OnUpdateCloseWorkspace(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(WorkspaceEnvironmentExist() && IsWorkspaceEnvironmentLoaded());
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Nouveau modèle".
void ZAApp::OnFileNewModel()
{
    // Call the file creation function
    FileNewModel();

    // Set to the previous file directory
    PSS_Global::SetToFileDirectory();
}

// Cette fonction est appelée lorsque l'entrée "Nouveau modèle" doit être mise à jour.
void ZAApp::OnUpdateFileNewModel(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Ouvrir un modèle".
void ZAApp::OnFileOpenModel()
{
    ASSERT(PSS_Global::GetProcessModelDocumentTemplate() != NULL);

    // Prompt the user (with all document templates)
    CString newName;
    CString initialDirectory = (gFirstTimeChangeServerDirectory == true) ? _T("") : GetModelTemplateDirectory();

    if (!DoPromptFileName(newName,
                          initialDirectory,
                          AFX_IDS_OPENFILE,
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                          TRUE,
                          PSS_Global::GetProcessModelDocumentTemplate()))
    {
        // Open cancelled
        return;
    }

    CWaitCursor Cursor;

    PSS_ProcessGraphModelDoc* pOpenFile = reinterpret_cast<PSS_ProcessGraphModelDoc*>(OpenDocumentFile(newName));

    if (pOpenFile != NULL)
    {
        // Add the opened file to recent file list
        PSS_Global::GetProcessModelDocumentTemplate()->AddToRecentFileList(newName);

        // Set the last loaded file
        SetLastLoadedFile(newName);
    }

    gFirstTimeChangeServerDirectory = true;
}

// Cette fonction est appelée lorsque l'entrée "Ouvrir un modèle" doit être mise à jour.
void ZAApp::OnUpdateFileOpenModel(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

// Cette fonction est appelée lorsque l'entrée "Enregistrer" doit être mise à jour.
void ZAApp::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveCDocument() && GetActiveCDocument()->IsModified());
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Enregistrer en tant que page Web".
void ZAApp::OnExportModelToHTMLFile()
{
    ZUPublishReportInfo* m_pReportInfo = new ZUPublishReportInfo();

    if (m_pReportInfo != NULL)
    {
        PSS_PublishModelToHTML::ExportModelToHTMLFile(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument()),
                                                      dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())->GetFirstModelView(),
                                                      m_pReportInfo,
                                                      m_pszProfileName);

        ZUPublishReportToHTML::ExportReportToHTMLFile(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument()),
                                                      m_pReportInfo);

        if (m_pReportInfo->DoLaunchBrowser == TRUE)
        {
            PSS_PublishModelToHTML::LaunchBrowser(m_pReportInfo->IndexName);
        }

        delete m_pReportInfo;
        m_pReportInfo = NULL;

        // JMR-MODIF - Le 28 février 2006 - La réattribution du langage d'origine se fait maintenant ici.
        PSS_ResourceManager::ChangeLanguage(dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument())->GetLanguage());
    }
}

// Cette fonction est appelée lorsque l'entrée "Enregistrer en tant que page Web" doit être mise à jour.
void ZAApp::OnUpdateExportModelToHTMLFile(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Tout enregistrer".
void ZAApp::OnFileSaveAll()
{
    // Saves the user group file
    if (!SaveUserGroupFile(false))
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_USERGROUPFILE, MB_OK);
    }

    // Saves the logical system file
    if (!SaveLogicalSystemFile(false))
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_LOGICALSYSTEMFILE, MB_OK);
    }

    // JMR-MODIF - Le 10 octobre 2005 - Sauvegarde le fichier de prestations.
    if (!SavePrestationsFile(false))
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_PRESTATIONSFILE, MB_OK);
    }

    // JMR-MODIF - Le 15 novembre 2006 - Sauvegarde le fichier de règles.
    if (!SaveRulesFile(false))
    {
        // Error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_RULESFILE, MB_OK);
    }

    // JMR-MODIF - Le 9 avril 2007 - Si le nom du fichier est vide, la fonction retourne FALSE. C'est juste une indication
    // qui signifie que le fichier n'a pas pu être modifié, ce qui est logique puisque le nom est vide, mais ceci provoque
    // l'affichage d'un message d'erreur déconcertant pour l'utilisateur, alors qu'il n'y a pas vraiment de problème.
    // Donc, on empêche l'utilisation de cette fonction si le nom du fichier est vide.
    if (m_GlobalHistoricValueFileName.IsEmpty() == false)
    {
        // Saves all historic values
        if (!PSS_Global::SaveToFileHistoricValue(m_GlobalHistoricValueFileName))
        {
            // Warm the user
            PSS_MsgBox mBox;
            mBox.Show(IDS_FAILSAVE_INTERNALDEFINITION, MB_OK);
        }
    }

    // Save the current workspace
    if (!SaveCurrentWorkspace())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_WORKSPACE, MB_OK);
    }

    // Save all modified documents
    if (!SaveAllModifiedNoPrompt())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FAILSAVE_OPENDOCUMENT, MB_OK);
    }

    // Saves the global state for model
    PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(m_pszProfileName);
    PSS_ModelGlobal::SaveGlobalPropertyAttributes();

    // Finally, saves the application options
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

// Cette fonction est appelée lorsque l'entrée "Tout enregistrer" doit être mise à jour.
void ZAApp::OnUpdadeFileSaveAll(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

// JMR-MODIF - Le 18 juillet 2005 - Mets à jour le menu "Aperçu avant impression"
// Cette fonction est appelée lorsque l'entrée "Aperçu avant impression" doit être mise à jour.
void ZAApp::OnUpdateFilePrintPreview(CCmdUI *pCmdUI)
{
    // On va rechercher directement dans le driver les informations nécessaire à la mise à jour.
    // C'est plus rapide et plus efficace que d'aller chercher la réponse de la fonction CanPrint dans
    // le document.
    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    // Recherche une imprimante par défaut.
    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg))
    {
        // JMR-MODIF - Le 23 février 2006 - Permets l'impression même si le format est incorrect.
/*
        DEVMODE FAR *lpDevMode = (DEVMODE FAR *)::GlobalLock( pPrintDlg->hDevMode );

        // Obtient la taille standard.
        short StandardSize = lpDevMode->dmPaperSize;

        if ( StandardSize != DMPAPER_A4 )
        {
            pCmdUI->Enable( FALSE );
        }
        else
        {
            pCmdUI->Enable( TRUE );
        }

        // Déverouille les pointeurs vers les structures de paramètres.
        ::GlobalUnlock( pPrintDlg->hDevMode );
*/
// ********************************************************************************************************
// JMR-MODIF - Le 24 avril 2006 - Teste les imprimantes non prises en charge par le système.

// Obtient les pointeurs vers les deux structures de paramètres.
        DEVNAMES FAR *lpDevNames = (DEVNAMES FAR *)::GlobalLock(pPrintDlg->hDevNames);
        DEVMODE FAR  *lpDevMode = (DEVMODE FAR  *)::GlobalLock(pPrintDlg->hDevMode);

        // Obtient les informations spécifiques au Driver.
        CString szDriver((LPTSTR)lpDevNames + lpDevNames->wDriverOffset);
        CString szDevice((LPTSTR)lpDevNames + lpDevNames->wDeviceOffset);
        CString szOutput((LPTSTR)lpDevNames + lpDevNames->wOutputOffset);

        // Crée un objet CDC basé sur les paramètres courants.
        CDC pDC;
        pDC.CreateDC(szDriver, szDevice, szOutput, lpDevMode);

        // Si le DC n'est pas alloué, l'imprimante n'est pas utilisable. C'est le cas p.ex. avec Adobe Distiller.
        if (pDC == NULL)
        {
            pCmdUI->Enable(FALSE);
        }
        else
        {
            pCmdUI->Enable(TRUE);

            // Désalloue le pointeur du CDC.
            pDC.DeleteDC();
        }

        // Déverouille les pointeurs vers les structures de paramètres.
        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);
        // ********************************************************************************************************
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }

    if (pPrintDlg != NULL)
    {
        delete pPrintDlg;
        pPrintDlg = NULL;
    }
}

// JMR-MODIF - Le 18 juillet 2005 - Mets à jour le menu "Imprimer"
// Cette fonction est appelée lorsque l'entrée "Imprimer" doit être mise à jour.
void ZAApp::OnUpdateFilePrint(CCmdUI *pCmdUI)
{
    // On va rechercher directement dans le driver les informations nécessaire à la mise à jour.
    // C'est plus rapide et plus efficace que d'aller chercher la réponse de la fonction CanPrint dans
    // le document.
    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    // Recherche une imprimante par défaut.
    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg))
    {
        // JMR-MODIF - Le 23 février 2006 - Permets l'impression même si le format est incorrect.
/*
        DEVMODE FAR  *lpDevMode = (DEVMODE FAR *)::GlobalLock( pPrintDlg->hDevMode );

        // Obtient la taille standard.
        short StandardSize = lpDevMode->dmPaperSize;

        if ( StandardSize != DMPAPER_A4 )
        {
            pCmdUI->Enable( FALSE );
        }
        else
        {
            pCmdUI->Enable( TRUE );
        }

        // Déverouille les pointeurs vers les structures de paramètres.
        ::GlobalUnlock( pPrintDlg->hDevMode );
*/

// ********************************************************************************************************
// JMR-MODIF - Le 24 avril 2006 - Teste les imprimantes non prises en charge par le système.

// Obtient les pointeurs vers les deux structures de paramètres.
        DEVNAMES FAR *lpDevNames = (DEVNAMES FAR *)::GlobalLock(pPrintDlg->hDevNames);
        DEVMODE FAR  *lpDevMode = (DEVMODE FAR  *)::GlobalLock(pPrintDlg->hDevMode);

        // Obtient les informations spécifiques au Driver.
        CString szDriver((LPTSTR)lpDevNames + lpDevNames->wDriverOffset);
        CString szDevice((LPTSTR)lpDevNames + lpDevNames->wDeviceOffset);
        CString szOutput((LPTSTR)lpDevNames + lpDevNames->wOutputOffset);

        // Crée un objet CDC basé sur les paramètres courants.
        CDC pDC;
        pDC.CreateDC(szDriver, szDevice, szOutput, lpDevMode);

        // Si le DC n'est pas alloué, l'imprimante n'est pas utilisable. C'est le cas p.ex. avec Adobe Distiller.
        if (pDC == NULL)
        {
            pCmdUI->Enable(FALSE);
        }
        else
        {
            pCmdUI->Enable(TRUE);

            // Désalloue le pointeur du CDC.
            pDC.DeleteDC();
        }

        // Déverouille les pointeurs vers les structures de paramètres.
        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);
        // ********************************************************************************************************
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }

    if (pPrintDlg != NULL)
    {
        delete pPrintDlg;
        pPrintDlg = NULL;
    }
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Propriétés".
void ZAApp::OnFileProperty()
{
    ZVModelWorkflowOptions dlg(true, dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument()));

    // If file properties have changed, set the modified flag
    if (dlg.DoModal() == IDOK)
    {
        // Request the change of the resource language
        PSS_ResourceManager::ChangeLanguage(dlg.GetLanguage());

        // Modified flag
        GetActiveBaseDocument()->SetModifiedFlag();
    }
}

// Cette fonction est appelée lorsque l'entrée "Propriétés" doit être mise à jour.
void ZAApp::OnUpdateFileProperty(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Publier le modèle vers Messenger".
void ZAApp::OnPublishToMessenger()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        // Activate the log tab first
        GetOutputWorkspace()->ActivateWorkflowLogTab();

        ZVPublishToMessengerWizard wz(pCurrentDoc, GetOutputWorkspace()->GetLogWorkflowView(), m_pszProfileName);
        wz.DoModal();
    }
}

// Cette fonction est appelée lorsque l'entrée "Publier le modèle vers Messenger" doit être mise à jour.
void ZAApp::OnUpdatePublishToMessenger(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// **************************************************** Menu Affichage ******************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Afficher la liste des attributs".
void ZAApp::OnDynamicAttributesDisplay()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        ZBPropertySet Set;
        PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(pCurrentDoc->GetModel(), Set);

        ZVChoosePropertyDlg choose(&Set,
                                   2,
                                   false,    // Selection
                                   true,    // AllowItemSelection
                                   false,    // AllowCategorySelection
                                   pCurrentDoc->GetDynamicPropertiesManager(), pCurrentDoc->GetModel());

        if (choose.DoModal() == IDOK)
        {
        }

        // Remove all properties
        ZBPropertyIterator i(&Set);
        ZBProperty* pProp;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            delete pProp;
        }

        Set.RemoveAll();
    }
}

// Cette fonction est appelée lorsque l'entrée "Afficher la liste des attributs" doit être mise à jour.
void ZAApp::OnUpdateDynamicAttributesDisplay(CCmdUI* pCmdUI)
{
    BOOL Enable = FALSE;
    PSS_BaseDocument* pDoc = GetActiveBaseDocument();

    if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc) &&
        dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->HasDynamicPropertiesManager())
    {
        Enable = TRUE;
    }

    pCmdUI->Enable(Enable);
}

// ***************************************************** Menu Projet ********************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Ajouter le fichier au projet".
void ZAApp::OnAddCurrentFileToProject()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    CDocument* pDoc = GetActiveCDocument();
    CString currentFileName = (pDoc) ? pDoc->GetPathName() : _T("");

    if (currentFileName.IsEmpty())
    {
        return;
    }

    // If the file is modified, then saves it first
    if (pDoc->IsModified())
    {
        if (!pDoc->OnSaveDocument(currentFileName))
        {
            // Warm the user
            return;
        }
    }

    GetProcessWorkspace()->GetWorkspaceView()->OnAddFileToProject(currentFileName);
}

// Cette fonction est appelée lorsque l'entrée "Ajouter le fichier au projet" doit être mise à jour.
void ZAApp::OnUpdateAddCurrentFileToProject(CCmdUI* pCmdUI)
{
    CDocument* pDoc = GetActiveCDocument();
    CString currentFileName = (pDoc) ? pDoc->GetPathName() : _T("");

    pCmdUI->Enable(!currentFileName.IsEmpty() &&
                   GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->CanAddCurrentFileToProject(currentFileName));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Nouveau dossier".
void ZAApp::OnWksNewGroup()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    GetProcessWorkspace()->GetWorkspaceView()->OnWksNewGroup();
}

// Cette fonction est appelée lorsque l'entrée "Nouveau dossier" doit être mise à jour.
void ZAApp::OnUpdateWksNewGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->GetSelectedGroup() != NULL ||
                   GetProcessWorkspace()->GetWorkspaceView()->IsRootSelected());
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Renommer le dossier".
void ZAApp::OnWksRenameGroup()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    GetProcessWorkspace()->GetWorkspaceView()->OnWksRenameGroup();
}

// Cette fonction est appelée lorsque l'entrée "Renommer le dossier" doit être mise à jour.
void ZAApp::OnUpdateWksRenameGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->GetSelectedGroup() != NULL);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Supprimer le dossier".
void ZAApp::OnWksDeleteGroup()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_CONF_WKS_DELETEGROUP, MB_YESNO) == IDNO)
        return;

    GetProcessWorkspace()->GetWorkspaceView()->OnWksDeleteGroup();
}

// Cette fonction est appelée lorsque l'entrée "Supprimer le dossier" doit être mise à jour.
void ZAApp::OnUpdateWksDeleteGroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->GetSelectedGroup() != NULL);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Ouvrir le fichier".
void ZAApp::OnWksOpenFile()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    GetProcessWorkspace()->GetWorkspaceView()->OnWksOpenFile();
}

// Cette fonction est appelée lorsque l'entrée "Ouvrir le fichier" doit être mise à jour.
void ZAApp::OnUpdateWksOpenFile(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->GetSelectedFile() != NULL);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Insérer un fichier".
void ZAApp::OnWksAddFile()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    GetProcessWorkspace()->GetWorkspaceView()->OnWksAddFile();
}

// Cette fonction est appelée lorsque l'entrée "Insérer un fichier" doit être mise à jour.
void ZAApp::OnUpdateWksAddFile(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   (GetProcessWorkspace()->GetWorkspaceView()->GetSelectedGroup() != NULL ||
                    GetProcessWorkspace()->GetWorkspaceView()->IsRootSelected()));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Supprimer le fichier".
void ZAApp::OnWksDeleteFile()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_CONF_WKS_DELETEFILE, MB_YESNO) == IDNO)
        return;

    GetProcessWorkspace()->GetWorkspaceView()->OnWksDeleteFile();
}

// Cette fonction est appelée lorsque l'entrée "Supprimer le fichier" doit être mise à jour.
void ZAApp::OnUpdateWksDeleteFile(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   GetProcessWorkspace()->GetWorkspaceView()->GetSelectedFile() != NULL);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Propriétés".
void ZAApp::OnWksProperties()
{
    ASSERT(GetProcessWorkspace()->GetWorkspaceView() != NULL);

    GetProcessWorkspace()->GetWorkspaceView()->OnWksProperties();
}

// Cette fonction est appelée lorsque l'entrée "Propriétés" doit être mise à jour.
void ZAApp::OnUpdateWksProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetProcessWorkspace() &&
                   GetProcessWorkspace()->GetWorkspaceView() &&
                   (GetProcessWorkspace()->GetWorkspaceView()->GetSelectedEntity() != NULL ||
                    GetProcessWorkspace()->GetWorkspaceView()->IsRootSelected()));
}

// ***************************************************** Menu Outils ********************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Assigner au modèle le fichier des groupes".
void ZAApp::OnAssignCurrentUserdef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->AssignCurrentUserDefGUID();
    }
}

// Cette fonction est appelée lorsque l'entrée "Assigner au modèle le fichier des groupes" doit être mise à jour.
void ZAApp::OnUpdateAssignCurrentUserdef(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Assigner au modèle le fichier des systèmes logiques".
void ZAApp::OnAssignCurrentSystemdef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->AssignCurrentSystemDefGUID();
    }
}

// Cette fonction est appelée lorsque l'entrée "Assigner au modèle le fichier des systèmes logiques" doit être mise à jour.
void ZAApp::OnUpdateAssignCurrentSystemdef(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// JMR-MODIF - Le 2 février 2006 - Ajout de la fonction OnAssignCurrentPrestationsDef.
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Assigner au modèle le fichier des prestations".
void ZAApp::OnAssignCurrentPrestationsDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->AssignCurrentPrestationsDefGUID();
    }
}

// JMR-MODIF - Le 2 février 2006 - Ajout de la fonction OnUpdateAssignCurrentPrestationsDef.
// Cette fonction est appelée lorsque l'entrée "Assigner au modèle le fichier des prestations" doit être mise à jour.
void ZAApp::OnUpdateAssignCurrentPrestationsDef(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// JMR-MODIF - Le 3 décembre 2006 - Ajout de la fonction OnAssignCurrentRulesDef.
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Assigner au modèle le fichier des règles".
void ZAApp::OnAssignCurrentRulesDef()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->AssignCurrentRulesDefGUID();
    }
}

// JMR-MODIF - Le 3 décembre 2006 - Ajout de la fonction OnUpdateAssignCurrentRulesDef.
// Cette fonction est appelée lorsque l'entrée "Assigner au modèle le fichier des règles" doit être mise à jour.
void ZAApp::OnUpdateAssignCurrentRulesDef(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Réassigner les groupes aux symboles".
void ZAApp::OnSymbolReassignUsergroup()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->ReassignUnit(GetOutputWorkspace()->GetLogView());
    }
}

// Cette fonction est appelée lorsque l'entrée "Réassigner les groupes aux symboles" doit être mise à jour.
void ZAApp::OnUpdateSymbolReassignUsergroup(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Réassigner les systèmes logiques aux symboles".
void ZAApp::OnSymbolReassignLogicalsys()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->ReassignSystem(GetOutputWorkspace()->GetLogView());
    }
}

// Cette fonction est appelée lorsque l'entrée "Réassigner les systèmes logiques aux symboles" doit être mise à jour.
void ZAApp::OnUpdateSymbolReassignLogicalsys(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// JMR-MODIF - Le 2 février 2006 - Ajout de la fonction OnSymbolReassignPrestations.
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Réassigner les prestations aux symboles".
void ZAApp::OnSymbolReassignPrestations()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->ReassignPrestations(GetOutputWorkspace()->GetLogView());
    }
}

// JMR-MODIF - Le 2 février 2006 - Ajout de la fonction OnUpdateSymbolReassignPrestations.
// Cette fonction est appelée lorsque l'entrée "Réassigner les prestations aux symboles" doit être mise à jour.
void ZAApp::OnUpdateSymbolReassignPrestations(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// JMR-MODIF - Le 3 décembre 2006 - Ajout de la fonction OnSymbolReassignRules.
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Réassigner les règles aux symboles".
void ZAApp::OnSymbolReassignRules()
{
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (pCurrentDoc)
    {
        pCurrentDoc->ReassignRules(GetOutputWorkspace()->GetLogView());
    }
}

// JMR-MODIF - Le 3 décembre 2006 - Ajout de la fonction OnUpdateSymbolReassignRules.
// Cette fonction est appelée lorsque l'entrée "Réassigner les règles aux symboles" doit être mise à jour.
void ZAApp::OnUpdateSymbolReassignRules(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() && ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc));
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport de contrôle".
void ZAApp::OnGenerateCheckReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc->GetModel() || !ISA(pCurrentDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
    {
        return;
    }

    CWaitCursor Cursor;

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report

        pNewFile->SetNewReportGridGenerator(new ZBCheckReportGenerator(pNewFile,
                                                                       dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                       pCurrentDoc));

        PSS_File file(pCurrentDoc->GetPathName());
        CString s;
        s.LoadString(IDS_CHECKREPORT_FILENAME);
        CString fn = file.GetFilePath() + s + file.GetFileTitle();
        CString strFilterExt;
        PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
        fn += strFilterExt;
        pNewFile->SetPathName(fn);

        // After the file name assignement, update the frame title
        pNewFile->UpdateFrameTitle();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// Cette fonction est appelée lorsque l'entrée "Générer le rapport de contrôle" doit être mise à jour.
void ZAApp::OnUpdateGenerateCheckReport(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() &&
                   ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc) &&
                   ((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetNotation() == E_MN_Beryl);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Mercutio".
void ZAApp::OnGenerateMercutioReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    CWaitCursor Cursor;

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc->GetModel() || !ISA(pCurrentDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
    {
        return;
    }

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report

        // Let the user choose a sub-process
        // filter object classes
        PSS_RuntimeClassSet rtClasses;
        rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
        rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

        PSS_SelectModelSymbolDlg Dlg(dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                     IDS_MERCUTIOREP_SELECTPROCESS,
                                     g_Selectable_Model | g_Selectable_GraphPage,
                                     &rtClasses);

        if (Dlg.DoModal() == IDOK)
        {
            if (Dlg.GetSelectedSymbol() && ISA(Dlg.GetSelectedSymbol(), PSS_ProcessSymbolBP))
            {
                CWaitCursor Cursor2;
                pNewFile->SetNewReportGridGenerator(new ZBMercutioReportGenerator(pNewFile,
                                                                                  dynamic_cast<PSS_ProcessGraphModelMdlBP*>(dynamic_cast<PSS_ProcessSymbolBP*>(Dlg.GetSelectedSymbol())->GetChildModel()),
                                                                                  pCurrentDoc));

                PSS_File file(pCurrentDoc->GetPathName());

                CString fn = file.GetFilePath() +
                    dynamic_cast<PSS_Symbol*>(Dlg.GetSelectedSymbol())->GetSymbolName() +
                    _T(" - ") +
                    file.GetFileTitle();

                CString strFilterExt;
                PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
                fn += strFilterExt;
                pNewFile->SetPathName(fn);

                // After the file name assignement, update the frame title
                pNewFile->UpdateFrameTitle();

                return;
            }
        }

        // Otherwise, close the document
        pNewFile->SetModifiedFlag(FALSE);
        pNewFile->OnCloseDocument();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// Cette fonction est appelée lorsque l'entrée "Générer le rapport Mercutio" doit être mise à jour.
void ZAApp::OnUpdateGenerateMercutioReport(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() &&
                   ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc) &&
                   ((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetNotation() == E_MN_Beryl);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Conceptor".
void ZAApp::OnGenerateConceptorReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    CWaitCursor Cursor;

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    if (!pCurrentDoc->GetModel() || !ISA(pCurrentDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
    {
        return;
    }

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        ZVConceptorReportOptions Dlg;

        if (Dlg.DoModal() == IDOK)
        {
            CWaitCursor Cursor2;

            // JMR-MODIF - Le 6 mars 2006 - Suppression de l'option Synthesys, car apparamment non implémentée.
            pNewFile->SetNewReportGridGenerator(new ZBConceptorReportGenerator(pNewFile,
                                                                               dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                               pCurrentDoc,
                                                                               TRUE,//Dlg.m_Synthesis,
                                                                               Dlg.m_Detail,
                                                                               Dlg.m_Deliverables));

            PSS_File file(pCurrentDoc->GetPathName());
            CString s;
            s.LoadString(IDS_CONCEPTORREPORT_FILENAME);
            CString fn = file.GetFilePath() + s + file.GetFileTitle();
            CString strFilterExt;
            PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
            fn += strFilterExt;
            pNewFile->SetPathName(fn);

            // After the file name assignement, update the frame title
            pNewFile->UpdateFrameTitle();

            return;
        }

        // Otherwise, close the document
        pNewFile->SetModifiedFlag(FALSE);
        pNewFile->OnCloseDocument();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// Cette fonction est appelée lorsque l'entrée "Générer le rapport Conceptor" doit être mise à jour.
void ZAApp::OnUpdateGenerateConceptorReport(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetActiveBaseDocument() &&
                   ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc) &&
                   ((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetNotation() == E_MN_Beryl);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Sesterces".
void ZAApp::OnGenerateSesterceReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    CWaitCursor Cursor;

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report
        pNewFile->SetNewReportGridGenerator(new ZBSesterceReportGenerator(pNewFile,
                                                                          dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                          pCurrentDoc));

        PSS_File file(pCurrentDoc->GetPathName());
        CString s;
        s.LoadString(IDS_SESTERCES_FILENAME);
        CString fn = file.GetFilePath() + s + file.GetFileTitle();
        CString strFilterExt;
        PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
        fn += strFilterExt;
        pNewFile->SetPathName(fn);

        // After the file name assignement, update the frame title
        pNewFile->UpdateFrameTitle();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// Cette fonction est appelée lorsque l'entrée "Générer le rapport Sesterces" doit être mise à jour.
void ZAApp::OnUpdateGenerateSesterceReport(CCmdUI* pCmdUI)
{
    if (!GetActiveBaseDocument() || !ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetIntegrateCostSimulation() &&
        ((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetNotation() == E_MN_Beryl);
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Sesterces Unités".
void ZAApp::OnGenerateSesterceUnitReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    // Display the wizard for the report creation
    ZVReportCreationWizard dlg(true, false);

    if (dlg.DoModal() == IDCANCEL)
    {
        return;
    }

    CWaitCursor Cursor;

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report
        pNewFile->SetNewReportGridGenerator(new ZBSesterceUnitReportGenerator(pNewFile,
                                                                              dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                              pCurrentDoc,
                                                                              dlg.IncludeMonthDetail()));

        PSS_File file(pCurrentDoc->GetPathName());
        CString s;
        s.LoadString(IDS_SESTERCESUNIT_FILENAME);
        CString fn = file.GetFilePath() + s + file.GetFileTitle();
        CString strFilterExt;
        PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
        fn += strFilterExt;
        pNewFile->SetPathName(fn);

        // After the file name assignement, update the frame title
        pNewFile->UpdateFrameTitle();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Sesterces Consolidé".
void ZAApp::OnGenerateSesterceConsolidatedReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    //    Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    // Display the wizard for the report creation
    ZVReportCreationWizard dlg(true, false);

    if (dlg.DoModal() == IDCANCEL)
    {
        return;
    }

    CWaitCursor Cursor;

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report
        pNewFile->SetNewReportGridGenerator(new ZBSesterceConsolidatedReportGenerator(pNewFile,
                                                                                      dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                                      pCurrentDoc,
                                                                                      dlg.IncludeMonthDetail()));

        PSS_File file(pCurrentDoc->GetPathName());
        CString s;
        s.LoadString(IDS_SESTERCESCONSOLIDATED_FILENAME);
        CString fn = file.GetFilePath() + s + file.GetFileTitle();
        CString strFilterExt;
        PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);
        fn += strFilterExt;
        pNewFile->SetPathName(fn);

        // After the file name assignement, update the frame title
        pNewFile->UpdateFrameTitle();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// JMR-MODIF - Le 6 mars 2006 - Ajout de la fonction OnGeneratePrestationsReport.
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Générer le rapport Prestations".
void ZAApp::OnGeneratePrestationsReport()
{
    ASSERT(PSS_Global::GetReportDocumentTemplate() != NULL);

#ifdef _DEBUG
    COleDateTime start = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)start.Format(_T("Start time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif

    // Return the casted active base document.
    PSS_ProcessGraphModelDoc* pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveBaseDocument());

    // Display the wizard for the report creation
    ZVReportCreationWizard dlg(true, false);

    if (dlg.DoModal() == IDCANCEL)
    {
        return;
    }

    CWaitCursor Cursor;

    // Create an empty report document file
    ZDGridReportDocument* pNewFile =
        (ZDGridReportDocument*)PSS_Global::GetReportDocumentTemplate()->OpenDocumentFile(NULL);

    if (pNewFile)
    {
        // Now we have an empty grid report
        pNewFile->SetNewReportGridGenerator(new ZBPrestationsReportGenerator(pNewFile,
                                                                             dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCurrentDoc->GetModel()),
                                                                             pCurrentDoc,
                                                                             dlg.IncludeMonthDetail()));

        CString s;
        CString strFilterExt;
        PSS_File file(pCurrentDoc->GetPathName());

        s.LoadString(IDS_PRESTATIONSREPORT_FILENAME);

        CString fn = file.GetFilePath() + s + file.GetFileTitle();

        PSS_Global::GetReportDocumentTemplate()->GetDocString(strFilterExt, CDocTemplate::filterExt);

        fn += strFilterExt;

        pNewFile->SetPathName(fn);

        // After the file name assignement, update the frame title
        pNewFile->UpdateFrameTitle();
    }

#ifdef _DEBUG
    COleDateTime end = COleDateTime::GetCurrentTime();

    if (GetOutputWorkspace()->GetLogView())
    {
        ZBGenericSymbolErrorLine e((const char*)end.Format(_T("End time= %H : %M : %S")));
        GetOutputWorkspace()->GetLogView()->AddLine(e);
    }
#endif
}

// JMR-MODIF - Le 6 mars 2006 - Ajout de la fonction OnUpdateGeneratePrestationsReport.
// Cette fonction est appelée lorsque l'entrée "Générer le rapport Prestations" doit être mise à jour.
void ZAApp::OnUpdateGeneratePrestationsReport(CCmdUI* pCmdUI)
{
    if (!GetActiveBaseDocument() || !ISA(GetActiveBaseDocument(), PSS_ProcessGraphModelDoc))
    {
        pCmdUI->Enable(FALSE);
        return;
    }

    pCmdUI->Enable(((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetIntegrateCostSimulation() &&
        ((PSS_ProcessGraphModelDoc*)GetActiveBaseDocument())->GetNotation() == E_MN_Beryl);
}

// ******************************************************** Menu ? **********************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "A propos de Conceptor".
void ZAApp::OnAppAbout()
{
    PSS_HtmlDialog About(IDR_ABOUT_CONCEPTOR_02);

    About.SetSize(600, 600);

    About.DoModal();
}

// ****************************************************** Menu Aide *********************************************

// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Support".
void ZAApp::OnHelpSupport()
{
    PSS_HtmlDialog About(IDR_SUPPORT_CONCEPTOR_02);

    About.SetSize(600, 600);

    About.DoModal();
}
// *************************************** Fonctions concernant des menus inattribués ***************************

// JMR-MODIF - Le 20 juillet 2005 - Supprimé l'option "Mise en page".
// Cette fonction est appelée lorsque l'utilisateur choisit l'entrée "Mise en page".
/*void ZAApp::OnFilePrintSetup()
{
    // Standard print setup command
    CWinApp::OnFilePrintSetup();

    PSS_Document *pDoc = GetActiveDocument();
    // If the page size has changed, recalculate the page
    if (pDoc)
    {
        pDoc->GetMainView()->SetZoomPercentage( pDoc->GetMainView()->GetZoomPercentage() );
        pDoc->UpdateAllViews( NULL );
    }
}*/

void ZAApp::OnFileOpen()
{
    ZAMainApp::OnFileOpen();
}

void ZAApp::OnProcessFileOpen()
{
    ASSERT(FALSE);
    return;
}
