/****************************************************************************
 * ==> PSS_Date ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a date                                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DateH
#define PSS_DateH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#ifndef _WIN32
    #include <afx.h>
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
* Date
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    class AFX_EXT_CLASS PSS_Date : public COleDateTime
    {
        public:
            typedef COleDateTime inherited;
#else
    class AFX_EXT_CLASS PSS_Date : public CTime
    {
        public:
            typedef CTime inherited;
#endif
        PSS_Date();

        /**
        * Constructor
        *@param time - time
        */
        inline PSS_Date(time_t time);

        /**
        * Constructor
        *@param year - year
        *@param month - month
        *@param day - day
        *@param hour - hour
        *@param min - minutes
        *@param sec - seconds
        *@param dst - daylight saving time, ignored if -1
        */
        inline PSS_Date(int year, int month, int day, int hour, int min, int sec, int dst = -1);

        /**
        * Constructor
        *@param dosDate - dos date
        *@param dosTime - dos time
        *@param dst - daylight saving time, ignored if -1
        */
        inline PSS_Date(WORD dosDate, WORD dosTime, int dst = -1);

        /**
        * Constructor
        *@param sysTime - system time
        *@param dst - daylight saving time, ignored if -1
        */
        inline PSS_Date(const ::SYSTEMTIME& sysTime, int dst = -1);

        /**
        * Constructor
        *@param fileTime - file time
        *@param dst - daylight saving time, ignored if -1
        */
        inline PSS_Date(const ::FILETIME& fileTime, int dst = -1);

        /**
        * Constructor
        *@param pDate - date
        *@param flags - flags
        *@param lcid - language identifier
        */
        PSS_Date(LPCTSTR pDate, DWORD flags = 0, LCID lcid = LANG_USER_DEFAULT);

        /**
        * Constructor
        *@param date - date
        */
        #ifdef _WIN32
            PSS_Date(DATE dt);
        #endif

        /**
        * Constructor
        *@param time - time
        */
        #ifdef _WIN32
            inline PSS_Date(const CTime& time);
        #endif

        /**
        * Constructor
        *@param time - time
        */
        #ifdef _WIN32
            inline PSS_Date(const COleDateTime& time);
        #endif

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Date(const PSS_Date& other);
        
        virtual ~PSS_Date();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        #ifdef _WIN32
            const PSS_Date& operator = (const COleDateTime& other);
        #endif

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Date& operator = (const CTime& other);

        /**
        * Stores from the archive to the date
        *@param ar - archive
        *@param time - date and time
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        #ifdef _WIN32
            friend CArchive& AFXAPI operator << (CArchive& ar, COleDateTime time);
        #else
            friend CArchive& AFXAPI operator << (CArchive& ar, CTime time);
        #endif

        /**
        * Stores the date to the archive
        *@param ar - archive
        *@param time - date and time
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        #ifdef _WIN32
            friend CArchive& AFXAPI operator >> (CArchive& ar, COleDateTime& time);
        #else
            friend CArchive& AFXAPI operator >> (CArchive& ar, CTime& time);
        #endif

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_Date* Clone() const;
            
        /**
        * Clears the date
        */
        virtual void Clear();

        /**
        * Checks if date is empty
        *@return TRUE if the date is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the today date
        *@return the today date
        */
        static inline PSS_Date GetToday();

        /**
        * Sets the today date
        */
        virtual inline void SetToday();

        /**
        * Gets the standard formatted date
        *@return the standard formatted date
        */
        virtual CString GetStandardFormattedDate() const;

        /**
        * Gets the standard formatted time
        *@return the standard formatted time
        */
        virtual CString GetStandardFormattedDateTime() const;

        /**
        * Gets the formatted date
        *@param format - date format
        *@return the formatted date
        */
        virtual CString GetFormattedDate(const CString& format) const;

        /**
        * Gets the formatted date
        *@param formatID - date format identifier
        *@return the formatted date
        */
        virtual CString GetFormattedDate(UINT formatID) const;

        /**
        * Clears the time
        */
        virtual void ClearTime();
};

//---------------------------------------------------------------------------
// PSS_Date
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(time_t time) :
    #ifndef _WIN32
        // 16 bit version
        CTime(time)
    #else
        // 32 bit version
        COleDateTime(time)
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(int year, int month, int day, int hour, int min, int sec, int dst) :
    #ifndef _WIN32
        // 16 bit version
        CTime(year, month, day, hour, min, sec, dst)
    #else
        // 32 bit version
        COleDateTime(year, month, day, hour, min, sec)
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(WORD dosDate, WORD dosTime, int dst) :
    #ifndef _WIN32
        // 16 bit version
        CTime(dosDate, dosTime, dst)
    #else
        // 32 bit version
        COleDateTime(dosDate, dosTime)
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(const ::SYSTEMTIME& sysTime, int dst) :
    #ifndef _WIN32
        // 16 bit version
        CTime(sysTime, dst)
    #else
        // 32 bit version
        COleDateTime(sysTime)
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(const ::FILETIME& fileTime, int dst) :
    #ifndef _WIN32
        // 16 bit version
        CTime(fileTime, dst)
    #else
        // 32 bit version
        COleDateTime(fileTime)
    #endif
{}
//---------------------------------------------------------------------------
PSS_Date::PSS_Date(const PSS_Date& other) :
    #ifndef _WIN32
        // 16 bit version
        CTime(other)
    #else
        // 32 bit version
        COleDateTime(other)
    #endif
{}
//---------------------------------------------------------------------------
#ifdef _WIN32
    PSS_Date::PSS_Date(const CTime& other) :
        COleDateTime(other.GetYear(),
                     other.GetMonth(),
                     other.GetDay(),
                     other.GetHour(),
                     other.GetMinute(),
                     other.GetSecond())
    {}
#endif
//---------------------------------------------------------------------------
#ifdef _WIN32
    PSS_Date::PSS_Date(const COleDateTime& other) :
        COleDateTime(other)
    {}
#endif
//---------------------------------------------------------------------------
PSS_Date PSS_Date::GetToday()
{
    #ifdef _WIN32
        return  COleDateTime::GetCurrentTime();
    #else
        return  CTime::GetCurrentTime();
    #endif
}
//---------------------------------------------------------------------------
void PSS_Date::SetToday()
{
    #ifdef _WIN32
        *this = COleDateTime::GetCurrentTime();
    #else
        *this = CTime::GetCurrentTime();
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_Date::IsEmpty() const
{
    #ifdef _WIN32
        return (m_dt <= 0);
    #else
        return (GetTime() <= 0);
    #endif
}
//---------------------------------------------------------------------------

#endif
