/****************************************************************************
 * ==> PSS_DropScrollView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a drop scroll view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DropScrollView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_DropScrollView, PSS_BasicScrollView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DropScrollView, PSS_BasicScrollView)
    //{{AFX_MSG_MAP(PSS_DropScrollView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DropScrollView
//---------------------------------------------------------------------------
PSS_DropScrollView::PSS_DropScrollView() :
    PSS_BasicScrollView()
{}
//---------------------------------------------------------------------------
PSS_DropScrollView::~PSS_DropScrollView()
{}
//---------------------------------------------------------------------------
void PSS_DropScrollView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DropScrollView::AssertValid() const
    {
        PSS_BasicScrollView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DropScrollView::Dump(CDumpContext& dc) const
    {
        PSS_BasicScrollView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
