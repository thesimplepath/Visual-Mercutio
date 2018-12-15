/****************************************************************************************************************
 *                                                     Classe ZBDate                                                *
 ****************************************************************************************************************
 * Cette classe permet de traiter les données des propriétés de date. Elle s'occupe également des conversions.    *
 ****************************************************************************************************************/

#include <StdAfx.h>

#include "ZBDate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **************************************************************************************************************
// *                                        ZBDate construction/destruction                                        *
// *                                         The default is the zero time.                                        *
// **************************************************************************************************************

ZBDate::ZBDate()
{
}

#ifdef _WIN32
ZBDate::ZBDate( LPCTSTR lpszDate, DWORD dwFlags /*= 0*/, LCID lcid /*= LANG_USER_DEFAULT*/ )
{
    try
    {
        ParseDateTime( lpszDate, dwFlags, lcid );
    }
    catch( CMemoryException* )
    {
    }
}

ZBDate::ZBDate( DATE dt )
{
    m_dt = dt;
}

const ZBDate& ZBDate::operator=( const COleDateTime &right )
{
    this->COleDateTime ::operator=( (COleDateTime&)right );
    return *this;
}

const ZBDate& ZBDate::operator=( const CTime &right )
{
    this->COleDateTime ::operator=( right.GetTime() );
    return *this;
}

void ZBDate::ClearTime()
{
    SetDateTime( GetYear(), GetMonth(), GetDay(), 0, 0, 0 );
}
#else
ZBDate::ZBDate( LPCTSTR lpszDate, DWORD dwFlags /*= 0*/, LCID lcid /*= LANG_USER_DEFAULT*/ )
{
    // In 16bit, do nothing
}

const ZBDate& ZBDate::operator=( const CTime &right )
{
    this->CTime ::operator=( (CTime&)right );
    return *this;
}

void ZBDate::ClearTime()
{
    *this = CTime( GetYear(), GetMonth(), GetDay(), 0, 0, 0 );
}
#endif

void ZBDate::Clear()
{
    m_dt = 0;
}

ZBDate* ZBDate::Clone()
{
    ZBDate*    pObject = new ZBDate( *this );
    return pObject;
}

ZBDate::~ZBDate()
{
}

CString    ZBDate::GetStandardFormatedDate()
{
    if ( IsEmpty() )
    {
        return _T( "" );
    }

#ifdef _WIN32
    return COleDateTime::Format( _T( "%d.%m.%Y" ) );
#else
    return CTime::Format( _T( "%d.%m.%Y" ) );
#endif
}

CString ZBDate::GetStandardFormatedDateTime()
{
    if ( IsEmpty() )
    {
        return _T( "" );
    }

#ifdef _WIN32
    return COleDateTime::Format( _T( "%d.%m.%Y - %H:%M:%S" ) );
#else
    return CTime::Format( _T( "%d.%m.%Y - %H:%M:%S" ) );
#endif
}

CString    ZBDate::GetFormatedDate( UINT nFormatID )
{
    if ( IsEmpty() )
    {
        return _T( "" );
    }

#ifdef _WIN32
    return COleDateTime::Format( nFormatID );
#else
    return CTime::Format( nFormatID );
#endif
}

CString    ZBDate::GetFormatedDate( CString Format )
{
    if ( IsEmpty() )
    {
        return _T( "" );
    }

#ifdef _WIN32
    return COleDateTime::Format( (LPCTSTR)Format );
#else
    return CTime::Format( (LPCTSTR)Format );
#endif
}

// **************************************************************************************************************
// *                                              ZBDate serialization                                            *
// **************************************************************************************************************

#ifdef _WIN32    // In 32bit
CArchive& AFXAPI operator<<( CArchive& ar, COleDateTime time )
{
    ar << (WORD)time.GetYear();
    ar << (WORD)time.GetMonth();
    ar << (WORD)time.GetDay();
    ar << (WORD)time.GetHour();
    ar << (WORD)time.GetMinute();
    ar << (WORD)time.GetSecond();
    return ar;
}

CArchive& AFXAPI operator>>( CArchive& ar, COleDateTime& rtime )
{
    WORD    wData;
    int        Year, Month, Day, Hour, Minute, Second;

    ar >> wData;
    Year = (int)wData;
    ar >> wData;
    Month = (int)wData;
    ar >> wData;
    Day = (int)wData;
    ar >> wData;
    Hour = (int)wData;
    ar >> wData;
    Minute = (int)wData;
    ar >> wData;
    Second = (int)wData;
    rtime.SetDateTime( Year, Month, Day, Hour, Minute, Second );

    return ar;
}
#else            // In 16bit
CArchive& AFXAPI operator<<( CArchive& ar, CTime time )
{
    ar << (WORD)time.GetYear();
    ar << (WORD)time.GetMonth();
    ar << (WORD)time.GetDay();
    ar << (WORD)time.GetHour();
    ar << (WORD)time.GetMinute();
    ar << (WORD)time.GetSecond();
    return ar;
}

CArchive& AFXAPI operator>>( CArchive& ar, CTime& rtime )
{
    WORD    wData;
    int        Year, Month, Day, Hour, Minute, Second;

    ar >> wData;
    Year = (int)wData;
    ar >> wData;
    Month = (int)wData;
    ar >> wData;
    Day = (int)wData;
    ar >> wData;
    Hour = (int)wData;
    ar >> wData;
    Minute = (int)wData;
    ar >> wData;
    Second = (int)wData;
    CTime    Time( Year, Month, Day, Hour, Minute, Second );
    rtime = Time;

    return ar;
}
#endif
