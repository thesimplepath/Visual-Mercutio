/****************************************************************************
 * ==> PSS_Date ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a date                                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Date.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_Date
//---------------------------------------------------------------------------
PSS_Date::PSS_Date() :
    #ifdef _WIN32
        COleDateTime()
    #else
        CTime()
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(LPCTSTR lpszDate, DWORD dwFlags, LCID lcid) :
    #ifdef _WIN32
        COleDateTime()
    #else
        CTime()
    #endif
{
    #ifdef _WIN32
        try
        {
            ParseDateTime(lpszDate, dwFlags, lcid);
        }
        catch (CMemoryException*)
        {}
    #endif
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    PSS_Date::PSS_Date(DATE dt) :
        COleDateTime()
    {
        m_dt = dt;
    }
#endif
//---------------------------------------------------------------------------
PSS_Date::~PSS_Date()
{}
//---------------------------------------------------------------------------
#ifdef _WIN32
    const PSS_Date& PSS_Date::operator = (const COleDateTime& other)
    {
        COleDateTime::operator = ((COleDateTime&)other);
        return *this;
    }
#endif
//---------------------------------------------------------------------------
const PSS_Date& PSS_Date::operator = (const CTime& other)
{
    #ifdef _WIN32
        COleDateTime ::operator = (other.GetTime());
    #else
        CTime::operator = ((CTime&)other);
    #endif

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_Date& date)
{
    ar << WORD(date.GetYear());
    ar << WORD(date.GetMonth());
    ar << WORD(date.GetDay());
    ar << WORD(date.GetHour());
    ar << WORD(date.GetMinute());
    ar << WORD(date.GetSecond());
    return ar;
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    CArchive& AFXAPI operator << (CArchive& ar, const COleDateTime& time)
#else
    CArchive& AFXAPI operator << (CArchive& ar, const CTime& time)
#endif
{
    ar << WORD(time.GetYear());
    ar << WORD(time.GetMonth());
    ar << WORD(time.GetDay());
    ar << WORD(time.GetHour());
    ar << WORD(time.GetMinute());
    ar << WORD(time.GetSecond());
    return ar;
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    CArchive& AFXAPI operator >> (CArchive& ar, COleDateTime& time)
#else
    CArchive& AFXAPI operator >> (CArchive& ar, CTime& time)
#endif
{
    WORD wData;

    ar >> wData;
    const int year = int(wData);

    ar >> wData;
    const int month = int(wData);

    ar >> wData;
    const int day = int(wData);

    ar >> wData;
    const int hour = int(wData);

    ar >> wData;
    const int minute = int(wData);

    ar >> wData;
    const int second = int(wData);

    #ifdef _WIN32
        time.SetDateTime(year, month, day, hour, minute, second);
    #else
        time = CTime(year, month, day, hour, minute, second);
    #endif

    return ar;
}
//---------------------------------------------------------------------------
PSS_Date* PSS_Date::Clone() const
{
    return new PSS_Date(*this);
}
//---------------------------------------------------------------------------
void PSS_Date::Clear()
{
    m_dt = 0;
}
//---------------------------------------------------------------------------
CString PSS_Date::GetStandardFormattedDate() const
{
    if (IsEmpty())
        return _T("");

    #ifdef _WIN32
        return COleDateTime::Format(_T("%d.%m.%Y"));
    #else
        return CTime::Format(_T("%d.%m.%Y"));
    #endif
}
//---------------------------------------------------------------------------
CString PSS_Date::GetStandardFormattedDateTime() const
{
    if (IsEmpty())
        return _T("");

    #ifdef _WIN32
        return COleDateTime::Format(_T("%d.%m.%Y - %H:%M:%S"));
    #else
        return CTime::Format(_T("%d.%m.%Y - %H:%M:%S"));
    #endif
}
//---------------------------------------------------------------------------
CString PSS_Date::GetFormattedDate(const CString& format) const
{
    if (IsEmpty())
        return _T("");

    #ifdef _WIN32
        return COleDateTime::Format(LPCTSTR(format));
    #else
        return CTime::Format(LPCTSTR(format));
    #endif
}
CString PSS_Date::GetFormattedDate(UINT formatID) const
{
    if (IsEmpty())
        return _T("");

    #ifdef _WIN32
        return COleDateTime::Format(formatID);
    #else
        return CTime::Format(formatID);
    #endif
}
//---------------------------------------------------------------------------
void PSS_Date::ClearTime()
{
    #ifdef _WIN32
        SetDateTime(GetYear(), GetMonth(), GetDay(), 0, 0, 0);
    #else
        *this = CTime(GetYear(), GetMonth(), GetDay(), 0, 0, 0);
    #endif
}
//---------------------------------------------------------------------------
