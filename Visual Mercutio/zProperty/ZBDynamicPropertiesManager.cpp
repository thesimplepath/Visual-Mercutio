// ZBDynamicPropertiesManager.cpp: implementation of the ZBDynamicPropertiesManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDynamicPropertiesManager.h"

#include "zPropertyIds.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// constant definition
const int gCategoryStep    = 40;
const int gItemStep        = 1;

//////////////////////////////////////////////////////////////////////
// _ZBDynamicPropertyInfo

IMPLEMENT_SERIAL( _ZBDynamicPropertyInfo, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

_ZBDynamicPropertyInfo::_ZBDynamicPropertyInfo( ZBProperty* pProperty, CRuntimeClass* pSelectableClass )
    : m_pProperty        ( pProperty ),
      m_pSelectableClass( pSelectableClass )
{
    m_SymbolName.Empty();
    m_SymbolRef = -1;
}

_ZBDynamicPropertyInfo::_ZBDynamicPropertyInfo( ZBProperty* pProperty, const CString SymbolName, int RefNumber )
    : m_pProperty        ( pProperty ),
      m_SymbolName        ( SymbolName ),
      m_SymbolRef        ( RefNumber ),
      m_pSelectableClass( NULL )
{
}

_ZBDynamicPropertyInfo::~_ZBDynamicPropertyInfo()
{
    if ( m_pProperty )
    {
        delete m_pProperty;
        m_pProperty = NULL;
    }

    if ( m_pSelectableClass )
    {
        delete m_pSelectableClass;
        m_pSelectableClass = NULL;
    }
}

_ZBDynamicPropertyInfo& _ZBDynamicPropertyInfo::operator=( const _ZBDynamicPropertyInfo& src )
{
    this->m_SymbolName            = src.m_SymbolName;
    this->m_SymbolRef            = src.m_SymbolRef;

    // Allocated a new Runtime Class structure
    m_pSelectableClass            = new CRuntimeClass;
    this->m_pSelectableClass    = src.m_pSelectableClass;

    // Assign a copy of the property object
    this->m_pProperty            = src.m_pProperty->Dup();

    return *this;
}

void _ZBDynamicPropertyInfo::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Store the runting class, if there is
        if ( m_pSelectableClass )
        {
            ar << (int)1;
            m_pSelectableClass->Store( ar );
        }
        else
        {
            ar << (int)0;
        }

        // Store the property
        ar << m_pProperty;

        // Store the symbol name and ref number
        ar << m_SymbolName;
        ar << m_SymbolRef;
    }
    else
    {
        // Load the runting class, if there is
        int value;
        ar >> value;

        if ( value == 1 )
        {
            UINT nSchema;

            if ( ( m_pSelectableClass = CRuntimeClass::Load( ar, &nSchema ) ) == NULL )
            {
                AfxThrowArchiveException( CArchiveException::badClass, _T( "" ) );
            }
        }
        else
        {
            m_pSelectableClass = NULL;
        }

        // Load the property
        ar >> m_pProperty;

        // Store the symbol name and ref number
        ar >> m_SymbolName;
        ar >> m_SymbolRef;
    }
}

//////////////////////////////////////////////////////////////////////
// ZBDynamicPropertiesManager

IMPLEMENT_SERIAL( ZBDynamicPropertiesManager, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructeur par défaut de la classe ZBDynamicPropertiesManager.
ZBDynamicPropertiesManager::ZBDynamicPropertiesManager()
{
}

// Constructeur par copie de la classe ZBDynamicPropertiesManager.
ZBDynamicPropertiesManager::ZBDynamicPropertiesManager( const ZBDynamicPropertiesManager& src )
{
    *this = src;
}

// Destructeur de la classe ZBDynamicPropertiesManager.
ZBDynamicPropertiesManager::~ZBDynamicPropertiesManager()
{
    FreePropertiesSet();
}

// Surcharge de l'opérateur = pour la classe ZBDynamicPropertiesManager.
ZBDynamicPropertiesManager& ZBDynamicPropertiesManager::operator=( const ZBDynamicPropertiesManager& src )
{
    ZBDynamicPropertiesInfoIterator i( &src.m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddDynamicProperty( pProp->Dup() );
    }

    return *this;
}

// Cette fonction permet de dupliquer un objet ZBDynamicPropertiesManager.
ZBDynamicPropertiesManager* ZBDynamicPropertiesManager::Dup() const
{
    return ( new ZBDynamicPropertiesManager( *this ) );
}

// Cette fonction permet de nettoyer l'ensemble des propriétés contenues dans la classe.
void ZBDynamicPropertiesManager::FreePropertiesSet()
{
    // JMR-MODIF - Le 21 mars 2006 - Nettoyage des memory leaks, code de nettoyage des objets inscrits dans m_Set.
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp != NULL )
        {
            delete pProp;
        }
    }

    m_Set.RemoveAll();
}

// Cette fonction permet d'ajouter une nouvelle propriété dans le registre de propriétés.
ZBProperty* ZBDynamicPropertiesManager::RegisterProperty( const CString                Category,
                                                          const CString                Item,
                                                          const CString                Description,
                                                          ZBProperty::PropertyType    DataType,
                                                          ZBStringFormat&            ft,
                                                          CRuntimeClass*            pSelectableClass /*= NULL*/)
{
    int CategoryID    = RetreiveCategoryID( Category );
    int ItemID        = GetNextItemID        ( Category );

    ZBProperty* pProp = CreateProperty( Category, CategoryID, Item, ItemID, Description, DataType, ft );

    if ( pProp )
    {
        // Sets the attribute as dynamic
        pProp->SetDynamic();
        AddDynamicProperty( pProp, pSelectableClass );

        return pProp;
    }

    return NULL;
}

// Cette fonction permet d'ajouter une nouvelle propriété dans le registre de propriétés.
ZBProperty* ZBDynamicPropertiesManager::RegisterProperty( const CString                Category,
                                                          const CString                Item,
                                                          const CString                Description,
                                                          ZBProperty::PropertyType    DataType,
                                                          ZBStringFormat&            ft,
                                                          const CString                SymbolName,
                                                          int                        RefNumber )
{
    int CategoryID    = RetreiveCategoryID( Category );
    int ItemID        = GetNextItemID        ( Category );

    ZBProperty* pProp = CreateProperty( Category, CategoryID, Item, ItemID, Description, DataType, ft );

    if ( pProp )
    {
        // Sets the attribute as dynamic
        pProp->SetDynamic();
        AddDynamicProperty( pProp, SymbolName, RefNumber );

        return pProp;
    }

    return NULL;
}

// Cette fonction permet d'obtenir l'ID d'une catégorie donnée, par rapport à son nom.
int ZBDynamicPropertiesManager::RetreiveCategoryID( const CString Category )
{
    int CategoryID;

    _ZBDynamicPropertyInfo* pDPI = FindPropertyCategory( Category );

    if ( pDPI )
    {
        CategoryID = pDPI->m_pProperty->GetCategoryID();
    }
    else
    {
        CategoryID = GetNextCategoryID();
    }

    return CategoryID;
}

// Cette fonction permet d'ajouter une propriété dynamique à l'ensemble des propriétés de la classe.
void ZBDynamicPropertiesManager::AddDynamicProperty( ZBProperty* pProperty, CRuntimeClass* pSelectableClass )
{
    _ZBDynamicPropertyInfo* pProp = new _ZBDynamicPropertyInfo( pProperty, pSelectableClass );
    AddDynamicProperty( pProp );
}

// Cette fonction permet d'ajouter une propriété dynamique à l'ensemble des propriétés de la classe.
void ZBDynamicPropertiesManager::AddDynamicProperty( ZBProperty*    pProperty,
                                                     const CString    SymbolName,
                                                     int            RefNumber )
{
    _ZBDynamicPropertyInfo* pProp = new _ZBDynamicPropertyInfo( pProperty, SymbolName, RefNumber );
    AddDynamicProperty( pProp );
}

// Cette fonction permet de retrouver une catégorie de propriétés.
_ZBDynamicPropertyInfo* ZBDynamicPropertiesManager::FindPropertyCategory( const CString Category )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty && pProp->m_pProperty->GetCategory() == Category )
        {
            return pProp;
        }
    }

    return NULL;
}

// Cette fonction permet de retrouver une catégorie de propriétés.
_ZBDynamicPropertyInfo* ZBDynamicPropertiesManager::FindPropertyCategory( int CategoryID )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty && pProp->m_pProperty->GetCategoryID() == CategoryID )
        {
            return pProp;
        }
    }

    return NULL;
}

// Cette fonction permet de retrouver une propriété dans une catégorie.
_ZBDynamicPropertyInfo* ZBDynamicPropertiesManager::FindPropertyItem( const CString Category,
                                                                      const CString ItemName )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty                                &&
             pProp->m_pProperty->GetCategory() == Category    &&
             pProp->m_pProperty->GetLabel() == ItemName )
        {
            return pProp;
        }
    }

    return NULL;
}

// Cette fonction permet de retrouver une propriété dans une catégorie.
_ZBDynamicPropertyInfo* ZBDynamicPropertiesManager::FindPropertyItem( int CategoryID, const CString ItemName )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty                                    &&
             pProp->m_pProperty->GetCategoryID() == CategoryID    &&
             pProp->m_pProperty->GetLabel() == ItemName )
        {
            return pProp;
        }
    }

    return NULL;
}

// Cette fonction permet de retrouver une propriété dans une catégorie.
_ZBDynamicPropertyInfo* ZBDynamicPropertiesManager::FindPropertyItem( int CategoryID, int ItemID )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty                                    &&
             pProp->m_pProperty->GetCategoryID() == CategoryID    &&
             pProp->m_pProperty->GetItemID() == ItemID )
        {
            return pProp;
        }
    }

    return NULL;
}

// Cette fonction permet de supprimer une propriété dans le registre de propriétés.
bool ZBDynamicPropertiesManager::UnregisterProperty( int CategoryID, int ItemID )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty                                    &&
             pProp->m_pProperty->GetCategoryID() == CategoryID    &&
             pProp->m_pProperty->GetItemID() == ItemID )
        {
            delete pProp;
            i.Remove();

            return true;
        }
    }

    return false;
}

// Cette fonction permet d'obtenir la prochaine catégorie de propriétés disponible.
int ZBDynamicPropertiesManager::GetNextCategoryID()
{
    int MaxCatID = ZS_BP_DYNAMICPROP_START;

    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty )
        {
            MaxCatID = __max( MaxCatID, pProp->m_pProperty->GetCategoryID() );
        }
    }

    return MaxCatID + gCategoryStep;
}

// Cette fonction permet d'obtenir l'ID de la prochaine propriété disponible dans une catégorie donnée.
int ZBDynamicPropertiesManager::GetNextItemID( const CString Category )
{
    int MaxItemID = 0;

    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty && 
             pProp->m_pProperty->GetCategory() == Category )
        {
            MaxItemID = __max( MaxItemID, pProp->m_pProperty->GetItemID() );
        }
    }

    return MaxItemID + gItemStep;
}

// Cette fonction permet d'obtenir l'ID de la prochaine propriété disponible dans une catégorie donnée.
int ZBDynamicPropertiesManager::GetNextItemID( int CategoryID )
{
    int MaxItemID = 0;

    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty && 
             pProp->m_pProperty->GetCategoryID() == CategoryID )
        {
            MaxItemID = __max( MaxItemID, pProp->m_pProperty->GetItemID() );
        }
    }

    return MaxItemID + gItemStep;
}

// JMR-MODIF - Le 19 août 2005 - Cette fonction permet de créer la liste des propriétés contenues dans une catégorie.
void ZBDynamicPropertiesManager::CreatePropertyList( CString Category, CStringArray& m_PropList )
{
    ZBDynamicPropertiesInfoIterator i( &m_Set );

    for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->m_pProperty &&
             pProp->m_pProperty->GetCategory()    == Category )
        {
            m_PropList.Add( pProp->m_pProperty->GetLabel() );
        }
    }
}

// Cette fonction permet de créer une nouvelle propriété.
ZBProperty* ZBDynamicPropertiesManager::CreateProperty( const CString                Category,
                                                        int                            CategoryID,
                                                        const CString                Item,
                                                        int                            ItemID,
                                                        const CString                Description,
                                                        ZBProperty::PropertyType    DataType,
                                                        ZBStringFormat&                ft )
{
    ZBProperty* pProp = NULL;

    switch ( DataType )
    { 
        case ZBProperty::PT_EDIT_STRING:
        case ZBProperty::PT_EDIT_STRING_READONLY:
        case ZBProperty::PT_EDIT_MULTILINE:
        case ZBProperty::PT_EDIT_MULTILINE_READONLY:
        {
            pProp = new ZBProperty( Category,
                                    CategoryID,
                                    Item,
                                    ItemID,
                                    Description,
                                    _T( "" ),
                                    DataType,
                                    true, // Enable
                                    ft );
            break;
        }

        case ZBProperty::PT_EDIT_DATE:
        case ZBProperty::PT_EDIT_DATE_READONLY:
        //RS-MODIF 08.08.2005 gestion attribut de temps
        //case ZBProperty::PT_EDIT_TIME:
        //case ZBProperty::PT_EDIT_TIME_READONLY:
        {
            ZBDate dt;
            pProp = new ZBProperty( Category,
                                    CategoryID,
                                    Item,
                                    ItemID,
                                    Description,
                                    dt,
                                    DataType,
                                    true, // Enable
                                    ZBStringFormat( ZBStringFormat::Date ) );
            break;
        }

        //case ZBProperty::PT_EDIT_TIMESPAN:
        //case ZBProperty::PT_EDIT_TIMESPAN_READONLY:
        case ZBProperty::PT_EDIT_TIME:
        case ZBProperty::PT_EDIT_TIME_READONLY:
        {
            ZBTimeSpan ts;

            pProp = new ZBProperty( Category,
                                    CategoryID,
                                    Item,
                                    ItemID,
                                    Description,
                                    ts,
                                    DataType,
                                    true, // Enable
                                    ZBStringFormat( ZBStringFormat::Time1 ) );
            break;
        }

        case ZBProperty::PT_EDIT_DURATION:
        case ZBProperty::PT_EDIT_DURATION_READONLY:
        {
            ZBDuration dr;

            pProp = new ZBProperty( Category,
                                    CategoryID,
                                    Item,
                                    ItemID,
                                    Description,
                                    dr,
                                    DataType,
                                    true, // Enable
                                    ZBStringFormat( ZBStringFormat::Duration7 ) );
            break;
        }

        case ZBProperty::PT_EDIT_NUMBER:
        case ZBProperty::PT_EDIT_NUMBER_READONLY:
        {
            pProp = new ZBProperty( Category,
                                    CategoryID,
                                    Item,
                                    ItemID,
                                    Description,
                                    double( 0 ),
                                    DataType,
                                    true, // Enable
                                    ft );
            break;
        }

        case ZBProperty::PT_EDIT_MENU:
        {
            break;
        }

        case ZBProperty::PT_EDIT_MENU_READONLY:
        {
            break;
        }

        case ZBProperty::PT_EDIT_INTELI:
        {
            break;
        }

        case ZBProperty::PT_EDIT_INTELI_READONLY:
        {
            break;
        }

        case ZBProperty::PT_COMBO_STRING:
        {
            break;
        }

        case ZBProperty::PT_COMBO_STRING_READONLY:
        {
            break;
        }

        case ZBProperty::PT_COMBO_NUMBER:
        {
            break;
        }

        case ZBProperty::PT_COMBO_NUMBER_READONLY:
        {
            break;
        }

        case ZBProperty::PT_EDIT_FONT:
        {
            break;
        }

        case ZBProperty::PT_EDIT_FILE:
        {
            break;
        }

        case ZBProperty::PT_EDIT_DIRECTORY:
        {
            break;
        }

        case ZBProperty::PT_EDIT_MULTIFILES:
        {
            break;
        }

        case ZBProperty::PT_EDIT_MULTIDIRECTORIES:
        {
            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED:
        {
            break;
        }

        case ZBProperty::PT_EDIT_EXTENDED_READONLY:
        {
            break;
        }
    }

    return pProp;
}

// Cette fonction permet d'archiver ou de désarchiver les données de la classe.
void ZBDynamicPropertiesManager::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Serialize the size
        ar << m_Set.GetSize();

        ZBDynamicPropertiesInfoIterator i( &m_Set );

        for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            ar << pProp;
        }
    }
    else
    {
        int Size;
        ar >> Size;

        _ZBDynamicPropertyInfo* pProp;

        for ( int i = 0; i < Size; ++i )
        {
            ar >> pProp;
            AddDynamicProperty( pProp );
        }
    }
}
