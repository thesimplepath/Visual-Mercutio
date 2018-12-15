
#ifndef ActLogFl_h
#define ActLogFl_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvent.h"

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


class AFX_EXT_CLASS ZUActivityLogFile 
{

  public:
      ZUActivityLogFile (CString LogFileName = "");
      ~ZUActivityLogFile();


      BOOL WriteLine (CString& Line);

      void Create (CString LogFileName);

      BOOL AppendToLog (ZBEventActivity& EventActivity);
      BOOL ClearLog ();
      BOOL Close ();

  private:
      CString    m_LogFileName;
      CFile        m_File;
      BOOL        m_IsOpen;

  private:
      ZUActivityLogFile(const ZUActivityLogFile &right);
      const ZUActivityLogFile & operator=(const ZUActivityLogFile &right);

      BOOL OpenCreate ();
      BOOL OpenRead ();
      BOOL OpenWrite ();

};


//#undef  AFX_DATA
//#define AFX_DATA

#endif
