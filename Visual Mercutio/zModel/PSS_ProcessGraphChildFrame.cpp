/****************************************************************************
 * ==> PSS_ProcessGraphChildFrame ------------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process child frame                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ProcessGraphChildFrame.h"

// processsoft
#include "zResMgr\PSS_ResourceManager.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "ProcGraphModelView.h"
#include "ZDProcessGraphPage.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
CDocument* PSS_ProcessGraphChildFrame::m_pLastActivatedDocument = NULL;
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProcessGraphChildFrame, SECMDIChildWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessGraphChildFrame, SECMDIChildWnd)
    //{{AFX_MSG_MAP(PSS_ProcessGraphChildFrame)
    ON_WM_MDIACTIVATE()
    ON_WM_MOUSEACTIVATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessGraphChildFrame
//---------------------------------------------------------------------------
PSS_ProcessGraphChildFrame::PSS_ProcessGraphChildFrame() :
    SECMDIChildWnd()
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphChildFrame::~PSS_ProcessGraphChildFrame()
{}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphChildFrame::AssertValid() const
    {
        SECMDIChildWnd::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphChildFrame::Dump(CDumpContext& dc) const
    {
        SECMDIChildWnd::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    // todo -cFeature -oJean: Modify the Window class or styles here by modifying the CREATESTRUCT cs
    return SECMDIChildWnd::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
    SECMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

    if (m_pLastActivatedDocument && m_pLastActivatedDocument != GetActiveDocument())
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTHASBEENSELECTED, 0, LPARAM(GetActiveDocument()));

    m_pLastActivatedDocument = GetActiveDocument();

    PSS_ProcessGraphModelDoc* pLastActivatedModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(m_pLastActivatedDocument);

    if (pLastActivatedModelDoc)
    {
        PSS_ProcessGraphModelMdl* pModel = pLastActivatedModelDoc->GetModel();

        // switch the context
        if (pModel)
            PSS_FloatingToolBar::SwitchContext(pModel->GetNotation());

        // request the resource language change
        PSS_ResourceManager::ChangeLanguage(pLastActivatedModelDoc->GetLanguage());

        // notify all document observers about the frame activation
        PSS_DocumentObserverMsg msg(UM_FRAMEHASBEENACTIVATED, m_pLastActivatedDocument, GetActiveView());
        pLastActivatedModelDoc->NotifyAllObservers(&msg);
    }
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphChildFrame::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    const int result = SECMDIChildWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);

    PSS_ProcessGraphModelDoc* pLastActivatedModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(m_pLastActivatedDocument);

    if (pLastActivatedModelDoc)
    {
        PSS_ProcessGraphModelMdl* pModel = pLastActivatedModelDoc->GetModel();

        // switch the context
        if (pModel)
            PSS_FloatingToolBar::SwitchContext(pModel->GetNotation());

        // request the resource language change
        PSS_ResourceManager::ChangeLanguage(pLastActivatedModelDoc->GetLanguage());

        // notify all document observers about the frame activation
        PSS_DocumentObserverMsg msg(UM_FRAMEHASBEENACTIVATED, m_pLastActivatedDocument, GetActiveView());
        pLastActivatedModelDoc->NotifyAllObservers(&msg);
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphChildFrame::OnUpdateFrameTitle(BOOL addToTitle)
{
    SECMDIChildWnd::OnUpdateFrameTitle(addToTitle);

    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetActiveDocument());

    if (!pModelDoc)
        return;

    PSS_ProcessGraphModelView* pModelView = dynamic_cast<PSS_ProcessGraphModelView*>(GetActiveView());

    if (!pModelView)
        return;

    // is document closing?
    if (!pModelDoc->IsClosing())
    {
        PSS_ProcessGraphModelMdl* pModel = pModelView->GetModel();

        if (!pModel)
            return;

        if (!pModel->GetAbsolutePath().IsEmpty())
        {
            CString wndText = pModel->GetAbsolutePath();

            // if has a page set, add the page name
            if (pModel->HasPageSet())
            {
                ZDProcessGraphPage* pPage = pModel->FindModelPage(pModel);

                if (pPage)
                    wndText += _T("[") + pPage->GetPageName() + _T("]");
            }

            SetWindowText(wndText);
        }
    }
}
//---------------------------------------------------------------------------
