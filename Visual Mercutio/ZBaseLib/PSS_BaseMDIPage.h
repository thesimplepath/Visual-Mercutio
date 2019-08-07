/****************************************************************************
 * ==> PSS_BaseMDIPage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic multiple document interface page          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BaseMDIPageH
#define PSS_BaseMDIPageH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "Splitter.h"
#include "PSS_BaseTitleMDIPage.h"
#include "ZIHtmlView.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic multiple document interface page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BaseMDIPage : public PSS_BaseTitleMDIPage
{
    DECLARE_DYNCREATE(PSS_BaseMDIPage)

    public:
        /**
        * Zoom data
        */
        struct IZoom
        {
            char* m_pName;
            int   m_Factor;
        };

        /**
        * Adds a schema
        *@param schema - schema to add
        */
        virtual void AddSchema(const CString& schema);

        /**
        * Removes all the schemas
        */
        virtual void RemoveAllSchema();

        /**
        * Checks if the html view is visible
        *@return TRUE if the html view is visible, otherwise FALSE
        */
        virtual inline BOOL IsHtmlViewVisible() const;

        /**
        * Sets the html view visibility
        *@param value - if TRUE, the html view will be visible
        */
        virtual inline void SetHtmlViewVisible(BOOL value = TRUE);

        /**
        * Sets if the html view should be shown
        *@param show - if TRUE, the html view will be shown
        */
        virtual void ViewHtmlView(BOOL show = TRUE);

        /**
        * Gets if only the html view should be shown
        *@return TRUE if only the html view should be shown, otherwise FALSE
        */
        virtual inline BOOL MustShowOnlyHtmlView() const;

        /**
        * Sets if only the html view should be shown
        *@param value - if TRUE, only the html view will be shown
        */
        virtual inline void SetShowOnlyHtmlView(BOOL value);

    protected:
        ZIHtmlView*     m_pHtmlView;
        CCJToolBar      m_ToolBar;
        CCJFlatComboBox m_Percentage;
        CCJFlatComboBox m_FileList;
        CCJFlatComboBox m_Schema;
        ZISplitter      m_Splitter;
        std::size_t     m_CurrentContext;
        int             m_BaseOffset;
        int             m_IndexDropList;
        int             m_IndexDropListStyle;
        int             m_IndexDropListSchema;
        int             m_IndexDropListFile;
        BOOL            m_IsZoomed;
        BOOL            m_IsIconic;

        PSS_BaseMDIPage();
        virtual ~PSS_BaseMDIPage();

        /**
        * Creates the zoom
        */
        virtual int CreateZoom();

        /**
        * Creates the schema
        */
        virtual int CreateSchema();

        /**
        * Creates the file list
        */
        virtual int CreateFileList();

        /**
        * Changes the context
        *@param context - new context to set
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL ChangeContext(std::size_t context);

        /**
        * Switches the bottom view
        *@param pView - view
        *@return the bottom view, NULL on error
        */
        virtual CView* SwitchBottomView( CView* pView );

        /**
        * Switches the top view
        *@param pView - view
        *@return the top view, NULL on error
        */
        virtual CView* SwitchTopView( CView* pView );

        /**
        * Gets the bottom view
        *@return the bottom view, NULL on error
        */
        virtual CView* GetBottomView();

        /**
        * Gets the top view
        *@return the top view, NULL on error
        */
        virtual CView* GetTopView();

        /// Generated message map functions
        //{{AFX_MSG(PSS_BaseMDIPage)
        afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
        afx_msg void OnViewFullScreen();
        afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
        afx_msg void OnZoomChange();
        afx_msg void OnSchemaChange();
        afx_msg void OnFileChange();
        afx_msg LONG OnFileListChanged(UINT message, LONG lParam);
        afx_msg LONG OnSetDefaultFile(UINT message, LONG wParam);
        afx_msg LONG OnSetDefaultFileOpen(WPARAM wParam, LPARAM lParam);
        afx_msg LONG OnSetDefaultSchema(UINT message, LONG wParam);
        afx_msg LONG OnSchemaHasChanged(UINT message, LONG wParam);
        afx_msg LONG OnNavigateURL(WPARAM wParam, LPARAM lParam);
        afx_msg LONG OnShowHtmlView(WPARAM wParam, LPARAM lParam);
        afx_msg LONG OnHideHtmlView(WPARAM wParam, LPARAM lParam);
        afx_msg void OnClose();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        BOOL m_HasBeenMaximized;
        BOOL m_IsHtmlViewVisible;
        BOOL m_ShowHtmlViewOnly;
};

//---------------------------------------------------------------------------
// PSS_BaseMDIPage
//---------------------------------------------------------------------------
BOOL PSS_BaseMDIPage::IsHtmlViewVisible() const
{
    return m_IsHtmlViewVisible;
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::SetHtmlViewVisible(BOOL value)
{
    m_IsHtmlViewVisible = value;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseMDIPage::MustShowOnlyHtmlView() const
{
    return m_ShowHtmlViewOnly;
}
//---------------------------------------------------------------------------
void PSS_BaseMDIPage::SetShowOnlyHtmlView(BOOL value)
{
    m_ShowHtmlViewOnly = value;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseMDIPage::ChangeContext(std::size_t context)
{
    return FALSE;
}
//---------------------------------------------------------------------------

#endif
