#if !defined(AFX_ZINTELLILISTBOX_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_)
#define AFX_ZINTELLILISTBOX_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIntelliListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZCIntelliEdit;


/////////////////////////////////////////////////////////////////////////////
// ZIntelliListBox window

class ZIntelliListBox : public CListBox
{
// Construction
public:
    ZIntelliListBox(ZCIntelliEdit* pEditCtrl = NULL);


// Operations
public:
    void    SetEditControl( ZCIntelliEdit* pEditCtrl );

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIntelliListBox)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZIntelliListBox();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZIntelliListBox)
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    void    TranslateSelectionToEditControl();

private:
    ZCIntelliEdit*    m_pEditCtrl;
    int                m_CurrentSelectionOnDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZINTELLILISTBOX_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_)
