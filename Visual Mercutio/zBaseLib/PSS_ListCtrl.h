/****************************************************************************
 * ==> PSS_ListCtrl --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic list controller                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ListCtrlH
#define PSS_ListCtrlH

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
* Generic list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ListCtrl : public CListCtrl
{
    public:
        PSS_ListCtrl();
        virtual ~PSS_ListCtrl();

        /**
        * Initializes the flat header
        *@return 0 on success, -1 on error
        */
        virtual int InitializeFlatHeader();

        /**
        * Sorts the text items
        *@param col - column to sort
        *@param ascending - if TRUE, the sorting will be performed in the ascending order
        *@param low - low index where the sorting will start
        *@param high - high index where the sorting will end
        */
        virtual BOOL SortTextItems(int col, BOOL ascending, int low = 0, int high = -1);

        /**
        * Sets the extended style
        *@param newStyle - new extended style to set
        */
        virtual void SetExtendedStyle(DWORD newStyle);

        /**
        * Builds the columns
        *@param cols - column count
        *@param pWidth - column width array
        *@param pColString - column string array
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BuildColumns(int cols, int* pWidth, int* pColString);

        /**
        * Auto-sizes the column
        *@param column - column index
        */
        virtual void AutoSizeColumn(int column);

        /**
        * Enables the sorting
        *@param value - if TRUE, the sorting will be enabled
        */
        virtual inline void EnableSort(BOOL value = TRUE);

        /**
        * Loads the image list
        *@param id - image list resource identifier
        *@param size - image size in pixels
        *@param grow - the number of images to add everytime the image list should be resized
        *@param maskColor - the mask color
        */
        virtual void LoadImageList(UINT id, int size, int grow, COLORREF maskColor);

        /**
        * Loads the image list
        *@param startID - index containing the the first image to load from resources
        *@param endID - index containing the the last image to load from resources
        *@param flags - flags
        *@param cx - image width
        *@param cy - image height
        */
        virtual void LoadImageList(UINT startID, UINT endID = 0, UINT flags = ILC_COLOR, int cx = 16, int cy = 16);

        /**
        * Loads the masked image list
        *@param startID - index containing the the first image to load from resources
        *@param endID - index containing the the last image to load from resources
        *@param cx - image width
        *@param cy - image height
        */
        virtual void LoadImageListMasked(UINT startID, UINT endID = 0, int cx = 16, int cy = 16);

        /**
        * Sets the header bitmap
        *@param col - column index
        *@param bitmapID - bitmap index in resources
        *@param remove
        */
        virtual void SetHeaderBitmap(int col, int bitmapID, DWORD remove);

        /**
        * Sets the enable over style
        *@param value - if TRUE, the enable over style will be enabled
        */
        virtual void SetEnableOver(BOOL value = TRUE);

        /**
        * Sets the enable edit label style
        *@param value - if TRUE, the enable edit label style will be enabled
        */
        virtual void SetEnableEditLabel(BOOL value = TRUE);

        /**
        * Sets the full row select style
        *@param value - if TRUE, the full row select style
        */
        virtual void SetFullRowSelect(BOOL value = TRUE);

        /**
        * Sets the hot cursor
        *@param hCursor - cursor
        */
        virtual inline void SetHotCursor(HCURSOR hCursor);

        /**
        * Deletes all the items
        *@param deleteImageList - if TRUE, the image list will also be deleted
        */
        virtual BOOL DeleteAllItems(BOOL deleteImageList = FALSE);

        /**
        * De-selects all the items
        */
        virtual void DeSelectAll();

        /**
        * Sets the current selection
        *@param index - selection index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetCurSel(std::size_t Index);

    protected:
        CCJFlatHeaderCtrl m_HeaderCtrl;
        CImageList*       m_pImageList;
        CString           m_Section;
        CString           m_Control;
        int               m_SortedCol;
        BOOL              m_EnableOver;
        BOOL              m_FullRowSelect;
        BOOL              m_SortAscending;
        BOOL              m_SaveColumnState;
        BOOL              m_EnableSort;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ListCtrl)
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ListCtrl)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDestroy();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_ListCtrl
//---------------------------------------------------------------------------
void PSS_ListCtrl::EnableSort(BOOL value)
{ 
    m_EnableSort = value; 
}
//---------------------------------------------------------------------------
void PSS_ListCtrl::SetHotCursor(HCURSOR hCursor)
{
    CListCtrl::SetHotCursor(hCursor);
}
//---------------------------------------------------------------------------

#endif
