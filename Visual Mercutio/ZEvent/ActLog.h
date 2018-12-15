#ifndef ActLog_h
#define ActLog_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvent.h"
#include "ActLogFl.h"
#include "ActLogDB.h"

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


class AFX_EXT_CLASS ZUActivityLog 
{
  public:
      ZUActivityLog(CString LogFileName = "", BOOL UseDatabase = FALSE);
      BOOL Create(CString LogFileName, BOOL UseDatabase = FALSE);
      BOOL Initialize();

      ~ZUActivityLog();


      //    The log filename.
      const CString GetLogFileName () const;
      void SetLogFileName (CString value);

      BOOL AppendToLog (ZBEventActivity& EventActivity);
      BOOL ClearLog ();
      BOOL Close ();

  private:
      ZUActivityLog(const ZUActivityLog &right);
      const ZUActivityLog & operator=(const ZUActivityLog &right);

    // Data Members for Class Attributes

       CString m_LogFileName;
       BOOL                        m_UseDatabase;
       ZUActivityLogDatabase*    m_pActivityLogDatabase;
       ZUActivityLogFile*        m_pActivityLogFile;
};



//#undef  AFX_DATA
//#define AFX_DATA


inline const CString ZUActivityLog::GetLogFileName () const
{
  return m_LogFileName;
}

inline void ZUActivityLog::SetLogFileName (CString value)
{
  m_LogFileName = value;
}


#endif
