/****************************************************************************
 * ==> PSS_Duration --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a duration and time conversion class              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Duration.h"

// std
#include <cmath>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_Duration
//---------------------------------------------------------------------------
const PSS_Duration& PSS_Duration::operator = (const PSS_Duration& other)
{
    m_Status      = other.m_Status;
    m_Span        = other.m_Span;
    m_HourPerDay  = other.m_HourPerDay;
    m_DayPerWeek  = other.m_DayPerWeek;
    m_DayPerMonth = other.m_DayPerMonth;
    m_DayPerYear  = other.m_DayPerYear;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_Duration& PSS_Duration::operator = (double value)
{
    m_Span   = value;
    m_Status = IEStatus::IE_S_Valid;

    return *this;
}
//---------------------------------------------------------------------------
PSS_Duration PSS_Duration::operator + (const PSS_Duration& other) const
{
    PSS_Duration durationTemp;

    // if either operand IE_S_Null, result IE_S_Null
    if (m_Status == IEStatus::IE_S_Null || other.m_Status == IEStatus::IE_S_Null)
    {
        durationTemp.m_Status = IEStatus::IE_S_Null;
        return durationTemp;
    }

    // if either operand IE_S_Invalid, result IE_S_Invalid
    if (m_Status == IEStatus::IE_S_Invalid || other.m_Status == IEStatus::IE_S_Invalid)
    {
        durationTemp.m_Status = IEStatus::IE_S_Invalid;
        return durationTemp;
    }

    // add spans and validate within legal range
    durationTemp.m_Span = m_Span + other.m_Span;
    durationTemp.CheckRange();

    return durationTemp;
}
//---------------------------------------------------------------------------
PSS_Duration PSS_Duration::operator - (const PSS_Duration& other) const
{
    PSS_Duration durationTemp;

    // if either operand IE_S_Null, result IE_S_Null
    if (m_Status == IEStatus::IE_S_Null || other.m_Status == IEStatus::IE_S_Null)
    {
        durationTemp.m_Status = IEStatus::IE_S_Null;
        return durationTemp;
    }

    // if either operand IE_S_Invalid, result IE_S_Invalid
    if (m_Status == IEStatus::IE_S_Invalid || other.m_Status == IEStatus::IE_S_Invalid)
    {
        durationTemp.m_Status = IEStatus::IE_S_Invalid;
        return durationTemp;
    }

    // add spans and validate within legal range
    durationTemp.m_Span = m_Span - other.m_Span;
    durationTemp.CheckRange();

    return durationTemp;
}
//---------------------------------------------------------------------------
long PSS_Duration::GetHours() const
{
    PSS_Assert(m_Status == IEStatus::IE_S_Valid);

    double dblTemp;

    // truncate days and scale up
    dblTemp = std::modf(m_Span, &dblTemp);

    long result = long((dblTemp + GetHalfSecond()) * double(m_HourPerDay));

    if (result >= long(m_HourPerDay))
        result -= long(m_HourPerDay);

    return result;
}
//---------------------------------------------------------------------------
long PSS_Duration::GetMinutes() const
{
    PSS_Assert(m_Status == IEStatus::IE_S_Valid);

    double dblTemp;

    // truncate hours and scale up
    dblTemp = std::modf(m_Span * double(m_HourPerDay), &dblTemp);

    long result = long((dblTemp + GetHalfSecond()) * 60.0);

    if (result >= 60)
        result -= 60;

    return result;
}
//---------------------------------------------------------------------------
long PSS_Duration::GetSeconds() const
{
    PSS_Assert(m_Status == IEStatus::IE_S_Valid);

    double dblTemp;

    // Truncate minutes and scale up
    dblTemp = std::modf(m_Span * double(m_HourPerDay) * 60.0, &dblTemp);

    long result = long((dblTemp + GetHalfSecond()) * 60.0);

    if (result >= 60)
        result -= 60;

    return result;
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator << (CArchive& ar, const PSS_Duration& duration)
{
    ar << long(duration.GetStatus());
    ar << duration.GetSpan();
    ar << duration.GetHourPerDay();
    ar << duration.GetDayPerWeek();
    ar << duration.GetDayPerMonth();
    ar << duration.GetDayPerYear();

    return ar;
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator >> (CArchive& ar, PSS_Duration& duration)
{
    long status;
    ar >> status;
    duration.SetStatus(PSS_Duration::IEStatus(status));

    double span;
    ar >> span;
    duration.SetSpan(span);

    int value;

    ar >> value;
    duration.SetHourPerDay(value);

    ar >> value;
    duration.SetDayPerWeek(value);

    ar >> value;
    duration.SetDayPerMonth(value);

    ar >> value;
    duration.SetDayPerYear(value);

    return ar;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    CDumpContext& AFXAPI operator << (CDumpContext& dc, const PSS_Duration& duration)
    {
        dc << _T("\nPSS_Duration Object:");
        dc << _T("\n\tduration_status = ")     << long(duration.GetStatus());
        dc << _T("\n\tdurationSpan = ")        << duration.GetSpan();
        dc << _T("\n\tdurationHourPerDay = ")  << duration.GetHourPerDay();
        dc << _T("\n\tdurationDayPerWeek = ")  << duration.GetDayPerWeek();
        dc << _T("\n\tdurationDayPerMonth = ") << duration.GetDayPerMonth();
        dc << _T("\n\tdurationDayPerYear = ")  << duration.GetDayPerYear();

        return dc;
    }
#endif
//---------------------------------------------------------------------------
