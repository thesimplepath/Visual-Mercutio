// ZIDropView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIDropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIDropView

IMPLEMENT_DYNCREATE(ZIDropView, ZVBasicView)

ZIDropView::ZIDropView()
{
}

ZIDropView::~ZIDropView()
{
}


BEGIN_MESSAGE_MAP(ZIDropView, ZVBasicView)
	//{{AFX_MSG_MAP(ZIDropView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIDropView drawing

void ZIDropView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// ZIDropView diagnostics

#ifdef _DEBUG
void ZIDropView::AssertValid() const
{
	ZVBasicView::AssertValid();
}

void ZIDropView::Dump(CDumpContext& dc) const
{
	ZVBasicView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIDropView message handlers
