// pointdlg.h : header file
//

#ifndef PointDlg_h
#define PointDlg_h 1


#include "zWinUtil32\PointerW.h"
#include "zBaseLib\PlanfObj.h"

/////////////////////////////////////////////////////////////////////////////
// ZDPointerDlg dialog

class ZDPointerDlg : public CDialog
{
// Construction
public:
	virtual ~ZDPointerDlg();
	ZDPointerDlg(CWnd* pParent = NULL);	// standard constructor
	void		Create( CWnd* pParent = NULL );
	virtual int DoModal();
	void 		Close();


	PlanFinObject*	GetSelectedObject() { return m_Obj; };

// Dialog Data
	//{{AFX_DATA(ZDPointerDlg)
	enum { IDD = IDD_POINTER };
	CString	m_sField;
	//}}AFX_DATA

private:
	int				m_ID;
	ZIPointerWnd	m_PointerWindow;
	PlanFinObject*	m_Obj;

// Implementation
protected:
	virtual void 	DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL 	OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(ZDPointerDlg)
	afx_msg LONG OnNotifyPointerObjSelected(UINT message, LONG wParam);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif	// PointDlg_h
