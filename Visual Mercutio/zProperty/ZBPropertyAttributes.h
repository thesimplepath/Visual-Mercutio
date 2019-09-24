#ifndef ZBPropertyAttributes_h
#define ZBPropertyAttributes_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZIProperties
#include "ZIProperties.h"

#ifdef _ZPROPERTYEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS _ZBPropertyAttribute
{
public:

    _ZBPropertyAttribute( int CategoryID = -1, int ItemID = -1 );

    ~_ZBPropertyAttribute()
    {
    };

    _ZBPropertyAttribute (_ZBPropertyAttribute& src);
    const _ZBPropertyAttribute & operator= ( const _ZBPropertyAttribute &right );

    _ZBPropertyAttribute* Clone();

    // Attribute accessor
    int GetCategoryID() const;
    void SetCategoryID( int value );

    int GetItemID() const;
    void SetItemID( int value );

    // Serialization
    AFX_EXT_API friend CArchive& operator >> ( CArchive& ar, _ZBPropertyAttribute& src );
    AFX_EXT_API friend CArchive& operator << ( CArchive& ar, const _ZBPropertyAttribute& src );

private:

    int m_CategoryID;
    int m_ItemID;
};

inline int _ZBPropertyAttribute::GetCategoryID() const
{
    return m_CategoryID;
}

inline void _ZBPropertyAttribute::SetCategoryID( int value )
{
    m_CategoryID = value;
}

inline int _ZBPropertyAttribute::GetItemID() const
{
    return m_ItemID;
}

inline void _ZBPropertyAttribute::SetItemID( int value )
{
    m_ItemID = value;
}

using namespace sfl;

//@type _ZBPropertyAttributeSet | An array of _ZBPropertyAttribute pointers.
//@iex typedef CCArray_T<_ZBPropertyAttribute*,_ZBPropertyAttribute*> _ZBPropertyAttributeSet;
typedef CCArray_T<_ZBPropertyAttribute*, _ZBPropertyAttribute*> _ZBPropertyAttributeSet;

//@type _ZBPropertyAttributeIterator | An iterator for _ZBPropertyAttributeSet collections.
//@iex typedef Iterator_T<_ZBPropertyAttribute*> _ZBPropertyAttributeIterator;
typedef Iterator_T<_ZBPropertyAttribute*> _ZBPropertyAttributeIterator;

class AFX_EXT_CLASS ZBPropertyAttributes
{
public:

    ZBPropertyAttributes();
    ~ZBPropertyAttributes();

    ZBPropertyAttributes( ZBPropertyAttributes& src );
    const ZBPropertyAttributes & operator= ( const ZBPropertyAttributes &right );

    ZBPropertyAttributes* Clone();

    bool LoadStateFromIniFile( const CString IniFile, int ObjectID );
    bool SaveStateToIniFile( const CString IniFile, int ObjectID );

    // RS-MODIF 12.12.04 delete attributes from inifile
    bool DeleteAttributesFromIniFile( const CString IniFile, int ObjectID );

    _ZBPropertyAttributeSet& GetAttributeSet()
    {
        return m_AttributeSet;
    };

    const _ZBPropertyAttributeSet& GetAttributeSetConst() const
    {
        return m_AttributeSet;
    };

    void RemoveAllAttributes();

    size_t GetAttributeCount() const
    {
        return m_AttributeSet.GetSize();
    };

    _ZBPropertyAttribute* GetAttributeAt( size_t Index )
    {
        if ( Index < GetAttributeCount() )
        {
            return m_AttributeSet.GetAt( Index );
        }

        return NULL;
    };

    void AddAttribute( _ZBPropertyAttribute* pAttribute );
    void AddAttributeAt( size_t Index, _ZBPropertyAttribute* pAttribute );

    void AddAttribute( int CategoryID, int ItemID = -1 )
    {
        AddAttribute( new _ZBPropertyAttribute( CategoryID, ItemID ) );
    };

    void AddAttributeAt( size_t Index, int CategoryID, int ItemID = -1 )
    {
        if ( Index < GetAttributeCount() )
        {
            AddAttributeAt( Index, new _ZBPropertyAttribute( CategoryID, ItemID ) );
        }
        else
        {
            AddAttribute( CategoryID, ItemID );
        }
    };

    bool DeleteAttribute( int CategoryID, int ItemID );
    void DeleteCategoryAttribute( int CategoryID );
    bool DeleteAttributeAt( size_t Index );

    _ZBPropertyAttribute* FindAttribute( int CategoryID, int ItemID );
    bool AttributeExist( int CategoryID, int ItemID )
    {
        return (FindAttribute( CategoryID, ItemID ) != NULL) ? true : false;
    };

    // Return true if one of the property content defined in this object
    // matches with the property set passed as a parameter
    bool Match( ZBPropertySet&    PropSet,
                const CString    What,
                bool            CaseSensitive = false,
                bool            PartialSearch = false );

    // Construct the right string
    CString GetString( ZBPropertySet* pPropSet, bool KeepOnlyNotEmpty = true );

    // Attribute accessor
    bool GetDisplayTitleText() const;
    void SetDisplayTitleText( bool value );

    // Serialization
    AFX_EXT_API friend CArchive& operator >> ( CArchive& ar, ZBPropertyAttributes& src );
    AFX_EXT_API friend CArchive& operator << ( CArchive& ar, const ZBPropertyAttributes& src );

private:

    _ZBPropertyAttributeSet    m_AttributeSet;
    bool                    m_DisplayTitleText;
};

inline bool ZBPropertyAttributes::GetDisplayTitleText() const
{
    return m_DisplayTitleText;
}

inline void ZBPropertyAttributes::SetDisplayTitleText( bool value )
{
    m_DisplayTitleText = value;
}

#endif