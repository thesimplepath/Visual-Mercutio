// ZIDropScrollView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIDropScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIDropScrollView

IMPLEMENT_DYNCREATE(ZIDropScrollView, ZVBasicScrollView)

ZIDropScrollView::ZIDropScrollView()
{
}

ZIDropScrollView::~ZIDropScrollView()
{
}


BEGIN_MESSAGE_MAP(ZIDropScrollView, ZVBasicScrollView)
	//{{AFX_MSG_MAP(ZIDropScrollView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIDropScrollView drawing

void ZIDropScrollView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// ZIDropScrollView diagnostics

#ifdef _DEBUG
void ZIDropScrollView::AssertValid() const
{
	ZVBasicScrollView::AssertValid();
}

void ZIDropScrollView::Dump(CDumpContext& dc) const
{
	ZVBasicScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIDropScrollView message handlers
