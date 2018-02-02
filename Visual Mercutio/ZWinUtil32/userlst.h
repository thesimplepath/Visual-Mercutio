//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//	Source file: UserLst.h

#ifndef UserLst_h
#define UserLst_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// UserMng
#include "zBaseLib\UserMng.h"

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
class AFX_EXT_CLASS ZCUserList : public ZIListCtrl  
{
#endif

#ifndef _WIN32 // In 16bit
class AFX_EXT_CLASS ZCUserList : public CListBox  
{
#endif
//	DECLARE_DYNAMIC(ZCUserList)

  public:
      ZCUserList (ZUUserManager* pUserManager = NULL, CString Departement = "");
      ~ZCUserList();
	  CString	GetSelectedUsername();
	  int		GetSelectedUsernames( CStringArray Array );


      int	Initialize (ZUUserManager* pUserManager, CString Departement = "");
      void	SetDepartement (CString Departement) { m_Departement = Departement; };
      int	Refresh ();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCUserList)
	//}}AFX_VIRTUAL
  protected:
	//{{AFX_MSG(ZCUserList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
    ZCUserList(const ZCUserList &right);
    const	ZCUserList & operator=(const ZCUserList &right);
	void	BuildColumns();

  private: //## implementation
	    ZUUserManager*	m_pUserManager;
		CString			m_Departement;
		BOOL			m_OnlyAdministrator;
		BOOL			m_OnlyNonAdministrator;
		BOOL			m_ColumnsBuilt;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
