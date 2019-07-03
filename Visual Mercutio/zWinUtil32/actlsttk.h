//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//    Source file: ActLstTk.h

#ifndef ActivityLstTk_h
#define ActivityLstTk_h 1

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
class AFX_EXT_CLASS ZCActivityTaskList : public ZIListCtrl  
{
#endif

#ifndef _WIN32 // In 16bit
class AFX_EXT_CLASS ZCActivityTaskList : public CListBox  
{
#endif

  public:
      ZCActivityTaskList (ZProcess* pProcess = NULL);
      ~ZCActivityTaskList();
      CString    GetSelectedActivity();
      int        GetSelectedActivities( CStringArray Array );
      void        SelectActivity (size_t ActivityIndex, BOOL ShouldClearAllSelection = FALSE);
      void        SelectActivity (const CString ActivityName, BOOL ShouldClearAllSelection = FALSE);
      void        ClearAllSelection();

      int        Initialize (ZProcess* pProcess);
      int        Refresh();
      BOOL        HasBuiltColumns() const { return m_HasBuiltColumns; };

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCActivityTaskList)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCActivityTaskList)
    afx_msg LRESULT OnActivityListChange( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnSelectActivityInTaskList( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCActivityTaskList(const ZCActivityTaskList &right);
      const ZCActivityTaskList & operator=(const ZCActivityTaskList &right);
      void    InsertActivity( ZBaseActivity& Activity, bool IsCurrentActivity );

#ifdef _WIN32
      void    BuildColumns();
#endif

  private: //## implementation
        ZProcess*        m_pProcess;
        BOOL            m_HasBuiltColumns;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
