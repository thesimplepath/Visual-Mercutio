/****************************************************************************
 * ==> PSS_GridReportView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridReportView.h"

// processsoft
#include "PSS_GridReportDocument.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
GXIMPLEMENT_DYNCREATE(PSS_GridReportView, ZVGridView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridReportView, ZVGridView)
    //{{AFX_MSG_MAP(PSS_GridReportView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridReportView
//---------------------------------------------------------------------------
PSS_GridReportView::PSS_GridReportView() :
    ZVGridView()
{}
//---------------------------------------------------------------------------
PSS_GridReportView::~PSS_GridReportView()
{}
//---------------------------------------------------------------------------
void PSS_GridReportView::SetupUserAttributes()
{
    // call the basic implementation
    ZVGridView::SetupUserAttributes();
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportView::AssertValid() const
    {
        ZVGridView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportView::Dump(CDumpContext& dc) const
    {
        ZVGridView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_GridReportView::OnInitialUpdate()
{
    ZVGridView::OnInitialUpdate();

    EnableHints(FALSE);

    // lock any drawing
    const BOOL old = LockUpdate();

    // disable undo mechanism for the following commands
    GetParam()->EnableUndo(FALSE);

    // get the view index
    int index = -1;

    CGXTabWnd* pTabWnd = GetTabWnd();

    if (pTabWnd)
        index = pTabWnd->GetBeam().FindTab(this);

    // cast the document pointer to the rigth class type. This is required because
    // the PSS_GridReportDocument implements the PSS_GridReportGenerator interface
    PSS_GridReportDocument* pMasterDoc = dynamic_cast<PSS_GridReportDocument*>(GetMasterDocument());

    if (pMasterDoc && index != -1)
    {
        // set the tab name
        pTabWnd->SetTabName(index, pMasterDoc->GetGeneratorTabName(index));

        // requires a data refresh before filling the grid
        if (pMasterDoc->ViewRequireDataRefresh())
        {
            // call the pre-data filled callback
            pMasterDoc->OnPreDataFilled(index);

            // asks the master document to fill the grid
            if (!pMasterDoc->FillGrid(*this, index))
            {
                // todo -cFeature -oJean: log error
            }

            // call the post-data filled callback
            pMasterDoc->OnPostDataFilled(index);
        }
    }

    // create the group control if required
    PSS_GridDocument* pDoc = GetDocument();

    if (pDoc)
        pDoc->InitializeGroupControls(this);

    // re-enable undo mechanism
    GetParam()->EnableUndo(TRUE);

    // unlock drawing
    LockUpdate(old);

    // certify that everything is redrawn
    Invalidate();

    // enable Objective Grid internal update-hint mechanism. This line should be put
    // as the last command in the OnInitialUpdate() function, because as long as the
    // EnableHints() function isn't called, the modified flag of the document will not
    // be changed
    EnableHints();
}
//---------------------------------------------------------------------------
void PSS_GridReportView::OnDraw(CDC* pDC)
{
    ASSERT_VALID(GetDocument());
    ZVGridView::OnDraw(pDC);
}
//---------------------------------------------------------------------------
