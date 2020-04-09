// ZVProcessWorkspace.cpp: implementation of the ZVProcessWorkspace class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVProcessWorkspace.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UnitObserverMsg.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zBaseLib\PSS_WorkspaceObserverMsg.h"
#include "zModel\PSS_LogicalSystemObserverMsg.h"
#include "Resources.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - LE 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

// Comment the line below if you don't want to see the webview tab
//#define _DISPLAY_WEBVIEW            1

// JMR-MODIF - Le 13 novembre 2006 - Espace de travail Scriptor obsolète. Nouveau code rends l'affichage optionnel.
//#define _DISPLAY_SCRIPTOR            2

#define IDC_WORKSPACEVIEW            110
#define IDC_MODELVIEW                111
#define IDC_FORMVIEW                112
#define IDC_FILEVIEW                113
#define IDC_USERVIEW                114
#define IDC_WEBVIEW                    115
#define IDC_LOGICALSYSTEMVIEW        116
#define IDC_PRESTATIONSVIEW            117        // JMR-MODIF - Le 12 octobre 2005 - Ajout de la ressource IDC_PRESTATIONSVIEW.
#define IDC_RULESVIEW                118        // JMR-MODIF - Le 13 novembre 2006 - Ajout de la ressource IDC_RULESVIEW.

IMPLEMENT_DYNAMIC(ZVProcessWorkspace, SECControlBar)

BEGIN_MESSAGE_MAP(ZVProcessWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(ZVProcessWorkspace)
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVProcessWorkspace::ZVProcessWorkspace()
    : SECControlBar(),
    m_pActiveDocument(NULL)
{}

ZVProcessWorkspace::~ZVProcessWorkspace()
{}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVProcessWorkspace::Release()
{
    m_LogicalSystemView.Release();
    m_PrestationsView.Release();
    m_RulesView.Release();
}

int ZVProcessWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    BOOL rtn_val;
    rtn_val = m_wndTab.Create(this);

    // Note: OT 5.0 and earlier would stretch a 32x32 icon resource down to
    // 16x16. 5.1 and above defaults to native 16x16 sized icons, when available
    // (avoids ugly stretching). Since we don't have 16x16 icons available, we
    // can specify the 32x32 resources in the AddTab calls below (will still
    // stretch down, but at least we are loading the images of interest)

    m_WorkspaceView.Create(WS_CHILD | WS_VISIBLE,
                           CRect(0, 0, 0, 0),
                           &m_wndTab,
                           IDC_WORKSPACEVIEW);

    CString s;
    s.LoadString(IDS_APPWKS_PROJECT);
    m_wndTab.AddTab(&m_WorkspaceView, s);
    m_wndTab.SetTabIcon(def_WorkspaceTabIndex, IDI_IL_WORKSPACEVIEW);

    m_ProcessModelView.Create(WS_CHILD | WS_VISIBLE,
                              CRect(0, 0, 0, 0),
                              &m_wndTab,
                              IDC_MODELVIEW);

    s.LoadString(IDS_APPWKS_MODELNAV);
    m_wndTab.AddTab(&m_ProcessModelView, s);
    m_wndTab.SetTabIcon(def_ModelDocumentTabIndex, IDI_IL_MODELVIEW);

    m_UserView.Create(NULL,
                      NULL,
                      WS_CHILD | WS_VISIBLE,
                      CRect(0, 0, 0, 0),
                      &m_wndTab,
                      IDC_USERVIEW);

    s.LoadString(IDS_APPWKS_UNITS);
    m_wndTab.AddTab(&m_UserView, s);
    m_wndTab.SetTabIcon(def_UserTabIndex, IDI_IL_USERVIEW);

    m_LogicalSystemView.Create(NULL,
                               NULL,
                               WS_CHILD | WS_VISIBLE,
                               CRect(0, 0, 0, 0),
                               &m_wndTab,
                               IDC_LOGICALSYSTEMVIEW);

    s.LoadString(IDS_APPWKS_LOGICALSYSTEMS);
    m_wndTab.AddTab(&m_LogicalSystemView, s);
    m_wndTab.SetTabIcon(def_LogicalSystemTabIndex, IDI_IL_LOGICALSYSTEMVIEW);

    // *********************************************************************************************
    // JMR-MODIF - Le 11 octobre 2005 - Ajout du code de création de la nouvelle vue de prestations.
    m_PrestationsView.Create(NULL,
                             NULL,
                             WS_CHILD | WS_VISIBLE,
                             CRect(0, 0, 0, 0),
                             &m_wndTab,
                             IDC_PRESTATIONSVIEW);

    s.LoadString(IDS_APPWKS_PRESTATIONS);
    m_wndTab.AddTab(&m_PrestationsView, s);
    m_wndTab.SetTabIcon(def_PrestationsTabIndex, IDI_IL_PRESTATIONSVIEW);
    // *********************************************************************************************

    // ******************************************************************************************
    // JMR-MODIF - Le 13 novembre 2006 - Ajout du code de création de la nouvelle vue des règles.
    m_RulesView.Create(NULL,
                       NULL,
                       WS_CHILD | WS_VISIBLE,
                       CRect(0, 0, 0, 0),
                       &m_wndTab,
                       IDC_RULESVIEW);

    s.LoadString(IDS_APPWKS_RULES);
    m_wndTab.AddTab(&m_RulesView, s);
    m_wndTab.SetTabIcon(def_RulesTabIndex, IDI_IL_RULESVIEW);
    // ******************************************************************************************

    m_FileView.Create(NULL,
                      NULL,
                      WS_CHILD | WS_VISIBLE,
                      CRect(0, 0, 0, 0),
                      &m_wndTab,
                      IDC_FILEVIEW);

    s.LoadString(IDS_APPWKS_FILEBROWSER);
    m_wndTab.AddTab(&m_FileView, s);
    m_wndTab.SetTabIcon(def_FileTabIndex, IDI_IL_FILEVIEW);

    // JMR-MODIF - Le 13 novembre 2006 - Espace de travail Scriptor obsolète. Nouveau code rends l'affichage optionnel.
#ifdef _DISPLAY_SCRIPTOR
    m_FormTemplateView.Create(WS_CHILD | WS_VISIBLE,
                              CRect(0, 0, 0, 0),
                              &m_wndTab,
                              IDC_FORMVIEW);

    s.LoadString(IDS_APPWKS_FORMS);
    m_wndTab.AddTab(&m_FormTemplateView, s);
    m_wndTab.SetTabIcon(def_FormTemplateTabIndex, IDI_IL_FORMVIEW);
#endif // _DISPLAY_SCRIPTOR

#ifdef _DISPLAY_WEBVIEW
    m_URLView.Create(NULL,
                     NULL,
                     WS_CHILD | WS_VISIBLE,
                     CRect(0, 0, 0, 0),
                     &m_wndTab,
                     IDC_WEBVIEW);

    s.LoadString(IDS_APPWKS_WEBBROWSER);
    m_wndTab.AddTab(&m_URLView, s);
    m_wndTab.SetTabIcon(def_WebTabIndex, IDI_IL_WEBVIEW);
#endif // _DISPLAY_WEBVIEW

    return 0;
}

void ZVProcessWorkspace::Initialize()
{
    // Set the first active view
    m_wndTab.ActivateTab(def_ModelDocumentTabIndex);
    m_wndTab.ScrollToTab(def_ModelDocumentTabIndex);
}

void ZVProcessWorkspace::OnContextMenu(CWnd* pWnd, CPoint point)
{
    // Try to locate the active tab
    CWnd* pActiveWnd;
    m_wndTab.GetActiveTab(pActiveWnd);

    // Check which window
    if (pActiveWnd == GetWorkspaceView())
    {
        if (GetWorkspaceView()->HasContextMenu(pWnd, point) != -1)
        {
            GetWorkspaceView()->ShowContextMenu(pWnd, point);

            // Done
            return;
        }
    }
    else if (pActiveWnd == GetUserView())
    {
        if (GetUserView()->HasContextMenu(pWnd, point) != -1)
        {
            GetUserView()->DisplayContextMenu(pWnd, point);

            // Done
            return;
        }
    }
    else if (pActiveWnd == GetLogicalSystemView())
    {
        if (GetLogicalSystemView()->HasContextMenu(pWnd, point) != -1)
        {
            GetLogicalSystemView()->DisplayContextMenu(pWnd, point);

            // Done
            return;
        }
    }
    else if (pActiveWnd == GetModelDocumentTree())
    {
        if (GetModelDocumentTree()->HasContextMenu(pWnd, point) != -1)
        {
            GetModelDocumentTree()->ShowContextMenu(pWnd, point);

            // Done
            return;
        }
    }
    // JMR-MODIF - Le 13 octobre 2005 - Ajout de l'appel pour le menu contextuel des prestations.
    else if (pActiveWnd == GetPrestationsView())
    {
        if (GetPrestationsView()->HasContextMenu(pWnd, point) != -1)
        {
            GetPrestationsView()->DisplayContextMenu(pWnd, point);

            // Done
            return;
        }
    }
    // JMR-MODIF - Le 26 décembre 2006 - Ajout de l'appel pour le menu contextuel des règles.
    else if (pActiveWnd == GetRulesView())
    {
        if (GetRulesView()->HasContextMenu(pWnd, point) != -1)
        {
            GetRulesView()->DisplayContextMenu(pWnd, point);

            // Done
            return;
        }
    }

    // If not trapped, call the base function
    SECControlBar::OnContextMenu(pWnd, point);
}

void ZVProcessWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, PSS_WorkspaceObserverMsg))
    {
        switch (dynamic_cast<PSS_WorkspaceObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_INITWORKSPACE:
            {
                ActivateWorkspaceTab();
                break;
            }

            case UM_CLOSEWORKSPACE:
            {
                break;
            }
        }
    }

    // Forward message
    m_WorkspaceView.OnUpdate(pSubject, pMsg);
    m_UserView.OnUpdate(pSubject, pMsg);
    m_LogicalSystemView.OnUpdate(pSubject, pMsg);
    m_PrestationsView.OnUpdate(pSubject, pMsg);    // JMR-MODIF - Le 11 octobre 2005 - Maj pour les prestations.
    m_RulesView.OnUpdate(pSubject, pMsg);            // JMR-MODIF - Le 15 novembre 2005 - Maj pour les règles.
}

// Initialize functions
void ZVProcessWorkspace::InitializeModelDocumentTree(PSS_ModelSet* pModelSet)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->Initialize("Document", pModelSet, IDB_IL_BP_SYMBOLS);
    }
}

void ZVProcessWorkspace::InitializeModelUnitTree(PSS_ModelSet* pModelSet)
{
    AddModelUnitSet(pModelSet);
}

// Empty functions
void ZVProcessWorkspace::EmptyModelDocumentTree()
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->Empty();
    }
}

void ZVProcessWorkspace::EmptyModelUnitTree()
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->Empty();
    }
}

// Refresh functions
void ZVProcessWorkspace::RefreshModelDocumentTree()
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->Refresh();
    }
}

void ZVProcessWorkspace::RefreshModelUnitTree()
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->Refresh();
    }
}

void ZVProcessWorkspace::AddModelDocument(PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddModel(pModel);
    }
}

void ZVProcessWorkspace::RemoveModelDocument(PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveModel(pModel);
    }
}

void ZVProcessWorkspace::AddModelDocumentSet(PSS_ModelSet* pModelSet)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddModelSet(pModelSet);
    }
}

void ZVProcessWorkspace::RemoveModelDocumentSet(PSS_ModelSet* pModelSet)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveModelSet(pModelSet);
    }
}

void ZVProcessWorkspace::AddModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddSymbol(pSymbol, pModel);
    }
}

void ZVProcessWorkspace::RemoveModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveSymbol(pSymbol, pModel);
    }
}

void ZVProcessWorkspace::ModifyModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->ModifySymbol(pSymbol, pModel);
    }
}


void ZVProcessWorkspace::AddModelUnit(PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddModel(pModel);
    }
}

void ZVProcessWorkspace::RemoveModelUnit(PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveModel(pModel);
    }
}

void ZVProcessWorkspace::AddModelUnitSet(PSS_ModelSet* pModelSet)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddModelSet(pModelSet);
    }
}

void ZVProcessWorkspace::RemoveModelUnitSet(PSS_ModelSet* pModelSet)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveModelSet(pModelSet);
    }
}

void ZVProcessWorkspace::AddModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->AddSymbol(pSymbol, pModel);
    }
}

void ZVProcessWorkspace::RemoveModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    ZCProcessModelDocument* pTree = GetModelDocumentTree();

    if (pTree)
    {
        pTree->RemoveSymbol(pSymbol, pModel);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZVProcessWorkspace message handlers

void ZVProcessWorkspace::OnSize(UINT nType, int cx, int cy)
{
    CRect rectInside;
    GetInsideRect(rectInside);

    ::SetWindowPos(m_wndTab.m_hWnd,
                   NULL,
                   rectInside.left,
                   rectInside.top,
                   rectInside.Width(),
                   rectInside.Height(),
                   SWP_NOZORDER | SWP_NOACTIVATE);

    SECControlBar::OnSize(nType, cx, cy);
}

void ZVProcessWorkspace::OnExtendContextMenu(CMenu* pMenu)
{}

void ZVProcessWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
    pTarget;            // UNUSED
    bDisableIfNoHndler;    // UNUSED
}

// List control is querying for subitem text...
void ZVProcessWorkspace::OnListGetDispInfoModelView(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

void ZVProcessWorkspace::OnListGetDispInfoFormView(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

void ZVProcessWorkspace::OnListGetDispInfoFileView(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

void ZVProcessWorkspace::OnListGetDispInfoUserView(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

void ZVProcessWorkspace::OnListGetDispInfoWebView(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

afx_msg LRESULT ZVProcessWorkspace::OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_BaseDocument* pDoc = (PSS_BaseDocument*)lParam;

    if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
    {
        PSS_ModelSet DocumentModelSet;

        DocumentModelSet.AddModel(((PSS_ProcessGraphModelDoc*)pDoc)->GetModel());
        InitializeModelDocumentTree(&DocumentModelSet);
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnInitializeModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_DocObserverMsg))
    {
        PSS_DocObserverMsg* pDocMsg = (PSS_DocObserverMsg*)pMsg;

        if (pDocMsg->GetDoc())
        {
            PSS_ModelSet DocumentModelSet;

            DocumentModelSet.AddModel(pDocMsg->GetDoc()->GetModel());
            InitializeModelDocumentTree(&DocumentModelSet);
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnCloseDocumentModelTree(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    EmptyModelDocumentTree();
    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnModelDocumentHasChanged(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 0;
    }

    RefreshModelDocumentTree();
    return 0;
}

afx_msg LRESULT ZVProcessWorkspace::OnInitializeModelUnit(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_UnitObserverMsg))
    {
        PSS_UnitObserverMsg* pUnitMsg = (PSS_UnitObserverMsg*)pMsg;

        if (pUnitMsg->GetUnitManager())
        {
            PSS_ModelSet UnitModelSet;

            pUnitMsg->GetUnitManager()->FillModelSet(UnitModelSet);
            InitializeModelUnitTree(&UnitModelSet);
        }
        else
        {
            InitializeModelUnitTree(NULL);
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnCloseUnitModelTree(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    EmptyModelUnitTree();
    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnModelUnitHasChanged(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    RefreshModelUnitTree();
    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnAddModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnRemoveModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnAddModelUnit(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_UnitObserverMsg))
    {
        PSS_UnitObserverMsg* pUnitMsg = (PSS_UnitObserverMsg*)pMsg;

        if (pUnitMsg->GetUnit() && pUnitMsg->GetUnit()->GetUnitDocument())
        {
            AddModelUnit(pUnitMsg->GetUnit()->GetUnitDocument()->GetModel());
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnRemoveModelUnit(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnAddModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_DocObserverMsg))
    {
        PSS_DocObserverMsg* pDocMsg = (PSS_DocObserverMsg*)pMsg;

        if (pDocMsg->GetModel() && pDocMsg->GetElement())
        {
            AddModelDocumentSymbol(pDocMsg->GetElement(), pDocMsg->GetModel());
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnRemoveModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_DocObserverMsg))
    {
        PSS_DocObserverMsg* pDocMsg = (PSS_DocObserverMsg*)pMsg;

        if (pDocMsg->GetModel() && pDocMsg->GetElement())
        {
            RemoveModelDocumentSymbol(pDocMsg->GetElement(), pDocMsg->GetModel());
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnModifyModelDocumentSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_DocObserverMsg))
    {
        PSS_DocObserverMsg* pDocMsg = (PSS_DocObserverMsg*)pMsg;

        if (pDocMsg->GetModel() && pDocMsg->GetElement())
        {
            ModifyModelDocumentSymbol(pDocMsg->GetElement(), pDocMsg->GetModel());
        }
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnAddModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnRemoveModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}

afx_msg LRESULT ZVProcessWorkspace::OnModifyModelUnitSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    return 1;
}
