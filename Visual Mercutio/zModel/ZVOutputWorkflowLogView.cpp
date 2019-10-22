// ZVOutputWorkflowLogView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVOutputWorkflowLogView.h"

#include "ZBSymbolLogObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOutputWorkflowLogView

IMPLEMENT_DYNAMIC(ZVOutputWorkflowLogView, ZVOutputView)

BEGIN_MESSAGE_MAP(ZVOutputWorkflowLogView, ZVOutputView)
    //{{AFX_MSG_MAP(ZVOutputWorkflowLogView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputWorkflowLogView::ZVOutputWorkflowLogView()
{
    SetSelectLast(true);
}

ZVOutputWorkflowLogView::~ZVOutputWorkflowLogView()
{}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputWorkflowLogView message handlers

// Call back function base on list events
void ZVOutputWorkflowLogView::OnSelChanged()
{
    // Do nothing
}
void ZVOutputWorkflowLogView::OnDoubleClick()
{
    CString s;

    if (GetCurrentItem(s) != -1)
    {
        ZBGenericSymbolErrorLine ErrorLine;
        (PSS_ErrorLine&)ErrorLine = s;
        ZBSymbolLogObserverMsg msg(ErrorLine);

        NotifyAllObservers(&msg);
    }
}
