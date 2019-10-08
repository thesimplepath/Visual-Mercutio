/****************************************************************************
 * ==> PSS_IntelliEdit -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense edit box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IntelliEditH
#define PSS_IntelliEditH

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
#include "ZIntelliListBox.h"
#include "PSS_DragEdit.h"

// forward class declaration
class ZCIntelliEdit;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Intellisense edit button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class ZIntelliEditButton : public CButton
{
public:
    ZIntelliEditButton();

    UINT GetNextID(CWnd* pWnd) const;
    virtual BOOL Create(ZCIntelliEdit* pEdit, CStringArray* pArrayOfValues, CSize* pSize = NULL);
    virtual ~ZIntelliEditButton();
    CWnd*    GetListBoxWnd() const
    {
        return (CWnd*)&m_ListBoxOfValues;
    };
    void    SetArrayOfValues(CStringArray* pArrayOfValues, bool Reload = true);
    void    ReloadListOfValues();

    void    SetListBoxSize(CSize sz)
    {
        m_Size = sz;
        //        CalculateSizeAndPosition();
    };
    int        GetListBoxCurSel();
    void    GetListBoxTextCurSel(CString& Text);
    void    SetListBoxCurSel(int CurSel);
    void    ListBoxSelectString(LPCTSTR lpszItem, int nStartAfter = -1);
    bool    IsFloatingListIsVisible() const;
    void    ShowListBox();
    void    HideListBox();



    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIntelliEditButton)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
protected:
    //{{AFX_MSG(ZIntelliEditButton)
    afx_msg void OnClicked();
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    ZCIntelliEdit*    m_pEdit;
    CFont            m_Font;

private:
    void    CalculateSizeAndPosition();
    void    ManageEntries();

private:
    CStringArray*        m_pArrayOfValues;
    ZIntelliListBox        m_ListBoxOfValues;
    int                    m_ListBoxHeight;
    CSize                m_Size;

};

//---------------------------------------------------------------------------
// PSS_IntelliEditBtn
//---------------------------------------------------------------------------
inline bool ZIntelliEditButton::IsFloatingListIsVisible() const
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()) || !m_ListBoxOfValues.IsWindowVisible())
        return false;
    return true;
}

inline int    ZIntelliEditButton::GetListBoxCurSel()
{
    if (!IsFloatingListIsVisible())
        return LB_ERR;
    return m_ListBoxOfValues.GetCurSel();
}

inline void    ZIntelliEditButton::SetListBoxCurSel(int CurSel)
{
    if (!IsFloatingListIsVisible())
        return;
    m_ListBoxOfValues.SetCurSel(CurSel);
}

inline void    ZIntelliEditButton::GetListBoxTextCurSel(CString& Text)
{
    int    CurSel = GetListBoxCurSel();
    if (CurSel == LB_ERR)
        Text = "";
    else
        m_ListBoxOfValues.GetText(CurSel, Text);
}

inline void    ZIntelliEditButton::ListBoxSelectString(LPCTSTR lpszItem, int nStartAfter)
{
    m_ListBoxOfValues.SelectString(nStartAfter, lpszItem);
}


inline void    ZIntelliEditButton::ShowListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;
    m_ListBoxOfValues.ShowWindow(SW_SHOW);
}

inline void    ZIntelliEditButton::HideListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;
    m_ListBoxOfValues.ShowWindow(SW_HIDE);
}

/**
* Intellisense edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZCIntelliEdit : public PSS_DragEdit
{
public:
    ZCIntelliEdit(CStringArray* pArrayOfValues = NULL, CSize* pSize = NULL);

    void    Initialize(CStringArray* pArrayOfValues, CSize* pSize = NULL);
    void    Initialize();
    void    SetArrayOfValues(CStringArray* pArrayOfValues, bool Reload = true);
    void    ReloadListOfValues();

    CSize    GetExtendedSize() const
    {
        return m_Size;
    };
    virtual void OnExtendedSizeHasChanged(int cx, int cy);

    bool    HasFocus() const
    {
        return m_HasFocus;
    };

    bool    IsFloatingListIsVisible() const;
    void    ShowListBox();
    void    HideListBox();

    bool    IsHistoryFloatingListIsVisible() const;
    void    ShowHistoryListBox();
    void    HideHistoryListBox();

    // This function allows derived class to permit or not the typed char.
    virtual bool    ValidateChar(UINT nChar, const CString EditText) const
    {
        return true;
    };
    virtual void    OnItemSelectedFromList()
    {};
    virtual void    OnEnter()
    {};
    virtual void    OnEscape()
    {};

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZCIntelliEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZCIntelliEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCIntelliEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    virtual void DestroyEdit();

protected:
    ZIntelliEditButton    m_Button;
    CStringArray*        m_pArrayOfValues;

private:
    int        BuildSimilarList(CString EditText);
    bool    CompareSimilar(CString PartialText, CString FullText);
    void    CalculateSizeAndPosition();
    int        GetListBoxCurSel();
    void    GetListBoxTextCurSel(CString& Text);
    void    SetListBoxCurSel(int CurSel);
    void    ListBoxSelectString(LPCTSTR lpszItem, int nStartAfter = -1);

    int        GetHistoryListBoxCurSel();
    void    GetHistoryListBoxTextCurSel(CString& Text);
    void    SetHistoryListBoxCurSel(int CurSel);
    void    HistoryListBoxSelectString(LPCTSTR lpszItem, int nStartAfter = -1);

private:
    ZIntelliListBox    m_ListBoxOfValues;
    CSize            m_Size;
    int                m_ListBoxHeight;
    bool            m_HasFocus;
    bool            m_BeingResized;


};

//---------------------------------------------------------------------------
// PSS_IntelliEdit
//---------------------------------------------------------------------------
inline int    ZCIntelliEdit::GetListBoxCurSel()
{
    if (!IsFloatingListIsVisible())
        return LB_ERR;
    return m_ListBoxOfValues.GetCurSel();
}

inline void    ZCIntelliEdit::SetListBoxCurSel(int CurSel)
{
    if (!IsFloatingListIsVisible())
        return;
    m_ListBoxOfValues.SetCurSel(CurSel);
}

inline void    ZCIntelliEdit::GetListBoxTextCurSel(CString& Text)
{
    int    CurSel = GetListBoxCurSel();
    if (CurSel == LB_ERR)
        Text = "";
    else
        m_ListBoxOfValues.GetText(CurSel, Text);
}

inline void    ZCIntelliEdit::ListBoxSelectString(LPCTSTR lpszItem, int nStartAfter)
{
    m_ListBoxOfValues.SelectString(nStartAfter, lpszItem);
}


inline bool ZCIntelliEdit::IsFloatingListIsVisible() const
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()) || !m_ListBoxOfValues.IsWindowVisible())
        return false;
    return true;
}

inline void    ZCIntelliEdit::ShowListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;
    m_ListBoxOfValues.ShowWindow(SW_SHOW);
}

inline void    ZCIntelliEdit::HideListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;
    m_ListBoxOfValues.ShowWindow(SW_HIDE);
}


inline void    ZCIntelliEdit::ReloadListOfValues()
{
    if (!::IsWindow(m_Button.GetSafeHwnd()))
        return;
    m_Button.ReloadListOfValues();
}

inline int    ZCIntelliEdit::GetHistoryListBoxCurSel()
{
    return m_Button.GetListBoxCurSel();
}

inline void    ZCIntelliEdit::SetHistoryListBoxCurSel(int CurSel)
{
    m_Button.SetListBoxCurSel(CurSel);
}

inline void    ZCIntelliEdit::GetHistoryListBoxTextCurSel(CString& Text)
{
    m_Button.GetListBoxTextCurSel(Text);
}

inline void    ZCIntelliEdit::HistoryListBoxSelectString(LPCTSTR lpszItem, int nStartAfter)
{
    m_Button.ListBoxSelectString(lpszItem, nStartAfter);
}


inline bool ZCIntelliEdit::IsHistoryFloatingListIsVisible() const
{
    return m_Button.IsFloatingListIsVisible();
}

inline void    ZCIntelliEdit::ShowHistoryListBox()
{
    m_Button.ShowListBox();
}

inline void    ZCIntelliEdit::HideHistoryListBox()
{
    m_Button.HideListBox();
}

#endif
