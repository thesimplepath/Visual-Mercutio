// ZVSelectSymbolFromGraphModel.cpp : implementation file

#include "stdafx.h"
#include "ZVSelectSymbolFromGraphModel.h"

#include "PSS_ProcessGraphModelMdl.h"
#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"

#include "zModelRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 11 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight = 22;

const int IDC_REFRESHVIEWS = 7000;
const int IDC_GO_UP = 7001;

const int UM_REFRESH = 20000;
const int UM_GO_UP = 20001;

/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolFromGraphModel dialog

BEGIN_MESSAGE_MAP(ZVSelectSymbolFromGraphModel, PSS_Dialog)
    //{{AFX_MSG_MAP(ZVSelectSymbolFromGraphModel)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectSymbolFromGraphModel::ZVSelectSymbolFromGraphModel(PSS_ProcessGraphModelMdl*    pModel,
                                                           const CString            Title            /*= ""*/,
                                                           int                        SelectableItem    /*= Selectable_All*/,
                                                           bool                    EnableNavigate    /*= true*/,
                                                           CWnd*                    pParent            /*= NULL*/)
    : PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_Title(Title),
    m_EnableNavigate(EnableNavigate),
    m_pSelectableClass(NULL),
    m_SelectableItem(SelectableItem)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    //}}AFX_DATA_INIT
}

ZVSelectSymbolFromGraphModel::ZVSelectSymbolFromGraphModel(PSS_ProcessGraphModelMdl*    pModel,
                                                           const CString            Title,
                                                           CRuntimeClass*            pSelectableClass,
                                                           bool                    EnableNavigate        /*= true*/,
                                                           CWnd*                    pParent                /*= NULL*/)
    : PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_Title(Title),
    m_EnableNavigate(EnableNavigate),
    m_pSelectableClass(pSelectableClass),
    m_SelectableItem(0)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    //}}AFX_DATA_INIT
}

ZVSelectSymbolFromGraphModel::ZVSelectSymbolFromGraphModel(PSS_ProcessGraphModelMdl*    pModel,
                                                           UINT                    nIDResTitle,
                                                           int                        SelectableItem    /*= Selectable_All*/,
                                                           bool                    EnableNavigate    /*= true*/,
                                                           CWnd*                    pParent            /*= NULL*/)
    : PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_EnableNavigate(EnableNavigate),
    m_pSelectableClass(NULL),
    m_SelectableItem(SelectableItem)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    //}}AFX_DATA_INIT

    m_Title.LoadString(nIDResTitle);
}

ZVSelectSymbolFromGraphModel::ZVSelectSymbolFromGraphModel(PSS_ProcessGraphModelMdl*    pModel,
                                                           UINT                    nIDResTitle,
                                                           CRuntimeClass*            pSelectableClass,
                                                           bool                    EnableNavigate        /*= true*/,
                                                           CWnd*                    pParent                /*= NULL*/)
    : PSS_Dialog(IDD_SELECTSYMBOL_GRAPH, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedSymbol(NULL),
    m_EnableNavigate(EnableNavigate),
    m_pSelectableClass(pSelectableClass),
    m_SelectableItem(0)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    //}}AFX_DATA_INIT

    m_Title.LoadString(nIDResTitle);
}
ZVSelectSymbolFromGraphModel::~ZVSelectSymbolFromGraphModel()
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    m_FlatToolBar.DetachObserver(this);
    m_wndModelGraph.DetachObserver(this);
}

void ZVSelectSymbolFromGraphModel::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVSelectSymbolFromGraphModel)
    DDX_Text(pDX, IDC_SYMBOLPATH, m_SymbolPath);
    //}}AFX_DATA_MAP
}

void ZVSelectSymbolFromGraphModel::CheckSymbol(CODSymbolComponent* pComp)
{
    // Display the absolute path
    if (!pComp)
    {
        m_SymbolPath = _T("");
    }
    else if (pComp && ISA(pComp, PSS_Symbol))
    {
        m_SymbolPath = dynamic_cast<PSS_Symbol*>(pComp)->GetAbsolutePath();
    }
    else if (pComp && ISA(pComp, PSS_LinkSymbol))
    {
        m_SymbolPath = dynamic_cast<PSS_LinkSymbol*>(pComp)->GetAbsolutePath();
    }

    // Reset the selected symbol
    m_pSelectedSymbol = NULL;

    // If the check must be done by runtime class
    if (m_pSelectableClass)
    {
        if (pComp && pComp->IsKindOf(m_pSelectableClass))
        {
            m_pSelectedSymbol = pComp;
        }
    }
    else
    {
        if (m_SelectableItem & Selectable_All)
        {
            m_pSelectedSymbol = pComp;
        }
        else if (m_SelectableItem & Selectable_LinkSymbol)
        {
            if (pComp && ISA(pComp, PSS_LinkSymbol))
            {
                m_pSelectedSymbol = pComp;
            }
        }
        else if (m_SelectableItem & Selectable_Process)
        {
            if (pComp && ISA(pComp, PSS_Symbol))
            {
                m_pSelectedSymbol = pComp;
            }
        }
        else if (m_SelectableItem & Selectable_Symbol)
        {
            if (pComp && ISA(pComp, PSS_Symbol))
            {
                m_pSelectedSymbol = pComp;
            }
        }
    }

    // Enable or not the OK button
    if (GetDlgItem(IDOK))
    {
        GetDlgItem(IDOK)->EnableWindow(m_pSelectedSymbol != NULL);
    }

    // Put value to the dialog
    UpdateData(FALSE);
}

void ZVSelectSymbolFromGraphModel::MoveControls(int cx, int cy)
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
        GetDlgItem(IDC_DIAGRAM)->MoveWindow(5, _FlatToolbarHeight + 5, cx - 10, cy - 70);
    }

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(1, 1, cx, _FlatToolbarHeight);
    }
}

void ZVSelectSymbolFromGraphModel::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, _ZBSelectSymbolObserverMsg))
    {
        CheckSymbol(dynamic_cast<_ZBSelectSymbolObserverMsg*>(pMsg)->GetComponent());
    }

    m_wndModelGraph.OnUpdate(pSubject, pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolFromGraphModel message handlers

void ZVSelectSymbolFromGraphModel::OnOK()
{
    // TODO: Add extra validation here

    PSS_Dialog::OnOK();
}

BOOL ZVSelectSymbolFromGraphModel::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                     WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                     CRect(0, 0, 100, _FlatToolbarHeight),
                                                     this,
                                                     IDC_FLAT_TB_SELECTSYMBOL);

    m_FlatToolBar.EnableNavigate(m_EnableNavigate);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);

    CRect rc;
    m_wndModelGraph.SubclassDlgItem(IDC_DIAGRAM, this);
    m_wndModelGraph.SetModel(m_pModel);
    m_wndModelGraph.ShowWindow(SW_SHOW);
    m_wndModelGraph.GetClientRect(&rc);
    m_wndModelGraph.Initialize();

    // Attach us as an observer for messages
    m_wndModelGraph.AttachObserver(this);

    // Set the enable navigate flag
    m_wndModelGraph.SetEnableNavigate(m_EnableNavigate);

    if (!m_Title.IsEmpty())
    {
        SetWindowText(m_Title);
    }

    GetClientRect(&rc);
    MoveControls(rc.Width(), rc.Height());

    CheckSymbol(NULL);

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVSelectSymbolFromGraphModel::OnSize(UINT nType, int cx, int cy)
{
    PSS_Dialog::OnSize(nType, cx, cy);
    MoveControls(cx, cy);

}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelWnd

BEGIN_MESSAGE_MAP(_ZVGraphModelWnd, CWnd)
    //{{AFX_MSG_MAP(_ZVGraphModelWnd)
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVGraphModelWnd::_ZVGraphModelWnd()
{
    m_pModel = NULL;
}

_ZVGraphModelWnd::~_ZVGraphModelWnd()
{}

void _ZVGraphModelWnd::Initialize()
{
    m_vpDialog.Create(this, NULL);
    m_vpDialog.SetModel(m_pModel);

    CRect rcClient;
    GetClientRect(&rcClient);
    m_vpDialog.SetSize(rcClient.Width(), rcClient.Height());

    m_vpDialog.OnInitialUpdate();
}

void _ZVGraphModelWnd::SetCurrentSymbol(CODSymbolComponent* pComp)
{
    _ZBSelectSymbolObserverMsg msg(pComp);
    NotifyAllObservers(&msg);
}

void _ZVGraphModelWnd::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    m_vpDialog.OnUpdate(pSubject, pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CDesignerView attributes

CWnd* _ZVGraphModelWnd::GetWnd() const
{
    return (CWnd*)this;
}

CODModel* _ZVGraphModelWnd::GetModel()
{
    return m_pModel;
}

void _ZVGraphModelWnd::SetModel(CODModel* pModel)
{
    ASSERT_VALID(pModel);

    m_pModel = pModel;
    m_vpDialog.SetModel(m_pModel);

    if (m_vpDialog.GetWnd() && ::IsWindow(m_vpDialog.GetWnd()->GetSafeHwnd()))
    {
        m_vpDialog.UpdateAll();
    }
}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelWnd message handlers

BOOL _ZVGraphModelWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // First pump through normal channels.  This allows you to override
    // the components default handling inside the view class.
    if (CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

    // then pump through the visual component
    return m_vpDialog.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL _ZVGraphModelWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    BOOL bHandled = FALSE;
    LRESULT lResult;

    bHandled = m_vpDialog.OnWndMsg(message, wParam, lParam, &lResult);

    if (!bHandled)
    {
        bHandled = CWnd::OnWndMsg(message, wParam, lParam, pResult);
    }

    return bHandled;
}

void _ZVGraphModelWnd::OnPaint()
{
    // Device context for painting
    CPaintDC dc(this);

    m_vpDialog.Draw(&dc);
}

void _ZVGraphModelWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    m_vpDialog.ReSizeToWnd(*this);
}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelViewport construction/destruction

_ZVGraphModelViewport::_ZVGraphModelViewport()
{}

_ZVGraphModelViewport::~_ZVGraphModelViewport()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelViewport implementation

BOOL _ZVGraphModelViewport::CreateController()
{
    m_pCtlr = new _ZVGraphModelController(this);
    m_bAutoDelCtlr = TRUE;

    return TRUE;
}

void _ZVGraphModelViewport::ReSizeToWnd(CWnd& Wnd)
{
    // viewport initialization
    CRect r;
    Wnd.GetClientRect(&r);
    SetSize(r.Size());
}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelViewport message handlers

void _ZVGraphModelViewport::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (m_pCtlr)
    {
        dynamic_cast<_ZVGraphModelController*>(m_pCtlr)->OnUpdate(pSubject, pMsg);
    }
}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelController

BEGIN_MESSAGE_MAP(_ZVGraphModelController, CODController)
    //{{AFX_MSG_MAP(_ZVGraphModelController)
    ON_WM_LBUTTONDBLCLK()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelController construction/destruction

_ZVGraphModelController::_ZVGraphModelController(CODViewport* pViewport)
    : CODController(pViewport),
    m_pSelectedSymbol(NULL)
{}

_ZVGraphModelController::~_ZVGraphModelController()
{}

CODSymbolComponent* _ZVGraphModelController::GetSymbolSelected()
{
    CODSymbolComponent* pComp = NULL;

    if (GetSelection()->GetSize() == 1 &&
        (ISA(GetSelection()->GetAt(0), PSS_Symbol) || ISA(GetSelection()->GetAt(0), PSS_LinkSymbol)))
    {
        pComp = (CODSymbolComponent*)GetSelection()->GetAt(0);
    }
    else if (GetSelection()->GetSize() == 1 && ISA(GetSelection()->GetAt(0), CODLabelComponent))
    {
        // Select the symbol behind
        pComp = dynamic_cast<CODLabelComponent*>(GetSelection()->GetAt(0))->GetOwner();
    }

    return pComp;
}

void _ZVGraphModelController::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_REFRESH:
            {
                OnRefresh();
                break;
            }

            case UM_GO_UP:
            {
                OnGoUp();
                break;
            }
        }
    }
}

void _ZVGraphModelController::OnRefresh()
{
    if (GetVp())
    {
        GetVp()->UpdateAll();
    }
}

void _ZVGraphModelController::OnGoUp()
{
    if (GetVp()->GetWnd() && reinterpret_cast<_ZVGraphModelWnd*>(GetVp()->GetWnd())->GetEnableNavigate())
    {
        CODModel* pModel = dynamic_cast<CODModel*>(GetModel());

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
        {
            if (dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetParent())
            {
                // Clear the selection
                ClearSelection();

                // Set the model
                reinterpret_cast<_ZVGraphModelWnd*>(GetVp()->GetWnd())->SetModel(dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetParent());

                // Refresh the view
                GetVp()->GetWnd()->UpdateWindow();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelController message handlers

void _ZVGraphModelController::OnSelectionChange(CODComponentSet* pChangedSet)
{
    CODController::OnSelectionChange(pChangedSet);

    // Save the selected element
    m_pSelectedSymbol = GetSymbolSelected();

    if (GetVp()->GetWnd())
    {
        // Set the symbol selected
        reinterpret_cast<_ZVGraphModelWnd*>(GetVp()->GetWnd())->SetCurrentSymbol(m_pSelectedSymbol);
    }
}

void _ZVGraphModelController::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CODComponent* pComp = GetSymbolSelected();

    if (GetVp()->GetWnd() && reinterpret_cast<_ZVGraphModelWnd*>(GetVp()->GetWnd())->GetEnableNavigate())
    {

        // If the symbol has a child model, open it
        if (pComp != NULL &&
            ISA(pComp, PSS_Symbol) &&
            dynamic_cast<PSS_Symbol*>(pComp)->GetChildModel())
        {
            // Clear the selection
            ClearSelection();

            // Set the model
            reinterpret_cast<_ZVGraphModelWnd*>(GetVp()->GetWnd())->SetModel(dynamic_cast<PSS_Symbol*>(pComp)->GetChildModel());

            // Refresh the view
            GetVp()->GetWnd()->UpdateWindow();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// _ZBSelectSymbolObserverMsg dialog

IMPLEMENT_DYNAMIC(_ZBSelectSymbolObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

_ZBSelectSymbolObserverMsg::_ZBSelectSymbolObserverMsg(CODSymbolComponent* pComp /*= NULL*/) :
    PSS_ObserverMsg(),
    m_pComp(pComp)
{}

_ZBSelectSymbolObserverMsg::~_ZBSelectSymbolObserverMsg()
{}

/////////////////////////////////////////////////////////////////////////////
// _ZVSelectSymbolFlatToolBar

BEGIN_MESSAGE_MAP(_ZVSelectSymbolFlatToolBar, CStatic)
    //{{AFX_MSG_MAP(_ZVSelectSymbolFlatToolBar)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_BN_CLICKED(IDC_GO_UP, OnGoUpButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

_ZVSelectSymbolFlatToolBar::_ZVSelectSymbolFlatToolBar()
    : m_EnableNavigate(true)
{
    m_ImageList.Create(IDB_SELECTSYM_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZVSelectSymbolFlatToolBar::~_ZVSelectSymbolFlatToolBar()
{}

void _ZVSelectSymbolFlatToolBar::EnableNavigate(bool EnableNavigate /*= true*/)
{
    m_EnableNavigate = EnableNavigate;

    if (m_EnableNavigate == false)
    {
        m_GoUpButton.SetChecked(TRUE);
    }
}

/////////////////////////////////////////////////////////////////////////////
// _ZVSelectSymbolFlatToolBar message handlers

int _ZVSelectSymbolFlatToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    int IconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);

    rc.top += 1;
    rc.bottom -= 1;
    rc.left += 1;
    rc.right = rc.left + 24;

    if (!m_RefreshButton.Create(NULL,
                                WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_REFRESHVIEWS))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_GoUpButton.Create(NULL,
                             WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                             rc,
                             this,
                             IDC_GO_UP))
    {
        TRACE0(_T("Unable to create button.\n"));
        return -1;
    }

    m_GoUpButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS), IDS_REFRESH);
    m_tooltip.AddTool(GetDlgItem(IDC_GO_UP), IDS_GO_UP);

    return 0;
}

void _ZVSelectSymbolFlatToolBar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}

void _ZVSelectSymbolFlatToolBar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg Msg(UM_REFRESH);
    NotifyAllObservers(&Msg);
}

void _ZVSelectSymbolFlatToolBar::OnGoUpButton()
{
    PSS_ToolbarObserverMsg Msg(UM_GO_UP);
    NotifyAllObservers(&Msg);
}

BOOL _ZVSelectSymbolFlatToolBar::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
