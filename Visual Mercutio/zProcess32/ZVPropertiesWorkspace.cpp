// ZVPropertiesWorkspace.cpp: implementation of the ZVPropertiesWorkspace class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVPropertiesWorkspace.h"

#include "zProperty\PSS_PropertyObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_DocObserverMsg.h"

#include "zBaseLib\PSS_SpanView.h"

#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 3 juilet 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define IDC_PROPERTIESVIEW                    102
#define IDC_PANVIEW                            103
#define IDC_INPUTATTRIBUTEVIEW                104
#define IDC_DISTRIBUTIONATTRIBUTEVIEW        105

IMPLEMENT_DYNAMIC(ZVPropertiesWorkspace, SECControlBar)

BEGIN_MESSAGE_MAP(ZVPropertiesWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(ZVPropertiesWorkspace)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_PROPERTIESVIEW, OnListGetDispInfo)
    ON_MESSAGE(UM_INITIALIZEDOCUMENTMODEL, OnInitializeModelDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVPropertiesWorkspace::ZVPropertiesWorkspace()
    : SECControlBar()
{}

ZVPropertiesWorkspace::~ZVPropertiesWorkspace()
{}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVPropertiesWorkspace::Release()
{}

int ZVPropertiesWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    CRect rc;
    GetClientRect(&rc);

    BOOL rtn_val;
    rtn_val = m_wndTab.Create(this);

    // Note: OT 5.0 and earlier would stretch a 32x32 icon resource down to
    // 16x16. 5.1 and above defaults to native 16x16 sized icons, when available
    // (avoids ugly stretching). Since we don't have 16x16 icons available, we
    // can specify the 32x32 resources in the AddTab calls below (will still
    // stretch down, but at least we are loading the images of interest)

    // Symbol Properties
    m_PropertyView.Create(NULL,
                          NULL,
                          WS_CHILD | WS_VISIBLE,
                          CRect(0, 0, 0, 0),
                          &m_wndTab,
                          IDC_PROPERTIESVIEW);

    CString s;
    s.LoadString(IDS_PROPERTYWKS_PROP);
    m_wndTab.AddTab(&m_PropertyView, s);
    m_wndTab.SetTabIcon(0, IDI_IL_PROPERTIESVIEW);

    // Input attributes    view
    m_InputAttributeView.Create(NULL,
                                NULL,
                                WS_CHILD | WS_VISIBLE,
                                CRect(0, 0, 0, 0),
                                &m_wndTab,
                                IDC_INPUTATTRIBUTEVIEW);

    s.LoadString(IDS_INPUTATTRIBUTEWKS_PROP);
    m_wndTab.AddTab(&m_InputAttributeView, s);
    m_wndTab.SetTabIcon(1, IDI_IL_INPUTATTRIBUTEVIEW);

    // Distribution attributes view
    m_DistributionAttributeView.Create(NULL,
                                       NULL,
                                       WS_CHILD | WS_VISIBLE,
                                       CRect(0, 0, 0, 0),
                                       &m_wndTab,
                                       IDC_DISTRIBUTIONATTRIBUTEVIEW);

    s.LoadString(IDS_DISTRIBUTIONATTRIBUTEWKS_PROP);
    m_wndTab.AddTab(&m_DistributionAttributeView, s);
    m_wndTab.SetTabIcon(2, IDI_IL_DISTRIBATTRIBUTEVIEW);

    m_PanView.Create(rc,
                     &m_wndTab,
                     IDC_PANVIEW);

    s.LoadString(IDS_PROPERTYWKS_PANVIEW);

    /* Don't add the pan view for the SR1
    m_wndTab.AddTab(&m_PanView, s);
    m_wndTab.SetTabIcon(3, IDI_IL_PANVIEW);
    */

    return 0;
}

void ZVPropertiesWorkspace::Initialize()
{
    // Set the first active view
    m_wndTab.ActivateTab(0);
    m_wndTab.ScrollToTab(0);

    // Set observers
    if (GetPropertyView())
    {
        GetPropertyView()->AttachObserver(this);
    }

    if (GetInputAttributeView())
    {
        GetInputAttributeView()->AttachObserver(this);
    }

    if (GetDistributionAttributeView())
    {
        GetDistributionAttributeView()->AttachObserver(this);
    }
}

void ZVPropertiesWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Call the OnUpdate method for all components
    GetPropertyView()->OnUpdate(pSubject, pMsg);
    GetInputAttributeView()->OnUpdate(pSubject, pMsg);
    GetDistributionAttributeView()->OnUpdate(pSubject, pMsg);

    // Check about frame activated
    // Set the right view to the pan window
    if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg))
    {
        switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_FRAMEHASBEENACTIVATED:
            {
                if (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetView() &&
                    ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetView(), PSS_SpanView))
                {
                    /* Don't add the pan view for the SR1
                    m_PanView.AssignPanView
                        ( dynamic_cast<PSS_SpanView*>( dynamic_cast<ZBDocumentObserverMsg*>( pMsg )->GetView() ) );
                    */
                    break;
                }
            }
        }
    }

    // RS-MODIF 21.12.04 should only appear if messenger
    bool IsMessenger = false;

    PSS_ProcessGraphModelDoc* test =
        (PSS_ProcessGraphModelDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

    if (test != NULL)
    {
        if (test->GetUseWorkflow())
        {
            IsMessenger = true;
        }
    }

    if (IsMessenger)
    {
        m_wndTab.EnableTab(1, TRUE);
        m_wndTab.EnableTab(2, TRUE);
    }
    else
    {
        m_wndTab.ActivateTab(0);
        m_wndTab.EnableTab(1, FALSE);
        m_wndTab.EnableTab(2, FALSE);
    }
}

afx_msg LRESULT ZVPropertiesWorkspace::OnInitializeModelDocument(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
    {
        return 1;
    }

    PSS_ObserverMsg* pMsg = (PSS_ObserverMsg*)lParam;

    if (pMsg && ISA(pMsg, PSS_DocObserverMsg))
    {
        PSS_DocObserverMsg* pDocMsg = (PSS_DocObserverMsg*)pMsg;

        if (pDocMsg->GetDoc())
        {
            // Notify all document's observers about the frame activation
            PSS_DocumentObserverMsg Msg(UM_FRAMEHASBEENACTIVATED,
                                        pDocMsg->GetDoc(),
                                        NULL);

            ((PSS_ProcessGraphModelDoc*)pDocMsg->GetDoc())->NotifyAllObservers(&Msg);
        }
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////
// ZVPropertiesWorkspace message handlers

void ZVPropertiesWorkspace::OnSize(UINT nType, int cx, int cy)
{
    CRect rectInside;
    GetInsideRect(rectInside);

    ::SetWindowPos(m_wndTab.m_hWnd,
                   NULL,
                   rectInside.left,
                   rectInside.top,
                   rectInside.Width(),
                   rectInside.Height(),
                   SWP_NOZORDER | SWP_NOACTIVATE);

    SECControlBar::OnSize(nType, cx, cy);
}

void ZVPropertiesWorkspace::OnExtendContextMenu(CMenu* pMenu)
{}

void ZVPropertiesWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
    pTarget;            // UNUSED
    bDisableIfNoHndler;    // UNUSED
}

// List control is querying for subitem text...
void ZVPropertiesWorkspace::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;
    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}
