/****************************************************************************
 * ==> PSS_SelectSymbolFromGraphModelDlg -----------------------------------*
 ****************************************************************************
 * Description : Provides a symbol selector from graphic model dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectSymbolFromGraphModelDlg.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight = 22;
const int g_RefreshViewsID    = 7000;
const int g_GoUpID            = 7001;
const int g_RefreshMsg        = 20000;
const int g_GoUpMsg           = 20001;
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport::IGraphModelViewport() :
    CODBufferedRulerViewport(),
    PSS_Observer()
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport::~IGraphModelViewport()
{}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport::CreateController()
{
    m_pCtlr        = new IGraphModelController(this);
    m_bAutoDelCtlr = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport::ResizeToWnd(const CWnd& wnd)
{
    CRect r;

    // viewport initialization
    wnd.GetClientRect(&r);
    SetSize(r.Size());
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelViewport::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    IGraphModelController* pController = dynamic_cast<IGraphModelController*>(m_pCtlr);

    if (pController)
        pController->OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectSymbolFromGraphModelDlg::IGraphModelController, CODController)
    //{{AFX_MSG_MAP(PSS_SelectSymbolFromGraphModelDlg::IGraphModelController)
    ON_WM_LBUTTONDBLCLK()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::IGraphModelController
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::IGraphModelController(CODViewport* pViewport) :
    CODController(pViewport),
    PSS_Observer(),
    m_pSelectedSymbol(NULL)
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::~IGraphModelController()
{}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::OnSelectionChange(CODComponentSet* pChangedSet)
{
    CODController::OnSelectionChange(pChangedSet);

    // save the selected element
    m_pSelectedSymbol = FindSelectedSymbol();

    CODViewport*    pViewport = GetVp();
    IGraphModelWnd* pWnd      = pViewport ? dynamic_cast<IGraphModelWnd*>(pViewport->GetWnd()) : NULL;

    // set the selected symbol
    if (pWnd)
        pWnd->SetCurrentSymbol(m_pSelectedSymbol);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ToolbarObserverMsg* pToolbarObserverMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarObserverMsg)
        switch (pToolbarObserverMsg->GetMessageID())
        {
            case g_RefreshMsg: OnRefresh(); break;
            case g_GoUpMsg:    OnGoUp();    break;
        }
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CODComponent*   pComp     = FindSelectedSymbol();
    CODViewport*    pViewport = GetVp();
    IGraphModelWnd* pWnd      = pViewport ? dynamic_cast<IGraphModelWnd*>(pViewport->GetWnd()) : NULL;

    if (pWnd && pWnd->GetEnableNavigate())
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        // if the symbol contains a child model, open it
        if (pSymbol && pSymbol->GetChildModel())
        {
            // clear the selection
            ClearSelection();

            // set the model
            pWnd->SetModel(pSymbol->GetChildModel());

            // refresh the view
            pWnd->UpdateWindow();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::OnRefresh()
{
    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->UpdateAll();
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::OnGoUp()
{
    CODViewport*    pViewport = GetVp();
    IGraphModelWnd* pWnd      = pViewport ? dynamic_cast<IGraphModelWnd*>(pViewport->GetWnd()) : NULL;

    if (pWnd && pWnd->GetEnableNavigate())
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetModel());

        if (pModel && pModel->GetParent())
        {
            // clear the selection
            ClearSelection();

            // set the model
            pWnd->SetModel(pModel->GetParent());

            // refresh the view
            pWnd->UpdateWindow();
        }
    }
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SelectSymbolFromGraphModelDlg::IGraphModelController::FindSelectedSymbol()
{
    CODSymbolComponent* pComp   = NULL;
    CODComponentSet*    pSelSet = GetSelection();

    if (pSelSet && pSelSet->GetSize() == 1)
    {
        CODComponent* pSelection = pSelSet->GetAt(0);

        if (pSelection)
        {
            PSS_Symbol*     pSelSymbol     =                     dynamic_cast<PSS_Symbol*>(pSelection);
            PSS_LinkSymbol* pSelLinkSymbol = pSelSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSelection);

            if (pSelSymbol)
                pComp = pSelSymbol;
            else
            if (pSelLinkSymbol)
                pComp = pSelLinkSymbol;
            else
            {
                CODLabelComponent* pSelectedLabel = dynamic_cast<CODLabelComponent*>(pSelection);

                // select the symbol behind
                if (pSelectedLabel)
                    pComp = pSelectedLabel->GetOwner();
            }
        }
    }

    return pComp;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd)
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::IGraphModelWnd() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_pModel(NULL),
    m_EnableNavigate(false)
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::~IGraphModelWnd()
{}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::Initialize()
{
    m_DialogViewport.Create(this, NULL);
    m_DialogViewport.SetModel(m_pModel);

    CRect rcClient;
    GetClientRect(&rcClient);
    m_DialogViewport.SetSize(rcClient.Width(), rcClient.Height());

    m_DialogViewport.OnInitialUpdate();
}
//---------------------------------------------------------------------------
CWnd* PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::GetWnd() const
{
    return (CWnd*)this;
}
//---------------------------------------------------------------------------
CODModel* PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::GetModel()
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::SetModel(CODModel* pModel)
{
    ASSERT_VALID(pModel);

    m_pModel = pModel;
    m_DialogViewport.SetModel(m_pModel);

    CWnd* pWnd = m_DialogViewport.GetWnd();

    if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
        m_DialogViewport.UpdateAll();
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::SetCurrentSymbol(CODSymbolComponent* pComp)
{
    ISelectSymbolObserverMsg msg(pComp);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    m_DialogViewport.OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::OnPaint()
{
    CPaintDC dc(this);
    m_DialogViewport.Draw(&dc);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    m_DialogViewport.ResizeToWnd(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    LRESULT lResult;
    BOOL    handled = m_DialogViewport.OnWndMsg(message, wParam, lParam, &lResult);

    if (!handled)
        handled = CWnd::OnWndMsg(message, wParam, lParam, pResult);

    return handled;
}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolFromGraphModelDlg::IGraphModelWnd::OnCmdMsg(UINT                nID,
                                                                 int                 nCode,
                                                                 void*               pExtra,
                                                                 AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // pump through normal channels. This allows the caller to override the components default handling inside the view class
    if (CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // pump through the visual component
    return m_DialogViewport.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
typedef PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg ISelectSymbolObserverMsg;
IMPLEMENT_DYNAMIC(ISelectSymbolObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg::ISelectSymbolObserverMsg(CODSymbolComponent* pComp) :
    PSS_ObserverMsg(),
    m_pComp(pComp)
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolObserverMsg::~ISelectSymbolObserverMsg()
{}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar)
    ON_BN_CLICKED(g_RefreshViewsID, OnRefreshButton)
    ON_BN_CLICKED(g_GoUpID, OnGoUpButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::ISelectSymbolFlatToolBar() :
    CStatic(),
    PSS_Subject(),
    m_EnableNavigate(true)
{
    m_ImageList.Create(IDB_SELECTSYM_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::~ISelectSymbolFlatToolBar()
{}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::EnableNavigate(bool enabled)
{
    m_EnableNavigate = enabled;

    if (!m_EnableNavigate)
        m_GoUpButton.SetChecked(TRUE);
}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // let the ToolTip process this message
    m_Tooltip.RelayEvent(pMsg);

    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);

    rc.top    += 1;
    rc.bottom -= 1;
    rc.left   += 1;
    rc.right   = rc.left + 24;

    if (!m_RefreshButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                g_RefreshViewsID))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    int iconIndex = 0;

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);
    ++iconIndex;

    if (!m_GoUpButton.Create(NULL,
                             WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                             rc,
                             this,
                             g_GoUpID))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_GoUpButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the ToolTip control
    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);

    m_Tooltip.AddTool(GetDlgItem(g_RefreshViewsID), IDS_REFRESH);
    m_Tooltip.AddTool(GetDlgItem(g_GoUpID),         IDS_GO_UP);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(g_RefreshMsg);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::ISelectSymbolFlatToolBar::OnGoUpButton()
{
    PSS_ToolbarObserverMsg msg(g_GoUpMsg);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectSymbolFromGraphModelDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_SelectSymbolFromGraphModelDlg)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectSymbolFromGraphModelDlg
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                                                     const CString&            title,
                                                                     int                       selectableItem,
                                                                     bool                      enableNavigate,
                                                                     CWnd*                     pParent) :
    PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    PSS_Observer(),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(NULL),
    m_Title(title),
    m_SelectableItem(selectableItem),
    m_EnableNavigate(enableNavigate)
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                                                     const CString&            title,
                                                                     CRuntimeClass*            pSelectableClass,
                                                                     bool                      enableNavigate,
                                                                     CWnd*                     pParent) :
    PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    PSS_Observer(),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(pSelectableClass),
    m_Title(title),
    m_SelectableItem(0),
    m_EnableNavigate(enableNavigate)
{}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                                                     UINT                      titleID,
                                                                     int                       selectableItem,
                                                                     bool                      enableNavigate,
                                                                     CWnd*                     pParent) :
    PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    PSS_Observer(),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(NULL),
    m_SelectableItem(selectableItem),
    m_EnableNavigate(enableNavigate)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::PSS_SelectSymbolFromGraphModelDlg(PSS_ProcessGraphModelMdl* pModel,
                                                                     UINT                      titleID,
                                                                     CRuntimeClass*            pSelectableClass,
                                                                     bool                      enableNavigate,
                                                                     CWnd*                     pParent) :
    PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    PSS_Observer(),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(pSelectableClass),
    m_SelectableItem(0),
    m_EnableNavigate(enableNavigate)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectSymbolFromGraphModelDlg::~PSS_SelectSymbolFromGraphModelDlg()
{
    m_FlatToolBar.DetachObserver(this);
    m_WndModelGraph.DetachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    ISelectSymbolObserverMsg* pSymObserverMsg = dynamic_cast<ISelectSymbolObserverMsg*>(pMsg);

    if (pSymObserverMsg)
        CheckSymbol(pSymObserverMsg->GetComponent());

    m_WndModelGraph.OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectSymbolFromGraphModelDlg)
    DDX_Text(pDX, IDC_SYMBOLPATH, m_SymbolPath);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectSymbolFromGraphModelDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    // create the flat toolbar
    static_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                CRect(0, 0, 100, g_FlatToolbarHeight),
                                                this,
                                                IDC_FLAT_TB_SELECTSYMBOL);

    m_FlatToolBar.EnableNavigate(m_EnableNavigate);

    // attach this class as a message observer
    m_FlatToolBar.AttachObserver(this);

    CRect rc;
    m_WndModelGraph.SubclassDlgItem(IDC_DIAGRAM, this);
    m_WndModelGraph.SetModel(m_pModel);
    m_WndModelGraph.ShowWindow(SW_SHOW);
    m_WndModelGraph.GetClientRect(&rc);
    m_WndModelGraph.Initialize();

    // attach this class as a message observer
    m_WndModelGraph.AttachObserver(this);

    // set the enable navigate flag
    m_WndModelGraph.SetEnableNavigate(m_EnableNavigate);

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    GetClientRect(&rc);
    MoveControls(rc.Width(), rc.Height());

    CheckSymbol(NULL);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::OnSize(UINT nType, int cx, int cy)
{
    PSS_Dialog::OnSize(nType, cx, cy);
    MoveControls(cx, cy);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::OnOK()
{
    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::MoveControls(int cx, int cy)
{
    CRect rc;

    if (GetDlgItem(IDOK))
    {
        GetDlgItem(IDOK)->GetClientRect(&rc);
        GetDlgItem(IDOK)->MoveWindow(cx - rc.Width() - 5, cy - rc.Height() - 5, rc.Width(), rc.Height());
        GetDlgItem(IDOK)->UpdateWindow();
    }

    if (GetDlgItem(IDCANCEL))
    {
        GetDlgItem(IDCANCEL)->GetClientRect(&rc);
        GetDlgItem(IDCANCEL)->MoveWindow(cx - rc.Width() - 90, cy - rc.Height() - 5, rc.Width(), rc.Height());
        GetDlgItem(IDCANCEL)->UpdateWindow();
    }

    if (GetDlgItem(IDC_SYMBOLPATH))
    {
        GetDlgItem(IDC_SYMBOLPATH)->GetClientRect(&rc);
        GetDlgItem(IDC_SYMBOLPATH)->MoveWindow(5,
                                               cy - rc.Height() - 5,
                                               ((cx - 200) > 10) ? (cx - 200) : 10, rc.Height());
    }

    if (GetDlgItem(IDC_DIAGRAM))
    {
        GetDlgItem(IDC_DIAGRAM)->GetClientRect(&rc);
        GetDlgItem(IDC_DIAGRAM)->MoveWindow(5, g_FlatToolbarHeight + 5, cx - 10, cy - 70);
    }

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
        m_FlatToolBar.MoveWindow(1, 1, cx, g_FlatToolbarHeight);
}
//---------------------------------------------------------------------------
void PSS_SelectSymbolFromGraphModelDlg::CheckSymbol(CODSymbolComponent* pComp)
{
    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

    // show the absolute path
    if (!pComp)
        m_SymbolPath = _T("");
    else
    if (pSymbol)
        m_SymbolPath = pSymbol->GetAbsolutePath();
    else
    if (pLinkSymbol)
        m_SymbolPath = pLinkSymbol->GetAbsolutePath();

    // reset the selected symbol
    m_pSelectedSymbol = NULL;

    // if the check must be done by runtime class
    if (m_pSelectableClass)
    {
        if (pComp && pComp->IsKindOf(m_pSelectableClass))
            m_pSelectedSymbol = pComp;
    }
    else
    if (m_SelectableItem & g_Selectable_All)
        m_pSelectedSymbol = pComp;
    else
    if (m_SelectableItem & g_Selectable_LinkSymbol)
    {
        if (pLinkSymbol)
            m_pSelectedSymbol = pComp;
    }
    else
    if (m_SelectableItem & g_Selectable_Process)
    {
        if (pSymbol)
            m_pSelectedSymbol = pComp;
    }
    else
    if (m_SelectableItem & g_Selectable_Symbol)
        if (pSymbol)
            m_pSelectedSymbol = pComp;

    // enable or not the OK button
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_pSelectedSymbol != NULL);

    // set the dialog values
    UpdateData(FALSE);
}
//---------------------------------------------------------------------------
