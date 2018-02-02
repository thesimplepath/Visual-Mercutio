// Source file: ActEvtOverviewC.h

#ifndef ActEvtOverviewC_h
#define ActEvtOverviewC_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\EventManager.h"
#include "zEvent\ActEvent.h"
#include "zBaseLib\ZITreeCtl.h"


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

class AFX_EXT_CLASS ZCEventActivityOverview : public ZITreeCtrl
{
  public:
      ZCEventActivityOverview (ZBEventManager* pEventManager = NULL);
      virtual ~ZCEventActivityOverview();
      void Initialize(ZBEventManager* pEventManager);
	  void Initialize();
      void Refresh();
	  ZBEventActivity*	GetSelectedActivityItem();
	  CString			GetSelectedUser();
	  CString			GetSelectedProcess();

	  CObArray&			GetUserActivities(const CString User);
	  CObArray&			GetProcessActivities(const CString Process, const CString User);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCEventActivityOverview)
	//}}AFX_VIRTUAL
  public:
	//{{AFX_MSG(ZCEventActivityOverview)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
      ZCEventActivityOverview(const ZCEventActivityOverview &right);
      const ZCEventActivityOverview & operator=(const ZCEventActivityOverview &right);


	class ElementType
	{
		public:
			enum	ActivityType { User, Process, Activity };
		public:
			ElementType( ZBEventActivity* pData = NULL, ActivityType Type = Activity );
			ElementType( const CString Name, ActivityType Type );
			~ElementType();
			ZBEventActivity*	m_pData;
			CString				m_Name;
			ActivityType		m_Type;
	};

  private:
	HTREEITEM	AddUserItem (ElementType* pElement, int IconIndex);
	HTREEITEM	AddProcessItem (ElementType* pElement, HTREEITEM hParentTreeItem, int IconIndex);
	HTREEITEM	AddSubItem (ElementType* pElement, HTREEITEM hParentTreeItem, int IconIndex);
	CString		FormatActivityText (ZBEventActivity* pData);
	BOOL		UserExist( const CString User );
	BOOL		ProcessExist( const CString Process );
	BOOL		EventPtrExist( ZBEventActivity* pActEvent );
	void		BuildUserArray();
	void		BuildProcessArray();
	void		DeleteAllElements();
	void		DeleteAllSubElements( HTREEITEM hTreeItem );

  private: //## implementation
	ZBEventManager* m_pEventManager;
	CStringArray	m_UserArray;
	CStringArray	m_ProcessArray;
	CObArray		m_ActPtrArray;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
