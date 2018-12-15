// Source file: UserTreeC.h

#ifndef UserTreeC_h
#define UserTreeC_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// UserTreeI
#include "UserTreeI.h"

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


class AFX_EXT_CLASS ZCUserTree : public ZITreeCtrl
{
  public:
      ZCUserTree (ZUUserManager* pUserManager = NULL);
      virtual ~ZCUserTree();
      void Initialize(ZUUserManager* pUserManager);
      void ReInitialize(ZUUserManager* pUserManager);
      void Refresh();
      ZUser*            GetSelectedUser();
      CString            GetSelectedDepartement();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCUserTree)
    //}}AFX_VIRTUAL
  public:
    //{{AFX_MSG(ZCUserTree)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCUserTree(const ZCUserTree &right);
      const ZCUserTree & operator=(const ZCUserTree &right);

  private: //## implementation
    ZUUserManager*    m_pUserManager;
    bool            m_Invalid;
    ZIUserTree        m_UserTree;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
