#if !defined(_ZCInPlaceMultiLineEdit_H__)
#define _ZCInPlaceMultiLineEdit_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCInPlaceMultiLineEdit_H.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zProperty\ZIInPlaceEdit.h"
#include "zBaseLib\ZCMultiLineEdit.h"



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
// ZCInPlaceMultiLineEdit

class AFX_EXT_CLASS ZCInPlaceMultiLineEdit : public ZCMultiLineEdit, public ZIInPlaceEdit
{
    ZCInPlaceMultiLineEdit(const ZCInPlaceMultiLineEdit& d);
    ZCInPlaceMultiLineEdit operator=(const ZCInPlaceMultiLineEdit& d);

protected:
    DECLARE_DYNAMIC(ZCInPlaceMultiLineEdit)

public:
    ZCInPlaceMultiLineEdit( bool IsReadOnly = false );
    virtual ~ZCInPlaceMultiLineEdit();

    // Operations
public:

    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, double dInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, float fInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText);
    virtual void SetEditText(double dValue);
    virtual void SetEditText(float fValue);
    // Retreive the text entered
    virtual CString GetEditText() const;

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    // Call when requires to process the extended command
    virtual void OnExtendedCommand();

    // ZCMultiLineEdit call-back. Used to trap when the edit has changed using the extended edit
    virtual void    OnEditTextChanged();

    bool IsEditCtrlHit( CPoint point ) const;
    bool IsEditButtonCtrlHit( CPoint point ) const;

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

    // Returns the extended size of the edit
    virtual CSize GetExtendedSize() const
    {
        return ZCMultiLineEdit::GetExtendedSize();
    };

private:
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceMultiLineEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceMultiLineEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Data
private:
};

inline ZCInPlaceMultiLineEdit::~ZCInPlaceMultiLineEdit()
{
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ZCInPlaceMultiLineEdit_H__)


