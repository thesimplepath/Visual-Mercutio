/****************************************************************************
 * ==> PSS_StringFormatter -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a string formatter                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StringFormatterH
#define PSS_StringFormatterH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* String formatter
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StringFormatter
{
    public:
        PSS_StringFormatter();
        virtual ~PSS_StringFormatter();

        /**
        * Gets the formatted buffer
        *@param value - value
        *@param sf - string format
        *@param useSeparator - if true, separator will be used
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return the formatted buffer, empty string on error
        */
        static CString GetFormattedBuffer(int          value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(unsigned int value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(short        value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Gets the formatted buffer
        *@param value - value
        *@param sf - string format
        *@param decimalPlace - decimal place
        *@param useSeparator - if true, separator will be used
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return the formatted buffer, empty string on error
        */
        static CString GetFormattedBuffer(float  value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General,  std::size_t decimalPlace = 0, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(long   value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General,  std::size_t decimalPlace = 0, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(double value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_General,  std::size_t decimalPlace = 0, bool useSeparator = false, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Gets the formatted buffer
        *@param value - value
        *@param sf - string format
        *@param lcid - language identifier
        *@return the formatted buffer, empty string on error
        */
        static CString GetFormattedBuffer(PSS_Date&     value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Date,     LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(PSS_TimeSpan& value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Time,     LCID lcid = ::GetUserDefaultLCID());
        static CString GetFormattedBuffer(PSS_Duration& value, PSS_StringFormat::IEFormatType sf = PSS_StringFormat::IE_FT_Duration, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Gets the formatted buffer
        *@param value - value
        *@param fmt - string format
        *@param lcid - language identifier
        *@return the formatted buffer, empty string on error
        */
        static CString GetFormattedBuffer(int           value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(unsigned int  value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(short         value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(float         value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(long          value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(double        value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(PSS_Date&     value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(PSS_TimeSpan& value, const PSS_StringFormat& fmt);
        static CString GetFormattedBuffer(PSS_Duration& value, const PSS_StringFormat& fmt);

        /**
        * Gets the custom formatted buffer
        *@param value - value
        *@param pCustom - custom string format
        *@param lcid - language identifier
        *@return the custom formatted buffer, empty string on error
        */
        static CString GetCustomFormattedBuffer(int           value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(unsigned int  value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(short         value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(float         value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(long          value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(double        value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(PSS_Date&     value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(PSS_TimeSpan& value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static CString GetCustomFormattedBuffer(PSS_Duration& value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Convert formatted buffer to value
        *@param buffer - formatted buffer to convert
        *@param[out] value - converted value on function ends, if succeeded
        *@param sf - string format
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return true on success, otherwise false
        */
        static bool ConvertFormattedBuffer(const CString& buffer, int&          value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, unsigned int& value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, short&        value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, float&        value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, long&         value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, double&       value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Date&     value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Duration& value, const PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Convert formatted buffer to value
        *@param buffer - formatted buffer to convert
        *@param[out] value - converted value on function ends, if succeeded
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return true on success, otherwise false
        */
        static bool ConvertFormattedBuffer(const CString& buffer, int&          value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, unsigned int& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, short&        value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, float&        value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, long&         value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, double&       value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Date&     value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Duration& value, LPCTSTR pCurrency = NULL, LCID lcid = ::GetUserDefaultLCID());

        /**
        * Convert formatted buffer to value
        *@param buffer - formatted buffer to convert
        *@param[out] value - converted value on function ends, if succeeded
        *@param fmt - string format
        *@return true on success, otherwise false
        */
        static bool ConvertFormattedBuffer(const CString& buffer, int&          value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, unsigned int& value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, short&        value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, float&        value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, long&         value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, double&       value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Date&     value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, const PSS_StringFormat& fmt);
        static bool ConvertFormattedBuffer(const CString& buffer, PSS_Duration& value, const PSS_StringFormat& fmt);

        /**
        * Convert custom formatted buffer to value
        *@param buffer - formatted buffer to convert
        *@param[out] value - converted value on function ends, if succeeded
        *@param pCustom - custom string format
        *@param lcid - language identifier
        *@return true on success, otherwise false
        */
        static bool ConvertCustomFormattedBuffer(const CString& buffer, int&          value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, unsigned int& value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, short&        value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, float&        value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, long&         value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, double&       value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, PSS_Date&     value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, PSS_TimeSpan& value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());
        static bool ConvertCustomFormattedBuffer(const CString& buffer, PSS_Duration& value, LPCTSTR pCustom, LCID lcid = ::GetUserDefaultLCID());

    private:
        /**
        * Replaces the decimal point regarding to the current locale
        *@param[in, out] buffer - buffer in which the decimal point should be replaced, modified buffer on function ends
        *@param lcid - language identifier
        */
        static void ReplaceDecimalPoint(CString& buffer, LCID lcid);

        /**
        * Removes the trailing zero
        *@param buffer - buffer in which the trailing zero should be removed
        *@param lcid - language identifier
        *@param pEndSymbol - end symbol
        *@return the trimmed string
        */
        static CString RemoveTrailingZero(const CString& buffer, LCID lcid, LPCTSTR pEndSymbol = NULL);

        /**
        * Converts a buffer to an amount buffer
        *@param buffer - buffer to convert
        *@param sf - string format
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return the converted buffer
        */
        static CString ConvertBufferToAmountBuffer(const CString&                 buffer,
                                                   PSS_StringFormat::IEFormatType sf,
                                                   LPCTSTR                        pCurrency,
                                                   LCID                           lcid);

        /**
        * Converts a buffer to a number
        *@param buffer - buffer to convert
        *@param[out] value - converted value on function ends, if succeeded
        *@param sf - string format
        *@param pCurrency - currency
        *@param lcid - language identifier
        *@return true on success, otherwise false
        */
        static bool ConvertBufferToNumber(const CString& buffer, double& value, PSS_StringFormat::IEFormatType& sf, LPCTSTR pCurrency, LCID lcid);
};

#endif
