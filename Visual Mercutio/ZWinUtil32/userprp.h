//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//    Source file: UserPrp.h

#ifndef UserPrp_h
#define UserPrp_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// ZUser
#include "zBaseLib\ZUser.h"

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
class AFX_EXT_CLASS ZCUserProperty : public ZIListCtrl  
{
#endif

#ifndef _WIN32 // In 16bit
class AFX_EXT_CLASS ZCUserProperty : public CListBox  
{
#endif
//    DECLARE_DYNAMIC(ZCUserProperty)

  public:
      ZCUserProperty (ZUser* pUser = NULL, BOOL EnableModify = FALSE);
      ~ZCUserProperty();
      BOOL    IsModified() const { return m_IsModified; };

      int    Initialize (ZUser* pUser, BOOL EnableModify = FALSE);
      void    EnableModify (BOOL EnableModify = TRUE) { m_EnableModify = EnableModify; };
      int    Refresh ();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCUserProperty)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCUserProperty)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
    ZCUserProperty(const ZCUserProperty &right);
    const    ZCUserProperty & operator=(const ZCUserProperty &right);
    void    BuildColumns();

  private: //## implementation
        ZUser*            m_pUser;
        BOOL            m_EnableModify;
        BOOL            m_ColumnsBuilt;
        BOOL            m_IsModified;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
