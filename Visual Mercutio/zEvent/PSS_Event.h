/****************************************************************************
 * ==> PSS_Event -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic event                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventH
#define PSS_EventH

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
#include "zBaseLib\PSS_ListCtrl.h"
#include "zBaseLib\PSS_Date.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int  g_Evt_Undefined               = 0;
const int  g_Evt_Server                  = 1;
const int  g_Evt_Activity                = 2;
const int  g_Evt_Reminder                = 3;
const int  g_Evt_Overview                = 4;
const char g_EventDateTimeFormatString[] = "%d.%m.%Y - %H:%M:%S";
const char g_EventDateFormatString[]     = "%d.%m.%Y";
//---------------------------------------------------------------------------

/**
* Generic event
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Event : public CObject
{
    DECLARE_DYNAMIC(PSS_Event)

    public:
        typedef CObject inherited;

        PSS_Event();

        /**
        * Constructor
        *@param timeStamp - time stamp
        *@param eventID - event identifier
        *@param userQueue - user queue
        */
        PSS_Event(const COleDateTime& timeStamp, int eventID = g_Evt_Undefined, const CString& userQueue = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Event(const PSS_Event& other);

        virtual ~PSS_Event();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Event& operator = (const PSS_Event& other);

        /**
        * Stores from the event to the list controller
        *@param event - event
        *@param listCtrl - list controller
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        #ifdef _WIN32
            AFX_EXT_API friend PSS_Event& operator >> (PSS_Event& left, PSS_ListCtrl& listCtrl);
        #endif

        /**
        * Gets the time stamp
        *@return the time stamp
        */
        virtual inline PSS_Date GetTimeStamp() const;

        /**
        * Gets the formatted time stamp
        *@return the time stamp
        */
        virtual inline CString GetFormattedTimeStamp() const;

        /**
        * Gets the event identifier
        *@return the event identifier
        */
        virtual inline int GetEventID() const;

        /**
        * Gets the event identifier as a string
        *@return the string containing the event identifier
        */
        virtual CString GetEventIDStr() const;

        /**
        * Gets the user queue
        *@return the user queue
        */
        virtual inline CString GetUserQueue() const;

        /**
        * Sets the user queue
        *@param value - the user queue
        */
        virtual inline void SetUserQueue(const CString& value);

        /**
        * Checks if the event is in the user queue
        *@return TRUE if the event is in the user queue, otherwise FALSE
        */
        virtual inline BOOL IsInUserQueue() const;

        /**
        * Parses the date and time
        *@param[out] dateTime - date and time to populate with the parsed value
        *@param value - the date and time value to parse
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ParseDateTime(COleDateTime& dateTime, const CString& value) const;

    protected:
        PSS_Date m_TimeStamp;
        CString  m_UserQueue;
        int      m_EventID;
};

//---------------------------------------------------------------------------
// PSS_Event
//---------------------------------------------------------------------------
PSS_Date PSS_Event::GetTimeStamp() const
{
    return m_TimeStamp;
}
//---------------------------------------------------------------------------
CString PSS_Event::GetFormattedTimeStamp() const
{
    return m_TimeStamp.Format(g_EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
int PSS_Event::GetEventID() const
{
    return m_EventID;
}
//---------------------------------------------------------------------------
CString PSS_Event::GetUserQueue() const
{
    return m_UserQueue;
}
//---------------------------------------------------------------------------
void PSS_Event::SetUserQueue(const CString& value)
{
    m_UserQueue = value;
}
//---------------------------------------------------------------------------
BOOL PSS_Event::IsInUserQueue() const
{
    return (m_UserQueue.IsEmpty() != TRUE);
}
//---------------------------------------------------------------------------

#endif