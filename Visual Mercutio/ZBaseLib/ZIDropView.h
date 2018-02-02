#if !defined(AFX_ZIDROPVIEW_H__96365A05_C418_4569_836C_1CC5162A7DCA__INCLUDED_)
#define AFX_ZIDROPVIEW_H__96365A05_C418_4569_836C_1CC5162A7DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIDropView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZIDrop.h"
#include "ZVBasicView.h"



#ifdef _ZBASELIBEXPORT
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
// ZIDropView view

class AFX_EXT_CLASS ZIDropView : public ZVBasicView, public ZIDrop
{
protected:
	ZIDropView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ZIDropView)

// Attributes
public:

// Operations
public:

	virtual bool AcceptDrop() const { return false; };

	virtual bool DropItem( CObject* pObj, CPoint pt ) { return false; };

	virtual bool AcceptDropItem( CObject* pObj, CPoint pt ) { return false; };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIDropView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ZIDropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZIDropView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIDROPVIEW_H__96365A05_C418_4569_836C_1CC5162A7DCA__INCLUDED_)
