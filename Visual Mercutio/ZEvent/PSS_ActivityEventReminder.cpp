/****************************************************************************
 * ==> PSS_ActivityEventReminder -------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event reminder                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityEventReminder.h"

// processsoft
#include "ZEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ActivityEventReminder
//---------------------------------------------------------------------------
PSS_ActivityEventReminder::PSS_ActivityEventReminder() :
    ZBEvent(COleDateTime::GetCurrentTime(), EVT_REMINDER)
{}
//---------------------------------------------------------------------------
PSS_ActivityEventReminder::PSS_ActivityEventReminder(const COleDateTime& time,
                                                     const CString&      priority,
                                                     const CString&      folderName,
                                                     const CString&      processName,
                                                     const CString&      activityName,
                                                     int                 remainingDays,
                                                     const COleDateTime& activityDueDate,
                                                     const CString&      processFileName,
                                                     const CString&      activityStatus,
                                                     const CString&      message) :
    ZBEvent(time, EVT_REMINDER),
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
PSS_ActivityEventReminder::~PSS_ActivityEventReminder()
{}
//---------------------------------------------------------------------------
PSS_ActivityEventReminder::PSS_ActivityEventReminder(const PSS_ActivityEventReminder& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
const PSS_ActivityEventReminder& PSS_ActivityEventReminder::operator = (const PSS_ActivityEventReminder& other)
{
    ZBEvent::operator = (other);

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
CString PSS_ActivityEventReminder::GetRemainingDaysString() const
{
    char buffer[10];
    sprintf_s(buffer, _tcslen(buffer), "%d", m_RemainingDays);
    return buffer;
}
//---------------------------------------------------------------------------
