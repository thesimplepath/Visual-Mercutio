// mainfrm.h : interface of the ZIMainFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(__DSGNFRM_H)
#define __DSGNFRM_H

// processsoft
#include "zBaseLib\PSS_BaseMainFrame.h"
#include "zWinUtil32\PSS_ProjectBar.h"
#include "zTip\PSS_TipOfDayBar.h"
#include "zTip\PSS_HelpContextBar.h"
#include "zBaseLib\ZISubject.h"
#include "ZVProcessWorkspace.h"
#include "ZVOutputWorkspace.h"
#include "ZVPropertiesWorkspace.h"

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorartions unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZIMainFrame : public PSS_BaseMainFrame
{
    DECLARE_DYNAMIC( ZIMainFrame )

public:

    ZIMainFrame();

    // Return the workspace reference
    ZVProcessWorkspace* GetWorkspace()
    {
        return &m_wndWorkspace;
    };

    // Return the output workspace reference
    ZVOutputWorkspace* GetOutputWorkspace()
    {
        return &m_wndOutputWorkspace;
    };

    // Return the output workspace reference
    ZVPropertiesWorkspace* GetPropertiesWorkspace()
    {
        return &m_wndPropertiesWorkspace;
    };

    PSS_ProjectBar& GetProjectWindowBar()
    {
        return m_ProjectWindowBar;
    };

    PSS_TipOfDayBar& GetwndTipOfDayBar()
    {
        return m_wndTipOfDayBar;
    };

    virtual void OnReloadBarState( bool Reset = false );
    virtual void OnSaveBarState();

    // Call back for Zoom In&Out
    virtual void ViewZoomIn();
    virtual void ViewZoomOut();

// Operations
public:

// Implementation
public:

    virtual ~ZIMainFrame();
    
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
    ////////////////////////////////////////////////////////////
    // Menu and Toolbar pure virtual functions
    
    // CreateToolBars function must be implemented by the derived class
    // it lets the user create all the toolbars
    virtual BOOL CreateToolBars();

    // CreateMainStatusBar function mus be implement by the derived class
    // it lets the user create the main status bar
    virtual BOOL CreateStatusBar();

    // CreateMenuBars function mus be implement by the derived class
    // it lets the user create the all the menus
    virtual BOOL CreateMenuBars();

    // InitializeDockingWindows function must be implement by the derived class
    // it lets the user initializing all docking windows
    virtual BOOL InitializeDockingWindows();

protected:

    // Generated message map functions
    //{{AFX_MSG(ZIMainFrame)
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    afx_msg void OnUpdatePage(CCmdUI *pCmdUI);
    afx_msg void OnViewFullScreen();
    afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
    afx_msg void OnViewProjectWindow();
    afx_msg void OnUpdateViewProjectWindow(CCmdUI* pCmdUI);
    afx_msg void OnViewTipOfDayBar();
    afx_msg void OnUpdateViewTipOfDayBar(CCmdUI* pCmdUI);
    afx_msg void OnViewHelpContextBar();
    afx_msg void OnUpdateViewHelpContextBar(CCmdUI* pCmdUI);
    afx_msg void OnViewWorkspace();
    afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
    afx_msg void OnViewOutputWorkspace();
    afx_msg void OnUpdateViewOutputWorkspace(CCmdUI* pCmdUI);
    afx_msg void OnViewProperties();
    afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
    afx_msg void OnCustomize();
    afx_msg void OnViewToolbar();
    afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
    afx_msg LRESULT OnDocumentLoaded( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnDDEExecute( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_ProjectBar        m_ProjectWindowBar;
    PSS_TipOfDayBar       m_wndTipOfDayBar;
    ZVProcessWorkspace    m_wndWorkspace;
    ZVOutputWorkspace     m_wndOutputWorkspace;
    ZVPropertiesWorkspace m_wndPropertiesWorkspace;
};

#endif // __DSGNFRM_H
/////////////////////////////////////////////////////////////////////////////