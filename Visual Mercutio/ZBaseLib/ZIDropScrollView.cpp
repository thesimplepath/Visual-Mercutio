// ZIDropScrollView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIDropScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(ZIDropScrollView, PSS_BasicScrollView)

BEGIN_MESSAGE_MAP(ZIDropScrollView, PSS_BasicScrollView)
    //{{AFX_MSG_MAP(ZIDropScrollView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIDropScrollView::ZIDropScrollView() :
    PSS_BasicScrollView()
{}
ZIDropScrollView::~ZIDropScrollView()
{}
void ZIDropScrollView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}
#ifdef _DEBUG
void ZIDropScrollView::AssertValid() const
{
    ZVBasicScrollView::AssertValid();
}
#endif
#ifdef _DEBUG
void ZIDropScrollView::Dump(CDumpContext& dc) const
{
    ZVBasicScrollView::Dump(dc);
}
#endif
