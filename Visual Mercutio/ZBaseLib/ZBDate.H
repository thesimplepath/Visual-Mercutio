/****************************************************************************************************************
 *                                                     Classe ZBDate                                                *
 ****************************************************************************************************************
 * Cette classe permet de traiter les données des propriétés de date. Elle s'occupe également des conversions.    *
 *                                                                                                                *
 * Author    : Dominique Aigroz                                                                                    *
 * HeaderFile: ZBDate.h                                                                                            *
 * Created   : 14.12.1994                                                                                        *
 * Modify    :                                                                                                    *
 *                                                                                                                *
 * Call      :                                                                                                    *
 ****************************************************************************************************************/

#if !defined(__ZBDATE_H)
#define __ZBDATE_H

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef _WIN32
class AFX_EXT_CLASS ZBDate : public COleDateTime
{
public:

    // Inherited feature
    typedef COleDateTime inherited;
#else
#include <afx.h>

class AFX_EXT_CLASS ZBDate : public CTime
{
public:

    // Inherited feature
    typedef CTime inherited;
#endif

public:

    ZBDate            ();
    virtual ~ZBDate    ();

    ZBDate( const ZBDate &right );
    ZBDate( time_t time );
    ZBDate( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST = -1 );
    ZBDate( WORD wDosDate, WORD wDosTime, int nDST = -1 );
    ZBDate( const SYSTEMTIME& sysTime, int nDST = -1 );
    ZBDate( const FILETIME& fileTime, int nDST = -1 );
    ZBDate( LPCTSTR lpszDate, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT );

    BOOL    IsEmpty();
    void    Clear();

#ifdef _WIN32
    ZBDate( DATE dt );
    ZBDate( const CTime &right );
    ZBDate( const COleDateTime &right );

    const ZBDate & operator=( const COleDateTime &right );
    const ZBDate & operator=( const CTime &right );
#else
    const ZBDate & operator=( const CTime &right );
#endif

    // Make a clone of the object.
    virtual ZBDate* Clone();

#ifdef _WIN32
    void            SetToday() { *this = COleDateTime::GetCurrentTime(); };
    static ZBDate    GetToday() { return  COleDateTime::GetCurrentTime(); };
#else
    void            SetToday() { *this = CTime::GetCurrentTime(); };
    static ZBDate    GetToday() { return  CTime::GetCurrentTime(); };
#endif

    CString    GetStandardFormatedDate();
    CString    GetStandardFormatedDateTime();
    CString    GetFormatedDate( CString Format );
    CString    GetFormatedDate( UINT nFormatID );
    void    ClearTime();

#ifdef _WIN32
    friend CArchive& AFXAPI operator<<( CArchive& ar, COleDateTime time );
    friend CArchive& AFXAPI operator>>( CArchive& ar, COleDateTime& rtime );
#else
    friend CArchive& AFXAPI operator<<( CArchive& ar, CTime time );
    friend CArchive& AFXAPI operator>>( CArchive& ar, CTime& rtime );
#endif
};

#ifndef _WIN32    // In 16bit
inline ZBDate::ZBDate( const ZBDate &right )
    : CTime( right )
{
}

inline ZBDate::ZBDate( time_t time )
    : CTime( time )
{
}

inline ZBDate::ZBDate( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST )
    : CTime( nYear, nMonth, nDay, nHour, nMin, nSec, nDST )
{
}

inline ZBDate::ZBDate( WORD wDosDate, WORD wDosTime, int nDST )
    : CTime( wDosDate, wDosTime, nDST )
{
}

inline ZBDate::ZBDate( const SYSTEMTIME& sysTime, int nDST )
    : CTime( sysTime, nDST )
{
}

inline ZBDate::ZBDate( const FILETIME& fileTime, int nDST )
    : CTime( fileTime, nDST )
{
}
#else            // In 32bit
inline ZBDate::ZBDate( const ZBDate &right )
    : COleDateTime( right )
{
}

inline ZBDate::ZBDate( const CTime &right )
    : COleDateTime( right.GetYear    (),
                    right.GetMonth    (),
                    right.GetDay    (),
                    right.GetHour    (),
                    right.GetMinute    (),
                    right.GetSecond    () )
{
}

inline ZBDate::ZBDate( const COleDateTime &right )
    : COleDateTime( right )
{
}

inline ZBDate::ZBDate( time_t time )
    : COleDateTime( time )
{
}

inline ZBDate::ZBDate( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST )
    : COleDateTime( nYear, nMonth, nDay, nHour, nMin, nSec )
{
}

inline ZBDate::ZBDate( WORD wDosDate, WORD wDosTime, int nDST )
    : COleDateTime( wDosDate, wDosTime )
{
}

inline ZBDate::ZBDate( const SYSTEMTIME& sysTime, int nDST )
    : COleDateTime( sysTime )
{
}

inline ZBDate::ZBDate( const FILETIME& fileTime, int nDST )
    : COleDateTime( fileTime )
{
}

#endif

inline BOOL ZBDate::IsEmpty()
{
#ifdef _WIN32    // In 32bit
    return ( m_dt <= 0 ) ? TRUE : FALSE;
#else            // In 16bit
    return ( GetTime() <= 0 ) ? TRUE : FALSE;
#endif
}

#endif // __ZBDATE_H