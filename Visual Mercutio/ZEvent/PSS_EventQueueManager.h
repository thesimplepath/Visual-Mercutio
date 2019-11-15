/****************************************************************************
 * ==> PSS_EventQueueManager -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event queue manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventQueueManagerH
#define PSS_EventQueueManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_EventManager.h"
#include "PSS_ActivityEventFile.h"

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
* Event queue manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventQueueManager
{
    public:
        PSS_EventQueueManager();
        virtual ~PSS_EventQueueManager();

        /**
        * Creates the class
        *@param directory - directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& directory);

        /**
        * Dispatches an activity event to the event queue
        *@param activityEvent - activity event to dispatch
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DispatchToEventQueue(const PSS_ActivityEvent& activityEvent);

    private:
        PSS_ActivityEventFile m_ActivityEventFile;
        CString               m_Directory;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventQueueManager(const PSS_EventQueueManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventQueueManager& operator = (const PSS_EventQueueManager& other);

        /**
        * Builds the activity event file name
        *@param activityEvent - activity event
        *@return the activity event file name
        */
        CString BuildActivityEventFilename(const PSS_ActivityEvent& activityEvent);
};

#endif
