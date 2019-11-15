/****************************************************************************
 * ==> PSS_ActivityReminderEventManager ------------------------------------*
 ****************************************************************************
 * Description : Provides an activity reminder event manager                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityReminderEventManager.h"

// std
#include <memory>

// processsoft
#include "PSS_ActivityEventFile.h"
#include "ZEvtRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityReminderEventManager
//---------------------------------------------------------------------------
PSS_ActivityReminderEventManager::PSS_ActivityReminderEventManager(PSS_ActivityEventManager* pEventManager, int remindDays) :
    PSS_EventManager(),
    m_pEventManager(pEventManager),
    m_RemindDays(remindDays)
{}
//---------------------------------------------------------------------------
PSS_ActivityReminderEventManager::PSS_ActivityReminderEventManager(const PSS_ActivityReminderEventManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityReminderEventManager::~PSS_ActivityReminderEventManager()
{}
//---------------------------------------------------------------------------
const PSS_ActivityReminderEventManager& PSS_ActivityReminderEventManager::operator = (const PSS_ActivityReminderEventManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ActivityReminderEventManager::Create(PSS_ActivityEventManager* pEventManager, int remindDays)
{
    m_pEventManager = pEventManager;
    m_RemindDays    = remindDays;

    Refresh();
}
//---------------------------------------------------------------------------
int PSS_ActivityReminderEventManager::Refresh()
{
    RemoveAllEvents();

    PSS_ActivityEvent* pEvent;
    int                effectiveRemainingDays;
    const int          eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
    {
        pEvent = static_cast<PSS_ActivityEvent*>(m_pEventManager->GetEventAt(i));

        if (EventShouldBeReminded(pEvent, &effectiveRemainingDays))
            AddEvent(COleDateTime::GetCurrentTime(), g_EventPriorityHigh, effectiveRemainingDays, pEvent);
    }

    return GetEventCount();
}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent* PSS_ActivityReminderEventManager::AddEvent(const COleDateTime& time,
                                                                      const CString&      priority,
                                                                      const CString&      folderName,
                                                                      const CString&      processName,
                                                                      const CString&      activityName,
                                                                      int                 remainingDays,
                                                                      const COleDateTime& activityDueDate,
                                                                      const CString&      processFilename,
                                                                      const CString&      activityStatus,
                                                                      const CString&      message)
{
    std::unique_ptr<PSS_ActivityReminderEvent> pEvent(new PSS_ActivityReminderEvent(time,
                                                                                    priority,
                                                                                    folderName,
                                                                                    processName,
                                                                                    activityName,
                                                                                    remainingDays,
                                                                                    activityDueDate,
                                                                                    processFilename,
                                                                                    activityStatus,
                                                                                    message));

    if (!PSS_EventManager::AddEvent(pEvent.get()))
        return NULL;

    return pEvent.release();
}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent* PSS_ActivityReminderEventManager::AddEvent(const COleDateTime& time,
                                                                      const CString&      priority,
                                                                      int                 remainingDays,
                                                                      const CString&      message,
                                                                      PSS_ActivityEvent*  pEvent)
{
    if (!pEvent)
        return NULL;

    return AddEvent(time,
                    priority,
                    pEvent->GetFolderName(),
                    pEvent->GetProcessName(),
                    pEvent->GetActivityName(),
                    remainingDays,
                    pEvent->GetActivityDueDate(),
                    pEvent->GetProcessFileName(),
                    pEvent->GetActivityStatus(),
                    message);
}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent* PSS_ActivityReminderEventManager::AddEvent(const COleDateTime& time,
                                                                      const CString&      priority,
                                                                      int                 remainingDays,
                                                                      PSS_ActivityEvent*  pEvent)
{
    if (!pEvent)
        return NULL;

    return AddEvent(time,
                    priority,
                    pEvent->GetFolderName(),
                    pEvent->GetProcessName(),
                    pEvent->GetActivityName(),
                    remainingDays,
                    pEvent->GetActivityDueDate(),
                    pEvent->GetProcessFileName(),
                    pEvent->GetActivityStatus(),
                    BuildReminderMessage(remainingDays));
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityReminderEventManager::EventShouldBeReminded(PSS_ActivityEvent* pEvent, int* EffectiveRemainingDays)
{
    if (pEvent->GetActivityDueDate().IsEmpty())
        return FALSE;

    COleDateTime dueDate = COleDateTime(pEvent->GetActivityDueDate().GetYear(),
                                        pEvent->GetActivityDueDate().GetMonth(),
                                        pEvent->GetActivityDueDate().GetDay(),
                                        0,
                                        0,
                                        0);

    COleDateTime today = COleDateTime::GetCurrentTime();
    today.SetDate(today.GetYear(), today.GetMonth(), today.GetDay());

    *EffectiveRemainingDays = int(dueDate - today);

    return (*EffectiveRemainingDays <= COleDateTimeSpan(m_RemindDays));
}
//---------------------------------------------------------------------------
CString PSS_ActivityReminderEventManager::BuildReminderMessage(int remainingDays)
{
    CString text;

    if (!remainingDays)
        text.LoadString(IDS_REMINDERDAYSEQ0);
    else
    if (remainingDays < 0)
        text.LoadString(IDS_REMINDERDAYSLT0);
    else
        text.LoadString(IDS_REMINDERDAYS);

    return text;
}
//---------------------------------------------------------------------------
