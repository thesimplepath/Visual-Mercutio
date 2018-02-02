// Source file: ActEvtReminderManager.cpp

#include <StdAfx.h>

#include "ActEvtReminderManager.h"
#include "ActEvtFl.h"
#include "ZEvtRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBActivityEventReminderManager 


ZBActivityEventReminderManager::ZBActivityEventReminderManager(ZBActivityEventManager* pEventManager, int RemindDays)
: m_pEventManager(pEventManager), m_RemindDays(RemindDays)
{
}

ZBActivityEventReminderManager::~ZBActivityEventReminderManager()
{
}

void	ZBActivityEventReminderManager::Create( ZBActivityEventManager* pEventManager, int RemindDays )
{
	m_pEventManager = pEventManager;
	m_RemindDays = RemindDays;
	Refresh();
}

int	ZBActivityEventReminderManager::Refresh()
{
	RemoveAllEvents();
	ZBEventActivity*	pEvent;
	int					EffectiveRemainingDays;				
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		pEvent = (ZBEventActivity*)m_pEventManager->GetEventAt(i);
		if (EventShouldBeReminded( pEvent, &EffectiveRemainingDays ))
			AddEvent( COleDateTime::GetCurrentTime(),
					  EventPriorityHigh,
					  EffectiveRemainingDays,
					  pEvent );
	}
	return GetEventCount();
}



ZBEventActivityReminder*	ZBActivityEventReminderManager::AddEvent(COleDateTime Time,
																	 CString Priority,
																	 int	 RemainingDays,
																	 CString Message,
																	 ZBEventActivity* pEvent)
{
	return AddEvent(Time,
					Priority,
					pEvent->GetFolderName(),
					pEvent->GetProcessName(),
					pEvent->GetActivityName(),
					RemainingDays,
					pEvent->GetActivityDueDate(), 
					pEvent->GetProcessFilename(),
					pEvent->GetActivityStatus(),
					Message);
}

ZBEventActivityReminder*	ZBActivityEventReminderManager::AddEvent(COleDateTime Time,
																	 CString Priority,
																	 int	 RemainingDays,
																	 ZBEventActivity* pEvent)
{
	return AddEvent(Time,
					Priority,
					pEvent->GetFolderName(),
					pEvent->GetProcessName(),
					pEvent->GetActivityName(),
					RemainingDays,
					pEvent->GetActivityDueDate(), 
					pEvent->GetProcessFilename(),
					pEvent->GetActivityStatus(),
					BuildReminderMessage( RemainingDays ));
}

ZBEventActivityReminder* ZBActivityEventReminderManager::AddEvent(COleDateTime Time,
																  CString Priority,
																  CString FolderName,
																  CString ProcessName,
																  CString ActivityName,
																  int	 RemainingDays,
																  COleDateTime ActivityDueDate,
																  CString ProcessFilename,
																  CString ActivityStatus,
																  CString Message)
{
	ZBEventActivityReminder*	pEvent = new ZBEventActivityReminder( Time,
																	  Priority,
																	  FolderName,
																	  ProcessName,
																	  ActivityName,
																	  RemainingDays,
																	  ActivityDueDate,
																	  ProcessFilename,
																	  ActivityStatus,
																	  Message);
	if (!ZBEventManager::AddEvent( pEvent ))
	{
		delete pEvent;
		pEvent = NULL;
	}
	return pEvent;
}



BOOL	ZBActivityEventReminderManager::EventShouldBeReminded( ZBEventActivity* pEvent, int* EffectiveRemainingDays )
{
	if (pEvent->GetActivityDueDate().IsEmpty())
		return FALSE;
	COleDateTime	DueDate = COleDateTime(pEvent->GetActivityDueDate().GetYear(), 
										   pEvent->GetActivityDueDate().GetMonth(), 
										   pEvent->GetActivityDueDate().GetDay(),
										   0,0,0);
	COleDateTime	Today =  COleDateTime::GetCurrentTime();
	Today.SetDate(Today.GetYear(), Today.GetMonth(), Today.GetDay() );
	*EffectiveRemainingDays = (int)(DueDate - Today);
	return (*EffectiveRemainingDays <= COleDateTimeSpan(m_RemindDays)) ? TRUE : FALSE;
}


CString	ZBActivityEventReminderManager::BuildReminderMessage( int RemainingDays )
{
	CString	Text;
	if (RemainingDays == 0)
		Text.LoadString( IDS_REMINDERDAYSEQ0 );
	else
		if (RemainingDays < 0)
			Text.LoadString( IDS_REMINDERDAYSLT0 );
		else
			Text.LoadString( IDS_REMINDERDAYS );
	return Text;
}
