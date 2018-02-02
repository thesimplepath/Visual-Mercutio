#if !defined(_ZCPROPERTYDESCRIPTION_H__)
#define _ZCPROPERTYDESCRIPTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCPropertyDescription.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zBaseLib\ZIObserver.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBProperty;
class ZIObserverMsg;



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
// ZCPropertyDescription window

class AFX_EXT_CLASS ZCPropertyDescription : public CStatic, public ZIObserver
{
// Construction
public:
	ZCPropertyDescription();

// Operations
public:
	// Observer call back
	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCPropertyDescription)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZCPropertyDescription();

	// Generated message map functions
protected:
	//{{AFX_MSG(ZCPropertyDescription)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


private:
	void EmptyControlData();
	void UpdateControlData(ZBProperty* pProp);


private:
	CString m_Title;
	CString m_Description;

	COLORREF m_crBackground;
	COLORREF m_crText;
	CFont m_Font;
	CFont m_FontBold;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ZCPROPERTYDESCRIPTION_H__)
