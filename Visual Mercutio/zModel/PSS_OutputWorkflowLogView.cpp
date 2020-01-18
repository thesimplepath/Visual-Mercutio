/****************************************************************************
 * ==> PSS_OutputWorkflowLogView -------------------------------------------*
 ****************************************************************************
 * Description : Provides an output workflow log view                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputWorkflowLogView.h"

// processsoft
#include "PSS_SymbolLogObserverMsg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_OutputWorkflowLogView, PSS_OutputView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputWorkflowLogView, PSS_OutputView)
    //{{AFX_MSG_MAP(PSS_OutputWorkflowLogView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputWorkflowLogView
//---------------------------------------------------------------------------
PSS_OutputWorkflowLogView::PSS_OutputWorkflowLogView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}
//---------------------------------------------------------------------------
PSS_OutputWorkflowLogView::~PSS_OutputWorkflowLogView()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkflowLogView::OnSelChanged()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkflowLogView::OnDoubleClick()
{
    CString str;

    if (GetCurrentItem(str) != -1)
    {
        PSS_GenericSymbolErrorLine errorLine;
        (PSS_ErrorLine&)errorLine = str;

        PSS_SymbolLogObserverMsg msg(errorLine);
        NotifyAllObservers(&msg);
    }
}
//---------------------------------------------------------------------------
