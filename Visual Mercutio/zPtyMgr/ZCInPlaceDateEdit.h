#if !defined(_ZCInPlaceDateEdit_H__)
#define _ZCInPlaceDateEdit_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCInPlaceDateEdit_H.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zProperty\ZIInPlaceEdit.h"
#include "zWinUtil32\ZSearchEdit.h"


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
// ZCInPlaceDateEdit

class AFX_EXT_CLASS ZCInPlaceDateEdit : public ZCSearchEdit, public ZIInPlaceEdit
{
    ZCInPlaceDateEdit(const ZCInPlaceDateEdit& d);
    ZCInPlaceDateEdit operator=(const ZCInPlaceDateEdit& d);

protected:
    DECLARE_DYNAMIC(ZCInPlaceDateEdit)

public:
    ZCInPlaceDateEdit( bool IsReadOnly = false );
    ZCInPlaceDateEdit( ZBDate& DateInitValue, bool IsReadOnly = false );
    virtual ~ZCInPlaceDateEdit();

    // Operations
public:
    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, ZBDate& DateInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText);
    virtual void SetEditText(ZBDate& DateValue);
    // Retreive the text entered
    virtual CString GetEditText() const;

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    // Call when requires to process the extended command
    virtual void OnExtendedCommand();

    bool IsEditCtrlHit( CPoint point ) const;
    bool IsEditButtonCtrlHit( CPoint point ) const;

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

private:
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceDateEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceDateEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Data
private:
};

inline ZCInPlaceDateEdit::ZCInPlaceDateEdit( bool IsReadOnly /*= false*/ )
: ZIInPlaceEdit((double)0, IsReadOnly)
{
}

inline ZCInPlaceDateEdit::ZCInPlaceDateEdit( ZBDate& DateInitValue, bool IsReadOnly /*= false*/ )
: ZIInPlaceEdit(DateInitValue, IsReadOnly)
{
}

inline ZCInPlaceDateEdit::~ZCInPlaceDateEdit()
{
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ZCInPlaceDateEdit_H__)


