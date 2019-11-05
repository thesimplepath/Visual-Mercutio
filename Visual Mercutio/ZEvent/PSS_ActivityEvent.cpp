/****************************************************************************
 * ==> PSS_ActivityEvent ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic file                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityEvent.h"

// processsoft
#include "ZEvtRes.h"
#include "ZProcess.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ActivityEvent, ZBEvent)
//---------------------------------------------------------------------------
// PSS_ActivityEvent
//---------------------------------------------------------------------------
PSS_ActivityEvent::PSS_ActivityEvent() :
    ZBEvent(COleDateTime::GetCurrentTime(), EVT_ACTIVITY)
{}
//---------------------------------------------------------------------------
PSS_ActivityEvent::PSS_ActivityEvent(IEType              eventType,
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
                                     BOOL                isInBackup) :
    ZBEvent(time, EVT_ACTIVITY),
    m_ActivityEventType(eventType),
    m_ProcessCreationDate(processCreationDate),
    m_ProcessDueDate(processDueDate),
    m_ActivityCreationDate(activityCreationDate),
    m_ActivityDueDate(activityDueDate),
    m_FolderName(folderName),
    m_FileName(fileName),
    m_ProcessName(processName),
    m_ActivityName(activityName),
    m_ActivityType(activityType),
    m_Sender(sender),
    m_Receiver(receiver),
    m_ProcessFileName(processFileName),
    m_ExchangeDataFileName(exchangeDataFileName),
    m_ProcessExchangeDataFileName(processExchangeDataFileName),
    m_ActivityStatus(activityStatus),
    m_Comments(comments),
    m_IsInBackup(isInBackup)
{}
//---------------------------------------------------------------------------
PSS_ActivityEvent::~PSS_ActivityEvent()
{}
//---------------------------------------------------------------------------
PSS_ActivityEvent::PSS_ActivityEvent(const PSS_ActivityEvent& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
const PSS_ActivityEvent& PSS_ActivityEvent::operator = (const PSS_ActivityEvent& other)
{
    ZBEvent::operator = (other);

    m_ActivityEventType           = other.m_ActivityEventType;
    m_ProcessCreationDate         = other.m_ProcessCreationDate;
    m_ProcessDueDate              = other.m_ProcessDueDate;
    m_ActivityCreationDate        = other.m_ActivityCreationDate;
    m_ActivityDueDate             = other.m_ActivityDueDate;
    m_FolderName                  = other.m_FolderName;
    m_FileName                    = other.m_FileName;
    m_ProcessName                 = other.m_ProcessName;
    m_ActivityName                = other.m_ActivityName;
    m_ActivityType                = other.m_ActivityType;
    m_Sender                      = other.m_Sender;
    m_Receiver                    = other.m_Receiver;
    m_ProcessFileName             = other.m_ProcessFileName;
    m_ExchangeDataFileName        = other.m_ExchangeDataFileName;
    m_ProcessExchangeDataFileName = other.m_ProcessExchangeDataFileName;
    m_ActivityStatus              = other.m_ActivityStatus;
    m_Comments                    = other.m_Comments;
    m_IsInBackup                  = other.m_IsInBackup;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_ActivityEvent::Clone() const
{
    return new PSS_ActivityEvent(*this);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetActivityEventTypeString() const
{
    switch (GetActivityEventType())
    {
        case IE_AT_ToDo:                        return "TD";
        case IE_AT_Message:                     return "MS";
        case IE_AT_DeleteToDoEvent:             return "DT";
        case IE_AT_LogEvent:                    return "LG";
        case IE_AT_DeleteFileEvent:             return "DF";
        case IE_AT_FindProcessStateEvent:       return "FP";
        case IE_AT_FindProcessesInitiatedEvent: return "FI";
    }

    return "XX";
}
//---------------------------------------------------------------------------
void PSS_ActivityEvent::SetActivityEventType(const CString& value)
{
    if (value == "TD")
        SetActivityEventType(IE_AT_ToDo);
    else
    if (value == "MS")
        SetActivityEventType(IE_AT_Message);
    else
    if (value == "DT")
        SetActivityEventType(IE_AT_DeleteToDoEvent);
    else
    if (value == "LG")
        SetActivityEventType(IE_AT_LogEvent);
    else
    if (value == "DF")
        SetActivityEventType(IE_AT_DeleteFileEvent);
    else
    if (value == "FP")
        SetActivityEventType(IE_AT_FindProcessStateEvent);
    else
    if (value == "FI")
        SetActivityEventType(IE_AT_FindProcessesInitiatedEvent);
    else
        SetActivityEventType(IE_AT_InvalidEvent);
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetFileExtension(int eventType) const
{
    switch (eventType == -1 ? GetActivityEventType() : IEType(eventType))
    {
        case IE_AT_ToDo:                        return g_EventExtension;
        case IE_AT_Message:                     return g_EventMessageExtension;
        case IE_AT_DeleteToDoEvent:
        case IE_AT_LogEvent:
        case IE_AT_DeleteFileEvent:
        case IE_AT_FindProcessStateEvent:
        case IE_AT_FindProcessesInitiatedEvent: return g_EventTemporalExtension;
    }

    return ".err";
}
//---------------------------------------------------------------------------
CString PSS_ActivityEvent::GetActivityStatusString() const
{
    return ZProcess::GetStatusString(m_ActivityStatus);
}
//---------------------------------------------------------------------------
