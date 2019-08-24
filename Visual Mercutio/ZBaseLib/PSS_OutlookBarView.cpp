/****************************************************************************
 * ==> PSS_OutlookBarView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an Outlook bar view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutlookBarView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_OutlookBarView, CView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutlookBarView, CView)
    //{{AFX_MSG_MAP(PSS_OutlookBarView)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_MESSAGE(WM_OUTLOOKBAR_NOTIFY, (LRESULT(CWnd::*)(WPARAM, LPARAM))OnOutbarNotify)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutlookBarView
//---------------------------------------------------------------------------
PSS_OutlookBarView::PSS_OutlookBarView() :
    CView()
{}
//---------------------------------------------------------------------------
PSS_OutlookBarView::~PSS_OutlookBarView()
{}
//---------------------------------------------------------------------------
void PSS_OutlookBarView::InitializeMenuControl(CContentItems* pContents,
                                               std::size_t    contentSize,
                                               CImageList*    pImageListSmall,
                                               CImageList*    pImageListLarge)
{
    // set the font to use for the menu control
    m_Font.CreatePointFont(85, _T("Tahoma"));
    m_OutlookBar.SetFont(&m_Font);

    // set the image list for the menu control
    m_OutlookBar.SetImageLists(pImageListSmall, pImageListLarge);
    m_OutlookBar.SetItems(pContents, contentSize);
}
//---------------------------------------------------------------------------
BOOL PSS_OutlookBarView::ChangeContext(std::size_t context)
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_OutlookBarView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
int PSS_OutlookBarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the pager control and set its parent to 'this'
    if (!m_Pager.Create(WS_CHILD | WS_VISIBLE | PGS_VERT, CRect(0, 0, 0, 0), this, IDC_PAGER_CONTROL))
    {
        TRACE0("Failed to create CPagerCtrl...\n");
        return -1;
    }

    // set the style to use with the COutlookBar
    const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LBS_OWNERDRAWVARIABLE | LBS_NOINTEGRALHEIGHT | WS_TABSTOP;

    // create the COutlookBar, and set its parent to CPagerCtrl.
    if (!m_OutlookBar.Create(dwStyle, CRect(0, 0, 0, 0), &m_Pager, IDC_OUTLOOK_BAR))
    {
        TRACE0("Failed to create COutlookBar...\n");
        return -1;
    }

    // set the CWnd object you want messages sent to
    m_OutlookBar.SetOwner(this);

    // set the vert/horz scroll area for pager
    m_Pager.SetScrollArea(0, 575);

    // set the child HWND to COutlookBar, and button size to 15
    m_Pager.SetChild(m_OutlookBar.m_hWnd);
    m_Pager.SetButtonSize(15);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_OutlookBarView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // size the outlook style menu, and set the column size same as view
    m_Pager.MoveWindow(0, 0, cx, cy);
    m_OutlookBar.Invalidate(true);
}
//---------------------------------------------------------------------------
BOOL PSS_OutlookBarView::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
        case OBM_ITEMCLICK: return ChangeContext(std::size_t(lParam));
    }

    return FALSE;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_OutlookBarView::AssertValid() const
    {
        CView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_OutlookBarView::Dump(CDumpContext& dc) const
    {
        CView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
