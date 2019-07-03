// Source file: ActEvtReminderC.h

#ifndef ActEvtReminderC_h
#define ActEvtReminderC_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\EventManager.h"
#include "zEvent\ActEvtReminderManager.h"
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

class AFX_EXT_CLASS ZCEventActivityViewerReminder : public ZIListCtrl
{
  public:
      ZCEventActivityViewerReminder (ZBActivityEventReminderManager* pReminderManager = NULL);
      virtual ~ZCEventActivityViewerReminder();
      void Initialize (ZBActivityEventReminderManager* pReminderManager);
      void Refresh ();
      ZBEventActivityReminder*    GetSelectedItem() const;

#ifdef _WIN32
    AFX_EXT_API    friend    ZBEventActivityReminder&    operator>>( ZBEventActivityReminder& left, ZCEventActivityViewerReminder& listCtrl );
#endif

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCEventActivityViewerReminder)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCEventActivityViewerReminder)
    afx_msg LRESULT OnNewActivityEvent( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCEventActivityViewerReminder(const ZCEventActivityViewerReminder &right);
      const ZCEventActivityViewerReminder & operator=(const ZCEventActivityViewerReminder &right);

  private:
    BOOL    ColumnsHasBeenBuilt() const { return m_ColumnsHasBeenBuilt; };
    BOOL    BuildColumns();

  private: //## implementation
    ZBActivityEventReminderManager*    m_pReminderManager;
    BOOL                            m_ColumnsHasBeenBuilt;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
