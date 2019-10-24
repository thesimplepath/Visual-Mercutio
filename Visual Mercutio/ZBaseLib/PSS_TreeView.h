/****************************************************************************
 * ==> PSS_TreeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic tree view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TreeViewH
#define PSS_TreeViewH

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
* Generic tree view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TreeView : public CTreeView
{
    DECLARE_DYNCREATE(PSS_TreeView)

    public:
        /**
        * Enables or disables the drag&drop support
        *@param value - if true, the drag&drop support will be enabled
        */
        virtual inline void DisableDragDrop(bool value = true);

        /**
        * Enables or disables the label edition
        *@param value - if true, the label edition will be enabled
        */
        virtual inline void EditLabels(bool value = true);

        /**
        * Sets if the view can show buttons
        *@param value - if true, the the view can show buttons
        */
        virtual inline void HasButtons(bool value = true);

        /**
        * Sets if the view can show lines
        *@param value - if true, the the view can show lines
        */
        virtual inline void HasLines(bool value = true);

        /**
        * Sets if the view can show lines at root
        *@param value - if true, the the view can show lines at root
        */
        virtual inline void LinesAtRoot(bool value = true);

        /**
        * Sets if the view always shows a selection
        *@param value - if true, the the view always shows a selection
        */
        virtual inline void ShowSelectionAlways(bool value = true);

        /**
        * Sets if the view can show checkboxes
        *@param value - if true, the the view can show checkboxes
        */
        virtual inline void ShowCheckBoxes(bool value = true);

        /**
        * Sets if the view can select tracks
        *@param value - if true, the the view can select tracks
        */
        virtual inline void TrackSelect(bool value = true);

        /**
        * Sets if the view can perform a full row selection on tracks
        *@param value - if true, the the view can perform a full row selection on tracks
        */
        virtual inline void FullRowSelect(bool value = true);

        /**
        * Sets if the view should single expand an item
        *@param value - if true, the the view should single expand an item
        */
        virtual inline void SingleExpand(bool value = true);

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
        * Expands the root item
        *@param deep - if TRUE, the root item children will also be expanded
        */
        virtual void ExpandRoot(BOOL deep = FALSE);

        /**
        * Expands a branch item
        *@param hTreeItem - tree item to expand
        *@param deep - if TRUE, the root item children will also be expanded
        */
        virtual void ExpandBranch(HTREEITEM hTreeItem, BOOL deep = FALSE);

        /**
        * Collapses the root item
        *@param deep - if TRUE, the root item children will also be collapsed
        */
        virtual void CollapseRoot(BOOL deep = FALSE);

        /**
        * Collapses a branch item
        *@param hTreeItem - tree item to expand
        *@param deep - if TRUE, the root item children will also be collapsed
        */
        virtual void CollapseBranch(HTREEITEM hTreeItem, BOOL deep = FALSE);

        /**
        * Selects an item by name
        *@param name - name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectItemName(const CString& name);

        /**
        * Checks if a name matches with the root item
        *@param name - name
        *@return TRUE if the name matches with the root item, otherwise FALSE
        */
        virtual BOOL IsRootItemName(const CString& name);

        /**
        * Checks if a name matches with the last item
        *@param name - name
        *@return TRUE if the name matches with the last item, otherwise FALSE
        */
        virtual BOOL IsLastItemName(const CString& name);

        /**
        * Checks if the selected item is the root one
        *@return TRUE if the selected item is the root one, otherwise FALSE
        */
        virtual BOOL IsSelectedItemRootItem();

        /**
        * Checks if the item name exists
        *@return TRUE if the item name exists, otherwise FALSE
        */
        virtual BOOL ItemNameExist(const CString& name);

        /**
        * Gets the selected item index
        *@param hParentItem - parent item to search from
        *@return the selected item index
        */
        virtual int GetSelectItemPosition(HTREEITEM hParentItem = NULL) const;

        /**
        * Gets the selected item name
        *@return the selected item name
        */
        virtual CString GetNameSelectedItem() const;

        /**
        * Deletes all the items
        *@param deleteImageList - if TRUE, the image list will also be deleted
        */
        virtual void DeleteAllItems(BOOL deleteImageList = FALSE);

        /**
        * Sets the new style
        *@param flags - flags to remove from style
        *@param setBits - if TRUE, the flags will be added instead of removed
        */
        virtual void SetNewStyle(long flags, BOOL setBits);

        /**
        * Transfers an item from a source parent to a destination
        *@param hItem - source item to copy from
        *@param hNewParent - new parent to copy to
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL TransferItem(HTREEITEM hItem, HTREEITEM hNewParent);

        /**
        * Checks if an item is a child of another
        *@param hItemChild - child item to search for
        *@param hItemSuspectedParent - parent item to search from
        *@return TRUE if the item is a child of the suspected parent, otherwise FALSE
        */
        virtual BOOL IsChildNodeOf(HTREEITEM hItemChild, HTREEITEM hItemSuspectedParent);

        /**
        * Gets the previous item
        *@param hItem - item to search from
        *@return the previous item, NULL if not found or on error
        */
        virtual HTREEITEM GetPrevItem(HTREEITEM hItem);

        /**
        * Gets the next item
        *@param hItem - item to search from
        *@return the next item, NULL if not found or on error
        */
        virtual HTREEITEM GetNextItem(HTREEITEM hItem);

        /**
        * Gets the last item
        *@param hItem - item to search from
        *@return the last item, NULL if not found or on error
        */
        virtual HTREEITEM GetLastItem(HTREEITEM hItem);

        /**
        * Finds an item
        *@param str - string to search
        *@param caseSensitive - if TRUE, the search will be case sensitive
        *@param downDir - if TRUE, the search will be performed to the bottom, otherwise to the top
        *@param wholeWord - if TRUE, the search will stop only if the whole word is found
        *@param hItem - item to search from
        *@return matching item, NULL if not found or on error
        */
        virtual HTREEITEM FindItem(const CString& str,
                                   BOOL           caseSensitive = FALSE,
                                   BOOL           downDir = TRUE,
                                   BOOL           wholeWord = FALSE,
                                   HTREEITEM      hItem = NULL);

        /**
        * Finds an item
        *@param label - label to search
        *@param hStartItem - item to search from
        *@return matching item, NULL if not found or on error
        */
        virtual HTREEITEM FindItem(const CString& label, HTREEITEM hStartItem = NULL);

        /**
        * Finds an item
        *@param pData - item data to search
        *@param hStartItem - item to search from
        *@return matching item, NULL if not found or on error
        */
        virtual HTREEITEM FindItemData(void* pData, HTREEITEM hStartItem = NULL);

    protected:
        CWnd*       m_pDropWnd;
        CObject*    m_pDragObj;
        HTREEITEM   m_hItemDrag;
        HTREEITEM   m_hItemDrop;
        HTREEITEM   m_hDragItem;
        CImageList* m_pImageList;
        CImageList* m_pDragImage;
        int         m_DragImageIndex;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_TreeView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_TreeView)
        afx_msg void OnBeginDrag(NMHDR* pnmhdr, LRESULT* pResult);
        afx_msg void OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT* pLResult);
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnDestroy();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        PSS_TreeView();
        virtual ~PSS_TreeView();

        /**
        * Called when the mouse button is up
        *@param point - mouse position
        */
        void OnButtonUp(const CPoint& point);

        /**
        * Checks if find item is valid
        *@param hItem - item to check
        *@return TRUE if find item is valid, otherwise FALSE
        */
        virtual BOOL IsFindValid(HTREEITEM hItem);

        /**
        * Gets the no-drop image index
        *@return the no-drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /**
        * Gets the drag object
        *@param hDragItem - drag item from which the object should be get
        *@return the drag object, NULL if not found or on error
        */
        virtual inline CObject* GetDragObject(HTREEITEM DragItem);

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

    private:
        BOOL m_Dragging;
};

//---------------------------------------------------------------------------
// PSS_TreeView
//---------------------------------------------------------------------------
void PSS_TreeView::DisableDragDrop(bool value)
{
    SetNewStyle(TVS_DISABLEDRAGDROP, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::EditLabels(bool value)
{
    SetNewStyle(TVS_EDITLABELS, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::HasButtons(bool value)
{
    SetNewStyle(TVS_HASBUTTONS, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::HasLines(bool value)
{
    SetNewStyle(TVS_HASLINES, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::LinesAtRoot(bool value)
{
    SetNewStyle(TVS_LINESATROOT, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::ShowSelectionAlways(bool value)
{
    SetNewStyle(TVS_SHOWSELALWAYS, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::ShowCheckBoxes(bool value)
{
    SetNewStyle(TVS_CHECKBOXES, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::TrackSelect(bool value)
{
    SetNewStyle(TVS_TRACKSELECT, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::FullRowSelect(bool value)
{
    SetNewStyle(TVS_FULLROWSELECT, value);
}
//---------------------------------------------------------------------------
void PSS_TreeView::SingleExpand(bool value)
{
    SetNewStyle(TVS_SINGLEEXPAND, value);
}
//---------------------------------------------------------------------------
int PSS_TreeView::GetIndexOfNoDropImage() const
{
    return -1;
}
//---------------------------------------------------------------------------
CObject* PSS_TreeView::GetDragObject(HTREEITEM dragItem)
{
    return (CObject*)GetTreeCtrl().GetItemData(dragItem);
}
//---------------------------------------------------------------------------

#endif
