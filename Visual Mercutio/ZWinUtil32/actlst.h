//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//	Source file: ActCmb.h

#ifndef ActivityLst_h
#define ActivityLst_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\ZProcess.h"
#include "zBaseLib\ZIListCtrl.h"

#ifdef _ZWINUTIL32EXPORT
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


#ifdef _WIN32 // In 32bit
class AFX_EXT_CLASS ZCActivityList : public ZIListCtrl  
{
#endif

#ifndef _WIN32 // In 16bit
class AFX_EXT_CLASS ZCActivityList : public CListBox  
{
#endif
//	DECLARE_DYNAMIC(ZCActivityList)

  public:
      ZCActivityList (ZProcess* pProcess = NULL, int ActivityType = 0, CString ExcludedActivity = "", BOOL StopWhenFound = TRUE, BOOL AttributedActivityOnly = FALSE);
      ~ZCActivityList();
	  CString	GetSelectedActivity();
	  int		GetSelectedActivities( CStringArray Array );


      int	Initialize (ZProcess* pProcess, int ActivityType = 0, CString ExcludedActivity = "", BOOL StopWhenFound = TRUE, BOOL AttributedActivityOnly = FALSE);
      int	Refresh ();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCActivityList)
	//}}AFX_VIRTUAL
  protected:
	//{{AFX_MSG(ZCActivityList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
      ZCActivityList(const ZCActivityList &right);
      const ZCActivityList & operator=(const ZCActivityList &right);

  private: //## implementation
		ZProcess*		m_pProcess;
		int				m_ActivityType;
		CString			m_ExcludedActivity;
		BOOL			m_StopWhenFound;
		BOOL			m_AttributedActivityOnly;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
