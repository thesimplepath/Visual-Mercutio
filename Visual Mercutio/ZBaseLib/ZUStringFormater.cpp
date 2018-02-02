// ZUStringFormater.cpp: implementation of the ZUStringFormatter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUStringFormater.h"

#include "ZAGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUStringFormatter::ZUStringFormatter()
{
}

ZUStringFormatter::~ZUStringFormatter()
{

}


// Convert value to string 
CString	ZUStringFormatter::GetFormattedBuffer( int value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
		s.Format( "%d%c", value*100, '%' );
	else
		s.Format( "%d", value );
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( unsigned int value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
		s.Format( "%u%c", value*100, '%' );
	else
		s.Format( "%u", value );
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( short value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
		s.Format( "%d%c", value*100, '%' );
	else
		s.Format( "%d", value );
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( float value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, size_t DecimalPlace /*= 0*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
	{
		if (DecimalPlace == -1)
		{
			// Maximum of 5 decimals Prb. with the rounding between float and double
			s.Format( "%.5lf%c", (double)(value*100), '%' );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid, "%" );
		}
		else
		{
			s.Format( "%.*lf%c", DecimalPlace, (double)(value*100), '%' );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	else
	{
		if (DecimalPlace == -1)
		{
			// Maximum of 5 decimals Prb. with the rounding between float and double
			s.Format( "%.5lf", (double)value );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid );
		}
		else
		{
			s.Format( "%.*lf", DecimalPlace, (double)value );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( long value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, size_t DecimalPlace /*= 0*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
	{
		if (DecimalPlace == -1)
		{
			// Maximum of 5 decimals Prb. with the rounding between long and double
			s.Format( "%.5lf%c", (double)(value*100), '%' );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid, "%" );
		}
		else
		{
			s.Format( "%.*lf%c", DecimalPlace, (double)(value*100), '%' );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	else
	{
		if (DecimalPlace == -1)
		{
			// Maximum of 5 decimals Prb. with the rounding between float and double
			s.Format( "%.5lf", (double)value );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid );
		}
		else
		{
			s.Format( "%.*lf", DecimalPlace, (double)value );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( double value, ZBStringFormat::FormatType sf /*= ZBStringFormat::General*/, size_t DecimalPlace /*= 0*/, bool UseSeparator /*= false*/, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString s;
	if (sf == ZBStringFormat::Percentage)
	{
		if (DecimalPlace == -1)
		{
			s.Format( "%lf%c", value*100, '%' );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid, "%" );
		}
		else
		{
			s.Format( "%.*lf%c", DecimalPlace, value*100, '%' );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	else
	{
		if (DecimalPlace == -1)
		{
			s.Format( "%lf", value );
			ReplaceDecimalPoint( s, lcid );
			s = RemoveTrailingZero( s, lcid );
		}
		else
		{
			s.Format( "%.*lf", DecimalPlace, value );
			ReplaceDecimalPoint( s, lcid );
		}
	}
	return (UseSeparator || 
		    sf == ZBStringFormat::Accounting ||
			sf == ZBStringFormat::Accounting1) ? ConvertBufferToAmountBuffer( s, sf, pCurrency, lcid ) : s;
}

CString	ZUStringFormatter::GetFormattedBuffer( ZBDate& value, ZBStringFormat::FormatType sf /*= ZBStringFormat::Date*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString DateStr = ZAGlobal::GetDateSeparator( lcid );
	char DateSep = (DateStr.IsEmpty()) ? '/' : DateStr.GetAt(0);
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? ':' : TimeStr.GetAt(0);

	CString s;
	switch (sf)
	{
		case ZBStringFormat::DateTime:	// dd/mm/yy hour:min
		{
			s.Format( "%d%c%d%c%d %d%c%d", 
						value.GetDay(), DateSep,
						value.GetMonth(), DateSep,
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute() 
					);
			break;
		}
		case ZBStringFormat::DateTime1:	// dd/mm/yy hour:min:sec
		{
			s.Format( "%d%c%d%c%d %d%c%d%c%d", 
						value.GetDay(), DateSep,
						value.GetMonth(), DateSep,
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute(), TimeSep,
						value.GetSecond()
					);
			break;
		}
		case ZBStringFormat::DateTime2:	// dd/mth/yy hour:min
		{
			s.Format( "%d%c%s%c%d %d%c%d", 
						value.GetDay(), DateSep,
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ), DateSep,
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute() 
					);
			break;
		}
		case ZBStringFormat::DateTime3:	// dd/mth/yy hour:min:sec
		{
			s.Format( "%d%c%s%c%d %d%c%d%c%d", 
						value.GetDay(), DateSep,
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ), DateSep,
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute(), TimeSep,
						value.GetSecond()
					);
			break;
		}
		case ZBStringFormat::DateTime4:	// dd-mth-yy hour:min
		{
			s.Format( "%d-%s-%d %d%c%d", 
						value.GetDay(), 
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ),
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute() 
					);
			break;
		}
		case ZBStringFormat::DateTime5:	// dd-mth-yy hour::min::sec
		{
			s.Format( "%d-%s-%d %d%c%d%c%d", 
						value.GetDay(), 
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ),
						value.GetYear(), 
						value.GetHour(), TimeSep,
						value.GetMinute(), TimeSep,
						value.GetSecond()
					);
			break;
		}
		case ZBStringFormat::Date:		// dd/mm/yy
		{
			s.Format( "%d%c%d%c%d", 
						value.GetDay(), DateSep,
						value.GetMonth(), DateSep,
						value.GetYear()
					);
			break;
		}
		case ZBStringFormat::Date1:		// dd/mth/yy
		{
			s.Format( "%d%c%s%c%d", 
						value.GetDay(), DateSep,
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ), DateSep,
						value.GetYear()
					);
			break;
		}
		case ZBStringFormat::Date2:		// mth-yy
		{
			s.Format( "%s-%d", 
						(const char*)ZAGlobal::GetShortMonth( value.GetMonth(), lcid ),
						value.GetYear()
					);
			break;
		}
		case ZBStringFormat::Date3:		// month-yy
		{
			s.Format( "%s-%d", 
						(const char*)ZAGlobal::GetFullMonth( value.GetMonth(), lcid ),
						value.GetYear()
					);
			break;
		}
		case ZBStringFormat::Date4:		// month dd, yy
		{
			s.Format( "%s %d, %d", 
						(const char*)ZAGlobal::GetFullMonth( value.GetMonth(), lcid ),
						value.GetDay(),
						value.GetYear()
					);
			break;
		}
		case ZBStringFormat::Time:		// hour:min
		{
			s.Format( "%d%c%d%", 
						value.GetHour(), TimeSep,
						value.GetMinute()
					);
			break;
		}
		case ZBStringFormat::Time1:		// hour:min:sec
		{
			s.Format( "%d%c%d%c%d", 
						value.GetHour(), TimeSep,
						value.GetMinute(), TimeSep,
						value.GetSecond()
					);
			break;
		}
		default:
			break;
	}
	return s;
}

CString	ZUStringFormatter::GetFormattedBuffer( ZBTimeSpan& value, ZBStringFormat::FormatType sf /*= ZBStringFormat::Time*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? ':' : TimeStr.GetAt(0);

	CString s;
	switch (sf)
	{
		case ZBStringFormat::Time:		// hour:min
		{
			s.Format( "%02d%c%02d%", 
						value.GetHours(), TimeSep,
						value.GetMinutes()
					);
			break;
		}
		case ZBStringFormat::Time1:		// hour:min:sec
		{
			s.Format( "%02d%c%02d%c%02d", 
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Time2:		// days-hour:min
		{
			s.Format( "%d-%02d%c%02d", 
						value.GetDays(), 
						value.GetHours(), TimeSep,
						value.GetMinutes()
					);
			break;
		}
		case ZBStringFormat::Time3:		// days-hour:min:sec
		{
			s.Format( "%d-%02d%c%02d%c%02d", 
						value.GetDays(), 
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		default:
			break;
	}
	return s;
}


CString	ZUStringFormatter::GetFormattedBuffer( ZBDuration& value, ZBStringFormat::FormatType sf /*= ZBStringFormat::Duration*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? ':' : TimeStr.GetAt(0);

	CString s;
	switch (sf)
	{
		case ZBStringFormat::Duration:		// days-hour:min
		{
			s.Format( "%d-%02d%c%02d", 
						value.GetDays(), 
						value.GetHours(), TimeSep,
						value.GetMinutes()
					);
			break;
		}
		case ZBStringFormat::Duration1:		// days-hour:min:sec
		{
			s.Format( "%d-%02d%c%02d%c%02d", 
						value.GetDays(), 
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Duration2:		// nnd hour:min
		{
			s.Format( "%d%s %02d%c%02d%c%02d", 
						value.GetDays(), 
						(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Duration3:		// nnd hour:min:sec
		{
			s.Format( "%d%s %02d%c%02d%c%02d", 
						value.GetDays(), 
						(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Duration4:		// nn days hour:min
		{
			s.Format( "%d %s %02d%c%02d%c%02d", 
						value.GetDays(), 
						(const char*)ZAGlobal::GetDayPrefix( lcid ),
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Duration5:		// nn days hour:min:sec
		{
			s.Format( "%d%s %02d%c%02d%c%02d", 
						value.GetDays(),
						(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
						value.GetHours(), TimeSep,
						value.GetMinutes(), TimeSep,
						value.GetSeconds()
					);
			break;
		}
		case ZBStringFormat::Duration6:		// nnd ##:##:##
		{
			if (value.GetSeconds() > 0)
			{
				s.Format( "%d%s %02d%c%02d%c%02d", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
							value.GetHours(), TimeSep,
							value.GetMinutes(), TimeSep,
							value.GetSeconds()
						);
			}
			else
			if (value.GetMinutes() > 0)
			{
				s.Format( "%d%s %02d%c%02d", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
							value.GetHours(), TimeSep,
							value.GetMinutes()
						);
			}
			else
			if (value.GetHours() > 0)
			{
				s.Format( "%d%s %02d%s", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayShortPrefix( lcid ),
							value.GetHours(),
							(const char*)ZAGlobal::GetHourShortPrefix( lcid )
						);
			}
			else
			{
				s.Format( "%d%s", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayShortPrefix( lcid )
						);
			}
			break;
		}
		case ZBStringFormat::Duration7:		// nn days ##:##:##
		{
			if (value.GetSeconds() > 0)
			{
				s.Format( "%d %s %02d%c%02d%c%02d", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayPrefix( lcid ),
							value.GetHours(), TimeSep,
							value.GetMinutes(), TimeSep,
							value.GetSeconds()
						);
			}
			else
			if (value.GetMinutes() > 0)
			{
				s.Format( "%d %s %02d%c%02d", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayPrefix( lcid ),
							value.GetHours(), TimeSep,
							value.GetMinutes()
						);
			}
			else
			if (value.GetHours() > 0)
			{
				s.Format( "%d %s %02d %s", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayPrefix( lcid ),
							value.GetHours(),
							(const char*)ZAGlobal::GetHourPrefix( lcid )
						);
			}
			else
			{
				s.Format( "%d %s", 
							value.GetDays(),
							(const char*)ZAGlobal::GetDayPrefix( lcid )
						);
			}
		}
		default:
			break;
	}
	return s;
}

CString	ZUStringFormatter::GetFormattedBuffer( int value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( unsigned int value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( short value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( float value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetDecimalPlace(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( long value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetDecimalPlace(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( double value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.GetDecimalPlace(), fmt.GetUseSeparator(), (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( ZBDate& value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( ZBTimeSpan& value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.Getlcid() );
}

CString	ZUStringFormatter::GetFormattedBuffer( ZBDuration& value, ZBStringFormat& fmt )
{
	return ZUStringFormatter::GetFormattedBuffer( value, fmt.Getft(), fmt.Getlcid() );
}

// Convert value to custom string 
CString	ZUStringFormatter::GetCustomFormattedBuffer( int value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( unsigned int value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( short value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( float value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( long value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( double value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( ZBDate& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( ZBTimeSpan& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

CString	ZUStringFormatter::GetCustomFormattedBuffer( ZBDuration& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return _T("");
}

// Convert string to value
bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, int& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	double dValue;
	bool RetValue = ZUStringFormatter::ConvertBufferToNumber( buffer, dValue, sf, pCurrency, lcid );
	// Only if no error
	if (RetValue)
		value = (int)dValue;
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, unsigned int& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	double dValue;
	bool RetValue = ZUStringFormatter::ConvertBufferToNumber( buffer, dValue, sf, pCurrency, lcid );
	// Only if no error
	if (RetValue)
		value = (unsigned int)dValue;
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, short& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	double dValue;
	bool RetValue = ZUStringFormatter::ConvertBufferToNumber( buffer, dValue, sf, pCurrency, lcid );
	// Only if no error
	if (RetValue)
		value = (short)dValue;
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, float& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	double dValue;
	bool RetValue = ZUStringFormatter::ConvertBufferToNumber( buffer, dValue, sf, pCurrency, lcid );
	// Only if no error
	if (RetValue)
		value = (float)dValue;
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, long& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	double dValue;
	bool RetValue = ZUStringFormatter::ConvertBufferToNumber( buffer, dValue, sf, pCurrency, lcid );
	// Only if no error
	if (RetValue)
		value = (long)dValue;
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, double& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	return ZUStringFormatter::ConvertBufferToNumber( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDate& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// RS-MODIF 05.08.2005 implémentation pour gestion de date
	// Convert a date

	// Retreive the separators
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? '.' : TimeStr.GetAt(0);

	// Now parse the string
	const char*	pBuffer = (const char*)buffer;
	char szTempDigit[100];
	char* pTempDigit = szTempDigit;

	// First, check if only a number without any prefix
	bool PrefixFound = false;
	for (; *pBuffer ; ++pBuffer)
	{
		// If it is a digit, copy the chars into the digit array
		if (isdigit(*pBuffer) || *pBuffer == DecimalSep)
		{
			*pTempDigit++ = *pBuffer;
		}
		else
		{
			PrefixFound = true;
			break;
		}
	}
	
	*pTempDigit = 0x00; // End of string
		
	value = szTempDigit;

	return true;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// RS-MODIF 08.08.2005 implémentation pour gestion de temps
	// Convert a time
	// RS-MODIF 16.08.2005 prise en charge des secondes

	// Retreive the separators
	//CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	//char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? '.' : TimeStr.GetAt(0);

	// Now parse the string
	const char*	pBuffer = (const char*)buffer;
	char szTempDigit[100];
	char* pTempDigit = szTempDigit;
	int day = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;
	bool hourset = false; // check if hours has already been registered

	for (; *pBuffer ; ++pBuffer)
	{
		// If it is a digit, copy the chars into the digit array
		if (isdigit(*pBuffer))
		{
			*pTempDigit++ = *pBuffer;
		}
		else if (*pBuffer == TimeSep) // time separator, so save the hour
		{
			*pTempDigit = 0x00; // End of string
			if (!hourset)
			{
			hour = atoi(szTempDigit);
			hourset = true;
			}
			else min = atoi(szTempDigit);
			pTempDigit = szTempDigit; // reset temp string
		}
	}
	
	*pTempDigit = 0x00; // End of string
	sec = atoi(szTempDigit);
		
	value.SetDateTimeSpan(day,hour,min,sec);

	return true;
}


bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDuration& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Convert a duration

	// Retreive the separators
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);
	CString TimeStr = ZAGlobal::GetTimeSeparator( lcid );
	char TimeSep = (TimeStr.IsEmpty()) ? '.' : TimeStr.GetAt(0);

	// Now parse the string
	const char*	pBuffer = (const char*)buffer;
	char szTempDigit[100];
	char* pTempDigit = szTempDigit;

	// First, check if only a number without any prefix
	bool PrefixFound = false;
	for (; *pBuffer ; ++pBuffer)
	{
		// If it is a digit, copy the chars into the digit array
		if (isdigit(*pBuffer) || *pBuffer == DecimalSep)
		{
			*pTempDigit++ = *pBuffer;
		}
		else
		{
			PrefixFound = true;
			break;
		}
	}
	// If no prefix found, just convert the number and set it
	if (PrefixFound == false)
	{
		*pTempDigit = 0x00; // End of string
		// Convert and assigns the value
		double dValue = atof( szTempDigit );
		value = dValue;
		// OK, valid
		return true;
	}

	// Otherwise, we have prefix to process

	// Retreive all prefixes function of the lang id
	CString MonthPrefix = ZAGlobal::GetMonthPrefix( lcid );
	CString MonthShortPrefix = ZAGlobal::GetMonthShortPrefix( lcid );
	CString WeekPrefix = ZAGlobal::GetWeekPrefix( lcid );
	CString WeekShortPrefix = ZAGlobal::GetWeekShortPrefix( lcid );
	CString DayPrefix = ZAGlobal::GetDayPrefix( lcid );
	CString DayShortPrefix = ZAGlobal::GetDayShortPrefix( lcid );
	CString HourPrefix = ZAGlobal::GetHourPrefix( lcid );
	CString HourShortPrefix = ZAGlobal::GetHourShortPrefix( lcid );

	// Alpha buffer used to save prefixes
	char szTempAlpha[100];
	char* pTempAlpha = szTempAlpha;
	// Reassigns the start of buffers
	pBuffer = (const char*)buffer;
	pTempDigit = szTempDigit;

	// Alpha and Digit counter used to know what has already been processed
	size_t AlphaCounter = 0;
	size_t DigitCounter = 0;

	int  Month = 0;
	int  Week = 0;
	long lDays = 0;
	int  nMinutes = 0;
	int  nHours = 0;
	int  nSeconds = 0;

	// Flag for sequence
	bool DayDone = false;
	bool HourDone = false;
	bool MinuteDone = false;

	for (; *pBuffer ; ++pBuffer)
	{
		// If it is a digit, copy the chars into the digit array
		if (isdigit(*pBuffer) || *pBuffer == DecimalSep)
		{
			// But before, check if we already have alpha into the array of alpha
			// If it is the case, that means we are able to convert the value
			// and to assigns it to the right variable
			if (AlphaCounter > 0 && DigitCounter == 0)
			{
				// Sets end of string for alpha.
				*pTempAlpha++ = 0x00;

				// Before taking other values, Convert the previous saved value first.
				long lValue = atol( szTempDigit );
				// Check what prefix is concerned
				if (MonthPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					Month = (int)lValue;
				}
				else
				if (WeekPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					Week = (int)lValue;
				}
				else
				if (DayPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					lDays = lValue;
				}
				else
				if (HourPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					nHours = lValue;
					HourDone = true;
				}
				else
				if (MonthShortPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					Month = (int)lValue;
				}
				else
				if (WeekShortPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					Week = (int)lValue;
				}
				else
				if (DayShortPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					lDays = lValue;
				}
				else
				if (HourShortPrefix.CompareNoCase( szTempAlpha ) == 0)
				{
					nHours = lValue;
					HourDone = true;
				}
				else
				{
					// Unknown prefix, ignore
					lDays = 0;
				}
				// Before continuing, reset the alpha counter
				AlphaCounter = 0;
				// And the start of pointer buffer
				pTempAlpha = szTempAlpha;
			}
			// Copy the digit to the array
			*pTempDigit++ = *pBuffer;
			++DigitCounter;
		}
		else
		// If we have a space
		if (*pBuffer == ' ')
		{
			// Do nothing, just skip it
		}
		else
		// If we have a standard day separator
		if (*pBuffer == '-')
		{
			// Then we must have digit in the array
			if (DigitCounter > 0)
			{
				// Sets end of string for digit.
				*pTempDigit++ = 0x00;
				// Converts the string to number and assigns it to days
				lDays = atol( szTempDigit );
				// Sets the sequence flag
				DayDone = true;
			}
			// Sets the start of pointer buffer
			pTempDigit = szTempDigit;
			// Reset the digit counter to zero
			DigitCounter = 0;
		}
		else
		// If we have a standard time separator
		if (*pBuffer == TimeSep)
		{
			// Then we must have digit in the array
			if (DigitCounter > 0)
			{
				// Sets end of string for digit.
				*pTempDigit++ = 0x00;
				// Converts the string to number and assigns it to an int value
				int iValue = atoi( szTempDigit );
				// Now check to wich value it is destinated
				// If hour and minute done, then it is seconds
				if (HourDone && MinuteDone)
				{
					nSeconds = iValue;
				}
				else
				// If only hour done, then it is minutes
				if (HourDone)
				{
					nMinutes = iValue;
					// Sets the sequence flag
					MinuteDone = true;
				}
				else
				// Otherwise, it is hours
				{
					nHours = iValue;
					// Sets the sequence flag
					HourDone = true;
				}
			}
			// Sets the start of pointer buffer
			pTempDigit = szTempDigit;
			// Reset the digit counter to zero
			DigitCounter = 0;
		}
		else
		// Otherwise, any other char must be copied into the alpha array

		{
			// But before copy the char, check if we have the alpha counter
			// to zero and the digit counter greather to zero
			// If it is the case, that means we are changing from digit to alpha.
			if (DigitCounter > 0 && AlphaCounter == 0)
			{
				// Sets end of string for digit.
				*pTempDigit++ = 0x00;
				// Reset the digit counter to zero
				DigitCounter = 0;
				// And the start of pointer buffer
				pTempDigit = szTempDigit;
			}
			// Then copy the alpha char to the buffer and increment the counter
			*pTempAlpha++ = *pBuffer;
			++AlphaCounter;
		}
	}
	// Now we've running all the string.
	// We need to determine what is the last digit

	// It is an alpha
	if (AlphaCounter > 0 && DigitCounter == 0)
	{
		// Sets end of string for alpha.
		*pTempAlpha++ = 0x00;
		// Convert the previous saved value first.
		long lValue = atol( szTempDigit );
		// Check what prefix is concerned
		if (MonthPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			Month = (int)lValue;
		}
		else
		if (WeekPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			Week = (int)lValue;
		}
		else
		if (DayPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			lDays = lValue;
		}
		else
		if (HourPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			nHours = lValue;
		}
		else
		if (MonthShortPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			Month = (int)lValue;
		}
		else
		if (WeekShortPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			Week = (int)lValue;
		}
		else
		if (DayShortPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			lDays = lValue;
		}
		else
		if (HourShortPrefix.CompareNoCase( szTempAlpha ) == 0)
		{
			nHours = lValue;
		}
		else
		{
			// Unknown prefix, ignore
			lDays = 0;
		}
	}
	else
	if (DigitCounter > 0 && AlphaCounter == 0)
	{
		// Sets end of string for digit.
		*pTempDigit++ = 0x00;
		// Converts the string to number and assigns it to an int value
		int iValue = atoi( szTempDigit );
		// Now check to wich value it is destinated
		// If hour and minute done, then it is seconds
		if (HourDone && MinuteDone)
		{
			nSeconds = iValue;
		}
		else
		// If only hour done, then it is minutes
		if (HourDone)
		{
			nMinutes = iValue;
		}
		else
		// Otherwise, it is hours
		{
			nHours = iValue;
		}
	}
	else
	{
		// Problem
		return false;
	}

	// Sets the duration
	value.SetDuration( lDays, nHours, nMinutes, nSeconds );

	// Now check if months and weeks are to be added
	if (Month > 0)
		value.AddMonth( Month );
	if (Week > 0)
		value.AddWeek( Week );

	return true;
}



////////////////////////////////////////////////////////////
bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, int& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, short& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, float& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, long& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, double& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDate& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDuration& value, LPCTSTR pCurrency /*= NULL*/, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	ZBStringFormat::FormatType sf;
	return ZUStringFormatter::ConvertFormattedBuffer( buffer, value, sf, pCurrency, lcid );
}

////////////////////////////////////////////////////////////

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, int& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, unsigned int& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, short& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, float& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, long& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, double& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDate& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}

bool ZUStringFormatter::ConvertFormattedBuffer( const CString buffer, ZBDuration& value, ZBStringFormat& fmt )
{
	ZBStringFormat::FormatType ft = fmt.Getft();
	bool RetValue = ZUStringFormatter::ConvertFormattedBuffer( buffer, value, ft, (fmt.GetCurrency().IsEmpty()) ? NULL : (const char*)fmt.GetCurrency(), fmt.Getlcid() );
	fmt.Setft( ft );
	return RetValue;
}



// Convert custom string to value
bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, int& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, short& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, float& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, long& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, double& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, ZBDate& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, ZBTimeSpan& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}

bool ZUStringFormatter::ConvertCustomFormattedBuffer( const CString buffer, ZBDuration& value, LPCTSTR custom, LCID lcid /*= ::GetUserDefaultLCID()*/ )
{
	// Not implemented
	return false;
}


void ZUStringFormatter::ReplaceDecimalPoint( CString& Buffer, LCID lcid )
{
	// Nothing to do
	if (Buffer.IsEmpty())
		return;

	// Retreive decimal separator
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);
	// Nothing to replace
	if (DecimalSep == '.')
		return;

	// Detect the decimal point char
	int DecimalPointPosition = Buffer.Find( '.' );
	// If found, replace
	if (DecimalPointPosition != -1)
		Buffer.SetAt(DecimalPointPosition, DecimalSep);
}



CString ZUStringFormatter::RemoveTrailingZero( CString Buffer, LCID lcid, LPCTSTR pEndSymbol /*= NULL*/ )
{
	char  szBuffer[500];
	char* pFinal = szBuffer;

	// Retreive decimal separator
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);


	int EndSymbolPosition = -1;
	// Detect the currency symbol
	if (pEndSymbol && strlen(pEndSymbol) > 0 &&
		(EndSymbolPosition=Buffer.Find( pEndSymbol )) != -1)
	{
		// Now remove the currency symbol
		CString sNewValue = Buffer.Left( EndSymbolPosition );
		int SizeRight = Buffer.GetLength() - EndSymbolPosition - strlen( pEndSymbol );
		if (SizeRight > 0)
			sNewValue += Buffer.Right( SizeRight );
		// Now copy the new unformatted buffer to sValue
		Buffer = sNewValue;
	}

	int	Len = Buffer.GetLength();
	char* p = Buffer.GetBuffer( Len + 1 );
	int	Count=0;

	// Check if the number string is too long
	// Maximum is 500 for a number
	if (Len > 500)
	{
		return _T("#too long");
	}

	// Until the end of the string or
	// till we encounter the decimal point
	// Copy the string
	while (*p && (*p != DecimalSep))
	{
		*pFinal++ = *p++;
	}

	// If we are not at the end of the string
	if (*p && *p == DecimalSep)
	{
		*pFinal++ = *p++;
		// Keep the last non zero position
		// Initialize it on the decimal separator
		char* pLastZeroPosition = pFinal-1;

		while (*p)
		{
			if (*p != '0')
				pLastZeroPosition = pFinal+1;
			*pFinal++ = *p++;
		}

		// Put end of string
		*pLastZeroPosition = 0x00;
	}
	else
		*pFinal = 0x00;	// End of string


	// Don't forget to release the buffer
	Buffer.ReleaseBuffer(-1);

	// If end symbol was defined
	if (pEndSymbol && strlen(pEndSymbol))
		return CString(szBuffer) + pEndSymbol;
	// Return the formatted buffer
	return szBuffer;

}

CString ZUStringFormatter::ConvertBufferToAmountBuffer( CString Buffer, ZBStringFormat::FormatType sf, LPCTSTR pCurrency, LCID lcid )
{
	char  szBuffer[500];
	char* pFinal = szBuffer;

	int	Len = Buffer.GetLength();
	char* p = Buffer.GetBuffer( Len + 1 );
	int	Count=0;

	// Check if the number string is too long
	// Maximum is 500 for a number
	if (Len > 500)
	{
		return _T("#too long");
	}

	CString ThousandStr = ZAGlobal::GetThousandSeparator( lcid );
	char ThousandSep = (ThousandStr.IsEmpty()) ? '\'' : ThousandStr.GetAt(0);
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);

	// If negative sign, copy it and move forward
	if (*p == '-')
	{
		*pFinal++ = *p++;
		--Len;
	}

	// Until the end of the string or
	// when encounter the decimal point
	for (; *p && (*p != DecimalSep) ; ++Count)
	{
		// Add the char ' every 3 digits
		// calculate if we are on a third
		// digit by substracting the i from
		// the length
		if (Count > 0 && ( (Len-Count) % 3) == 0)
			*pFinal++ = ThousandSep;
		*pFinal++ = *p++;
	}
	// Copy char after the decimal point, till the end
	while (*p)
		*pFinal++ = *p++;

	// If a currency is defined, then copy the currency at the end of the string
	if (pCurrency && strlen(pCurrency) > 0)
	{
		// Add a space
		*pFinal++ = ' ';
		// Copy all char till the end
		while (*pCurrency)
			*pFinal++ = *pCurrency++;

	}
	*pFinal = 0x00;	// End of string

	// Don't forget to release the buffer
	Buffer.ReleaseBuffer(-1);
	// Return the formatted buffer
	return szBuffer;
}






bool ZUStringFormatter::ConvertBufferToNumber( CString sValue, double& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency, LCID lcid )
{

	if (sValue.IsEmpty())
	{
		value = 0;
		return true;
	}
	// Retreive the separators
	CString ThousandStr = ZAGlobal::GetThousandSeparator( lcid );
	char ThousandSep = (ThousandStr.IsEmpty()) ? '\'' : ThousandStr.GetAt(0);
	CString DecimalStr = ZAGlobal::GetDecimalSeparator( lcid );
	char DecimalSep = (DecimalStr.IsEmpty()) ? '.' : DecimalStr.GetAt(0);


	// Convert the string to a double
	// assign the result to value

	// Test if the char % is present
	// If it is the case remove it and
	// divide the number by 100
	// If the char % is present the char '
	// can't be present at the same time
	int	PercPosition;
	if ((PercPosition=sValue.Find( '%' )) != -1)
	{
		// Test if at the same time we have the thousand separator char
		if (sValue.Find( ThousandSep ) != -1)
		{
			// Don't assign the value and return false
			return false;
		}
		// Replace the percentage sign by a space
		sValue.SetAt( PercPosition, ' ' );
		// Calculates and assigns the value
		value = atof( (const char*)sValue ) / (double)100;
		// Sets the right format
		sf = ZBStringFormat::Percentage;
		return true;
	}
	
	int CurrencyPosition = -1;
	// Detect the currency symbol
	if (pCurrency && strlen(pCurrency) > 0 &&
		(CurrencyPosition=sValue.Find( pCurrency )) != -1)
	{
		// Now remove the currency symbol
		CString sNewValue = sValue.Left( CurrencyPosition );
		int SizeRight = sValue.GetLength() - CurrencyPosition - strlen( pCurrency );
		if (SizeRight > 0)
			sNewValue += sValue.Right( SizeRight );
		// And set the currency format
		sf = ZBStringFormat::Currency;
		// Now copy the new unformatted buffer to sValue
		sValue = sNewValue;
		// Continue the test to check if amount
	}

	// Test if we have the thousand separator char
	int DecimalPosition = sValue.Find( DecimalSep );

	int ThousandPosition;
	// Test if we have the thousand separator char
	if ((ThousandPosition=sValue.Find( ThousandSep )) != -1)
	{
		// Remove the thousand separator char
		const char*	pBuffer = (const char*)sValue;
		char szTemp[500];
		char* pTemp = szTemp;

		for (int i = 0; *pBuffer ; ++pBuffer)
		{
			if (*pBuffer != ThousandSep)
				*pTemp++ = *pBuffer;
		}
		// Sets end of string
		*pTemp = 0x00;
		// Now copy the new unformatted buffer to sValue
		sValue = szTemp;
	}

	// Convert the value
	value = atof( (const char*)sValue );
	// If thousand found, sets the amount format
	// But, if currency found, don't change the currency format
	if (ThousandPosition != -1 && 
		CurrencyPosition == -1)
	{
		sf = ZBStringFormat::Accounting;
	}


	// ok
	return true;
}