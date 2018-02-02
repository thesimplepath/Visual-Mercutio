#if !defined(AFX_ZVCOMMANDLINEDLG_H__020B2E04_0186_46D6_8268_A784B3D8CFBE__INCLUDED_)
#define AFX_ZVCOMMANDLINEDLG_H__020B2E04_0186_46D6_8268_A784B3D8CFBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVCommandLineDlg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZSearchEdit.h"

#include "zWinUtil32\zWinUtil32.h"



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
// ZVCommandLineDlg dialog

class AFX_EXT_CLASS ZVCommandLineDlg : public CDialog
{
// Construction
public:
	ZVCommandLineDlg(const CString JobName = "",
					 const CString CommandLine = "",
					 const CString Parameters = "",
					 const CString StartupDir = "",
					 int Priority = 0,
					 int WindowMode = 0,
					 CWnd* pParent = NULL);   // standard constructor


	CString	GetJobName() const
	{
		return m_JobName;
	};
	CString GetCommandLine() const
	{
		return m_CommandLine;
	};
	CString GetParameters() const
	{
		return m_Parameters;
	};
	CString GetStartupDir() const
	{
		return m_StartupDir;
	};
	int GetPriority() const
	{
		return m_Priority;
	};
	int GetWindowMode() const
	{
		return m_WindowMode;
	};

private:
// Dialog Data
	//{{AFX_DATA(ZVCommandLineDlg)
	enum { IDD = IDD_COMMANDLINE };
	ZCSearchEdit	m_Arguments;
	CComboBox	m_PriorityList;
	CComboBox	m_WindowModeList;
	ZCSearchEdit	m_StartupDirectory;
	ZCSearchEdit	m_Application;
	CString			m_JobName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVCommandLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVCommandLineDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnFileArg();
	afx_msg void OnDirArg();
	afx_msg void OnSysVarArg();
	afx_msg void OnChangeJobname();
	afx_msg void OnChangeApplication();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL	IsOK();
    void	SaveValuesToObject();
	void	CheckControlState();

private:
	CString m_CommandLine;
	CString m_Parameters;
	CString m_StartupDir;
	int m_Priority;
	int m_WindowMode;

	bool m_JobNameHasChanged;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVCOMMANDLINEDLG_H__020B2E04_0186_46D6_8268_A784B3D8CFBE__INCLUDED_)
