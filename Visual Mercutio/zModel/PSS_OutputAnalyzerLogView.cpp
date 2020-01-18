/****************************************************************************
 * ==> PSS_OutputAnalyzerLogView -------------------------------------------*
 ****************************************************************************
 * Description : Provides an output analyser log view                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputAnalyzerLogView.h"

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
IMPLEMENT_DYNAMIC(PSS_OutputAnalyzerLogView, PSS_OutputView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputAnalyzerLogView, PSS_OutputView)
    //{{AFX_MSG_MAP(PSS_OutputAnalyzerLogView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputAnalyzerLogView
//---------------------------------------------------------------------------
PSS_OutputAnalyzerLogView::PSS_OutputAnalyzerLogView() :
    PSS_OutputView()
{
    SetSelectLast(true);
}
//---------------------------------------------------------------------------
PSS_OutputAnalyzerLogView::~PSS_OutputAnalyzerLogView()
{}
//---------------------------------------------------------------------------
void PSS_OutputAnalyzerLogView::OnSelChanged()
{}
//---------------------------------------------------------------------------
void PSS_OutputAnalyzerLogView::OnDoubleClick()
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
