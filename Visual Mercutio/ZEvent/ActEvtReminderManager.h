// Source file: ActEvtReminderManager.h

#ifndef ActEvtReminderManager_h
#define ActEvtReminderManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEventReminder.h"
#include "EventManager.h"
#include "ActEvtManager.h"

#ifdef _ZEVENTEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBActivityEventReminderManager : public	ZBEventManager
{
  public:
      ZBActivityEventReminderManager (ZBActivityEventManager* pEventManager = NULL, int RemindDays = 1);
	  void	Create( ZBActivityEventManager* pEventManager, int RemindDays = 1 );
	  int	Refresh();

      ~ZBActivityEventReminderManager();
	  ZBEventActivityReminder*	AddEvent(COleDateTime Time,
										 CString Priority,
										 CString FolderName,
										 CString ProcessName,
										 CString ActivityName,
										 int	 RemainingDays,
										 COleDateTime ActivityDueDate,
										 CString ProcessFilename,
										 CString ActivityStatus,
										 CString Message);

	  ZBEventActivityReminder*	AddEvent(COleDateTime Time,
										 CString Priority,
										 int	 RemainingDays,
										 CString Message,
										 ZBEventActivity* pEvent);

	  ZBEventActivityReminder*	AddEvent(COleDateTime Time,
										 CString Priority,
										 int	 RemainingDays,
										 ZBEventActivity* pEvent);

	  BOOL	EventShouldBeReminded( ZBEventActivity* pEvent, int* EffectiveRemainingDays );

  protected:

  private:
      ZBActivityEventReminderManager(const ZBActivityEventReminderManager &right);
      const ZBActivityEventReminderManager & operator=(const ZBActivityEventReminderManager &right);

	  CString	BuildReminderMessage( int RemainingDays );
  private:
	  ZBActivityEventManager*	m_pEventManager;
	  int						m_RemindDays;
};



//#undef  AFX_DATA
//#define AFX_DATA



#endif
