#if !defined(_ZCInPlaceListBox_H__)
#define _ZCInPlaceListBox_H__

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zProperty\PSS_InPlaceEdit.h"

// forward class declaration
class ZCInPlaceListBox;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceEdit

// todo -cWarning -oJean: WARNING another class is already named PSS_InPlaceEdit!!!
class _ZCInPlaceEdit : public CEdit
{
public:
    _ZCInPlaceEdit();
    virtual ~_ZCInPlaceEdit();

    void SetOwnerListBox(ZCInPlaceListBox* pOwnerList)
    {
        m_pOwnerList = pOwnerList;
    };

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZCInPlaceEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZCInPlaceEdit)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    _ZCInPlaceEdit(const _ZCInPlaceEdit& d);
    _ZCInPlaceEdit& operator=(const _ZCInPlaceEdit& d);

private:
    ZCInPlaceListBox* m_pOwnerList;
};


/////////////////////////////////////////////////////////////////////////////
// _ZCInPlaceListBox

class _ZCInPlaceListBox : public CListBox
{
public:
    _ZCInPlaceListBox();
    virtual ~_ZCInPlaceListBox();

    void SetOwnerListBox(ZCInPlaceListBox* pOwnerList)
    {
        m_pOwnerList = pOwnerList;
    };

    // Operations
protected:
    void ProcessSelected(bool bProcess = true);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZCInPlaceListBox)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZCInPlaceListBox)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    _ZCInPlaceListBox(const _ZCInPlaceListBox& d);
    _ZCInPlaceListBox& operator=(const _ZCInPlaceListBox& d);

private:
    ZCInPlaceListBox* m_pOwnerList;
};


/////////////////////////////////////////////////////////////////////////////
// ZCInPlaceListBox

class AFX_EXT_CLASS ZCInPlaceListBox : public CWnd, public PSS_InPlaceEdit
{
protected:
    DECLARE_DYNAMIC(ZCInPlaceListBox)

public:
    ZCInPlaceListBox(bool IsReadOnly = false);
    virtual ~ZCInPlaceListBox();

    // Attributes
public:
    int GetCurrentSelection() const;
    DWORD GetDWordData() const;
    CString GetTextData() const;

    // Operations
public:
    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, const CRect& rect, DWORD exDwStyle = 0);
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText);
    // Retrieve the text entered
    virtual CString GetEditText() const;

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    int SetCurSel(int nSelect, bool bSendSetData = true);
    int SetCurSel(const CString Value, bool bSendSetData = true);

    int AddString(LPCTSTR pStrText, DWORD nData = 0);

    bool IsEditCtrlHit(CPoint point) const;
    bool IsEditButtonCtrlHit(CPoint point) const;

    void ResetContent();
    void ResetListBoxHeight();

    // Called by the edit child control when a key is pressed
    void NotifyEditKeyPressed(UINT nChar);
    // Called by the listbox child control when something has to be done
    void NotifiyListBoxAction(UINT nAction);

    // Virtual function to cancel and save the edition
    virtual void CancelEdit();
    virtual void SaveValue();

private:
    ZCInPlaceListBox(const ZCInPlaceListBox& d);
    ZCInPlaceListBox operator=(const ZCInPlaceListBox& d);

    void SetCurSelToEdit(int nSelect);
    void ApplyListBoxValueToEdit();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInPlaceListBox)
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCInPlaceListBox)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    void HideListBox();
    void SetFocusToEdit();
    void MoveSelection(UINT Key);

    // Data
private:
    static int    m_nButtonDx;

    int            m_nCurrentSelection;
    CString        m_strInitialValueText;

    _ZCInPlaceEdit m_wndEdit;
    _ZCInPlaceListBox m_wndList;
};

inline ZCInPlaceListBox::~ZCInPlaceListBox()
{}

inline int ZCInPlaceListBox::GetCurrentSelection() const
{
    return m_nCurrentSelection;
}

inline DWORD ZCInPlaceListBox::GetDWordData() const
{
    return m_nCurrentSelection != -1 ? m_wndList.GetItemData(m_nCurrentSelection) : 0;
}

#endif
