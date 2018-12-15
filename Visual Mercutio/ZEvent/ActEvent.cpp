// ActEvent.cpp: implementation of the ZBEventActivity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ActEvent.h"
#include "ZEvtRes.h"
#include "ZProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBEventActivity, ZBEvent )



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBEventActivity::ZBEventActivity()
: ZBEvent(COleDateTime::GetCurrentTime(), EVT_ACTIVITY)
{

}

ZBEventActivity::ZBEventActivity(ActivityEventType EventType,
                                 CString Filename,
                                 COleDateTime Time, 
                                 CString FolderName,
                                 CString ProcessName,
                                 COleDateTime ProcessCreationDate,
                                 COleDateTime ProcessDueDate,
                                 CString ActivityType,
                                 CString ActivityName,
                                 COleDateTime ActivityCreationDate,
                                 COleDateTime ActivityDueDate,
                                 CString Sender,
                                 CString Receiver,
                                 CString ProcessFilename,
                                 CString ExchangeDataFilename,
                                 CString ProcessExchangeDataFilename,
                                 CString ActivityStatus,
                                 CString Comments,
                                 BOOL     IsInBackup)
:    ZBEvent(Time, EVT_ACTIVITY),
    m_ActivityEventType(EventType),
    m_FolderName(FolderName),
    m_Filename(Filename),
    m_ProcessName(ProcessName),
    m_ProcessCreationDate(ProcessCreationDate),
    m_ProcessDueDate(ProcessDueDate),
    m_ActivityType(ActivityType),
    m_ActivityName(ActivityName),
    m_ActivityCreationDate(ActivityCreationDate),
    m_ActivityDueDate(ActivityDueDate),
    m_Sender(Sender),
    m_Receiver(Receiver),
    m_ProcessFilename(ProcessFilename),
    m_ExchangeDataFilename(ExchangeDataFilename),
    m_ProcessExchangeDataFilename(ProcessExchangeDataFilename),
    m_ActivityStatus(ActivityStatus),
    m_Comments(Comments),
    m_IsInBackup(IsInBackup)
{
}

ZBEventActivity::~ZBEventActivity()
{

}



ZBEventActivity::ZBEventActivity(const ZBEventActivity &right)
{
    *this = right;
}

const ZBEventActivity & ZBEventActivity::operator=(const ZBEventActivity &right)
{
    ZBEvent::operator=( right );
    m_ActivityEventType = right.m_ActivityEventType;
    m_FolderName = right.m_FolderName;
    m_Filename = right.m_Filename;
    m_ProcessName = right.m_ProcessName;
    m_ProcessCreationDate = right.m_ProcessCreationDate;
    m_ProcessDueDate = right.m_ProcessDueDate;
    m_ActivityType = right.m_ActivityType;
    m_ActivityName = right.m_ActivityName;
    m_ActivityCreationDate = right.m_ActivityCreationDate;
    m_ActivityDueDate = right.m_ActivityDueDate;
    m_Sender = right.m_Sender;
    m_Receiver = right.m_Receiver;
    m_ProcessFilename = right.m_ProcessFilename;
    m_ExchangeDataFilename = right.m_ExchangeDataFilename;
    m_ProcessExchangeDataFilename = right.m_ProcessExchangeDataFilename;
    m_ActivityStatus = right.m_ActivityStatus;
    m_Comments = right.m_Comments;    
    m_IsInBackup = right.m_IsInBackup;
    return *this;
}

ZBEventActivity*    ZBEventActivity::Clone()
{
    ZBEventActivity*    pNew = new ZBEventActivity( *this );
    return pNew;
}
CString    ZBEventActivity::GetActivityEventTypeString() const
{
    switch (GetActivityEventType())
    {
        case ToDoActivity: return "TD";
        case MessageActivity: return "MS";
        case DeleteToDoEvent: return "DT";
        case LogActivityEvent: return "LG";
        case DeleteFileEvent: return "DF";
        case FindProcessStateEvent: return "FP";
        case FindProcessesInitiatedEvent: return "FI";
    }
    return "XX";
}


void    ZBEventActivity::SetActivityEventType(const CString value)
{
    if (value == "TD")
        SetActivityEventType( ToDoActivity );
    else
    if (value == "MS")
        SetActivityEventType( MessageActivity );
    else
    if (value == "DT")
        SetActivityEventType( DeleteToDoEvent );
    else
    if (value == "LG")
        SetActivityEventType( LogActivityEvent );
    else
    if (value == "DF")
        SetActivityEventType( DeleteFileEvent );
    else
    if (value == "FP")
        SetActivityEventType( FindProcessStateEvent );
    else
    if (value == "FI")
        SetActivityEventType( FindProcessesInitiatedEvent );
    else
        SetActivityEventType( InvalidActivityEvent );
}


CString    ZBEventActivity::GetActivityStatusString() const
{
    return ZProcess::GetStatusString( m_ActivityStatus );
}


CString    ZBEventActivity::GetFileExtension( int EventType ) const
{
    EventType = (EventType == -1) ? GetActivityEventType() : (ActivityEventType)EventType;
    switch (EventType)
    {
        case ToDoActivity: return sEventExtension;
        case MessageActivity: return sEventMessageExtension;
        case DeleteToDoEvent: 
        case LogActivityEvent:
        case DeleteFileEvent:
        case FindProcessStateEvent:
        case FindProcessesInitiatedEvent:
        {
            return sEventTemporalExtension;
        }
    }
    return ".err";
}
