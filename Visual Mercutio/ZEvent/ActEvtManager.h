// Source file: ActEvtManager.h

#ifndef ActivityEventManager_h
#define ActivityEventManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvent.h"
#include "EventManager.h"


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


class AFX_EXT_CLASS ZBActivityEventManager : public	ZBEventManager
{
  public:
      ZBActivityEventManager ();
      ~ZBActivityEventManager();
	  ZBEventActivity*	AddEvent(ActivityEventType EventType,
								 CString Filename,
								 COleDateTime Time, 
							     CString FolderName,
								 CString ProcessName,
								 COleDateTime ProcessCreationDate,
								 COleDateTime ProcessDueDate,
 								 CString ActivityType,
								 CString ActivityName,
								 COleDateTime ActivityCreationDate,
								 COleDateTime ActivityDueDate,
								 CString Sender,
								 CString Receiver,
								 CString ProcessFilename,
								 CString ExchangeDataFilename,
								 CString ProcessExchangeDataFilename,
								 CString ActivityStatus,
								 CString Comments );

	  virtual ZBEvent*	LoadEventFromFile( const CString Filename );

  protected:

  private:
      ZBActivityEventManager(const ZBActivityEventManager &right);
      const ZBActivityEventManager & operator=(const ZBActivityEventManager &right);


};



//#undef  AFX_DATA
//#define AFX_DATA


#endif
