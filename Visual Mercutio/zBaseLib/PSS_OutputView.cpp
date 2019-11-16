/****************************************************************************
 * ==> PSS_OutputView ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputView.h"

// processsoft
#include "PSS_ToolbarObserverMsg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputView::IOutputViewListBox, CListBox)
    //{{AFX_MSG_MAP(PSS_OutputView::IOutputViewListBox)
    ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
    ON_CONTROL_REFLECT(LBN_DBLCLK, OnDblclk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputView::IOutputViewListBox
//---------------------------------------------------------------------------
PSS_OutputView::IOutputViewListBox::IOutputViewListBox() :
    CListBox(),
    PSS_Subject()
{}
//---------------------------------------------------------------------------
PSS_OutputView::IOutputViewListBox::~IOutputViewListBox()
{}
//---------------------------------------------------------------------------
void PSS_OutputView::IOutputViewListBox::OnSelchange()
{
    PSS_ToolbarObserverMsg msg(LBN_SELCHANGE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_OutputView::IOutputViewListBox::OnDblclk()
{
    PSS_ToolbarObserverMsg msg(LBN_DBLCLK);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_OutputView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputView, CWnd)
    //{{AFX_MSG_MAP(PSS_OutputView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputView
//---------------------------------------------------------------------------
PSS_OutputView::PSS_OutputView() :
    CWnd(),
    PSS_Log(),
    PSS_Subject(),
    PSS_Observer(),
    m_pListBox(NULL),
    m_SelectLast(false),
    m_IsInDebugMode(false)
{
    m_pListBox   = new IOutputViewListBox();
    m_ClrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}
//---------------------------------------------------------------------------
PSS_OutputView::~PSS_OutputView()
{}
//---------------------------------------------------------------------------
void PSS_OutputView::Release()
{
    if (!m_pListBox)
    {
        m_pListBox->DetachObserver(this);
        delete m_pListBox;
        m_pListBox = NULL;
    }
}
//---------------------------------------------------------------------------
void PSS_OutputView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ToolbarObserverMsg* pToolbarObserverMsg  = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarObserverMsg)
        switch (pToolbarObserverMsg->GetMessageID())
        {
            case LBN_SELCHANGE:
                OnSelChanged();
                break;

            case LBN_DBLCLK:
                OnDoubleClick();
                break;
        }
}
//---------------------------------------------------------------------------
int PSS_OutputView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_pListBox)
        return -1;

    if (!m_pListBox->Create(WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_DISABLENOSCROLL | LBS_NOTIFY,
                            CRect(0, 0, 0, 0),
                            this,
                            IDC_OUTPUTVIEW_LIST))
    {
        TRACE0(_T("Failed to create view for the CListBox in ZVOutputView\n"));
        return -1;
    }

    // get the log font
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);

    VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
                                  sizeof(NONCLIENTMETRICS),
                                  &ncm,
                                  0));

    m_Font.CreateFontIndirect(&ncm.lfMessageFont);
    m_pListBox->SetFont(&m_Font);
    m_pListBox->SetHorizontalExtent(2000);

    m_pListBox->AttachObserver(this);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_OutputView::OnSize(UINT nType, int cx, int cy)
{
    if (!m_pListBox)
        return;

    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_pListBox->GetSafeHwnd()))
        m_pListBox->MoveWindow(0, 0, cx, cy);
}
//---------------------------------------------------------------------------
BOOL PSS_OutputView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    BOOL    handled = FALSE;
    LRESULT lResult;

    if (m_pListBox)
        handled = m_pListBox->OnWndMsg(message, wParam, lParam, &lResult);

    if (!handled)
        handled = CWnd::OnWndMsg(message, wParam, lParam, pResult);

    return handled;
}
//---------------------------------------------------------------------------
BOOL PSS_OutputView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    if (!m_pListBox)
        return FALSE;

    // pump through normal channels to override the components default handling inside the view class
    if (CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // pump through the visual component
    return m_pListBox->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//---------------------------------------------------------------------------
void PSS_OutputView::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // get the client rect for this control
    CRect rc;
    GetClientRect(&rc);

    // set the background to transparent, and draw a 3D border around the control
    dc.SetBkMode(TRANSPARENT);
    dc.FillSolidRect(rc, m_ClrBtnFace);
}
//---------------------------------------------------------------------------
void PSS_OutputView::OnSelChanged()
{}
//---------------------------------------------------------------------------
void PSS_OutputView::OnDoubleClick()
{}
//---------------------------------------------------------------------------
