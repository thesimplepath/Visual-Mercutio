// Source file: UserTreeI.h

#ifndef UserTreeI_h
#define UserTreeI_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// UserMng
#include "zBaseLib\UserMng.h"

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


class AFX_EXT_CLASS ZIUserTree
{
  public:
      ZIUserTree (ZITreeCtrl* pTreeCtrl = NULL, ZUUserManager* pUserManager = NULL);
      virtual ~ZIUserTree();
      void Initialize(ZITreeCtrl* pTreeCtrl, ZUUserManager* pUserManager);
      void ReInitialize(ZUUserManager* pUserManager);
      void Refresh();
	  ZUser*			GetSelectedUser();
	  CString			GetSelectedDepartement();

	  void	OnUserListChanged();

  private:
      ZIUserTree(const ZIUserTree &right);
      const ZIUserTree & operator=(const ZIUserTree &right);
	  void	CreateTree();
	  void	InitializeTree();

  private:
	HTREEITEM	AddDepartementItem (const CString Departement, int IconIndex);
	HTREEITEM	AddUserItem (ZUser* pData, HTREEITEM hParentTreeItem, int IconIndex);
	BOOL		DepartementExist( const CString Departement );
	void		BuildDepartementArray();

  private: //## implementation
	ZITreeCtrl*		m_pTreeCtrl;
    ZUUserManager*	m_pUserManager;
	CStringArray	m_DepartementArray;
	bool			m_Invalid;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
