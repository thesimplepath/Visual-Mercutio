/****************************************************************************
 * ==> PSS_GridReportChildFrame --------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report child frame                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridReportChildFrame.h"

// processsoft
#include "PSS_GridReportDocument.h"
#include "PSS_GridReportView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_GridReportChildFrame, PSS_GridChildFrame)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridReportChildFrame, PSS_GridChildFrame)
    //{{AFX_MSG_MAP(PSS_GridReportChildFrame)
    ON_MESSAGE(WM_GX_INITNEW, OnInitNew)
    ON_MESSAGE(WM_GX_INITFILE, OnInitFromFile)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridReportChildFrame
//---------------------------------------------------------------------------
PSS_GridReportChildFrame::PSS_GridReportChildFrame() :
    PSS_GridChildFrame()
{
    SetDocRuntimeClass (RUNTIME_CLASS(PSS_GridReportDocument));
    SetViewRuntimeClass(RUNTIME_CLASS(PSS_GridReportView));
}
//---------------------------------------------------------------------------
PSS_GridReportChildFrame::~PSS_GridReportChildFrame()
{
    CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());

    // need to remove the tab manager when destroying the child frame, because sometimes
    // it remains for no reason and causes the application to crash
    if (pAppAdapt)
    {
        CWnd* pWnd = CGXFrameAdapter::GetWindow();

        if (pWnd)
            pAppAdapt->RemoveTabManager(pWnd->GetRuntimeClass(), m_pContext ? m_pContext->m_pCurrentDoc : NULL);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportChildFrame::AssertValid() const
    {
        PSS_GridChildFrame::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportChildFrame::Dump(CDumpContext& dc) const
    {
        PSS_GridChildFrame::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
LRESULT PSS_GridReportChildFrame::OnInitNew(WPARAM wParam, LPARAM lParam)
{
    // a crash may occurs in this function if the pointer m_hWnd from m_pActivePane is wrong
    const LRESULT lResult = CGXWChildFrame::OnInitNew(wParam, lParam);

    // need a valid create context
    if (!m_pContext)
        return lResult;

    CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());

    if (!pAppAdapt)
        return lResult;

    CWnd* pWnd = CGXFrameAdapter::GetWindow();

    if (!pWnd)
        return lResult;

    // the call to GetTabManager fails to create a new tab manager depending on an information in
    // m_pContext->m_pCurrentDoc. Stingray calls a routine where GetMap()->Lookup(dw, pObject) should
    // return FALSE (that is, the object at memory dw should not exist). When the object exist, the
    // crash occurs
    CGXTabWndMgr*           pMgr    = pAppAdapt->GetTabManager(pWnd->GetRuntimeClass(), m_pContext->m_pCurrentDoc);
    PSS_GridReportDocument* pCurDoc = dynamic_cast<PSS_GridReportDocument*>(m_pContext->m_pCurrentDoc);

    // call the post initialization callback
    if (pCurDoc)
        pCurDoc->OnPostInitialized(pMgr, pAppAdapt, true);

    return lResult;
}
//---------------------------------------------------------------------------
LRESULT PSS_GridReportChildFrame::OnInitFromFile(WPARAM wParam, LPARAM lParam)
{
    const LRESULT lResult = CGXWChildFrame::OnInitFromFile(wParam, lParam);

    // need a valid create context
    if (!m_pContext)
        return lResult;

    CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());

    if (!pAppAdapt)
        return lResult;

    CWnd* pWnd = CGXFrameAdapter::GetWindow();

    if (!pWnd)
        return lResult;

    CGXTabWndMgr*           pMgr    = pAppAdapt->GetTabManager(pWnd->GetRuntimeClass(), m_pContext->m_pCurrentDoc);
    PSS_GridReportDocument* pCurDoc = dynamic_cast<PSS_GridReportDocument*>(m_pContext->m_pCurrentDoc);

    // call the post initialization callback
    if (pCurDoc)
        pCurDoc->OnPostInitialized(pMgr, pAppAdapt, false);

    return lResult;
}
//---------------------------------------------------------------------------
void PSS_GridReportChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
    PSS_GridChildFrame::OnUpdateFrameTitle(bAddToTitle);

    PSS_GridReportDocument* pDoc = dynamic_cast<PSS_GridReportDocument*>(GetActiveDocument());

    // set the title
    if (pDoc)
        SetWindowText(pDoc->GetReportTitle());
}
//---------------------------------------------------------------------------
