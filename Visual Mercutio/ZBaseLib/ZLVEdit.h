// ZLVEdit.h : interface of the CListEditView class
//

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZLVEDIT_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_)
#define AFX_ZLVEDIT_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




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
// ZLVEdit 

/////////////////////////////////////////////////////////////////////////////
// CListEditCtrl window

class AFX_EXT_CLASS ZLVEdit : public CEdit
{
// Construction
public:
    ZLVEdit(int iItem, int iSubItem, CString sInitText);
// Attributes
public:

// Operations
public:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CListEditCtrl)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZLVEdit(){};
private:    
    int m_iItem;
    int m_iSubItem;    
    CString m_strInitText;
    BOOL  m_bVK_ESCAPE;
    int m_x;
    int m_y;
    // Generated message map functions
protected:
    //{{AFX_MSG(CListEditCtrl)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnNcDestroy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);    
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZLVEDIT_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_)
