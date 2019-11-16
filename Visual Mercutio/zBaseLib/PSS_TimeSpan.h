/****************************************************************************
 * ==> PSS_TimeSpan --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a time span                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TimeSpanH
#define PSS_TimeSpanH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Time span
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TimeSpan : public COleDateTimeSpan
{
    public:
        typedef COleDateTimeSpan inherited;

        PSS_TimeSpan();

        /**
        * Constructor
        *@param time - time
        */
        inline PSS_TimeSpan(double time);

        /**
        * Constructor
        *@param days - days
        *@param hours - hours
        *@param mins - minutes
        *@param secs - seconds
        */
        inline PSS_TimeSpan(long days, int hours, int mins, int secs);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_TimeSpan(const PSS_TimeSpan& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_TimeSpan(const CTimeSpan& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_TimeSpan(const COleDateTimeSpan& other);

        virtual ~PSS_TimeSpan();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TimeSpan& operator = (const PSS_TimeSpan& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TimeSpan& operator = (const CTimeSpan& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TimeSpan& operator = (const COleDateTimeSpan& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_TimeSpan* Clone() const;

        /**
        * Checks if time span is empty
        *@return TRUE if time span is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Clears the time span
        */
        virtual void Clear();

        /**
        * Gets the standard formatted time span
        *@return the standard formatted time span
        */
        virtual CString GetStandardFormattedTimeSpan() const;

        /**
        * Gets the formatted time span
        *@param format - format
        *@return the formatted time span
        */
        virtual CString GetFormattedTimeSpan(const CString& format) const;

        /**
        * Gets the formatted time span
        *@param formatID - format resource identifier
        *@return the formatted time span
        */
        virtual CString GetFormattedTimeSpan(UINT formatID) const;
};

//---------------------------------------------------------------------------
// PSS_TimeSpan
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan(double time) :
    COleDateTimeSpan(time)
{}
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan(long days, int hours, int mins, int secs) :
    COleDateTimeSpan(days, hours, mins, secs)
{}
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan(const PSS_TimeSpan& other) :
    COleDateTimeSpan(other)
{}
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan(const CTimeSpan& other) :
    COleDateTimeSpan(long(other.GetDays()), other.GetHours(), other.GetMinutes(), other.GetSeconds())
{}
//---------------------------------------------------------------------------
PSS_TimeSpan::PSS_TimeSpan(const COleDateTimeSpan& other)
    : COleDateTimeSpan(other)
{}
//---------------------------------------------------------------------------
BOOL PSS_TimeSpan::IsEmpty() const
{
    return !m_span;
}
//---------------------------------------------------------------------------

#endif
