// Source file: UserQueueManager.h

#ifndef UserQueueManager_h
#define UserQueueManager_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_EventManager.h"
#include "UserDMng.h"
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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBUserQueueManager
{
public:
    ZBUserQueueManager();
    ~ZBUserQueueManager();
    BOOL                Create(const CString Directory);
    PSS_ActivityEvent*    DispatchToUserQueue(const CString Filename);
    BOOL    RemoveEventFromUserQueue(PSS_ActivityEvent& EventActivity, CString User);
    BOOL    RemoveEventFromReceiverQueue(PSS_ActivityEvent& EventActivity);
    BOOL    RemoveEventFromSenderQueue(PSS_ActivityEvent& EventActivity);

protected:
    BOOL    ForwardToUserQueue(PSS_ActivityEvent& EventActivity);
    BOOL    RemoveFromUserQueue(PSS_ActivityEvent& EventActivity, CString User);
    BOOL    RemoveAssociatedEventFromUserQueue(PSS_ActivityEvent& EventActivity);
    BOOL    CheckDirectory(PSS_ActivityEvent& EventActivity);
    BOOL    ProceedDeleteMessage(PSS_ActivityEvent& EventActivity);

private:
    ZBUserQueueManager(const ZBUserQueueManager &right);
    const ZBUserQueueManager & operator=(const ZBUserQueueManager &right);

    CString    BuildUserActivityEventFilename(CString Filename, const CString User);
    BOOL        RemoveEventFilename(const CString Filename);

private:
    ZBUserDirectoryManager m_UserDirectoryManager;
    PSS_ActivityEventFile  m_ActivityEventFile;
    CString                m_Directory;
};

#endif
