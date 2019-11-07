/****************************************************************************
 * ==> PSS_ActivityEvent ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic file                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventH
#define PSS_ActivityEventH

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
#include "PSS_Event.h"

#ifdef _ZEVENTEXPORT
    //put the values back to make AFX_EXT_CLASS export again
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
const char g_EventPriorityHigh[]   = "HG";
const char g_EventPriorityMedium[] = "MD";
const char g_EventPriorityLow[]    = "LW";
//---------------------------------------------------------------------------

/**
* Activity event
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEvent : public PSS_Event
{
    DECLARE_DYNAMIC(PSS_ActivityEvent)

    public:
        /**
        * Activity event type
        */
        enum IEType
        {
            IE_AT_InvalidEvent,
            IE_AT_ToDo,
            IE_AT_Message,
            IE_AT_DeleteToDoEvent,
            IE_AT_LogEvent,
            IE_AT_DeleteFileEvent,
            IE_AT_FindProcessStateEvent,
            IE_AT_FindProcessesInitiatedEvent
        };

        typedef PSS_Event inherited;

        PSS_ActivityEvent();

        /**
        * Constructor
        *@param eventType - event type
        *@param fileName - file name
        *@param time - time
        *@param folderName - folder name
        *@param processName - process name
        *@param processCreationDate - process creation date
        *@param processDueDate - process due date
        *@param activityType - activity type
        *@param activityName - activity name
        *@param activityCreationDate - activity creation date
        *@param activityDueDate - activity due date
        *@param sender - sender
        *@param receiver - receiver
        *@param processFileName - process file name
        *@param exchangeDataFileName - exchange data file name
        *@param activityStatus - activity status
        *@param comments - comments
        *@param isInBackup - if TRUE, the activity happens in a backup context
        */
        PSS_ActivityEvent(IEType              eventType,
                          const CString&      fileName,
                          const COleDateTime& time,
                          const CString&      folderName,
                          const CString&      processName,
                          const COleDateTime& processCreationDate,
                          const COleDateTime& processDueDate,
                          const CString&      activityType,
                          const CString&      activityName,
                          const COleDateTime& activityCreationDate,
                          const COleDateTime& activityDueDate,
                          const CString&      sender,
                          const CString&      receiver,
                          const CString&      processFileName,
                          const CString&      exchangeDataFileName,
                          const CString&      processExchangeDataFileName,
                          const CString&      activityStatus,
                          const CString&      comments,
                          BOOL                isInBackup = FALSE);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEvent(const PSS_ActivityEvent& other);

        virtual ~PSS_ActivityEvent();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEvent& operator = (const PSS_ActivityEvent& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_ActivityEvent* Clone() const;

        /**
        * Gets the activity event type
        *@return the activity event type
        */
        virtual inline IEType GetActivityEventType() const;

        /**
        * Gets the activity event type as a string
        *@return the activity event type as a string
        */
        virtual CString GetActivityEventTypeString() const;

        /**
        * Sets the activity event type
        *@param value - the activity event type
        */
        virtual inline void SetActivityEventType(IEType value);
        virtual        void SetActivityEventType(const CString& value);

        /**
        * Gets the file extension type matching with an event type
        *@param eventType - event type
        *@return the file extension type
        */
        virtual CString GetFileExtension(int eventType = -1) const;

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
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Sets the file name
        *@param value - the file name
        */
        virtual inline void SetFileName(const CString& value);

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
        * Gets the process creation date
        *@return the process creation date
        */
        virtual inline PSS_Date GetProcessCreationDate() const;

        /**
        * Sets the process creation date
        *@param value - the process creation date
        */
        virtual inline void SetProcessCreationDate(const COleDateTime& value);

        /**
        * Sets the process creation date
        *@param year - year
        *@param month - month
        *@param day - day
        *@param hour - hour
        *@param min - min
        *@param sec - sec
        *@return the newly added date and time status
        */
        virtual inline int SetProcessCreationDate(int year, int month, int day, int hour, int min, int sec);

        /**
        * Sets the process creation date from a string
        *@param value - the process creation date
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetProcessCreationDate(const CString& value);

        /**
        * Gets the formatted process creation date
        *@return the formatted process creation date
        */
        virtual inline CString GetFormattedProcessCreationDate() const;

        /**
        * Gets the formatted process creation date and time
        *@return the formatted process creation date and time
        */
        virtual inline CString GetFormattedProcessCreationDateTime() const;

        /**
        * Gets the process due date
        *@return the process due date
        */
        virtual inline PSS_Date GetProcessDueDate() const;

        /**
        * Sets the process due date
        *@param value - the process due date
        */
        virtual inline void SetProcessDueDate(const COleDateTime& value);

        /**
        * Sets the process due date
        *@param year - year
        *@param month - month
        *@param day - day
        *@param hour - hour
        *@param min - min
        *@param sec - sec
        *@return the newly added date and time status
        */
        virtual inline int SetProcessDueDate(int year, int month, int day, int hour, int min, int sec);

        /**
        * Sets the process due date from a string
        *@param value - the process due date
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetProcessDueDate(const CString& value);

        /**
        * Gets the process due date as a string
        *@return the process due date as a string
        */
        virtual inline CString GetFormattedProcessDueDate() const;

        /**
        * Gets the process due date and time as a string
        *@return the process due date and time as a string
        */
        virtual inline CString GetFormattedProcessDueDateTime() const;

        /**
        * Gets the activity creation date
        *@return the activity creation date
        */
        virtual inline PSS_Date GetActivityCreationDate() const;

        /**
        * Sets the activity creation date
        *@param value - the activity creation date
        */
        virtual inline void SetActivityCreationDate(const COleDateTime& value);

        /**
        * Sets the activity creation date
        *@param year - year
        *@param month - month
        *@param day - day
        *@param hour - hour
        *@param min - min
        *@param sec - sec
        *@return the newly added date and time status
        */
        virtual inline int SetActivityCreationDate(int year, int month, int day, int hour, int min, int sec);

        /**
        * Sets the activity creation date from a string
        *@param value - the activity creation date
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetActivityCreationDate(const CString& value);

        /**
        * Gets the formatted activity creation date
        *@return the formatted activity creation date
        */
        virtual inline CString GetFormattedActivityCreationDate() const;

        /**
        * Gets the formatted activity creation date and time
        *@return the formatted activity creation date and time
        */
        virtual inline CString GetFormattedActivityCreationDateTime() const;

        /**
        * Gets the activity due date
        *@return the activity due date
        */
        virtual inline PSS_Date GetActivityDueDate() const;

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
        * Sets the activity due date
        *@param value - the activity due date
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetActivityDueDate(CString value);

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
        * Gets the activity type
        *@return the activity type
        */
        virtual inline CString GetActivityType() const;

        /**
        * Sets the activity type
        *@param value - the activity type
        */
        virtual inline void SetActivityType(const CString& value);

        /**
        * Gets the sender
        *@return the sender
        */
        virtual inline CString GetSender() const;

        /**
        * Sets the sender
        *@param value - the sender
        */
        virtual inline void SetSender(const CString& value);

        /**
        * Gets the receiver
        *@return the receiver
        */
        virtual inline CString GetReceiver() const;

        /**
        * Sets the receiver
        *@param value - the receiver
        */
        virtual inline void SetReceiver(const CString& value);

        /**
        * Gets the process file name
        *@return the process file name
        */
        virtual inline CString GetProcessFileName() const;

        /**
        * Sets the process file name
        *@param value - the process file name
        */
        virtual inline void SetProcessFileName(const CString& value);

        /**
        * Gets the Exchange data file name
        *@return the Exchange data file name
        */
        virtual inline CString GetExchangeDataFileName() const;

        /**
        * Sets the Exchange data file name
        *@param value - the Exchange data file name
        */
        virtual inline void SetExchangeDataFileName(const CString& value);

        /**
        * Gets the process Exchange data file name
        *@return the process Exchange data file name
        */
        virtual inline CString GetProcessExchangeDataFileName() const;

        /**
        * Sets the process Exchange data file name
        *@param value - the process Exchange data file name
        */
        virtual inline void SetProcessExchangeDataFileName(const CString& value);

        /**
        * Gets the activity status
        *@return the activity status
        */
        virtual inline CString GetActivityStatus() const;

        /**
        * Gets the activity status as a string
        *@return the activity status as a string
        */
        virtual CString GetActivityStatusString() const;

        /**
        * Sets the activity status
        *@param value - the activity status
        */
        virtual inline void SetActivityStatus(const CString& value);

        /**
        * Gets the comments
        *@return the comments
        */
        virtual inline CString GetComments() const;

        /**
        * Sets the comments
        *@param value - the comments
        */
        virtual inline void SetComments(const CString& value);

        /**
        * Gets if the activity happens in a backup context
        *@return TRUE if the activity happens in a backup context, otherwise FALSE
        */
        virtual inline BOOL GetIsInBackup() const;

        /**
        * Sets if the activity happens in a backup context
        *@param value - if TRUE, the activity happens in a backup context
        */
        virtual inline void SetIsInBackup(BOOL value = TRUE);
        virtual inline void SetIsInBackup(const CString& value);

    protected:
        IEType   m_ActivityEventType;
        PSS_Date m_ProcessCreationDate;
        PSS_Date m_ProcessDueDate;
        PSS_Date m_ActivityCreationDate;
        PSS_Date m_ActivityDueDate;
        CString  m_FolderName;
        CString  m_FileName;
        CString  m_ProcessName;
        CString  m_ActivityName;
        CString  m_ActivityType;
        CString  m_Sender;
        CString  m_Receiver;
        CString  m_ProcessFileName;
        CString  m_ExchangeDataFileName;
        CString  m_ProcessExchangeDataFileName;
        CString  m_ActivityStatus;
        CString  m_Comments;
        BOOL     m_IsInBackup;
};

//---------------------------------------------------------------------------
// PSS_ActivityEvent
//---------------------------------------------------------------------------
PSS_ActivityEvent::IEType PSS_ActivityEvent::GetActivityEventType() const
{
    return m_ActivityEventType;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityEventType(IEType value)
{
    m_ActivityEventType = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetFolderName(const CString& value)
{
    m_FolderName = value;
};
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetProcessName() const
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetProcessName(const CString& value)
{
    m_ProcessName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetActivityName() const
{
    return m_ActivityName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityName(const CString& value)
{
    m_ActivityName = value;
}
//---------------------------------------------------------------------------
PSS_Date PSS_ActivityEvent::GetProcessCreationDate() const
{
    return m_ProcessCreationDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetProcessCreationDate(const COleDateTime& value)
{
    m_ProcessCreationDate = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEvent::SetProcessCreationDate(int year, int month, int day, int hour, int min, int sec)
{
    return m_ProcessCreationDate.SetDateTime(year, month, day, hour, min, sec);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEvent::SetProcessCreationDate(const CString& value)
{
    return ParseDateTime(m_ProcessCreationDate, value);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedProcessCreationDate() const
{
    return m_ProcessCreationDate.Format(g_EventDateFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedProcessCreationDateTime() const
{
    return m_ProcessCreationDate.Format(g_EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
PSS_Date PSS_ActivityEvent::GetProcessDueDate() const
{
    return m_ProcessDueDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetProcessDueDate(const COleDateTime& value)
{
    m_ProcessDueDate = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEvent::SetProcessDueDate(int year, int month, int day, int hour, int min, int sec)
{
    return m_ProcessDueDate.SetDateTime(year, month, day, hour, min, sec);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEvent::SetProcessDueDate(const CString& value)
{
    return ParseDateTime(m_ProcessDueDate, value);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedProcessDueDate() const
{
    return m_ProcessDueDate.Format(g_EventDateFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedProcessDueDateTime() const
{
    return m_ProcessDueDate.Format(g_EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
PSS_Date PSS_ActivityEvent::GetActivityCreationDate() const
{
    return m_ActivityCreationDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityCreationDate(const COleDateTime& value)
{
    m_ActivityCreationDate = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEvent::SetActivityCreationDate(int year, int month, int day, int hour, int min, int sec)
{
    return m_ActivityCreationDate.SetDateTime(year, month, day, hour, min, sec);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEvent::SetActivityCreationDate(const CString& value)
{
    return ParseDateTime(m_ActivityCreationDate, value);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedActivityCreationDate() const
{
    return m_ActivityCreationDate.Format(g_EventDateFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedActivityCreationDateTime() const
{
    return m_ActivityCreationDate.Format(g_EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
PSS_Date PSS_ActivityEvent::GetActivityDueDate() const
{
    return m_ActivityDueDate;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityDueDate(const COleDateTime& value)
{
    m_ActivityDueDate = value;
}
//---------------------------------------------------------------------------
int PSS_ActivityEvent::SetActivityDueDate(int year, int month, int day, int hour, int min, int sec)
{
    return m_ActivityDueDate.SetDateTime(year, month, day, hour, min, sec);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEvent::SetActivityDueDate(CString value)
{
    return ParseDateTime(m_ActivityDueDate, value);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedActivityDueDate() const
{
    return m_ActivityDueDate.Format(g_EventDateFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFormattedActivityDueDateTime() const
{
    return m_ActivityDueDate.Format(g_EventDateTimeFormatString);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetActivityType() const
{
    return m_ActivityType;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityType(const CString& value)
{
    m_ActivityType = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetSender() const
{
    return m_Sender;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetSender(const CString& value)
{
    m_Sender = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetReceiver() const
{
    return m_Receiver;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetReceiver(const CString& value)
{
    m_Receiver = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetProcessFileName() const
{
    return m_ProcessFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetProcessFileName(const CString& value)
{
    m_ProcessFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetExchangeDataFileName() const
{
    return m_ExchangeDataFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetExchangeDataFileName(const CString& value)
{
    m_ExchangeDataFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetProcessExchangeDataFileName() const
{
    return m_ProcessExchangeDataFileName;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetProcessExchangeDataFileName(const CString& value)
{
    m_ProcessExchangeDataFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetActivityStatus() const
{
    return m_ActivityStatus;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityStatus(const CString& value)
{
    m_ActivityStatus = value;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetComments(const CString& value)
{
    m_Comments = value;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEvent::GetIsInBackup() const
{
    return m_IsInBackup;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetIsInBackup(BOOL value)
{
    m_IsInBackup = value;
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetIsInBackup(const CString& value)
{
    m_IsInBackup = std::atoi((const char*)value);
}
//---------------------------------------------------------------------------

#endif
