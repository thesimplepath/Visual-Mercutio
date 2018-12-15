// Source file: UserQueueManager.h

#ifndef UserQueueManager_h
#define UserQueueManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "EventManager.h"
#include "UserDMng.h"
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


class AFX_EXT_CLASS ZBUserQueueManager
{
  public:
        ZBUserQueueManager ();
        ~ZBUserQueueManager();
        BOOL                Create( const CString Directory );
        ZBEventActivity*    DispatchToUserQueue( const CString Filename );
        BOOL    RemoveEventFromUserQueue( ZBEventActivity& EventActivity, CString User );
        BOOL    RemoveEventFromReceiverQueue( ZBEventActivity& EventActivity );
        BOOL    RemoveEventFromSenderQueue( ZBEventActivity& EventActivity );

  protected:
        BOOL    ForwardToUserQueue( ZBEventActivity& EventActivity );
        BOOL    RemoveFromUserQueue( ZBEventActivity& EventActivity, CString User );
        BOOL    RemoveAssociatedEventFromUserQueue( ZBEventActivity& EventActivity );
        BOOL    CheckDirectory( ZBEventActivity& EventActivity );
        BOOL    ProceedDeleteMessage( ZBEventActivity& EventActivity );

  private:
      ZBUserQueueManager(const ZBUserQueueManager &right);
      const ZBUserQueueManager & operator=(const ZBUserQueueManager &right);

      CString    BuildUserActivityEventFilename( CString Filename, const CString User );
      BOOL        RemoveEventFilename( const CString Filename );

  private: //## implementation
    CString                    m_Directory;
    ZBUserDirectoryManager    m_UserDirectoryManager;
    ZBEventActivityFile        m_EventActivityFile;
};



//#undef  AFX_DATA
//#define AFX_DATA



#endif
