// ZUStringFormater.h: interface for the ZUStringFormatter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUStringFormater_H__0F9D664A_F3FB_4639_8738_B4525329F5F6__INCLUDED_)
#define AFX_ZUStringFormater_H__0F9D664A_F3FB_4639_8738_B4525329F5F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBStringFormat.h"
#include "ZBDate.h"
#include "ZBTimeSpan.h"
#include "ZBDuration.h"


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZUStringFormatter  
{

public:
	ZUStringFormatter();
	virtual ~ZUStringFormatter();

	// Convert value to string 
	static CString	GetFormattedBuffer( int value, ZBStringFormat::FormatType sf = ZBStringFormat::General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( unsigned int value, ZBStringFormat::FormatType sf = ZBStringFormat::General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( short value, ZBStringFormat::FormatType sf = ZBStringFormat::General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( float value, ZBStringFormat::FormatType sf = ZBStringFormat::General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( long value, ZBStringFormat::FormatType sf = ZBStringFormat::General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( double value, ZBStringFormat::FormatType sf = ZBStringFormat::General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( ZBDate& value, ZBStringFormat::FormatType sf = ZBStringFormat::Date, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( ZBTimeSpan& value, ZBStringFormat::FormatType sf = ZBStringFormat::Time, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetFormattedBuffer( ZBDuration& value, ZBStringFormat::FormatType sf = ZBStringFormat::Duration, LCID lcid = ::GetUserDefaultLCID() );

	static CString	GetFormattedBuffer( int value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( unsigned int value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( short value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( float value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( long value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( double value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( ZBDate& value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( ZBTimeSpan& value, ZBStringFormat& fmt );
	static CString	GetFormattedBuffer( ZBDuration& value, ZBStringFormat& fmt );

	// Convert value to custom string 
	static CString	GetCustomFormattedBuffer( int value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( unsigned int value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( short value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( float value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( long value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( double value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( ZBDate& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( ZBTimeSpan& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static CString	GetCustomFormattedBuffer( ZBDuration& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );

	// Convert string to value
	static bool ConvertFormattedBuffer( const CString buffer, int& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, unsigned int& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, short& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, float& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, long& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, double& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDate& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDuration& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );

	static bool ConvertFormattedBuffer( const CString buffer, int& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, short& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, float& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, long& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, double& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDate& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDuration& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );

	static bool ConvertFormattedBuffer( const CString buffer, int& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, unsigned int& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, short& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, float& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, long& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, double& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDate& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBTimeSpan& value, ZBStringFormat& fmt );
	static bool	ConvertFormattedBuffer( const CString buffer, ZBDuration& value, ZBStringFormat& fmt );


	// Convert custom string to value
	static bool	ConvertCustomFormattedBuffer( const CString buffer, int& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, short& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, float& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, long& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, double& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, ZBDate& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, ZBTimeSpan& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
	static bool	ConvertCustomFormattedBuffer( const CString buffer, ZBDuration& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );


private:
	static void ReplaceDecimalPoint( CString& Buffer, LCID lcid );
	static CString RemoveTrailingZero( CString Buffer, LCID lcid, LPCTSTR pEndSymbol = NULL );
	static CString ConvertBufferToAmountBuffer( CString Buffer, ZBStringFormat::FormatType sf, LPCTSTR pCurrency, LCID lcid );
	static bool ConvertBufferToNumber( CString sValue, double& value, ZBStringFormat::FormatType& sf, LPCTSTR pCurrency, LCID lcid );
};

#endif // !defined(AFX_ZUStringFormater_H__0F9D664A_F3FB_4639_8738_B4525329F5F6__INCLUDED_)
