// ZBDynamicPropertiesManager.h: interface for the ZBDynamicPropertiesManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDynamicPropertiesManager_H__D311F521_8934_41E0_A3E6_9EECBE05EA7F__INCLUDED_)
#define AFX_ZBDynamicPropertiesManager_H__D311F521_8934_41E0_A3E6_9EECBE05EA7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_StringFormat.h"
#include "ZBProperty.h"

//////////////////////////////////////////////////////////////////////
// Forward declaration

#ifdef _ZPROPERTYEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZBDynamicPropertyInfo keeps the state of a property for a specific reference
// If the reference is not kept, we will no search for it.
// We keep the following attributes:
//   - Collapsed or expanded
//   - Control size
//   - The control extended size

class _ZBDynamicPropertyInfo : public CObject
{
    DECLARE_SERIAL( _ZBDynamicPropertyInfo )

public:

    _ZBDynamicPropertyInfo()
    {
        m_SymbolName.Empty();

        m_SymbolRef            = -1;
        m_pSelectableClass    = NULL;
        m_pProperty            = NULL;
    };

    _ZBDynamicPropertyInfo( ZBProperty* pProperty, CRuntimeClass* pSelectableClass );
    _ZBDynamicPropertyInfo( ZBProperty* pProperty, const CString SymbolName, int RefNumber );

    virtual ~_ZBDynamicPropertyInfo();

    // Allow copy constructor and assignement operator
    _ZBDynamicPropertyInfo( const _ZBDynamicPropertyInfo& src )
    {
        *this = src;
    };

    _ZBDynamicPropertyInfo& operator=( const _ZBDynamicPropertyInfo& src );

    /* Create a duplicate copy of this object. */
    virtual _ZBDynamicPropertyInfo* Dup() const
    {
        return ( new _ZBDynamicPropertyInfo(*this) );
    }

    /* Serializes the object. */
    virtual void Serialize( CArchive& ar );

public:

    CString            m_SymbolName;
    int             m_SymbolRef;
    CRuntimeClass*    m_pSelectableClass;
    ZBProperty*        m_pProperty;
};

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBDynamicPropertiesInfoSet | An array of _ZBDynamicPropertyInfo pointers.
//@iex typedef CCArray_T<_ZBDynamicPropertyInfo*,_ZBDynamicPropertyInfo*> ZBDynamicPropertiesInfoSet;
typedef CCArray_T<_ZBDynamicPropertyInfo*, _ZBDynamicPropertyInfo*> ZBDynamicPropertiesInfoSet;

//@type _ZBDynamicPropertyInfo | An iterator for ZBDynamicPropertiesInfoSet collections.
//@iex typedef Iterator_T<ZIProperties*> ZBDynamicPropertiesInfoIterator;
typedef Iterator_T<_ZBDynamicPropertyInfo*> ZBDynamicPropertiesInfoIterator;

/////////////////////////////////////////////////////////////////////////////
// ZBDynamicPropertiesManager

class AFX_EXT_CLASS ZBDynamicPropertiesManager : public CObject
{
    DECLARE_SERIAL( ZBDynamicPropertiesManager )

public:

    ZBDynamicPropertiesManager();
    virtual ~ZBDynamicPropertiesManager();

    /* Copy constructor. */
    ZBDynamicPropertiesManager( const ZBDynamicPropertiesManager& src );

    /* Assignment operator. */
    ZBDynamicPropertiesManager& operator=( const ZBDynamicPropertiesManager& src );

    /* Create a duplicate copy of this object. */
    virtual ZBDynamicPropertiesManager* Dup() const;

    ZBProperty* RegisterProperty( const CString                Category,
                                  const CString                Item,
                                  const CString                Description,
                                  ZBProperty::PropertyType    DataType,
                                 PSS_StringFormat&            ft,
                                  CRuntimeClass*            pSelectableClass    = NULL);

    ZBProperty* RegisterProperty( const CString                Category,
                                  const CString                Item,
                                  const CString                Description,
                                  ZBProperty::PropertyType    DataType,
                                 PSS_StringFormat&            ft,
                                  const CString                SymbolName,
                                  int                        RefNumber);

    bool UnregisterProperty( int CategoryID, int ItemID );

    bool PropertyCategoryExist( const CString Category )
    {
        return ( FindPropertyCategory( Category ) != NULL ) ? true : false;
    };

    bool PropertyCategoryExist( int CategoryID )
    {
        return ( FindPropertyCategory( CategoryID ) != NULL ) ? true : false;
    };

    bool PropertyItemExist( const CString Category, const CString ItemName )
    {
        return ( FindPropertyItem( Category, ItemName ) != NULL ) ? true : false;
    };

    bool PropertyItemExist( int CategoryID, const CString ItemName )
    {
        return ( FindPropertyItem( CategoryID, ItemName ) != NULL ) ? true : false;
    };

    bool PropertyItemExist( int CategoryID, int ItemID )
    {
        return ( FindPropertyItem( CategoryID, ItemID ) != NULL ) ? true : false;
    };

    ZBProperty* GetPropertyItem( const CString Category, const CString ItemName )
    {
        _ZBDynamicPropertyInfo* pInfo = FindPropertyItem( Category, ItemName );
        return ( pInfo ) ? pInfo->m_pProperty : NULL;
    };

    ZBProperty* GetPropertyItem( int CategoryID, const CString ItemName )
    {
        _ZBDynamicPropertyInfo* pInfo = FindPropertyItem( CategoryID, ItemName );
        return ( pInfo ) ? pInfo->m_pProperty : NULL;
    };

    ZBProperty* GetPropertyItem( int CategoryID, int ItemID )
    {
        _ZBDynamicPropertyInfo* pInfo = FindPropertyItem( CategoryID, ItemID );
        return ( pInfo ) ? pInfo->m_pProperty : NULL;
    };

    int GetNextCategoryID();
    int GetNextItemID( const CString Category );
    int GetNextItemID( int CategoryID );

    ZBDynamicPropertiesInfoSet& GetDynamicPropertiesInfoSet()
    {
        return m_Set;
    };

    // JMR-MODIF - Le 19 août 2005 - Ajout de la fonction CreatePropertyList.
    void CreatePropertyList( CString Category, CStringArray& m_PropList );

    /* Serializes the object. */
    virtual void Serialize(CArchive& ar);

private:

    void FreePropertiesSet();
    void AddDynamicProperty( _ZBDynamicPropertyInfo* pProp )
    {
        m_Set.Add( pProp );
    };

    void AddDynamicProperty( ZBProperty* pProperty, CRuntimeClass* pSelectableClass );
    void AddDynamicProperty( ZBProperty* pProperty, const CString SymbolName, int RefNumber );

    int RetrieveCategoryID( const CString Category );

    ZBProperty* CreateProperty( const CString                Category,
                                int                            CategoryID,
                                const CString                Item,
                                int                            ItemID,
                                const CString                Description,
                                ZBProperty::PropertyType    DataType,
                               PSS_StringFormat&                ft );

    _ZBDynamicPropertyInfo* FindPropertyCategory( const CString Category );
    _ZBDynamicPropertyInfo* FindPropertyCategory( int CategoryID );
    _ZBDynamicPropertyInfo* FindPropertyItem( const CString Category, const CString ItemName );
    _ZBDynamicPropertyInfo* FindPropertyItem( int CategoryID, const CString ItemName );
    _ZBDynamicPropertyInfo* FindPropertyItem( int CategoryID, int ItemID );

private:

    ZBDynamicPropertiesInfoSet m_Set;
};

#endif // !defined(AFX_ZBDynamicPropertiesManager_H__D311F521_8934_41E0_A3E6_9EECBE05EA7F__INCLUDED_)