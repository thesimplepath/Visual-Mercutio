/****************************************************************************
 * ==> PSS_PropertiesWorkspace ---------------------------------------------*
 ****************************************************************************
 * Description : Provides the properties workspace                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertiesWorkspace.h"

// processsoft
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_SpanView.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zProperty\PSS_PropertyObserverMsg.h"

// resources
#include "resource.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global messages
//---------------------------------------------------------------------------
#define IDC_PROPERTIESVIEW            102
#define IDC_PANVIEW                   103
#define IDC_INPUTATTRIBUTEVIEW        104
#define IDC_DISTRIBUTIONATTRIBUTEVIEW 105
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertiesWorkspace, SECControlBar)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertiesWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(PSS_PropertiesWorkspace)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_PROPERTIESVIEW, OnListGetDispInfo)
    ON_MESSAGE(UM_INITIALIZEDOCUMENTMODEL, OnInitializeModelDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertiesWorkspace
//---------------------------------------------------------------------------
PSS_PropertiesWorkspace::PSS_PropertiesWorkspace() :
    SECControlBar(),
    PSS_Subject(),
    PSS_Observer()
{}
//---------------------------------------------------------------------------
PSS_PropertiesWorkspace::~PSS_PropertiesWorkspace()
{}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::Initialize()
{
    // set the first active view
    m_WndTab.ActivateTab(0);
    m_WndTab.ScrollToTab(0);

    PSS_PropertiesView* pPropertiesView = GetPropertyView();

    if (pPropertiesView)
        pPropertiesView->AttachObserver(this);

    PSS_InputAttributesView* pInputAttrView = GetInputAttributeView();

    if (pInputAttrView)
        pInputAttrView->AttachObserver(this);

    PSS_DistributionAttributesView* pDistribAttrView = GetDistributionAttributeView();

    if (pDistribAttrView)
        pDistribAttrView->AttachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::Release()
{}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // call the OnUpdate method for all components
    GetPropertyView()->OnUpdate(pSubject, pMsg);
    GetInputAttributeView()->OnUpdate(pSubject, pMsg);
    GetDistributionAttributeView()->OnUpdate(pSubject, pMsg);

    // don't add the pan view for the SR1
    /*
    PSS_DocumentObserverMsg* pDocMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

    // check about frame activated, set the right view to the pan window
    if (pDocMsg)
        switch (pDocMsg->GetMessageID())
        {
            case UM_FRAMEHASBEENACTIVATED:
            {
                PSS_SpanView* pSpanView = dynamic_cast<PSS_SpanView*>(pDocMsg->GetView());

                if (pSpanView)
                {
                    m_PanView.AssignPanView(pSpanView);
                    break;
                }
            }
        }
    */

    bool       isMessenger = false;
    CFrameWnd* pFrameWnd   = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (pFrameWnd)
    {
        CFrameWnd* pActiveFrame = pFrameWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pProcGraphMdl = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pProcGraphMdl && pProcGraphMdl->GetUseWorkflow())
                isMessenger = true;
        }
    }

    // should only appear if messenger
    if (isMessenger)
    {
        m_WndTab.EnableTab(1, TRUE);
        m_WndTab.EnableTab(2, TRUE);
    }
    else
    {
        m_WndTab.ActivateTab(0);
        m_WndTab.EnableTab(1, FALSE);
        m_WndTab.EnableTab(2, FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::OnExtendContextMenu(CMenu* pMenu)
{}
//---------------------------------------------------------------------------
int PSS_PropertiesWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rc;
    GetClientRect(&rc);

    // NOTE OT 5.0 and earlier would stretch a 32x32 icon resource down to
    // 16x16. 5.1 and above defaults to native 16x16 sized icons, when available
    // (avoids ugly stretching). Since no 16x16 icons are available, 32x32 resources
    // may be specified in the AddTab calls below (will still stretch down,
    // but at least the images of interest will be loaded)
    const BOOL result = m_WndTab.Create(this);

    // symbol Properties
    m_PropertyView.Create(NULL,
                          NULL,
                          WS_CHILD | WS_VISIBLE,
                          CRect(0, 0, 0, 0),
                          &m_WndTab,
                          IDC_PROPERTIESVIEW);

    CString str;
    str.LoadString(IDS_PROPERTYWKS_PROP);
    m_WndTab.AddTab(&m_PropertyView, str);
    m_WndTab.SetTabIcon(0, IDI_IL_PROPERTIESVIEW);

    // input attributes view
    m_InputAttributeView.Create(NULL,
                                NULL,
                                WS_CHILD | WS_VISIBLE,
                                CRect(0, 0, 0, 0),
                                &m_WndTab,
                                IDC_INPUTATTRIBUTEVIEW);

    str.LoadString(IDS_INPUTATTRIBUTEWKS_PROP);
    m_WndTab.AddTab(&m_InputAttributeView, str);
    m_WndTab.SetTabIcon(1, IDI_IL_INPUTATTRIBUTEVIEW);

    // distribution attributes view
    m_DistributionAttributeView.Create(NULL,
                                       NULL,
                                       WS_CHILD | WS_VISIBLE,
                                       CRect(0, 0, 0, 0),
                                       &m_WndTab,
                                       IDC_DISTRIBUTIONATTRIBUTEVIEW);

    str.LoadString(IDS_DISTRIBUTIONATTRIBUTEWKS_PROP);
    m_WndTab.AddTab(&m_DistributionAttributeView, str);
    m_WndTab.SetTabIcon(2, IDI_IL_DISTRIBATTRIBUTEVIEW);

    m_PanView.Create(rc, &m_WndTab, IDC_PANVIEW);

    // don't add the pan view for the SR1
    /*
    str.LoadString(IDS_PROPERTYWKS_PANVIEW);
    m_WndTab.AddTab(&m_PanView, str);
    m_WndTab.SetTabIcon(3, IDI_IL_PANVIEW);
    */

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::OnSize(UINT nType, int cx, int cy)
{
    CRect rectInside;
    GetInsideRect(rectInside);

    ::SetWindowPos(m_WndTab.m_hWnd,
                   NULL,
                   rectInside.left,
                   rectInside.top,
                   rectInside.Width(),
                   rectInside.Height(),
                   SWP_NOZORDER | SWP_NOACTIVATE);

    SECControlBar::OnSize(nType, cx, cy);
}
//---------------------------------------------------------------------------
void PSS_PropertiesWorkspace::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_PropertiesWorkspace::OnInitializeModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 1;

    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocMsg->GetDoc());

        if (pDoc)
        {
            // notify all document observers about the frame activation
            PSS_DocumentObserverMsg msg(UM_FRAMEHASBEENACTIVATED, pDoc, NULL);
            pDoc->NotifyAllObservers(&msg);
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
