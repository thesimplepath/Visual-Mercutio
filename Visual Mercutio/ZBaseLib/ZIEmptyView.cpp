// ZIEmptyView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIEmptyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIEmptyView

IMPLEMENT_DYNCREATE(ZIEmptyView, CFormView)

ZIEmptyView::ZIEmptyView()
	: CFormView(ZIEmptyView::IDD)
{
	//{{AFX_DATA_INIT(ZIEmptyView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ZIEmptyView::~ZIEmptyView()
{
}

void ZIEmptyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIEmptyView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIEmptyView, CFormView)
	//{{AFX_MSG_MAP(ZIEmptyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIEmptyView diagnostics

#ifdef _DEBUG
void ZIEmptyView::AssertValid() const
{
	CFormView::AssertValid();
}

void ZIEmptyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIEmptyView message handlers
