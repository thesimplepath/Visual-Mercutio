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

// processsoft
#include "PSS_StringFormat.h"
#include "PSS_Date.h"
#include "PSS_TimeSpan.h"
#include "PSS_Duration.h"

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
    static CString    GetFormattedBuffer( int value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( unsigned int value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( short value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( float value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( long value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( double value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, size_t DecimalPlace = 0, bool UseSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer( PSS_Date& value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Date, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer(PSS_TimeSpan& value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Time, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetFormattedBuffer(PSS_Duration& value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Duration, LCID lcid = ::GetUserDefaultLCID() );

    static CString    GetFormattedBuffer( int value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer( unsigned int value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer( short value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer( float value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer( long value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer( double value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer(PSS_Date& value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer(PSS_TimeSpan& value, PSS_StringFormat& fmt );
    static CString    GetFormattedBuffer(PSS_Duration& value, PSS_StringFormat& fmt );

    // Convert value to custom string 
    static CString    GetCustomFormattedBuffer( int value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer( unsigned int value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer( short value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer( float value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer( long value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer( double value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer(PSS_Date& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer(PSS_TimeSpan& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static CString    GetCustomFormattedBuffer(PSS_Duration& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );

    // Convert string to value
    static bool ConvertFormattedBuffer( const CString buffer, int& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, unsigned int& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, short& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, float& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, long& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, double& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Date& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_TimeSpan& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Duration& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );

    static bool ConvertFormattedBuffer( const CString buffer, int& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, short& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, float& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, long& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, double& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Date& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_TimeSpan& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Duration& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID() );

    static bool ConvertFormattedBuffer( const CString buffer, int& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, unsigned int& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, short& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, float& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, long& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, double& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Date& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_TimeSpan& value, PSS_StringFormat& fmt );
    static bool    ConvertFormattedBuffer( const CString buffer, PSS_Duration& value, PSS_StringFormat& fmt );


    // Convert custom string to value
    static bool    ConvertCustomFormattedBuffer( const CString buffer, int& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, unsigned int& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, short& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, float& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, long& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, double& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, PSS_Date& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, PSS_TimeSpan& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );
    static bool    ConvertCustomFormattedBuffer( const CString buffer, PSS_Duration& value, LPCTSTR custom, LCID lcid = ::GetUserDefaultLCID() );


private:
    static void ReplaceDecimalPoint( CString& Buffer, LCID lcid );
    static CString RemoveTrailingZero( CString Buffer, LCID lcid, LPCTSTR pEndSymbol = NULL );
    static CString ConvertBufferToAmountBuffer( CString Buffer, PSS_StringFormat::IEFormatType sf, LPCTSTR pCurrency, LCID lcid );
    static bool ConvertBufferToNumber( CString sValue, double& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency, LCID lcid );
};

#endif // !defined(AFX_ZUStringFormater_H__0F9D664A_F3FB_4639_8738_B4525329F5F6__INCLUDED_)
