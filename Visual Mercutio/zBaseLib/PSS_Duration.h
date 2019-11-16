/****************************************************************************
 * ==> PSS_Duration --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a duration and time conversion class              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DurationH
#define PSS_DurationH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Max_Days_In_SpanDuration 3615897L
//---------------------------------------------------------------------------

/**
* Duration and time conversion
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Duration
{
    public:
        /**
        * Duration status
        */
        enum IEStatus
        {
            IE_S_Valid   = 0,
            IE_S_Invalid = 1, // invalid date (out of range, etc...)
            IE_S_Null    = 2, // no value
        };

        /**
        * constructor
        *@param hourPerDay - number of hours per days
        *@param dayPerWeek - number of days per weeks
        *@param dayPerMonth - number of days per months
        *@param dayPerYear - number of days per years
        */
        inline PSS_Duration(int hourPerDay  = 8,
                            int dayPerWeek  = 5,
                            int dayPerMonth = 22,
                            int dayPerYear  = 220);

        /**
        * constructor
        *@param value - duration
        *@param hourPerDay - number of hours per days
        *@param dayPerWeek - number of days per weeks
        *@param dayPerMonth - number of days per months
        *@param dayPerYear - number of days per years
        */
        inline PSS_Duration(double value,
                            int    hourPerDay  = 8,
                            int    dayPerWeek  = 5,
                            int    dayPerMonth = 22,
                            int    dayPerYear  = 220);

        /**
        * constructor
        *@param days - days
        *@param hours - hours
        *@param mins - minutes
        *@param secs - seconds
        *@param hourPerDay - number of hours per days
        *@param dayPerWeek - number of days per weeks
        *@param dayPerMonth - number of days per months
        *@param dayPerYear - number of days per years
        */
        inline PSS_Duration(long days,
                            int  hours,
                            int  mins,
                            int  secs        = 0,
                            int  hourPerDay  = 8,
                            int  dayPerWeek  = 5,
                            int  dayPerMonth = 22,
                            int  dayPerYear  = 220);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_Duration(const PSS_Duration& other);

        virtual inline ~PSS_Duration();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Duration& operator = (const PSS_Duration& other);

        /**
        * Assignment operator
        *@param value - duration
        *@return copy of itself
        */
        const PSS_Duration& operator = (double value);

        /**
        * Equality operator
        *@param other - other object to compare with
        *@return TRUE if objects content are equals, otherwise FALSE
        */
        inline BOOL operator == (const PSS_Duration& other) const;

        /**
        * Inequality operator
        *@param other - other object to compare with
        *@return TRUE if objects content differ, otherwise FALSE
        */
        inline BOOL operator != (const PSS_Duration& other) const;

        /**
        * Less than operator
        *@param other - other object to compare with
        *@return TRUE if object content value is less than other, otherwise FALSE
        */
        inline BOOL operator < (const PSS_Duration& other) const;

        /**
        * Higher than operator
        *@param other - other object to compare with
        *@return TRUE if object content value is higher than other, otherwise FALSE
        */
        inline BOOL operator > (const PSS_Duration& other) const;

        /**
        * Less than or equal operator
        *@param other - other object to compare with
        *@return TRUE if object content value is less than or equal to other, otherwise FALSE
        */
        inline BOOL operator <= (const PSS_Duration& other) const;

        /**
        * Higher than or equal operator
        *@param other - other object to compare with
        *@return TRUE if object content value is higher than or equal to other, otherwise FALSE
        */
        inline BOOL operator >= (const PSS_Duration& other) const;

        /**
        * Addition operator
        *@param other - other object to add
        *@return added object
        */
        PSS_Duration operator + (const PSS_Duration& other) const;

        /**
        * Subtraction operator
        *@param other - other object to subtract
        *@return subtracted object
        */
        PSS_Duration operator - (const PSS_Duration& other) const;

        /**
        * Addition and assignment operator
        *@param other - other object to add
        *@return copy of itself
        */
        inline const PSS_Duration& operator += (const PSS_Duration& other);

        /**
        * Subtraction and assignment operator
        *@param other - other object to subtract
        *@return copy of itself
        */
        inline const PSS_Duration& operator -= (const PSS_Duration& other);

        /**
        * Negation operator
        *@return negated object
        */
        inline PSS_Duration operator - () const;

        /**
        * Conversion to double operator
        */
        inline operator double() const;

        /**
        * Gets the status
        *@return the status
        */
        virtual inline IEStatus GetStatus() const;

        /**
        * Sets the status
        *@param status - the status
        */
        virtual inline void SetStatus(IEStatus status);

        /**
        * Gets the time span
        *@return the time span
        */
        virtual inline double GetSpan() const;

        /**
        * Sets the time span
        *@param value - the time span
        */
        virtual inline void SetSpan(double value);

        /**
        * Gets the number of hours per day
        *@return the number of hours per day
        */
        virtual inline int GetHourPerDay() const;

        /**
        * Sets the number of hours per day
        *@param status - the number of hours per day
        */
        virtual inline void SetHourPerDay(int value);

        /**
        * Gets the number of days per week
        *@return the number of days per week
        */
        virtual inline int GetDayPerWeek() const;
 
        /**
        * Sets the number of days per week
        *@param status - the number of days per week
        */
        virtual inline void SetDayPerWeek(int value);

        /**
        * Gets the number of days per month
        *@return the number of days per month
        */
        virtual inline int GetDayPerMonth() const;

        /**
        * Sets the number of days per month
        *@param value - the number of days per month
        */
        virtual inline void SetDayPerMonth(int value);

        /**
        * Gets the number of days per year
        *@return the number of days per year
        */
        virtual inline int GetDayPerYear() const;

        /**
        * Sets the number of days per year
        *@param value - the number of days per year
        */
        virtual inline void SetDayPerYear(int value);

        /**
        * Gets the span in days
        *@return the span in days (about -3.65e6 to 3.65e6)
        */
        virtual inline double GetTotalDays() const;

        /**
        * Gets the span in hours
        *@return the span in hours (about -8.77e7 to 8.77e6)
        */
        virtual inline double GetTotalHours() const;

        /**
        * Gets the span in minutes
        *@return the span in minutes (about -5.26e9 to 5.26e9)
        */
        virtual inline double GetTotalMinutes() const;

        /**
        * Gets the span in seconds
        *@return the span in seconds (about -3.16e11 to 3.16e11)
        */
        virtual inline double GetTotalSeconds() const;

        /**
        * Gets the span days
        *@return the span days
        */
        virtual inline long GetDays() const;

        /**
        * Gets the span hours
        *@return the span hours (-23 to 23)
        */
        virtual long GetHours() const;

        /**
        * Gets the span minutes
        *@return the span minutes (-59 to 59)
        */
        virtual long GetMinutes() const;

        /**
        * Gets the span seconds
        *@return the span seconds (-59 to 59)
        */
        virtual long GetSeconds() const;

        /**
        * Converts the number of week in number of days
        *@param value - number of weeks to convert
        *@return converted number of days
        */
        virtual inline double ConvertWeekToDays(int value) const;

        /**
        * Converts the number of months in number of days
        *@param value - number of months to convert
        *@return converted number of days
        */
        virtual inline double ConvertMonthToDays(int value) const;

        /**
        * Adds a number of weeks
        *@param value - weeks to add
        */
        virtual inline void AddWeek(int value);

        /**
        * Adds a number of months
        *@param value - months to add
        */
        virtual inline void AddMonth(int value);

        /**
        * Subtract a number of weeks
        *@param value - weeks to subtract
        */
        virtual inline void SubWeek(int value);

        /**
        * Subtract a number of months
        *@param value - months to subtract
        */
        virtual inline void SubMonth(int value);

        /**
        * Sets the duration
        *@param days - days
        *@param hours - hours
        *@param mins - minutes
        *@param secs - seconds
        */
        virtual inline void SetDuration(long days, int hours, int mins, int secs = 0);

    private:
        IEStatus m_Status;
        double   m_Span;
        int      m_HourPerDay;
        int      m_DayPerWeek;
        int      m_DayPerMonth;
        int      m_DayPerYear;

        /**
        * Gets a half second
        *@return the halp second
        */
        inline double GetHalfSecond() const;

        /**
        * Checks the range
        */
        inline void CheckRange();
};

/**
* Stores from the archive to the duration
*@param ar - archive
*@param duration - duration
*@return archive, to allow operator to be chained with other items, e.g a >> b >> c
*/
CArchive& AFXAPI operator << (CArchive& ar, const PSS_Duration& duration);

/**
* Stores the duration to the archive
*@param ar - archive
*@param duration - duration
*@return archive, to allow operator to be chained with other items, e.g a << b << c
*/
CArchive& AFXAPI operator >> (CArchive& ar, PSS_Duration& duration);

/**
* Streams the duration to the dump context
*@param dc - dump context
*@param duration - duration
*@return dump context, to allow operator to be chained with other items, e.g a >> b >> c
*/
#ifdef _DEBUG
    CDumpContext& AFXAPI operator << (CDumpContext& dc, const PSS_Duration& duration);
#endif

//---------------------------------------------------------------------------
// PSS_Duration
//---------------------------------------------------------------------------
PSS_Duration::PSS_Duration(int hourPerDay, int dayPerWeek, int dayPerMonth, int dayPerYear) :
    m_Status(IE_S_Valid),
    m_Span(0.0),
    m_HourPerDay(hourPerDay),
    m_DayPerWeek(dayPerWeek),
    m_DayPerMonth(dayPerMonth),
    m_DayPerYear(dayPerYear)
{}
//---------------------------------------------------------------------------
PSS_Duration::PSS_Duration(double value, int hourPerDay, int dayPerWeek, int dayPerMonth, int dayPerYear) :
    m_Status(IE_S_Valid),
    m_Span(value),
    m_HourPerDay(hourPerDay),
    m_DayPerWeek(dayPerWeek),
    m_DayPerMonth(dayPerMonth),
    m_DayPerYear(dayPerYear)
{}
//---------------------------------------------------------------------------
PSS_Duration::PSS_Duration(long days,
                           int  hours,
                           int  mins,
                           int  secs,
                           int  hourPerDay,
                           int  dayPerWeek,
                           int  dayPerMonth,
                           int  dayPerYear) :
    m_Status(IE_S_Valid),
    m_Span(0.0),
    m_HourPerDay(hourPerDay),
    m_DayPerWeek(dayPerWeek),
    m_DayPerMonth(dayPerMonth),
    m_DayPerYear(dayPerYear)
{
    SetDuration(days, hours, mins, secs);
}
//---------------------------------------------------------------------------
PSS_Duration::PSS_Duration(const PSS_Duration& other) :
    m_Status(IE_S_Valid),
    m_Span(0.0),
    m_HourPerDay(8),
    m_DayPerWeek(5),
    m_DayPerMonth(22),
    m_DayPerYear(220)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Duration::~PSS_Duration()
{}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator == (const PSS_Duration& other) const
{
    return (m_Status == other.m_Status && m_Span == other.m_Span);
}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator != (const PSS_Duration& other) const
{
    return (m_Status != other.m_Status || m_Span != other.m_Span);
}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator < (const PSS_Duration& other) const
{
    ASSERT(m_Status == IE_S_Valid);
    ASSERT(other.m_Status == IE_S_Valid);
    return (m_Span < other.m_Span);
}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator > (const PSS_Duration& other) const
{
    ASSERT(m_Status == IE_S_Valid);
    ASSERT(other.m_Status == IE_S_Valid);
    return (m_Span > other.m_Span);
}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator <= (const PSS_Duration& other) const
{
    ASSERT(m_Status == IE_S_Valid);
    ASSERT(other.m_Status == IE_S_Valid);
    return (m_Span <= other.m_Span);
}
//---------------------------------------------------------------------------
BOOL PSS_Duration::operator >= (const PSS_Duration& other) const
{
    ASSERT(m_Status == IE_S_Valid);
    ASSERT(other.m_Status == IE_S_Valid);
    return (m_Span >= other.m_Span);
}
//---------------------------------------------------------------------------
const PSS_Duration& PSS_Duration::operator += (const PSS_Duration& other)
{
    *this = *this + other;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_Duration& PSS_Duration::operator -= (const PSS_Duration& other)
{
    *this = *this - other;
    return *this;
}
//---------------------------------------------------------------------------
PSS_Duration PSS_Duration::operator - () const
{
    return -this->m_Span;
}
//---------------------------------------------------------------------------
PSS_Duration::operator double() const
{
    return m_Span;
}
//---------------------------------------------------------------------------
PSS_Duration::IEStatus PSS_Duration::GetStatus() const
{
    return m_Status;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetStatus(IEStatus status)
{
    m_Status = status;
}
//---------------------------------------------------------------------------
double PSS_Duration::GetSpan() const
{
    return m_Span;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetSpan(double value)
{
    m_Span = value;
}
//---------------------------------------------------------------------------
int PSS_Duration::GetHourPerDay() const
{
    return m_HourPerDay;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetHourPerDay(int value)
{
    m_HourPerDay = value;
}
//---------------------------------------------------------------------------
int PSS_Duration::GetDayPerWeek() const
{
    return m_DayPerWeek;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetDayPerWeek(int value)
{
    m_DayPerWeek = value;
}
//---------------------------------------------------------------------------
int PSS_Duration::GetDayPerMonth() const
{
    return m_DayPerMonth;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetDayPerMonth(int value)
{
    m_DayPerMonth = value;
}
//---------------------------------------------------------------------------
int PSS_Duration::GetDayPerYear() const
{
    return m_DayPerYear;
}
//---------------------------------------------------------------------------
void PSS_Duration::SetDayPerYear(int value)
{
    m_DayPerYear = value;
}
//---------------------------------------------------------------------------
double PSS_Duration::GetTotalDays() const
{
    ASSERT(m_Status == IE_S_Valid);
    return m_Span;
}
//---------------------------------------------------------------------------
double PSS_Duration::GetTotalHours() const
{
    ASSERT(m_Status == IE_S_Valid);
    return long(m_Span * double(m_HourPerDay) + GetHalfSecond());
}
//---------------------------------------------------------------------------
double PSS_Duration::GetTotalMinutes() const
{
    ASSERT(m_Status == IE_S_Valid);
    return long(m_Span * double(m_HourPerDay) * 60.0 + GetHalfSecond());
}
//---------------------------------------------------------------------------
double PSS_Duration::GetTotalSeconds() const
{
    ASSERT(m_Status == IE_S_Valid);
    return long(m_Span * double(m_HourPerDay) * 60.0 * 60.0 + GetHalfSecond());
}
//---------------------------------------------------------------------------
long PSS_Duration::GetDays() const
{
    ASSERT(m_Status == IE_S_Valid);
    return long(m_Span);
}
//---------------------------------------------------------------------------
double PSS_Duration::ConvertWeekToDays(int value) const
{
    return (double(m_DayPerWeek) * double(value));
}
//---------------------------------------------------------------------------
double PSS_Duration::ConvertMonthToDays(int value) const
{
    return (double(m_DayPerMonth) * double(value));
}
//---------------------------------------------------------------------------
void PSS_Duration::AddWeek(int value)
{
    *this += ConvertWeekToDays(value);
}
//---------------------------------------------------------------------------
void PSS_Duration::AddMonth(int value)
{
    *this += ConvertMonthToDays(value);
}
//---------------------------------------------------------------------------
void PSS_Duration::SubWeek(int value)
{
    *this -= ConvertWeekToDays(value);
}
//---------------------------------------------------------------------------
void PSS_Duration::SubMonth(int value)
{
    *this -= ConvertMonthToDays(value);
}
//---------------------------------------------------------------------------
void PSS_Duration::SetDuration(long days, int hours, int mins, int secs)
{
    // set date span by breaking into fractional days (all input ranges valid)
    m_Span = days                                           +
            (double(hours) /  double(m_HourPerDay))         +
            (double(mins)  / (double(m_HourPerDay) * 60.0)) +
            (double(secs)  / (double(m_HourPerDay) * 60.0 * 60.0));

    SetStatus(IE_S_Valid);
}
//---------------------------------------------------------------------------
double PSS_Duration::GetHalfSecond() const
{
    return (1.0 / (2.0 * (60.0 * 60.0 * double(m_HourPerDay))));
}
//---------------------------------------------------------------------------
void PSS_Duration::CheckRange()
{
    if (m_Span < -M_Max_Days_In_SpanDuration || m_Span > M_Max_Days_In_SpanDuration)
        SetStatus(IE_S_Invalid);
}
//---------------------------------------------------------------------------

#endif
