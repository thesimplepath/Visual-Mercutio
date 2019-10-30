// ZVOutputSymbolLogView.cpp : implementation file

#include "stdafx.h"
#include "ZVOutputSymbolLogView.h"

#include "ZBSymbolLogObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSymbolLogView

IMPLEMENT_DYNAMIC(ZVOutputSymbolLogView, PSS_OutputView)

BEGIN_MESSAGE_MAP(ZVOutputSymbolLogView, PSS_OutputView)
    //{{AFX_MSG_MAP(ZVOutputSymbolLogView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputSymbolLogView::ZVOutputSymbolLogView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}

ZVOutputSymbolLogView::~ZVOutputSymbolLogView()
{}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSymbolLogView message handlers

// Call back function base on list events
void ZVOutputSymbolLogView::OnSelChanged()
{
    // Do nothing
}

void ZVOutputSymbolLogView::OnDoubleClick()
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
