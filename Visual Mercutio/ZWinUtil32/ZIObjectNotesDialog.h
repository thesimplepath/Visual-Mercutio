#if !defined(AFX_ZIOBJECTNOTESDIALOG_H__B28C1803_6E71_11D3_9632_0000B45D7C6F__INCLUDED_)
#define AFX_ZIOBJECTNOTESDIALOG_H__B28C1803_6E71_11D3_9632_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIObjectNotesDialog.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZIDialog.h"

#include "ZWinUtil32.h"

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
// ZIObjectNotesDialog dialog

class AFX_EXT_CLASS ZIObjectNotesDialog : public ZIDialog
{
// Construction
public:
	ZIObjectNotesDialog(const CString Comment = "", const CString Username = "", CWnd* pParent = NULL);   // standard constructor
	const CString	GetComment() const { return m_Comment; };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIObjectNotesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIObjectNotesDialog)
	afx_msg void OnDeleteNotes();
	afx_msg void OnChangeNotesEdit();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
// Dialog Data
	//{{AFX_DATA(ZIObjectNotesDialog)
	enum { IDD = IDD_OBJECTNOTES };
	CString	m_Comment;
	//}}AFX_DATA
	CString	m_Username;
	CString	m_SaveText;
	BOOL	m_TextChanged;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIOBJECTNOTESDIALOG_H__B28C1803_6E71_11D3_9632_0000B45D7C6F__INCLUDED_)
