/****************************************************************************
 * ==> PSS_PropertyListView ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property list view                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyListView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_PropertyListView, CView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertyListView, CView)
    //{{AFX_MSG_MAP(PSS_PropertyListView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertyListView
//---------------------------------------------------------------------------
PSS_PropertyListView::PSS_PropertyListView() :
    CView(),
    PSS_Observer()
{}
//---------------------------------------------------------------------------
PSS_PropertyListView::~PSS_PropertyListView()
{}
//---------------------------------------------------------------------------
void PSS_PropertyListView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    m_ListCtrl.OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::OnDraw(CDC* pDC)
{}
//---------------------------------------------------------------------------
int PSS_PropertyListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_ListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT, CRect(), this, 1);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PropertyListView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    m_ListCtrl.MoveWindow(0, 0, cx, cy);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PropertyListView::AssertValid() const
    {
        CView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PropertyListView::Dump(CDumpContext& dc) const
    {
        CView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
