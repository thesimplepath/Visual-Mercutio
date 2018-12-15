// mainfrm.cpp : implementation of the ZIMainFrame class

#include "stdafx.h"
#include "MainFrm.h"
#include "zBaseLib\draw.h"
#include "ZAApp.h"

#include "ZCProcessModelDocument.h"
#include "zModel\ProcGraphModelDoc.h"
#include "zModelBP\ProcGraphModelCtlrBP.h"

#include "zBaseLib\MsgBox.h"
#include "Resource.h"

#include "zModel\ZBDocObserverMsg.h"

#include "zBaseLib\ZUFloatingToolbar.h"
#include "zModel\zModelRes.h"
#include "zModelBP\zModelBPRes.h"

#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
#endif

// Used to access predefined registry keys
#include "RegistryDef.h"
#include "zBaseLib\ZBRegisterSetup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// **********************************************************************************************************
// *                                            INFORMATION IMPORTANTE                                        *
// *                                                                                                        *
// * Lors de l'ajout d'un nouvel élément dans une barre d'outils, il est nécessaire de réinitialiser le        *
// * fichier zProcess32.ini situé dans le répertoire c:\Windows. Tant que cette opération n'aura pas été    *
// * effectuée, le nouveau bouton n'apparaîtra pas dans la barre d'outils.                                    *
// **********************************************************************************************************

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

static UINT BASED_CODE fileButtons[] =
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
    ID_CHOOSE_SERVER,
    ID_VIEW_FULLSCREEN,
};

static UINT BASED_CODE browseButtons[] =
{
    ID_GO_PARENTMODEL,
    ID_REFRESH,
    ID_BROWSE_SOURCESYMBOL,
    ID_FIND_SYMBOL,
};

static UINT BASED_CODE zoomButtons[] =
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

static UINT BASED_CODE gridButtons[] =
{
    ID_OD_GRID,
    ID_OD_SNAP_TO_GRID,
    ID_OD_PAGE_BOUNDS,
    ID_SHOWMODELBORDER,
};

static UINT BASED_CODE drawingButtons[] =
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

static UINT BASED_CODE rotationButtons[] =
{
    ID_OD_FREE_ROTATE,
    ID_SEPARATOR,
    ID_OD_ROTATE_LEFT,
    ID_OD_ROTATE_RIGHT,
    ID_OD_FLIP_HORIZONTAL,
    ID_OD_FLIP_VERTICAL,
};

static UINT BASED_CODE alignButtons[] =
{
    ID_OD_ALIGN_TOP,
    ID_OD_ALIGN_MIDDLE,
    ID_OD_ALIGN_BOTTOM,
    ID_OD_ALIGN_LEFT,
    ID_OD_ALIGN_CENTER,
    ID_OD_ALIGN_RIGHT,
};

static UINT BASED_CODE arrangeButtons[] =
{
    ID_OD_SPACE_ACROSS,
    ID_OD_SPACE_DOWN,
    ID_OD_SAME_WIDTH,
    ID_OD_SAME_HEIGHT,
    ID_OD_SAME_SIZE,
};

static UINT BASED_CODE moveButtons[] =
{
    ID_OD_NUDGE_UP,
    ID_OD_NUDGE_DOWN,
    ID_OD_NUDGE_LEFT,
    ID_OD_NUDGE_RIGHT,
};

static UINT BASED_CODE groupButtons[] =
{
    ID_OD_GROUP,
    ID_OD_UNGROUP,
    ID_SEPARATOR,
    ID_OD_FRONT,
    ID_OD_BACK,
    ID_OD_FORWARD,
    ID_OD_BACKWARD,
};

static UINT BASED_CODE workspaceButtons[] =
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

static UINT BASED_CODE modelisationButtons[] =
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

// JMR-MODIF - Le 6 mars 2006 - Ajout de la déclaration ID_GENERATE_REPORT_PRESTATIONS.
// JMR-MODIF - Le 23 juillet 2007 - Ajout de la déclaration ID_CALCULATE_RISKS.
static UINT BASED_CODE modelGenerationButtons[] =
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

static UINT BASED_CODE modelSimulationButtons[] =
{
    ID_PLAY_SIMULATION,
    ID_SEPARATOR,
    ID_PAUSE_SIMULATION,
    ID_REW_SIMULATION,
    ID_FWD_SIMULATION,
    ID_SEPARATOR,
    ID_STOP_SIMULATION,
};

static UINT BASED_CODE symbolAttributesButtons[] =
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

// JMR-MODIF - Le 17 octobre 2005 - Ajout de la déclaration des symboles.
// JMR-MODIF - Le 4 janvier 2006 - Ajout des symboles CRE/CRI/CRO/Document/Délai/En cours/Incident/Non validé/OPAP1/
// OPAP2/OPAP3/Qualité/Risque/Validité à la barre d'outils. Remaniement de l'emplacement des symboles conformément
// au document reçu.
// JMR-MODIF - le 22 mars 2006 - Ajout du symbole TextZone.
static UINT BASED_CODE addSymbolsButtons[] =
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

/////////////////////////////////////////////////////////////////////////////
// Menu bar declarations

// IDs
#define ID_MENUBAR_FILE_MAINFRAME    0x80000001
#define ID_MENUBAR_FILE_MODEL        0x80000002
#define ID_MENUBAR_EDIT                0x80000003
#define ID_MENUBAR_DISPLAY            0x80000004
#define ID_MENUBAR_DRAWING            0x80000005
#define ID_MENUBAR_INSERTION        0x80000006
#define ID_MENUBAR_WORKSPACE        0x80000007
#define ID_MENUBAR_TOOLS            0x80000008
#define ID_MENUBAR_WINDOW            0x80000009
#define ID_MENUBAR_HELP                0x80000010

// View Bit Flags
#define BITFLAG_MAINFRAME            0x00000001
#define BITFLAG_MODELVIEW            0x00000002
#define BITFLAG_MODELBPVIEW            0x00000004
#define BITFLAG_REPORTVIEW            0x00000008
#define BITFLAG_ALL                    ( BITFLAG_MAINFRAME | BITFLAG_MODELVIEW | BITFLAG_MODELBPVIEW | BITFLAG_REPORTVIEW )

// Table mapping bitflag to menu resource
static SECMenuMap menuMap[] =
{
    { IDR_MAINFRAME,        BITFLAG_MAINFRAME },
    { IDR_MODEL,            BITFLAG_MODELVIEW },
    { IDR_BP_MODEL,            BITFLAG_MODELBPVIEW },
    { IDR_MERCUTIOREPORT,    BITFLAG_REPORTVIEW }
};

// Default menu bar layout
static UINT menuButtons[] =
{
    ID_MENUBAR_FILE_MAINFRAME,    // "File" submenu for mainframe view
    ID_MENUBAR_FILE_MODEL,        // "File" submenu for model view
    ID_MENUBAR_EDIT,
    ID_MENUBAR_DISPLAY,
    ID_MENUBAR_DRAWING,
    ID_MENUBAR_INSERTION,
    ID_MENUBAR_WORKSPACE,
    ID_MENUBAR_TOOLS,
    ID_MENUBAR_WINDOW,
    ID_MENUBAR_HELP,
};

// This is not satisfactory, but in the meantime keep it as this
// After, load strings from resources
//#define _ENGLISHRESOURCES 1

#ifdef _ENGLISHRESOURCES
/////////////////////////////////////////////////////////////////////////////
// Define the button map
BEGIN_BUTTON_MAP( btnMap )
    MENU_BUTTON_EX(ID_MENUBAR_FILE_MAINFRAME, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 0, _T("&Files"), BITFLAG_MAINFRAME)
    MENU_BUTTON_EX(ID_MENUBAR_FILE_MODEL, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MODEL), 0, _T("&Files"), BITFLAG_MODELVIEW | BITFLAG_MODELBPVIEW | BITFLAG_REPORTVIEW)
    MENU_BUTTON_EX(ID_MENUBAR_EDIT, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 1, _T("&Edition"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_DISPLAY, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 2, _T("D&isplay"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_DRAWING, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 3, _T("&Drawing"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_INSERTION, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 4, _T("&Insertion"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_WORKSPACE, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 5, _T("&Project"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_TOOLS, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 6, _T("&Tools"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_WINDOW, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 7, _T("&Window"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_HELP, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 8, _T("&?"), BITFLAG_ALL)
END_BUTTON_MAP()
#endif

#ifndef _ENGLISHRESOURCES
/////////////////////////////////////////////////////////////////////////////
// Define the button map
BEGIN_BUTTON_MAP( btnMap )
    MENU_BUTTON_EX(ID_MENUBAR_FILE_MAINFRAME, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 0, _T("&Fichiers"), BITFLAG_MAINFRAME)
    MENU_BUTTON_EX(ID_MENUBAR_FILE_MODEL, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MODEL), 0, _T("&Fichiers"), BITFLAG_MODELVIEW | BITFLAG_MODELBPVIEW | BITFLAG_REPORTVIEW)
    MENU_BUTTON_EX(ID_MENUBAR_EDIT, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 1, _T("&Edition"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_DISPLAY, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 2, _T("&Affichage"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_DRAWING, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 3, _T("&Dessin"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_INSERTION, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 4, _T("&Insertion"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_WORKSPACE, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 5, _T("&Projet"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_TOOLS, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 6, _T("&Outils"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_WINDOW, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 7, _T("Fe&nêtres"), BITFLAG_ALL)
    MENU_BUTTON_EX(ID_MENUBAR_HELP, SEC_TBBS_NODISABLE, MAKEINTRESOURCE(IDR_MAINFRAME), 8, _T("&?"), BITFLAG_ALL)
END_BUTTON_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIMainFrame

IMPLEMENT_DYNAMIC( ZIMainFrame, ZIBaseMainFrame )

BEGIN_MESSAGE_MAP( ZIMainFrame, ZIBaseMainFrame )
    //{{AFX_MSG_MAP(ZIMainFrame)
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

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,        // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_PAGE,
};

/////////////////////////////////////////////////////////////////////////////
// ZIMainFrame construction/destruction

ZIMainFrame::ZIMainFrame()
{
    // JMR-MODIF - Le 30 septemnre 2007 - Initialisation des variables m_nPage et m_nTotalPage.
    m_nPage            = 0;
    m_nTotalPage    = 0;
}

ZIMainFrame::~ZIMainFrame()
{
}

// JMR-MODIF - Le 16 août 2005 - Surcharge de la commande OnDDEExecute pour corriger un bug de Visual Studio 7.1.
LRESULT ZIMainFrame::OnDDEExecute( WPARAM wParam, LPARAM lParam )
{
    // Unpack the DDE message
    UINT_PTR    unused;
    HGLOBAL        hData;

    // IA64: Assume DDE LPARAMs are still 32-bit
    VERIFY( UnpackDDElParam( WM_DDE_EXECUTE,
                             lParam,
                             &unused,
                             (UINT_PTR*)&hData ) );

    // Get the command string
    TCHAR    szCommand[_MAX_PATH * 2]    = {0};
    LPCTSTR    lpsz                        = (LPCTSTR)GlobalLock( hData );
    int        commandLength                = lstrlen( lpsz );

    // This line is added to original MS code.
    int arrayLen = sizeof( szCommand ) / sizeof( TCHAR );

    // This line is changed to avoid _countof (another include file).
    if ( commandLength >= arrayLen )
    {
        // The command would be truncated. This could be a security
        // problem.
        TRACE0( _T( "Warning: Command was ignored because it was too long.\n" ) );
        return 0L;
    }

    // This line is needed to rectify a problem.
    lstrcpyn( szCommand, lpsz, arrayLen );

    GlobalUnlock( hData );

    // Acknowledge now - before attempting to execute
    ::PostMessage( (HWND)wParam,
                   WM_DDE_ACK,
                   (WPARAM)m_hWnd,
                   // IA64: Assume DDE LPARAMs are still 32-bit
                   ReuseDDElParam( lParam, WM_DDE_EXECUTE, WM_DDE_ACK, (UINT)0x8000, (UINT_PTR)hData ) );

    // Don't execute the command when the window is disabled
    if ( !IsWindowEnabled() )
    {
        // JMR-MODIF - Le 16 août 2005 - Ajout d'un message pour tenir compte du cas où l'application n'est
        // pas ouverte lorsque l'utilisateur tente d'ouvrir un fichier associé à Mercutio. Ce n'est pas la meilleure
        // solution, mais cela permet à l'utilisateur de comprendre ce qui se passe. Le bug vient certainement du fait
        // que la surcharge de la présente fonction n'est pas à l'endroit le plus approprié. Lorsque l'application est
        // complétement démarrée, c'est cette fonction qui est appelée. Mais il est très probable que lorsque
        // l'utilisateur double-clique sur un fichier, l'application ne soit pas encore initialisée lorsque la présente
        // fonction est appelée. Aussi, elle retourne un message IsWindowEnabled == FALSE. Mais ensuite, lorsque
        // l'initialisation est terminée, c'est la fonction OnDDEExecute de base qui est appelée. Or, cette fonction
        // comporte un bug dans la version 7.1 de Visual Studio. Ce qui explique aussi l'apparition du message
        // "Impossible de trouver le fichier e:\dde", symptôme typique du bug de la fonction standard, qui apparaît
        // après le message ci-dessous.
        AfxMessageBox( _T( "Le fichier n'a pas pu s'ouvrir correctement car l'application n'était pas ouverte. Veuillez réessayer avec l'application ouverte au préalable." ) );

        TRACE( traceAppMsg, 0, _T( "Warning: DDE command '%s' ignored because window is disabled.\n" ),
               szCommand );

        return 0L;
    }

    // Execute the command
    if ( !AfxGetApp()->OnDDECommand( szCommand ) )
    {
        TRACE( traceAppMsg, 0, _T( "Error: failed to execute DDE command '%s'.\n" ), szCommand );
    }

    return 0L;
}

void ZIMainFrame::OnReloadBarState( bool Reset /*= false*/ )
{
    bool            Reload        = false;
    CString            value;
    ZBRegisterSetup    Registry;

    if ( Registry.GetRegValue( REGKEY_CONCEPTORROOT, REGKEY_RELOADTOOLBAR, value ) )
    {
        if ( value == _T( "1" ) )
        {
            Reload = true;
        }
    }

    // Check the keyboard state
    // If the shift key is pressed, then reload the toolbar also
    BYTE pbKeyState [256];

    GetKeyboardState ( (LPBYTE)&pbKeyState );

    if ( pbKeyState[VK_SHIFT] & 0x80 )
    {
        MsgBox mbox;

        if ( mbox.DisplayMsgBox( IDS_ASKRESET_TOOLBARS, MB_YESNO ) == IDYES )
        {
            Reload = true;
        }
    }

    ZIBaseMainFrame::OnReloadBarState( Reload );

    if ( Reload )
    {
        Registry.UpdateRegValue( REGKEY_CONCEPTORROOT, REGKEY_RELOADTOOLBAR, _T( "0" ) );
    }
}

void ZIMainFrame::OnSaveBarState()
{
    ZIBaseMainFrame::OnSaveBarState();
}

BOOL ZIMainFrame::CreateToolBars()
{
    ASSERT( m_pControlBarManager != NULL );
    ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );

    SECToolBarManager* pMgr = (SECToolBarManager*)m_pControlBarManager;

    // Use the following calls for multiple bitmaps ( to surpass the 2048 pixel width limit on toolbar bitmaps )
    pMgr->LoadToolBarResource( MAKEINTRESOURCE( IDR_MAINFRAME ),            NULL );
    pMgr->AddToolBarResource ( MAKEINTRESOURCE( IDR_BP_MODELISATION ),        NULL );
    // JMR-MODIF - Le 17 octobre 2005 - Ajoute les images des symboles aux menus.
    pMgr->AddToolBarResource ( MAKEINTRESOURCE( IDR_BP_ADDSYMBOLS ),        NULL );
    pMgr->AddToolBarResource ( MAKEINTRESOURCE( IDR_SIMULATION_TOOLBAR ),    NULL );
    pMgr->AddToolBarResource ( MAKEINTRESOURCE( IDR_DYNATTRIB_TOOLBAR ),    NULL );
    VERIFY( pMgr->LoadToolBarResource() );

    // Loads the button map
    pMgr->SetButtonMap( btnMap );

    CString Title;
    Title.LoadString( IDS_TB_FILEBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR,
                                Title,
                                NUMELEMENTS( fileButtons ),
                                fileButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP );

    Title.LoadString( IDS_TB_BROWSEBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 10,
                                Title,
                                NUMELEMENTS( browseButtons ),
                                browseButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                AFX_IDW_TOOLBAR );        // NextTo

    Title.LoadString( IDS_TB_ZOOMBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 11,
                                Title,
                                NUMELEMENTS( zoomButtons ),
                                zoomButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                TRUE );                    // Show

    Title.LoadString( IDS_TB_GRIDBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 12,
                                Title,
                                NUMELEMENTS( gridButtons ),
                                gridButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_DRAWINGBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 13,
                                Title,
                                NUMELEMENTS( drawingButtons ),
                                drawingButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP );

    Title.LoadString( IDS_TB_ROTATIONBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 14,
                                Title,
                                NUMELEMENTS( rotationButtons ),
                                rotationButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_ALIGNBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 15,
                                Title,
                                NUMELEMENTS( alignButtons ),
                                alignButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show 

    Title.LoadString( IDS_TB_ARRANGEBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 16,
                                Title,
                                NUMELEMENTS( arrangeButtons ),
                                arrangeButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_MOVEBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 17,
                                Title,
                                NUMELEMENTS( moveButtons ),
                                moveButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_GROUPBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 18,
                                Title,
                                NUMELEMENTS( groupButtons ),
                                groupButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_WORKSPACEBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 19,
                                Title,
                                NUMELEMENTS( workspaceButtons ),
                                workspaceButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                NULL,                    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    Title.LoadString( IDS_TB_ATTRIBUTESBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 20,
                                Title,
                                NUMELEMENTS( symbolAttributesButtons ),
                                symbolAttributesButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                AFX_IDW_TOOLBAR + 11,    // NextTo
                                TRUE,                    // Docking
                                TRUE );                    // Show

    Title.LoadString( IDS_TB_SIMULATIONBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 21,
                                Title,
                                NUMELEMENTS( modelSimulationButtons ),
                                modelSimulationButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                AFX_IDW_TOOLBAR + 20,    // NextTo
                                TRUE,                    // Docking
                                FALSE );                // Show

    // **********************************************************************************************************
    // JMR-MODIF - Le 19 octobre 2005 - Ajout de la barre des symboles externes.
    Title.LoadString( IDS_TB_BPSYMBOLSBUTTONS );

    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 22,
                                Title,
                                NUMELEMENTS( addSymbolsButtons ),
                                addSymbolsButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,
                                AFX_IDW_TOOLBAR + 13,    // Placé à côté de la barre de dessin
                                TRUE,                    // Docking
                                TRUE );                    // Show
    // **********************************************************************************************************

    Title.LoadString( IDS_TB_BPMODELISATIONBUTTONS );

    // JMR-MODIF - Le 22 mars 2006 - Modification du positionnement par défaut de La barre d'outils "Modélisation".
    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 23,
                                Title,
                                NUMELEMENTS( modelisationButtons ),
                                modelisationButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,    // AFX_IDW_DOCKBAR_RIGHT devient AFX_IDW_DOCKBAR_TOP
                                AFX_IDW_TOOLBAR + 20,    // NextTo. NULL devient AFX_IDW_TOOLBAR + 20.
                                TRUE,                    // Docking
                                TRUE );                    // Show. FALSE devient TRUE.

    // Register BP toolbar
    ZUFloatingToolbar::RegisterToolbar( _ModelisationToolbarName, AFX_IDW_TOOLBAR + 23, this, BerylNotation );

    Title.LoadString( IDS_TB_BPMODELGENERATIONBUTTONS );

    // JMR-MODIF - Le 22 mars 2006 - Modification du positionnement par défaut de La barre d'outils "Génération".
    pMgr->DefineDefaultToolBar( AFX_IDW_TOOLBAR + 24,
                                Title,
                                NUMELEMENTS( modelGenerationButtons ),
                                modelGenerationButtons,
                                CBRS_ALIGN_ANY,
                                AFX_IDW_DOCKBAR_TOP,    // AFX_IDW_DOCKBAR_RIGHT devient AFX_IDW_DOCKBAR_TOP
                                AFX_IDW_TOOLBAR + 23,    // NextTo
                                TRUE,                    // Docking
                                TRUE );                    // Show. FALSE devient TRUE.

    ZUFloatingToolbar::RegisterToolbar( _ModelGenerationToolbarName, AFX_IDW_TOOLBAR + 24, this, BerylNotation );

    // Enable the tooltips
    pMgr->EnableToolTips( TRUE );

    return TRUE;
}

BOOL ZIMainFrame::CreateStatusBar()
{
    if ( !m_wndStatusBar.Create( this ) ||
         !m_wndStatusBar.SetIndicators( indicators, sizeof( indicators ) / sizeof( UINT ) ) )
    {
        TRACE( _T( "Failed to create status bar\n" ) );
        return FALSE;    // Fail to create
    }

    m_wndStatusBar.SetPaneInfo( 3, ID_INDICATOR_PAGE, SBPS_NORMAL, 80 );

    return TRUE;
}

BOOL ZIMainFrame::CreateMenuBars()
{
    ASSERT( m_pControlBarManager != NULL );
    ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );

    SECToolBarManager* pMgr = (SECToolBarManager*)m_pControlBarManager;

    // Used to load menus
    pMgr->SetMenuInfo( 2, IDR_MAINFRAME, IDR_MODEL );

    pMgr->SetMenuMap( menuMap, NUMELEMENTS( menuMap ) );
    pMgr->LayoutMenuBar( NUMELEMENTS( menuButtons ), menuButtons );

    return TRUE;
}

int ZIMainFrame::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( ZIBaseMainFrame::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }

    return 0;
}

BOOL ZIMainFrame::InitializeDockingWindows()
{
    ///////////////////////////////////////////////////
    // Initialize dialog bar m_wndWorkspace
    ///////////////////////////////////////////////////

    // Project Workspace Window
    if ( !m_wndWorkspace.Create( this,
                                 _T( "Espace de travail" ),
                                 CBRS_LEFT | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                 CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                 ID_VIEW_WORKSPACE ) )
    {
        TRACE0( _T( "Failed to create dialog bar m_wndWorkspace\n" ) );
        return -1;
    }

    m_wndWorkspace.Initialize();
    m_wndWorkspace.EnableDocking( CBRS_ALIGN_ANY );
    DockControlBarEx( &m_wndWorkspace, AFX_IDW_DOCKBAR_LEFT, 0, 0, (float)0.80, 220 );
    ShowControlBar( &m_wndWorkspace, TRUE, TRUE );

    ///////////////////////////////////////////////////
    // Initialize dialog bar m_wndPropertiesWorkspace
    ///////////////////////////////////////////////////
    if ( !m_wndPropertiesWorkspace.Create( this,
                                           _T( "Propriétés" ),
                                           CBRS_RIGHT | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                           CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                           ID_VIEW_PROPERTIES ) ) 
    {
        TRACE0( _T( "Failed to create dialog bar m_wndPropertiesWorkspace\n" ) );
        return -1;        // fail to create
    }

    m_wndPropertiesWorkspace.Initialize();
    m_wndPropertiesWorkspace.EnableDocking( CBRS_ALIGN_ANY );
    DockControlBarEx( &m_wndPropertiesWorkspace, AFX_IDW_DOCKBAR_RIGHT, 0, 0, (float)0.80, 220 );
    ShowControlBar( &m_wndPropertiesWorkspace, FALSE, FALSE );

    ///////////////////////////////////////////////////
    // Initialize dialog bar m_wndOutputWorkspace
    ///////////////////////////////////////////////////
    if ( !m_wndOutputWorkspace.Create( this,
                                       _T( "Log" ),
                                       CBRS_BOTTOM | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                       CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                       ID_VIEW_OUTPUTWORKSPACE ) )
    {
        TRACE0( _T( "Failed to create dialog bar m_wndOutputWorkspace\n" ) );
        return -1;        // fail to create
    }

    m_wndOutputWorkspace.Initialize();
    m_wndOutputWorkspace.EnableDocking( CBRS_ALIGN_ANY );
    DockControlBarEx( &m_wndOutputWorkspace, AFX_IDW_DOCKBAR_BOTTOM, 0, 0, (float)0.40, 100 );
    ShowControlBar( &m_wndOutputWorkspace, FALSE, FALSE );

    ///////////////////////////////////////////////////
    // Initialize dialog bar m_wndTipOfDayBar
    ///////////////////////////////////////////////////
    if (!m_wndTipOfDayBar.Create( this,
                                  _T( "Saviez-vous que..." ),
                                  CBRS_BOTTOM | WS_VISIBLE | CBRS_SIZE_DYNAMIC,
                                  CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL | CBRS_EX_BORDERSPACE,
                                  ID_VIEW_TIPOFDAY ) )
    {
        TRACE0( "Failed to create dialog bar m_wndTipOfDayBar\n" );
        return -1;        // fail to create
    }

    m_wndTipOfDayBar.SetURL( IDR_TESTTIP_FILE, AfxGetInstanceHandle() );
    m_wndTipOfDayBar.EnableDocking( CBRS_ALIGN_ANY );
    DockControlBarEx( &m_wndTipOfDayBar, AFX_IDW_DOCKBAR_BOTTOM, 0, 0, (float)0.30, 100 );
    ShowControlBar( &m_wndTipOfDayBar, FALSE, FALSE );

    return TRUE;
}

void ZIMainFrame::OnCustomize()
{
    SECToolBarSheet toolbarSheet;
    SECToolBarsPage toolbarPage;

    toolbarPage.SetManager( (SECToolBarManager*)m_pControlBarManager );
    toolbarSheet.AddPage( &toolbarPage );

    SECToolBarCmdPage cmdPage( SECToolBarCmdPage::IDD, IDS_COMMANDS );
    cmdPage.SetManager( (SECToolBarManager*)m_pControlBarManager );

    // Add button group
    CString Title;
    Title.LoadString( IDS_TB_FILEBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( fileButtons ), fileButtons );

    Title.LoadString( IDS_TB_BROWSEBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( browseButtons ), browseButtons );

    Title.LoadString( IDS_TB_ZOOMBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( zoomButtons ), zoomButtons );

    Title.LoadString( IDS_TB_GRIDBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( gridButtons ), gridButtons );

    Title.LoadString( IDS_TB_DRAWINGBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( drawingButtons ), drawingButtons );

    Title.LoadString( IDS_TB_ROTATIONBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( rotationButtons ), rotationButtons );

    Title.LoadString( IDS_TB_ALIGNBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( alignButtons ), alignButtons );

    Title.LoadString( IDS_TB_ARRANGEBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( arrangeButtons ), arrangeButtons );

    Title.LoadString( IDS_TB_MOVEBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( moveButtons ), moveButtons );

    Title.LoadString( IDS_TB_GROUPBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( groupButtons ), groupButtons );

    Title.LoadString( IDS_TB_WORKSPACEBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( workspaceButtons ), workspaceButtons );

    Title.LoadString( IDS_TB_SIMULATIONBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( modelSimulationButtons ), modelSimulationButtons );

    Title.LoadString( IDS_TB_ATTRIBUTESBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( symbolAttributesButtons ), symbolAttributesButtons );

    Title.LoadString( IDS_TB_BPMODELISATIONBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( modelisationButtons ), modelisationButtons );

    Title.LoadString( IDS_TB_BPMODELGENERATIONBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( modelGenerationButtons ), modelGenerationButtons );

    // **********************************************************************************************************
    // JMR-MODIF - Le 19 octobre 2005 - Ajout de la barre des symboles à la liste de personnalisation.
    Title.LoadString( IDS_TB_BPSYMBOLSBUTTONS );
    cmdPage.DefineBtnGroup( Title, NUMELEMENTS( addSymbolsButtons ), addSymbolsButtons );
    // **********************************************************************************************************

    // Add menu
    cmdPage.DefineMenuGroup( _T( "Menus" ) );

    toolbarSheet.AddPage( &cmdPage );

    toolbarSheet.DoModal();
}

void ZIMainFrame::OnViewToolbar()
{
    ASSERT_KINDOF( SECToolBarManager, m_pControlBarManager );

    if( ( (SECToolBarManager*)m_pControlBarManager )->ExecViewToolBarsDlg() == IDC_TOOLBAR_CUSTOMIZE )
    {
        OnCustomize();
    }
}

void ZIMainFrame::OnUpdateViewToolbar( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( TRUE );
}

void ZIMainFrame::ViewZoomIn()
{
    CDocument* pDoc = GetActiveDocument();

    if ( pDoc && ISA( pDoc, ZDDocument ) )
    {
        int Zoom = ( (ZDDocument*)pDoc )->GetMainView()->GetZoomPercentage() + 25;

        Zoom = __min( 400, Zoom );

        ( (ZDDocument*)pDoc )->GetMainView()->SetZoomPercentage( Zoom );
        ( (ZDDocument*)pDoc )->UpdateAllViews( NULL );
    }
}

void ZIMainFrame::ViewZoomOut()
{
    CDocument* pDoc = GetActiveDocument();

    if ( pDoc && ISA( pDoc, ZDDocument ) )
    {
        int Zoom = ( (ZDDocument*)pDoc )->GetMainView()->GetZoomPercentage() - 25;

        Zoom = __max( 25, Zoom );

        ( (ZDDocument*)pDoc )->GetMainView()->SetZoomPercentage( Zoom );
        ( (ZDDocument*)pDoc )->UpdateAllViews( NULL );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZIMainFrame diagnostics

#ifdef _DEBUG
void ZIMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void ZIMainFrame::Dump( CDumpContext& dc ) const
{
    CMDIFrameWnd::Dump( dc );
}
#endif //_DEBUG

void ZIMainFrame::OnViewFullScreen()
{
    ZIBaseMainFrame::OnViewFullScreen();
}

void ZIMainFrame::OnUpdateViewFullScreen( CCmdUI* pCmdUI )
{
    pCmdUI->SetCheck( ZIBaseMainFrame::IsFullScreen() );
}

void ZIMainFrame::OnViewProjectWindow()
{
    OnBarCheck( ID_VIEW_PROJECTWINDOW );
}

void ZIMainFrame::OnUpdateViewProjectWindow( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_PROJECTWINDOW;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnViewTipOfDayBar()
{
    OnBarCheck( ID_VIEW_TIPOFDAY );
}

void ZIMainFrame::OnUpdateViewTipOfDayBar( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_TIPOFDAY;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnViewHelpContextBar()
{
    OnBarCheck( ID_VIEW_HELPCONTEXT );
}

void ZIMainFrame::OnUpdateViewHelpContextBar( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_HELPCONTEXT;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnViewWorkspace()
{
    OnBarCheck( ID_VIEW_WORKSPACE );
}

void ZIMainFrame::OnUpdateViewWorkspace( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_WORKSPACE;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnViewOutputWorkspace()
{
    OnBarCheck( ID_VIEW_OUTPUTWORKSPACE );
}

void ZIMainFrame::OnUpdateViewOutputWorkspace( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_OUTPUTWORKSPACE;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnViewProperties()
{
    OnBarCheck( ID_VIEW_PROPERTIES );
}

void ZIMainFrame::OnUpdateViewProperties( CCmdUI* pCmdUI )
{
    pCmdUI->m_nID = ID_VIEW_PROPERTIES;
    OnUpdateControlBarMenu( pCmdUI );
}

void ZIMainFrame::OnUpdatePage( CCmdUI *pCmdUI )
{
    pCmdUI->Enable();
    char strPage[50];
    sprintf( strPage, _T( "Page %d/%d" ), m_nPage, m_nTotalPage );
    pCmdUI->SetText( strPage );
}

afx_msg LRESULT ZIMainFrame::OnDocumentLoaded( WPARAM wParam, LPARAM lParam )
{
    ZIObserverMsg* pMsg = (ZIObserverMsg*)lParam;

    if ( pMsg && ISA( pMsg, ZBDocObserverMsg ) )
    {
        ZBDocObserverMsg* pDocMsg = (ZBDocObserverMsg*)pMsg;

        if ( pDocMsg->GetpDoc() )
        {
            // Attach process workspace as observer
            pDocMsg->GetpDoc()->AttachObserver( GetWorkspace() );
            pDocMsg->GetpDoc()->AttachObserver( GetPropertiesWorkspace() );
            pDocMsg->GetpDoc()->AttachObserver( GetOutputWorkspace() );

            GetOutputWorkspace()->AttachObserver( pDocMsg->GetpDoc() );

            pDocMsg->GetpDoc()->Initialize( GetOutputWorkspace()->GetLogView(),
                                            GetOutputWorkspace()->GetLogAnalyzerView(),
                                            GetOutputWorkspace()->GetLogSearchView(),
                                            GetOutputWorkspace()->GetLogWorkflowView(),
                                            NULL,        // User manager
                                            NULL,        // Mail
                                            NULL );        // Template manager
        }
    }

    return 1;
}

void ZIMainFrame::OnClose()
{
    if ( ZAApp::ZAGetApp()->ExitAppl() )
    {
        // JMR-MODIF - Le 30 août 2005 - Sauvegarde de l'état de l'environnement avant la destruction.
        if ( ZIBaseMainFrame::MustSaveBarState() )
        {
            ZIBaseMainFrame::OnSaveBarState();
        }

        // JMR-MODIF - Le 29 août 2005 - Ajout du code de nettoyage dans la fonction OnClose.
        m_wndWorkspace.Release();
        m_wndOutputWorkspace.Release();
        m_wndPropertiesWorkspace.Release();

        ZIBaseMainFrame::OnClose();
    }
}
