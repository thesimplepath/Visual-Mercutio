// ZVOutputSearchView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVOutputSearchView.h"

#include "PSS_SymbolLogObserverMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSearchView

IMPLEMENT_DYNAMIC(ZVOutputSearchView, PSS_OutputView)

BEGIN_MESSAGE_MAP(ZVOutputSearchView, PSS_OutputView)
    //{{AFX_MSG_MAP(ZVOutputSearchView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVOutputSearchView::ZVOutputSearchView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}

ZVOutputSearchView::~ZVOutputSearchView()
{}

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

    if (GetCurrentItem(s) != -1)
    {
        PSS_GenericSymbolErrorLine ErrorLine;
        (PSS_ErrorLine&)ErrorLine = s;
        PSS_SymbolLogObserverMsg msg(ErrorLine);

        NotifyAllObservers(&msg);
    }
}
