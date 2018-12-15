/////////////////////////////////////////////////////////////////////////////
//@doc String16
//@module String16.cpp | Header of the <c String16> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 04/2002
// 
/////////////////////////////////////////////////////////////////////////////

#ifndef String16_h
#define String16_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZCONVERSIONEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// String16 ////////////////////////////////////////////////////////
// Shim class that converts both 8-bit (foreign) and
// 16-bit (native) strings to 16-bit wideness

class AFX_EXT_CLASS String16
{
public:

    // Native and foreign constructors
    String16( const char* p8 );
    String16( const wchar_t* p16 );

    // Non-virtual destructor (this class is concrete)
    ~String16( void );

    // Native conversion operator
    operator const wchar_t * ( void ) const;

    // Copy constructor
    String16( const String16& ref );

    void setAt( size_t i, char c )
    {
        ASSERT( i < length() );
        m_sz[i] = c;
    }

    size_t length() const
    {
        return wcslen( m_sz );
    }

private:

    // Native wideness string
    wchar_t *m_sz;

    // Is foreign??
    BOOL m_bIsForeign;
};

// Copy constructor.
inline String16::String16( const String16& ref )
    : m_sz            ( (wchar_t *)ref.m_sz ),
    // JMR-MODIF - Le 25 janvier 2006 - Nettoyage des memory leaks, m_bIsForeign doit être à FALSE sur une référence.
      m_bIsForeign    ( FALSE ) //ref.m_bIsForeign )
{
}

// Native constructor is a pass-through.
inline String16::String16( const wchar_t *p16 )
    : m_sz            ( (wchar_t *)p16 ),
      m_bIsForeign    ( FALSE )
{
}

// Simply give out the native wideness string.
inline String16::operator const wchar_t * ( void ) const
{
    return m_sz;
}

// Foreign constructor requires allocation of a native string and conversion.
inline String16::String16( const char *p8 )
    // JMR-MODIF - Le 25 janvier 2006 - Nettoyage des memory leaks, formattage de la variable m_sz.
    : m_sz            ( NULL ),
      m_bIsForeign    ( TRUE )
{
    // Calculate string length
    size_t len = strlen( p8 );

    // Calculate required buffer size (some characters may
    // already occupy 16-bits under DBCS)

    size_t size = mbstowcs( 0, p8, len ) + 1;

    // Alloc native string and convert
    if ( m_sz = new wchar_t[size] )
    {
        mbstowcs( m_sz, p8, size );
    }
}

// Delete native string only if synthesized in foreign constructor.
inline String16::~String16( void )
{
    // JMR-MODIF - Le 25 janvier 2006 - Nettoyage des memory leaks, implémentation du code de destruction.
    if ( m_bIsForeign )
    {
        if ( m_sz )
        {
            delete[] m_sz;
            m_sz = NULL;
        }
    }
}

#endif