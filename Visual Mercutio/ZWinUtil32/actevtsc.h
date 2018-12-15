// Source file: ActEvtSC.h

#ifndef ActEvtSC_h
#define ActEvtSC_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\EventManager.h"
#include "zEvent\ActEvent.h"
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


class AFX_EXT_CLASS ZCEventActivity : public ZIListCtrl
{
  public:
      ZCEventActivity (ZBEventManager* pEventManager = NULL);
      virtual ~ZCEventActivity();
      void Initialize (ZBEventManager* pEventManager);
      void Refresh ();
      ZBEventActivity*    GetSelectedItem() const;

#ifdef _WIN32
    AFX_EXT_API    friend    ZBEventActivity&    operator>>( ZBEventActivity& left, ZCEventActivity& listCtrl );
#endif

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCEventActivity)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCEventActivity)
    afx_msg LRESULT OnNewActivityEvent( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCEventActivity(const ZCEventActivity &right);
      const ZCEventActivity & operator=(const ZCEventActivity &right);

  private:
    BOOL    ColumnsHasBeenBuilt() const { return m_ColumnsHasBeenBuilt; };
    BOOL    BuildColumns();

  private: //## implementation
    ZBEventManager* m_pEventManager;
    BOOL            m_ColumnsHasBeenBuilt;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
