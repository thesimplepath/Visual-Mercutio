#if !defined(_ZBPROPERTYITEMS_H__)
#define _ZBPROPERTYITEMS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZBPropertyItems.h : header file

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zProperty\ZBPropertyItem.h"

#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemString

class ZBPropertyItemString : public ZBPropertyItem
{
    ZBPropertyItemString( const ZBPropertyItemString& d );
    ZBPropertyItemString& operator=( const ZBPropertyItemString& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemString )

public:

    ZBPropertyItemString( LPCTSTR pStrName = NULL, bool IsReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemString();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemString::ZBPropertyItemString( LPCTSTR    pStrName,
                                                   bool        ReadOnly    /*= false*/,
                                                   bool        CanBeEdited    /*= true*/)
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemString::~ZBPropertyItemString()
{
}

inline void ZBPropertyItemString::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( m_strText, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZCInPlaceListBox;

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemList

class AFX_EXT_CLASS ZBPropertyItemList : public ZBPropertyItem
{
    ZBPropertyItemList( const ZBPropertyItemList& d );
    ZBPropertyItemList& operator=( const ZBPropertyItemList& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemList )

public:

    ZBPropertyItemList( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemList();

    virtual void SetData( CStringArray* values )
    {
        m_data = values;
    }

    virtual void GetData( CStringArray* values ) const
    {
        values = m_data;
    }

    void GetData( bool& nItem ) const;

    virtual LPCTSTR GetItemData( int nItem ) const;

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );

    virtual void SetData( const CString sText );
    virtual CString GetData() const;

    void SetItemListData(ZCInPlaceListBox* pWndInPlaceControl);

// Data
private:

    CStringArray*    m_data;
    int                m_nItem;
};

inline ZBPropertyItemList::ZBPropertyItemList( LPCTSTR    pStrName    /*= NULL*/,
                                               bool        ReadOnly    /*= false*/,
                                               bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited ),
      m_data        ( NULL ),
      m_nItem        ( 0 )
{
}

inline ZBPropertyItemList::~ZBPropertyItemList()
{
}

inline void ZBPropertyItemList::GetData( bool& nItem ) const
{
    nItem = ToBool( m_nItem );
}

inline CString ZBPropertyItemList::GetData() const
{
    return m_strText;
}

inline LPCTSTR ZBPropertyItemList::GetItemData( int nItem ) const
{
    return ( m_data && nItem < m_data->GetSize() ) ? static_cast<const char*>( m_data->GetAt( nItem ) ) : NULL;
}

inline void ZBPropertyItemList::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemExtended

class AFX_EXT_CLASS ZBPropertyItemExtended : public ZBPropertyItem
{
    ZBPropertyItemExtended( const ZBPropertyItemExtended& d );
    ZBPropertyItemExtended& operator=( const ZBPropertyItemExtended& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemExtended )

public:

    ZBPropertyItemExtended( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemExtended();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemExtended::ZBPropertyItemExtended( LPCTSTR    pStrName    /*= NULL*/,
                                                       bool        ReadOnly    /*= false*/,
                                                       bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemExtended::~ZBPropertyItemExtended()
{
}

inline void ZBPropertyItemExtended::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZCInPlaceIntelliEdit;

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemIntelliEdit

class AFX_EXT_CLASS ZBPropertyItemIntelliEdit : public ZBPropertyItem
{
    ZBPropertyItemIntelliEdit( const ZBPropertyItemIntelliEdit& d );
    ZBPropertyItemIntelliEdit& operator=( const ZBPropertyItemIntelliEdit& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemIntelliEdit )

public:

    ZBPropertyItemIntelliEdit( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemIntelliEdit();

    virtual void SetData( CStringArray* values )
    {
        m_data = values;
    }

    virtual void GetData( CStringArray* values ) const
    {
        values = m_data;
    }

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );

    virtual void SetData( const CString sText );
    virtual CString GetData() const;

// Data
private:

    CStringArray*    m_data;
    int                m_nItem;
};

inline ZBPropertyItemIntelliEdit::ZBPropertyItemIntelliEdit( LPCTSTR    pStrName    /*= NULL*/,
                                                             bool        ReadOnly    /*= false*/,
                                                             bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited ),
      m_data        ( NULL ),
      m_nItem        ( 0 )
{
}

inline ZBPropertyItemIntelliEdit::~ZBPropertyItemIntelliEdit()
{
}

inline CString ZBPropertyItemIntelliEdit::GetData() const
{
    return m_strText;
}

inline void ZBPropertyItemIntelliEdit::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZCInPlaceMultiLineEdit;

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMultiLineEdit

class AFX_EXT_CLASS ZBPropertyItemMultiLineEdit : public ZBPropertyItem
{
    ZBPropertyItemMultiLineEdit( const ZBPropertyItemMultiLineEdit& d );
    ZBPropertyItemMultiLineEdit& operator=( const ZBPropertyItemMultiLineEdit& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemMultiLineEdit )

public:

    ZBPropertyItemMultiLineEdit( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemMultiLineEdit();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );

    virtual void SetData( const CString sText );
    virtual CString GetData() const;
};

inline ZBPropertyItemMultiLineEdit::ZBPropertyItemMultiLineEdit( LPCTSTR    pStrName    /*= NULL*/,
                                                                 bool        ReadOnly    /*= false*/,
                                                                 bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemMultiLineEdit::~ZBPropertyItemMultiLineEdit()
{
}

inline CString ZBPropertyItemMultiLineEdit::GetData() const
{
    return m_strText;
}

inline void ZBPropertyItemMultiLineEdit::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDuration

class AFX_EXT_CLASS ZBPropertyItemDuration : public ZBPropertyItem
{
    ZBPropertyItemDuration( const ZBPropertyItemDuration& d );
    ZBPropertyItemDuration& operator=( const ZBPropertyItemDuration& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemDuration )

public:

    ZBPropertyItemDuration( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemDuration();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemDuration::ZBPropertyItemDuration( LPCTSTR    pStrName    /*= NULL*/,
                                                       bool        ReadOnly    /*= false*/,
                                                       bool        CanBeEdited    /*= true*/)
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemDuration::~ZBPropertyItemDuration()
{
}


inline void ZBPropertyItemDuration::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDate

class AFX_EXT_CLASS ZBPropertyItemDate : public ZBPropertyItem
{
    ZBPropertyItemDate( const ZBPropertyItemDate& d );
    ZBPropertyItemDate& operator=( const ZBPropertyItemDate& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemDate )

public:

    ZBPropertyItemDate( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemDate();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemDate::ZBPropertyItemDate( LPCTSTR    pStrName    /*= NULL*/,
                                               bool        ReadOnly    /*= false*/,
                                               bool        CanBeEdited    /*= true*/)
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemDate::~ZBPropertyItemDate()
{
}

inline void ZBPropertyItemDate::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

// RS-MODIF 08.08.2005 ajout de la propriété item "time"
/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemTime

class AFX_EXT_CLASS ZBPropertyItemTime : public ZBPropertyItem
{
    ZBPropertyItemTime( const ZBPropertyItemTime& d );
    ZBPropertyItemTime& operator=( const ZBPropertyItemTime& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemTime )

public:

    ZBPropertyItemTime( LPCTSTR pStrName = NULL, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemTime();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemTime::ZBPropertyItemTime( LPCTSTR    pStrName    /*= NULL*/,
                                               bool        ReadOnly    /*= false*/,
                                               bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
}

inline ZBPropertyItemTime::~ZBPropertyItemTime()
{
}

inline void ZBPropertyItemTime::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMenuFileDir

class AFX_EXT_CLASS ZBPropertyItemMenuFileDir : public ZBPropertyItem
{
    ZBPropertyItemMenuFileDir( const ZBPropertyItemMenuFileDir& d );
    ZBPropertyItemMenuFileDir& operator=( const ZBPropertyItemMenuFileDir& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemMenuFileDir )

public:

    ZBPropertyItemMenuFileDir( LPCTSTR    pStrName    = NULL,
                               bool        AsFile        = true,
                               bool        ReadOnly    = false,
                               bool        CanBeEdited    = true );

    ZBPropertyItemMenuFileDir( CMenu* pMenu, bool ReadOnly = false, bool CanBeEdited = true);
    virtual ~ZBPropertyItemMenuFileDir();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );

private:

    enum MenuFileDirType { MFD_MENU, MFD_FILE, MFD_DIRECTORY };

// Data
private:
    MenuFileDirType    m_ControlType;
    CMenu*            m_pMenu;
};

inline ZBPropertyItemMenuFileDir::ZBPropertyItemMenuFileDir( LPCTSTR    pStrName    /*= NULL*/,
                                                             bool        AsFile        /*= true*/,
                                                             bool        ReadOnly    /*= false*/,
                                                             bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( pStrName, ReadOnly, CanBeEdited )
{
    // Sets the right type
    m_ControlType = ( AsFile ) ? MFD_FILE : MFD_DIRECTORY;
}

inline ZBPropertyItemMenuFileDir::ZBPropertyItemMenuFileDir( CMenu*    pMenu,
                                                             bool    ReadOnly    /*= false*/,
                                                             bool    CanBeEdited    /*= true*/ )
    : ZBPropertyItem( NULL, ReadOnly, CanBeEdited ),
      m_pMenu        ( pMenu ),
      m_ControlType    ( MFD_MENU )
{
}

inline ZBPropertyItemMenuFileDir::~ZBPropertyItemMenuFileDir()
{
}

inline void ZBPropertyItemMenuFileDir::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemNumber

class AFX_EXT_CLASS ZBPropertyItemNumber : public ZBPropertyItem
{
    ZBPropertyItemNumber( const ZBPropertyItemNumber& d );
    ZBPropertyItemNumber& operator=( const ZBPropertyItemNumber& d );

protected:

    DECLARE_DYNAMIC( ZBPropertyItemNumber )

public:

    ZBPropertyItemNumber( double Value = 0, bool ReadOnly = false, bool CanBeEdited = true );
    ZBPropertyItemNumber( float Value, bool ReadOnly = false, bool CanBeEdited = true );
    virtual ~ZBPropertyItemNumber();

    // Operations
    virtual void DrawValue( CDC* pDC, CRect& rect );

    virtual void CreateInPlaceControl( CWnd*            pWndParent,
                                       CRect&            rect,
                                       ZIInPlaceEdit*&    pWndInPlaceControl,
                                       CSize            ExtendedSize        = CSize( 0, 0 ) );
};

inline ZBPropertyItemNumber::ZBPropertyItemNumber( double    Value        /*= 0*/,
                                                   bool        ReadOnly    /*= false*/,
                                                   bool        CanBeEdited    /*= true*/)
    : ZBPropertyItem( NULL, ReadOnly, CanBeEdited )
{
    SetData( Value );
}

inline ZBPropertyItemNumber::ZBPropertyItemNumber( float    Value,
                                                   bool        ReadOnly    /*= false*/,
                                                   bool        CanBeEdited    /*= true*/ )
    : ZBPropertyItem( NULL, ReadOnly, CanBeEdited )
{
    SetData( Value );
}

inline ZBPropertyItemNumber::~ZBPropertyItemNumber()
{
}

inline void ZBPropertyItemNumber::DrawValue( CDC* pDC, CRect& rect )
{
    pDC->DrawText( GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER );
}

#endif // !defined(_ZBPROPERTYITEMS_H__)