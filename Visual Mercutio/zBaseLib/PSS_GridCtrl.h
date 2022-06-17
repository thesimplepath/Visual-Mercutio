/****************************************************************************
 * ==> PSS_GridCtrl --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid controller                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridCtrlH
#define PSS_GridCtrlH

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

// mfc
#include <afxtempl.h>

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
* Grid controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridCtrl : public CListCtrl
{
    public:
        /**
        * Tree item rectangle
        */
        class IRectangle
        {
            public:
                /**
                * Constructor
                *@param pCtrl - control
                *@param pDC - device context
                *@param indent - indent
                *@param rect - rectangle
                */
                IRectangle(PSS_GridCtrl* pCtrl, CDC* pDC, int indent, const CRect& rect);

                virtual ~IRectangle();

                /**
                * Draws the rectangle
                *@param pCtrl - control
                */
                virtual void DrawRectangle(PSS_GridCtrl* pCtrl);

                /**
                * Draws the plus symbol
                */
                virtual void DrawPlus();

                /**
                * Draws the minus symbol
                */
                virtual void DrawMinus();

                /**
                * Gets the rectangle left edge
                *@return the rectangle left edge
                */
                virtual inline int GetLeft() const;

                /**
                * Gets the rectangle top edge
                *@return the rectangle top edge
                */
                virtual inline int GetTop() const;

                /**
                * Gets the hit test rectangle
                *@return the hit test rectangle
                */
                virtual inline CRect GetHitTestRect() const;

                /**
                * Checks if a point hit the rectangle
                *@param pt - point to check
                *@return TRUE if the point hit the rectangle, otherwise FALSE
                */
                virtual BOOL HitTest(const CPoint& pt) const;

            private:
                CDC*  m_pDC;
                POINT m_LeftTop;
                SIZE  m_RightBottom;
                int   m_TopDown;
                int   m_Left;
                int   m_Top;
        };

        /**
        * Tree item info
        */
        class IItemInfo
        {
            public:
                /**
                * Control type enumeration
                */
                enum class IEControlType
                {
                    IE_CT_Edit,
                    IE_CT_ComboBox,
                    IE_CT_DateControl,
                    IE_CT_SpinButton,
                    IE_CT_DropDownListViewWhatEverControl
                };

                IItemInfo();
                virtual ~IItemInfo();

                /**
                * Gets the item text
                *@return the item text
                */
                virtual inline const CString& GetItemText();

                /**
                * Sets the item text
                *@param item - item text
                */
                virtual inline void SetItemText(const CString& item);

                /**
                * Sets the item text
                *@param item - item text
                *@param color - background color
                */
                virtual inline void SetItemText(const CString& item, COLORREF color);

                /**
                * Adds a sub-item text
                *@param subItem - sub-item text to set
                */
                virtual inline void AddSubItemText(const CString& subItem);

                /**
                * Adds a sub-item text
                *@param subItem - sub-item text to set
                *@param color - background color
                */
                virtual inline void AddSubItemText(const CString& subItem, COLORREF color);

                /**
                * Gets the sub-item text
                *@param index - sub-item index
                *@return the sub-item text, empty string if not found or on error
                */
                virtual inline CString GetSubItem(int index);

                /**
                * Sets a sub-item text at index
                *@param index - index
                *@param subItem - sub-item text to set
                *@param image - image index
                */
                virtual inline void SetSubItemText(int index, const CString& subItem, int image);

                /**
                * Sets a sub-item text at index
                *@param index - index
                *@param subItem - sub-item text to set
                */
                virtual inline void SetSubItemText(int index, const CString& subItem);

                /**
                * Sets a sub-item text at index
                *@param index - index
                *@param subItem - sub-item text to set
                *@param color - background color
                */
                virtual inline void SetSubItemText(int index, const CString& subItem, COLORREF color);

                /**
                * Sets a sub-item image at index
                *@param index - index
                *@param image - image index
                */
                virtual inline void SetSubItemImage(int index, int image);

                /**
                * Gets the item count
                *@return the item count
                */
                virtual inline int GetItemCount() const;

                /**
                * Gets the control type
                *@param col - column
                *@param[out] - control type to populate
                *@return TRUE on success, otherwise FALSE
                */
                virtual inline BOOL GetControlType(int nCol, IEControlType& controlType) const;

                /**
                * Sets the control type
                *@param ctrlType - control type to set
                *@param col - column, if -1 the default control type for all columns will be changed
                *@note By default, all column control types are set to IE_CT_Edit
                */
                virtual inline void SetControlType(IEControlType ctrlType, int col = -1);

                /**
                * Gets the data list
                *@param subItemIndex - sub-item index to get from
                *@param[out] pList - data list to populate
                *@return TRUE on success, otherwise FALSE
                */
                virtual inline BOOL GetListData(int subItemIndex, CStringList*& pList) const;

                /**
                * Sets the data list
                *@param subItemIndex - sub-item index to set to
                *@param pInitArr - initial array
                */
                virtual inline void SetListData(int subItemIndex, CStringList* pInitArr);

                /**
                * Gets the check state
                *@return the check state
                *@note Used only with LVS_EX_CHECKBOXES style
                */
                virtual inline BOOL GetCheck() const;

                /**
                * Sets the check state
                *@param value - the check state
                *@note Used only with LVS_EX_CHECKBOXES style
                */
                virtual inline void SetCheck(BOOL value);

                /**
                * Gets the icon image index in tree column
                *@return the icon image index in tree column
                */
                virtual inline int GetImage() const;

                /**
                * Sets the icon image index in tree column
                *@param index - the icon image index in tree column
                */
                virtual inline void SetImage(int index);

                /**
                * Gets the sub-item image index
                *@param index - sub-item index
                *@return the sub-item image index
                */
                virtual inline int GetSubItemImage(int index) const;

                /**
                * Gets the item background color
                *@return the item background color
                */
                virtual inline COLORREF GetBkColor() const;

                /**
                * Gets the sub-item background color
                *@param index - sub-item index to get from
                *@return the sub-item background color
                */
                virtual inline COLORREF GetBkColor(int index) const;

                /**
                * Copies the objects from another item info
                *@param pItemInfo - item info to copy from
                *@note You should modify this when you add new data to this class
                */
                virtual void CopyObjects(IItemInfo* pItemInfo);

                /**
                * Copies the sub-item image list content from another item info
                *@param pItemInfo - item info to copy from
                */
                virtual void CopySubItemImageList(IItemInfo* pItemInfo);

                /**
                * Copies the controls from another item info
                *@param pItemInfo - item info to copy from
                */
                virtual void CopyControls(IItemInfo* pItemInfo);

                /**
                * Copies the colors from another item info
                *@param pItemInfo - item info to copy from
                */
                virtual void CopyColors(IItemInfo* pItemInfo);

            private:
                CMap<int, int, IEControlType, IEControlType&> m_ControlTypes;
                CMap<int, int, COLORREF, COLORREF&>           m_Colors;
                CMap<int, int, CStringList*, CStringList*>    m_ListData;
                CMap<int, int, int, int&>                     m_ImageSubItems;
                IEControlType                                 m_EnumCtrlType;
                LPARAM                                        m_LParam; // NOTE why not use this like used in listbox, listctrl...
                COLORREF                                      m_Color;
                CString                                       m_ItemName;
                CStringArray                                  m_SubItems;
                int                                           m_Image;
                BOOL                                          m_Check;
        };

        /**
        * Tree item
        */
        class IItem : public CObject
        {
            friend PSS_GridCtrl;

            public:
                IItem();
                virtual ~IItem();

            private:
                IItem*     m_pParent;
                IItemInfo* m_pNodeInfo;
                CObList    m_ListChild;
                int        m_Index;
                int        m_Indent;
                int        m_SetChildFlag;
                BOOL       m_HideChildren;
        };

        PSS_GridCtrl();
        virtual ~PSS_GridCtrl();

        /**
        * Copies the data
        *@param pSource - dource data to copy from
        *@return copied item info data
        *@note Used in drag/drop operations
        *@note MUST override this to make a copy of CItemInfo... see the CMySuperGrid.cpp for implementation
        */
        virtual IItemInfo* CopyData(IItemInfo* pSrc);

        /**
        * Gets the icon state
        *@param pItem - tree item
        *@return icon state
        *@note Called from within DrawItem returns valid image index
        *@note You MUST override this function to set your current icon, must of course be a valid CImageList index
        */
        virtual int GetIcon(const IItem* pItem) const;

        /**
        * Get the current cell color
        *@return the current cell color
        */
        virtual COLORREF GetCellRGB() const;

        /**
        * Inserts the root item
        *@param pRoot - root item info
        *@return the newly created item, NULL on error
        *@note The root item info will be deleted internally and should no longer be deleted from outside
        */
        virtual IItem* InsertRootItem(IItemInfo* pRoot);

        /**
        * Deletes the root item
        *@param pRoot - root item
        */
        virtual void DeleteRootItem(IItem* pRoot);

        /**
        * Checks if an item is the root item
        *@param pITem - item to check
        *@return TRUE if an item is the root item, otherwise FALSE
        */
        virtual BOOL IsRoot(IItem* pItem) const;

        /**
        * Gets the root item
        *@param index - item index
        *@return the root item, NULL if not found or on error
        */
        virtual IItem* GetRootItem(int index);

        /**
        * Gets the root count
        *@return the root count
        */
        virtual inline int GetRootCount();

        /**
        * Deletes all the items
        */
        virtual void DeleteAll();

        /**
        * Gets the previous node from a node
        *@param pRoot - root node
        *@param pNode - node to search from
        *@param init - if TRUE, the search will be initialized, otherwise it will continue since the last known point
        *@param dontIncludeHidden - if TRUE, the hidden items will not be included in the search
        *@return the previous node from the node, NULL if no previous node or on error
        */
        virtual IItem* GetPrev(IItem* pRoot, IItem* pNode, BOOL init = TRUE, BOOL dontIncludeHidden = TRUE);

        /**
        * Gets the next node from a node
        *@param pRoot - root node
        *@param pNode - node to search from
        *@param init - if TRUE, the search will be initialized, otherwise it will continue since the last known point
        *@param dontIncludeHidden - if TRUE, the hidden items will not be included in the search
        *@return the previous node from the node, NULL if no previous node or on error
        */
        virtual IItem* GetNext(IItem* pRoot, IItem* pNode, BOOL init = TRUE, BOOL dontIncludeHidden=TRUE);

        /**
        * Gets the selected item
        *@return the selected item
        */
        virtual int GetSelectedItem() const;

        /**
        * Gets the item at index
        *@param index - item index
        *@return the item, NULL if not found or on error
        *@note Be careful, index must be valid
        */
        virtual IItem* GetTreeItem(int index);

        /**
        * Gets the item count
        *@return the item count
        */
        virtual UINT GetCount() const;

        /**
        * Gets the children count an item contains
        *@param pItem - item
        *@return the children count
        */
        virtual int GetChildrenCount(const IItem* pItem) const;

        /**
        * Checks if the tree item is a child of a parent
        *@param pParent - parent
        *@param pChild - child item to check
        *@return TRUE if the tree item is a child of a parent, otherwise FALSE
        */
        virtual BOOL IsChildOf(const IItem* pParent, const IItem* pChild) const;

        /**
        * Checks if the item contains children
        *@param pItem - item to check
        *@return TRUE if the item contains children, otherwise FALSE
        */
        virtual BOOL ItemHasChildren(const IItem* pItem) const;

        /**
        * Sets if item contains children, but they were were still not inserted yet
        *@param pItem - item to check
        *@param flag - flag
        */
        virtual void SetChildrenFlag(IItem* pItem, int flag) const;

        /**
        * Checks if an item is collapsed
        *@param pItem - item to check
        *@return TRUE if an item is collapsed, otherwise FALSE
        */
        virtual BOOL IsCollapsed(const IItem* pItem) const;

        /**
        * Gets the item indent
        *@param pItem - item
        *@return the item indent
        */
        virtual int GetIndent(const IItem* pItem) const;

        /**
        * Sets the item indent
        *@param pItem - item
        *@param indent - the item indent
        */
        virtual void SetIndent(IItem* pItem, int indent);

        /**
        * Gets the item index
        *@param pItem - item
        *@return the item index
        */
        virtual int GetCurIndex(const IItem* pItem) const;

        /**
        * Sets the item index
        *@param pItem - item
        *@param index - the item index
        */
        virtual void SetCurIndex(IItem* pItem, int index);

        /**
        * Gets the item parent
        *@param pItem - item
        *@return the item parent, NULL if not found or on error
        */
        virtual IItem* GetParentItem(const IItem* pItem);

        /**
        * Sets the item parent
        *@param pItem - item
        *@param pParent - the item parent
        */
        virtual void SetParentItem(IItem* pItem, IItem* pParent);

        /**
        * Gets the item data
        *@param pItem - item
        *@return the item data, NULL if not found or on error
        */
        virtual IItemInfo* GetData(const IItem* pItem);

        /**
        * Updates the item data
        *@param pItem - item
        *@param pInfo - item data to update
        *@param updateRow - if TRUE, the whole item will be invalidated
        */
        virtual void UpdateData(IItem* pItem, IItemInfo* pInfo, BOOL updateRow = FALSE);

        /**
        * Inserts an item
        *@param pParent - parent item
        *@param pInfo - item info
        *@param update - if TRUE, the item will be updated after insertion
        *@return the new parent node, NULL on error
        *@note The item info will be deleted internally and should no longer be deleted from outside
        *@note The update parameter is here for performance reasons, when e.g 100 node are inserted, each having 10 children
        *      (i.e 1000 list view items). The update parameter should be set to FALSE (default) but when an item is inserted,
        *      and it should be visible right away, the update parameter should be set to TRUE. (see the update parameter usage
        *      in the CMySuperGridCtrl::HowToInsertItemsAfterTheGridHasBeenInitialized() function)
        */
        virtual IItem* InsertItem(IItem* pParent, IItemInfo* pInfo, BOOL update = FALSE);

        /**
        * Collapses an item and all its children
        *@param pItem - item to collapse
        */
        virtual void Collapse(IItem* pItem);

        /**
        * Expands an item
        *@param pItem - item to expand
        *@param index - item index
        *@return the expanded folder last index
        */
        virtual int Expand(IItem* pItem, int index);

        /**
        * Expands all items from an item
        *@param pItem - item
        *@param[out] scroll - contains the scroll position on function ends
        *@return the expanded item last index
        */
        virtual void ExpandAll(IItem* pItem, int& scroll);

        /**
        * Expands all nodes in item until the stop item is reached
        *@param pItem - item to expand
        *@param pStopAt - item to stop at
        */
        virtual void ExpandUntil(IItem* pItem, IItem* pStopAt);

        /**
        * Selects a node. If the node is collapsed, all items within the node are expanded and the node is selected
        *@param pLocateNode - the node to locate and select
        *@return the selected node list view index
        */
        virtual int SelectNode(IItem* pLocateNode);

        /**
        * Deletes an item, takes the node to delete and its list view item index
        *@param pItem - item to delete
        *@param index - item index
        *@note The item to delete should be visible, hence the item index as argument
        */
        virtual void DeleteItemEx(IItem* pItem, int item);

        /**
        * Gets the column count
        *@return the column count
        */
        virtual int GetColCount() const;

        /**
        * Performs an items quick sort
        *@param sortChildren - if TRUE, each children will also be sorted
        */
        virtual void SortEx(BOOL sortChildren);

        /**
        * Performs an item quick sort
        *@param pParent - parent item to sort
        *@param sortChildren - if TRUE, each children will also be sorted
        */
        virtual void Sort(IItem* pParent, BOOL sortChildren);

        /**
        * Gets the head position
        *@param pItem - item
        *@return the head position, NULL if not found or on error
        */
        virtual POSITION GetHeadPosition(IItem* pItem) const;

        /**
        * Gets the tail position
        *@param pItem - item
        *@return the tail position, NULL if not found or on error
        */
        virtual POSITION GetTailPosition(IItem* pItem) const;

        /**
        * Gets the previous child item
        *@param pItem - item
        *@param[in, out] pPos - item position
        *@return the previous child item, NULL if not found or on error
        */
        virtual IItem* GetPrevChild(IItem* pItem, POSITION& pPos) const;

        /**
        * Gets the next child item
        *@param pItem - item
        *@param[in, out] pPos - item position
        *@return the next child item, NULL if not found or on error
        */
        virtual IItem* GetNextChild(IItem *pItem, POSITION& pPos) const;

        /**
        * Gets the root head position
        *@return the root head position, NULL if not found or on error
        */
        virtual POSITION GetRootHeadPosition() const;

        /**
        * Gets the root tail position
        *@return the root tail position, NULL if not found or on error
        */
        virtual POSITION GetRootTailPosition() const;

        /**
        * Gets the previous root position
        *@param pPos - position
        *@param[in, out] pos - root position
        *@return the previous root position, NULL if not found or on error
        */
        virtual IItem* GetPrevRoot(POSITION& pPos) const;

        /**
        * Gets the next root position
        *@param pPos - position
        *@param[in, out] pPos - root position
        *@return the next root position, NULL if not found or on error
        */
        virtual IItem* GetNextRoot(POSITION& pPos) const;

        /**
        * Adds a tail item
        *@param pParent - parent item to add to
        *@param pChild - child item to add
        */
        virtual void AddTail(IItem* pParent, IItem* pChild);

        /**
        * Invalidates the item
        *@param item - item index
        *@note The index should be valid, because it will not be checked before used
        */
        virtual void InvalidateItemRect(int index);

        /**
        * Invalidates the item
        *@param pItem - item
        */
        virtual void InvalidateItemRect(IItem* pItem);

        /**
        * Invalidates the item content
        *@param pItem - item
        */
        virtual void InvalidateItem(IItem* pItem);

        /**
        * Called when list view items are updated
        *@param pItem - item
        *@param pLvItem - list view item
        */
        virtual void OnUpdateListViewItem(IItem* pItem, LV_ITEM* pLvItem);

        /**
        * Called when left mouse button is down above a cell
        *@param flags - flags
        *@param point - clicked point
        *@param hitTest - hit test info
        */
        virtual void OnControlLButtonDown(UINT flags, const CPoint& point, LVHITTESTINFO& hitTest);

        /**
        * Called when a drag image should be provided. By default creates an image and a text
        *@param index - item index
        *@return the image list
        */
        virtual CImageList* CreateDragImageEx(int index);

        /**
        * Called before item is about to explode
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent expanding
        */
        virtual BOOL OnItemExpanding(IItem* pItem, int index);

        /**
        * Called after item was expanded
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent expanding
        */
        virtual BOOL OnItemExpanded(IItem* pItem, int index);

        /**
        * Called before item is collapsed
        *@param pItem - item
        *@return TRUE to continue, FALSE to prevent collapse
        */
        virtual BOOL OnItemCollapsing(IItem* pItem);

        /**
        * called after item was collapsed
        *@param pItem - item
        *@return TRUE to continue, FALSE to prevent collapse
        */
        virtual BOOL OnItemCollapsed(IItem* pItem);

        /**
        * Called when item is about to be deleted
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent the item to be deleted
        */
        virtual BOOL OnDeleteItem(IItem* pItem, int index);

        /**
        * Called before VK_ADD key down is processed
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent to expand item
        */
        virtual BOOL OnVKAdd(IItem* pItem, int index);

        /**
        * Called before VK_SUBTRACT key down is pocessed
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent to collapse item
        */
        virtual BOOL OnVkSubtract(IItem* pItem, int index);

        /**
        * Called before VK_MULTIPLY key down is pocessed
        *@param pItem - item
        *@param index - item index
        *@return TRUE to continue, FALSE to prevent to expand all
        */
        virtual BOOL OnVKMultiply(IItem* pItem, int index);

        /**
        * Called when other controls than edit control should be handled
        *@return TRUE to continue, FALSE to prevent to expand item
        */
        virtual BOOL OnVkReturn();

        /**
        * Called before OnLButtonDown and OnDblclk events are processed
        *@param hitTest - hit test info
        *@return TRUE to continue, FALSE to prevent the item to be selected
        */
        virtual BOOL OnItemLButtonDown(LVHITTESTINFO& hitTest);

        /**
        * Called before editing the cell
        *@param item - item index
        *@param subItem - sub-item index
        */
        virtual void OnBeginLabelEdit(int item, int subItem);

        /**
        * Called after the cell was updated
        *@param pText - text
        *@param item - item index
        *@param subItem - sub-item index
        */
        virtual void OnEndLabelEdit(LPCSTR pText, int item, int subItem);

    protected:
        int m_CxImage;
        int m_CyImage;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_GridCtrl)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridCtrl)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnTimer(UINT nIDEvent);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
        afx_msg void OnSysColorChange();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the root index
        *@param pRoot - root item
        *@return the root index
        */
        virtual int GetRootIndex(IItem* lpRoot);

        /**
        * Delete an item and all of its children
        *@param pItem - item to delete
        *@param clean - if TRUE, item data will also be deleted
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Delete(IItem* pItem, BOOL clean = TRUE);

        /**
        * Copies item children
        *@param pDest - destination item
        *@param pSrc - source item
        */
        virtual void CopyChildren(IItem* pDest, IItem* pSrc);

        /**
        * Called when the drag&drop should be performed
        *@param pTarget - drop target
        *@param pItem - dragged item
        *@return TRUE if the drag&drop operation may continue, otherwise FALSE
        */
        virtual BOOL DoDragDrop(IItem* pTarget, IItem* pItem);

        /**
        * Internally updates the nodes
        */
        virtual void InternalUpdateTree();

        /**
        * Get the node index
        *@param pNode - node
        *@return the index
        */
        virtual int NodeToIndex(IItem* pNode);

        /**
        * Checks if the user clicked the [+] [-] symbols, also handles LVS_EX_CHECKBOXES
        *@param point - clicked point
        *@param hitTest - hit test info
        *@return TRUE if the user clicked the [+] [-] symbols, otherwise FALSE
        */
        virtual BOOL HitTestOnSign(const CPoint& point, LVHITTESTINFO& hitTest);

        /**
        * Creates an edit control
        *@param item - item index
        *@param col - column
        *@return the newly created edit control, NULL on error
        */
        virtual CEdit* EditLabelEx(int item, int col);

        /**
        * Gets a column order value from a column index value
        *@param index - index
        *@return the column order value
        */
        virtual int IndexToOrder(int index);

        /**
        * Sets the item hide flag
        *@param pItem - item
        *@param value - flag value
        */
        virtual void Hide(IItem* pItem, BOOL value);

        /**
        * Gets the currently selected sub-item index
        *@return the currently selected sub-item index
        */
        virtual inline int GetCurSubItem();

        /**
        * Gets the drag item
        *@return the drag item
        */
        virtual inline int GetDragItem() const;

        /**
        * Gets the drop target item
        *@return the drop target item
        */
        virtual inline int GetDropTargetItem() const;

        /**
        * Gets the sub-item image list
        *@param pImageList - the sub-item image list to populate
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetSubItemImageList(CImageList* pImageList = NULL);

    private:
        CPtrList   m_RootItems;
        CImageList m_SubItemImages;
        CBrush     m_BrushErase;
        CPen       m_PenTreeLine;
        CPen       m_PenRectangle;
        CPen       m_PenPlusMinus;
        HIMAGELIST m_hImageList;
        int        m_CurSubItem;
        int        m_DragItem;
        int        m_DragTarget;
        BOOL       m_IsDragging;

        /**
        * Deletes items from a start item
        *@param pStartAt - item from which delete should start
        *@param pItem - item
        *@param clean - if TRUE, item data will also be deleted
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Delete(IItem* pStartAt, IItem* pItem, BOOL clean = TRUE);

        /**
        * Gets the item count
        *@param item - item
        *@param[out] count - item count on function ends
        *@return the item count
        */
        UINT GetCount(IItem* pItem, UINT& count) const;

        /**
        * Draws the tree item
        *@param pDC - device context to draw to
        *@param pItem - item to draw
        *@param index - item index
        *@param rect - item surrounding rectangle
        */
        void DrawTreeItem(CDC* pDC, IItem* pItem, int index, const CRect& rect);

        /**
        * Draws the cell focus
        *@param pDC - device context to draw to
        *@param item - item index
        *@param subItem - sub-item index
        *@param iconOffset - icon offset
        */
        void DrawFocusCell(CDC* pDC, int item, int subItem, int iconOffset);

        /**
        * Draws the down arrow of an item containing a combobox
        *@param pDC - device context to draw to
        *@param pItem - item
        *@param index - item index
        *@param column - column
        *@param subIconOffset - sub-icon offset
        */
        void DrawComboBox(CDC* pDC, IItem* pItem, int index, int column, int subIconOffset);

        /**
        * Makes a string shorter
        *@param pDC - device context to use for measurements
        *@param pLong - long string to make shorter
        *@param columnLen - column length
        *@param offset - offset
        *@return the shorter string
        */
        LPCTSTR MakeShortString(CDC* pDC, LPCTSTR pLong, int columnLen, int offset);

        /**
        * Sets the hide flag for an item and all its children
        *@param pItem - item
        *@param hide - if TRUE, the item and its children will be hidden
        *@param indent - item indent
        */
        void HideChildren(IItem* pItem, BOOL hide, int indent);

        /**
        * Checks whether a column is visible and scrolls to it if yes
        *@param col - column
        */
        void MakeColumnVisible(int col);

        /**
        * Compares children items for sorting
        *@param pItem1 - first item to compare
        *@param pItem2 - second item to compare
        *@return
        */
        static int CompareChildren(const void* pItem1, const void* pItem2);

        /**
        * Clears the item
        *@param pItem - item to clear
        */
        void Clear(IItem* pItem);

        /**
        * Gets the index matching with an item
        *@param pStartPos - start position where the search should begin
        *@param pItem - item
        *@param[out] index - item index on function ends
        *@param init - if TRUE, the search will be initialized, otherwise it will continue since the last known point
        *@return the item index
        */
        int NodeToIndex(IItem* pStartPos, IItem* pItem, int& index, BOOL init = TRUE);
};

//---------------------------------------------------------------------------
// PSS_GridCtrl::IRectangle
//---------------------------------------------------------------------------
int PSS_GridCtrl::IRectangle::GetLeft() const
{
    return m_Left;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::IRectangle::GetTop() const
{
    return m_Top;
}
//---------------------------------------------------------------------------
CRect PSS_GridCtrl::IRectangle::GetHitTestRect() const
{
    return CRect(m_LeftTop, m_RightBottom);
}
//---------------------------------------------------------------------------
// PSS_GridCtrl::IItemInfo
//---------------------------------------------------------------------------
const CString& PSS_GridCtrl::IItemInfo::GetItemText()
{
    return m_ItemName;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetItemText(const CString& item)
{
    m_ItemName = item;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetItemText(const CString& item, COLORREF color)
{
    m_ItemName = item; m_Color = color;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::AddSubItemText(const CString& subItem)
{
    m_SubItems.Add(subItem);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::AddSubItemText(const CString& subItem, COLORREF color)
{
    const int index = m_SubItems.Add(subItem);
    m_Colors.SetAt(index, color);
}
//---------------------------------------------------------------------------
CString PSS_GridCtrl::IItemInfo::GetSubItem(int index)
{
    if (index < m_SubItems.GetSize())
        return m_SubItems.GetAt(index);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetSubItemText(int index, const CString& subItem, int image)
{
    m_SubItems.SetAtGrow(index, subItem);
    m_ImageSubItems.SetAt(index, image);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetSubItemText(int index, const CString& subItem)
{
    m_SubItems.SetAtGrow(index, subItem);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetSubItemText(int index, const CString& subItem, COLORREF color)
{
    m_SubItems.SetAtGrow(index, subItem);
    m_Colors.SetAt(index, color);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetSubItemImage(int index, int image)
{
    m_ImageSubItems.SetAt(index, image);
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::IItemInfo::GetItemCount() const
{
    return m_SubItems.GetSize();
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IItemInfo::GetControlType(int nCol, IEControlType& controlType) const
{
    if (!m_ControlTypes.Lookup(nCol, controlType))
    {
        controlType = IEControlType::IE_CT_Edit;
        return 0;
    }

    return 1;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetControlType(IEControlType ctrlType, int col)
{
    m_ControlTypes.SetAt(col, ctrlType);
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IItemInfo::GetListData(int subItemIndex, CStringList*& pList) const
{
    return m_ListData.Lookup(subItemIndex, pList);
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetListData(int subItemIndex, CStringList* pInitArr)
{
    std::unique_ptr<CStringList> pList(new CStringList());
    pList->AddTail(pInitArr);
    m_ListData.SetAt(subItemIndex, pList.get());

    // will be deleted in destructor
    pList.release();
}
//---------------------------------------------------------------------------
BOOL PSS_GridCtrl::IItemInfo::GetCheck() const
{
    return m_Check;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetCheck(BOOL value)
{
    m_Check = value;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::IItemInfo::GetImage() const
{
    return m_Image;
}
//---------------------------------------------------------------------------
void PSS_GridCtrl::IItemInfo::SetImage(int index)
{
    m_Image = index;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::IItemInfo::GetSubItemImage(int index) const
{
    int subImage = -1;
    m_ImageSubItems.Lookup(index, subImage);
    return subImage;
}
//---------------------------------------------------------------------------
COLORREF PSS_GridCtrl::IItemInfo::GetBkColor() const
{
    return m_Color;
}
//---------------------------------------------------------------------------
COLORREF PSS_GridCtrl::IItemInfo::GetBkColor(int index) const
{
    COLORREF color;

    if (!m_Colors.Lookup(index, color))
        return COLORREF(-1);

    return color;
}
//---------------------------------------------------------------------------
// PSS_GridCtrl
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetRootCount()
{
    return m_RootItems.GetCount();
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetCurSubItem()
{
    return m_CurSubItem;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetDragItem() const
{
    return m_DragItem;
}
//---------------------------------------------------------------------------
int PSS_GridCtrl::GetDropTargetItem() const
{
    return m_DragTarget;
}
//---------------------------------------------------------------------------

#endif
