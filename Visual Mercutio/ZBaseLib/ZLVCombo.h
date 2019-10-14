/****************************************************************************
 * ==> PSS_ListViewCombo ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a list view combobox                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ListViewComboH
#define PSS_ListViewComboH

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
* List view combobox
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ListViewCombo : public CComboBox
{
    public:
        /**
        * Constructor
        *@param items - item index
        *@param subItem - sub-item index
        *@param pItems - items
        */
        PSS_ListViewCombo(int item, int subItem, CStringList* pItems);

        virtual ~PSS_ListViewCombo();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ListViewCombo)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ListViewCombo)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnNcDestroy();
        afx_msg void OnCloseup();
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CStringList m_Items;
        int         m_Item;
        int         m_SubItem;
        BOOL        m_Escape;
};

#endif
