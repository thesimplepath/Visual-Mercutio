/****************************************************************************
 * ==> PSS_MainFrame -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the main frame                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MainFrame.h"

// processsoft
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_FloatingToolBar.h"
#include "zBaseLib\PSS_RegisterSetup.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zModelBP\PSS_ProcessGraphModelControllerBP.h"
#include "PSS_ProcessModelDocument.h"
#include "PSS_App.h"

// resources
#ifdef _DEBUG
    #include "zFormsRes\zFormsRes.h"
#endif
#include "zModel\zModelRes.h"
#include "zModelBP\zModelBPRes.h"
#include "Resources.h"
#include "PSS_RegistryDefs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Windows messages
//---------------------------------------------------------------------------
#define ID_MENUBAR_FILE_MAINFRAME 0x80000001
#define ID_MENUBAR_FILE_MODEL     0x80000002
#define ID_MENUBAR_EDIT           0x80000003
#define ID_MENUBAR_DISPLAY        0x80000004
#define ID_MENUBAR_DRAWING        0x80000005
#define ID_MENUBAR_INSERTION      0x80000006
#define ID_MENUBAR_WORKSPACE      0x80000007
#define ID_MENUBAR_TOOLS          0x80000008
#define ID_MENUBAR_WINDOW         0x80000009
#define ID_MENUBAR_HELP           0x80000010
//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_BitFlag_MainFrame   0x00000001
#define M_BitFlag_ModelView   0x00000002
#define M_BitFlag_ModelBPView 0x00000004
#define M_BitFlag_ReportView  0x00000008
#define M_BitFlag_All         (M_BitFlag_MainFrame | M_BitFlag_ModelView | M_BitFlag_ModelBPView | M_BitFlag_ReportView)
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------

/**
* IMPORTANT NOTE when a new item should be added in a toolbar, the zProcess32.ini file
* in the c:\Windows dir should be reseted. The new button will not appear in the toolbar
* until this operation will be carried out
*/

static UINT BASED_CODE g_FileButtons[] =
{
    ID_FILE_NEWMODEL,
    ID_FILE_OPENMODEL,
    ID_FILE_SAVE,
    ID_FILE_SAVE_ALL,
    ID_SEPARATOR,
    ID_FILE_PRINT_PREVIEW,
    ID_FILE_PRINT,
    ID_SEPARATOR,
    ID_EDIT_UNDO,
    ID_EDIT_REDO,
    ID_SEPARATOR,
    ID_VIEW_WORKSPACE,
    ID_VIEW_OUTPUTWORKSPACE,
    ID_VIEW_PROPERTIES,
    ID_SEPARATOR,
    ID_CHANGE_FILEVERSION,
    ID_SEPARATOR,
    ID_VIEW_TIPOFDAY,
    ID_SEPARATOR,
    ID_SELECT_SERVER,
    ID_VIEW_FULLSCREEN,
};

static UINT BASED_CODE g_BrowseButtons[] =
{
    ID_GO_PARENTMODEL,
    ID_REFRESH,
    ID_BROWSE_SOURCESYMBOL,
    ID_FIND_SYMBOL,
};

static UINT BASED_CODE g_ZoomButtons[] =
{
    ID_OD_ZOOM,
    ID_VIEW_ZOOMIN,
    ID_VIEW_ZOOMOUT,
    ID_OD_ZOOM_FIT,
    ID_OD_ZOOM_SELECTION,
    ID_SEPARATOR,
    ID_OD_PAN,
    ID_OD_DRAW_SELECT,
};

static UINT BASED_CODE g_GridButtons[] =
{
    ID_OD_GRID,
    ID_OD_SNAP_TO_GRID,
    ID_OD_PAGE_BOUNDS,
    ID_SHOWMODELBORDER,
};

static UINT BASED_CODE g_DrawingButtons[] =
{
    ID_OD_EDIT_VERTICES,
    ID_OD_PROPERTIES,
    ID_SEPARATOR,
    ID_EDIT_FORMATPAINTER,
    ID_SEPARATOR,
    ID_OD_DRAW_LINE,
    ID_OD_DRAW_POLYLINE,
    ID_OD_DRAW_POLYGON,
    ID_OD_DRAW_RECT,
    ID_OD_DRAW_POLYCURVE,
    ID_OD_DRAW_CLOSEDCURVE,
    ID_OD_DRAW_ELLIPSE,
    ID_SEPARATOR,
    ID_OD_DRAW_TEXT,
    ID_OD_DRAW_IMAGE,
    ID_OD_DRAW_PORT,
};

static UINT BASED_CODE g_RotationButtons[] =
{
    ID_OD_FREE_ROTATE,
    ID_SEPARATOR,
    ID_OD_ROTATE_LEFT,
    ID_OD_ROTATE_RIGHT,
    ID_OD_FLIP_HORIZONTAL,
    ID_OD_FLIP_VERTICAL,
};

static UINT BASED_CODE g_AlignButtons[] =
{
    ID_OD_ALIGN_TOP,
    ID_OD_ALIGN_MIDDLE,
    ID_OD_ALIGN_BOTTOM,
    ID_OD_ALIGN_LEFT,
    ID_OD_ALIGN_CENTER,
    ID_OD_ALIGN_RIGHT,
};

static UINT BASED_CODE g_ArrangeButtons[] =
{
    ID_OD_SPACE_ACROSS,
    ID_OD_SPACE_DOWN,
    ID_OD_SAME_WIDTH,
    ID_OD_SAME_HEIGHT,
    ID_OD_SAME_SIZE,
};

static UINT BASED_CODE g_MoveButtons[] =
{
    ID_OD_NUDGE_UP,
    ID_OD_NUDGE_DOWN,
    ID_OD_NUDGE_LEFT,
    ID_OD_NUDGE_RIGHT,
};

static UINT BASED_CODE g_GroupButtons[] =
{
    ID_OD_GROUP,
    ID_OD_UNGROUP,
    ID_SEPARATOR,
    ID_OD_FRONT,
    ID_OD_BACK,
    ID_OD_FORWARD,
    ID_OD_BACKWARD,
};

static UINT BASED_CODE g_WorkspaceButtons[] =
{
    ID_WKS_NEWGROUP,
    ID_WKS_RENAMEGROUP,
    ID_WKS_DELETEGROUP,
    ID_SEPARATOR,
    ID_WKS_ADDFILE,
    ID_WKS_DELETEFILE,
    ID_WKS_PROPERTIES,
    ID_SEPARATOR,
    ID_WKS_ADD_CURRENTFILE,
};

static UINT BASED_CODE g_ModelisationButtons[] =
{
    ID_OD_DRAW_SELECT,
    ID_SEPARATOR,
    ID_INS_BP_PROCEDURE,
    ID_INS_BP_PROCESS,
    ID_INS_BP_PAGE,
    ID_INS_BP_DOOR,
    ID_INS_BP_START,
    ID_INS_BP_STOP,
    ID_SEPARATOR,
    ID_INS_BP_DELIVERABLE,
    ID_SEPARATOR,
    ID_INS_BP_PACKAGE,
};

static UINT BASED_CODE g_ModelGenerationButtons[] =
{
    ID_CHECK_MODEL,
    ID_RECALCULATE_MODEL_PARAM,
    ID_RECALCULATE_MODEL_DURATION,
    ID_CALCULATE_RISKS,
    ID_SEPARATOR,
    ID_GENERATE_REPORT_CHECK,
    ID_GENERATE_REPORT_MERCUTIO,
    ID_GENERATE_REPORT_CONCEPTOR,
    ID_GENERATE_REPORT_SESTERCE,
    ID_GENERATE_REPORT_SESTERCE_UNIT,
    ID_GENERATE_REPORT_SESTERCE_CONSOLIDATED,
    ID_GENERATE_REPORT_PRESTATIONS,
};

static UINT BASED_CODE g_ModelSimulationButtons[] =
{
    ID_PLAY_SIMULATION,
    ID_SEPARATOR,
    ID_PAUSE_SIMULATION,
    ID_REW_SIMULATION,
    ID_FWD_SIMULATION,
    ID_SEPARATOR,
    ID_STOP_SIMULATION,
};

static UINT BASED_CODE g_SymbolAttributesButtons[] =
{
    ID_SYM_SHOWNAMEAREA,
    ID_SYM_SHOWDESCRIPTIONAREA,
    ID_SYM_SHOWATTRIBUTEAREA,
    ID_SEPARATOR,
    ID_SYM_SELECTATTRIBUTES,
    ID_SYM_SHOWLABELATTRIBUTES,
    ID_SEPARATOR,
    ID_DYNATTR_ADD,
    ID_DYNATTR_DISPLAY,
};

static UINT BASED_CODE g_AddSymbolsButtons[] =
{
    ID_INS_BP_ALERT,
    ID_INS_BP_DOCUMENT,
    ID_INS_BP_INDICATOR,
    ID_INS_BP_QUALITY,
    ID_SEPARATOR,
    ID_INS_BP_DELAY,
    ID_SEPARATOR,
    ID_INS_BP_IN_PROCESS,
    ID_INS_BP_NOT_VALIDATED,
    ID_INS_BP_VALIDATED,
    ID_SEPARATOR,
    ID_INS_BP_RISK,
    ID_INS_BP_INCIDENT,
    ID_INS_BP_CRI,
    ID_SEPARATOR,
    ID_INS_BP_CRE,
    ID_INS_BP_CRO,
    ID_SEPARATOR,
    ID_INS_BP_OPAP1,
    ID_INS_BP_OPAP2,
    ID_INS_BP_OPAP3,
    ID_SEPARATOR,
    ID_INS_BP_TEXTZONE
};

/// default menu bar layout
static UINT g_MenuButtons[] =
{
    ID_MENUBAR_FILE_MAINFRAME,    // "File" sub-menu for mainframe view
    ID_MENUBAR_FILE_MODEL,        // "File" sub-menu for model view
    ID_MENUBAR_EDIT,
    ID_MENUBAR_DISPLAY,
    ID_MENUBAR_DRAWING,
    ID_MENUBAR_INSERTION,
    ID_MENUBAR_WORKSPACE,
    ID_MENUBAR_TOOLS,
    ID_MENUBAR_WINDOW,
    ID_MENUBAR_HELP,
};

/// bit flag to menu resource mapping table
static SECMenuMap g_MenuMap[] =
{
    {IDR_MAINFRAME,      M_BitFlag_MainFrame},
    {IDR_MODEL,          M_BitFlag_ModelView},
    {IDR_BP_MODEL,       M_BitFlag_ModelBPView},
    {IDR_MERCUTIOREPORT, M_BitFlag_ReportView}
};

static UINT BASED_CODE g_Indicators[] =
{
    ID_SEPARATOR,      // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_PAGE,
};
//---------------------------------------------------------------------------
// Button message map
//---------------------------------------------------------------------------
// todo -cFeature -oJean: not satisfactory, but for now keep it that way. In the future
//                        the strings should be moved in the resources
//#define ENGLISH_RESOURCES

#ifdef ENGLISH_RESOURCES
    BEGIN_BUTTON_MAP(g_BtnMap)
        MENU_BUTTON_EX(ID_MENUBAR_FILE_MAINFRAME, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 0, _T("&Files"),     M_BitFlag_MainFrame)
        MENU_BUTTON_EX(ID_MENUBAR_FILE_MODEL,     SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MODEL),     0, _T("&Files"),     M_BitFlag_ModelView | M_BitFlag_ModelBPView | M_BitFlag_ReportView)
        MENU_BUTTON_EX(ID_MENUBAR_EDIT,           SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 1, _T("&Edition"),   M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_DISPLAY,        SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 2, _T("D&isplay"),   M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_DRAWING,        SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 3, _T("&Drawing"),   M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_INSERTION,      SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 4, _T("&Insertion"), M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_WORKSPACE,      SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 5, _T("&Project"),   M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_TOOLS,          SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 6, _T("&Tools"),     M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_WINDOW,         SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 7, _T("&Window"),    M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_HELP,           SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 8, _T("&?"),         M_BitFlag_All)
    END_BUTTON_MAP()
#else
    BEGIN_BUTTON_MAP(g_BtnMap)
        MENU_BUTTON_EX(ID_MENUBAR_FILE_MAINFRAME, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 0, _T("&Fichiers"),  M_BitFlag_MainFrame)
        MENU_BUTTON_EX(ID_MENUBAR_FILE_MODEL,     SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MODEL),     0, _T("&Fichiers"),  M_BitFlag_ModelView | M_BitFlag_ModelBPView | M_BitFlag_ReportView)
        MENU_BUTTON_EX(ID_MENUBAR_EDIT,           SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 1, _T("&Edition"),   M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_DISPLAY,        SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 2, _T("&Affichage"), M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_DRAWING,        SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 3, _T("&Dessin"),    M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_INSERTION,      SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 4, _T("&Insertion"), M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_WORKSPACE,      SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 5, _T("&Projet"),    M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_TOOLS,          SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 6, _T("&Outils"),    M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_WINDOW,         SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 7, _T("Fe&nêtres"),  M_BitFlag_All)
        MENU_BUTTON_EX(ID_MENUBAR_HELP,           SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 8, _T("&?"),         M_BitFlag_All)
    END_BUTTON_MAP()
#endif
//---------------------------------------------------------------------------
// PSS_MainFrame
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_MainFrame, PSS_BaseMainFrame)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MainFrame, PSS_BaseMainFrame)
    //{{AFX_MSG_MAP(PSS_MainFrame)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAGE, OnUpdatePage)
    ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
    ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullScreen)
    ON_COMMAND(ID_VIEW_PROJECTWINDOW, OnViewProjectWindow)
    ON_UPDATE_COMMAND_UI(ID_VIEW_PROJECTWINDOW, OnUpdateViewProjectWindow)
    ON_COMMAND(ID_VIEW_TIPOFDAY, OnViewTipOfDayBar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_TIPOFDAY, OnUpdateViewTipOfDayBar)
    ON_COMMAND(ID_VIEW_HELPCONTEXT, OnViewHelpContextBar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_HELPCONTEXT, OnUpdateViewHelpContextBar)
    ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
    ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
    ON_COMMAND(ID_VIEW_OUTPUTWORKSPACE, OnViewOutputWorkspace)
    ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUTWORKSPACE, OnUpdateViewOutputWorkspace)
    ON_COMMAND(ID_VIEW_PROPERTIES, OnViewProperties)
    ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateViewProperties)
    ON_COMMAND(IDC_CUSTOMIZE, OnCustomize)
    ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
    ON_MESSAGE(UM_DOCUMENTLOADED, OnDocumentLoaded)
    ON_MESSAGE(WM_DDE_EXECUTE, OnDDEExecute)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MainFrame
//---------------------------------------------------------------------------
PSS_MainFrame::PSS_MainFrame() :
    PSS_BaseMainFrame()
{}
//---------------------------------------------------------------------------
PSS_MainFrame::~PSS_MainFrame()
{}
//---------------------------------------------------------------------------
void PSS_MainFrame::ViewZoomIn()
{
    PSS_Document* pDoc = dynamic_cast<PSS_Document*>(GetActiveDocument());

    if (!pDoc)
        return;

    PSS_View* pMainView = pDoc->GetMainView();

    if (!pMainView)
        return;

    const int zoom = __min(400, pMainView->GetZoomPercentage() + 25);

    pMainView->SetZoomPercentage(zoom);
    pDoc->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::ViewZoomOut()
{
    PSS_Document* pDoc = dynamic_cast<PSS_Document*>(GetActiveDocument());

    if (!pDoc)
        return;

    PSS_View* pMainView = pDoc->GetMainView();

    if (!pMainView)
        return;

    const int zoom = __max(25, pMainView->GetZoomPercentage() - 25);

    pMainView->SetZoomPercentage(zoom);
    pDoc->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_MainFrame::AssertValid() const
    {
        PSS_BaseMainFrame::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_MainFrame::Dump(CDumpContext& dc) const
    {
        PSS_BaseMainFrame::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_MainFrame::OnReloadBarState(bool reset)
{
    PSS_RegisterSetup registry;
    CString           value;
    bool              reload = false;

    // get the value from the registry. If returned false, assume that the key does not exists, which is not an error
    if (registry.GetRegValue(HKEY_LOCAL_MACHINE, REGKEY_CONCEPTORROOT, REGKEY_RELOADTOOLBAR, value, false, true))
        if (value == _T("1"))
            reload = true;

    // get the keyboard state
    BYTE keyState[256];
    ::GetKeyboardState(LPBYTE(&keyState));

    // if the shift key is pressed, also reload the toolbar
    if (keyState[VK_SHIFT] & 0x80)
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_ASKRESET_TOOLBARS, MB_YESNO) == IDYES)
            reload = true;
    }

    PSS_BaseMainFrame::OnReloadBarState(reload);

    if (reload)
        registry.UpdateRegValue(HKEY_LOCAL_MACHINE, REGKEY_CONCEPTORROOT, REGKEY_RELOADTOOLBAR, _T("0"));
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnSaveBarState()
{
    PSS_BaseMainFrame::OnSaveBarState();
}
//---------------------------------------------------------------------------
int PSS_MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_BaseMainFrame::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnClose()
{
    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return;

    if (!pApp->ExitApp())
        return;

    if (GetMustSaveBarState())
        OnSaveBarState();

    m_WndWorkspace.Release();
    m_WndOutputWorkspace.Release();
    m_WndPropertiesWorkspace.Release();

    PSS_BaseMainFrame::OnClose();
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdatePage(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable();

    char pageName[50];
    std::sprintf(pageName, _T("Page %d/%d"), m_Page, m_TotalPage);
    pCmdUI->SetText(pageName);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewFullScreen()
{
    PSS_BaseMainFrame::OnViewFullScreen();
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->SetCheck(PSS_BaseMainFrame::IsFullScreen());
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewProjectWindow()
{
    OnBarCheck(ID_VIEW_PROJECTWINDOW);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewProjectWindow(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_PROJECTWINDOW;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewTipOfDayBar()
{
    OnBarCheck(ID_VIEW_TIPOFDAY);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewTipOfDayBar(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_TIPOFDAY;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewHelpContextBar()
{
    OnBarCheck(ID_VIEW_HELPCONTEXT);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewHelpContextBar(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_HELPCONTEXT;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewWorkspace()
{
    OnBarCheck(ID_VIEW_WORKSPACE);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_WORKSPACE;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewOutputWorkspace()
{
    OnBarCheck(ID_VIEW_OUTPUTWORKSPACE);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewOutputWorkspace(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_OUTPUTWORKSPACE;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewProperties()
{
    OnBarCheck(ID_VIEW_PROPERTIES);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewProperties(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->m_nID = ID_VIEW_PROPERTIES;
    OnUpdateControlBarMenu(pCmdUI);
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnCustomize()
{
    SECToolBarsPage toolbarPage;
    toolbarPage.SetManager((SECToolBarManager*)m_pControlBarManager);

    SECToolBarSheet toolbarSheet;
    toolbarSheet.AddPage(&toolbarPage);

    SECToolBarCmdPage cmdPage(SECToolBarCmdPage::IDD, IDS_COMMANDS);
    cmdPage.SetManager((SECToolBarManager*)m_pControlBarManager);

    CString title;

    // add button group
    title.LoadString(IDS_TB_FILEBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_FileButtons),             g_FileButtons);
    title.LoadString(IDS_TB_BROWSEBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_BrowseButtons),           g_BrowseButtons);
    title.LoadString(IDS_TB_ZOOMBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_ZoomButtons),             g_ZoomButtons);
    title.LoadString(IDS_TB_GRIDBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_GridButtons),             g_GridButtons);
    title.LoadString(IDS_TB_DRAWINGBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_DrawingButtons),          g_DrawingButtons);
    title.LoadString(IDS_TB_ROTATIONBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_RotationButtons),         g_RotationButtons);
    title.LoadString(IDS_TB_ALIGNBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_AlignButtons),            g_AlignButtons);
    title.LoadString(IDS_TB_ARRANGEBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_ArrangeButtons),          g_ArrangeButtons);
    title.LoadString(IDS_TB_MOVEBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_MoveButtons),             g_MoveButtons);
    title.LoadString(IDS_TB_GROUPBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_GroupButtons),            g_GroupButtons);
    title.LoadString(IDS_TB_WORKSPACEBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_WorkspaceButtons),        g_WorkspaceButtons);
    title.LoadString(IDS_TB_SIMULATIONBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_ModelSimulationButtons),  g_ModelSimulationButtons);
    title.LoadString(IDS_TB_ATTRIBUTESBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_SymbolAttributesButtons), g_SymbolAttributesButtons);
    title.LoadString(IDS_TB_BPMODELISATIONBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_ModelisationButtons),     g_ModelisationButtons);
    title.LoadString(IDS_TB_BPMODELGENERATIONBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_ModelGenerationButtons),  g_ModelGenerationButtons);
    title.LoadString(IDS_TB_BPSYMBOLSBUTTONS);
    cmdPage.DefineBtnGroup(title, NUMELEMENTS(g_AddSymbolsButtons),       g_AddSymbolsButtons);

    // todo -cFeature -oJean: Localize me
    // add menu
    cmdPage.DefineMenuGroup(_T("Menus"));

    toolbarSheet.AddPage(&cmdPage);
    toolbarSheet.DoModal();
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnViewToolbar()
{
    SECToolBarManager* pControlBarManager = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);

    if (!pControlBarManager)
        return;

    if (pControlBarManager->ExecViewToolBarsDlg() == IDC_TOOLBAR_CUSTOMIZE)
        OnCustomize();
}
//---------------------------------------------------------------------------
void PSS_MainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
LRESULT PSS_MainFrame::OnDocumentLoaded(WPARAM wParam, LPARAM lParam)
{
    PSS_ObserverMsg*    pMsg    = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_DocObserverMsg* pDocMsg = dynamic_cast<PSS_DocObserverMsg*>(pMsg);

    if (pDocMsg)
    {
        PSS_ProcessGraphModelDoc* pDoc = pDocMsg->GetDoc();

        if (pDoc)
        {
            PSS_ProcessWorkspace* pProcessWorkspace = GetWorkspace();

            // attach process workspace as observer
            if (pProcessWorkspace)
                pDoc->AttachObserver(pProcessWorkspace);

            PSS_PropertiesWorkspace* pPropsWorkspace = GetPropertiesWorkspace();

            // attach properties workspace as observer
            if (pPropsWorkspace)
                pDoc->AttachObserver(pPropsWorkspace);

            PSS_OutputWorkspace* pOutputWorkspace = GetOutputWorkspace();

            if (pOutputWorkspace)
            {
                // attach output workspace as observer
                pDoc->AttachObserver(pOutputWorkspace);
                pOutputWorkspace->AttachObserver(pDoc);

                pDoc->Initialize(pOutputWorkspace->GetLogView(),
                                 pOutputWorkspace->GetAnalyzerLogView(),
                                 pOutputWorkspace->GetSearchLogView(),
                                 pOutputWorkspace->GetWorkflowLogView(),
                                 NULL,
                                 NULL,
                                 NULL);
            }
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_MainFrame::OnDDEExecute(WPARAM wParam, LPARAM lParam)
{
    UINT_PTR unused;
    HGLOBAL  hData;

    // unpack the DDE message. IA64: Assume DDE LPARAMs are still 32-bit
    VERIFY(::UnpackDDElParam(WM_DDE_EXECUTE,
                             lParam,
                             &unused,
                             (UINT_PTR*)&hData));

    // get the command string
    LPCTSTR pData = LPCTSTR(::GlobalLock(hData));

    if (!pData)
        return 0L;

    TCHAR command[_MAX_PATH * 2] = {0};

    try
    {
        const int commandLength = lstrlen(pData);

        // this line is added to original MS code
        const int arrayLen = sizeof(command) / sizeof(TCHAR);

        // this line is required to avoid _countof (another include file)
        if (commandLength >= arrayLen)
        {
            // the command would be truncated. This may be a security problem
            TRACE0("Warning: Command was ignored because it was too long.\n");
            return 0L;
        }

        // this line is needed to rectify an issue
        lstrcpyn(command, pData, arrayLen);
    }
    catch (...)
    {
        ::GlobalUnlock(hData);
        throw;
    }

    ::GlobalUnlock(hData);

    // acknowledge now - before attempting to execute. IA64: Assume DDE LPARAMs are still 32-bit
    ::PostMessage(reinterpret_cast<HWND>(wParam),
                  WM_DDE_ACK,
                  WPARAM(m_hWnd),
                  ::ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK, UINT(0x8000), UINT_PTR(hData)));

    // don't execute the command when the window is disabled
    if (!IsWindowEnabled())
    {
        // show an error message if the user opened a file associated with Visual Mercutio while the application
        // isn't opened. This is not the best solution, but at least the user may understand what is happening.
        // The bug comes probably because the override of this function isn't at the best possible place. Indeed
        // this function is called when the application is running. But the application may be partially opened,
        // or not opened at all, when a Visual Mercutio project file is opened by the user, and thus when this
        // function is called, for that reason IsWindowEnabled() will always return false. And after the init
        // will be completed, the basic OnDDEExecute() function will be called instead, but it contains a bug
        // in Visual Studio 7.1. This is also the reason why a "Unable to find the file e:\dde" error message
        // appears while the application is opened this way, which is the bug itself
        ::AfxMessageBox(_T("Le fichier n'a pas pu s'ouvrir correctement car l'application n'était pas ouverte. Veuillez réessayer avec l'application ouverte au préalable."));
        TRACE(traceAppMsg, 0, _T("Warning - DDE command '%s' ignored because window is disabled.\n"), command);
        return 0L;
    }

    CWinApp* pApp = ::AfxGetApp();

    // execute the command
    if (!pApp || !pApp->OnDDECommand(command))
        TRACE(traceAppMsg, 0, _T("Error: failed to execute DDE command '%s'.\n"), command);

    return 0L;
}
//---------------------------------------------------------------------------
BOOL PSS_MainFrame::CreateToolBars()
{
    SECToolBarManager* pMgr = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);

    if (!pMgr)
        return FALSE;

    // use the following calls for multiple bitmaps (to surpass the 2048 pixel width limit on toolbar bitmaps)
    pMgr->LoadToolBarResource(MAKEINTRESOURCE(IDR_MAINFRAME), NULL);
    pMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_BP_MODELISATION), NULL);
    pMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_BP_ADDSYMBOLS), NULL);
    pMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_SIMULATION_TOOLBAR), NULL);
    pMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_DYNATTRIB_TOOLBAR), NULL);
    VERIFY(pMgr->LoadToolBarResource());

    // load the button map
    pMgr->SetButtonMap(g_BtnMap);

    CString title;
    title.LoadString(IDS_TB_FILEBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR,
                               title,
                               NUMELEMENTS(g_FileButtons),
                               g_FileButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP);

    title.LoadString(IDS_TB_BROWSEBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 10,
                               title,
                               NUMELEMENTS(g_BrowseButtons),
                               g_BrowseButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR);

    title.LoadString(IDS_TB_ZOOMBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 11,
                               title,
                               NUMELEMENTS(g_ZoomButtons),
                               g_ZoomButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               TRUE);

    title.LoadString(IDS_TB_GRIDBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 12,
                               title,
                               NUMELEMENTS(g_GridButtons),
                               g_GridButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_DRAWINGBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 13,
                               title,
                               NUMELEMENTS(g_DrawingButtons),
                               g_DrawingButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP);

    title.LoadString(IDS_TB_ROTATIONBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 14,
                               title,
                               NUMELEMENTS(g_RotationButtons),
                               g_RotationButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_ALIGNBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 15,
                               title,
                               NUMELEMENTS(g_AlignButtons),
                               g_AlignButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_ARRANGEBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 16,
                               title,
                               NUMELEMENTS(g_ArrangeButtons),
                               g_ArrangeButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_MOVEBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 17,
                               title,
                               NUMELEMENTS(g_MoveButtons),
                               g_MoveButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_GROUPBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 18,
                               title,
                               NUMELEMENTS(g_GroupButtons),
                               g_GroupButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_WORKSPACEBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 19,
                               title,
                               NUMELEMENTS(g_WorkspaceButtons),
                               g_WorkspaceButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               NULL,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_ATTRIBUTESBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 20,
                               title,
                               NUMELEMENTS(g_SymbolAttributesButtons),
                               g_SymbolAttributesButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR + 11,
                               TRUE,
                               TRUE);

    title.LoadString(IDS_TB_SIMULATIONBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 21,
                               title,
                               NUMELEMENTS(g_ModelSimulationButtons),
                               g_ModelSimulationButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR + 20,
                               TRUE,
                               FALSE);

    title.LoadString(IDS_TB_BPSYMBOLSBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 22,
                               title,
                               NUMELEMENTS(g_AddSymbolsButtons),
                               g_AddSymbolsButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR + 13,
                               TRUE,
                               TRUE);

    title.LoadString(IDS_TB_BPMODELISATIONBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 23,
                               title,
                               NUMELEMENTS(g_ModelisationButtons),
                               g_ModelisationButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR + 20,
                               TRUE,
                               TRUE);

   // register BP toolbar
    PSS_FloatingToolBar::RegisterToolBar(M_ModelisationToolbarName, AFX_IDW_TOOLBAR + 23, this, EModelNotation::E_MN_Beryl);

    title.LoadString(IDS_TB_BPMODELGENERATIONBUTTONS);

    pMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 24,
                               title,
                               NUMELEMENTS(g_ModelGenerationButtons),
                               g_ModelGenerationButtons,
                               CBRS_ALIGN_ANY,
                               AFX_IDW_DOCKBAR_TOP,
                               AFX_IDW_TOOLBAR + 23,
                               TRUE,
                               TRUE);

    PSS_FloatingToolBar::RegisterToolBar(M_ModelGenerationToolbarName, AFX_IDW_TOOLBAR + 24, this, EModelNotation::E_MN_Beryl);

    // enable the tooltips
    pMgr->EnableToolTips(TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_MainFrame::CreateStatusBar()
{
    if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(g_Indicators, sizeof(g_Indicators) / sizeof(UINT)))
    {
        TRACE("Failed to create status bar\n");
        return FALSE;
    }

    m_StatusBar.SetPaneInfo(3, ID_INDICATOR_PAGE, SBPS_NORMAL, 80);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_MainFrame::CreateMenuBars()
{
    SECToolBarManager* pMgr = dynamic_cast<SECToolBarManager*>(m_pControlBarManager);

    if (!pMgr)
        return FALSE;

    // used to load menus
    pMgr->SetMenuInfo(2, IDR_MAINFRAME, IDR_MODEL);
    pMgr->SetMenuMap(g_MenuMap, NUMELEMENTS(g_MenuMap));
    pMgr->LayoutMenuBar(NUMELEMENTS(g_MenuButtons), g_MenuButtons);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_MainFrame::InitializeDockingWindows()
{
    // todo -cFeature -oJean: Localize me
    // workspace window
    if (!m_WndWorkspace.Create(this,
                               _T("Espace de travail"),
                               CBRS_LEFT | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                               CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                               ID_VIEW_WORKSPACE))
    {
        TRACE0("Failed to create dialog bar m_wndWorkspace\n");
        return -1;
    }

    m_WndWorkspace.Initialize();
    m_WndWorkspace.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBarEx(&m_WndWorkspace, AFX_IDW_DOCKBAR_LEFT, 0, 0, 0.8f, 220);
    ShowControlBar(&m_WndWorkspace, TRUE, TRUE);

    // todo -cFeature -oJean: Localize me
    // properties window
    if (!m_WndPropertiesWorkspace.Create(this,
                                         _T("Propriétés"),
                                         CBRS_RIGHT | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                         CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                         ID_VIEW_PROPERTIES))
    {
        TRACE0("Failed to create dialog bar m_wndPropertiesWorkspace\n");
        return -1;
    }

    m_WndPropertiesWorkspace.Initialize();
    m_WndPropertiesWorkspace.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBarEx(&m_WndPropertiesWorkspace, AFX_IDW_DOCKBAR_RIGHT, 0, 0, 0.8f, 220);
    ShowControlBar(&m_WndPropertiesWorkspace, FALSE, FALSE);

    // todo -cFeature -oJean: Localize me
    // output window
    if (!m_WndOutputWorkspace.Create(this,
                                     _T("Log"),
                                     CBRS_BOTTOM | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                     CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                     ID_VIEW_OUTPUTWORKSPACE))
    {
        TRACE0("Failed to create dialog bar m_wndOutputWorkspace\n");
        return -1;
    }

    m_WndOutputWorkspace.Initialize();
    m_WndOutputWorkspace.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBarEx(&m_WndOutputWorkspace, AFX_IDW_DOCKBAR_BOTTOM, 0, 0, 0.4f, 100);
    ShowControlBar(&m_WndOutputWorkspace, FALSE, FALSE);

    // todo -cFeature -oJean: Localize me
    // tooltip window
    if (!m_WndTipOfDayBar.Create(this,
                                 _T("Saviez-vous que..."),
                                 CBRS_BOTTOM | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                 CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                 ID_VIEW_TIPOFDAY))
    {
        TRACE0("Failed to create dialog bar m_wndTipOfDayBar\n");
        return -1;
    }

    m_WndTipOfDayBar.SetURL(IDR_TESTTIP_FILE, AfxGetInstanceHandle());
    m_WndTipOfDayBar.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBarEx(&m_WndTipOfDayBar, AFX_IDW_DOCKBAR_BOTTOM, 0, 0, 0.3f, 100);
    ShowControlBar(&m_WndTipOfDayBar, FALSE, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
