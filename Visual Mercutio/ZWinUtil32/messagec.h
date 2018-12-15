// Source file: MessageC.h

#ifndef MessageC_h
#define MessageC_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\EventManager.h"
#include "zEvent\ZBEventServer.h"
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

class AFX_EXT_CLASS ZCEventLog : public ZIListCtrl
{
  public:
      ZCEventLog (ZBEventManager* pEventManager = NULL);
      ~ZCEventLog();
      void Initialize (ZBEventManager* pEventManager);
      void Refresh ();

#ifdef _WIN32
    AFX_EXT_API    friend    ZBEventServer&    operator>>( ZBEventServer& left, ZCEventLog& listCtrl );
#endif

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCEventLog)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCEventLog)
    afx_msg LRESULT OnNewEvent( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCEventLog(const ZCEventLog &right);
      const ZCEventLog & operator=(const ZCEventLog &right);

  private:
    BOOL    ColumnsHasBeenBuilt() const { return m_ColumnsHasBeenBuilt; };
    BOOL    BuildColumns();

  private: //## implementation
    ZBEventManager* m_pEventManager;
    BOOL            m_ColumnsHasBeenBuilt;

};


#endif
