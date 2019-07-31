// ActEventReminder.cpp: implementation of the ZBEventActivityReminder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ActEventReminder.h"
#include "ZEvtRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBEventActivityReminder::ZBEventActivityReminder()
: ZBEvent(COleDateTime::GetCurrentTime(), EVT_REMINDER)
{

}

ZBEventActivityReminder::ZBEventActivityReminder(COleDateTime Time,
                                                 CString Priority,
                                                 CString FolderName,
                                                 CString ProcessName,
                                                 CString ActivityName,
                                                 int     RemainingDays,
                                                 COleDateTime ActivityDueDate,
                                                 CString ProcessFilename,
                                                 CString ActivityStatus,
                                                 CString Message)
:    ZBEvent(Time, EVT_REMINDER), 
    m_Priority(Priority),
    m_FolderName(FolderName),
    m_ProcessName(ProcessName),
    m_ActivityName(ActivityName),
    m_RemainingDays(RemainingDays),
    m_ActivityDueDate(ActivityDueDate),
    m_ProcessFilename(ProcessFilename),
    m_ActivityStatus(ActivityStatus),
    m_Message(Message)
{
}

ZBEventActivityReminder::~ZBEventActivityReminder()
{

}



ZBEventActivityReminder::ZBEventActivityReminder(const ZBEventActivityReminder &right)
{
    *this = right;
}

const ZBEventActivityReminder & ZBEventActivityReminder::operator=(const ZBEventActivityReminder &right)
{
    ZBEvent::operator=( right );
    m_Priority = right.m_Priority;
    m_FolderName = right.m_FolderName;
    m_ProcessName = right.m_ProcessName;
    m_ActivityName = right.m_ActivityName;
    m_RemainingDays = right.m_RemainingDays;
    m_ActivityDueDate = right.m_ActivityDueDate;
    m_ProcessFilename = right.m_ProcessFilename;
    m_ActivityStatus = right.m_ActivityStatus;
    m_Message = right.m_Message;    
    return *this;
}


CString ZBEventActivityReminder::GetRemainingDaysString() const
{
    char buffer[10];
    sprintf_s(buffer, _tcslen(buffer), "%d", m_RemainingDays);
    return buffer;
}