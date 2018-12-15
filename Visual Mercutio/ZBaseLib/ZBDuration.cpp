/****************************************************************************************************************
 *                                                   Classe ZBDuration                                            *
 ****************************************************************************************************************
 * Cette classe permet de traiter les données des propriétés de durée. Elle s'occupe également des conversions.    *
 ****************************************************************************************************************/

#include "stdafx.h"
#include "ZBDuration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **************************************************************************************************************
// *                                                Fonctions Get                                                *
// **************************************************************************************************************

long ZBDuration::GetHours() const
{
    ASSERT( GetStatus() == valid );

    double dblTemp;

    // Truncate days and scale up
    dblTemp = modf( m_span, &dblTemp );

    long lReturns = (long)( ( dblTemp + GetHalfSecond() ) * (double)m_HourPerDay );

    if ( lReturns >= (long)m_HourPerDay )
    {
        lReturns -= (long)m_HourPerDay;
    }

    return lReturns;
}

long ZBDuration::GetMinutes() const
{
    ASSERT( GetStatus() == valid );

    double dblTemp;

    // Truncate hours and scale up
    dblTemp = modf( m_span * (double)m_HourPerDay, &dblTemp );

    long lReturns = (long)( ( dblTemp + GetHalfSecond() ) * 60 );

    if ( lReturns >= 60 )
    {
        lReturns -= 60;
    }

    return lReturns;
}

long ZBDuration::GetSeconds() const
{
    ASSERT( GetStatus() == valid );

    double dblTemp;

    // Truncate minutes and scale up
    dblTemp = modf( m_span * (double)m_HourPerDay * 60, &dblTemp );

    long lReturns = (long)( ( dblTemp + GetHalfSecond() ) * 60 );

    if ( lReturns >= 60 )
    {
        lReturns -= 60;
    }

    return lReturns;
}

// **************************************************************************************************************
// *                                                Assignment operators                                        *
// **************************************************************************************************************

const ZBDuration& ZBDuration::operator=( double value )
{
    m_span = value;
    SetStatus( valid );
    return *this;
}

const ZBDuration& ZBDuration::operator=( const ZBDuration& right )
{
    m_span            = right.m_span;
    m_status        = right.m_status;
    m_HourPerDay    = right.m_HourPerDay;
    m_DayPerWeek    = right.m_DayPerWeek;
    m_DayPerMonth    = right.m_DayPerMonth;
    m_DayPerYear    = right.m_DayPerYear;

    return *this;
}

// **************************************************************************************************************
// *                                                Math operators                                                *
// **************************************************************************************************************

ZBDuration ZBDuration::operator+( const ZBDuration& right ) const
{
    ZBDuration durationTemp;

    // If either operand Null, result Null
    if ( GetStatus() == null || right.GetStatus() == null )
    {
        durationTemp.SetStatus( null );
        return durationTemp;
    }

    // If either operand Invalid, result Invalid
    if ( GetStatus() == invalid || right.GetStatus() == invalid )
    {
        durationTemp.SetStatus( invalid );
        return durationTemp;
    }

    // Add spans and validate within legal range
    durationTemp.m_span = m_span + right.m_span;
    durationTemp.CheckRange();

    return durationTemp;
}

ZBDuration ZBDuration::operator-( const ZBDuration& right ) const
{
    ZBDuration durationTemp;

    // If either operand Null, result Null
    if ( GetStatus() == null || right.GetStatus() == null )
    {
        durationTemp.SetStatus( null );
        return durationTemp;
    }

    // If either operand Invalid, result Invalid
    if ( GetStatus() == invalid || right.GetStatus() == invalid )
    {
        durationTemp.SetStatus( invalid );
        return durationTemp;
    }

    // Add spans and validate within legal range
    durationTemp.m_span = m_span - right.m_span;
    durationTemp.CheckRange();

    return durationTemp;
}

// **************************************************************************************************************
// *                                                serialization                                                *
// **************************************************************************************************************

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<( CDumpContext& dc, ZBDuration right )
{
    dc << _T( "\nZBDuration Object:" );
    dc << _T( "\n\tduration_status = " )        << (long)right.m_status;
    dc << _T( "\n\tdurationSpan = " )            << right.m_span;
    dc << _T( "\n\tdurationHourPerDay = " )        << right.m_HourPerDay;
    dc << _T( "\n\tdurationDayPerWeek = " )        << right.m_DayPerWeek;
    dc << _T( "\n\tdurationDayPerMonth = " )    << right.m_DayPerMonth;

    return dc << "\n\tdurationDayPerYear = " << right.m_DayPerYear;
}
#endif // _DEBUG

CArchive& AFXAPI operator<<( CArchive& ar, ZBDuration right )
{
    ar << (long)right.m_status;
    ar << right.m_span;
    ar << right.m_HourPerDay;
    ar << right.m_DayPerWeek;
    ar << right.m_DayPerMonth;

    return ar << right.m_DayPerYear;
}

CArchive& AFXAPI operator>>( CArchive& ar, ZBDuration& right )
{
    ar >> (long&)right.m_status;
    ar >> right.m_span;
    ar >> right.m_HourPerDay;
    ar >> right.m_DayPerWeek;
    ar >> right.m_DayPerMonth;

    return ar >> right.m_DayPerYear;
}
