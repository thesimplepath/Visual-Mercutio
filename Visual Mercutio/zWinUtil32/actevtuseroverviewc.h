// Source file: ActEvtUserOverviewC.h

#ifndef ActEvtUserOverviewC_h
#define ActEvtUserOverviewC_h 1

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


class AFX_EXT_CLASS ZCEventActivityUserOverview : public ZITreeCtrl
{
  public:
      ZCEventActivityUserOverview (ZBEventManager* pEventManager = NULL);
      virtual ~ZCEventActivityUserOverview();
      void Initialize(ZBEventManager* pEventManager);
      void Initialize();
      void Refresh();
      ZBEventActivity*    GetSelectedActivityItem();
      CString            GetSelectedProcess();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCEventActivityUserOverview)
    //}}AFX_VIRTUAL
  public:
    //{{AFX_MSG(ZCEventActivityUserOverview)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCEventActivityUserOverview(const ZCEventActivityUserOverview &right);
      const ZCEventActivityUserOverview & operator=(const ZCEventActivityUserOverview &right);

  private:
    HTREEITEM    AddProcessItem (const CString ProcessName, int IconIndex);
    HTREEITEM    AddSubItem (ZBEventActivity* pData, HTREEITEM hParentTreeItem, int IconIndex);
    CString        FormatActivityText (ZBEventActivity* pData);
    BOOL        ProcessExist( const CString Process );
    void        BuildProcessArray();

  private: //## implementation
    ZBEventManager* m_pEventManager;
    CStringArray    m_ProcessArray;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
