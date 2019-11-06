/****************************************************************************
 * ==> PSS_ActivityEventReminder -------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event reminder                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventReminderH
#define PSS_ActivityEventReminderH

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
#include "ZBEvent.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Activity event reminder
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventReminder : public ZBEvent
{
    public:
        PSS_ActivityEventReminder();

        /**
        * Constructor
        *@param time - time
        *@param priority - priority
        *@param folderName - folder name
        *@param processName - process name
        *@param activityName - activity name
        *@param remainingDays - remaining days
        *@param activityDueDate - activity due date
        *@param processFileName - process file name
        *@param activityStatus - activity status
        *@param message - message
        */
        PSS_ActivityEventReminder(const COleDateTime& time,
                                  const CString&      priority,
                                  const CString&      folderName,
                                  const CString&      processName,
                                  const CString&      activityName,
                                  int                 remainingDays,
                                  const COleDateTime& activityDueDate,
                                  const CString&      processFileName,
                                  const CString&      activityStatus,
                                  const CString&      message);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventReminder(const PSS_ActivityEventReminder& other);

        virtual ~PSS_ActivityEventReminder();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventReminder& operator = (const PSS_ActivityEventReminder& other);

        /**
        * Gets the priority
        *@return the priority
        */
        virtual inline CString GetPriority() const;

        /**
        * Sets the priority
        *@param value - the priority
        */
        virtual inline void SetPriority(const CString& value);

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Sets the folder name
        *@param value - the folder name
        */
        virtual inline void SetFolderName(const CString& value);

        /**
        * Gets the process name
        *@return the process name
        */
        virtual inline CString GetProcessName() const;

        /**
        * Sets the process name
        *@param value - the process name
        */
        virtual inline void SetProcessName(const CString& value);

        /**
        * Gets the activity name
        *@return the activity name
        */
        virtual inline CString GetActivityName() const;

        /**
        * Sets the activity name
        *@param value - the activity name
        */
        virtual inline void SetActivityName(const CString& value);

        /**
        * Gets the remaining days
        *@return the remaining days
        */
        virtual inline int GetRemainingDays() const;

        /**
        * Gets the remaining days as a string
        *@return the remaining days as a string
        */
        virtual CString GetRemainingDaysString() const;

        /**
        * Sets the remaining days
        *@param value - the remaining days
        */
        virtual inline void SetRemainingDays(int value);

        /**
        * Gets the activity due date
        *@return the activity due date
        */
        virtual inline COleDateTime GetActivityDueDate() const;

        /**
        * Sets the activity due date
        *@param value - the activity due date
        */
        virtual inline void SetActivityDueDate(const COleDateTime& value);

        /**
        * Sets the activity due date
        *@param year - year
        *@param month - month
        *@param day - day
        *@param hour - hour
        *@param min - min
        *@param sec - sec
        *@return the newly added date and time status
        */
        virtual inline int SetActivityDueDate(int year, int month, int day, int hour, int min, int sec);

        /**
        * Sets the activity due date to a string
        *@param value - the activity due date
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetActivityDueDate(const CString& value);

        /**
        * Gets the formatted activity due date
        *@return the formatted activity due date
        */
        virtual inline CString GetFormattedActivityDueDate() const;

        /**
        * Gets the formatted activity due date and time
        *@return the formatted activity due date and time
        */
        virtual inline CString GetFormattedActivityDueDateTime() const;

        /**
        * Gets the process file name
        *@return the process file name
        */
        virtual inline CString GetProcessFilename() const;

        /**
        * Sets the process file name
        *@param value - the process file name
        */
        virtual inline void SetProcessFilename(const CString& value);

        /**
        * Gets the activity status
        *@return the activity status
        */
        virtual inline CString GetActivityStatus() const;

        /**
        * Sets the activity status
        *@param value - the activity status
        */
        virtual inline void SetActivityStatus(const CString& value);

        /**
        * Gets the message
        *@return the message
        */
        virtual inline CString GetMessage() const;

        /**
        * Sets the message
        *@param value - the message
        */
        virtual inline void SetMessage(const CString& value);

    protected:
        COleDateTime m_ActivityDueDate;
        CString      m_ProcessName;
        CString      m_FolderName;
        CString      m_Priority;
        CString      m_ActivityName;
        CString      m_ProcessFileName;
        CString      m_ActivityStatus;
        CString      m_Message;
        int          m_RemainingDays;
};

//---------------------------------------------------------------------------
// PSS_ActivityEventReminder
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetPriority() const
{
    return m_Priority;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetPriority(const CString& value)
{
    m_Priority = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetFolderName(const CString& value)
{
    m_FolderName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetProcessName() const
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetProcessName(const CString& value)
{
    m_ProcessName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetActivityName() const
{
    return m_ActivityName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetActivityName(const CString& value)
{
    m_ActivityName = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEventReminder::GetRemainingDays() const
{
    return m_RemainingDays;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetRemainingDays(int value)
{
    m_RemainingDays = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_ActivityEventReminder::GetActivityDueDate() const
{
    return m_ActivityDueDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetActivityDueDate(const COleDateTime& value)
{
    m_ActivityDueDate = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEventReminder::SetActivityDueDate(int year, int month, int day, int hour, int min, int sec)
{
    return m_ActivityDueDate.SetDateTime(year, month, day, hour, min, sec);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventReminder::SetActivityDueDate(const CString& value)
{
    return ParseDateTime(m_ActivityDueDate, value);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetFormattedActivityDueDate() const
{
    return m_ActivityDueDate.Format(EventDateFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetFormattedActivityDueDateTime() const
{
    return m_ActivityDueDate.Format(EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetProcessFilename() const
{
    return m_ProcessFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetProcessFilename(const CString& value)
{
    m_ProcessFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetActivityStatus() const
{
    return m_ActivityStatus;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetActivityStatus(const CString& value)
{
    m_ActivityStatus = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventReminder::GetMessage() const
{
    return m_Message;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventReminder::SetMessage(const CString& value)
{
    m_Message = value;
}
//---------------------------------------------------------------------------

#endif
