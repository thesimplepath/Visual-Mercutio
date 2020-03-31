// ZVOutputWorkspace.cpp: implementation of the ZVOutputWorkspace class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVOutputWorkspace.h"

#include "Resource.h"

#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 13 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define IDC_OUTPUTSYMBOLVIEW                101
#define IDC_OUTPUTANALYZERVIEW                102
#define IDC_OUTPUTWORKFLOWVIEW                103
#define IDC_OUTPUTSEARCHVIEW                104

IMPLEMENT_DYNAMIC(ZVOutputWorkspace, SECControlBar)

BEGIN_MESSAGE_MAP(ZVOutputWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(ZVOutputWorkspace)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_OUTPUTSYMBOLVIEW, OnListGetDispInfo)
    ON_COMMAND(ID_CLEAR_WINDOW, OnClearWindow)
    ON_COMMAND(ID_SETDEBUGMODE_WINDOW, OnSetDebugMode)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVOutputWorkspace::ZVOutputWorkspace()
    : SECControlBar()
{}

ZVOutputWorkspace::~ZVOutputWorkspace()
{}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre un nettoyage de la mémoire.
void ZVOutputWorkspace::Release()
{
    m_OutputView.Release();
    m_OutputSearchView.Release();
    m_OutputAnalyzerView.Release();
    m_OutputWkfView.Release();
}

void ZVOutputWorkspace::LogClearOutput()
{
    PSS_OutputSymbolLogView* pView = GetLogView();

    if (pView)
    {
        pView->ClearLog();
    }
}

void ZVOutputWorkspace::LogAddLine(const CString Line)
{
    PSS_OutputSymbolLogView* pView = GetLogView();

    if (pView)
    {
        pView->AddLine(Line);
    }
}

// Create the view and associate it to the right tab.
int ZVOutputWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    BOOL rtn_val;
    rtn_val = m_wndTab.Create(this);

    // The general log window
    m_OutputView.Create(NULL,
                        NULL,
                        WS_CHILD | WS_VISIBLE,
                        CRect(0, 0, 0, 0),
                        &m_wndTab,
                        IDC_OUTPUTSYMBOLVIEW);

    CString s;
    s.LoadString(IDS_OUTPUTWKS_MODEL);
    m_wndTab.AddTab(&m_OutputView, s);

    // The search log window
    m_OutputSearchView.Create(NULL,
                              NULL,
                              WS_CHILD | WS_VISIBLE,
                              CRect(0, 0, 0, 0),
                              &m_wndTab,
                              IDC_OUTPUTSEARCHVIEW);

    s.LoadString(IDS_OUTPUTWKS_SEARCH);
    m_wndTab.AddTab(&m_OutputSearchView, s);

    // The analyzer log window
    m_OutputAnalyzerView.Create(NULL,
                                NULL,
                                WS_CHILD | WS_VISIBLE,
                                CRect(0, 0, 0, 0),
                                &m_wndTab,
                                IDC_OUTPUTANALYZERVIEW);

    s.LoadString(IDS_OUTPUTWKS_ANALYZER);
    m_wndTab.AddTab(&m_OutputAnalyzerView, s);

    // The workflow log window
    m_OutputWkfView.Create(NULL,
                           NULL,
                           WS_CHILD | WS_VISIBLE,
                           CRect(0, 0, 0, 0),
                           &m_wndTab,
                           IDC_OUTPUTWORKFLOWVIEW);

    s.LoadString(IDS_OUTPUTWKS_WORKFLOW);
    m_wndTab.AddTab(&m_OutputWkfView, s);

    return 0;
}

void ZVOutputWorkspace::Initialize()
{
    // Set the first active view
    m_wndTab.ActivateTab(def_SymbolLogTabIndex);
    m_wndTab.ScrollToTab(def_SymbolLogTabIndex);

    // Set observers
    if (GetLogView())
    {
        GetLogView()->AttachObserver(this);

        // Initialize the flag for debug mode
        GetLogView()->SetDebugMode(false);
    }

    if (GetLogAnalyzerView())
    {
        GetLogAnalyzerView()->AttachObserver(this);

        // Initialize the flag for debug mode
        GetLogAnalyzerView()->SetDebugMode(false);
    }

    if (GetLogWorkflowView())
    {
        GetLogWorkflowView()->AttachObserver(this);

        // Initialize the flag for debug mode
        GetLogWorkflowView()->SetDebugMode(false);
    }

    if (GetLogSearchView())
    {
        GetLogSearchView()->AttachObserver(this);

        // Initialize the flag for debug mode
        GetLogSearchView()->SetDebugMode(false);
    }
}

void ZVOutputWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Check about document close
    // Detach observer
    if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg) &&
        ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), PSS_ProcessGraphModelDoc))
    {
        switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_REFRESHDOCUMENT:
            case UM_OPENDOCUMENT:
            {
                break;
            }

            case UM_CLOSEDOCUMENT:
            {
                PSS_ProcessGraphModelDoc* pDoc =
                    dynamic_cast<PSS_ProcessGraphModelDoc*>(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument());

                DetachObserver(pDoc);
                break;
            }
        }
    }
    else if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
    {
        switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_ACTIVATE_LOGSYMBOL_TAB:
            {
                ActivateSymbolLogTab();
                break;
            }

            case UM_ACTIVATE_LOGANALYZER_TAB:
            {
                ActivateAnalyzerLogTab();
                break;
            }

            case UM_ACTIVATE_LOGWORKFLOW_TAB:
            {
                ActivateAnalyzerLogTab();
                break;
            }

            case UM_ACTIVATE_LOGSEARCH_TAB:
            {
                ActivateSearchLogTab();
                break;
            }

            default:
            {
                break;
            }
        }
    }

    // RS-MODIF 21.12.04 should only appear if messenger
    bool isMessenger = false;
    bool isSesterces = false;

    CFrameWnd* pFrameWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (pFrameWnd)
    {
        CFrameWnd* pActiveFrame = pFrameWnd->GetActiveFrame();

        if (pActiveFrame)
        {
            PSS_ProcessGraphModelDoc* pProcGraphMdl = dynamic_cast<PSS_ProcessGraphModelDoc*>(pActiveFrame->GetActiveDocument());

            if (pProcGraphMdl)
            {
                if (pProcGraphMdl->GetUseWorkflow())
                    isMessenger = true;

                if (pProcGraphMdl->GetIntegrateCostSimulation())
                    isSesterces = true;
            }
        }
    }

    if (isMessenger)
    {
        m_wndTab.EnableTab(3, TRUE);
    }
    else
    {
        m_wndTab.ActivateTab(0);
        m_wndTab.EnableTab(3, FALSE);
    }

    if (isSesterces)
    {
        m_wndTab.EnableTab(2, TRUE);
    }
    else
    {
        m_wndTab.ActivateTab(0);
        m_wndTab.EnableTab(2, FALSE);
    }

    // Forward message
    NotifyAllObservers(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVOutputWorkspace message handlers

void ZVOutputWorkspace::OnSize(UINT nType, int cx, int cy)
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

void ZVOutputWorkspace::OnExtendContextMenu(CMenu* pMenu)
{
    CString strMenu;
    pMenu->AppendMenu(MF_SEPARATOR);
    VERIFY(strMenu.LoadString(ID_CLEAR_WINDOW));

    pMenu->AppendMenu(MF_STRING, ID_CLEAR_WINDOW, strMenu);
    VERIFY(strMenu.LoadString(ID_SETDEBUGMODE_WINDOW));

    // Sets the check or unchecked flag for debug mode
    UINT nFlags = MF_STRING;

    CWnd* pWnd;

    if (m_wndTab.GetActiveTab(pWnd))
    {
        if (pWnd == GetLogView())
        {
            nFlags |= ((GetLogView()->IsInDebugMode()) ? MF_CHECKED : MF_UNCHECKED);
        }
        else if (pWnd == GetLogAnalyzerView())
        {
            nFlags |= ((GetLogAnalyzerView()->IsInDebugMode()) ? MF_CHECKED : MF_UNCHECKED);
        }
        else if (pWnd == GetLogWorkflowView())
        {
            nFlags |= ((GetLogWorkflowView()->IsInDebugMode()) ? MF_CHECKED : MF_UNCHECKED);
        }
        else if (pWnd == GetLogSearchView())
        {
            nFlags |= ((GetLogSearchView()->IsInDebugMode()) ? MF_CHECKED : MF_UNCHECKED);
        }
    }
    else
    {
        nFlags |= MF_DISABLED;
    }

    pMenu->AppendMenu(nFlags, ID_SETDEBUGMODE_WINDOW, strMenu);
}

// List control is querying for subitem text...
void ZVOutputWorkspace::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* lvdi;

    lvdi = (LV_DISPINFO*)pNMHDR;

    *pResult = 0;
}

void ZVOutputWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{}

void ZVOutputWorkspace::OnClearWindow()
{
    CWnd* pWnd;

    if (m_wndTab.GetActiveTab(pWnd))
    {
        if (pWnd == GetLogView())
        {
            GetLogView()->ClearLog();
        }
        else if (pWnd == GetLogAnalyzerView())
        {
            GetLogAnalyzerView()->ClearLog();
        }
        else if (pWnd == GetLogWorkflowView())
        {
            GetLogWorkflowView()->ClearLog();
        }
        else if (pWnd == GetLogSearchView())
        {
            GetLogSearchView()->ClearLog();
        }
    }
}

void ZVOutputWorkspace::OnSetDebugMode()
{
    CWnd* pWnd;

    if (m_wndTab.GetActiveTab(pWnd))
    {
        if (pWnd == GetLogView())
        {
            GetLogView()->SetDebugMode(!GetLogView()->IsInDebugMode());
        }
        else if (pWnd == GetLogAnalyzerView())
        {
            GetLogAnalyzerView()->SetDebugMode(!GetLogAnalyzerView()->IsInDebugMode());
        }
        else if (pWnd == GetLogWorkflowView())
        {
            GetLogWorkflowView()->SetDebugMode(!GetLogWorkflowView()->IsInDebugMode());
        }
        else if (pWnd == GetLogSearchView())
        {
            GetLogSearchView()->SetDebugMode(!GetLogSearchView()->IsInDebugMode());
        }
    }
}
