/****************************************************************************
 * ==> PSS_FieldView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldViewH
#define PSS_FieldViewH

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
#include "zBaseLib\PSS_TreeView.h"
#include "PSS_FieldTree.h"

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
* Field view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldView : public PSS_TreeView
{
    DECLARE_DYNCREATE(PSS_FieldView)

    public:
        PSS_FieldView();
        virtual ~PSS_FieldView();

        /**
        * Initializes the view
        *@param pDoc - document
        *@param pFieldRepository - field repository, can be NULL
        */
        virtual void Initialize(PSS_Document* pDoc, PSS_FieldRepository* pFieldRepository = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FieldView)
        virtual void OnDraw(CDC* pDC);
        virtual void PostNcDestroy();
        //}}AFX_VIRTUAL

        /**
        * Gets the no-drop image index
        *@return the no-drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

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
        //{{AFX_MSG(ZIFieldView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg LRESULT OnInitializeFieldRepository(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnReloadFieldList(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnFieldAdded(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnFieldRemoved(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnFieldRenamed(WPARAM wParam, LPARAM lParam);
        afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_Document*        m_pDoc;
        PSS_FieldRepository* m_pFieldRepository;
        PSS_FieldTree        m_FieldTree;
};

//---------------------------------------------------------------------------
// PSS_FieldView
//---------------------------------------------------------------------------
int PSS_FieldView::GetIndexOfNoDropImage() const
{
    return 20;
}
//---------------------------------------------------------------------------

#endif
