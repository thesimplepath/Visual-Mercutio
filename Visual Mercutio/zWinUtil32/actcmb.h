//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//    Source file: ActCmb.h

#ifndef ActivityCmb_h
#define ActivityCmb_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zEvent\ZProcess.h"


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
class AFX_EXT_CLASS ZCActivityCombo : public CCJFlatComboBox  
{
#endif

#ifndef _WIN32 // In 16bit
class AFX_EXT_CLASS ZCActivityCombo : public CComboBox  
{
#endif
//    DECLARE_DYNAMIC(ZCActivityCombo)

  public:
      ZCActivityCombo (ZProcess* pProcess = NULL, int ActivityType = 0, CString ExcludedActivity = "", BOOL StopWhenFound = TRUE, BOOL AttributedActivityOnly = FALSE);
      ~ZCActivityCombo();
      CString    GetSelectedActivity();
      void        SelectActivity( const CString ActivityName );


      int    Initialize (ZProcess* pProcess, int ActivityType = 0, CString ExcludedActivity = "", BOOL StopWhenFound = TRUE, BOOL AttributedActivityOnly = FALSE);
      int    Refresh();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCActivityCombo)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCActivityCombo)
    //}}AFX_MSG
//    DECLARE_MESSAGE_MAP()
  private:
      ZCActivityCombo(const ZCActivityCombo &right);
      const ZCActivityCombo & operator=(const ZCActivityCombo &right);

  private: //## implementation
        ZProcess*        m_pProcess;
        int                m_ActivityType;
        CString            m_ExcludedActivity;
        BOOL            m_StopWhenFound;
        BOOL            m_AttributedActivityOnly;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
