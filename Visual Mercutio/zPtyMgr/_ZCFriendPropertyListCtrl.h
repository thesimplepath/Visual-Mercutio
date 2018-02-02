#if !defined(AFX__ZCFRIENDPROPERTYLISTCTRL_H__C583EE57_E4B2_4D26_84D4_50BA2ADCE19E__INCLUDED_)
#define AFX__ZCFRIENDPROPERTYLISTCTRL_H__C583EE57_E4B2_4D26_84D4_50BA2ADCE19E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCFriendPropertyListCtrl.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// _ZCFriendPropertyListCtrl window

class _ZCFriendPropertyListCtrl : public CListCtrl
{
// Construction
public:
	_ZCFriendPropertyListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(_ZCFriendPropertyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~_ZCFriendPropertyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(_ZCFriendPropertyListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__ZCFRIENDPROPERTYLISTCTRL_H__C583EE57_E4B2_4D26_84D4_50BA2ADCE19E__INCLUDED_)
