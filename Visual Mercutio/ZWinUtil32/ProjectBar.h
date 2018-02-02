// ProjectBar.h : header file
//  

#if !defined(INFOVERBAR_H_INCLUDED)
#define INFOVERBAR_H_INCLUDED

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

#include "ProjectWndC.h"

#include "zWinUtil32\ZWinUtil32.h"

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
// ZIProjectBar class

class AFX_EXT_CLASS ZIProjectBar : public CCJControlBar
{
// Construction
public:
	ZIProjectBar(BOOL OnlyVisible = TRUE);


// Operations
public:
	void Initialize( BOOL OnlyVisible );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIProjectBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZIProjectBar();

// Generated message map functions
protected:
	//{{AFX_MSG(ZIProjectBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZCProjectWindowTree		m_ProjectWindowCtrl;
	BOOL					m_OnlyVisible;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(INFOVERBAR_H_INCLUDED)

