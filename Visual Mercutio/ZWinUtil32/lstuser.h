// lstuser.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIDialog.h"
#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#include "zBaseLib\UserMng.h"


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

/////////////////////////////////////////////////////////////////////////////
// ZIListUserDlg dialog

class AFX_EXT_CLASS ZIListUserDlg : public ZIDialog
{
// Construction
public:
	ZIListUserDlg(ZUUserManager& UserManager, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(ZIListUserDlg)
	enum { IDD = IDD_LIST_OF_USERS };
	CButton	m_InsertButton;
	CListBox	m_ListOfUsers;
	CString	m_sDescription;
	CString	m_Responsible;
	CString	m_EMail;
	CString	m_Departement;
	BOOL	m_IsAdministrator;
	//}}AFX_DATA

	ZUser*	GetUserPtr() { return m_pUser; };

private:
	ZUUserManager&		m_UserManager;
	ZUser*				m_pUser;
	
private:
	void LoadSource();
	void CheckControlState();
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(ZIListUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeListOfUsers();
	afx_msg void OnSource();
	afx_msg void OnDblclkListOfUsers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef  AFX_DATA
//#define AFX_DATA

