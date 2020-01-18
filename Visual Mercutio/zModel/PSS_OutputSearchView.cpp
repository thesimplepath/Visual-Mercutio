/****************************************************************************
 * ==> PSS_OutputSearchView ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output search view                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputSearchView.h"

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
IMPLEMENT_DYNAMIC(PSS_OutputSearchView, PSS_OutputView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputSearchView, PSS_OutputView)
    //{{AFX_MSG_MAP(PSS_OutputSearchView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputSearchView
//---------------------------------------------------------------------------
PSS_OutputSearchView::PSS_OutputSearchView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}
//---------------------------------------------------------------------------
PSS_OutputSearchView::~PSS_OutputSearchView()
{}
//---------------------------------------------------------------------------
void PSS_OutputSearchView::OnSelChanged()
{}
//---------------------------------------------------------------------------
void PSS_OutputSearchView::OnDoubleClick()
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
