// Source file: ActEvtToDoMgr.h

#ifndef ActivityEventToDoManager_h
#define ActivityEventToDoManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvtManager.h"


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


class AFX_EXT_CLASS ZBActivityEventToDoManager : public	ZBActivityEventManager
{
  public:
      ZBActivityEventToDoManager ();
      ~ZBActivityEventToDoManager();

	  virtual ZBEvent*	LoadEventFromFile( const CString Filename );

  protected:

  private:
      ZBActivityEventToDoManager(const ZBActivityEventToDoManager &right);
      const ZBActivityEventToDoManager & operator=(const ZBActivityEventToDoManager &right);


};



//#undef  AFX_DATA
//#define AFX_DATA


#endif
