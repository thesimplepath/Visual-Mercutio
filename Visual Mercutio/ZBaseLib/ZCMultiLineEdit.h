#if !defined(AFX_ZCMultiLineEdit_H__63999555_6224_42B8_92C9_2440F93DDB78__INCLUDED_)
#define AFX_ZCMultiLineEdit_H__63999555_6224_42B8_92C9_2440F93DDB78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCMultiLineEdit.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZIntelliMultiLineBox.h"
#include "ZBDragEdit.h"


/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class    ZCMultiLineEdit;


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




class ZMultiLineEditButton : public CButton 
{
public:
    ZMultiLineEditButton();

public:
    UINT GetNextID(CWnd* pWnd) const;
    virtual BOOL Create(ZCMultiLineEdit* pEdit, CSize* pSize = NULL, bool Expanded = true, bool ResizeParent = true );
    virtual ~ZMultiLineEditButton();

    void    SetMultiLineEditBoxSize( CSize sz )
    {
        m_Size = sz;
    };



    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZMultiLineEditButton)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
protected:
    //{{AFX_MSG(ZMultiLineEditButton)
    afx_msg void OnClicked();
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    ZCMultiLineEdit*    m_pEdit;
    CFont                m_Font;
    CSize                m_Size;

};


/////////////////////////////////////////////////////////////////////////////
// _ZCExpandedMultiLineEdit window

class _ZCExpandedMultiLineEdit : public ZBDragEdit
{
// Construction
public:
    _ZCExpandedMultiLineEdit( ZCMultiLineEdit* pEditCtrl = NULL, CSize Size = CSize(0,0) );

// Attributes
public:

// Operations
public:
    virtual BOOL Create(ZCMultiLineEdit* pEditCtrl, CSize Size = CSize(0,0) );
    void    SetEditControl( ZCMultiLineEdit* pEditCtrl, CSize Size = CSize(0,0) );

    void    SetMultiLineEditBoxText( CString EditValue );

    CSize    GetExtendedSize() const
    {
        return m_Size;
    };


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZCExpandedMultiLineEdit)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~_ZCExpandedMultiLineEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(_ZCExpandedMultiLineEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    CString m_EditValue;

private:
    ZCMultiLineEdit* m_pEditCtrl;
    CSize             m_Size;
    int                 m_MultiLineEditBoxHeight;
    bool             m_BeingResized;
};


/////////////////////////////////////////////////////////////////////////////
// ZCMultiLineEdit window

class AFX_EXT_CLASS ZCMultiLineEdit : public ZBDragEdit
{
// Construction
public:
    ZCMultiLineEdit( CString EditValue = "", CSize* pSize = NULL );

// Attributes
public:

// Operations
public:
    void    Initialize(    CString EditValue, CSize* pSize = NULL );
    void    Initialize( CSize Size );
    void    Initialize();
    void    SetEditText( CString EditValue, bool Reload = true );
    void    SetMultiLineEditBoxText( CString EditValue );

    void    ExpandBaseEdit();
    void    CollapseBaseEdit( bool CopyTextBack = true );

    bool    EditIsExpanded() const
    {
        return m_EditIsExpanded;
    };

    CSize    GetExtendedSize() const
    {
        return m_Size;
    };
    virtual void OnExtendedSizeHasChanged( int cx, int cy );

    bool    HasFocus() const { return m_HasFocus; };

    bool    IsMultiLineEditBoxVisible() const;
    void    ShowMultiLineEditBox();
    void    HideMultiLineEditBox();

    void    OnMultiLineEditBoxEnter();
    void    OnMultiLineEditBoxEscape();

    // This function allows derived class to permit or not the typed char.
    virtual bool    ValidateChar(UINT nChar, const CString EditText) const { return true; };
    virtual void    OnEditTextChanged() {};
    virtual void    OnEnter() {};
    virtual void    OnEscape() {};

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCMultiLineEdit)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZCMultiLineEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCMultiLineEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    void        SetNewStyle(long lStyleMask, BOOL bSetBits);
    virtual void DestroyEdit( );

protected:
    ZMultiLineEditButton    m_ExpandedButton;
    ZMultiLineEditButton    m_CollapsedButton;
    CString m_EditValue;

private:
    void    CalculateSizeAndPosition();
    void    GetListBoxTextCurSel( CString& Text );

    void    GetMultiLineEditBoxText( CString& Text );

private:
    _ZCExpandedMultiLineEdit    m_ExpandedEditBox;
    CSize                        m_Size;
    int                            m_MultiLineEditBoxHeight;
    bool                        m_HasFocus;
    bool                        m_BeingResized;
    bool                        m_InCreationProcess;
    bool                        m_EditIsExpanded;
    CRect                        m_InitialRect;


};


////////////////////////////////////////////////////////////////////////////



inline bool ZCMultiLineEdit::IsMultiLineEditBoxVisible() const
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()) || !m_ExpandedEditBox.IsWindowVisible())
        return false;
    return true;
}

inline void    ZCMultiLineEdit::ShowMultiLineEditBox()
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;
    m_ExpandedEditBox.ShowWindow( SW_SHOW );
}

inline void    ZCMultiLineEdit::HideMultiLineEditBox()
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;
    m_ExpandedEditBox.ShowWindow( SW_HIDE );
}


inline void    ZCMultiLineEdit::SetMultiLineEditBoxText( CString EditValue )
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;
    m_ExpandedEditBox.SetWindowText( EditValue );
}

inline void    ZCMultiLineEdit::GetMultiLineEditBoxText( CString& Text )
{
    m_ExpandedEditBox.GetWindowText(Text);
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCMultiLineEdit_H__63999555_6224_42B8_92C9_2440F93DDB78__INCLUDED_)
