/****************************************************************************
 * ==> PSS_StringFormatter -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a string formatter                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_StringFormatter.h"

 // processsoft
#include "PSS_Global.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ManageValueIntelliEditDlg
//---------------------------------------------------------------------------
PSS_StringFormatter::PSS_StringFormatter()
{}
//---------------------------------------------------------------------------
PSS_StringFormatter::~PSS_StringFormatter()
{}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(int                            value,
                                                PSS_StringFormat::IEFormatType sf,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
        str.Format("%d%c", value * 100, '%');
    else
        str.Format("%d", value);

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(unsigned int                   value,
                                                PSS_StringFormat::IEFormatType sf,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
        str.Format("%u%c", value * 100, '%');
    else
        str.Format("%u", value);

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(short                          value,
                                                PSS_StringFormat::IEFormatType sf,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
        str.Format("%d%c", value * 100, '%');
    else
        str.Format("%d", value);

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(float                          value,
                                                PSS_StringFormat::IEFormatType sf,
                                                std::size_t                    decimalPlace,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
    {
        if (decimalPlace == -1)
        {
            // maximum of 5 decimals because of issues with the rounding between float and double
            str.Format("%.5lf%c", double(value * 100), '%');
            ReplaceDecimalPoint(str, lcid);
            str = RemoveTrailingZero(str, lcid, "%");
        }
        else
        {
            str.Format("%.*lf%c", decimalPlace, double(value * 100), '%');
            ReplaceDecimalPoint(str, lcid);
        }
    }
    else
    if (decimalPlace == -1)
    {
        // maximum of 5 decimals because of issues with the rounding between float and double
        str.Format("%.5lf", double(value));
        ReplaceDecimalPoint(str, lcid);
        str = RemoveTrailingZero(str, lcid);
    }
    else
    {
        str.Format("%.*lf", decimalPlace, double(value));
        ReplaceDecimalPoint(str, lcid);
    }

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(long                           value,
                                                PSS_StringFormat::IEFormatType sf,
                                                std::size_t                    decimalPlace,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
    {
        if (decimalPlace == -1)
        {
            // maximum of 5 decimals because of issues with the rounding between float and double
            str.Format("%.5lf%c", double(value * 100), '%');
            ReplaceDecimalPoint(str, lcid);
            str = RemoveTrailingZero(str, lcid, "%");
        }
        else
        {
            str.Format("%.*lf%c", decimalPlace, double(value * 100), '%');
            ReplaceDecimalPoint(str, lcid);
        }
    }
    else
    if (decimalPlace == -1)
    {
        // maximum of 5 decimals because of issues with the rounding between float and double
        str.Format("%.5lf", double(value));
        ReplaceDecimalPoint(str, lcid);
        str = RemoveTrailingZero(str, lcid);
    }
    else
    {
        str.Format("%.*lf", decimalPlace, double(value));
        ReplaceDecimalPoint(str, lcid);
    }

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(double                         value,
                                                PSS_StringFormat::IEFormatType sf,
                                                std::size_t                    decimalPlace,
                                                bool                           useSeparator,
                                                LPCTSTR                        pCurrency,
                                                LCID                           lcid)
{
    CString str;

    if (sf == PSS_StringFormat::IE_FT_Percentage)
    {
        if (decimalPlace == -1)
        {
            str.Format("%lf%c", value * 100, '%');
            ReplaceDecimalPoint(str, lcid);
            str = RemoveTrailingZero(str, lcid, "%");
        }
        else
        {
            str.Format("%.*lf%c", decimalPlace, value * 100, '%');
            ReplaceDecimalPoint(str, lcid);
        }
    }
    else
    if (decimalPlace == -1)
    {
        str.Format("%lf", value);
        ReplaceDecimalPoint(str, lcid);
        str = RemoveTrailingZero(str, lcid);
    }
    else
    {
        str.Format("%.*lf", decimalPlace, value);
        ReplaceDecimalPoint(str, lcid);
    }

    return (useSeparator || sf == PSS_StringFormat::IE_FT_Accounting || sf == PSS_StringFormat::IE_FT_Accounting1) ?
            ConvertBufferToAmountBuffer(str, sf, pCurrency, lcid) : str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_Date& value, PSS_StringFormat::IEFormatType sf, LCID lcid)
{
    const CString dateStr = PSS_Global::GetDateSeparator(lcid);
    const char    dateSep = dateStr.IsEmpty() ? '/' : dateStr.GetAt(0);
    const CString timeStr = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep = timeStr.IsEmpty() ? ':' : timeStr.GetAt(0);
    CString       str;

    switch (sf)
    {
        case PSS_StringFormat::IE_FT_DateTime:
            // dd/mm/yy hour:min
            str.Format("%d%c%d%c%d %d%c%d",
                       value.GetDay(),
                       dateSep,
                       value.GetMonth(),
                       dateSep,
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute());
            break;

        case PSS_StringFormat::IE_FT_DateTime1:
            // dd/mm/yy hour:min:sec
            str.Format("%d%c%d%c%d %d%c%d%c%d",
                       value.GetDay(),
                       dateSep,
                       value.GetMonth(),
                       dateSep,
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute(),
                       timeSep,
                       value.GetSecond());
            break;

        case PSS_StringFormat::IE_FT_DateTime2:
            // dd/mth/yy hour:min
            str.Format("%d%c%s%c%d %d%c%d",
                       value.GetDay(),
                       dateSep,
                       (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid),
                       dateSep,
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute());
            break;

        case PSS_StringFormat::IE_FT_DateTime3:
            // dd/mth/yy hour:min:sec
            str.Format("%d%c%s%c%d %d%c%d%c%d",
                       value.GetDay(),
                       dateSep,
                       (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid),
                       dateSep,
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute(),
                       timeSep,
                       value.GetSecond());
            break;

        case PSS_StringFormat::IE_FT_DateTime4:
            // dd-mth-yy hour:min
            str.Format("%d-%s-%d %d%c%d",
                       value.GetDay(),
                       (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid),
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute());
            break;

        case PSS_StringFormat::IE_FT_DateTime5:
            // dd-mth-yy hour::min::sec
            str.Format("%d-%s-%d %d%c%d%c%d",
                       value.GetDay(),
                       (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid),
                       value.GetYear(),
                       value.GetHour(),
                       timeSep,
                       value.GetMinute(),
                       timeSep,
                       value.GetSecond());
            break;

        case PSS_StringFormat::IE_FT_Date:
            // dd/mm/yy
            str.Format("%d%c%d%c%d",
                       value.GetDay(),
                       dateSep,
                       value.GetMonth(),
                       dateSep,
                       value.GetYear());
            break;

        case PSS_StringFormat::IE_FT_Date1:
            // dd/mth/yy
            str.Format("%d%c%s%c%d",
                       value.GetDay(),
                       dateSep,
                       (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid),
                       dateSep,
                       value.GetYear());
            break;

        case PSS_StringFormat::IE_FT_Date2:
            // mth-yy
            str.Format("%s-%d", (const char*)PSS_Global::GetShortMonth(value.GetMonth(), lcid), value.GetYear());
            break;

        case PSS_StringFormat::IE_FT_Date3:
            // month-yy
            str.Format("%s-%d", (const char*)PSS_Global::GetFullMonth(value.GetMonth(), lcid), value.GetYear());
            break;

        case PSS_StringFormat::IE_FT_Date4:
            // month dd, yy
            str.Format("%s %d, %d",
                       (const char*)PSS_Global::GetFullMonth(value.GetMonth(), lcid),
                       value.GetDay(),
                       value.GetYear());
            break;

        case PSS_StringFormat::IE_FT_Time:
            // hour:min
            str.Format("%d%c%d%",
                       value.GetHour(),
                       timeSep,
                       value.GetMinute());
            break;

        case PSS_StringFormat::IE_FT_Time1:
            // hour:min:sec
            str.Format("%d%c%d%c%d",
                       value.GetHour(),
                       timeSep,
                       value.GetMinute(),
                       timeSep,
                       value.GetSecond());
            break;

        default:
            break;
    }

    return str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_TimeSpan& value, PSS_StringFormat::IEFormatType sf, LCID lcid)
{
    const CString timeStr = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep = timeStr.IsEmpty() ? ':' : timeStr.GetAt(0);
    CString       str;

    switch (sf)
    {
        case PSS_StringFormat::IE_FT_Time:
            // hour:min
            str.Format("%02d%c%02d%", value.GetHours(), timeSep, value.GetMinutes());
            break;

        case PSS_StringFormat::IE_FT_Time1:
            // hour:min:sec
            str.Format("%02d%c%02d%c%02d",
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Time2:
            // days-hour:min
            str.Format("%d-%02d%c%02d",
                       value.GetDays(),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes());
            break;

        case PSS_StringFormat::IE_FT_Time3:
            // days-hour:min:sec
            str.Format("%d-%02d%c%02d%c%02d",
                       value.GetDays(),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        default:
            break;
    }

    return str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_Duration& value, PSS_StringFormat::IEFormatType sf, LCID lcid)
{
    const CString timeStr = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep = timeStr.IsEmpty() ? ':' : timeStr.GetAt(0);
    CString       str;

    switch (sf)
    {
        case PSS_StringFormat::IE_FT_Duration:
            // days-hour:min
            str.Format("%d-%02d%c%02d",
                       value.GetDays(),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes());
            break;

        case PSS_StringFormat::IE_FT_Duration1:
            // days-hour:min:sec
            str.Format("%d-%02d%c%02d%c%02d",
                       value.GetDays(),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Duration2:
            // nnd hour:min
            str.Format("%d%s %02d%c%02d%c%02d",
                       value.GetDays(),
                       (const char*)PSS_Global::GetDayShortPrefix(lcid),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Duration3:
            // nnd hour:min:sec
            str.Format("%d%s %02d%c%02d%c%02d",
                       value.GetDays(),
                       (const char*)PSS_Global::GetDayShortPrefix(lcid),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Duration4:
            // nn days hour:min
            str.Format("%d %s %02d%c%02d%c%02d",
                       value.GetDays(),
                       (const char*)PSS_Global::GetDayPrefix(lcid),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Duration5:
            // nn days hour:min:sec
            str.Format("%d%s %02d%c%02d%c%02d",
                       value.GetDays(),
                       (const char*)PSS_Global::GetDayShortPrefix(lcid),
                       value.GetHours(),
                       timeSep,
                       value.GetMinutes(),
                       timeSep,
                       value.GetSeconds());
            break;

        case PSS_StringFormat::IE_FT_Duration6:
            // nnd ##:##:##
            if (value.GetSeconds() > 0)
                str.Format("%d%s %02d%c%02d%c%02d",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayShortPrefix(lcid),
                           value.GetHours(),
                           timeSep,
                           value.GetMinutes(),
                           timeSep,
                           value.GetSeconds());
            else
            if (value.GetMinutes() > 0)
                str.Format("%d%s %02d%c%02d",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayShortPrefix(lcid),
                           value.GetHours(),
                           timeSep,
                           value.GetMinutes());
            else
            if (value.GetHours() > 0)
                str.Format("%d%s %02d%s",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayShortPrefix(lcid),
                           value.GetHours(),
                           (const char*)PSS_Global::GetHourShortPrefix(lcid));
            else
                str.Format("%d%s",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayShortPrefix(lcid));

            break;

        case PSS_StringFormat::IE_FT_Duration7:
            // nn days ##:##:##
            if (value.GetSeconds() > 0)
                str.Format("%d %s %02d%c%02d%c%02d",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayPrefix(lcid),
                           value.GetHours(),
                           timeSep,
                           value.GetMinutes(),
                           timeSep,
                           value.GetSeconds());
            else
            if (value.GetMinutes() > 0)
                str.Format("%d %s %02d%c%02d",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayPrefix(lcid),
                           value.GetHours(),
                           timeSep,
                           value.GetMinutes());
            else
            if (value.GetHours() > 0)
                str.Format("%d %s %02d %s",
                           value.GetDays(),
                           (const char*)PSS_Global::GetDayPrefix(lcid),
                           value.GetHours(),
                           (const char*)PSS_Global::GetHourPrefix(lcid));
            else
                str.Format("%d %s", value.GetDays(), (const char*)PSS_Global::GetDayPrefix(lcid));

        default:
            break;
    }

    return str;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(int value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(unsigned int value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(short value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(float value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetDecimalPlace(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(long value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetDecimalPlace(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(double value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value,
                              fmt.GetFormatType(),
                              fmt.GetDecimalPlace(),
                              fmt.GetUseSeparator(),
                              fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                              fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_Date& value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value, fmt.GetFormatType(), fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_TimeSpan& value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value, fmt.GetFormatType(), fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetFormattedBuffer(PSS_Duration& value, const PSS_StringFormat& fmt)
{
    return GetFormattedBuffer(value, fmt.GetFormatType(), fmt.GetLCID());
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(int value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(unsigned int value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(short value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(float value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(long value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(double value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(PSS_Date& value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(PSS_TimeSpan& value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::GetCustomFormattedBuffer(PSS_Duration& value, LPCTSTR pCustom, LCID lcid)
{
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 int&                            value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    double     number;
    CString    str    = buffer;
    const bool result = ConvertBufferToNumber(str, number, sf, pCurrency, lcid);

    // only if no error
    if (result)
        value = int(number);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 unsigned int&                   value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    double     number;
    CString    str    = buffer;
    const bool result = ConvertBufferToNumber(str, number, sf, pCurrency, lcid);

    // only if no error
    if (result)
        value = unsigned int(number);

    return number;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 short&                          value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    double     number;
    CString    str    = buffer;
    const bool result = ConvertBufferToNumber(str, number, sf, pCurrency, lcid);

    // only if no error
    if (result)
        value = short(number);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 float&                          value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    double     number;
    CString    str    = buffer;
    const bool result = ConvertBufferToNumber(str, number, sf, pCurrency, lcid);

    // only if no error
    if (result)
        value = float(number);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 long&                           value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    double     number;
    CString    str    = buffer;
    const bool result = ConvertBufferToNumber(str, number, sf, pCurrency, lcid);

    // only if no error
    if (result)
        value = long(number);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 double&                         value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    CString str = buffer;
    return ConvertBufferToNumber(str, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 PSS_Date&                       value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    // convert a date. Get the separators
    const CString decimalStr = PSS_Global::GetDecimalSeparator(lcid);
    const char    decimalSep = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);
    const CString timeStr    = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep    = timeStr.IsEmpty() ? '.' : timeStr.GetAt(0);

    // parse the string
    const char* pBuffer = (const char*)buffer;
    char        tempDigit[100];
    char*       pTempDigit = tempDigit;

    // check if only a number without any prefix
    bool prefixFound = false;

    for (; *pBuffer; ++pBuffer)
        // if it's a digit, copy the chars to the digit array
        if (isdigit(*pBuffer) || *pBuffer == decimalSep)
        {
            *pTempDigit = *pBuffer;
            ++pTempDigit;
        }
        else
        {
            prefixFound = true;
            break;
        }

    // end of string
    *pTempDigit = 0x00;

    value = tempDigit;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 PSS_TimeSpan&                   value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    // convert a time. Get the separators
    const CString timeStr = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep = timeStr.IsEmpty() ? '.' : timeStr.GetAt(0);

    // parse the string
    const char* pBuffer = (const char*)buffer;
    char        tempDigit[100];
    char*       pTempDigit = tempDigit;
    int         day        = 0;
    int         hour       = 0;
    int         min        = 0;
    int         sec        = 0;
    bool        hourset    = false;

    for (; *pBuffer; ++pBuffer)
    {
        // if it's a digit, copy the chars to the digit array
        if (isdigit(*pBuffer))
        {
            *pTempDigit = *pBuffer;
            ++pTempDigit;
        }
        else
        // time separator, so save the hour
        if (*pBuffer == timeSep)
        {
            // end of string
            *pTempDigit = 0x00;

            // check if hours has already been registered
            if (!hourset)
            {
                hour    = std::atoi(tempDigit);
                hourset = true;
            }
            else
                min = std::atoi(tempDigit);

            // reset temp string
            pTempDigit = tempDigit;
        }
    }

    // end of string
    *pTempDigit = 0x00;
    sec         = std::atoi(tempDigit);

    value.SetDateTimeSpan(day, hour, min, sec);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString&                  buffer,
                                                 PSS_Duration&                   value,
                                                 PSS_StringFormat::IEFormatType& sf,
                                                 LPCTSTR                         pCurrency,
                                                 LCID                            lcid)
{
    // convert a duration. Get the separators
    const CString decimalStr = PSS_Global::GetDecimalSeparator(lcid);
    const char    decimalSep = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);
    const CString timeStr    = PSS_Global::GetTimeSeparator(lcid);
    const char    timeSep    = timeStr.IsEmpty() ? '.' : timeStr.GetAt(0);

    // parse the string
    const char* pBuffer = (const char*)buffer;
    char        tempDigit[100];
    char*       pTempDigit  = tempDigit;
    bool        prefixFound = false;

    // check if only a number without any prefix
    for (; *pBuffer; ++pBuffer)
        // if it's a digit, copy the chars to the digit array
        if (isdigit(*pBuffer) || *pBuffer == decimalSep)
        {
            *pTempDigit = *pBuffer;
            ++pTempDigit;
        }
        else
        {
            prefixFound = true;
            break;
        }

    // if no prefix found, just convert the number and set it
    if (!prefixFound)
    {
        // end of string
        *pTempDigit = 0x00;

        // convert and assign the value
        value = std::atof(tempDigit);

        // ok, valid
        return true;
    }

    // get the localized prefix
    const CString monthPrefix      = PSS_Global::GetMonthPrefix(lcid);
    const CString monthShortPrefix = PSS_Global::GetMonthShortPrefix(lcid);
    const CString weekPrefix       = PSS_Global::GetWeekPrefix(lcid);
    const CString weekShortPrefix  = PSS_Global::GetWeekShortPrefix(lcid);
    const CString dayPrefix        = PSS_Global::GetDayPrefix(lcid);
    const CString dayShortPrefix   = PSS_Global::GetDayShortPrefix(lcid);
    const CString hourPrefix       = PSS_Global::GetHourPrefix(lcid);
    const CString hourShortPrefix  = PSS_Global::GetHourShortPrefix(lcid);

    // alpha buffer used to save prefixes
    char tempAlpha[100];
    char* pTempAlpha = tempAlpha;

    // reassign the buffer start pointer
    pBuffer    = (const char*)buffer;
    pTempDigit = tempDigit;

    // alpha and digit counter used to know what has already been processed
    std::size_t alphaCounter = 0;
    std::size_t digitCounter = 0;

    int  month   = 0;
    int  week    = 0;
    long days    = 0;
    int  hours   = 0;
    int  minutes = 0;
    int  seconds = 0;

    // flag for sequence
    bool dayDone    = false;
    bool hourDone   = false;
    bool minuteDone = false;

    // iterate through chars
    for (; *pBuffer; ++pBuffer)
        // if it's a digit, copy the chars to the digit array
        if (isdigit(*pBuffer) || *pBuffer == decimalSep)
        {
            // check if alpha is already contained in the alpha array. If true, then the value can be converted
            // and assigned to the correct variable
            if (alphaCounter > 0 && digitCounter == 0)
            {
                // set alpha string end
                *pTempAlpha = 0x00;
                ++pTempAlpha;

                // convert the previously saved value
                const long number = std::atol(tempDigit);

                // check what prefix is concerned
                if (!monthPrefix.CompareNoCase(tempAlpha))
                    month = int(number);
                else
                if (!weekPrefix.CompareNoCase(tempAlpha))
                    week = int(number);
                else
                if (!dayPrefix.CompareNoCase(tempAlpha))
                    days = number;
                else
                if (!hourPrefix.CompareNoCase(tempAlpha))
                {
                    hours    = number;
                    hourDone = true;
                }
                else
                if (!monthShortPrefix.CompareNoCase(tempAlpha))
                    month = int(number);
                else
                if (!weekShortPrefix.CompareNoCase(tempAlpha))
                    week = int(number);
                else
                if (!dayShortPrefix.CompareNoCase(tempAlpha))
                    days = number;
                else
                if (!hourShortPrefix.CompareNoCase(tempAlpha))
                {
                    hours    = number;
                    hourDone = true;
                }
                else
                    // unknown prefix, ignore
                    days = 0;

                // reset the alpha counter
                alphaCounter = 0;

                // reset the buffer start pointer
                pTempAlpha = tempAlpha;
            }

            // copy the digit to the array
            *pTempDigit = *pBuffer;
            ++pTempDigit;
            ++digitCounter;
        }
        else
        if (*pBuffer == ' ')
        {
            // space separator, do nothing, just skip it
        }
        else
        if (*pBuffer == '-')
        {
            // standard day separator, check if the array contains digits
            if (digitCounter > 0)
            {
                // set digit string end
                *pTempDigit = 0x00;
                ++pTempDigit;

                // convert the string to number and assign it to days
                days = std::atol(tempDigit);

                // set the sequence flag
                dayDone = true;
            }

            // set the buffer start pointer
            pTempDigit = tempDigit;

            // reset the digit counter to zero
            digitCounter = 0;
        }
        else
        if (*pBuffer == timeSep)
        {
            // standard time separator, check if the array contains digits
            if (digitCounter > 0)
            {
                // set the digit string end
                *pTempDigit = 0x00;
                ++pTempDigit;

                // convert the string to number and assign it to an int value
                const int number = std::atoi(tempDigit);

                // check which is the target value. If hour and minute done, then it's seconds
                if (hourDone && minuteDone)
                    seconds = number;
                else
                if (hourDone)
                {
                    // if only hour done, then it's minutes
                    minutes = number;

                    // set the sequence flag
                    minuteDone = true;
                }
                else
                {
                    // otherwise, it's hours
                    hours = number;

                    // set the sequence flag
                    hourDone = true;
                }
            }

            // set the buffer start pointer
            pTempDigit = tempDigit;

            // reset the digit counter to zero
            digitCounter = 0;
        }
        else
        {
            // any other char should be copied to the alpha array. Before copy it, check if the alpha counter
            // is equals to zero and if the digit counter is greather than zero. If it's the case, the digit
            // should be moved to the alpha array
            if (digitCounter > 0 && !alphaCounter)
            {
                // set digit string end
                *pTempDigit = 0x00;
                ++pTempDigit;

                // reset the digit counter to zero
                digitCounter = 0;

                // reset the buffer start pointer
                pTempDigit = tempDigit;
            }

            // copy the alpha char to the buffer and increment the counter
            *pTempAlpha = *pBuffer;
            ++pTempAlpha;
            ++alphaCounter;
        }

    // all the string was parsed, check if the last digit is alpha
    if (alphaCounter > 0 && !digitCounter)
    {
        // set alpha string end
        *pTempAlpha = 0x00;
        ++pTempAlpha;

        // convert the previous saved value
        const long number = std::atol(tempDigit);

        // check what prefix is concerned
        if (!monthPrefix.CompareNoCase(tempAlpha))
            month = int(number);
        else
        if (!weekPrefix.CompareNoCase(tempAlpha))
            week = int(number);
        else
        if (!dayPrefix.CompareNoCase(tempAlpha))
            days = number;
        else
        if (!hourPrefix.CompareNoCase(tempAlpha))
            hours = number;
        else
        if (!monthShortPrefix.CompareNoCase(tempAlpha))
            month = int(number);
        else
        if (!weekShortPrefix.CompareNoCase(tempAlpha))
            week = int(number);
        else
        if (!dayShortPrefix.CompareNoCase(tempAlpha))
            days = number;
        else
        if (!hourShortPrefix.CompareNoCase(tempAlpha))
            hours = number;
        else
            // unknown prefix, ignore
            days = 0;
    }
    else
    if (digitCounter > 0 && !alphaCounter)
    {
        // set digit string end
        *pTempDigit = 0x00;
        ++pTempDigit;

        // converts the string to number and assign it to an int value
        const int number = std::atoi(tempDigit);

        // check which is the target value. If hour and minute done, then it's seconds
        if (hourDone && minuteDone)
            seconds = number;
        else
        if (hourDone)
            // if only hour done, then it's minutes
            minutes = number;
        else
            // otherwise, it's hours
            hours = number;
    }
    else
        // an error occurred
        return false;

    // set the duration
    value.SetDuration(days, hours, minutes, seconds);

    // check if months and weeks should be added
    if (month > 0)
        value.AddMonth(month);

    if (week > 0)
        value.AddWeek(week);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, int& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, unsigned int& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, short& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, float& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, long& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, double& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_Date& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_Duration& value, LPCTSTR pCurrency, LCID lcid)
{
    PSS_StringFormat::IEFormatType sf;
    return ConvertFormattedBuffer(buffer, value, sf, pCurrency, lcid);
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, int& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, unsigned int& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, short& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, float& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, long& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    bool                           result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, double& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_Date& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertFormattedBuffer(const CString& buffer, PSS_Duration& value, PSS_StringFormat& fmt)
{
    PSS_StringFormat::IEFormatType ft     = fmt.GetFormatType();
    const bool                     result = ConvertFormattedBuffer(buffer,
                                                                   value,
                                                                   ft,
                                                                   fmt.GetCurrency().IsEmpty() ? NULL : (const char*)fmt.GetCurrency(),
                                                                   fmt.GetLCID());
    fmt.SetFormatType(ft);
    return result;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, int& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, unsigned int& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, short& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, float& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, long& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, double& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, PSS_Date& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertCustomFormattedBuffer(const CString& buffer, PSS_Duration& value, LPCTSTR pCustom, LCID lcid)
{
    // not implemented
    return false;
}
//---------------------------------------------------------------------------
void PSS_StringFormatter::ReplaceDecimalPoint(CString& buffer, LCID lcid)
{
    // nothing to do?
    if (buffer.IsEmpty())
        return;

    // get decimal separator
    const CString decimalStr = PSS_Global::GetDecimalSeparator(lcid);
    const char    decimalSep = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);

    // nothing to replace?
    if (decimalSep == '.')
        return;

    // search the decimal point char position
    const int decimalPointPosition = buffer.Find('.');

    // if found, replace
    if (decimalPointPosition != -1)
        buffer.SetAt(decimalPointPosition, decimalSep);
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::RemoveTrailingZero(CString& buffer, LCID lcid, LPCTSTR pEndSymbol)
{
    char  strBuffer[500];
    char* pFinal = strBuffer;

    // get decimal separator
    const CString decimalStr = PSS_Global::GetDecimalSeparator(lcid);
    const char    decimalSep = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);

    int endSymbolPosition = -1;

    // get the currency symbol
    if (pEndSymbol && std::strlen(pEndSymbol) > 0 && (endSymbolPosition = buffer.Find(pEndSymbol)) != -1)
    {
        // remove the currency symbol
        CString   newValue  = buffer.Left(endSymbolPosition);
        const int sizeRight = buffer.GetLength() - endSymbolPosition - std::strlen(pEndSymbol);

        if (sizeRight > 0)
            newValue += buffer.Right(sizeRight);

        // copy the new unformatted buffer to resulting value
        buffer = newValue;
    }

    int   len   = buffer.GetLength();
    char* pC    = buffer.GetBuffer(len + 1);
    int   count = 0;

    // check if the string number is too long. Maximum is 500 for a number
    if (len > 500)
        return _T("#too long");

    // copy the string until the string end is reached or the decimal point is found
    while (*pC && (*pC != decimalSep))
    {
        *pFinal = *pC;
        ++pFinal;
        ++pC;
    }

    // if the string end was reached
    if (*pC && *pC == decimalSep)
    {
        *pFinal = *pC;
        ++pFinal;
        ++pC;

        // keep the last non zero position and initialize it on the decimal separator
        char* pLastZeroPosition = pFinal - 1;

        while (*pC)
        {
            if (*pC != '0')
                pLastZeroPosition = pFinal + 1;

            *pFinal = *pC;
            ++pFinal;
            ++pC;
        }

        // put end of string
        *pLastZeroPosition = 0x00;
    }
    else
        // end of string
        *pFinal = 0x00;

    // release the buffer
    buffer.ReleaseBuffer(-1);

    // was end symbol defined?
    if (pEndSymbol && std::strlen(pEndSymbol))
        return CString(strBuffer) + pEndSymbol;

    // return the formatted buffer
    return strBuffer;
}
//---------------------------------------------------------------------------
CString PSS_StringFormatter::ConvertBufferToAmountBuffer(CString&                       buffer,
                                                         PSS_StringFormat::IEFormatType sf,
                                                         LPCTSTR                        pCurrency,
                                                         LCID                           lcid)
{
    char  strBuffer[500];
    char* pFinal = strBuffer;
    int   len    = buffer.GetLength();
    char* pC     = buffer.GetBuffer(len + 1);
    int   count  = 0;

    // check if the string number is too long. Maximum is 500 for a number
    if (len > 500)
        return _T("#too long");

    const CString thousandStr = PSS_Global::GetThousandSeparator(lcid);
    const char    thousandSep = thousandStr.IsEmpty() ? '\'' : thousandStr.GetAt(0);
    const CString decimalStr  = PSS_Global::GetDecimalSeparator(lcid);
    char const    decimalSep  = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);

    // if negative sign, copy it and move forward
    if (*pC == '-')
    {
        *pFinal = *pC;
        ++pFinal;
        ++pC;
        --len;
    }

    // copy the string until the string end is reached or the decimal point is found
    for (; *pC && (*pC != decimalSep); ++count)
    {
        // add the ' char every 3 digits, calculate if the third digit was reached by substracting
        // the count from the length
        if (count > 0 && ((len - count) % 3) == 0)
        {
            *pFinal = thousandSep;
            ++pFinal;
        }

        *pFinal = *pC;
        ++pFinal;
        ++pC;
    }

    // copy char after the decimal point, till the end
    while (*pC)
    {
        *pFinal = *pC;
        ++pFinal;
        ++pC;
    }

    // if a currency is defined, copy the currency on the string end
    if (pCurrency && strlen(pCurrency) > 0)
    {
        // sdd a space
        *pFinal = ' ';
        ++pFinal;

        // copy all chars till the end
        while (*pCurrency)
        {
            *pFinal = *pCurrency;
            ++pFinal;
            ++pCurrency;
        }
    }

    // end of string
    *pFinal = 0x00;

    // don't forget to release the buffer
    buffer.ReleaseBuffer(-1);

    // return the formatted buffer
    return strBuffer;
}
//---------------------------------------------------------------------------
bool PSS_StringFormatter::ConvertBufferToNumber(CString&                        buffer,
                                                double&                         value,
                                                PSS_StringFormat::IEFormatType& sf,
                                                LPCTSTR                         pCurrency,
                                                LCID                            lcid)
{
    if (buffer.IsEmpty())
    {
        value = 0;
        return true;
    }

    // get the separators
    const CString thousandStr = PSS_Global::GetThousandSeparator(lcid);
    const char    thousandSep = thousandStr.IsEmpty() ? '\'' : thousandStr.GetAt(0);
    const CString decimalStr  = PSS_Global::GetDecimalSeparator(lcid);
    const char    decimalSep  = decimalStr.IsEmpty() ? '.' : decimalStr.GetAt(0);
    int           percPosition;

    // convert the string to a double and assign the result to value. Test if the char % is present.
    // If it's the case, remove it and divide the number by 100. If the % char was found, the ' char
    // can't exists at the same time
    if ((percPosition = buffer.Find('%')) != -1)
    {
        // check if the thousand separator char was found
        if (buffer.Find(thousandSep) != -1)
            // don't assign the value and return false
            return false;

        // replace the percentage sign by a space
        buffer.SetAt(percPosition, ' ');

        // calculate and assign the value
        value = std::atof((const char*)buffer) / 100.0;

        // set the right format
        sf = PSS_StringFormat::IE_FT_Percentage;
        return true;
    }

    int currencyPosition = -1;

    // search for the currency symbol
    if (pCurrency && std::strlen(pCurrency) > 0 && (currencyPosition = buffer.Find(pCurrency)) != -1)
    {
        // remove the currency symbol
        CString   newValue  = buffer.Left(currencyPosition);
        const int sizeRight = buffer.GetLength() - currencyPosition - std::strlen(pCurrency);

        if (sizeRight > 0)
            newValue += buffer.Right(sizeRight);

        // set the currency format
        sf = PSS_StringFormat::IE_FT_Currency;

        // copy the new unformatted buffer to sValue
        buffer = newValue;

        // continue the test to check if amount
    }

    // search for the thousand separator char
    const int decimalPosition = buffer.Find(decimalSep);
    int       thousandPosition;

    // check if the thousand separator char was foud
    if ((thousandPosition = buffer.Find(thousandSep)) != -1)
    {
        // remove the thousand separator char
        const char* pBuffer = (const char*)buffer;
        char        temp[500];
        char*       pTemp = temp;

        for (int i = 0; *pBuffer; ++pBuffer)
            if (*pBuffer != thousandSep)
            {
                *pTemp = *pBuffer;
                ++pTemp;
            }

        // set string end
        *pTemp = 0x00;

        // copy the new unformatted buffer to resulting buffer
        buffer = temp;
    }

    // convert the value
    value = std::atof((const char*)buffer);

    // if thousand separator was found, set the amount format, but if currency was found, don't change the currency format
    if (thousandPosition != -1 && currencyPosition == -1)
        sf = PSS_StringFormat::IE_FT_Accounting;

    return true;
}
//---------------------------------------------------------------------------
