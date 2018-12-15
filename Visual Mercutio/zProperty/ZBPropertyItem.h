// ZBPropertyItem.h : header file

#if !defined(_ZBPROPERTYITEM_H__)
#define _ZBPROPERTYITEM_H__

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

#include "zBaseLib\zPtrList.h"
#include "zBaseLib\ZBSmartString.h"
#include "zProperty\ZIInPlaceEdit.h"
#include "zBaseLib\ZBStringFormat.h"
#include "zBaseLib\ZUStringFormater.h"
#include "zBaseLib\ZBDuration.h"
#include "zBaseLib\ZBDate.h"
//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
#include "zBaseLib\ZBTimeSpan.h"

#ifdef _ZPROPERTYEXPORT
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
// ZBPropertyItem

class AFX_EXT_CLASS ZBPropertyItem : public CObject
{
    ZBPropertyItem( const ZBPropertyItem& d );
    ZBPropertyItem& operator=( const ZBPropertyItem& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItem )

public:

    enum PropertyItemNumberType
    {
        PI_STRING,
        PI_DOUBLE,
        PI_FLOAT,
        PI_DATE,
        PI_TIME,
        PI_DURATION
    };

public:

    ZBPropertyItem( LPCTSTR pStrName = NULL, bool IsReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItem();

    // Attributes
    const CString& GetName() const;
    void SetName( LPCTSTR pStrName );

    bool GetEnabled() const;
    bool SetEnabled( bool bEnable = true );

    bool IsReadOnly() const
    {
        return m_ReadOnly;
    };

    // Determine if the item can be edited
    virtual bool CanBeEdited() const
    {
        return m_CanBeEdited;
    };

    bool GetHasChanged() const;
    void SetHasChanged( bool value = true );

    int GetPropertyID() const;
    void SetPropertyID( int nPropertyID );

    CSize GetSize() const;
    void SetSize( CSize value );

    CSize GetExtendedSize() const;
    void SetExtendedSize( CSize value );

    bool GetSaveState() const;
    void SetSaveState( bool value );

    bool GetSaveStatePerProperty() const;
    void SetSaveStatePerProperty( bool value );

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd* pWndParent,
                                       CRect& rect,
                                       ZIInPlaceEdit*& pWndInPlaceControl,
                                       CSize ExtendedSize = CSize( 0, 0 ) );

    virtual void DestroyInPlaceControl( ZIInPlaceEdit*& pWndInPlaceControl );

    // Set and get data for string
    virtual void SetData( const CString sText );
    virtual CString GetData() const;

    // Set and get data for double
    virtual void SetData( double Value );
    virtual double GetDataDouble() const;

    // Set and get data for float
    virtual void SetData( float Value );
    virtual float GetDataFloat() const;

    // Set and get data for duration
    virtual void SetData( ZBDuration& Value );
    virtual ZBDuration GetDataDuration() const;

    // Set and get data for date
    virtual void SetData( ZBDate& Value );
    virtual ZBDate GetDataDate() const;

    // RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    // Set and get data for time
    virtual void SetData( ZBTimeSpan& Value );
    virtual ZBTimeSpan GetDataTime() const;

    // Set and get for array of strings
    virtual void SetData( CStringArray* values )
    {
    };

    virtual void GetData( CStringArray* values ) const
    {
    };

    ZBStringFormat& GetStringFormat();
    void SetStringFormat( ZBStringFormat& value );

    bool IsEnabledDragNDrop() const;
    void EnableDragNDrop( bool value = true );

    int     GetItemOrder() const;
    void SetItemOrder( int value );
    
    int     GetCategoryOrder() const;
    void SetCategoryOrder( int value );

// Data
protected:

    PropertyItemNumberType    m_Type;
    CString                    m_strText;
    double                    m_dValue;
    float                    m_fValue;
    ZBDuration                m_durationValue;
    ZBDate                    m_dateValue;
    //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    ZBTimeSpan                m_timeValue;

private:

    CString                    m_strName;
    bool                    m_bEnabled;
    int                        m_PropertyID;
    bool                    m_ReadOnly;
    bool                    m_CanBeEdited;
    bool                    m_HasChanged;
    ZBStringFormat            m_ft;

    bool                    m_SaveState;
    bool                    m_SaveStatePerProperty;
    CSize                    m_Size;
    CSize                    m_ExtendedSize;

    bool                    m_EnableDragNDrop;

    int                        m_ItemOrder;
    int                        m_CategoryOrder;
};

inline ZBPropertyItem::ZBPropertyItem( LPCTSTR pStrName, bool ReadOnly /*= false*/, bool CanBeEdited /*= true*/ )
    : m_Size                    ( 0, 0 ), 
      m_ExtendedSize            ( 0, 0 ),
      m_SaveState                ( true ),
      m_SaveStatePerProperty    ( true )
{
    m_Type            = PI_STRING;    // Default is a string
    m_strName        = ( pStrName != NULL ) ? pStrName : _T( "" );
    m_bEnabled        = true;
    m_PropertyID    = 0;
    m_ReadOnly        = ReadOnly;
    m_CanBeEdited    = CanBeEdited;
    m_HasChanged    = false;

    m_ItemOrder        = -1;
    m_CategoryOrder    = -1;
}

inline ZBPropertyItem::~ZBPropertyItem()
{
}

inline const CString& ZBPropertyItem::GetName() const
{
    return m_strName;
}

inline void ZBPropertyItem::SetName( LPCTSTR pStrName )
{
    m_strName = ( pStrName != NULL ) ? pStrName : _T( "" );
}

inline bool ZBPropertyItem::GetEnabled() const
{
    return m_bEnabled;
}

inline bool ZBPropertyItem::GetHasChanged() const
{
    return m_HasChanged;
}

inline void ZBPropertyItem::SetHasChanged( bool value /*= true*/ )
{
    m_HasChanged = value;
}

inline int ZBPropertyItem::GetPropertyID() const
{
    return m_PropertyID;
}

inline void ZBPropertyItem::SetPropertyID( int nPropertyID )
{
    m_PropertyID = nPropertyID;
}

inline ZBStringFormat& ZBPropertyItem::GetStringFormat()
{
    return m_ft;
}

inline void ZBPropertyItem::SetStringFormat( ZBStringFormat& value )
{
    m_ft = value;
}

inline void ZBPropertyItem::SetData( const CString sText )
{
    switch( m_Type )
    {
        case PI_STRING:
        {
            m_strText = sText;
            break;
        }

        case PI_DOUBLE:
        {
            double value;

            if ( ZUStringFormatter::ConvertFormattedBuffer( sText, value, GetStringFormat() ) )
            {
                m_dValue = value;
            }

            break;

        }
        case PI_FLOAT:
        {
            float value;

            if ( ZUStringFormatter::ConvertFormattedBuffer( sText, value, GetStringFormat() ) )
            {
                m_fValue = value;
            }

            break;
        }

        case PI_DURATION:
        {
            ZBDuration value;

            if ( ZUStringFormatter::ConvertFormattedBuffer( sText, (ZBDuration&)value, GetStringFormat() ) )
            {
                m_durationValue = value;
            }

            break;
        }

        case PI_DATE:
        {
            ZBDate value;

            if ( ZUStringFormatter::ConvertFormattedBuffer( sText, (ZBDate&)value, GetStringFormat() ) )
            {
                m_dateValue = value;
            }

            break;
        }

        // RS-MODIF 08.08.2005 ajout attribut dynamique "temps"
        case PI_TIME:
        {
            ZBTimeSpan value;

            if ( ZUStringFormatter::ConvertFormattedBuffer( sText, (ZBTimeSpan&)value, GetStringFormat() ) )
            {
                m_timeValue = value;
            }

            break;
        }
    }
}

inline void ZBPropertyItem::SetData( double Value )
{
    m_Type            = PI_DOUBLE;
    m_dValue        = Value;
}

inline double ZBPropertyItem::GetDataDouble() const
{
    return m_dValue;
};

inline void ZBPropertyItem::SetData( float Value )
{
    m_Type            = PI_FLOAT;
    m_fValue        = Value;
}

inline float ZBPropertyItem::GetDataFloat() const
{
    return m_fValue;
};

inline void ZBPropertyItem::SetData( ZBDuration& Value )
{
    m_Type            = PI_DURATION;
    m_durationValue    = Value;
}

inline ZBDuration ZBPropertyItem::GetDataDuration() const
{
    return m_durationValue;
};

inline void ZBPropertyItem::SetData( ZBDate& Value )
{
    m_Type            = PI_DATE;
    m_dateValue        = Value;
}


//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
inline void ZBPropertyItem::SetData( ZBTimeSpan& Value )
{
    m_Type            = PI_TIME;
    m_timeValue        = Value;
}

inline ZBDate ZBPropertyItem::GetDataDate() const
{
    return m_dateValue;
};

//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
inline ZBTimeSpan ZBPropertyItem::GetDataTime() const
{
    return m_timeValue;
};

inline CString ZBPropertyItem::GetData() const
{
    CString sText;

    switch( m_Type )
    {
        case PI_STRING:
        {
            return m_strText;
        }

        case PI_DOUBLE:
        {
            // Format the value function of the string format specified
            sText = ZUStringFormatter::GetFormattedBuffer( m_dValue,
                                                           const_cast<ZBPropertyItem*>(this)->GetStringFormat() );
            break;
        }
        case PI_FLOAT:
        {
            // Format the value function of the string format specified
            sText = ZUStringFormatter::GetFormattedBuffer( m_fValue,
                                                           const_cast<ZBPropertyItem*>(this)->GetStringFormat() );
            break;
        }
        case PI_DURATION:
        {
            // Format the value function of the string format specified
            sText = ZUStringFormatter::GetFormattedBuffer( (ZBDuration&)m_durationValue,
                                                           const_cast<ZBPropertyItem*>(this)->GetStringFormat() );
            break;
        }
        case PI_DATE:
        {
            // Format the value function of the string format specified
            sText = ZUStringFormatter::GetFormattedBuffer( (ZBDate&)m_dateValue,
                                                           const_cast<ZBPropertyItem*>(this)->GetStringFormat() );
            break;
        }
        //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
        case PI_TIME:
        {
            // Format the value function of the string format specified
            sText = ZUStringFormatter::GetFormattedBuffer( (ZBTimeSpan&)m_timeValue,
                                                           const_cast<ZBPropertyItem*>(this)->GetStringFormat() );
            break;
        }
    }

    return sText;
}

inline void ZBPropertyItem::DrawValue( CDC* /*pDC*/, CRect& /*rect*/ )
{
}

inline CSize ZBPropertyItem::GetSize() const
{
    return m_Size;
}

inline void ZBPropertyItem::SetSize( CSize value )
{
    m_Size = value;
}

inline CSize ZBPropertyItem::GetExtendedSize() const
{
    return m_ExtendedSize;
}

inline void ZBPropertyItem::SetExtendedSize( CSize value )
{
    m_ExtendedSize = value;
}

inline bool ZBPropertyItem::GetSaveState() const
{
    return m_SaveState;
}

inline void ZBPropertyItem::SetSaveState( bool value )
{
    m_SaveState = value;
}

inline bool ZBPropertyItem::GetSaveStatePerProperty() const
{
    return m_SaveStatePerProperty;
}

inline void ZBPropertyItem::SetSaveStatePerProperty( bool value )
{
    m_SaveStatePerProperty = value;
}

inline bool ZBPropertyItem::IsEnabledDragNDrop() const
{
    return m_EnableDragNDrop;
}

inline void ZBPropertyItem::EnableDragNDrop( bool value /*= true*/ )
{
    m_EnableDragNDrop = value;
}

inline int    ZBPropertyItem::GetItemOrder() const
{
    return m_ItemOrder;
}

inline void ZBPropertyItem::SetItemOrder( int value )
{
    m_ItemOrder = value;
}

inline int    ZBPropertyItem::GetCategoryOrder() const
{
    return m_CategoryOrder;
}

inline void ZBPropertyItem::SetCategoryOrder( int value )
{
    m_CategoryOrder = value;
}

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBPropertyItemSet | An array of ZBPropertyItem pointers.
//@iex typedef CCArray_T<ZBPropertyItem*,ZBPropertyItem*> ZBPropertyItemSet;
typedef CCArray_T<ZBPropertyItem*, ZBPropertyItem*> ZBPropertyItemSet;

//@type ZBPropertyItemIterator | An iterator for ZBPropertyItemSet collections.
//@iex typedef Iterator_T<ZBPropertyItem*> ZBPropertyItemIterator;
typedef Iterator_T<ZBPropertyItem*> ZBPropertyItemIterator;

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemCategory

class AFX_EXT_CLASS ZBPropertyItemCategory : public ZBPropertyItem
{
    ZBPropertyItemCategory( const ZBPropertyItemCategory& d );
    ZBPropertyItemCategory& operator=( const ZBPropertyItemCategory& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemCategory )

public:

    ZBPropertyItemCategory( LPCTSTR pStrName = NULL, bool IsReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemCategory();

    bool PropertyItemExist( int nPropertyID );
    bool PropertyItemExist( LPCTSTR pStrItemName );
    bool PropertyItemExist( ZBPropertyItem* pPropertyItem );

    // Attributes
    void AddPropertyItem( ZBPropertyItem* pPropertyItem );

    bool GetChildrenVisible() const;
    void SetChildrenVisible( bool bVisible = true );

    int GetNumberItems() const;
    int GetNumberEnabledItems() const;

    // Operations
    ZBPropertyItem* GetPropertyItem( int nPropertyID );
    ZBPropertyItem* GetPropertyItem( LPCTSTR pStrItemName );

    ZBPropertyItemSet& GetPropertyItemSet()
    {
        return m_PropertyItemSet;
    };

    const ZBPropertyItemSet& GetPropertyItemSetConst() const
    {
        return m_PropertyItemSet;
    };

    void RemoveAllPropertyItems();

// Datas
private:

    ZBPropertyItemSet    m_PropertyItemSet;
    bool                m_bChildrenVisible;
};

inline ZBPropertyItemCategory::ZBPropertyItemCategory( LPCTSTR    pStrName,
                                                       bool        ReadOnly    /*= false*/,
                                                       bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
    m_bChildrenVisible = false;
}

inline ZBPropertyItemCategory::~ZBPropertyItemCategory()
{
    RemoveAllPropertyItems();
}

inline bool ZBPropertyItemCategory::PropertyItemExist( int nPropertyID )
{
    return ( GetPropertyItem( nPropertyID) ) ? true : false;
}

inline bool ZBPropertyItemCategory::PropertyItemExist( LPCTSTR pStrItemName )
{
    return ( GetPropertyItem( pStrItemName ) ) ? true : false;
}

inline void ZBPropertyItemCategory::AddPropertyItem( ZBPropertyItem* pPropertyItem )
{
    m_PropertyItemSet.Add( pPropertyItem );
}

inline bool ZBPropertyItemCategory::GetChildrenVisible() const
{
    return m_bChildrenVisible;
}

inline void ZBPropertyItemCategory::SetChildrenVisible( bool bVisible )
{
    m_bChildrenVisible = bVisible;
}

inline int ZBPropertyItemCategory::GetNumberItems() const
{
    return m_PropertyItemSet.GetSize();
}

/////////////////////////////////////////////////////////////////////////////

#define BEGIN_LIST_ITEM_DATA_TYPE( new_class ) \
class new_class : public ZBPropertyItemList \
{ \
    new_class( const new_class& d ); \
    new_class& operator=( const new_class& d ); \
public: \
    new_class( LPCTSTR pStrName = NULL ) : ZBPropertyItemList( pStrName ) {}; \
    virtual ~new_class() {}; \
    virtual LPCTSTR GetItemData( int nItem ) const; \
private: \
    static ZBSmartString m_data[]; \
}; \
ZBSmartString new_class::m_data[] = { 
#define ID_STRING_ITEM_DATA( idString ) \
    ZBSmartString(UINT( idString ))
#define LPCTSTR_STRING_ITEM_DATA( string ) \
    ZBSmartString(LPCTSTR( string ))
#define END_LIST_ITEM_DATA_TYPE( new_class ) \
}; \
LPCTSTR new_class::GetItemData( int nItem ) const \
{ \
    return nItem < sizeof( new_class::m_data )/sizeof( ZBSmartString ) ? LPCTSTR( m_data[nItem] ) : NULL; \
}

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_ZBPROPERTYITEM_H__)