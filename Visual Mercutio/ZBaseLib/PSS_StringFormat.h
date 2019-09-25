/****************************************************************************
 * ==> PSS_StringFormat ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a string format                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StringFormatH
#define PSS_StringFormatH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_StringFormat
    #define PSS_StringFormat ZBStringFormat
#endif

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
* String format
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StringFormat : public CObject
{
    DECLARE_SERIAL(PSS_StringFormat)

    public:
        /**
        * Format type
        */
        enum IEFormatType
        {
            IE_FT_General,
            IE_FT_Number,
            IE_FT_Currency,
            IE_FT_Accounting,  // with thousand separator
            IE_FT_Accounting1, // with thousand separator and automatic decimal
            IE_FT_DateTime,    // dd/mm/yy hour:min
            IE_FT_DateTime1,   // dd/mm/yy hour:min:sec
            IE_FT_DateTime2,   // dd/mth/yy hour:min
            IE_FT_DateTime3,   // dd/mth/yy hour:min:sec
            IE_FT_DateTime4,   // dd-mth-yy hour::min
            IE_FT_DateTime5,   // dd-mth-yy hour::min::sec
            IE_FT_Date,        // dd/mm/yy
            IE_FT_Date1,       // dd/mth/yy
            IE_FT_Date2,       // mth-yy
            IE_FT_Date3,       // month-yy
            IE_FT_Date4,       // month dd, yy
            IE_FT_Time,        // hour:min
            IE_FT_Time1,       // hour:min:sec
            IE_FT_Time2,       // days-hour:min
            IE_FT_Time3,       // days-hour:min:sec
            IE_FT_Duration,    // dys-hour:min
            IE_FT_Duration1,   // dys-hour:min:sec
            IE_FT_Duration2,   // nnd hour:min:sec
            IE_FT_Duration3,   // nnd hour:min
            IE_FT_Duration4,   // nn days hour:min
            IE_FT_Duration5,   // nn days hour:min:sec
            IE_FT_Duration6,   // nnd ##:##:##
            IE_FT_Duration7,   // nn days ##:##:##
            IE_FT_Percentage,
            IE_FT_Scientific,
            IE_FT_Custom
        };

        typedef CObject inherited;

        /**
        * Constructor
        *@param formatType - format type
        *@param useSeparator - if true, separators will be used
        *@param decimalPlace - decimal place
        *@param currency - currency
        *@param lcid - language identifier
        */
        PSS_StringFormat(IEFormatType   formatType   =  IE_FT_General,
                         bool           useSeparator =  false,
                         int            decimalPlace = -1,
                         const CString& currency     = _T(""),
                         LCID           lcid         =  0);

        /**
        * Constructor
        *@param customFormat - custom format
        *@param lcid - language identifier
        */
        PSS_StringFormat(const CString& customFormat, LCID lcid = 0);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StringFormat(const PSS_StringFormat& other);

        virtual ~PSS_StringFormat();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_StringFormat& operator = (const PSS_StringFormat& other);

        /**
        * Releases the string format
        */
        virtual void Release();

        /**
        * Sets a new language
        *@param primaryLanguage - primary language
        *@param subLanguage - sub-language
        *@param sortID - sort identifier
        */
        virtual inline void SetLanguage(USHORT primaryLanguage, USHORT subLanguage, WORD sortID = SORT_DEFAULT);

        /**
        * Gets the format type
        *@return the format type
        */
        virtual inline IEFormatType GetFormatType() const;

        /**
        * Sets the format type
        *@param value - the format type
        */
        virtual inline void SetFormatType(IEFormatType value);

        /**
        * Gets if the separator is used
        *@return true if the separator is used, otherwise false
        */
        virtual inline bool GetUseSeparator() const;

        /**
        * Sets if the separator is used
        *@param value - if true, the separator is used
        */
        virtual inline void SetUseSeparator(bool value);

        /**
        * Gets the decimal place
        *@return the decimal place
        */
        virtual inline int GetDecimalPlace() const;

        /**
        * Sets the decimal place
        *@param value - the decimal place
        */
        virtual inline void SetDecimalPlace(int value);

        /**
        * Gets the currency
        *@return the currency
        */
        virtual inline CString GetCurrency() const;

        /**
        * Sets the currency
        *@param value - the currency
        */
        virtual inline void SetCurrency(const CString& value);

        /**
        * Gets the custom format
        *@return the custom format
        */
        virtual inline CString GetCustomFormat() const;

        /**
        * Sets the custom format
        *@param value - the custom format
        */
        virtual inline void SetCustomFormat(const CString& value);

        /**
        * Gets the language identifier
        *@return the language identifier
        */
        virtual inline LCID GetLCID() const;

        /**
        * Sets the language identifier
        *@param value - the language identifier
        */
        virtual inline void SetLCID(LCID value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        IEFormatType m_FormatType;
        CString      m_Currency;
        CString      m_CustomFormat;
        LCID         m_LCID;
        int          m_DecimalPlace;
        bool         m_UseSeparator;
};

//---------------------------------------------------------------------------
// PSS_StringFormat
//---------------------------------------------------------------------------
void PSS_StringFormat::SetLanguage(USHORT primaryLanguage, USHORT subLanguage, WORD sortID)
{
    const WORD li = MAKELANGID(primaryLanguage, subLanguage);
    m_LCID        = MAKELCID  (li,              sortID);
}
//---------------------------------------------------------------------------
PSS_StringFormat::IEFormatType PSS_StringFormat::GetFormatType() const
{
    return m_FormatType;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetFormatType(PSS_StringFormat::IEFormatType value)
{
    m_FormatType = value;
}
//---------------------------------------------------------------------------
bool PSS_StringFormat::GetUseSeparator() const
{
    return m_UseSeparator;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetUseSeparator(bool value)
{
    m_UseSeparator = value;
}
//---------------------------------------------------------------------------
int PSS_StringFormat::GetDecimalPlace() const
{
    return m_DecimalPlace;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetDecimalPlace(int value)
{
    m_DecimalPlace = value;
}
//---------------------------------------------------------------------------
CString PSS_StringFormat::GetCurrency() const
{
    return m_Currency;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetCurrency(const CString& value)
{
    m_Currency = value;
}
//---------------------------------------------------------------------------
CString PSS_StringFormat::GetCustomFormat() const
{
    return m_CustomFormat;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetCustomFormat(const CString& value)
{
    m_CustomFormat = value;
}
//---------------------------------------------------------------------------
LCID PSS_StringFormat::GetLCID() const
{
    return m_LCID;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::SetLCID(LCID value)
{
    m_LCID = value;
}
//---------------------------------------------------------------------------

#endif
