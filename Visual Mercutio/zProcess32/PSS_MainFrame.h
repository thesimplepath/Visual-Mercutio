/****************************************************************************
 * ==> PSS_MainFrame -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the main frame                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MainFrameH
#define PSS_MainFrameH

// processsoft
#include "zBaseLib\PSS_BaseMainFrame.h"
#include "zBaseLib\PSS_Subject.h"
#include "zWinUtil32\PSS_ProjectBar.h"
#include "zTip\PSS_TipOfDayBar.h"
#include "zTip\PSS_HelpContextBar.h"
#include "ZVProcessWorkspace.h"
#include "PSS_OutputWorkspace.h"
#include "ZVPropertiesWorkspace.h"

/**
* Main frame
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MainFrame : public PSS_BaseMainFrame
{
    DECLARE_DYNAMIC(PSS_MainFrame)

    public:
        PSS_MainFrame();
        virtual ~PSS_MainFrame();

        /**
        * Gets the workspace
        *@return the workspace
        */
        virtual inline ZVProcessWorkspace* GetWorkspace();

        /**
        * Gets the output workspace
        *@return the output workspace
        */
        virtual inline PSS_OutputWorkspace* GetOutputWorkspace();

        /**
        * Gets the properties workspace
        *@return the properties workspace
        */
        virtual inline ZVPropertiesWorkspace* GetPropertiesWorkspace();

        /**
        * Gets the project window bar
        *@return the project window bar
        */
        virtual inline PSS_ProjectBar& GetProjectWindowBar();

        /**
        * Gets the tip of the day bar
        *@return the tip of the day bar
        */
        virtual inline PSS_TipOfDayBar& GetwndTipOfDayBar();

        /**
        * Zooms in the view
        */
        virtual void ViewZoomIn();

        /**
        * Zooms out the view
        */
        virtual void ViewZoomOut();

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

        /**
        * Called when the state bar is reloaded
        *@param reset - if true, the state bar was reseted
        */
        virtual void OnReloadBarState(bool reset = false);

        /**
        * Called when the state bar is saved
        */
        virtual void OnSaveBarState();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_BaseMainFrame)
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
        afx_msg LRESULT OnDocumentLoaded(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Creates all the toolbars
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateToolBars();

        /**
        * Creates the main status bar
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateStatusBar();

        /**
        * Creates all the menu bars
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateMenuBars();

        /**
        * Initializes all the docking windows
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeDockingWindows();

    private:
        PSS_ProjectBar        m_ProjectWindowBar;
        PSS_TipOfDayBar       m_WndTipOfDayBar;
        ZVProcessWorkspace    m_WndWorkspace;
        PSS_OutputWorkspace   m_WndOutputWorkspace;
        ZVPropertiesWorkspace m_WndPropertiesWorkspace;
};

//---------------------------------------------------------------------------
// PSS_MainFrame
//---------------------------------------------------------------------------
ZVProcessWorkspace* PSS_MainFrame::GetWorkspace()
{
    return &m_WndWorkspace;
}
//---------------------------------------------------------------------------
PSS_OutputWorkspace* PSS_MainFrame::GetOutputWorkspace()
{
    return &m_WndOutputWorkspace;
}
//---------------------------------------------------------------------------
ZVPropertiesWorkspace* PSS_MainFrame::GetPropertiesWorkspace()
{
    return &m_WndPropertiesWorkspace;
}
//---------------------------------------------------------------------------
PSS_ProjectBar& PSS_MainFrame::GetProjectWindowBar()
{
    return m_ProjectWindowBar;
}
//---------------------------------------------------------------------------
PSS_TipOfDayBar& PSS_MainFrame::GetwndTipOfDayBar()
{
    return m_WndTipOfDayBar;
}
//---------------------------------------------------------------------------

#endif
