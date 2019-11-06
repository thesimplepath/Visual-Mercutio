// Source file: EventQueueManager.h

#ifndef EventQueueManager_h
#define EventQueueManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "EventManager.h"
#include "PSS_ActivityEventFile.h"

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


class AFX_EXT_CLASS ZBEventQueueManager
{
public:
    ZBEventQueueManager();
    virtual ~ZBEventQueueManager();

    BOOL Create(const CString Directory);

    BOOL DispatchToEventQueue(PSS_ActivityEvent& EventActivity);

private:
    PSS_ActivityEventFile m_ActivityEventFile;
    CString               m_Directory;

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    ZBEventQueueManager(const ZBEventQueueManager& other);

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const ZBEventQueueManager& operator = (const ZBEventQueueManager& other);

    CString BuildActivityEventFilename(PSS_ActivityEvent& EventActivity);
};

#endif
