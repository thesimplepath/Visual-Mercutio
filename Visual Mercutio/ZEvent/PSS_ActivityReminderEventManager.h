/****************************************************************************
 * ==> PSS_ActivityReminderEventManager ------------------------------------*
 ****************************************************************************
 * Description : Provides an activity reminder event manager                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityReminderEventManagerH
#define PSS_ActivityReminderEventManagerH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityReminderEvent.h"
#include "PSS_EventManager.h"
#include "PSS_ActivityEventManager.h"

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
* Activity reminder event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityReminderEventManager : public PSS_EventManager
{
public:
    /**
    * Constructor
    *@param pEventManager - event manager
    *@param remindDays - reminder days
    */
    PSS_ActivityReminderEventManager(PSS_ActivityEventManager* pEventManager = NULL, int remindDays = 1);

    virtual ~PSS_ActivityReminderEventManager();

    /**
    * Creates the manager
    *@param pEventManager - event manager
    *@param remindDays - reminder days
    */
    virtual void Create(PSS_ActivityEventManager* pEventManager, int remindDays = 1);

    /**
    * Refreshes the manager
    *@return the event count
    */
    virtual int Refresh();

    /**
    * Adds an event
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
    *@return newly added event, NULL on error
    */
    virtual PSS_ActivityReminderEvent* AddEvent(const COleDateTime& time,
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
    * Adds an event
    *@param time - time
    *@param priority - priority
    *@param remainingDays - remaining days
    *@param message - message
    *@param pEvent - event
    *@return newly added event, NULL on error
    */
    virtual PSS_ActivityReminderEvent* AddEvent(const COleDateTime& time,
                                                const CString&      priority,
                                                int                 remainingDays,
                                                const CString&      message,
                                                PSS_ActivityEvent*  pEvent);

    /**
    * Adds an event
    *@param time - time
    *@param priority - priority
    *@param remainingDays - remaining days
    *@param pEvent - event
    *@return newly added event, NULL on error
    */
    virtual PSS_ActivityReminderEvent* AddEvent(const COleDateTime& time,
                                                const CString&      priority,
                                                int                 remainingDays,
                                                PSS_ActivityEvent*  pEvent);

    /**
    * Checks if the event should be reminded
    *@param pEvent - event to check
    *@param pEffectiveRemainingDays - effective remaining days
    *@return TRUE if the event should be reminded, otherwise FALSE
    */
    virtual BOOL EventShouldBeReminded(PSS_ActivityEvent* pEvent, int* pEffectiveRemainingDays);

private:
    PSS_ActivityEventManager* m_pEventManager;
    int                       m_RemindDays;

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    PSS_ActivityReminderEventManager(const PSS_ActivityReminderEventManager& other);

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const PSS_ActivityReminderEventManager& operator = (const PSS_ActivityReminderEventManager& other);

    /**
    * Builds the reminder message
    *@param remainingDays - remaining days
    *@return the reminder message
    */
    CString BuildReminderMessage(int remainingDays);
};

#endif
