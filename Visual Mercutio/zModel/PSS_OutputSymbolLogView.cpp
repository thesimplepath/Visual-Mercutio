/****************************************************************************
 * ==> PSS_OutputSymbolLogView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an output symbol log view                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputSymbolLogView.h"

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
IMPLEMENT_DYNAMIC(PSS_OutputSymbolLogView, PSS_OutputView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputSymbolLogView, PSS_OutputView)
    //{{AFX_MSG_MAP(PSS_OutputSymbolLogView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputSymbolLogView
//---------------------------------------------------------------------------
PSS_OutputSymbolLogView::PSS_OutputSymbolLogView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}
//---------------------------------------------------------------------------
PSS_OutputSymbolLogView::~PSS_OutputSymbolLogView()
{}
//---------------------------------------------------------------------------
void PSS_OutputSymbolLogView::OnSelChanged()
{}
//---------------------------------------------------------------------------
void PSS_OutputSymbolLogView::OnDoubleClick()
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
