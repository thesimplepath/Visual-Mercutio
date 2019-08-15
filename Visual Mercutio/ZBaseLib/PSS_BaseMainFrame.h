/****************************************************************************
 * ==> PSS_BaseMainFrame ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic main frame                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BaseMainFrameH
#define PSS_BaseMainFrameH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZConfigW.h"
#include "PSS_StatusBar.h"
#include "PSS_PaletteBar.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

#ifdef __CREATE_LOGO_
    /**
    * Main MDI client frame
    *@author Dominique Aigroz, Jean-Milost Reymond
    */
    class PSS_MainMDIClientFrame : public CWnd
    {
        public:
            PSS_MainMDIClientFrame();
            virtual ~PSS_MainMDIClientFrame();

        protected:
            /// Generated message map functions
            //{{AFX_MSG(PSS_MainMDIClient)
            afx_msg void OnSize(UINT nType, int cx, int cy);
            afx_msg BOOL OnEraseBkgnd(CDC* pDC);
            //}}AFX_MSG
            DECLARE_MESSAGE_MAP()

            /**
            * Gets the super window process address (for the subclassing)
            *@return the super window process address
            */
            virtual WNDPROC* GetSuperWndProcAddr();

        private:
            /**
            * Shows the logo
            *@param pDC - device context
            */
            void ShowLogo(CDC* pDC);
    };
#endif

/**
* Basic main frame window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BaseMainFrame : public SECMDIFrameWnd
{
    DECLARE_DYNAMIC(PSS_BaseMainFrame)

    public:
        #ifdef __CREATE_LOGO_
            PSS_MainMDIClientFrame m_MDIClientFrame; // the MDI client necessary to subclassing the main frame
        #endif

        /**
        * Constructor
        *@param mustSaveBarState - if true, the save bar state will be saved
        */
        PSS_BaseMainFrame(bool mustSaveBarState = true);

        virtual ~PSS_BaseMainFrame();

        /**
        * Sets if the save bar state should be saved
        *@param mustSaveBarState - if true, the save bar state will be saved
        */
        virtual inline void SetMustSaveBarState(bool mustSaveBarState);

        /**
        * Gets if the save bar state should be saved
        *@param mustSaveBarState - if true, the save bar state will be saved
        */
        virtual inline bool GetMustSaveBarState() const;

        /**
        * Called when the bar state is reloaded
        *@param reset - if true, bar state will also be reseted
        */
        virtual void OnReloadBarState(bool reset = false);

        /**
        * Called when the bar state is saved
        */
        virtual void OnSaveBarState();

        /**
        * Gets the status bar
        *@return the status bar
        */
        virtual inline PSS_StatusBar& GetStatusBar();

        #ifdef __CREATE_LOGO_
            /**
            * Creates the client
            *@param pCreateStruct - create structure
            *@param pMenu - menu
            *@return the created client identifier
            */
            virtual int CreateClient(LPCREATESTRUCT pCreateStruct, CMenu* pMenu);
        #endif

        /**
        * Loads the menu bar
        *@param menuID - menu identifier
        */
        virtual void LoadMenuBar(UINT menuID);

        /**
        * Sets the page number
        *@param page - page number
        *@param total - total page
        */
        virtual inline void SetPageNumber(int page, int totalPage);

        /**
        * Called when the full screen is toggled
        */
        virtual void OnViewFullScreen();

        /**
        * Checks if the window is in full screen mode
        *@return TRUE if the window is in full screeen mode, otherwise FALSE
        */
        virtual inline BOOL IsFullScreen();

        /**
        * Checks if the window pointer (i.e the mouse cursor) is visible
        *@return TRUE if the pointer window is visible, otherwise FALSE
        */
        virtual BOOL PointerWindowIsVisible();

        /**
        * Shows the window pointer (i.e the mouse cursor) 
        */
        virtual void ShowPointerWindow();

        /**
        * Hides the window pointer (i.e the mouse cursor) 
        */
        virtual void HidePointerWindow();

        /**
        * Gets the window configuration
        *@return the window configuration
        */
        virtual inline ZAWindowConfiguration& GetWindowConfiguration();

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_BaseMainFrame)
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

    protected:
        PSS_StatusBar     m_StatusBar;
        SECCustomToolBar* m_pToolBar;
        int               m_Page;
        int               m_TotalPage;
        bool              m_MustSaveBarState;

        /**
        * Creates the toolbar
        *@return TRUE on success, otherwise FALSE
        *@note CreateToolBars function must be implemented by the derived class,
        *      it lets the user create all the toolbars
        */
        virtual BOOL CreateToolBars() = 0;

        /**
        * Creates the status bar
        *@return TRUE on success, otherwise FALSE
        *@note CreateMainStatusBar function mus be implement by the derived class,
        *      it lets the user create the main status bar
        */
        virtual BOOL CreateStatusBar() = 0;

        /**
        * Creates the menu bars
        *@return TRUE on success, otherwise FALSE
        *@note CreateMenuBars function mus be implement by the derived class,
        *      it lets the user create the all the menus
        */
        virtual BOOL CreateMenuBars() = 0;

        /**
        * Initializes the docking windows
        *@return TRUE on success, otherwise FALSE
        *@note InitializeDockingWindows function must be implement by the derived class,
        *      it lets the user initializing all docking windows
        */
        virtual BOOL InitializeDockingWindows() = 0;

        /// generated message map
        //{{AFX_MSG(PSS_BaseMainFrame)
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

    private:
        ZAWindowConfiguration m_WindowConfiguration;
        SECFullScreenView     m_FSView;
        bool                  m_SaveBarStateHasBeenInitialized;
};

//---------------------------------------------------------------------------
// PSS_BaseMainFrame
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::SetMustSaveBarState(bool mustSaveBarState)
{
    m_MustSaveBarState = mustSaveBarState;
}
//---------------------------------------------------------------------------
bool PSS_BaseMainFrame::GetMustSaveBarState() const
{
    return m_MustSaveBarState;
}
//---------------------------------------------------------------------------
PSS_StatusBar& PSS_BaseMainFrame::GetStatusBar()
{
    return m_StatusBar;
}
//---------------------------------------------------------------------------
void PSS_BaseMainFrame::SetPageNumber(int page, int totalPage)
{
    m_Page      = page;
    m_TotalPage = totalPage;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseMainFrame::IsFullScreen()
{
    return m_FSView.GetFSMode();
}
//---------------------------------------------------------------------------
ZAWindowConfiguration& PSS_BaseMainFrame::GetWindowConfiguration()
{
    return m_WindowConfiguration;
}
//---------------------------------------------------------------------------

#endif
