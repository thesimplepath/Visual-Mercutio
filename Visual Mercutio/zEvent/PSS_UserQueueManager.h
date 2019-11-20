/****************************************************************************
 * ==> PSS_UserQueueManager ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user queue manager                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserQueueManagerH
#define PSS_UserQueueManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_EventManager.h"
#include "PSS_UserDirectoryManager.h"
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
* User queue manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserQueueManager
{
    public:
        PSS_UserQueueManager();
        virtual ~PSS_UserQueueManager();

        /**
        * Creates the queue
        *@param directory - directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& directory);

        /**
        * Dispatches an user to the user queue
        *@param fileName - the file name
        *@return the dispatched user activity event, NULL on error
        */
        virtual PSS_ActivityEvent* DispatchToUserQueue(const CString& fileName);

        /**
        * Removes an activity event from the user queue
        *@param activityEvent - activity event to remove
        *@param user - user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveEventFromUserQueue(const PSS_ActivityEvent& activityEvent, const CString& user);

        /**
        * Removes an activity event from the receiver queue
        *@param activityEvent - activity event to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveEventFromReceiverQueue(const PSS_ActivityEvent& activityEvent);

        /**
        * Removes an activity event from the sender queue
        *@param activityEvent - activity event to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveEventFromSenderQueue(const PSS_ActivityEvent& activityEvent);

    protected:
        /**
        * Forwards an activity event from the user queue
        *@param activityEvent - activity event to forward
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ForwardToUserQueue(const PSS_ActivityEvent& activityEvent);

        /**
        * Removes an activity event from the user queue
        *@param activityEvent - activity event to remove
        *@param user - user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFromUserQueue(const PSS_ActivityEvent& activityEvent, const CString& user);

        /**
        * Removes an associated activity event from the user queue
        *@param activityEvent - activity event to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveAssociatedEventFromUserQueue(const PSS_ActivityEvent& activityEvent);

        /**
        * Checks the directory matching with an activity event
        *@param activityEvent - the activity event
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CheckDirectory(const PSS_ActivityEvent& activityEvent);

        /**
        * Proceeds to the delete message
        *@param activityEvent - the activity event
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ProceedDeleteMessage(const PSS_ActivityEvent& activityEvent);

    private:
        PSS_UserDirectoryManager m_UserDirectoryManager;
        PSS_ActivityEventFile    m_ActivityEventFile;
        CString                  m_Directory;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserQueueManager(const PSS_UserQueueManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserQueueManager& operator = (const PSS_UserQueueManager& other);

        /**
        * Builds the activity event file name
        *@param fileName - the file name template
        *@param user - the user name
        *@return the activity event file name
        */
        CString BuildUserActivityEventFileName(const CString& fileName, const CString& user);

        /**
        * Removes the activity event file name
        *@param fileName - the file name to remove
        *@return TRUE on success, otherwise FALSE
        */
        BOOL RemoveEventFileName(const CString& fileName);
};

#endif
