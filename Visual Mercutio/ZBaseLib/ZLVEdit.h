/****************************************************************************
 * ==> PSS_ListViewEdit ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a list view edit                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ListViewEditH
#define PSS_ListViewEditH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
* List view edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ListViewEdit : public CEdit
{
    public:
        /**
        * Constructor
        *@param item - item
        *@param subItem - sub-item
        *@param initText - initial text
        */
        PSS_ListViewEdit(int item, int subItem, const CString& initText);

        virtual ~PSS_ListViewEdit();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ListViewEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ListViewEdit)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnNcDestroy();
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_InitText;
        int     m_Item;
        int     m_SubItem;
        int     m_X;
        int     m_Y;
        BOOL    m_Escape;
};

#endif
