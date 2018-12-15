// basrfrm.h : interface of the ZIBaseMainFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(__BASEFRM_H)
#define __BASEFRM_H

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "aniload.h"

// For access to SECCustomToolBar
#include "palette.h"

#include "zBaseLib\ZConfigW.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef __CREATE_LOGO_

/////////////////////////////////////////////////////////////////////////////
// MainMDIClient window

class MainMDIClient : public CWnd
{
// Construction / Destruction
public:

    MainMDIClient();
    virtual ~MainMDIClient();

// Implementation
private:

    void DisplayLogo( CDC *pDC );

protected:

    // Generated message map functions
    //{{AFX_MSG(MainMDIClient)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:

    // For the subclassing
    WNDPROC *GetSuperWndProcAddr();
};

#endif // __CREATE_LOGO_

class AFX_EXT_CLASS ZIBaseMainFrame : public SECMDIFrameWnd
{
    DECLARE_DYNAMIC( ZIBaseMainFrame )

public:

    ZIBaseMainFrame( bool MustSaveBarState = true );
    virtual ~ZIBaseMainFrame();

    ////////////////////////////////////////////////////////////
    // Bar State management functions
    void SetMustSaveBarState( bool MustSaveBarState )
    {
        m_MustSaveBarState = MustSaveBarState;
    }

    bool MustSaveBarState() const
    {
        return m_MustSaveBarState;
    }

    virtual void OnReloadBarState( bool Reset = false );
    virtual void OnSaveBarState();

    ZIStatusBar&  GetStatusBar()
    {
        return m_wndStatusBar;
    }

// Attributes
public:

#ifdef __CREATE_LOGO_
    // The MDI Client necessary to subclassing
    // the Main Frame
    MainMDIClient m_MDIClient;
#endif // __CREATE_LOGO_

// Operations
public:

#ifdef __CREATE_LOGO_
    int CreateClient( LPCREATESTRUCT lpCreateStruct, CMenu *pMenu );
#endif // __CREATE_LOGO_

    void LoadMenuBar( UINT nIDMenu );

    void SetPageNumber( int iPage, int iTotalPage )
    {
        m_nPage            = iPage;
        m_nTotalPage    = iTotalPage;
    }

    // Full Screen functionality
    void OnViewFullScreen();

    BOOL IsFullScreen()
    {
        return m_FSView.GetFSMode();
    }

    virtual BOOL PointerWindowIsVisible()
    {
        return FALSE;
    }

    virtual void ShowPointerWindow()
    {
    }

    virtual void HidePointerWindow()
    {
    }

    ZAWindowConfiguration& GetWindowConfiguration();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIBaseMainFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    ////////////////////////////////////////////////////////////
    // Menu and Toolbar pure virtual functions
    
    // CreateToolBars function must be implemented by the derived class
    // it lets the user create all the toolbars
    virtual BOOL CreateToolBars() = 0;

    // CreateMainStatusBar function mus be implement by the derived class
    // it lets the user create the main status bar
    virtual BOOL CreateStatusBar() = 0;

    // CreateMenuBars function mus be implement by the derived class
    // it lets the user create the all the menus
    virtual BOOL CreateMenuBars() = 0;

    // InitializeDockingWindows function must be implement by the derived class
    // it lets the user initializing all docking windows
    virtual BOOL InitializeDockingWindows() = 0;

protected:

    SECCustomToolBar* CreatePaletteBar( UINT    nID,
                                        CPoint    point,
                                        CString    Title            = _T( "" ),
                                        DWORD    dwEnableDocking    = CBRS_ALIGN_ANY );

    SECCustomToolBar* CreatePaletteBar( UINT        nID,
                                        CPoint        point,
                                        const UINT*    lpIDArray    = NULL,
                                        int            nIDCount    = 0,
                                        UINT        nColumns    = 1 );

    SECCustomToolBar* CreateToolBar( UINT nID, CString Title = _T( "" ), DWORD dwEnableDocking = CBRS_ALIGN_ANY );

// Generated message map functions
protected:

    //{{AFX_MSG(ZIBaseMainFrame)
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnViewPointer();
    afx_msg void OnUpdateViewPointer(CCmdUI* pCmdUI);
    afx_msg void OnUpdateHelpIndex(CCmdUI* pCmdUI);
    afx_msg void OnUpdateHelpUsing(CCmdUI* pCmdUI);
    afx_msg void OnClose();
    afx_msg LRESULT OnFSModeChange(WPARAM wPar, LPARAM lPar);
    virtual BOOL OnCommand( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// control bar embedded members
protected:

    ZIStatusBar                m_wndStatusBar;

    SECCustomToolBar*        m_pwndToolBar;

    bool                    m_MustSaveBarState;

    // Represents the page to display
    int                        m_nPage;
    int                        m_nTotalPage;

private:

    bool                    m_SaveBarStateHasBeenInitialized;

    ZAWindowConfiguration    m_WindowConfiguration;

    //Full Screen component
    SECFullScreenView        m_FSView;
};

inline ZAWindowConfiguration& ZIBaseMainFrame::GetWindowConfiguration()
{
    return m_WindowConfiguration;
}

#endif // __BASEFRM_H