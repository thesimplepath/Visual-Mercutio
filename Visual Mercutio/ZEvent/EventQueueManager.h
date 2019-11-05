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
#include "ActEvtFl.h"

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
    ~ZBEventQueueManager();
    BOOL    Create(const CString Directory);
    BOOL    DispatchToEventQueue(PSS_ActivityEvent& EventActivity);

protected:

private:
    ZBEventQueueManager(const ZBEventQueueManager &right);
    const ZBEventQueueManager & operator=(const ZBEventQueueManager &right);

    CString    BuildActivityEventFilename(PSS_ActivityEvent& EventActivity);

private:
    ZBEventActivityFile m_EventActivityFile;
    CString             m_Directory;
};

#endif
