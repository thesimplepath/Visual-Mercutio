/****************************************************************************
 * ==> PSS_ProjectView -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProjectViewH
#define PSS_ProjectViewH

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
#include "PSS_ProjectTree.h"

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
* Project view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProjectView : public CTreeView
{
    DECLARE_DYNCREATE(PSS_ProjectView)

    public:
        /**
        * Initializes the project view
        *@param visibleOnly - visible only
        */
        virtual void Initialize(BOOL visibleOnly);

    protected:
        PSS_ProjectView();
        virtual ~PSS_ProjectView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProjectView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

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

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProjectView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg LRESULT OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam);
        afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ProjectTree m_ProjectTree;
        BOOL            m_VisibleOnly;
};

#endif
