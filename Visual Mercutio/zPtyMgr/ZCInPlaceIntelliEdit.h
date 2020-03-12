#if !defined(_ZCInPlaceIntelliEdit_H__)
#define _ZCInPlaceIntelliEdit_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCInPlaceIntelliEdit_H.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_IntelliEdit.h"
#include "zProperty\ZIInPlaceEdit.h"


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
// ZCInPlaceIntelliEdit

class AFX_EXT_CLASS ZCInPlaceIntelliEdit : public PSS_IntelliEdit, public ZIInPlaceEdit
{
    ZCInPlaceIntelliEdit(const ZCInPlaceIntelliEdit& d);
    ZCInPlaceIntelliEdit operator=(const ZCInPlaceIntelliEdit& d);

protected:
    DECLARE_DYNAMIC(ZCInPlaceIntelliEdit)

public:
    ZCInPlaceIntelliEdit(bool IsReadOnly = false);
    virtual ~ZCInPlaceIntelliEdit();

    // Operations
public:
    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, double dInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, float fInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText);
    virtual void SetEditText(double dValue);
    virtual void SetEditText(float fValue);
    // Retrieve the text entered
    virtual CString GetEditText() const;

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Call when requires to process the extended command
    virtual void OnExtendedCommand();

    // ZCIntelliEdit call-back. Used to trap when the user selects and item from the list of values
    virtual void    OnItemSelectedFromList();

    bool IsEditCtrlHit(CPoint point) const;
    bool IsEditButtonCtrlHit(CPoint point) const;

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

    // Returns the extended size of the edit
    virtual CSize GetExtendedSize() const
    {
        return PSS_IntelliEdit::GetExtendedSize();
    };

private:
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceIntelliEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceIntelliEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Data
private:
};

inline ZCInPlaceIntelliEdit::~ZCInPlaceIntelliEdit()
{}

#endif
