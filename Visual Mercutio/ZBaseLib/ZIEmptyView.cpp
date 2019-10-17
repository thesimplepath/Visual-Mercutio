/****************************************************************************
 * ==> PSS_EmptyView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an empty form view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZIEmptyView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_EmptyView, CFormView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_EmptyView, CFormView)
    //{{AFX_MSG_MAP(PSS_EmptyView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EmptyView
//---------------------------------------------------------------------------
PSS_EmptyView::PSS_EmptyView() :
    CFormView(PSS_EmptyView::IDD)
{}
//---------------------------------------------------------------------------
PSS_EmptyView::~PSS_EmptyView()
{}
//---------------------------------------------------------------------------
void PSS_EmptyView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_EmptyView)
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_EmptyView::AssertValid() const
    {
        CFormView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_EmptyView::Dump(CDumpContext& dc) const
    {
        CFormView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
