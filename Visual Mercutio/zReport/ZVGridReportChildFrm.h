// ZVGridReportChildFrm.h : interface of the ZVGridReportChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVGridReportChildFrm_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZVGridReportChildFrm_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZVGridChildFrm.h"

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZVGridReportChildFrame : public ZVGridChildFrame
{
	DECLARE_DYNCREATE( ZVGridReportChildFrame )

public:

	ZVGridReportChildFrame();

// Attributes
public:

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVGridReportChildFrame)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~ZVGridReportChildFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
protected:

	//{{AFX_MSG(ZVGridReportChildFrame)
	afx_msg LRESULT OnInitNew( WPARAM, LPARAM );
	afx_msg LRESULT OnInitFromFile( WPARAM, LPARAM );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnUpdateFrameTitle( BOOL bAddToTitle );
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVGridReportChildFrm_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
