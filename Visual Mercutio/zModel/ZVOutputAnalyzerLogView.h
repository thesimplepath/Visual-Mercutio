// ZVOutputAnalyzerLogView.h : header file

#if !defined(AFX_ZVOutputAnalyzerLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_)
#define AFX_ZVOutputAnalyzerLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_

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

#include "zBaseLib\ZVOutputView.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 3 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVOutputAnalyzerLogView view

class AFX_EXT_CLASS ZVOutputAnalyzerLogView : public ZVOutputView
{
public:

	DECLARE_DYNAMIC( ZVOutputAnalyzerLogView )

	// Protected constructor used by dynamic creation
	ZVOutputAnalyzerLogView();
	virtual ~ZVOutputAnalyzerLogView();

// Generated message map functions
protected:

	//{{AFX_MSG(ZVOutputAnalyzerLogView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Call back function base on list events
	virtual void OnSelChanged();
	virtual void OnDoubleClick();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVOutputAnalyzerLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_)
