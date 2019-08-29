/****************************************************************************
 * ==> PSS_TemplateView ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template view                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateViewH
#define PSS_TemplateViewH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZITreeView.h"
#include "PSS_TemplateTree.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Template view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateView : public ZITreeView
{
    DECLARE_DYNCREATE(PSS_TemplateView)

    public:
        /**
        * Initializes the template view
        *@param pTemplateManager - template manager
        *@param includeFiles - if TRUE, files will be included
        */
        virtual void Initialize(ZDTemplateManager* pTemplateManager, BOOL includeFiles);

        /**
        * Re-initializes the template view
        *@param pTemplateManager - template manager
        *@param includeFiles - if TRUE, files will be included
        */
        virtual void ReInitialize(ZDTemplateManager* pTemplateManager, BOOL includeFiles);

        /**
        * Refreshes the template view
        */
        virtual void Refresh();

        /**
        * Gets the selected item name
        *@return the selected item name
        */
        virtual CString GetSelectedItemName();

        /**
        * Gets the selected item folder
        *@return the selected item folder
        */
        virtual PSS_TemplateDir* GetSelectedItemFolder();

        /**
        * Gets the selected item file
        *@return the selected item file
        */
        virtual PSS_TemplateFile* GetSelectedItemFile();

        /**
        * Selects the item name
        *@param name - item name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectItemName(const CString& name);

        /**
        * Called when selection changed
        */
        virtual void OnSelChangedEvent();

        /**
        * Called when view is clicked
        */
        virtual void OnClickEvent();

        /**
        * Called when view is double-clicked
        */
        virtual void OnDblClickEvent();

        /**
        * Called when view is right clicked
        */
        virtual void OnRightClickEvent();

        /**
        * Called when view is right double-clicked
        */
        virtual void OnRightDblClickEvent();

    protected:
        PSS_TemplateTree   m_TemplateTree;
        ZDTemplateManager* m_pTemplateManager;
        BOOL               m_IncludeFiles;

        PSS_TemplateView();
        virtual ~PSS_TemplateView();

        /**
        * Gets the no-drop image index
        *@return the no-drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_TemplateView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_TemplateView)
        afx_msg LRESULT OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnReloadTemplateManager(WPARAM wParam, LPARAM lParam);
        afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

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
};

//---------------------------------------------------------------------------
// PSS_TemplateView
//---------------------------------------------------------------------------
int PSS_TemplateView::GetIndexOfNoDropImage() const
{
    return 2;
}
//---------------------------------------------------------------------------

#endif
