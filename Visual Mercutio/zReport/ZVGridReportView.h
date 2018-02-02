// ZVGridReportView.h : interface of the ZVGridReportView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVGridReportView_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZVGridReportView_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

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

#include "ZVGridView.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDGridReportDocument;

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

class AFX_EXT_CLASS ZVGridReportView : public ZVGridView
{
protected:

	// Create from serialization only
	GXDECLARE_DYNCREATE( ZVGridReportView )
	ZVGridReportView();

// Operations
public:

	// User attributes initialization 
	virtual void SetupUserAttributes();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVGridReportView)
	public:
	virtual void OnDraw(CDC* pDC);	// overridden to draw this view
	protected:
	virtual void OnInitialUpdate();	// called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~ZVGridReportView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(ZVGridReportView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVGridReportView_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
