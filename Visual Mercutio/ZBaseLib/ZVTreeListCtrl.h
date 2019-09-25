/****************************************************************************
 * ==> PSS_TreeListCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a tree list controller                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TreeListCtrlH
#define PSS_TreeListCtrlH

#if _MSC_VER > 1000
    #pragma once
#endif

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <vector>

// processsoft
#include "zBaseLib\ZIListCtrl.h"

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
* Tree list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TreeListCtrl : public ZIListCtrl
{
    public:
        /**
        * Tree list controller info
        */
        class IInfo
        {
            public:
                std::vector<CString> m_Columns;
                LPARAM               m_LParam;
                int                  m_Level;
                int                  m_Image;
                int                  m_Item;
                bool                 m_Collapsed;

                IInfo();
                virtual ~IInfo();
        };

        PSS_TreeListCtrl();
        virtual ~PSS_TreeListCtrl();

        /**
        * Creates the tree list controller
        *@param style - style
        *@param rect - rect
        *@param pParentWnd - parent window, can be NULL
        *@param id - identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(DWORD style, const RECT& rect, CWnd* pParentWnd, UINT id);

        /**
        * Adds an item
        *@param pItem - item name
        *@param imageIndex - image index
        *@param level - level
        *@param lParam - lParam
        *@return newly added item index, -1 on error
        */
        virtual int AddItem(LPCTSTR pItem, int image, int level, LPARAM lParam = NULL);

        /**
        * Sets the item text
        *@param itemIndex - item index
        *@param subItemIndex - sub-item index
        *@param pText - text
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetItemText(int itemIndex, int subItemIndex, LPCTSTR pText);

        /**
        * Gets the message low parameter
        *@param itemIndex - item index
        *@return the message low parameter
        */
        virtual LPARAM GetParam(int itemIndex);

        /**
        * Deletes all the items
        *@param deleteImageList - if TRUE, the image list will also be deleted
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteAllItems(BOOL deleteImageList = FALSE);

    protected:
        std::vector<IInfo> m_TreeCtrl;
        CImageList         m_ILState;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZVTreeListCtrl)
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZVTreeListCtrl)
        afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Adds an item
        *@param itemIndex - item index
        *@param posArray - position in array
        *@param info - item info
        *@return inserted item index, -1 on error
        */
        virtual int InsertItem(int itemIndex, int posArray, IInfo& info);

        /**
        * Collapses an item
        *@param pos - position
        *@param itemIndex - item index
        */
        virtual void Collapse(int pos, int itemIndex);

        /**
        * Expands an item
        *@param itemIndex - item index
        *@param recursive - if true, the sub-item will also be expanded
        *@param counterInsert - counter insert
        */
        virtual int Expand(int itemIndex, bool recursive, int& counterInsert);
};

#endif
