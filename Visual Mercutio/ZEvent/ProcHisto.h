#ifndef ProcHisto_h
#define ProcHisto_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ActEvent.h"
// ProcHistoDAO
#include "ProcHistoDAO.h"

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


class AFX_EXT_CLASS ZDProcessHistoryDb 
{
public:
	enum DatabaseType { DAODatabase, ODBCDatabase };
  public:
      ZDProcessHistoryDb(CString DatabaseFileName = "", DatabaseType DatabaseTp = DAODatabase);
      BOOL Create(CString DatabaseFileName, DatabaseType DatabaseTp = DAODatabase);
	  BOOL Initialize();

      ~ZDProcessHistoryDb();


      //	The log filename.
      const CString GetDatabaseFileName () const;
      void SetDatabaseFileName (CString value);

      BOOL AppendEventToHistoric (ZBEventActivity& EventActivity);
      BOOL Close ();

  private:
      ZDProcessHistoryDb(const ZDProcessHistoryDb &right);
      const ZDProcessHistoryDb & operator=(const ZDProcessHistoryDb &right);

    // Data Members for Class Attributes

	   CString						m_DatabaseFileName;
	   DatabaseType					m_DatabaseTp;
	   ZDProcessHistoryDAO*			m_pProcessHistoDAO;
};



//#undef  AFX_DATA
//#define AFX_DATA


inline const CString ZDProcessHistoryDb::GetDatabaseFileName () const
{
  return m_DatabaseFileName;
}

inline void ZDProcessHistoryDb::SetDatabaseFileName (CString value)
{
  m_DatabaseFileName = value;
}


#endif // ProcHisto_h
