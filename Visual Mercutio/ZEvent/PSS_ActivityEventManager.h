/****************************************************************************
 * ==> PSS_ActivityEventManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventManagerH
#define PSS_ActivityEventManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"
#include "EventManager.h"

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
* Activity event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventManager : public ZBEventManager
{
    public:
        PSS_ActivityEventManager();
        virtual ~PSS_ActivityEventManager();

        /**
        * Constructor
        *@param eventType - event type
        *@param fileName - file name
        *@param time - time
        *@param folderName - folder name
        *@param processName - process name
        *@param processCreationDate - process creation date
        *@param processDueDate - process due date
        *@param activityType - activity type
        *@param activityName - activity name
        *@param activityCreationDate - activity creation date
        *@param activityDueDate - activity due date
        *@param sender - sender
        *@param receiver - receiver
        *@param processFileName - process file name
        *@param exchangeDataFileName - exchange data file name
        *@param processExchangeDataFileName - process Exchange data file name
        *@param activityStatus - activity status
        *@param comments - comments
        */
        virtual PSS_ActivityEvent* AddEvent(PSS_ActivityEvent::IEType eventType,
                                            const CString&            fileName,
                                            const COleDateTime&       time,
                                            const CString&            folderName,
                                            const CString&            processName,
                                            const COleDateTime&       processCreationDate,
                                            const COleDateTime&       processDueDate,
                                            const CString&            activityType,
                                            const CString&            activityName,
                                            const COleDateTime&       activityCreationDate,
                                            const COleDateTime&       activityDueDate,
                                            const CString&            sender,
                                            const CString&            receiver,
                                            const CString&            processFileName,
                                            const CString&            exchangeDataFileName,
                                            const CString&            processExchangeDataFileName,
                                            const CString&            activityStatus,
                                            const CString&            comments);

        /**
        * Loads an event from a file
        *@param fileName - file name
        *@return the event, NULL on error
        */
        virtual PSS_Event* LoadEventFromFile(const CString& fileName);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventManager(const PSS_ActivityEventManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventManager& operator = (const PSS_ActivityEventManager& other);
};

#endif
