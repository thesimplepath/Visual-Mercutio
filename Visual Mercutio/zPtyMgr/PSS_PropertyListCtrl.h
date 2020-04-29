/****************************************************************************
 * ==> PSS_PropertyListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a property list controller                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyListCtrlH
#define PSS_PropertyListCtrlH

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
#include "zProperty\PSS_InPlaceEdit.h"
#include "zProperty\PSS_PropertyItem.h"
#include "PSS_PropertyItemManager.h"

// forward class declaration
class PSS_Properties;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Property list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyListCtrl : public CDragListBox,
                                           public PSS_Subject,
                                           public PSS_Observer
{
    friend class PSS_PropertyItemManager;

    DECLARE_DYNAMIC(PSS_PropertyListCtrl)

    public:
        /**
        * Constructor
        *@param pIniFile - the initalization file
        */
        PSS_PropertyListCtrl(LPCTSTR pIniFile = NULL);

        virtual ~PSS_PropertyListCtrl();

        /**
        * Initializes the controller
        *@param pProps - the properties
        *@param pIniFile - the initalization file
        */
        virtual void Initialize(PSS_Properties* pProps = NULL, LPCTSTR pIniFile = NULL);

        /**
        * Initializes the controller
        *@param propSet - the property set
        *@param pIniFile - the initalization file
        */
        virtual void Initialize(PSS_Properties::IPropertySet& propSet, LPCTSTR pIniFile = NULL);

        /**
        * Loads the states from the initialization file
        *@param pIniFile - the initalization file
        */
        virtual void LoadStateFromIniFile(const CString& iniFile);

        /**
        * Refreshes the controller
        *@param deleteEditCtrl - if true, the edited control will be deleted
        *@param reloadControlData - if true, the control data will be reloaded
        */
        virtual void Refresh(bool deleteEditCtrl = true, bool reloadControlData = false);

        /**
        * Redraws all the items in the controller
        */
        virtual void RedrawAll();

        /**
        * Empties the controller
        */
        virtual void Empty();

        /**
        * Sets the show type
        *@param type - the show type
        */
        virtual inline void SetShowType(PSS_PropertyItemManager::IEPropertyShowType type);

        /**
        * Checks if the property list is read-only
        *@return true if the property list is read-only, otherwise false
        */
        virtual inline bool IsListInReadOnly() const;

        /**
        * Sets the property list as read-only
        *@param valuze - if true, the property list is read-only
        */
        virtual inline void SetListInReadOnly(bool value = true);

        /**
        * Gets the category tab
        *@param index - the category index
        *@return the category tab, NULL if not found or on error
        */
        virtual inline PSS_PropertyItemCategory* GetCategoryTab(int index) const;

        /**
        * Adds a new tab
        *@param pTabName - the tab name
        *@return the newly added tab, NULL on error
        */
        virtual inline PSS_PropertyItemCategory* AddNewTab(LPCTSTR pTabName);

        /**
        * Gets the matching property item
        *@param pPropItem - the property item with which the property to find should match
        *@return the matching property item, NULL if not found or on error
        */
        virtual inline PSS_Property* GetMatchingProperty(PSS_PropertyItem* pPropItem);

        /**
        * Checks the controller state
        */
        virtual void CheckState();

        /**
        * Updates the control data
        *@param pData - the data to update
        *@return true on success, otherwise false
        */
        virtual inline bool UpdateControlData(const PSS_Properties* pData);

        /**
        * Updates the property data
        *@param pPropItem - the property item to update, if NULL all items will be updated
        *@return true on success, otherwise false
        */
        virtual inline bool UpdatePropertyData(PSS_PropertyItem* pPropItem = NULL) const;

        /**
        * Checkes the current property data
        *@param pPropItem - the property item to update
        *@param[in, out] proposedValue - the proposed value, updated value on check ends
        *@return true if the data check succeeded, otherwise false
        */
        virtual inline bool CheckCurrentPropertyData(PSS_PropertyItem* pPropItem, CString& proposedValue);

        /**
        * Processes the extended current property data
        *@param pPropItem - the property item to update
        *@param[in, out] proposedValue - the proposed value, updated value on check ends
        *@param refresh - if true, the item will be refreshed
        */
        virtual inline bool ProcessExtendedCurrentPropertyData(PSS_PropertyItem* pPropItem, CString& proposedValue, bool& refresh);

        /**
        * Processes the menu command current property data
        *@param menuCmdID - the menu command identifier
        *@param pPropItem - the property item to update
        *@param[in, out] proposedValue - the proposed value, updated value on check ends
        *@param refresh - if true, the item will be refreshed
        */
        virtual inline bool ProcessMenuCommandCurrentPropertyData(int               menuCmdID,
                                                                  PSS_PropertyItem* pPropItem,
                                                                  CString&          proposedValue,
                                                                  bool&             refresh);

        /**
        * Saves the property state
        *@param pPropItem - the property item to save
        *@return true on success, otherwise false
        */
        virtual inline bool SavePropertyState(PSS_PropertyItem* pPropItem);

        /**
        * Saves the property state
        *@param pPropCategoryItem - the property category item to save
        *@return true on success, otherwise false
        */
        virtual inline bool SavePropertyState(PSS_PropertyItemCategory* pPropCategoryItem);

        /**
        * Sets the property state to the property
        *@param pPropItem - the property item to set
        *@return true on success, otherwise false
        */
        virtual inline bool SetPropertyStateToProperty(PSS_PropertyItem* pPropItem);

        /**
        * Sets the property state to the property
        *@param pPropCategoryItem - the property category item to set
        *@return true on success, otherwise false
        */
        virtual inline bool SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropCategoryItem);

        /**
        * Gets the property state
        *@param pPropItem - the property item to get
        *@return the property state, NULL if not found or on error
        */
        virtual inline PSS_PropertyItemManager::IPropertyState* GetPropertyState(PSS_PropertyItem* pPropertyItem);

        /**
        * Gets the property state
        *@param pPropCategoryItem - the property category item to get
        *@return the property state, NULL if not found or on error
        */
        virtual inline PSS_PropertyItemManager::IPropertyState* GetPropertyCategoryState(PSS_PropertyItemCategory* pPropCategoryItem);

        /**
        * Sets the property item manager
        *@param pPropItemManager - the property item manager to set
        */
        virtual void SetPropertyItemManager(PSS_PropertyItemManager* pPropItemManager);

        /**
        * Gets the current property item
        *@return the current property item, NULL if no selection or on error
        */
        virtual PSS_PropertyItem* GetCurrentPropertyItem();

        /**
        * Gets the current property item
        *@param index - the item index
        *@return the current property item, NULL if no selection or on error
        */
        virtual PSS_PropertyItem* GetPropertyItem(int index);

        /**
        * Inserts a property item
        *@param pPropItem - the property item to insert
        *@param index - the item index to insert to
        */
        virtual inline void InsertPropertyItem(PSS_PropertyItem* pPropItem, int index = 0);

        /**
        * Deletes a property item
        *@param pPropItem - the property item to delete
        */
        virtual void DeletePropertyItem(PSS_PropertyItem* pPropItem);

        /**
        * Deletes a property item
        *@param index - the item index to delete
        */
        virtual inline void DeletePropertyItem(int index);

        /**
        * Resets the content
        *@param deleteEditCtrl - if true, the edit control will also be deleted
        */
        virtual void ResetContent(bool deleteEditCtrl = true);

        /**
        * Shows the in-place controls
        *@param show - if true, the in-place controls will be shown
        */
        virtual void ShowInPlaceControl(bool show = true);

        /**
        * Called when the data changed
        *@param pPropItem - the property item containing the data
        *@param index - the property index
        *@param refresh - if true, the item will be refreshed
        */
        virtual inline void OnDataChanged(PSS_PropertyItem* pPropItem, int index, bool& refresh);

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PropertyListCtrl)
        virtual void PreSubclassWindow();
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual inline void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        virtual inline int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PropertyListCtrl)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg LONG OnKeyPressed(WPARAM wParam, LPARAM lParam);
        afx_msg void OnSelChange();
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Begins a drag operation
        *@param point - the drag point in pixels
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BeginDrag(CPoint pt);

        /**
        * Called when an item was dropped
        *@param srcIndex - the dropped item source index
        *@param point - the drop point in pixels
        */
        virtual void Dropped(int srcIndex, CPoint pt);

        /**
        * Detaches the observer from the edit control
        */
        virtual void DetachObserverForEditCtrl();

        /**
        * Creates an in-place control
        *@param item - the item index
        *@param previousItem - the previous item index
        */
        virtual void CreateInPlaceControl(int item, int previousItem = -1);

        /**
        * Edits the previous item
        */
        virtual void EditPreviousItem();

        /**
        * Edits the next item
        */
        virtual void EditNextItem();

        /**
        * Called when an item should be collapsed
        *@param pPropertyItemTab - the property item tab
        *@param item - the item index to collapse
        */
        virtual void DoCollapse(PSS_PropertyItemCategory* pPropertyItemTab, int item);

        /**
        * Called when an item should be expanded
        *@param pPropertyItemTab - the property item tab
        *@param[in, out] item - the item index to extend, the extended item index when extended
        */
        virtual void DoExpand(PSS_PropertyItemCategory* pPropertyItemTab, int& item);

        /**
        * Called when an item should be toggled between the extended and collapsed state
        *@param item - the item index to collapse
        *@param pPropertyItem - the property item to expand or collapse
        */
        virtual void DoCollapseExpand(int item, PSS_PropertyItem* pPropertyItem = NULL);

        /**
        * Gets the item value rectangle
        *@param[out] rect - the item value rectangle
        */
        virtual void GetItemValueRect(CRect& rect);

        /**
        * Sets the current data
        *@return true on success, otherwise false
        */
        virtual bool SetCurrentData();

        /**
        * Deletes any opened in-place control
        */
        virtual void NoInPlaceControl();

        /**
        * Checks if the property list is in phase with the model
        *@return true if the property list is in phase with the model, otherwise false
        */
        virtual bool IsListInPhase();

        /**
        * Lookup for property item
        *@param startChar - the first char to find
        *@return true if matching property item was found, otherwise false
        */
        virtual bool LookupPropertyItem(char startChar);

        /**
        * Searches for a property item
        *@param startChar - the first char to find
        *@param fromIndex - the index from which the search should begin
        *@param count - the search count
        *@return the property item, -1 if not found or on error
        */
        virtual int SearchPropertyItem(char startChar, int fromIndex, int count);

        /**
        * Redraws an item
        *@param item - the item index to redraw
        */
        virtual void RedrawItem(int item);

    private:
        PSS_InPlaceEdit*         m_pWndInPlaceControl;
        PSS_PropertyItemManager* m_pPropItemManager;
        PSS_Properties*          m_pCurrentProps;
        PSS_PropertyItem*        m_pSrcDragPropItem;
        HCURSOR                  m_hCurSplitter;
        CFont                    m_Font;
        CFont                    m_FontBold;
        CString                  m_IniFile;
        int                      m_SplitterX;
        int                      m_SrcDragPropItemIndex;
        int                      m_SelectedItem;
        bool                     m_IniFileLoaded;
        bool                     m_ListInReadOnly;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PropertyListCtrl(const PSS_PropertyListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PropertyListCtrl& operator = (const PSS_PropertyListCtrl& other);
};

//---------------------------------------------------------------------------
// PSS_PropertyListCtrl
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::SetShowType(PSS_PropertyItemManager::IEPropertyShowType type)
{
    if (m_pPropItemManager)
        m_pPropItemManager->SetShowType(type);
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::IsListInReadOnly() const
{
    return m_ListInReadOnly;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::SetListInReadOnly(bool value)
{
    m_ListInReadOnly = value;
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyListCtrl::GetCategoryTab(int index) const
{
    if (m_pPropItemManager)
        return m_pPropItemManager->GetCategoryTab(index);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyListCtrl::AddNewTab(LPCTSTR pTabName)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->AddNewTab(pTabName);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Property* PSS_PropertyListCtrl::GetMatchingProperty(PSS_PropertyItem* pPropItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->GetMatchingProperty(pPropItem);

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::UpdateControlData(const PSS_Properties* pData)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->UpdateControlData(pData);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::UpdatePropertyData(PSS_PropertyItem* pPropItem) const
{
    if (m_pPropItemManager)
        return m_pPropItemManager->UpdatePropertyData(pPropItem);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::CheckCurrentPropertyData(PSS_PropertyItem* pPropItem, CString& proposedValue)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->CheckCurrentPropertyData(pPropItem, proposedValue);

    // In this case return true, assuming all values entered are correct
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::ProcessExtendedCurrentPropertyData(PSS_PropertyItem* pPropItem, CString& proposedValue, bool& refresh)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->ProcessExtendedCurrentPropertyData(pPropItem, proposedValue, refresh);

    // return false in this case, nothing has been processed, therefore nothing has changed
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::ProcessMenuCommandCurrentPropertyData(int               menuCmdID,
                                                          PSS_PropertyItem* pPropItem,
                                                          CString&          proposedValue,
                                                          bool&             refresh)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->ProcessMenuCommandCurrentPropertyData(menuCmdID,
                                                                         pPropItem,
                                                                         proposedValue,
                                                                         refresh);

    // return true in this case, and assume that all values entered are correct
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::SavePropertyState(PSS_PropertyItem* pPropItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->SavePropertyState(pPropItem);

    // fail
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::SavePropertyState(PSS_PropertyItemCategory* pPropCategoryItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->SavePropertyState(pPropCategoryItem);

    // fail
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::SetPropertyStateToProperty(PSS_PropertyItem* pPropItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->SetPropertyStateToProperty(pPropItem);

    // fail
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PropertyListCtrl::SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropCategoryItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->SetPropertyStateToProperty(pPropCategoryItem);

    // fail
    return false;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState* PSS_PropertyListCtrl::GetPropertyState(PSS_PropertyItem* pPropertyItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->GetPropertyState(pPropertyItem);

    // fail
    return NULL;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState* PSS_PropertyListCtrl::GetPropertyCategoryState(PSS_PropertyItemCategory* pPropCategoryItem)
{
    if (m_pPropItemManager)
        return m_pPropItemManager->GetPropertyCategoryState(pPropCategoryItem);

    // fail
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::InsertPropertyItem(PSS_PropertyItem* pPropItem, int index)
{
    PSS_Assert(pPropItem);
    InsertString(index, LPCTSTR(pPropItem));
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::DeletePropertyItem(int index)
{
    PSS_Assert(index >= 0);
    DeleteString(index);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::OnDataChanged(PSS_PropertyItem* pPropItem, int index, bool& refresh)
{
    if (m_pPropItemManager)
        m_pPropItemManager->OnDataChanged(pPropItem, this, index, refresh);
}
//---------------------------------------------------------------------------
void PSS_PropertyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{}
//---------------------------------------------------------------------------
int PSS_PropertyListCtrl::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
    return 0;
}
//---------------------------------------------------------------------------

#endif
