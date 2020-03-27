/****************************************************************************
 * ==> PSS_GridChildFrame --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid child frame                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridChildFrame.h"

// processsoft
#include "PSS_GridDocument.h"
#include "PSS_GridView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_GridChildFrame, CGXWChildFrame)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridChildFrame, CGXWChildFrame)
    //{{AFX_MSG_MAP(PSS_GridChildFrame)
    ON_UPDATE_COMMAND_UI(ID_INSERTSKSHEET, CGXWChildFrame::CanInsertWorkSheet)
    ON_UPDATE_COMMAND_UI(ID_DELETEWKSHEET, CGXWChildFrame::CanDeleteWorkSheet)
    ON_COMMAND(ID_INSERTSKSHEET, OnInsertsksheet)
    ON_COMMAND(ID_DELETEWKSHEET, OnDeletewksheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridChildFrame
//---------------------------------------------------------------------------
PSS_GridChildFrame::PSS_GridChildFrame() :
    CGXWChildFrame()
{
    SetDocRuntimeClass (RUNTIME_CLASS(PSS_GridDocument));
    SetViewRuntimeClass(RUNTIME_CLASS(PSS_GridView));

    // initialize the number of tabs to 1, and not 3, as the default
    SetNumberOfTabs(1);
}
//---------------------------------------------------------------------------
PSS_GridChildFrame::~PSS_GridChildFrame()
{}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridChildFrame::AssertValid() const
    {
        CGXWChildFrame::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridChildFrame::Dump(CDumpContext& dc) const
    {
        CGXWChildFrame::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_GridChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    return CGXWChildFrame::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
void PSS_GridChildFrame::OnInsertsksheet()
{
    InsertWorkSheetHandler();
}
//---------------------------------------------------------------------------
void PSS_GridChildFrame::OnDeletewksheet()
{
    DeleteWorkSheetHandler();
}
//---------------------------------------------------------------------------
