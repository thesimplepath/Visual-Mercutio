/****************************************************************************
 * ==> PSS_BaseMainFrame ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic main frame                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BaseMainFrame.h"

// processsoft
#include "PSS_DrawFunctions.h"
#include "PSS_VisualTool.h"
#include "PSS_BaseMDIPage.h"
#include "PSS_FloatingToolBar.h"
#include "PSS_Messages.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Def_SaveWindowStateStr _T("zForms_Save_Window_State")
//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
// Note: the toolbar buttons sends a wmSECToolBarWndNotify registered
// message for button notifications. Unfortunately, this value is a
// const int which can not be mapped properly across the Dll boundary.
// If using a static library, wmSECToolBarWndNotify can be safely used
// in the ON_REGISTERED_MESSAGE macro below, but if using OT as a DLL,
// you must issue the following call to get the appropriate value.
// Since this mechanism is safe for static libraries as well, using
// for both.
const int g_AppToolBarWndNotify = RegisterWindowMessage(_T("WM_ZFORMS_TOOLBARWNDNOTIFY"));
//---------------------------------------------------------------------------
#ifdef __CREATE_LOGO_
    //-----------------------------------------------------------------------
    // Message map
    //-----------------------------------------------------------------------
    BEGIN_MESSAGE_MAP(PSS_MainMDIClientFrame, CWnd)
        //{{AFX_MSG_MAP(PSS_MainMDIClientFrame)
        ON_WM_SIZE()
        ON_WM_ERASEBKGND()
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
    //-----------------------------------------------------------------------
    // PSS_MainMDIClientFrame
    //-----------------------------------------------------------------------
    PSS_MainMDIClientFrame::PSS_MainMDIClientFrame() :
        CWnd()
    {}
    //-----------------------------------------------------------------------
    PSS_MainMDIClientFrame::~PSS_MainMDIClientFrame()
    {}
    //-----------------------------------------------------------------------
    void PSS_MainMDIClientFrame::OnSize(UINT nType, int cx, int cy)
    {
        CWnd::OnSize(nType, cx, cy);

        CRect rect;
        GetClientRect(&rect);
        InvalidateRect(&rect);
    }
    //-----------------------------------------------------------------------
    BOOL PSS_MainMDIClientFrame::OnEraseBkgnd(CDC* pDC)
    {
        ASSERT_VALID(pDC);

        // fill background with APPWORKSPACE
        CBrush backBrush(defCOLOR_LTGRAY);
        CBrush* pOldBrush = pDC->SelectObject(&backBrush);

        // Erase the area needed
        CRect rect;
        pDC->GetClipBox(&rect);

        pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
        pDC->SelectObject(pOldBrush);

        ShowLogo(pDC);
        return(TRUE);
    }
    //-----------------------------------------------------------------------
    WNDPROC* PSS_MainMDIClientFrame::GetSuperWndProcAddr()
    {
        static WNDPROC pOldProc;
        return(&pOldProc);
    }
    //-----------------------------------------------------------------------
    void PSS_MainMDIClientFrame::ShowLogo(CDC *pDC)
    {
        CRect  rect;
        GetClientRect(&rect);

        CPoint pt;

        // show the logo
        GetSizeOfBitmapFile(MAKEINTRESOURCE(IDB_MDI), AfxGetInstanceHandle(), &pt);

        // calculate the middle of the area to display the bitmap
        DisplayBitmapFile(MAKEINTRESOURCE(IDB_MDI),
                          pDC->m_hDC,
                          AfxGetInstanceHandle(),
                          (rect.right  - rect.left) / 2 - (pt.x / 2),
                          (rect.bottom - rect.top)  / 2 - (pt.y / 2));
    }
    //-----------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_BaseMainFrame, SECMDIFrameWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BaseMainFrame, SECMDIFrameWnd)
    //{{AFX_MSG_MAP(PSS_BaseMainFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_INITMENUPOPUP()
    ON_COMMAND(ID_VIEW_POINTER, OnViewPointer)
    ON_UPDATE_COMMAND_UI(ID_VIEW_POINTER, OnUpdateViewPointer)
    ON_MESSAGE(FSM_SETMODE, OnFSModeChange)
    /*
    ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
    ON_UPDATE_COMMAND_UI(ID_HELP_INDEX, OnUpdateHelpIndex)
    ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
    ON_UPDATE_COMMAND_UI(ID_HELP_USING, OnUpdateHelpUsing)
    ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelpIndex)
    ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
    ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
    */
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BaseMainFrame
//---------------------------------------------------------------------------
PSS_BaseMainFrame::PSS_BaseMainFrame(bool mustSaveBarState) :
    SECMDIFrameWnd(),
    m_pToolBar(NULL),
    m_Page(0),
    m_TotalPage(0),
    m_MustSaveBarState(mustSaveBarState),
    m_SaveBarStateHasBeenInitialized(false)
{
    m_pControlBarManager = new SECToolBarManager(this);
    m_pMenuBar           = new SECMDIMenuBar;           // ...or SECMenuBar for SDI

    // use the cool bitmap menu support
    EnableBmpMenus();

    // initialize the Floating Toolbar
    PSS_FloatingToolBar::Initialize(&m_WindowConfiguration,
                                    dynamic_cast<SECToolBarManager*>(m_pControlBarManager),
                                    m_pMenuBar);
}
//---------------------------------------------------------------------------
PSS_BaseMainFrame::~PSS_BaseMainFrame()
{
    if (m_pToolBar)
        delete m_pToolBar;

    // delete the control bar manager
    if (m_pControlBarManager)
        delete m_pControlBarManager;

    if (m_pMenuBar)
        delete m_pMenuBar;
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnReloadBarState(bool reset)
{
    if (GetMustSaveBarState())
    {
        m_WindowConfiguration.Create(AfxGetApp()->m_pszProfileName);
        m_WindowConfiguration.RestoreWindowPosition(this, _T("MainWindow"));

        if (m_pControlBarManager)
        {
            if (reset)
                LoadBarState(_T("Unknown profile"));
            else
                LoadBarState(M_Def_SaveWindowStateStr);

            SECToolBarManager* pToolBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);
            PSS_Assert(pToolBarManager);

            if (reset)
                pToolBarManager->LoadState(_T("Unknown profile"));
            else
                pToolBarManager->LoadState(M_Def_SaveWindowStateStr);
        }

        m_SaveBarStateHasBeenInitialized = true;
    }
    else
    {
        SECToolBarManager* pToolBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);
        PSS_Assert(pToolBarManager);
        pToolBarManager->SetDefaultDockState();
    }
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnSaveBarState()
{
    if (GetMustSaveBarState())
    {
        // if not initialized, do it before saving space
        if (!m_SaveBarStateHasBeenInitialized)
            m_WindowConfiguration.Create(AfxGetApp()->m_pszProfileName);

        m_WindowConfiguration.SaveWindowPosition(this, _T("MainWindow"));

        if (m_pControlBarManager)
        {
            SaveBarState(M_Def_SaveWindowStateStr);

            SECToolBarManager* pToolBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);
            PSS_Assert(pToolBarManager);
            pToolBarManager->SaveState(M_Def_SaveWindowStateStr);
        }
    }
}
//---------------------------------------------------------------------------
#ifdef __CREATE_LOGO_
    int PSS_BaseMainFrame::CreateClient(LPCREATESTRUCT pCreateStruct, CMenu* pMenu)
    {
        if (!CMDIFrameWnd::CreateClient(pCreateStruct, pMenu))
            return FALSE;

        // m_hWndMDIClient is the pointer to the MDI Client
        m_MDIClientFrame.SubclassWindow(m_hWndMDIClient);

        return TRUE;
    }
#endif
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::LoadMenuBar(UINT menuID)
{
    if (m_pMenuBar && m_pControlBarManager)
    {
        SECToolBarManager* pToolBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);
        PSS_Assert(pToolBarManager);
        pToolBarManager->SetMenuInfo(1, menuID);
    }
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnViewFullScreen()
{
    // bitmap toolbar with OT defined resource
    m_FSView.SetFSMode();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseMainFrame::PointerWindowIsVisible()
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::ShowPointerWindow()
{}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::HidePointerWindow()
{}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BaseMainFrame::AssertValid() const
    {
        CMDIFrameWnd::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BaseMainFrame::Dump(CDumpContext& dc) const
    {
        CMDIFrameWnd::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_BaseMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!SECMDIFrameWnd::PreCreateWindow(cs))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_BaseMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (SECMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // calls the derived method to create the menus
    if (!CreateMenuBars())
        return -1;

    // calls the derived method to create the toolbars
    if (!CreateToolBars())
        return -1;

    // calls the derived method to create the status bar
    if (!CreateStatusBar())
        return -1;

    EnableDocking(CBRS_ALIGN_ANY);

    // calls the derived method to initialize the docking windows
    if (!InitializeDockingWindows())
        return -1;

    // call this to position the default toolbars as configured by
    // the DefineDefaultToolBar commands above. Don't do this
    // if you are going immediately use LoadBarState/LoadState below,
    // as these functions will call it anyways on nonexistent state info
    SECToolBarManager* pToolBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);
    PSS_Assert(pToolBarManager);

    pToolBarManager->EnableCoolLook();

    // The 'context list' mode provides a pop-up menu listing all the control bars
    // that are present in this frame. Similar to the Visual Studio UI, docking
    //windows can be turned on or off using this menu
    EnableContextListMode(TRUE);

    // required to restore state
    OnReloadBarState();

    // set by default the edition tool
    PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IEToolType::IE_TT_VToolEdit;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    if (pPopupMenu->GetMenuItemCount())
        if (pPopupMenu->GetMenuItemID(0) >= MENU_COMMAND && pPopupMenu->GetMenuItemID(0) <= MAX_MENU_COMMAND)
            m_bAutoMenuEnable = FALSE;

    CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
    m_bAutoMenuEnable = TRUE;
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnViewPointer()
{
    if (PointerWindowIsVisible())
        HidePointerWindow();
    else
        ShowPointerWindow();
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnUpdateViewPointer(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->SetCheck(PointerWindowIsVisible());
}
//---------------------------------------------------------------------------
/*
void PSS_BaseMainFrame::OnUpdateHelpIndex(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(FALSE);
}
*/
//---------------------------------------------------------------------------
/*
void PSS_BaseMainFrame::OnUpdateHelpUsing(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(FALSE);
}
*/
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::OnClose()
{
    SECMDIFrameWnd::OnClose();
}
//---------------------------------------------------------------------------
LRESULT PSS_BaseMainFrame::OnFSModeChange(WPARAM wParam, LPARAM)
{
    // wParam is TRUE when the full screen mode is being set. Notify the active view
    // so that it can restore the toolbar
    CMDIChildWnd* pMDIChild = MDIGetActive();

    if (pMDIChild && ::IsWindow(pMDIChild->GetSafeHwnd()))
    {
        CView* pActvView = pMDIChild->GetActiveView();
        pActvView->PostMessage(WM_NOTIFYVIEW_ONFULLSCREEN, wParam);
        pMDIChild->PostMessage(WM_NOTIFYVIEW_ONFULLSCREEN, wParam);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd && wParam >= MENU_COMMAND && wParam <= MAX_MENU_COMMAND)
    {
        pWnd->SendMessageToDescendants(ID_SPECIALHELPMENU, wParam);
        return 1;
    }

    return CWnd::OnCommand(wParam, lParam);
}
//---------------------------------------------------------------------------
