/****************************************************************************
 * ==> PSS_PropertyItemManager ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property item manager                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyItemManagerH
#define PSS_PropertyItemManagerH

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
#include "zProperty\PSS_PropertyItem.h"
#include "zProperty\PSS_Properties.h"

// forward class declaration
class PSS_PropertyListCtrl;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Property item manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyItemManager
{
    public:
        /**
        * Property show type
        */
        enum class IEPropertyShowType
        {
            IE_ST_AllProperties,
            IE_ST_StaticProperties,
            IE_ST_DynamicProperties
        };

        /**
        * Keeps the property state for a specific reference. The following attributes are kept:
        * - Collapsed or expanded
        * - Control size
        * - The control extended size
        */
        class IPropertyState
        {
            public:
                inline IPropertyState();

                /**
                * Constructor
                *@param prop - the property
                *@param objectReference - the object reference
                */
                inline IPropertyState(PSS_Property& prop, double objectReference = 0.0);

                /**
                * Constructor
                *@param propItemCat - the property item category
                *@param objectReference - the object reference
                */
                inline IPropertyState(PSS_PropertyItemCategory& propItemCat, double objectReference = 0.0);

                /**
                * Copy constructor
                *@param other - other object to copy from
                */
                inline IPropertyState(const IPropertyState& other);

                virtual inline ~IPropertyState();

                /**
                * Copy operator
                *@param other - other object to copy from
                *@return copy of itself
                */
                inline IPropertyState& operator = (const IPropertyState& other);

                /**
                * Gets the object reference
                *@return the object reference
                */
                virtual inline double GetObjectReference() const;

                /**
                * Sets the object reference
                *@param value - the object reference
                */
                virtual inline void SetObjectReference(double value);

                /**
                * Gets the category identifier
                *@return the category identifier
                */
                virtual inline int GetCategoryID() const;

                /**
                * Sets the category identifier
                *@param value - the category identifier
                */
                virtual inline void SetCategoryID(int value);

                /**
                * Gets the item identifier
                *@return the item identifier
                */
                virtual inline int GetItemID() const;

                /**
                * Sets the item identifier
                *@param value - the item identifier
                */
                virtual inline void SetItemID(int value);

                /**
                * Gets if the item is collapsed
                *@return true if the item is collapsed, otherwise false
                */
                virtual inline bool GetCollapsed() const;

                /**
                * Sets if the item is collapsed
                *@param value - if true, the item is collapsed
                */
                virtual inline void SetCollapsed(bool value);

                /**
                * Gets the item size
                *@return the item size
                */
                virtual inline CSize GetSize() const;

                /**
                * Sets the item size
                *@param value - the item size
                */
                virtual inline void SetSize(const CSize& value);

                /**
                * Gets the item extended size
                *@return the item extended size
                */
                virtual inline CSize GetExtendedSize() const;

                /**
                * Sets the item extended size
                *@param value - the item extended size
                */
                virtual inline void SetExtendedSize(const CSize& value);

                /**
                * Gets the category order
                *@return the category order
                */
                virtual inline int GetCategoryOrder() const;

                /**
                * Sets the category order
                *@param value - the category order
                */
                virtual inline void SetCategoryOrder(int value);

                /**
                * Gets the item order
                *@return the item order
                */
                virtual inline int GetItemOrder() const;

                /**
                * Sets the item order
                *@param value - the item order
                */
                virtual inline void SetItemOrder(int value);

            private:
                CSize  m_Size;
                CSize  m_ExtendedSize;
                double m_ObjectReference;
                int    m_CategoryID;
                int    m_ItemID;
                int    m_CategoryOrder;
                int    m_ItemOrder;
                bool   m_Collapsed;
        };

        typedef CCArray_T <PSS_PropertyItemCategory*, PSS_PropertyItemCategory*> IItemCategorySet;
        typedef Iterator_T<PSS_PropertyItemCategory*>                            IItemCategoryIterator;
        typedef CCArray_T <IPropertyState*, IPropertyState*>                     IPropertyStateSet;
        typedef Iterator_T<IPropertyState*>                                      IPropertyStateIterator;

        inline PSS_PropertyItemManager();
        virtual inline ~PSS_PropertyItemManager();

        /**
        * Empties the manager
        */
        virtual void Empty();

        /**
        * Sets the property list controller
        *@param pCtrl - the property list controller
        */
        virtual void SetPropertyListCtrl(PSS_PropertyListCtrl* pCtrl);

        /**
        * Sets the show type
        *@param type - the show type
        */
        virtual inline void SetShowType(IEPropertyShowType type);

        /**
        * Gets the item category set
        *@return the item category set
        */
        virtual inline       IItemCategorySet& GetItemCategorySet();
        virtual inline const IItemCategorySet& GetItemCategorySet() const;

        /**
        * Gets the category count
        *@return the category count
        */
        virtual inline std::size_t GetCategoryCount() const;

        /**
        * Gets the category tab
        *@return index - the index
        *@return the category tab, NULL if not found or on error
        */
        virtual inline PSS_PropertyItemCategory* GetCategoryTab(int index) const;

        /**
        * Gets the tab
        *@return pPropertyItem - the property item
        *@return the tab, NULL if not found or on error
        */
        virtual PSS_PropertyItemCategory* GetTab(PSS_PropertyItem* pPropertyItem);

        /**
        * Gets the property matching with another one
        *@param pPropertyItem - the property item for which the matching one should be found
        *@return the matching property, NULL if not found or on error
        */
        virtual PSS_Property* GetMatchingProperty(PSS_PropertyItem* pPropertyItem);

        /**
        * Adds a new tab
        *@param pTabName - the tab name
        *@return the newly created tab, NULL on error
        */
        virtual PSS_PropertyItemCategory* AddNewTab(LPCTSTR pTabName);

        /**
        * Checks the state
        *@param fromControlIndex - the from control index
        *@param fromPropertyItemID - the from property item identifier
        */
        virtual void CheckState(int fromControlIndex, BYTE fromPropertyItemID);

        /**
        * Updates the control data
        *@param pData - the control data
        *@return true on success, otherwise false
        */
        virtual bool UpdateControlData(const PSS_Properties* pData);

        /**
        * Updates the control data
        *@param propSet - the property set
        *@return true on success, otherwise false
        */
        virtual bool UpdateControlData(PSS_Properties::IPropertySet& propSet);

        /**
        * Updates the property data
        *@param pPropertyItem - the property item
        *@return true on success, otherwise false
        */
        virtual bool UpdatePropertyData(PSS_PropertyItem* pPropertyItem = NULL);

        /**
        * Checks the current property data
        *@param pPropertyItem - the property item
        *@param[in, out] proposedValue - the proposed value
        *@return true on success, otherwise false
        */
        virtual bool CheckCurrentPropertyData(PSS_PropertyItem* pPropertyItem, CString& proposedValue);

        /**
        * Processes the current extended property data
        *@param pPropertyItem - the property item
        *@param[in, out] proposedValue - the proposed value
        *@param refresh - if true, the item will be refreshed immediately
        */
        virtual bool ProcessExtendedCurrentPropertyData(PSS_PropertyItem* pPropertyItem,
                                                        CString&          proposedValue,
                                                        bool&             refresh);

        /**
        * Processes the current menu command property data
        *@param menuCmdID - the menu command identifier
        *@param pPropertyItem - the property item
        *@param[in, out] proposedValue - the proposed value
        *@param refresh - if true, the item will be refreshed immediately
        */
        virtual bool ProcessMenuCommandCurrentPropertyData(int               menuCmdID,
                                                           PSS_PropertyItem* pPropertyItem,
                                                           CString&          proposedValue,
                                                           bool&             refresh);

        /**
        * Saves the property state
        *@param pPropertyItem - the property item
        */
        virtual bool SavePropertyState(PSS_PropertyItem* pPropertyItem);

        /**
        * Saves the property state
        *@param pPropertyCategoryItem - the property category item
        */
        virtual bool SavePropertyState(PSS_PropertyItemCategory* pPropertyCategoryItem);

        /**
        * Sets the property state to property
        *@param pPropertyItem - the property item
        */
        virtual bool SetPropertyStateToProperty(PSS_PropertyItem* pPropertyItem);

        /**
        * Sets the property state to property
        *@param pPropertyCategoryItem - the property category item
        */
        virtual bool SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropertyCategoryItem);

        /**
        * Gets the property state
        *@param pPropertyItem - the property item
        *@return the property state, NULL if not found or on error
        */
        virtual IPropertyState* GetPropertyState(PSS_PropertyItem* pPropertyItem);

        /**
        * Gets the property category state
        *@param pPropertyCategoryItem - the property category item
        *@return the property category state, NULL if not found or on error
        */
        virtual IPropertyState* GetPropertyCategoryState(PSS_PropertyItemCategory* pPropertyCategoryItem);

        /**
        * Loads the state from initialization file
        *@param iniFile - the initialization file
        *@return true on success, otherwise false
        */
        virtual bool LoadStateFromIniFile(const CString& iniFile);

        /**
        * Saves the state to initialization file
        *@param iniFile - the initialization file
        *@return true on success, otherwise false
        */
        virtual bool SaveStateToIniFile(const CString& iniFile);

        /**
        * Called when the data changed
        *@param pPropertyItem - the property item containing the data
        *@param pWndPropertyListCtrl - the window property list controller
        *@param index - the index
        *@param refresh - if true, the item will be refreshed immediately
        */
        virtual inline void OnDataChanged(PSS_PropertyItem*     pPropertyItem,
                                          PSS_PropertyListCtrl* pWndPropertyListCtrl,
                                          int                   index,
                                          bool&                 refresh);

        /**
        * Called when the internal property item was dropped
        *@param pSrcPropertyItem - the source property item
        *@param pDstPropertyItem - the destination property item
        *@param top2Down - if true, the drag&drop happens from top to down
        *@return true if the item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(PSS_PropertyItem* pSrcPropertyItem,
                                                PSS_PropertyItem* pDstPropertyItem,
                                                bool              top2Down);

    protected:
        IItemCategorySet             m_PropertyItemTabSet;
        IPropertyStateSet            m_PropertyState;
        PSS_Properties::IPropertySet m_PropSet;
        PSS_Properties*              m_pCurrentData;
        PSS_PropertyListCtrl*        m_pWndPropertyListCtrl;

        /**
        * Checks if a tab exists and returns it if yes
        *@param pTabName - the tab name to search
        *@return the tab, NULL if not found or on error
        */
        virtual PSS_PropertyItemCategory* TabExist(LPCTSTR pTabName);

        /**
        * Applies the property changes
        *@return true on success, otherwise false
        */
        virtual bool ApplyPropertyChanges();

    private:
        IEPropertyShowType m_ShowType;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PropertyItemManager(const PSS_PropertyItemManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PropertyItemManager& operator = (const PSS_PropertyItemManager& other);

        /**
        * Updates the control data
        *@return true on success, otherwise false
        */
        bool UpdateControlData();

        /**
        * Creates the property item
        *@param prop - the property
        *@return the newly created property item, NULL on error
        */
        PSS_PropertyItem* CreatePropertyItem(PSS_Property& Prop);

        /**
        * Sets the data to the property item
        *@param pPropertyItem - the property item
        *@param prop - the property
        */
        void SetDataToPropertyItem(PSS_PropertyItem* pPropertyItem, PSS_Property& prop);

        /**
        * Sets the item data to the property
        *@param pPropertyItem - the property item
        *@param prop - the property
        */
        void SetItemDataToProperty(PSS_PropertyItem* pPropertyItem, PSS_Property& prop);

        /**
        * Frees the property set
        */
        void FreePropertySet();

        /**
        * Deletes teh unused tab
        */
        void DeleteUnusedTab();

        /**
        * Deletes all the tabs
        */
        void DeleteAllTabs();

        /**
        * Checks if the tab exists in properties
        *@param pTabName - the tab name to search
        *@return true on success, otherwise false
        */
        bool ExistInPropSet(LPCTSTR pTabName);

        /**
        * Deletes the property state
        */
        void DeletePropertyState();

        /**
        * Sets the initial category order
        */
        void SetInitialCategoryOrder();

        /**
        * Reorders the category
        */
        void ReorderCategory();

        /**
        * Saves all the category orders
        */
        void SaveAllCategoryOrders();

        /**
        * Called when a category is dropped
        *@param pSrcCategoryItem - the source category item
        *@param pDstPropertyItem - the destination category item
        *@param top2Down - if true, the drag&drop happens from top to down
        *@return true if the category was dropped, otherwise false
        */
        bool OnDropCategory(PSS_PropertyItemCategory* pSrcCategoryItem, PSS_PropertyItem* pDstPropertyItem, bool top2Down);
};

//---------------------------------------------------------------------------
// PSS_PropertyItemManager::IPropertyState
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState::IPropertyState() :
    m_ObjectReference(0.0),
    m_CategoryID(-1),
    m_ItemID(-1),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState::IPropertyState(PSS_Property& prop, double objectReference) :
    m_ObjectReference(objectReference),
    m_CategoryID(prop.GetCategoryID()),
    m_ItemID(-1),
    m_CategoryOrder(prop.GetCategoryOrder()),
    m_ItemOrder(prop.GetItemOrder()),
    m_Collapsed(false)
{
    if (prop.GetSaveStatePerProperty())
        m_ItemID = prop.GetItemID();
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState::IPropertyState(PSS_PropertyItemCategory& propItemCat, double objectReference) :
    m_ObjectReference(objectReference),
    m_CategoryID(propItemCat.GetPropertyID()),
    m_ItemID(0),
    m_CategoryOrder(propItemCat.GetCategoryOrder()),
    m_ItemOrder(-1),
    m_Collapsed(!propItemCat.GetChildrenVisible())
{}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState::IPropertyState(const IPropertyState& src) :
    m_ObjectReference(0.0),
    m_CategoryID(-1),
    m_ItemID(0),
    m_CategoryOrder(-1),
    m_ItemOrder(-1),
    m_Collapsed(false)
{
    *this = src;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState::~IPropertyState()
{}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IPropertyState& PSS_PropertyItemManager::IPropertyState::operator = (const IPropertyState& other)
{
    m_Size            = other.GetSize();
    m_ExtendedSize    = other.GetExtendedSize();
    m_ObjectReference = other.GetObjectReference();
    m_CategoryID      = other.GetCategoryID();
    m_ItemID          = other.GetItemID();
    m_CategoryOrder   = other.m_CategoryOrder;
    m_ItemOrder       = other.m_ItemOrder;
    m_Collapsed       = other.GetCollapsed();

    return *this;
}
//---------------------------------------------------------------------------
double PSS_PropertyItemManager::IPropertyState::GetObjectReference() const
{
    return m_ObjectReference;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetObjectReference(double value)
{
    m_ObjectReference = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemManager::IPropertyState::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetCategoryID(int value)
{
    m_CategoryID = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemManager::IPropertyState::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetItemID(int value)
{
    m_ItemID = value;
}
//---------------------------------------------------------------------------
bool PSS_PropertyItemManager::IPropertyState::GetCollapsed() const
{
    return m_Collapsed;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetCollapsed(bool value)
{
    m_Collapsed = value;
}
//---------------------------------------------------------------------------
CSize PSS_PropertyItemManager::IPropertyState::GetSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetSize(const CSize& value)
{
    m_Size = value;
}
//---------------------------------------------------------------------------
CSize PSS_PropertyItemManager::IPropertyState::GetExtendedSize() const
{
    return m_ExtendedSize;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetExtendedSize(const CSize& value)
{
    m_ExtendedSize = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemManager::IPropertyState::GetCategoryOrder() const
{
    return m_CategoryOrder;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetCategoryOrder(int value)
{
    m_CategoryOrder = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyItemManager::IPropertyState::GetItemOrder() const
{
    return m_ItemOrder;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::IPropertyState::SetItemOrder(int value)
{
    m_ItemOrder = value;
}
//---------------------------------------------------------------------------
// PSS_PropertyItemManager
//---------------------------------------------------------------------------
PSS_PropertyItemManager::PSS_PropertyItemManager() :
    m_pCurrentData(NULL),
    m_pWndPropertyListCtrl(NULL),
    m_ShowType(IEPropertyShowType::IE_ST_AllProperties)
{
    DeleteAllTabs();
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::~PSS_PropertyItemManager()
{
    DeleteAllTabs();
    FreePropertySet();
    DeletePropertyState();
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::SetShowType(IEPropertyShowType type)
{
    m_ShowType = type;
}
//---------------------------------------------------------------------------
PSS_PropertyItemManager::IItemCategorySet& PSS_PropertyItemManager::GetItemCategorySet()
{
    return m_PropertyItemTabSet;
}
//---------------------------------------------------------------------------
const PSS_PropertyItemManager::IItemCategorySet& PSS_PropertyItemManager::GetItemCategorySet() const
{
    return m_PropertyItemTabSet;
}
//---------------------------------------------------------------------------
std::size_t PSS_PropertyItemManager::GetCategoryCount() const
{
    return m_PropertyItemTabSet.GetSize();
}
//---------------------------------------------------------------------------
PSS_PropertyItemCategory* PSS_PropertyItemManager::GetCategoryTab(int index) const
{
    return (index < int(GetCategoryCount()) ? m_PropertyItemTabSet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
void PSS_PropertyItemManager::OnDataChanged(PSS_PropertyItem*     pPropertyItem,
                                            PSS_PropertyListCtrl* pWndPropertyListCtrl,
                                            int                   index,
                                            bool&                 refresh)
{
    PSS_Property* pProp = GetMatchingProperty(pPropertyItem);

    // before updating the property, call the pre property change function
    if (pProp)
        // on issue, stop the update process
        if (!m_pCurrentData->OnPrePropertyChanged(pPropertyItem->GetData(), *pProp, m_PropSet))
            return;

    // apply the property changes
    UpdatePropertyData(pPropertyItem);

    // call the post property change function
    if (pProp && m_pCurrentData->OnPostPropertyChanged(*pProp, m_PropSet, refresh))
        ApplyPropertyChanges();
}
//---------------------------------------------------------------------------

#endif
