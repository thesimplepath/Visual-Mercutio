// Source file: SrvEvtManager.h

#ifndef ServerEventManager_h
#define ServerEventManager_h 1


// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZBEventServer.h"
#include "PSS_EventManager.h"

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


class AFX_EXT_CLASS ZBServerEventManager : public PSS_EventManager
{
  public:
      ZBServerEventManager ();
      ~ZBServerEventManager();
      ZBEventServer*    AddEvent( COleDateTime Time, CString fileName, EventResult EventResultValue );

  protected:

  private:
      ZBServerEventManager(const ZBServerEventManager &right);
      const ZBServerEventManager & operator=(const ZBServerEventManager &right);

};



//#undef  AFX_DATA
//#define AFX_DATA


#endif
