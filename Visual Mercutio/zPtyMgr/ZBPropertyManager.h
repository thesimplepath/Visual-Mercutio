// ZBPropertyManager.h : header file

#if !defined(_ZBPropertyManager_H__)
#define _ZBPropertyManager_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zProperty\PSS_PropertyItem.h"
#include "zProperty\PSS_Properties.h"

#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZBPropertyState keeps the state of a property for a specific reference
// If the reference is not kept, we will no search for it.
// We keep the following attributes:
//   - Collapsed or expanded
//   - Control size
//   - The control extended size

class _ZBPropertyState
{
public:

    _ZBPropertyState();
    _ZBPropertyState(PSS_Property& Property, double ObjectReference = 0);
    _ZBPropertyState(PSS_PropertyItemCategory& PropItemCat, double ObjectReference = 0);

    // Allow copy constructor and assignement operator
    _ZBPropertyState(const _ZBPropertyState& src);
    _ZBPropertyState& operator=(const _ZBPropertyState& src);

    double GetObjectReference() const;
    void SetObjectReference(double value);

    int GetCategoryID() const;
    void SetCategoryID(int value);

    int GetItemID() const;
    void SetItemID(int value);

    bool GetCollapsed() const;
    void SetCollapsed(bool value);

    CSize GetSize() const;
    void SetSize(CSize value);

    CSize GetExtendedSize() const;
    void SetExtendedSize(CSize value);

    int GetItemOrder() const;
    void SetItemOrder(int value);

    int GetCategoryOrder() const;
    void SetCategoryOrder(int value);

private:

    // The object reference is used to associate a property to a specific object
    double    m_ObjectReference;

    // The categoryID and the ItemID is used to recognize the right property
    int        m_CategoryID;
    int        m_ItemID;

    bool    m_Collapsed;
    CSize    m_Size;
    CSize    m_ExtendedSize;

    int        m_ItemOrder;
    int        m_CategoryOrder;
};

inline _ZBPropertyState::_ZBPropertyState()
    : m_Size(0, 0),
    m_ExtendedSize(0, 0)
{
    m_CategoryID = -1;
    m_ItemID = -1;
    m_ObjectReference = 0;
    m_Collapsed = false;
    m_ItemOrder = -1;
    m_CategoryOrder = -1;;
}

inline _ZBPropertyState::_ZBPropertyState(PSS_Property& Property, double ObjectReference /*= 0*/)
    : m_Size(0, 0),
    m_ExtendedSize(0, 0)
{
    m_CategoryID = Property.GetCategoryID();

    if (Property.GetSaveStatePerProperty())
    {
        m_ItemID = Property.GetItemID();
    }
    else
    {
        m_ItemID = -1;
    }

    m_ObjectReference = ObjectReference;
    m_Collapsed = false;
    m_ItemOrder = Property.GetItemOrder();
    m_CategoryOrder = Property.GetCategoryOrder();
}

inline _ZBPropertyState::_ZBPropertyState(PSS_PropertyItemCategory& PropItemCat, double ObjectReference /*= 0*/)
    : m_Size(0, 0),
    m_ExtendedSize(0, 0)
{
    m_CategoryID = PropItemCat.GetPropertyID();

    // Sub item equal to zero for categories
    m_ItemID = 0;
    m_ObjectReference = ObjectReference;
    m_Collapsed = !PropItemCat.GetChildrenVisible();
    m_ItemOrder = -1;
    m_CategoryOrder = PropItemCat.GetCategoryOrder();
}

inline _ZBPropertyState::_ZBPropertyState(const _ZBPropertyState& src)
{
    *this = src;
}

inline _ZBPropertyState& _ZBPropertyState::operator=(const _ZBPropertyState& src)
{
    m_CategoryID = src.GetCategoryID();
    m_ItemID = src.GetItemID();
    m_ObjectReference = src.GetObjectReference();

    m_Collapsed = src.GetCollapsed();
    m_Size = src.GetSize();
    m_ExtendedSize = src.GetExtendedSize();

    m_ItemOrder = src.m_ItemOrder;
    m_CategoryOrder = src.m_CategoryOrder;

    return *this;
}

inline double _ZBPropertyState::GetObjectReference() const
{
    return m_ObjectReference;
}

inline void _ZBPropertyState::SetObjectReference(double value)
{
    m_ObjectReference = value;
}

inline int _ZBPropertyState::GetCategoryID() const
{
    return m_CategoryID;
}

inline void _ZBPropertyState::SetCategoryID(int value)
{
    m_CategoryID = value;
}

inline int _ZBPropertyState::GetItemID() const
{
    return m_ItemID;
}

inline void _ZBPropertyState::SetItemID(int value)
{
    m_ItemID = value;
}

inline bool _ZBPropertyState::GetCollapsed() const
{
    return m_Collapsed;
}

inline void _ZBPropertyState::SetCollapsed(bool value)
{
    m_Collapsed = value;
}

inline CSize _ZBPropertyState::GetSize() const
{
    return m_Size;
}

inline void _ZBPropertyState::SetSize(CSize value)
{
    m_Size = value;
}

inline CSize _ZBPropertyState::GetExtendedSize() const
{
    return m_ExtendedSize;
}

inline void _ZBPropertyState::SetExtendedSize(CSize value)
{
    m_ExtendedSize = value;
}

inline int _ZBPropertyState::GetItemOrder() const
{
    return m_ItemOrder;
}

inline void _ZBPropertyState::SetItemOrder(int value)
{
    m_ItemOrder = value;
}

inline int _ZBPropertyState::GetCategoryOrder() const
{
    return m_CategoryOrder;
}

inline void _ZBPropertyState::SetCategoryOrder(int value)
{
    m_CategoryOrder = value;
}

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZCPropertyListCtrl;

/////////////////////////////////////////////////////////////////////////////
// constant declaration
enum PropertyDisplayType
{
    AllProperties,
    StaticProperties,
    DynamicProperties
};

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBItemCategorySet | An array of ZBPropertyItemCategory pointers.
//@iex typedef CCArray_T<ZBPropertyItemCategory*,ZBPropertyItemCategory*> ZBItemCategorySet;
typedef CCArray_T<PSS_PropertyItemCategory*, PSS_PropertyItemCategory*> ZBItemCategorySet;

//@type ZBItemCategoryIterator | An iterator for ZBItemCategorySet collections.
//@iex typedef Iterator_T<ZBPropertyItemCategory*> ZBItemCategoryIterator;
typedef Iterator_T<PSS_PropertyItemCategory*> ZBItemCategoryIterator;

//@type _ZBPropertyStateSet | An array of _ZBPropertyState pointers.
//@iex typedef CCArray_T<_ZBPropertyState*,_ZBPropertyState*> _ZBPropertyStateSet;
typedef CCArray_T<_ZBPropertyState*, _ZBPropertyState*> _ZBPropertyStateSet;

//@type _ZBPropertyStateIterator | An iterator for _ZBPropertyStateSet collections.
//@iex typedef Iterator_T<_ZBPropertyState*> _ZBPropertyStateIterator;
typedef Iterator_T<_ZBPropertyState*> _ZBPropertyStateIterator;

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemManager

class AFX_EXT_CLASS ZBPropertyItemManager
{
public:

    ZBPropertyItemManager();
    ~ZBPropertyItemManager();

    void Empty();
    void SetPropertyListCtrl(ZCPropertyListCtrl* pCtrl);

    void SetDisplayType(PropertyDisplayType tp)
    {
        m_DisplayType = tp;
    };

    // Attributes
    ZBItemCategorySet& GetItemCategorySet()
    {
        return m_PropertyItemTabSet;
    };

    const ZBItemCategorySet& GetItemCategorySetConst() const
    {
        return m_PropertyItemTabSet;
    };

    size_t GetCategoryCount() const
    {
        return m_PropertyItemTabSet.GetSize();
    };

    PSS_PropertyItemCategory* GetCategoryTab(int nIndex) const
    {
        return (nIndex < (int)GetCategoryCount()) ? m_PropertyItemTabSet.GetAt(nIndex) : NULL;
    };

    PSS_PropertyItemCategory* GetTab(PSS_PropertyItem* pPropertyItem);
    PSS_Property*           GetCorrespondingProperty(PSS_PropertyItem* pPropertyItem);

    // Operations
    PSS_PropertyItemCategory* AddNewTab(LPCTSTR pStrTabName);
    void CheckState(int nFromControlIndex, BYTE nFromPropertyItemID);

    virtual void OnDataChanged(PSS_PropertyItem*        pPropertyItem,
                               ZCPropertyListCtrl*    pWndPropertyListCtrl,
                               int                    nIndex,
                               bool&                Refresh);

    virtual bool UpdateControlData(const PSS_Properties* pData);
    virtual bool UpdateControlData(PSS_Properties::IPropertySet& PropSet);
    virtual bool UpdatePropertyData(PSS_PropertyItem* pPropertyItem = NULL);
    virtual bool CheckCurrentPropertyData(PSS_PropertyItem* pPropertyItem, CString& ProposedValue);

    virtual bool ProcessExtendedCurrentPropertyData(PSS_PropertyItem*    pPropertyItem,
                                                    CString&            ProposedValue,
                                                    bool&                Refresh);

    virtual bool ProcessMenuCommandCurrentPropertyData(int                MenuCommand,
                                                       PSS_PropertyItem*    pPropertyItem,
                                                       CString&        ProposedValue,
                                                       bool&            Refresh);

    /////////////////////////////////////////////////////////////////////////////
    // Property state management methods
    bool SavePropertyState(PSS_PropertyItem* pPropertyItem);
    bool SetPropertyStateToProperty(PSS_PropertyItem* pPropertyItem);
    bool SavePropertyState(PSS_PropertyItemCategory* pPropertyCategoryItem);
    bool SetPropertyStateToProperty(PSS_PropertyItemCategory* pPropertyCategoryItem);
    _ZBPropertyState* GetPropertyState(PSS_PropertyItem* pPropertyItem);
    _ZBPropertyState* GetPropertyCategoryState(PSS_PropertyItemCategory* pPropertyCategoryItem);

    bool LoadStateFromIniFile(const CString IniFile);
    bool SaveStateToIniFile(const CString IniFile);

    bool OnDropInternalPropertyItem(PSS_PropertyItem*    pSrcPropertyItem,
                                    PSS_PropertyItem*    pDstPropertyItem,
                                    bool                Top2Down);

protected:

    // If the tab exists, return it, otherwise return NULL
    PSS_PropertyItemCategory* TabExist(LPCTSTR pStrTabName);
    bool ApplyPropertyChanges();

private:

    // Does not allow copy constructor and assignement operator
    ZBPropertyItemManager(const ZBPropertyItemManager& d);
    ZBPropertyItemManager& operator=(const ZBPropertyItemManager& d);

    bool UpdateControlData();
    PSS_PropertyItem* CreatePropertyItem(PSS_Property& Prop);
    void SetDataToPropertyItem(PSS_PropertyItem* pPropertyItem, PSS_Property& Prop);
    void SetItemDataToProperty(PSS_PropertyItem* pPropertyItem, PSS_Property& Prop);
    void FreePropertySet();
    void DeleteUnusedTab();
    void DeleteAllTabs();
    bool ExistInPropSet(LPCTSTR pStrTabName);

    /////////////////////////////////////////////////////////////////////////////
    // Property state management methods
    void DeletePropertyState();

    bool OnDropCategory(PSS_PropertyItemCategory*    pSrcCategoryItem,
                        PSS_PropertyItem*            pDstPropertyItem,
                        bool                        Top2Down);

    void SetInitialCategoryOrder();
    void ReOrderCategory();
    void SaveAllCategoryOrders();

    // Datas
protected:

    ZBItemCategorySet    m_PropertyItemTabSet;

    PSS_Properties::IPropertySet        m_PropSet;

    PSS_Properties*        m_pCurrentData;

    ZCPropertyListCtrl*    m_pWndPropertyListCtrl;

    _ZBPropertyStateSet    m_PropertyState;

private:

    PropertyDisplayType    m_DisplayType;
};

inline ZBPropertyItemManager::ZBPropertyItemManager()
    : m_pWndPropertyListCtrl(NULL),
    m_pCurrentData(NULL),
    m_DisplayType(AllProperties)
{
    DeleteAllTabs();
}

inline ZBPropertyItemManager::~ZBPropertyItemManager()
{
    DeleteAllTabs();
    FreePropertySet();
    DeletePropertyState();
}

inline void ZBPropertyItemManager::OnDataChanged(PSS_PropertyItem*        pPropertyItem,
                                                 ZCPropertyListCtrl*    pWndPropertyListCtrl,
                                                 int                    nIndex,
                                                 bool&                    Refresh)
{
    PSS_Property* pProp = GetCorrespondingProperty(pPropertyItem);

    // Before updating the property,
    // call the pre property change function
    if (pProp)
    {
        // If a problem, stop the update process
        if (!m_pCurrentData->OnPrePropertyChanged(pPropertyItem->GetData(), *pProp, m_PropSet))
        {
            return;
        }
    }

    // Now apply the change to the property
    UpdatePropertyData(pPropertyItem);

    // Call the post property change function
    if (pProp && m_pCurrentData->OnPostPropertyChanged(*pProp, m_PropSet, Refresh))
    {
        ApplyPropertyChanges();
    }
}

/////////////////////////////////////////////////////////////////////////////
#define BEGIN_PROPERTY_TAB_IDNAME(idTabName, enabled) \
{ \
    ZBPropertyItemCategory* pNewTab = AddNewTab(LoadString(idTabName)); \
    pNewTab->SetEnabled(enabled); \
    PSS_PropertyItem* pPropertyItem;
#define PROPERTY_ITEM_IDNAME(id, class_name, idItemName, enabled) \
    pPropertyItem = new class_name(LoadString(idItemName)); \
    pPropertyItem->SetEnabled(enabled); \
    pPropertyItem->SetPropertyID(id);\
    pNewTab->AddPropertyItem(pPropertyItem);

#define BEGIN_PROPERTY_TAB(tabName, enabled) \
{ \
    ZBPropertyItemCategory* pNewTab = AddNewTab(tabName); \
    pNewTab->SetEnabled(enabled); \
    PSS_PropertyItem* pPropertyItem;
#define PROPERTY_ITEM(id, class_name, itemName, enabled) \
    pPropertyItem = new class_name(itemName); \
    pPropertyItem->SetEnabled(enabled); \
    pPropertyItem->SetPropertyID(id);\
    pNewTab->AddPropertyItem(pPropertyItem);
#define END_PROPERTY_TAB() \
}

#define BEGIN_ITERATE_PROPERTY_ITEMS() \
    POSITION pos = m_PropertyItemTabSet.GetHeadPosition(); \
    while(pos != NULL) \
    { \
        ZBPropertyItemCategory* pPropertyItemTab = m_PropertyItemTabSet.GetNext(pos); \
        POSITION posItem = pPropertyItemTab->GetHeadPosition(); \
        while(posItem != NULL) \
        { \
            PSS_PropertyItem* pPropertyItem = pPropertyItemTab->GetNext(posItem); \
            switch(pPropertyItem->GetPropertyID()) \
            {
#define SET_ITEM_STRING(id, string) \
                case id: \
                    static_cast<ZBPropertyItemString*>(pPropertyItem)->SetData(string); \
                    break;
#define GET_ITEM_STRING(id, string) \
                case id: \
                    string = static_cast<ZBPropertyItemString*>(pPropertyItem)->GetData(); \
                    break;
#define SET_ITEM_LIST(id, item) \
                case id: \
                static_cast<ZBPropertyItemList*>(pPropertyItem)->SetData(item); \
                    break;
#define GET_ITEM_LIST(id, item) \
                case id: \
                    static_cast<ZBPropertyItemList*>(pPropertyItem)->GetData(item); \
                    break;
#define END_ITERATE_PROPERTY_ITEMS() \
                default: ; \
            } \
        } \
    }

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
