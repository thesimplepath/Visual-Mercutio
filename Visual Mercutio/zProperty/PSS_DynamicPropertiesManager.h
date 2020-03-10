/****************************************************************************
 * ==> PSS_DynamicPropertiesManager ----------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic properties manager                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DynamicPropertiesManagerH
#define PSS_DynamicPropertiesManagerH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DynamicPropertyInfo
    #define PSS_DynamicPropertyInfo _ZBDynamicPropertyInfo
#endif
#ifndef PSS_DynamicPropertiesManager
    #define PSS_DynamicPropertiesManager ZBDynamicPropertiesManager
#endif

// processsoft
#include "zBaseLib\PSS_StringFormat.h"
#include "PSS_Property.h"

#ifdef _ZPROPERTYEXPORT
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
* Keeps the property state for a specific reference. If the reference is not kept,
* the property will not be searched. The following attributes are available:
* - Collapsed or expanded
* - Control size
* - The control extended size
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DynamicPropertyInfo : public CObject
{
    DECLARE_SERIAL(PSS_DynamicPropertyInfo)

    public:
        CRuntimeClass* m_pSelectableClass;
        PSS_Property*  m_pProperty;
        CString        m_SymbolName;
        int            m_SymbolRef;

        inline PSS_DynamicPropertyInfo();

        /**
        * Constructor
        *@param pProperty - the property
        *@param pSelectableClass - the selectable class
        */
        PSS_DynamicPropertyInfo(PSS_Property* pProperty, CRuntimeClass* pSelectableClass);

        /**
        * Constructor
        *@param pProperty - the property
        *@param symbolName - the symbol name
        *@param refNumber - the reference number
        */
        PSS_DynamicPropertyInfo(PSS_Property* pProperty, const CString& symbolName, int refNumber);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_DynamicPropertyInfo(const PSS_DynamicPropertyInfo& other);

        virtual ~PSS_DynamicPropertyInfo();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DynamicPropertyInfo& operator = (const PSS_DynamicPropertyInfo& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_DynamicPropertyInfo* Dup() const;

        /* Serializes the object. */
        virtual void Serialize(CArchive& ar);
};

//---------------------------------------------------------------------------
// PSS_DynamicPropertyInfo
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo::PSS_DynamicPropertyInfo() :
    CObject(),
    m_pSelectableClass(NULL),
    m_pProperty(NULL),
    m_SymbolRef(-1)
{}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo::PSS_DynamicPropertyInfo(const PSS_DynamicPropertyInfo& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertyInfo::Dup() const
{
    return new PSS_DynamicPropertyInfo(*this);
}
//---------------------------------------------------------------------------

/**
* Dynamic properties manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DynamicPropertiesManager : public CObject
{
    DECLARE_SERIAL(PSS_DynamicPropertiesManager)

    public:
        typedef CCArray_T <PSS_DynamicPropertyInfo*, PSS_DynamicPropertyInfo*> IDynamicPropertiesInfoSet;
        typedef Iterator_T<PSS_DynamicPropertyInfo*>                           IDynamicPropertiesInfoIterator;

        PSS_DynamicPropertiesManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DynamicPropertiesManager(const PSS_DynamicPropertiesManager& other);

        virtual ~PSS_DynamicPropertiesManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DynamicPropertiesManager& operator = (const PSS_DynamicPropertiesManager& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_DynamicPropertiesManager* Dup() const;

        /**
        * Creates the property list
        *@param category - the category
        *@param propList - the property list
        */
        void CreatePropertyList(const CString& category, CStringArray& propList);

        /**
        * Registers a property
        *@param category - the property category
        *@param item - the property item
        *@param description - the property description
        *@param dataType - the property data type
        *@param strFormat - the property string format
        *@param pSelectableClass - the selectable class
        *@return the newly registerd property, NULL on error
        */
        virtual PSS_Property* RegisterProperty(const CString&       category,
                                               const CString&       item,
                                               const CString&       description,
                                               PSS_Property::IEType dataType,
                                               PSS_StringFormat&    strFormat,
                                               CRuntimeClass*       pSelectableClass = NULL);

        /**
        * Registers a property
        *@param category - the property category
        *@param item - the property item
        *@param description - the property description
        *@param dataType - the property data type
        *@param strFormat - the property string format
        *@param symbolName - the symbol name
        *@param refNumber - the reference number
        *@return the newly registerd property, NULL on error
        */
        virtual PSS_Property* RegisterProperty(const CString&       category,
                                               const CString&       item,
                                               const CString&       description,
                                               PSS_Property::IEType dataType,
                                               PSS_StringFormat&    strFormat,
                                               const CString&       symbolName,
                                               int                  refNumber);

        /**
        * Unregisters a property
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        *@return true on success, otherwise false
        */
        virtual bool UnregisterProperty(int categoryID, int itemID);

        /**
        * Checks if a property category exists
        *@param category - the property category to check
        *@return true if the property category exists, otherwise false
        */
        virtual inline bool PropertyCategoryExist(const CString& category);

        /**
        * Checks if a property category exists
        *@param categoryID - the property category identifier to check
        *@return true if the property category exists, otherwise false
        */
        virtual inline bool PropertyCategoryExist(int categoryID);

        /**
        * Checks if a property item exists
        *@param category - the property category
        *@param itemName - the property item name
        *@return true if the property item exists, otherwise false
        */
        virtual inline bool PropertyItemExist(const CString& category, const CString& itemName);

        /**
        * Checks if a property item exists
        *@param categoryID - the property category identifier
        *@param itemName - the property item name
        *@return true if the property item exists, otherwise false
        */
        virtual inline bool PropertyItemExist(int categoryID, const CString& itemName);

        /**
        * Checks if a property item exists
        *@param categoryID - the property category identifier
        *@param itemID - the property item identifier
        *@return true if the property item exists, otherwise false
        */
        virtual inline bool PropertyItemExist(int categoryID, int itemID);

        /**
        * Gets a property item
        *@param category - the property category
        *@param itemName - the property item name
        *@return the property item, NULL if not found or on error
        */
        virtual inline PSS_Property* GetPropertyItem(const CString& category, const CString& itemName);

        /**
        * Gets a property item
        *@param categoryID - the property category identifier
        *@param itemName - the property item name
        *@return the property item, NULL if not found or on error
        */
        virtual inline PSS_Property* GetPropertyItem(int categoryID, const CString& itemName);

        /**
        * Gets a property item
        *@param categoryID - the property category identifier
        *@param itemID - the property item identifier
        *@return the property item, NULL if not found or on error
        */
        virtual inline PSS_Property* GetPropertyItem(int categoryID, int itemID);

        /**
        * Gets the next category identifier
        *@return the next category identifier, -1 if not found or on error
        */
        virtual int GetNextCategoryID() const;

        /**
        * Gets the next item identifier
        *@param category - the property category
        *@return the next item identifier, -1 if not found or on error
        */
        virtual int GetNextItemID(const CString& category) const;

        /**
        * Gets the next item identifier
        *@param categoryID - the property category identifier
        *@return the next item identifier, -1 if not found or on error
        */
        virtual int GetNextItemID(int categoryID);

        /**
        * Gets the dynamic properties info set
        *@return the dynamic properties info set
        */
        virtual inline IDynamicPropertiesInfoSet& GetDynamicPropertiesInfoSet();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        IDynamicPropertiesInfoSet m_Set;

        /**
        * Creates a property
        *@param category - the property category
        *@param categoryID - the property category identifier
        *@param item - the property item
        *@param itemID - the property item identifier
        *@param description - the property description
        *@param dataType - the property data type
        *@param strFormat - the property string format
        *@return the newly created property, NULL on error
        */
        PSS_Property* CreateProperty(const CString&       category,
                                     int                  categoryID,
                                     const CString&       item,
                                     int                  itemID,
                                     const CString&       description,
                                     PSS_Property::IEType dataType,
                                     PSS_StringFormat&    strFormat);

        /**
        * Frees the property set
        */
        void FreePropertiesSet();

        /**
        * Adds a dynamic property
        *@param pPropInfo - the property info to add
        */
        inline void AddDynamicProperty(PSS_DynamicPropertyInfo* pPropInfo);

        /**
        * Adds a dynamic property
        *@param pProperty - the dynamic property to add
        *@param pSelectableClass - the selectable class
        */
        void AddDynamicProperty(PSS_Property* pProperty, CRuntimeClass* pSelectableClass);

        /**
        * Adds a dynamic property
        *@param pProperty - the dynamic property to add
        *@param symbolName - the symbol name
        *@param refNumber - the reference number
        */
        void AddDynamicProperty(PSS_Property* pProperty, const CString& symbolName, int refNumber);

        /**
        * Gets the category identifier
        *@param category - the category for which the identifier should be get
        *@return the category identifier
        */
        int GetCategoryID(const CString& category);

        /**
        * Finds the property category
        *@param category - the category
        *@return the property category, NULL if not found or on error
        */
        PSS_DynamicPropertyInfo* FindPropertyCategory(const CString& category);

        /**
        * Finds the property category
        *@param categoryID - the category identifier
        *@return the property category, NULL if not found or on error
        */
        PSS_DynamicPropertyInfo* FindPropertyCategory(int CategoryID);

        /**
        * Finds the property item
        *@param category - the category
        *@param itemName - the property item name
        *@return the property item, NULL if not found or on error
        */
        PSS_DynamicPropertyInfo* FindPropertyItem(const CString& category, const CString& itemName);

        /**
        * Finds the property item
        *@param categoryID - the category identifier
        *@param itemName - the property item name
        *@return the property item, NULL if not found or on error
        */
        PSS_DynamicPropertyInfo* FindPropertyItem(int categoryID, const CString& itemName);

        /**
        * Finds the property item
        *@param categoryID - the category identifier
        *@param itemID - the property item identifier
        *@return the property item, NULL if not found or on error
        */
        PSS_DynamicPropertyInfo* FindPropertyItem(int categoryID, int ItemID);
};

//---------------------------------------------------------------------------
// PSS_DynamicPropertiesManager
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::PropertyCategoryExist(const CString& category)
{
    return FindPropertyCategory(category);
}
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::PropertyCategoryExist(int categoryID)
{
    return FindPropertyCategory(categoryID);
}
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::PropertyItemExist(const CString& category, const CString& itemName)
{
    return FindPropertyItem(category, itemName);
}
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::PropertyItemExist(int categoryID, const CString& itemName)
{
    return FindPropertyItem(categoryID, itemName);
}
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::PropertyItemExist(int categoryID, int itemID)
{
    return FindPropertyItem(categoryID, itemID);
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::GetPropertyItem(const CString& category, const CString& itemName)
{
    PSS_DynamicPropertyInfo* pInfo = FindPropertyItem(category, itemName);
    return (pInfo ? pInfo->m_pProperty : NULL);
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::GetPropertyItem(int categoryID, const CString& itemName)
{
    PSS_DynamicPropertyInfo* pInfo = FindPropertyItem(categoryID, itemName);
    return (pInfo ? pInfo->m_pProperty : NULL);
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::GetPropertyItem(int categoryID, int itemID)
{
    PSS_DynamicPropertyInfo* pInfo = FindPropertyItem(categoryID, itemID);
    return (pInfo) ? pInfo->m_pProperty : NULL;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager::IDynamicPropertiesInfoSet& PSS_DynamicPropertiesManager::GetDynamicPropertiesInfoSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::AddDynamicProperty(PSS_DynamicPropertyInfo* pPropInfo)
{
    m_Set.Add(pPropInfo);
}
//---------------------------------------------------------------------------

#endif
