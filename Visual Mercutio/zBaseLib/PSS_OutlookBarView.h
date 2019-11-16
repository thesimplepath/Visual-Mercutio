/****************************************************************************
 * ==> PSS_OutlookBarView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an Outlook bar view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OutlookBarViewH
#define PSS_OutlookBarViewH

#if _MSC_VER > 1000
    #pragma once
#endif

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Outlook bar view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OutlookBarView : public CView
{
    DECLARE_DYNCREATE(PSS_OutlookBarView)

    public:
        /**
        * Initializes the menu control
        *@param pContents - content items
        *@param contentSize - content size
        *@param pImageListSmall - small image list, can be NULL
        *@param pImageListLarge - large image list, can be NULL
        */
        virtual void InitializeMenuControl(CContentItems* pContents,
                                           std::size_t    contentSize,
                                           CImageList*    pImageListSmall = NULL,
                                           CImageList*    pImageListLarge = NULL);

        /**
        * Changes the context
        *@param context - new context identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ChangeContext(std::size_t context);

    protected:
        CCJOutlookBar m_OutlookBar;
        CCJPagerCtrl  m_Pager;
        CFont         m_Font;
        CRect         m_Rect;

        PSS_OutlookBarView();
        virtual ~PSS_OutlookBarView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZIOutlookBarView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZIOutlookBarView)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg BOOL OnOutbarNotify(WPARAM wParam, LPARAM lParam);
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

#endif
