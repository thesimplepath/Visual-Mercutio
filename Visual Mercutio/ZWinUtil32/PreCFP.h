// PreCFP.h : header file

#if !defined(AFX_PRECFP_H__DAECC7A4_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
#define AFX_PRECFP_H__DAECC7A4_4817_11D3_95FB_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#else
	#include "ZWinUtil32.h"
#endif

#include "ZSearchEdit.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 5 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIPreConditionFormProc dialog

class AFX_EXT_CLASS ZIPreConditionFormProc : public ZIWizardDialog
{
// Construction
public:

	// Standard constructor
	ZIPreConditionFormProc( CString			ActivityName,
							CStringArray&	FormNameArray,
							BOOL			FileRequired,
							BOOL			IsLast,
							BOOL			IsProcess,
							CStringArray&	FileArray,
							CWnd*			pParent			= NULL);

	// Dialog Data
	//{{AFX_DATA(ZIPreConditionFormProc)
	enum { IDD = IDD_WZPREACT_FORMPROC };
	ZCSearchEdit	m_Filename;
	CString	m_ActivityName;
	CString	m_FormName;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIPreConditionFormProc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIPreConditionFormProc)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void BuildText( int FormIndex );
	void CheckStates();
	BOOL CheckFiles();

private:

	CStringArray&	m_FormNameArray;
	CStringArray&	m_FileArray;

	BOOL			m_FileRequired;
	BOOL			m_IsLast;
	BOOL			m_IsProcess;

	int				m_CurrentFormIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRECFP_H__DAECC7A4_4817_11D3_95FB_0000B45D7C6F__INCLUDED_)
