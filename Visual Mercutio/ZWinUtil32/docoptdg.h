// docoptdg.h : header file
//
#if !defined(AFX_DOCOPTDG_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_)
#define AFX_DOCOPTDG_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zBaseLib\DocOpt.h"
#include "zRes32\zRes.h"


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
// ZADocOptionDLG dialog

class AFX_EXT_CLASS ZADocOptionDLG : public CDialog
{
// Construction
public:
	ZADocOptionDLG(ZDDocumentOptions *pDocOptions, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(ZADocOptionDLG)
	enum { IDD = IDD_DOCUMENT_OPTIONS };
	CStatic	m_SmallLineCtrl;
	CStatic	m_DashedLineCtrl;
	CStatic	m_DottedCtrl;
	CStatic	m_LinedCtrl;
	int		m_EmtyStyle;
	int		m_SynchronisationYesNo;
	int		m_ShowHiddenFieldYesNoDoc;
	int		m_ShowEmptyLineYesNoDoc;
	int		m_SynchronizationTime;
	CString	m_FLF_Filename;
	int		m_GenerateHeader;
	int		m_SeparatorType;
	int		m_AutomaticFilenameGeneration;
	BOOL	m_PrintEmptyStyleWhenEmpty;
	//}}AFX_DATA

private:
	ZDDocumentOptions*	m_pDocOptions;

private:
	void CheckControlState();

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(ZADocOptionDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnClicked();
	afx_msg void OnSelectFLF();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_DOCOPTDG_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_)
