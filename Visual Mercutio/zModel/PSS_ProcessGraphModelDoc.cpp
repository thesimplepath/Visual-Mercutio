/****************************************************************************
 * ==> PSS_ProcessGraphModelDoc --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model document                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelDoc.h"

// processsoft
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zBaseLib\PSS_GUID.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zMediator\PSS_Application.h"
#include "zProperty\ZBDynamicPropertiesManager.h"
#include "PSS_ProcessGraphModelView.h"
#include "PSS_ProcessGraphChildFrame.h"
#include "PSS_ProcessGraphModelController.h"
#include "PSS_DocObserverMsg.h"
#include "ZBUnitObserverMsg.h"
#include "PSS_LogicalSystemEntity.h"
#include "PSS_GenericSymbolErrorLine.h"

// resources
#include "zModelRes.h"

// windows
#include <io.h>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcessGraphModelDoc, PSS_BaseDocument, g_DefVersion)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessGraphModelDoc, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_ProcessGraphModelDoc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelDoc
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc::PSS_ProcessGraphModelDoc() :
    PSS_BaseDocument(),
    m_pModel(NULL),
    m_pUserManager(NULL),
    m_pMail(NULL),
    m_pTemplateManager(NULL),
    m_DynamicPropertiesManager(NULL),
    m_pUnitManager(NULL),
    m_pWorkflowDefinition(NULL),
    m_pOutputLog(NULL),
    m_pAnalyzerLog(NULL),
    m_pSearchLog(NULL),
    m_pWorflowLog(NULL),
    m_HourPerDay(0),
    m_DayPerWeek(0),
    m_DayPerMonth(0),
    m_DayPerYear(0),
    m_StandardSize(-1),
    m_Orientation(-1),
    m_IsDocumentClosing(FALSE),
    m_IsReadOnly(FALSE),
    m_IsInModelCreation(false),
    m_UseWorkflow(false),
    m_BrowseInSameWindow(false),
    m_IntegrateCostSimulation(false),
    m_CheckConsistency(false),
    m_ShowPageBorder(false)
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc::~PSS_ProcessGraphModelDoc()
{
    DeleteWorkflowDefinition();

    // delete the dynamic properties manager
    if (m_DynamicPropertiesManager)
        delete m_DynamicPropertiesManager;

    // delete the model
    if (m_pModel)
    {
        PSS_ProcessGraphModelMdl* pRoot = m_pModel->GetRoot();

        if (pRoot)
            pRoot->DeleteModelSet();

        delete m_pModel;
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::Initialize(PSS_Log*           pOutputLog,
                                          PSS_Log*           pAnalyzerLog,
                                          PSS_Log*           pSearchLog,
                                          PSS_Log*           pWorflowLog,
                                          ZUUserManager*     pUserManager,
                                          ZUMail*            pMail,
                                          ZDTemplateManager* pTemplateManager)
{
    m_pUserManager     = pUserManager;
    m_pMail            = pMail;
    m_pTemplateManager = pTemplateManager;
    m_pOutputLog       = pOutputLog;
    m_pAnalyzerLog     = pAnalyzerLog;
    m_pSearchLog       = pSearchLog;
    m_pWorflowLog      = pWorflowLog;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::PreCloseFrame(CFrameWnd* pFrame)
{
    PSS_ProcessGraphModelView* pView = dynamic_cast<PSS_ProcessGraphModelView*>(pFrame->GetActiveView());

    if (pView)
    {
        // notify all document observers about the document closing
        PSS_DocumentObserverMsg msg(UM_CLOSEDOCUMENT, this);
        NotifyAllObservers(&msg);

        if (m_pModel)
        {
            // also notify all model observers
            m_pModel->NotifyAllObservers(&msg);

            PSS_ProcessGraphModelMdl* pRoot = m_pModel->GetRoot();

            if (pRoot)
                pRoot->DetachAllObserversInHierarchy(pView->GetViewport(), this);

            m_pModel->RemoveObserver(pView->GetViewport());
            m_pModel->DetachObserver(this);
        }

        m_EmptyModel.RemoveObserver(pView->GetViewport());
        m_EmptyModel.DetachObserver(this);
    }

    // call the base class function
    PSS_BaseDocument::PreCloseFrame(pFrame);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::IsClosing()
{
    return m_IsDocumentClosing;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::AssignCurrentUserDefGUID()
{
    ZBUserGroupEntity* pUserGroup = GetMainUserGroup();

    // no user group, error
    if (!pUserGroup)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_USERGROUP);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        return false;
    }

    // assign the current GUID
    AssignUserDefGUID(pUserGroup->GetGUID());

    if (m_pOutputLog)
    {
        CString message;
        message.LoadString(IDS_USERGROUP_ASSIGNED);
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    // main user group is valid
    if (pModel)
        pModel->SetMainUserGroupValid();

    // modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::ReassignUnit(PSS_Log* pLog)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_UNITREASSIGN_START);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    // main user group is not valid
    if (pModel->MainUserGroupIsValid())
        pModel->ReassignUnit(pLog);
    else
    {
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_UNITCANNOTREASSIGN);
            PSS_GenericSymbolErrorLine error(message);
            pLog->AddLine(error);
        }

        return;
    }

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_UNITREASSIGN_STOP);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::AssignCurrentSystemDefGUID()
{
    PSS_LogicalSystemEntity* pSystem = GetMainLogicalSystem();

    // no system, error
    if (!pSystem)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_SYSTEMDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        return false;
    }

    // assign the current system
    AssignSystemDefGUID(pSystem->GetGUID());

    if (m_pOutputLog)
    {
        CString message;
        message.LoadString(IDS_SYSTEMDEFXML_ASSIGNED);
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    // main logical system is valid
    if (pModel)
        pModel->SetMainLogicalSystemValid();

    // modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::ReassignSystem(PSS_Log* pLog)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_SYSTEMREASSIGN_START);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    // if the logical system file is valid, iterate through elements and assign system
    if (pModel->MainLogicalSystemIsValid())
        pModel->ReassignSystem(pLog);
    else
    {
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_SYSTEMCANNOTREASSIGN);
            PSS_GenericSymbolErrorLine error(message);
            pLog->AddLine(error);
        }

        return;
    }

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_SYSTEMREASSIGN_STOP);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::AssignCurrentPrestationsDefGUID()
{
    PSS_LogicalPrestationsEntity* pPrestations = GetMainLogicalPrestations();

    // no prestations, error
    if (!pPrestations)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_PRESTATIONSDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        return false;
    }

    // assign the current GUID
    AssignPrestationsDefGUID(pPrestations->GetGUID());

    if (m_pOutputLog)
    {
        CString message;
        message.LoadString(IDS_PRESTATIONS_ASSIGNED);
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    // main prestation is valid
    if (pModel)
        pModel->SetMainLogicalPrestationsValid();

    // modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::ReassignPrestations(PSS_Log* pLog)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_PRESTATIONSREASSIGN_START);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    // main prestations is not valid
    if (pModel->MainLogicalPrestationsIsValid())
        pModel->ReassignPrestations(pLog);
    else
    {
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_PRESTATIONSCANNOTREASSIGN);
            PSS_GenericSymbolErrorLine error(message);
            pLog->AddLine(error);
        }

        return;
    }

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_PRESTATIONSREASSIGN_STOP);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::AssignCurrentRulesDefGUID()
{
    PSS_LogicalRulesEntity* pRules = GetMainLogicalRules();

    // no Rules, error
    if (!pRules)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_RULESDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        return false;
    }

    // assign the current GUID
    AssignRulesDefGUID(pRules->GetGUID());

    if (m_pOutputLog)
    {
        CString message;
        message.LoadString(IDS_RULES_ASSIGNED);
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    // main rule is valid
    if (pModel)
        pModel->SetMainLogicalRulesValid();

    // modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::ReassignRules(PSS_Log* pLog /*= NULL*/)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_RULESREASSIGN_START);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    // main rules are not valid
    if (pModel->MainLogicalRulesIsValid())
        pModel->ReassignRules(pLog);
    else
    {
        if (pLog)
        {
            CString message;
            message.LoadString(IDS_AL_RULESCANNOTREASSIGN);
            PSS_GenericSymbolErrorLine error(message);
            pLog->AddLine(error);
        }

        return;
    }

    if (pLog)
    {
        CString message;
        message.LoadString(IDS_AL_RULESREASSIGN_STOP);
        PSS_GenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetPageUnits(ZBPageUnits& value)
{
    m_PageUnits = value;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetPageUnits(CODRuler& value)
{
    m_PageUnits = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::InsertUnit(const CString& fileName)
{
    PSS_File file(fileName);

    if (!file.Exist())
        return false;

    if (!m_pUnitManager)
        CreateUnitManager();

    ZBUnit* pUnit = m_pUnitManager->CreateNewUnit(_T(""), fileName);

    if (!pUnit)
        return false;

    if (!m_pUnitManager->LoadUnit(pUnit))
        return false;

    m_pUnitManager->FillModelSet(m_UnitModelSet);

    CWnd* pMainWnd = AfxGetMainWnd();
    ASSERT(pMainWnd);

    // build the message
    ZBUnitObserverMsg UnitMsg(ZBUnitObserverMsg::OpenUnit, NULL, pUnit);
    pMainWnd->SendMessageToDescendants(UM_ADDUNITMODEL, 0, LPARAM(&UnitMsg));

    // model has been modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::LoadAllUnits()
{
    if (m_pUnitManager)
        return m_pUnitManager->LoadAllUnits();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GenerateModelWorkflow()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);
    return pModel->GenerateModelWorkflow(m_pOutputLog, this);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::CheckModelWorkflow(BOOL ModelIsClean)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);
    return pModel->CheckModelWorkflow(m_pOutputLog, ModelIsClean);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::DeleteWorkflowDefinition()
{
    if (m_pWorkflowDefinition)
        delete m_pWorkflowDefinition;

    m_pWorkflowDefinition = NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetUseWorkflow(bool value)
{
    if (value)
    {
        if (!m_pWorkflowDefinition)
            m_pWorkflowDefinition = new ZBWorkflowDefinition;
    }
    else
        // delete the workflow definition object to clear the workflow usage
        DeleteWorkflowDefinition();

    m_UseWorkflow = value;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetNewModel(PSS_ProcessGraphModelMdl* pModel)
{
    if (m_pModel)
        delete m_pModel;

    m_pModel = NULL;

    // assign new created model
    m_pModel = pModel;

    // if a new model is defined, create the first page
    if (m_pModel && !m_pModel->MainPageSetExist())
        m_pModel->CreateNewPage(m_pModel);

    // now create the new associated viewport
    PSS_ProcessGraphModelView* pView = GetFirstModelView();

    if (pView && m_pModel)
    {
        PSS_ProcessGraphModelViewport* pViewport = pView->GetViewport();

        if (pViewport)
        {
            // create the new associated model controller and assigns it to the viewport
            pViewport->AssignNewController(m_pModel->CreateController(pView->GetViewport()), m_pModel);

            // set the new model
            pView->SetModel(m_pModel);

            // initialize the viewport
            pViewport->OnInitialUpdate();
        }

        // switch the context
        PSS_FloatingToolBar::SwitchContext(m_pModel->GetNotation());

        // build the message
        PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_OpenDocument, this);
        AfxGetMainWnd()->SendMessageToDescendants(UM_INITIALIZEDOCUMENTMODEL, 0, LPARAM(&docMsg));
    }
}
//---------------------------------------------------------------------------
PSS_DocumentPageSetup* PSS_ProcessGraphModelDoc::GetPrinterPageSize()
{
    PSS_ProcessGraphModelView* pView = GetFirstModelView();

    if (pView)
    {
        // the only condition where m_StandardSize and m_Orientation aren't equals to -1
        // is after the serialization, if a document was opened. So the page structure
        // should be updated
        if (m_StandardSize != -1 && m_Orientation != -1)
            pView->SetPrinterPageSize(m_PaperSize, m_StandardSize, m_Orientation);

        return pView->GetPrinterPageSize();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelView* PSS_ProcessGraphModelDoc::GetFirstModelView()
{
    POSITION pPos  = GetFirstViewPosition();
    CView*   pView = GetNextView(pPos);

    // iterate through all views
    while (pView)
    {
        if (ISA(pView, PSS_ProcessGraphModelView))
            return static_cast<PSS_ProcessGraphModelView*>(pView);

        pView = GetNextView(pPos);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CView* PSS_ProcessGraphModelDoc::FindView(const CString& name)
{
    POSITION pPos  = GetFirstViewPosition();
    CView*   pView = GetNextView(pPos);

    // iterate through all views
    while (pView)
    {
        if (ISA(pView, PSS_ProcessGraphModelView))
            if (static_cast<PSS_ProcessGraphModelView*>(pView)->GetViewName() == name)
                return pView;

        pView = GetNextView(pPos);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CView* PSS_ProcessGraphModelDoc::ActivateView(const CString& name)
{
    CView* pView = FindView(name);

    if (pView)
    {
        PSS_ProcessGraphChildFrame* pWnd = dynamic_cast<PSS_ProcessGraphChildFrame*>(pView->GetParent());

        if (pWnd)
        {
            CMDIFrameWnd* pMainWnd = dynamic_cast<CMDIFrameWnd*>(AfxGetMainWnd());

            if (pMainWnd)
            {
                pMainWnd->MDIActivate(pWnd);
                return pView;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
CView* PSS_ProcessGraphModelDoc::SwitchView(CView* pNewView, std::size_t index)
{
    CFrameWnd* pMainWnd = dynamic_cast<CFrameWnd*>(AfxGetMainWnd());

    if (!pMainWnd)
        return NULL;

    CView* pActiveView = pMainWnd->GetActiveView();

    if (!pActiveView)
        return NULL;

    // get the view identifier
    const UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);

    ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
    ::SetWindowLong(pNewView->m_hWnd,    GWL_ID, temp);

    pActiveView->ShowWindow(SW_HIDE);
    pNewView->ShowWindow(SW_SHOW);

    pMainWnd->SetActiveView(pNewView);
    pMainWnd->RecalcLayout();

    pNewView->Invalidate();

    return pActiveView;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::IsModified()
{
    return (PSS_BaseDocument::IsModified() || GetModel()->IsModified());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AllocatePropertiesManager(bool deleteFirst)
{
    if (deleteFirst && m_DynamicPropertiesManager)
        delete m_DynamicPropertiesManager;

    m_DynamicPropertiesManager = new ZBDynamicPropertiesManager;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::DeleteContents()
{
    static BOOL documentAlreadyOpened = FALSE;

    // initialize a new model if the document isn't closing
    if (!m_IsDocumentClosing && !documentAlreadyOpened)
    {
        m_EmptyModel.Initialize();
        GetModel()->Initialize();

        documentAlreadyOpened = TRUE;
    }

    PSS_BaseDocument::DeleteContents();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::DoFileSave()
{
    // unlock the file to avoid to show the save as dialog box
    SetFileReadOnly(m_strPathName, FALSE);

    const BOOL result = CDocument::DoFileSave();

    // lock the file again on the save end
    SetFileReadOnly(m_strPathName, TRUE);

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::SetFileReadOnly(const char* pPathName, BOOL value)
{
    if (!pPathName)
        return FALSE;

    std::unique_ptr<PSS_File> pFile(new PSS_File(pPathName));

    if (pFile.get() && pFile->Exist())
    {
        pFile->SetReadOnly(value);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(loadArchive);
        result = true;
    }
    CATCH (CArchiveException, e)
    {
        result = false;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // if everything is ok, set the path name
    if (result)
        SetPathName(fileName, FALSE);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::SaveToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument  = this;
    saveArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(saveArchive);
        result = true;
    }
    CATCH (CArchiveException, e)
    {
        result = false;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();

    // after a save, clear the modified flag
    SetModifiedFlag(FALSE);

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::Serialize(CArchive& ar)
{
    // serialize stamp and base information
    PSS_BaseDocument::Serialize(ar);

    m_PageUnits.Serialize(ar);

    // serialize the canvas model
    m_EmptyModel.Serialize(ar);

    // only if the object is serialized from and to a document
    if (!ar.m_pDocument)
        return;

    PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (ar.IsStoring())
    {
        // store the file GUID
        ar << m_GUID;

        // store the adequate user def GUID
        ar << m_UserDefGUID;

        // store the system user def GUID 
        ar << m_SystemDefGUID;

        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 24)
            ar << m_PrestationsDefGUID;

        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 26)
            ar << m_RulesDefGUID;

        ar << m_pModel;
        ar << m_pUnitManager;

        // serialize workflow data member
        ar << WORD(m_UseWorkflow);

        // serialize the workflow definition
        ar << m_pWorkflowDefinition;

        // serialize the flag for browsing in the same window
        ar << WORD(m_BrowseInSameWindow);

        // cost simulation flag
        ar << WORD(m_IntegrateCostSimulation);

        // consistency flag
        ar << WORD(m_CheckConsistency);

        ar << m_HourPerDay;
        ar << m_DayPerWeek;
        ar << m_DayPerMonth;
        ar << m_DayPerYear;
        ar << m_CurrencySymbol;
        ar << WORD(m_ShowPageBorder);

        PSS_ProcessGraphModelView* pView = GetFirstModelView();

        if (pView)
        {
            PSS_DocumentPageSetup* m_pPageSetup = pView->GetPrinterPageSize();

            ar << m_pPageSetup->GetPaperSize();
            ar << m_pPageSetup->GetStandardSize();
            ar << m_pPageSetup->GetOrientation();
        }
        else
        {
            // should not happen, but create a default page if no view available
            ar << g_DefaultPaperSize;
            ar << g_DefaultStandardSize;
            ar << g_DefaultOrientation;
        }

        // serialize the dynamic properties manager
        ar << m_DynamicPropertiesManager;

        // call the post write method
        GetModel()->PostWrite(ar);
    }
    else
    {
        if (GetDocumentStamp().GetInternalVersion() >= 19)
        {
            ar >> m_GUID;
            ar >> m_UserDefGUID;
            ar >> m_SystemDefGUID;

            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 24)
                ar >> m_PrestationsDefGUID;

            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 26)
                ar >> m_RulesDefGUID;
        }

        PSS_ProcessGraphModelMdl* pModel = NULL;
        ar >> pModel;
        ar >> m_pUnitManager;

        WORD wValue;
        ar >> wValue;
        m_UseWorkflow = wValue;

        // deserialize the workflow definition
        ar >> (CObject*&)m_pWorkflowDefinition;

        // deserialize the flag for browsing in the same window
        ar >> wValue;
        m_BrowseInSameWindow = wValue;

        // cost simulation flag
        ar >> wValue;
        m_IntegrateCostSimulation = wValue;

        // consistency flag
        ar >> wValue;
        m_CheckConsistency = wValue;

        ar >> m_HourPerDay;
        ar >> m_DayPerWeek;
        ar >> m_DayPerMonth;
        ar >> m_DayPerYear;
        ar >> m_CurrencySymbol;

        // show page border flag
        ar >> wValue;
        m_ShowPageBorder = wValue;

        // printer page attributes
        ar >> m_PaperSize;
        ar >> m_StandardSize;
        ar >> m_Orientation;

        // serialize the dynamic properties manager
        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 21)
            ar >> (CObject*&)m_DynamicPropertiesManager;

        // replace the existing model by the one read above
        SetNewModel(pModel);

        // initialize the unit manager is there is one defined
        if (m_pUnitManager)
        {
            PSS_ProcessModelDocTmpl* pDocTemplate = dynamic_cast<PSS_ProcessModelDocTmpl*>(GetDocTemplate());

            if (pDocTemplate)
            {
                m_pUnitManager->Initialize(pDocTemplate);
                m_pUnitManager->LoadAllUnits();
            }
        }

        // call the post read method
        GetModel()->PostRead(ar);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelDoc::AssertValid() const
    {
        PSS_BaseDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelDoc::Dump(CDumpContext& dc) const
    {
        PSS_BaseDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::OnPostOpenDocument()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    ASSERT(pModel);

    // call the PostOpenDocument method
    pModel->OnPostOpenDocument(GetDocumentStamp().GetInternalVersion());

    // check if the right GUID was found for the SystemDef, the UserDef, the PrestationsDef and the RulesDef
    ZBUserGroupEntity* pUserGroup = GetMainUserGroup();

    if (!pUserGroup)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_USERGROUP);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);

            // main user group is not valid
            pModel->SetMainUserGroupValid(false);
        }
    }
    else
    if (!m_UserDefGUID.IsEmpty() && m_UserDefGUID != pUserGroup->GetGUID())
    {
        // if the current user def GUID is not empty and is different, show an error message
        // and set the flag to avoid updates on userdef's linked items
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_USERGROUP_DIFFMODEL);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        // main user group is not valid
        pModel->SetMainUserGroupValid(false);
    }
    else
        // main user group is valid
        pModel->SetMainUserGroupValid();

    PSS_LogicalSystemEntity* pSystem = GetMainLogicalSystem();

    // no system, error
    if (!pSystem)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_SYSTEMDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);

            // main logical system is not valid
            pModel->SetMainLogicalSystemValid(false);
        }
    }
    else
    if (!m_SystemDefGUID.IsEmpty() && m_SystemDefGUID != pSystem->GetGUID())
    {
        // if the current system def GUID is not empty and is different, show an error message
        // and set the flag to avoid updates on system's linked items
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_SYSTEMDEFXML_DIFFMODEL);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        // main logical system is not valid
        pModel->SetMainLogicalSystemValid(false);
    }
    else
        // main logical system is valid
        pModel->SetMainLogicalSystemValid();

    PSS_LogicalPrestationsEntity* pPrestations = GetMainLogicalPrestations();

    // no prestations, error
    if (!pPrestations)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_PRESTATIONSDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);

            // main logical prestations is not valid
            pModel->SetMainLogicalPrestationsValid(false);
        }
    }
    else
    if (!m_PrestationsDefGUID.IsEmpty() && m_PrestationsDefGUID != pPrestations->GetGUID())
    {
        // if the current prestations def GUID is not empty and is different, show an error message
        // and set the flag to avoid updates on prestations's linked items
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_PRESTATIONSDEFXML_DIFFMODEL);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        // main logical prestations is not valid
        pModel->SetMainLogicalPrestationsValid(false);
    }
    else
        // main logical prestations is valid
        pModel->SetMainLogicalPrestationsValid();

    PSS_LogicalRulesEntity* pRules = GetMainLogicalRules();

    // no rules, error
    if (!pRules)
    {
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_MISSING_RULESDEF);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);

            // main logical Rules is not valid
            pModel->SetMainLogicalRulesValid(false);
        }
    }
    else
    if (!m_RulesDefGUID.IsEmpty() && m_RulesDefGUID != pRules->GetGUID())
    {
        // if the current rules def GUID is not empty and is different, show an error message
        // and set the flag to avoid updates on rules linked items
        if (m_pOutputLog)
        {
            CString message;
            message.LoadString(IDS_ERR_RULESDEFXML_DIFFMODEL);
            PSS_GenericSymbolErrorLine error(message);
            m_pOutputLog->AddLine(error);
        }

        // main logical rules is not valid
        pModel->SetMainLogicalRulesValid(false);
    }
    else
        // main logical rules is valid
        pModel->SetMainLogicalRulesValid();

    // message to notify end of fileopen
    if (m_pOutputLog)
    {
        CString message;
        message.Format(IDS_MSG_OPENMODEL_END, pModel->GetModelName(), GetPathName());
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::OnNewDocument()
{
    m_IsDocumentClosing = FALSE;

    if (!PSS_BaseDocument::OnNewDocument())
        return FALSE;

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return FALSE;

    // set model name for new document
    pModel->SetModelName(GetTitle());

    CWnd* pMainWnd = AfxGetMainWnd();
    ASSERT(pMainWnd);

    if (!IsUnit() && HasUnit())
    {
        // build the message
        PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_OpenDocument, this);
        pMainWnd->SendMessageToDescendants(UM_INITIALIZEDOCUMENTMODEL, 0, LPARAM(&docMsg));

        // build the message even if the unit manager is NULL
        ZBUnitObserverMsg unitMsg(ZBUnitObserverMsg::OpenUnit, m_pUnitManager);
        pMainWnd->SendMessageToDescendants(UM_INITIALIZEUNITMODEL, 0, LPARAM(&unitMsg));
    }

    // build the message even if the unit manager is NULL
    PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_OpenDocument, this);
    pMainWnd->SendMessage(UM_DOCUMENTLOADED, 0, LPARAM(&docMsg));

    // assign the current system def, user def, prestations def and rules def
    AssignCurrentSystemDefGUID();
    AssignCurrentUserDefGUID();
    AssignCurrentPrestationsDefGUID();
    AssignCurrentRulesDefGUID();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::OnOpenDocument(LPCTSTR pPathName)
{
    if (!pPathName)
        return FALSE;

    m_IsDocumentClosing = FALSE;

    // open file message
    if (m_pOutputLog)
    {
        CString message;
        message.Format(IDS_MSG_OPENMODEL_START, pPathName);
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    if (!PSS_BaseDocument::OnOpenDocument(pPathName))
        return FALSE;

    CWnd* pMainWnd = AfxGetMainWnd();
    ASSERT(pMainWnd);

    if (!IsUnit() && HasUnit())
    {
        // build the message
        PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_OpenDocument, this);
        pMainWnd->SendMessageToDescendants(UM_INITIALIZEDOCUMENTMODEL, 0, LPARAM(&docMsg));

        // build the message even if the unit manager is NULL
        ZBUnitObserverMsg unitMsg(ZBUnitObserverMsg::OpenUnit, m_pUnitManager);
        pMainWnd->SendMessageToDescendants(UM_INITIALIZEUNITMODEL, 0, LPARAM(&unitMsg));
    }

    // build the message even if the unit manager is NULL
    PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_OpenDocument, this);
    pMainWnd->SendMessage(UM_DOCUMENTLOADED, 0, LPARAM(&docMsg));

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::OnSaveDocument(const char* pPathName)
{
    if (!pPathName)
        return FALSE;

    if (!std::strlen(pPathName))
        return DoSave(NULL);

    // check if the user selection is valid
    if (m_IsReadOnly && GetPathName() == pPathName)
    {
        // the user tried to erase a file opened in read-only mode
        PSS_MsgBox mBox;

        mBox.Show(IDS_FILE_READONLY_DONOTSAVE, MB_OK);
        return FALSE;
    }
    else
    if (m_IsReadOnly && GetPathName() != pPathName)
        // the user cannot modify the opened file, but tries to save it under a new name. He can obtain
        // the modification rights for his new file in this case
        SetReadOnly(FALSE);
    else
    if (!m_IsReadOnly && GetPathName() != pPathName)
        // the user has the rights to modify the file, but is trying to save it under a new name. In this case,
        // the previous file should be unlocked, and the new should be locked instead. Be careful, as the
        // GetPathName() function content wasn't updated, it still contains the old file path
        SetFileReadOnly(GetPathName(), FALSE);

    // if template check the model
    if (DocumentIsTemplate())
    {}

    // build the new title, if FALSE do not add to MRU
    SetPathName(pPathName, FALSE);

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    // update the model information
    if (pModel)
        pModel->SetModelName(GetTitle());

    PSS_MainForm* pMainForm = PSS_Application::Instance()->GetMainForm();
    ASSERT(pMainForm);
    pMainForm->UpdateLastLoadedFile(pPathName);

    // Message to notify the start of filesave
    if (m_pOutputLog)
    {
        CString message;
        message.Format(IDS_MSG_SAVEMODEL_END, pModel ? pModel->GetModelName() : "<#Error>", GetPathName());
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    // check if a GUID was defined for the system def, the user def, the prestations def and the rules def
    if (m_UserDefGUID.IsEmpty())
        AssignCurrentUserDefGUID();

    if (m_SystemDefGUID.IsEmpty())
        AssignCurrentSystemDefGUID();

    if (m_PrestationsDefGUID.IsEmpty())
        AssignCurrentPrestationsDefGUID();

    if (m_RulesDefGUID.IsEmpty())
        AssignCurrentRulesDefGUID();

    // unlock the file to allow the save
    SetFileReadOnly(pPathName, FALSE);

    // save the document
    const BOOL result = PSS_BaseDocument::OnSaveDocument(pPathName);

    // lock the file again once the save is completed
    SetFileReadOnly(pPathName, TRUE);

    CWnd* pMainWnd = AfxGetMainWnd();
    ASSERT(pMainWnd);

    // build the message
    PSS_DocObserverMsg docMsg;
    pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));

    // message to notify the file save end
    if (m_pOutputLog)
    {
        CString message;
        message.Format(IDS_MSG_SAVEMODEL_END, pModel->GetModelName(), GetPathName());
        PSS_GenericSymbolErrorLine error(message);
        m_pOutputLog->AddLine(error);
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::OnCloseDocument()
{
    m_IsDocumentClosing = TRUE;

    CWnd* pMainWnd = AfxGetMainWnd();
    ASSERT(pMainWnd);

    pMainWnd->SendMessageToDescendants(UM_CLOSEDOCUMENTMODELTREE);
    pMainWnd->SendMessageToDescendants(UM_CLOSEUNITMODELTREE);

    // when an user locked a model, its file is locked on the disk, but the m_IsReadOnly wrongly
    // remains on FALSE. The user is the only one which can unlock the file if he closes it
    if (!IsReadOnly())
        SetFileReadOnly(GetPathName(), FALSE);

    PSS_BaseDocument::OnCloseDocument();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ProcessGraphModelView* pView = GetFirstModelView();

    // forward the message to the controller
    if (pView)
    {
        PSS_ProcessGraphModelController* pModelCtrl = pView->GetModelController();

        if (pModelCtrl)
            pModelCtrl->OnUpdate(pSubject, pMsg);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::CreateUnitManager()
{
    m_pUnitManager = new ZBUnitManager;

    if (!m_pUnitManager)
        return false;

    PSS_ProcessModelDocTmpl* pDocTemplate = dynamic_cast<PSS_ProcessModelDocTmpl*>(GetDocTemplate());

    if (pDocTemplate)
        m_pUnitManager->Initialize(pDocTemplate);

    return true;
}
//---------------------------------------------------------------------------
