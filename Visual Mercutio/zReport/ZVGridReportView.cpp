// ZVGridReportView.cpp : implementation of the ZVGridReportView class

#include "stdafx.h"

#include "ZDGridReportDoc.h"
#include "ZVGridReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportView

GXIMPLEMENT_DYNCREATE(ZVGridReportView, ZVGridView)

BEGIN_MESSAGE_MAP(ZVGridReportView, ZVGridView)
    //{{AFX_MSG_MAP(ZVGridReportView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportView construction/destruction

ZVGridReportView::ZVGridReportView()
{}

ZVGridReportView::~ZVGridReportView()
{}

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportView drawing

void ZVGridReportView::OnDraw(CDC* pDC)
{
    PSS_GridDocument* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    ZVGridView::OnDraw(pDC);
    // TODO: add draw code for native data here
}

void ZVGridReportView::OnInitialUpdate()
{
    ZVGridView::OnInitialUpdate();

    EnableHints(FALSE);

    // Lock any drawing
    BOOL bOld = LockUpdate();

    // disable undo mechanism for the following commands
    GetParam()->EnableUndo(FALSE);

    // Retrieve the right view index
    int Index = -1;

    // RS-MODIF 15.12.04 doc bug
    CGXTabWnd* pTabWnd = GetTabWnd();

    if (pTabWnd)
    {
        Index = pTabWnd->GetBeam().FindTab(this);
    }

    if (Index != -1)
    {
        // Sets the correct tab name
        // RS-MODIF 15.12.04 test
        pTabWnd->SetTabName(Index,
                            dynamic_cast<ZDGridReportDocument*>(GetMasterDocument())->GetGeneratorTabName(Index));
    }

    // Cast the document pointer to the rigth class type
    // This is required, because the ZDGridReportDocument implements 
    // the ZIGridReportGenerator interface
    ASSERT(ISA(GetMasterDocument(), ZDGridReportDocument));

    // Now asks the master document to fill the grid
    if (Index != -1 && dynamic_cast<ZDGridReportDocument*>(GetMasterDocument())->ViewRequireDataRefresh())
    {
        // Cast the document pointer to the rigth class type
        // This is required, because the ZDGridReportDocument implements 
        // the ZIGridReportGenerator interface
        ASSERT(ISA(GetMasterDocument(), ZDGridReportDocument));

        // Call the predata filled call-back
        dynamic_cast<ZDGridReportDocument*>(GetMasterDocument())->OnPreDataFilled(Index);

        // Now asks the master document to fill the grid
        if (!dynamic_cast<ZDGridReportDocument*>(GetMasterDocument())->FillGrid(*this, Index))
        {
            // Log error
        }

        // Call the postdata filled call-back
        dynamic_cast<ZDGridReportDocument*>(GetMasterDocument())->OnPostDataFilled(Index);
    }

    // Create group control if necessary
    PSS_GridDocument* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    pDoc->InitializeGroupControls(this);

    // Reenable undo mechanism
    GetParam()->EnableUndo(TRUE);

    // Unlock drawing
    LockUpdate(bOld);

    // Just to be sure that everything is redrawn
    Invalidate();

    // Enable Objective Grid internal update-hint mechanism
    // You should put this line as last command into OnInitialUpdate,
    // becaus as long as EnableHints is not called, the modified flag
    // of the document will not be changed.
    EnableHints();
}

void ZVGridReportView::SetupUserAttributes()
{
    // Call the basic implementation
    ZVGridView::SetupUserAttributes();
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportView diagnostics

#ifdef _DEBUG
void ZVGridReportView::AssertValid() const
{
    ZVGridView::AssertValid();
}

void ZVGridReportView::Dump(CDumpContext& dc) const
{
    ZVGridView::Dump(dc);
}
#endif
