// ZVOutputSearchView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVOutputSearchView.h"

#include "ZBSymbolLogObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSearchView

IMPLEMENT_DYNAMIC( ZVOutputSearchView, ZVOutputView )

BEGIN_MESSAGE_MAP( ZVOutputSearchView, ZVOutputView )
	//{{AFX_MSG_MAP(ZVOutputSearchView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputSearchView::ZVOutputSearchView()
{
	SetSelectLast( true );
}

ZVOutputSearchView::~ZVOutputSearchView()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSearchView message handlers

// Call back function base on list events
void ZVOutputSearchView::OnSelChanged()
{
	// Do nothing
}
void ZVOutputSearchView::OnDoubleClick()
{
	CString s;

	if ( GetCurrentItem( s ) != -1 )
	{
		ZBGenericSymbolErrorLine ErrorLine;
		(ZIErrorLine&)ErrorLine = s;
		ZBSymbolLogObserverMsg msg( ErrorLine );	

		NotifyAllObservers( &msg );
	}
}
