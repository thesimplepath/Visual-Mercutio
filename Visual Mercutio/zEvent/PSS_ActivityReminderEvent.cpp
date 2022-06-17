/****************************************************************************
 * ==> PSS_ActivityReminderEvent -------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event reminder                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityReminderEvent.h"

// processsoft
#include "ZEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ActivityReminderEvent
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent::PSS_ActivityReminderEvent() :
    PSS_Event(COleDateTime::GetCurrentTime(), g_Evt_Reminder),
    m_RemainingDays(0)
{}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent::PSS_ActivityReminderEvent(const COleDateTime& time,
                                                     const CString&      priority,
                                                     const CString&      folderName,
                                                     const CString&      processName,
                                                     const CString&      activityName,
                                                     int                 remainingDays,
                                                     const COleDateTime& activityDueDate,
                                                     const CString&      processFileName,
                                                     const CString&      activityStatus,
                                                     const CString&      message) :
    PSS_Event(time, g_Evt_Reminder),
    m_ActivityDueDate(activityDueDate),
    m_ProcessName(processName),
    m_FolderName(folderName),
    m_Priority(priority),
    m_ActivityName(activityName),
    m_ProcessFileName(processFileName),
    m_ActivityStatus(activityStatus),
    m_Message(message),
    m_RemainingDays(remainingDays)
{}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent::~PSS_ActivityReminderEvent()
{}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent::PSS_ActivityReminderEvent(const PSS_ActivityReminderEvent& other) :
    PSS_Event(),
    m_RemainingDays(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
const PSS_ActivityReminderEvent& PSS_ActivityReminderEvent::operator = (const PSS_ActivityReminderEvent& other)
{
    PSS_Event::operator = (other);

    m_ActivityDueDate = other.m_ActivityDueDate;
    m_ProcessName     = other.m_ProcessName;
    m_FolderName      = other.m_FolderName;
    m_Priority        = other.m_Priority;
    m_ActivityName    = other.m_ActivityName;
    m_ProcessFileName = other.m_ProcessFileName;
    m_ActivityStatus  = other.m_ActivityStatus;
    m_Message         = other.m_Message;
    m_RemainingDays   = other.m_RemainingDays;

    return *this;
}
//---------------------------------------------------------------------------
CString PSS_ActivityReminderEvent::GetRemainingDaysString() const
{
    char buffer[10];
    ::sprintf_s(buffer, 10, "%d", m_RemainingDays);
    return buffer;
}
//---------------------------------------------------------------------------
