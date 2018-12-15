
#ifndef ActLogDB_h
#define ActLogDB_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvent.h"
#include "ZDActivityLogRecordset.h"


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


class AFX_EXT_CLASS ZUActivityLogDatabase 
{

  public:
        ZUActivityLogDatabase (CString LogFileName = "");

        ~ZUActivityLogDatabase();

        void Create (CString LogFileName);

        BOOL AppendToLog (ZBEventActivity& EventActivity);
        BOOL ClearLog ();
        BOOL Close ();

        CString GetLogFileName () const;
        
  private:

        CDaoDatabase            m_LogDatabase;
        ZDActivityLogRecordset*    m_pLogRecordset;
        CString                    m_LogFileName;

  private:
        ZUActivityLogDatabase(const ZUActivityLogDatabase &right);

        const ZUActivityLogDatabase & operator=(const ZUActivityLogDatabase &right);

        BOOL OpenRead ();
        BOOL OpenWrite ();

};



//#undef  AFX_DATA
//#define AFX_DATA

#endif
