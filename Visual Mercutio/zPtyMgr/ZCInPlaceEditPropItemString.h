#if !defined(_ZCINPLACEEDITPROPITEMSTRING_H__)
#define _ZCINPLACEEDITPROPITEMSTRING_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCInPlaceEditPropItemString.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zProperty\ZIInPlaceEdit.h"
#include "zBaseLib\PSS_DragEdit.h"


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
// ZCInPlaceEdit

class AFX_EXT_CLASS ZCInPlaceEdit : public PSS_DragEdit, public ZIInPlaceEdit
{
    ZCInPlaceEdit(const ZCInPlaceEdit& d);
    ZCInPlaceEdit& operator=(const ZCInPlaceEdit& d);
protected:
    DECLARE_DYNAMIC(ZCInPlaceEdit)

public:

    ZCInPlaceEdit();
    ZCInPlaceEdit(const CString& srtInitText, bool IsReadOnly = false);
    ZCInPlaceEdit(double dInitValue, bool IsReadOnly = false);
    ZCInPlaceEdit(float fInitValue, bool IsReadOnly = false);
    virtual ~ZCInPlaceEdit();

    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, double dInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, float fInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    // Set the right edit text
    virtual void SetEditText(const CString& strText);
    virtual void SetEditText(double dValue);
    virtual void SetEditText(float fValue);
    // Retrieve the text entered
    virtual CString GetEditText() const;


    // Used to create the edit control
    virtual CWnd* CreateInPlaceEditCtrl(const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        // The base function does nothing
        return NULL;
    };

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Data
protected:

};

inline ZCInPlaceEdit::ZCInPlaceEdit()
    : ZIInPlaceEdit()
{}

inline ZCInPlaceEdit::ZCInPlaceEdit(const CString& strInitText, bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(strInitText, IsReadOnly)
{}

inline ZCInPlaceEdit::ZCInPlaceEdit(double dInitValue, bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(dInitValue, IsReadOnly)
{}

inline ZCInPlaceEdit::ZCInPlaceEdit(float fInitValue, bool IsReadOnly /*= false*/)
    : ZIInPlaceEdit(fInitValue, IsReadOnly)
{}

inline ZCInPlaceEdit::~ZCInPlaceEdit()
{}


/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEditPropItemString

class AFX_EXT_CLASS ZCInPlaceEditPropItemString : public ZCInPlaceEdit
{
    ZCInPlaceEditPropItemString(const ZCInPlaceEditPropItemString& d);
    ZCInPlaceEditPropItemString& operator=(const ZCInPlaceEditPropItemString& d);
protected:
    DECLARE_DYNAMIC(ZCInPlaceEditPropItemString)

public:
    ZCInPlaceEditPropItemString(const CString srtInitText = "", bool IsReadOnly = false);
    ~ZCInPlaceEditPropItemString();

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceEditPropItemString)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

};

inline ZCInPlaceEditPropItemString::ZCInPlaceEditPropItemString(const CString srtInitText /*= ""*/, bool IsReadOnly /*= false*/)
    : ZCInPlaceEdit(srtInitText, IsReadOnly)
{}

inline ZCInPlaceEditPropItemString::~ZCInPlaceEditPropItemString()
{}



/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceEditPropItemNumber

class AFX_EXT_CLASS ZCInPlaceEditPropItemNumber : public ZCInPlaceEdit
{
    ZCInPlaceEditPropItemNumber(const ZCInPlaceEditPropItemNumber& d);
    ZCInPlaceEditPropItemNumber& operator=(const ZCInPlaceEditPropItemNumber& d);
protected:
    DECLARE_DYNAMIC(ZCInPlaceEditPropItemNumber)

public:
    ZCInPlaceEditPropItemNumber(double Value = 0, bool IsReadOnly = false);
    ZCInPlaceEditPropItemNumber(float Value, bool IsReadOnly = false);
    ~ZCInPlaceEditPropItemNumber();

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, double dInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, float fInitValue, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceEditPropItemString)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
};

inline ZCInPlaceEditPropItemNumber::ZCInPlaceEditPropItemNumber(double Value /*= 0*/, bool IsReadOnly /*= false*/)
    : ZCInPlaceEdit(Value, IsReadOnly)
{}

inline ZCInPlaceEditPropItemNumber::ZCInPlaceEditPropItemNumber(float Value, bool IsReadOnly /*= false*/)
    : ZCInPlaceEdit(Value, IsReadOnly)
{}

inline ZCInPlaceEditPropItemNumber::~ZCInPlaceEditPropItemNumber()
{}

#endif
