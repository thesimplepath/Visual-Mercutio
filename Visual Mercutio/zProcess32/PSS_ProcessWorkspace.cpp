/****************************************************************************
 * ==> PSS_ProcessWorkspace ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the process workspace                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessWorkspace.h"

// processsoft
#include "zBaseLib\PSS_WorkspaceObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UnitObserverMsg.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zModel\PSS_LogicalSystemObserverMsg.h"

// resources
#include "Resources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

// uncomment the line below if you don't want to see the webview tab
//#define SHOW_WEBVIEW

// uncomment the line below if you don't want to see the Scriptor tab
//#define SHOW_SCRIPTOR

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define IDC_WORKSPACEVIEW     110
#define IDC_MODELVIEW         111
#define IDC_FORMVIEW          112
#define IDC_FILEVIEW          113
#define IDC_USERVIEW          114
#define IDC_WEBVIEW           115
#define IDC_LOGICALSYSTEMVIEW 116
#define IDC_PRESTATIONSVIEW   117
#define IDC_RULESVIEW         118
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ProcessWorkspace, SECControlBar)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(PSS_ProcessWorkspace)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_CONTEXTMENU()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_MODELVIEW, OnListGetDispInfoModelView)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_FORMVIEW, OnListGetDispInfoFormView)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_FILEVIEW, OnListGetDispInfoFileView)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_USERVIEW, OnListGetDispInfoUserView)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_WEBVIEW, OnListGetDispInfoWebView)
    ON_MESSAGE(UM_INITIALIZEDOCUMENTMODEL, OnInitializeModelDocument)
    ON_MESSAGE(UM_DOCUMENTMODELHASCHANGED, OnModelDocumentHasChanged)
    ON_MESSAGE(UM_INITIALIZEUNITMODEL, OnInitializeModelUnit)
    ON_MESSAGE(UM_UNITMODELHASCHANGED, OnModelUnitHasChanged)
    ON_MESSAGE(UM_ADDDOCUMENTMODEL, OnAddModelDocument)
    ON_MESSAGE(UM_REMOVEDOCUMENTMODEL, OnRemoveModelDocument)
    ON_MESSAGE(UM_ADDUNITMODEL, OnAddModelUnit)
    ON_MESSAGE(UM_REMOVEUNITMODEL, OnRemoveModelUnit)
    ON_MESSAGE(UM_ELEMENTADDEDDOCUMENTMODEL, OnAddModelDocumentSymbol)
    ON_MESSAGE(UM_ELEMENTREMOVEDDOCUMENTMODEL, OnRemoveModelDocumentSymbol)
    ON_MESSAGE(UM_ELEMENTMODIFIEDDOCUMENTMODEL, OnModifyModelDocumentSymbol)
    ON_MESSAGE(UM_ELEMENTADDEDUNITMODEL, OnAddModelUnitSymbol)
    ON_MESSAGE(UM_ELEMENTREMOVEDUNITMODEL, OnRemoveModelUnitSymbol)
    ON_MESSAGE(UM_ELEMENTMODIFIEDUNITMODEL, OnModifyModelUnitSymbol)
    ON_MESSAGE(UM_CLOSEDOCUMENTMODELTREE, OnCloseDocumentModelTree)
    ON_MESSAGE(UM_CLOSEUNITMODELTREE, OnCloseUnitModelTree)
    ON_MESSAGE(UM_DOCUMENTHASBEENSELECTED, OnDocumentHasBeenSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessWorkspace
//---------------------------------------------------------------------------
PSS_ProcessWorkspace::PSS_ProcessWorkspace() :
    SECControlBar(),
    PSS_Subject(),
    PSS_Observer(),
    m_pActiveDocument(NULL)
{}
//---------------------------------------------------------------------------
PSS_ProcessWorkspace::~PSS_ProcessWorkspace()
{}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::Initialize()
{
    // set the first active view
    m_WndTab.ActivateTab(g_ModelDocumentTabIndex);
    m_WndTab.ScrollToTab(g_ModelDocumentTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::Release()
{
    m_LogicalSystemView.Release();
    m_PrestationsView.Release();
    m_RulesView.Release();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::InitializeModelDocumentTree(PSS_ModelSet* pModelSet)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->Initialize("Document", pModelSet, IDB_IL_BP_SYMBOLS);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelDocument(PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelDocumentSet(PSS_ModelSet* pModelSet)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelDocument(PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelDocumentSet(PSS_ModelSet* pModelSet)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ModifyModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->ModifySymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::EmptyModelDocumentTree()
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->Empty();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RefreshModelDocumentTree()
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::InitializeModelUnitTree(PSS_ModelSet* pModelSet)
{
    AddModelUnitSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::EmptyModelUnitTree()
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->Empty();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RefreshModelUnitTree()
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelUnit(PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelUnitSet(PSS_ModelSet* pModelSet)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelUnit(PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveModel(pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelUnitSet(PSS_ModelSet* pModelSet)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveModelSet(pModelSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::AddModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->AddSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::RemoveModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    PSS_ProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
        pTree->RemoveSymbol(pSymbol, pModel);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnExpandBranch()
{
    CWnd* pWnd;
    m_WndTab.GetActiveTab(pWnd);

    if (pWnd == GetUserView())
        GetUserView()->OnExpandBranch();
    else
    if (pWnd == GetLogicalSystemView())
        GetLogicalSystemView()->OnExpandBranch();
    else
    if (pWnd == GetPrestationsView())
        GetPrestationsView()->OnExpandBranch();
    else
    if (pWnd == GetRulesView())
        GetRulesView()->OnExpandBranch();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnCollapseBranch()
{
    CWnd* pWnd;
    m_WndTab.GetActiveTab(pWnd);

    if (pWnd == GetUserView())
        GetUserView()->OnCollapseBranch();
    else
    if (pWnd == GetLogicalSystemView())
        GetLogicalSystemView()->OnCollapseBranch();
    else
    if (pWnd == GetPrestationsView())
        GetPrestationsView()->OnCollapseBranch();
    else
    if (pWnd == GetRulesView())
        GetRulesView()->OnCollapseBranch();
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_WorkspaceObserverMsg* pWorkspaceMsg = dynamic_cast<PSS_WorkspaceObserverMsg*>(pMsg);

    if (pWorkspaceMsg)
        switch (pWorkspaceMsg->GetMessageID())
        {
            case UM_INITWORKSPACE:  ActivateWorkspaceTab(); break;
            case UM_CLOSEWORKSPACE:                         break;
        }

    // forward message
    m_WorkspaceView.OnUpdate(pSubject, pMsg);
    m_UserView.OnUpdate(pSubject, pMsg);
    m_LogicalSystemView.OnUpdate(pSubject, pMsg);
    m_PrestationsView.OnUpdate(pSubject, pMsg);
    m_RulesView.OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnExtendContextMenu(CMenu* pMenu)
{}
//---------------------------------------------------------------------------
int PSS_ProcessWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    const BOOL result = m_WndTab.Create(this);

    // NOTE OT 5.0 and earlier would stretch a 32x32 icon resource down to
    // 16x16. 5.1 and above defaults to native 16x16 sized icons, when available
    // (avoids ugly stretching). Since no 16x16 icons are available, 32x32 resources
    // may be specified in the AddTab calls below (will still stretch down,
    // but at least the images of interest will be loaded)
    m_WorkspaceView.Create(WS_CHILD | WS_VISIBLE,
                           CRect(0, 0, 0, 0),
                           &m_WndTab,
                           IDC_WORKSPACEVIEW);

    CString str;
    str.LoadString(IDS_APPWKS_PROJECT);
    m_WndTab.AddTab(&m_WorkspaceView, str);
    m_WndTab.SetTabIcon(g_WorkspaceTabIndex, IDI_IL_WORKSPACEVIEW);

    m_ProcessModelView.Create(WS_CHILD | WS_VISIBLE,
                              CRect(0, 0, 0, 0),
                              &m_WndTab,
                              IDC_MODELVIEW);

    str.LoadString(IDS_APPWKS_MODELNAV);
    m_WndTab.AddTab(&m_ProcessModelView, str);
    m_WndTab.SetTabIcon(g_ModelDocumentTabIndex, IDI_IL_MODELVIEW);

    m_UserView.Create(NULL,
                      NULL,
                      WS_CHILD | WS_VISIBLE,
                      CRect(0, 0, 0, 0),
                      &m_WndTab,
                      IDC_USERVIEW);

    str.LoadString(IDS_APPWKS_UNITS);
    m_WndTab.AddTab(&m_UserView, str);
    m_WndTab.SetTabIcon(g_UserTabIndex, IDI_IL_USERVIEW);

    m_LogicalSystemView.Create(NULL,
                               NULL,
                               WS_CHILD | WS_VISIBLE,
                               CRect(0, 0, 0, 0),
                               &m_WndTab,
                               IDC_LOGICALSYSTEMVIEW);

    str.LoadString(IDS_APPWKS_LOGICALSYSTEMS);
    m_WndTab.AddTab(&m_LogicalSystemView, str);
    m_WndTab.SetTabIcon(g_LogicalSystemTabIndex, IDI_IL_LOGICALSYSTEMVIEW);

    m_PrestationsView.Create(NULL,
                             NULL,
                             WS_CHILD | WS_VISIBLE,
                             CRect(0, 0, 0, 0),
                             &m_WndTab,
                             IDC_PRESTATIONSVIEW);

    str.LoadString(IDS_APPWKS_PRESTATIONS);
    m_WndTab.AddTab(&m_PrestationsView, str);
    m_WndTab.SetTabIcon(g_PrestationsTabIndex, IDI_IL_PRESTATIONSVIEW);

    m_RulesView.Create(NULL,
                       NULL,
                       WS_CHILD | WS_VISIBLE,
                       CRect(0, 0, 0, 0),
                       &m_WndTab,
                       IDC_RULESVIEW);

    str.LoadString(IDS_APPWKS_RULES);
    m_WndTab.AddTab(&m_RulesView, str);
    m_WndTab.SetTabIcon(g_RulesTabIndex, IDI_IL_RULESVIEW);

    m_FileView.Create(NULL,
                      NULL,
                      WS_CHILD | WS_VISIBLE,
                      CRect(0, 0, 0, 0),
                      &m_WndTab,
                      IDC_FILEVIEW);

    str.LoadString(IDS_APPWKS_FILEBROWSER);
    m_WndTab.AddTab(&m_FileView, str);
    m_WndTab.SetTabIcon(g_FileTabIndex, IDI_IL_FILEVIEW);

    #ifdef SHOW_SCRIPTOR
        m_FormTemplateView.Create(WS_CHILD | WS_VISIBLE,
                                  CRect(0, 0, 0, 0),
                                  &m_WndTab,
                                  IDC_FORMVIEW);

        str.LoadString(IDS_APPWKS_FORMS);
        m_WndTab.AddTab(&m_FormTemplateView, str);
        m_WndTab.SetTabIcon(g_FormTemplateTabIndex, IDI_IL_FORMVIEW);
    #endif

    #ifdef SHOW_WEBVIEW
        m_URLView.Create(NULL,
                         NULL,
                         WS_CHILD | WS_VISIBLE,
                         CRect(0, 0, 0, 0),
                         &m_WndTab,
                         IDC_WEBVIEW);

        str.LoadString(IDS_APPWKS_WEBBROWSER);
        m_WndTab.AddTab(&m_URLView, str);
        m_WndTab.SetTabIcon(g_WebTabIndex, IDI_IL_WEBVIEW);
    #endif

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnSize(UINT nType, int cx, int cy)
{
    CRect rectInside;
    GetInsideRect(rectInside);

    ::SetWindowPos(m_WndTab.m_hWnd,
                   NULL,
                   rectInside.left,
                   rectInside.top,
                   rectInside.Width(),
                   rectInside.Height(),
                   SWP_NOZORDER | SWP_NOACTIVATE);

    SECControlBar::OnSize(nType, cx, cy);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnContextMenu(CWnd* pWnd, CPoint point)
{
    // get the active tab window
    CWnd* pActiveWnd;
    m_WndTab.GetActiveTab(pActiveWnd);

    if (!pActiveWnd)
        return;

    PSS_WorkspaceTreeCtrl* pWorkspaceView = GetWorkspaceView();

    if (pActiveWnd == pWorkspaceView)
        if (pWorkspaceView->HasContextMenu(pWnd, point) != -1)
        {
            pWorkspaceView->ShowContextMenu(pWnd, point);
            return;
        }

    PSS_UserGroupView* pUserView = GetUserView();

    if (pActiveWnd == pUserView)
        if (pUserView->HasContextMenu(pWnd, point) != -1)
        {
            pUserView->ShowContextMenu(pWnd, point);
            return;
        }

    PSS_LogicalSystemView* pLogicalSystemView = GetLogicalSystemView();

    if (pActiveWnd == pLogicalSystemView)
        if (pLogicalSystemView->HasContextMenu(pWnd, point) != -1)
        {
            pLogicalSystemView->ShowContextMenu(pWnd, point);
            return;
        }

    PSS_ProcessModelDocument* pProcessModelDocument = GetModelDocumentTree();

    if (pActiveWnd == pProcessModelDocument)
        if (pProcessModelDocument->HasContextMenu(pWnd, point) != -1)
        {
            pProcessModelDocument->ShowContextMenu(pWnd, point);
            return;
        }

    PSS_PrestationsView* pPrestationsView = GetPrestationsView();

    if (pActiveWnd == pPrestationsView)
        if (pPrestationsView->HasContextMenu(pWnd, point) != -1)
        {
            pPrestationsView->ShowContextMenu(pWnd, point);
            return;
        }

    PSS_RulesView* pRulesView = GetRulesView();

    if (pActiveWnd == pRulesView)
        if (pRulesView->HasContextMenu(pWnd, point) != -1)
        {
            pRulesView->ShowContextMenu(pWnd, point);
            return;
        }

    // if not found, call the base function
    SECControlBar::OnContextMenu(pWnd, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnListGetDispInfoModelView(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnListGetDispInfoFormView(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnListGetDispInfoFileView(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnListGetDispInfoUserView(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::OnListGetDispInfoWebView(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnInitializeModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelDoc* pDoc = pDocMsg->GetDoc();

        if (pDoc)
        {
            PSS_ModelSet documentModelSet;
            documentModelSet.AddModel(pDoc->GetModel());
            InitializeModelDocumentTree(&documentModelSet);
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnModelDocumentHasChanged(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    RefreshModelDocumentTree();
    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnInitializeModelUnit(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*     pMsg     = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_UnitObserverMsg* pUnitMsg = dynamic_cast<PSS_UnitObserverMsg*>(pMsg);

    if (pUnitMsg)
    {
        PSS_UnitManager* pUnitManager = pUnitMsg->GetUnitManager();

        if (pUnitManager)
        {
            PSS_ModelSet unitModelSet;
            pUnitManager->FillModelSet(unitModelSet);
            InitializeModelUnitTree(&unitModelSet);
        }
        else
            InitializeModelUnitTree(NULL);
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnModelUnitHasChanged(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    RefreshModelUnitTree();
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnAddModelDocument(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnRemoveModelDocument(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnAddModelUnit(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*     pMsg     = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_UnitObserverMsg* pUnitMsg = dynamic_cast<PSS_UnitObserverMsg*>(pMsg);

    if (pUnitMsg)
    {
        PSS_Unit* pUnit = pUnitMsg->GetUnit();

        if (pUnit)
        {
            PSS_ProcessGraphModelDoc* pGraphModelDoc = pUnit->GetUnitDocument();
            AddModelUnit(pGraphModelDoc->GetModel());
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnRemoveModelUnit(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnAddModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelMdl* pModel  = pDocMsg->GetModel();
        CODSymbolComponent*       pSymbol = pDocMsg->GetElement();

        if (pModel && pSymbol)
            AddModelDocumentSymbol(pSymbol, pModel);
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnRemoveModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelMdl* pModel  = pDocMsg->GetModel();
        CODSymbolComponent*       pSymbol = pDocMsg->GetElement();

        if (pModel && pSymbol)
            RemoveModelDocumentSymbol(pSymbol, pModel);
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnModifyModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelMdl* pModel  = pDocMsg->GetModel();
        CODSymbolComponent*       pSymbol = pDocMsg->GetElement();

        if (pModel && pSymbol)
            ModifyModelDocumentSymbol(pSymbol, pModel);
    }

    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnAddModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnRemoveModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnModifyModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnCloseDocumentModelTree(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    EmptyModelDocumentTree();
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnCloseUnitModelTree(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    EmptyModelUnitTree();
    return 1;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessWorkspace::OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_BaseDocument*         pDoc      = reinterpret_cast<PSS_BaseDocument*>(lParam);
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc);

    if (pModelDoc)
    {
        PSS_ModelSet documentModelSet;
        documentModelSet.AddModel(pModelDoc->GetModel());
        InitializeModelDocumentTree(&documentModelSet);
    }

    return 1;
}
//---------------------------------------------------------------------------
