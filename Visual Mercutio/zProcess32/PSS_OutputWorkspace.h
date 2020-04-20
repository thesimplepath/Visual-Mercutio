/****************************************************************************
 * ==> PSS_OutputWorkspace -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output workspace                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OutputWorkspaceH
#define PSS_OutputWorkspaceH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zModel\PSS_OutputSymbolLogView.h"
#include "zModel\PSS_OutputSearchView.h"
#include "zModel\PSS_OutputAnalyzerLogView.h"
#include "zModel\PSS_OutputWorkflowLogView.h"

//---------------------------------------------------------------------------
// Tab Index constant definition
//---------------------------------------------------------------------------
const int g_SymbolLogTabIndex   = 0;
const int g_SearchLogTabIndex   = 1;
const int g_AnalyzerLogTabIndex = 2;
const int g_WkfLogTabIndex      = 3;
//---------------------------------------------------------------------------

/**
* Output workspace
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_OutputWorkspace : public SECControlBar,
                            public PSS_Subject,
                            public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_OutputWorkspace)

    public:
        PSS_OutputWorkspace();
        virtual ~PSS_OutputWorkspace();

        /**
        * Initializes the workspace
        */
        virtual void Initialize();

        /**
        * Releases the workspace
        */
        virtual void Release();

        /**
        * Clears the logs output
        */
        virtual void ClearLogOutput();

        /**
        * Adds a line in the logs output
        *@param line - the log line to add
        */
        virtual void AddLogLine(const CString& line);

        /**
        * Gets the log view
        *@return the log view
        */
        virtual inline PSS_OutputSymbolLogView* GetLogView();

        /**
        * Activates the symbol log tab
        */
        virtual inline void ActivateSymbolLogTab();

        /**
        * Shows the symbol log tab
        */
        virtual inline void ShowSymbolLogTab();

        /**
        * Hides the symbol log tab
        */
        virtual inline void HideSymbolLogTab();

        /**
        * Gets the search log view
        *@return the search log view
        */
        virtual inline PSS_OutputSearchView* GetSearchLogView();

        /**
        * Activates the search log tab
        */
        virtual inline void ActivateSearchLogTab();

        /**
        * Shows the search log tab
        */
        virtual inline void ShowSearchLogTab();

        /**
        * Hides the search log tab
        */
        virtual inline void HideSearchLogTab();

        /**
        * Gets the analyser log view
        *@return the analyser log view
        */
        virtual inline PSS_OutputAnalyzerLogView* GetAnalyzerLogView();

        /**
        * Activates the analyser log tab
        */
        virtual inline void ActivateAnalyzerLogTab();

        /**
        * Shows the analyser log tab
        */
        virtual inline void ShowAnalyzerLogTab();

        /**
        * Hides the analyser log tab
        */
        virtual inline void HideAnalyzerLogTab();

        /**
        * Gets the workflow log view
        *@return the workflow log view
        */
        virtual inline PSS_OutputWorkflowLogView* GetWorkflowLogView();

        /**
        * Activates the workflow log tab
        */
        virtual inline void ActivateWorkflowLogTab();

        /**
        * Shows the workflow log tab
        */
        virtual inline void ShowWorkflowLogTab();

        /**
        * Hides the workflow log tab
        */
        virtual inline void HideWorkflowLogTab();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_OutputWorkspace)
        virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
        virtual void OnExtendContextMenu(CMenu* pMenu);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_OutputWorkspace)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClearWindow();
        afx_msg void OnSetDebugMode();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        SEC3DTabWnd               m_WndTab;
        PSS_OutputSymbolLogView   m_OutputView;
        PSS_OutputSearchView      m_OutputSearchView;
        PSS_OutputAnalyzerLogView m_OutputAnalyzerView;
        PSS_OutputWorkflowLogView m_OutputWkfView;
};

//---------------------------------------------------------------------------
// PSS_OutputWorkspace
//---------------------------------------------------------------------------
PSS_OutputSymbolLogView* PSS_OutputWorkspace::GetLogView()
{
    return &m_OutputView;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ActivateSymbolLogTab()
{
    m_WndTab.ActivateTab(g_SymbolLogTabIndex);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ShowSymbolLogTab()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::HideSymbolLogTab()
{}
//---------------------------------------------------------------------------
PSS_OutputSearchView* PSS_OutputWorkspace::GetSearchLogView()
{
    return &m_OutputSearchView;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ActivateSearchLogTab()
{
    m_WndTab.ActivateTab(g_SearchLogTabIndex);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ShowSearchLogTab()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::HideSearchLogTab()
{}
//---------------------------------------------------------------------------
PSS_OutputAnalyzerLogView* PSS_OutputWorkspace::GetAnalyzerLogView()
{
    return &m_OutputAnalyzerView;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ActivateAnalyzerLogTab()
{
    m_WndTab.ActivateTab(g_AnalyzerLogTabIndex);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ShowAnalyzerLogTab()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::HideAnalyzerLogTab()
{}
//---------------------------------------------------------------------------
PSS_OutputWorkflowLogView* PSS_OutputWorkspace::GetWorkflowLogView()
{
    return &m_OutputWkfView;
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ActivateWorkflowLogTab()
{
    m_WndTab.ActivateTab(g_WkfLogTabIndex);
}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::ShowWorkflowLogTab()
{}
//---------------------------------------------------------------------------
void PSS_OutputWorkspace::HideWorkflowLogTab()
{}
//---------------------------------------------------------------------------

#endif
