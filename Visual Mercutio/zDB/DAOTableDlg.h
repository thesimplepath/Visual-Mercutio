#if !defined(AFX_DAOTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define AFX_DAOTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DAOTableDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBaseLib\ZIDialog.h"
#include "zWinUtil32\ZWinUtil32.h"
#include "DAOTableLst.h"


#ifdef _ZDBEXPORT
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
// ZDAOTableDlg dialog

class AFX_EXT_CLASS ZDAOTableDlg : public ZIDialog
{
// Construction
public:
	ZDAOTableDlg(CWnd* pParent = NULL);   // standard constructor
	ZDAOTableDlg(CDaoDatabase* pDB, CWnd* pParent = NULL);   // standard constructor
	CString	GetTableName() const { return m_TableName; };

// Dialog Data
	//{{AFX_DATA(ZDAOTableDlg)
	enum { IDD = IDD_DATABASE_TABLE };
	ZCDAOTableList	m_ListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZDAOTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase* m_pDB;
	CString m_TableName;
	// Generated message map functions
	//{{AFX_MSG(ZDAOTableDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
