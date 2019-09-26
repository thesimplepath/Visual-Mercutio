/****************************************************************************
 * ==> PSS_DropView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a drop view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DropView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_DropView, PSS_BasicView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DropView, PSS_BasicView)
    //{{AFX_MSG_MAP(PSS_DropView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DropView
//---------------------------------------------------------------------------
PSS_DropView::PSS_DropView() :
    PSS_BasicView()
{}
//---------------------------------------------------------------------------
PSS_DropView::~PSS_DropView()
{}
//---------------------------------------------------------------------------
void PSS_DropView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DropView::AssertValid() const
    {
        PSS_BasicView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DropView::Dump(CDumpContext& dc) const
    {
        PSS_BasicView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
