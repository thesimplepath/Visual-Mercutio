/****************************************************************************
 * ==> PSS_OutputWorkspace -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output workspace                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutputWorkspace.h"

// processsoft
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

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
#define IDC_OUTPUTSYMBOLVIEW   101
#define IDC_OUTPUTANALYZERVIEW 102
#define IDC_OUTPUTWORKFLOWVIEW 103
#define IDC_OUTPUTSEARCHVIEW   104
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_OutputWorkspace, SECControlBar)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutputWorkspace, SECControlBar)
    //{{AFX_MSG_MAP(PSS_OutputWorkspace)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_OUTPUTSYMBOLVIEW, OnListGetDispInfo)
    ON_COMMAND(ID_CLEAR_WINDOW, OnClearWindow)
    ON_COMMAND(ID_SETDEBUGMODE_WINDOW, OnSetDebugMode)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutputWorkspace
//---------------------------------------------------------------------------
PSS_OutputWorkspace::PSS_OutputWorkspace() :
    SECControlBar(),
    PSS_Subject(),
    PSS_Observer()
{}
//---------------------------------------------------------------------------
PSS_OutputWorkspace::~PSS_OutputWorkspace()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::Initialize()
{
    // set the first active view
    m_WndTab.ActivateTab(g_SymbolLogTabIndex);
    m_WndTab.ScrollToTab(g_SymbolLogTabIndex);

    PSS_OutputSymbolLogView* pLogView = GetLogView();

    if (pLogView)
    {
        pLogView->AttachObserver(this);

        // initialize the flag for debug mode
        pLogView->SetDebugMode(false);
    }

    PSS_OutputSearchView* pSearchLogView = GetSearchLogView();

    if (pSearchLogView)
    {
        pSearchLogView->AttachObserver(this);

        // initialize the flag for debug mode
        pSearchLogView->SetDebugMode(false);
    }

    PSS_OutputAnalyzerLogView* pAnalyserLogView = GetAnalyzerLogView();

    if (pAnalyserLogView)
    {
        pAnalyserLogView->AttachObserver(this);

        // initialize the flag for debug mode
        pAnalyserLogView->SetDebugMode(false);
    }

    PSS_OutputWorkflowLogView* pWorkflowLogView = GetWorkflowLogView();

    if (pWorkflowLogView)
    {
        pWorkflowLogView->AttachObserver(this);

        // initialize the flag for debug mode
        pWorkflowLogView->SetDebugMode(false);
    }
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::Release()
{
    m_OutputView.Release();
    m_OutputSearchView.Release();
    m_OutputAnalyzerView.Release();
    m_OutputWkfView.Release();
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ClearLogOutput()
{
    PSS_OutputSymbolLogView* pView = GetLogView();

    if (pView)
        pView->ClearLog();
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::AddLogLine(const CString& line)
{
    PSS_OutputSymbolLogView* pView = GetLogView();

    if (pView)
        pView->AddLine(line);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_DocumentObserverMsg* pDocMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

    // check about document closing, detach observer
    if (pDocMsg)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocMsg->GetDocument());

        if (pDoc)
            switch (pDocMsg->GetMessageID())
            {
                case UM_CLOSEDOCUMENT: DetachObserver(pDoc); break;
            }
    }
    else
    {
        PSS_ToolbarObserverMsg* pToolbarMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

        if (pToolbarMsg)
        {
            switch (pToolbarMsg->GetMessageID())
            {
                case UM_ACTIVATE_LOGSYMBOL_TAB:   ActivateSymbolLogTab();   break;
                case UM_ACTIVATE_LOGANALYZER_TAB: ActivateAnalyzerLogTab(); break;
                case UM_ACTIVATE_LOGWORKFLOW_TAB: ActivateAnalyzerLogTab(); break;
                case UM_ACTIVATE_LOGSEARCH_TAB:   ActivateSearchLogTab();   break;
                default:                                                    break;
            }
        }
    }

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

    // should only appear if messenger
    if (isMessenger)
        m_WndTab.EnableTab(3, TRUE);
    else
    {
        m_WndTab.ActivateTab(0);
        m_WndTab.EnableTab(3, FALSE);
    }

    if (isSesterces)
        m_WndTab.EnableTab(2, TRUE);
    else
    {
        m_WndTab.ActivateTab(0);
        m_WndTab.EnableTab(2, FALSE);
    }

    // forward message
    NotifyAllObservers(pMsg);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnExtendContextMenu(CMenu* pMenu)
{
    pMenu->AppendMenu(MF_SEPARATOR);

    CString str;
    VERIFY(str.LoadString(ID_CLEAR_WINDOW));

    pMenu->AppendMenu(MF_STRING, ID_CLEAR_WINDOW, str);

    VERIFY(str.LoadString(ID_SETDEBUGMODE_WINDOW));

    // set the check/unchecked flag for debug mode
    UINT  flags = MF_STRING;
    CWnd* pWnd;

    if (m_WndTab.GetActiveTab(pWnd))
    {
        if (pWnd == GetLogView())
            flags |= ((GetLogView()->IsInDebugMode()) ? MF_CHECKED : MF_UNCHECKED);
        else
        if (pWnd == GetAnalyzerLogView())
            flags |= (GetAnalyzerLogView()->IsInDebugMode() ? MF_CHECKED : MF_UNCHECKED);
        else
        if (pWnd == GetWorkflowLogView())
            flags |= (GetWorkflowLogView()->IsInDebugMode() ? MF_CHECKED : MF_UNCHECKED);
        else
        if (pWnd == GetSearchLogView())
            flags |= (GetSearchLogView()->IsInDebugMode() ? MF_CHECKED : MF_UNCHECKED);
    }
    else
        flags |= MF_DISABLED;

    pMenu->AppendMenu(flags, ID_SETDEBUGMODE_WINDOW, str);
}
//---------------------------------------------------------------------------
int PSS_OutputWorkspace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    const BOOL result = m_WndTab.Create(this);

    // the general log window
    m_OutputView.Create(NULL,
                        NULL,
                        WS_CHILD | WS_VISIBLE,
                        CRect(0, 0, 0, 0),
                        &m_WndTab,
                        IDC_OUTPUTSYMBOLVIEW);

    CString str;
    str.LoadString(IDS_OUTPUTWKS_MODEL);
    m_WndTab.AddTab(&m_OutputView, str);

    // the search log window
    m_OutputSearchView.Create(NULL,
                              NULL,
                              WS_CHILD | WS_VISIBLE,
                              CRect(0, 0, 0, 0),
                              &m_WndTab,
                              IDC_OUTPUTSEARCHVIEW);

    str.LoadString(IDS_OUTPUTWKS_SEARCH);
    m_WndTab.AddTab(&m_OutputSearchView, str);

    // The analyzer log window
    m_OutputAnalyzerView.Create(NULL,
                                NULL,
                                WS_CHILD | WS_VISIBLE,
                                CRect(0, 0, 0, 0),
                                &m_WndTab,
                                IDC_OUTPUTANALYZERVIEW);

    str.LoadString(IDS_OUTPUTWKS_ANALYZER);
    m_WndTab.AddTab(&m_OutputAnalyzerView, str);

    // The workflow log window
    m_OutputWkfView.Create(NULL,
                           NULL,
                           WS_CHILD | WS_VISIBLE,
                           CRect(0, 0, 0, 0),
                           &m_WndTab,
                           IDC_OUTPUTWORKFLOWVIEW);

    str.LoadString(IDS_OUTPUTWKS_WORKFLOW);
    m_WndTab.AddTab(&m_OutputWkfView, str);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnSize(UINT nType, int cx, int cy)
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
void PSS_OutputWorkspace::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnClearWindow()
{
    CWnd* pWnd;

    if (m_WndTab.GetActiveTab(pWnd))
    {
        PSS_OutputSymbolLogView* pLogView = GetLogView();

        if (pWnd == pLogView)
            pLogView->ClearLog();

        PSS_OutputSearchView* pSearchLogView = GetSearchLogView();

        if (pWnd == pSearchLogView)
            pSearchLogView->ClearLog();

        PSS_OutputAnalyzerLogView* pAnalyserLogView = GetAnalyzerLogView();

        if (pWnd == pAnalyserLogView)
            pAnalyserLogView->ClearLog();

        PSS_OutputWorkflowLogView* pWorkflowLogView = GetWorkflowLogView();

        if (pWnd == pWorkflowLogView)
            pWorkflowLogView->ClearLog();

    }
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::OnSetDebugMode()
{
    CWnd* pWnd;

    if (m_WndTab.GetActiveTab(pWnd))
    {
        PSS_OutputSymbolLogView* pLogView = GetLogView();

        if (pWnd == pLogView)
            pLogView->SetDebugMode(!pLogView->IsInDebugMode());

        PSS_OutputSearchView* pSearchLogView = GetSearchLogView();

        if (pWnd == pSearchLogView)
            pSearchLogView->SetDebugMode(!pSearchLogView->IsInDebugMode());

        PSS_OutputAnalyzerLogView* pAnalyserLogView = GetAnalyzerLogView();

        if (pWnd == pAnalyserLogView)
            pAnalyserLogView->SetDebugMode(!pAnalyserLogView->IsInDebugMode());

        PSS_OutputWorkflowLogView* pWorkflowLogView = GetWorkflowLogView();

        if (pWnd == pWorkflowLogView)
            pWorkflowLogView->SetDebugMode(!pWorkflowLogView->IsInDebugMode());
    }
}
//---------------------------------------------------------------------------
