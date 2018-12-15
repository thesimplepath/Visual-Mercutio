// ZVOutputAnalyzerLogView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVOutputAnalyzerLogView.h"

#include "ZBSymbolLogObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOutputAnalyzerLogView

IMPLEMENT_DYNAMIC( ZVOutputAnalyzerLogView, ZVOutputView )

BEGIN_MESSAGE_MAP( ZVOutputAnalyzerLogView, ZVOutputView )
    //{{AFX_MSG_MAP(ZVOutputAnalyzerLogView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputAnalyzerLogView::ZVOutputAnalyzerLogView()
{
    SetSelectLast( true );
}

ZVOutputAnalyzerLogView::~ZVOutputAnalyzerLogView()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputAnalyzerLogView message handlers

// Call back function base on list events
void ZVOutputAnalyzerLogView::OnSelChanged()
{
    // Do nothing
}
void ZVOutputAnalyzerLogView::OnDoubleClick()
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
