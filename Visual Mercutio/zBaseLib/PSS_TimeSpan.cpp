/****************************************************************************
 * ==> PSS_TimeSpan --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a time span                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TimeSpan.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_TimeSpan
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan() :
    COleDateTimeSpan()
{}
//---------------------------------------------------------------------------
PSS_TimeSpan::~PSS_TimeSpan()
{}
//---------------------------------------------------------------------------
const PSS_TimeSpan& PSS_TimeSpan::operator = (const PSS_TimeSpan& other)
{
    COleDateTimeSpan::operator = ((COleDateTimeSpan&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_TimeSpan& PSS_TimeSpan::operator = (const CTimeSpan& other)
{
    SetDateTimeSpan(long(other.GetDays()), other.GetHours(), other.GetMinutes(), other.GetSeconds());
    return *this;
}
//---------------------------------------------------------------------------
const PSS_TimeSpan& PSS_TimeSpan::operator = (const COleDateTimeSpan& other)
{
    COleDateTimeSpan::operator = ((COleDateTimeSpan&)other);
    return *this;
}
//---------------------------------------------------------------------------
PSS_TimeSpan* PSS_TimeSpan::Clone() const
{
    return new PSS_TimeSpan(*this);
}
//---------------------------------------------------------------------------
void PSS_TimeSpan::Clear()
{
    m_span = 0;
}
//---------------------------------------------------------------------------
CString PSS_TimeSpan::GetStandardFormattedTimeSpan() const
{
    if (IsEmpty())
        return _T("");

    return COleDateTimeSpan::Format(_T("%H:%M:%S"));
}
//---------------------------------------------------------------------------
CString PSS_TimeSpan::GetFormattedTimeSpan(const CString& format) const
{
    if (IsEmpty())
        return _T("");

    return COleDateTimeSpan::Format(LPCTSTR(format));
}
//---------------------------------------------------------------------------
CString PSS_TimeSpan::GetFormattedTimeSpan(UINT formatID) const
{
    if (IsEmpty())
        return _T("");

    return COleDateTimeSpan::Format(formatID);
}
//---------------------------------------------------------------------------
